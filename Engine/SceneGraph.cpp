#include "SceneGraph.h"

SceneGraph::SceneGraph(Shader &shader) : _shader(shader) {
    glUseProgram(shader.getId());
}

SceneGraph::SceneGraph(const AssetLoader::gltf& loadedFile, Shader &shader) : SceneGraph(shader){
    Json::Value gltf = loadedFile.j;
    vector<vector<char>> data = loadedFile.buffers;

    auto getBufferView = [&gltf, &data](unsigned int accessorID) -> std::tuple<std::vector<char>, unsigned int, unsigned int>{
        Json::Value bufferView = gltf["bufferViews"][gltf["accessors"][accessorID]["bufferView"].asUInt()];
        return std::make_tuple(data[bufferView["buffer"].asUInt()], bufferView["byteLength"].asUInt(), bufferView["byteOffset"].asUInt());
    };

    auto parseVector3 = [&](Json::Value node){
        return Vector3{node[0].asFloat(), node[1].asFloat(), node[2].asFloat()};
    };

    auto setNodeTransforms = [&](Json::Value node, EmptyObject obj){
        if (node.isMember("translation")) {
            obj.setPosition(parseVector3(node["translation"]));
        }
        if (node.isMember("rotation")) {
            obj.setRotation(Vector3::QuaternionToEuler(node["rotation"][0].asFloat(), node["rotation"][1].asFloat(), node["rotation"][2].asFloat(), node["rotation"][3].asFloat()));
        }
        if (node.isMember("scale")) {
            obj.setScale(parseVector3(node["scale"]));
        }
    };

    for(Json::Value& material : gltf["materials"]){
        Json::Value& mData = material["pbrMetallicRoughness"];
        Json::Value& bcf = mData["baseColorFactor"];
        Vector3 const color = Vector3(bcf[0].asFloat(), bcf[1].asFloat(), bcf[2].asFloat());
        this->materials[material["name"].asCString()] = PBRMetallicRoughness{color, mData["metallicFactor"].asFloat(), mData["roughnessFactor"].asFloat()};
    }

    for(Json::Value& mesh : gltf["meshes"]) {
        Json::Value& primitive = mesh["primitive"][0];

        auto posArgs = getBufferView(primitive["attributes"]["POSITION"].asUInt());
        auto texArgs = getBufferView(primitive["attributes"]["TEXCOORD_0"].asUInt());
        auto normArgs = getBufferView(primitive["attributes"]["NORMAL"].asUInt());
        auto indexArgs = getBufferView(primitive["indices"].asUInt());

        this->meshes[mesh["name"].asCString()] = Mesh{
                std::apply(dataFromAccessor<float>, posArgs),
                std::apply(dataFromAccessor<float>, texArgs),
                std::apply(dataFromAccessor<float>, normArgs),
                std::apply(dataFromAccessor<unsigned int>, indexArgs)
        };
    }

    std::vector<unprocessedPortalLink> unprocessedPortalLinks;
    for(Json::Value& node : gltf["nodes"]){
        if(node.isMember("mesh")){
            Object3D::Tags tag = Object3D::Tags::def;
            if (node.isMember("extras") && node["extras"].isMember("linked_portal")){
                unprocessedPortalLinks.push_back({node["name"].asCString(), node["extras"]["linked_portal"]["name"].asCString()});
                tag = Object3D::Tags::portal;
            }

            Object3D obj = Object3D{meshes[gltf["meshes"][node["mesh"].asUInt()]["name"].asCString()], shader, materials[gltf["materials"][gltf["meshes"][node["mesh"].asUInt()]["primitives"][0]["material"].asUInt()]["name"].asCString()], tag};
            this->objects[node["name"].asCString()] = obj;
            setNodeTransforms(node, obj);
        } else if(node.isMember("camera")){
            Json::Value& camData = gltf["cameras"][node["camera"].asUInt()]["perspective"];

            float const fov = glMath::toDeg(glMath::toYFOV(camData["yfov"].asFloat(), camData["aspectRatio"].asFloat()));
            Camera cam = Camera{fov, Config::aspect, camData["znear"].asFloat(), camData["zfar"].asFloat()};
            setMainCamera(cam);
            setNodeTransforms(node, cam);
        } else if (node.isMember("extensions") && node["extensions"].isMember("KHR_lights_punctual") && this->lights.size() < Config::maxLightsCount){
            Json::Value& lightData = gltf["extensions"]["KHR_lights_punctual"]["lights"][node["extensions"]["KHR_lights_punctual"]["light"].asUInt()];

            PointLight light = PointLight{parseVector3(lightData["color"]), glMath::toPower(lightData["intensity"].asFloat())};
            this->lights[node["name"].asCString()] = light;
            setNodeTransforms(node, light);
        }
    }

    for(auto link : unprocessedPortalLinks){
        portalLinks.emplace_back(objects.find(link.master)->second, objects.find(link.link)->second, 0);
    }

    setLights();
}

void SceneGraph::portalDraw() {
    //for all portals evaluating on which side of the portal an observer is
    unsigned int linksCount = portalLinks.size();
    int newSides[linksCount];
    for (int i = 0; i < linksCount; ++i) {
        newSides[i] = Vector3::side(portalLinks[i].master.transform.position, mainCamera.transform.position, portalLinks[i].master.transform.back());
    }

    //handling teleportation
    for (int i = 0; i < linksCount; ++i) {
        auto [master, link, side] = portalLinks[i];
        const int newSide = newSides[i];

        const bool collide = Vector3::distance(master.transform.position, mainCamera.transform.position) < master.mesh.boundingRadius();

        if(side == 0){
            portalLinks[i].side = newSide;
        } else if(newSide != side && collide) {
            mainCamera.transform.copy(
                    Transform(mainCamera.relativeMirror(master.worldMatrix(), link.worldMatrix()).inverse()));
            for (PortalLink newLink: portalLinks) {
                newLink.side = Vector3::side(newLink.master.transform.position, mainCamera.transform.position,
                                             newLink.master.transform.back());
            }
        }
        portalLinks[i].side = newSide;
    }

    //drawing the insides of the portal(the stencil part)
    for(const auto [master, link, side] : portalLinks){
//drawing frame into stencil
        glColorMask(false, false, false, false);
        glDepthMask(false);
        glDisable(GL_DEPTH_TEST);

        glEnable(GL_STENCIL_TEST);
        glStencilOp(GL_INCR, GL_KEEP, GL_KEEP);
        glStencilFunc(GL_NEVER, 1, 0xff);
        glStencilMask(0xff);

        master.drawObject();

        //drawing scene inside the portal
        glColorMask(true,true,true, true);
        glDepthMask(true);

        glEnable(GL_DEPTH_TEST);

        glStencilMask(0x00);
        glStencilFunc(GL_EQUAL, 1, 0xff);

        Matrix4 rm = mainCamera.relativeMirror(master.worldMatrix(), link.worldMatrix());
        Matrix4 proj = Matrix4{mainCamera.projectionMatrix};
        proj.clipProjectionMatrix(Camera::clippingPlane(master.transform, mainCamera.viewMat(), side));

        glUniformMatrix4fv(glGetUniformLocation(_shader.getId(), "projection"), 4, false, proj.entries);
        glUniformMatrix4fv(glGetUniformLocation(_shader.getId(), "view"), 4, false, rm.entries);

        Vector3 rmInversePosition = rm.inverse().position();
        glUniform3f(glGetUniformLocation(_shader.getId(), "projection"), rmInversePosition.x, rmInversePosition.y, rmInversePosition.z);
        defaultDraw(portalExceptionTags);

        //resetting stencil test to separate stencils of every portal
        updateActiveCamera(mainCamera);

        glColorMask(false, false, false, false);
        glDepthMask(false);
        glEnable(GL_STENCIL_TEST);
        glStencilMask(0xff);

        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilOp(GL_DECR, GL_KEEP, GL_KEEP);
        master.drawObject();
    }

    //drawing portals to depth buffer from original point of view
    glDisable(GL_STENCIL_TEST);
    glColorMask(false, false, false, false);
    glDepthMask(true);
    glClear(GL_DEPTH_BUFFER_BIT);

    for (PortalLink link : portalLinks) {
        link.master.drawObject();
    }

    //drawing the rest of the scene with default view and setting
    glColorMask(true, true, true,true);
    defaultDraw(portalExceptionTags);
}

void SceneGraph::defaultDraw(std::vector<enum Object3D::Tags> exceptionTags) {
    for(auto& [name, obj] : objects){
        if(exceptionTags.empty() || std::find(exceptionTags.begin(), exceptionTags.end(), obj.tag) != exceptionTags.end()){
            obj.drawObject();
        }
    }
}

void SceneGraph::setMainCamera(Camera& camera) {
    this->mainCamera = camera;
    updateActiveCamera(camera);
}

void SceneGraph::updateScene(Vector4 clearColor) {
    glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    this->updateActiveCamera(mainCamera);
}

void SceneGraph::updateActiveCamera(Camera &camera) {
    glUniformMatrix4fv(glGetUniformLocation(_shader.getId(), "projection"), 4, false, camera.projectionMatrix.entries);
    glUniformMatrix4fv(glGetUniformLocation(_shader.getId(), "view"), 4, false, camera.viewMat().entries);
    glUniform3f(glGetUniformLocation(_shader.getId(), "cameraPosition"), camera.transform.position.x, camera.transform.position.y, camera.transform.position.z);
}

void SceneGraph::updateActiveCamera(Matrix4 &projection, Matrix4 &view, Vector3 &position) {
    glUniformMatrix4fv(glGetUniformLocation(_shader.getId(), "projection"), 4, false, projection.entries);
    glUniformMatrix4fv(glGetUniformLocation(_shader.getId(), "view"), 4, false, view.entries);
    glUniform3f(glGetUniformLocation(_shader.getId(), "cameraPosition"), position.x, position.y, position.z);
}

void SceneGraph::setLights() {
    int len = Config::maxLightsCount * 3;
    float pos[len], color[len];

    int count = 0;
    for(const auto& [key, value] : lights){
        pos[count] = value.transform.position.x;
        pos[count + 1] = value.transform.position.y;
        pos[count + 2] = value.transform.position.z;

        color[count] = value.color.x;
        color[count + 1] = value.color.y;
        color[count + 2] = value.color.z;

        count+=3;
    }
    for(int i = 0; i < len - lights.size() * 3; i+=3){
        pos[i] = 0;
        pos[i + 1] = 0;
        pos[i + 2] = 0;

        color[i] = 0;
        color[i + 1] = 0;
        color[i + 2] = 0;
    }

    glUniform3fv(glGetUniformLocation(_shader.getId(), "lightPositions"), len, pos);
    glUniform3fv(glGetUniformLocation(_shader.getId(), "lightColors"), len, color);
}

template<typename T>
T* SceneGraph::dataFromAccessor(std::vector<char> &data, unsigned int byteLength, unsigned int byteOffset) {
    if (data.size() < byteOffset + byteLength) {
        std::cerr << "Error: not enough bytes in the vector to read a float." << std::endl;
    }
    T* value = new T[byteLength];
    std::copy(data.begin() + byteOffset, data.begin() + byteOffset + byteLength, value);
    return value;
}