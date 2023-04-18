#include "SceneGraph.h"

SceneGraph::SceneGraph(Shader &shader) : _shader(shader) {
    glUseProgram(shader.getId());
}

SceneGraph::SceneGraph(Json::Value gltf, Shader &shader) : SceneGraph(shader){
    std::vector<std::ifstream> buffers;
    for (const auto& buffer : gltf["buffers"]) {
        buffers.emplace_back(Config::gltfPath + buffer["uri"].asCString(), std::ios::binary);
        if (!buffers.back().is_open()) {
            std::cerr << "ERROR::BUFFERS::COULD_NOT_OPEN_FILE" << std::endl;
        }
    }

    auto getBufferView = [&gltf](unsigned int accessorID) -> std::tuple<unsigned int, unsigned int, unsigned int>{
        Json::Value bufferView = gltf["bufferViews"][gltf["accessors"][accessorID]["bufferView"].asUInt()];
        return std::make_tuple(bufferView["buffer"].asUInt(), bufferView["byteLength"].asUInt(), bufferView["byteOffset"].asUInt());
    };

    auto parseVector3 = [&](Json::Value node){
        return Vector3{node[0].asFloat(), node[1].asFloat(), node[2].asFloat()};
    };

    auto setNodeTransforms = [&](Json::Value node, EmptyObject& obj){
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

    auto getNodeFromIndex = [&gltf, this](unsigned int index) -> EmptyObject&{
        Json::Value node = gltf["nodes"][index];
        if(node.isMember("mesh")) {
            return this->objects.at(node["name"].asCString());
        } else if(node.isMember("camera")){
            return this->mainCamera;
        } else if(node.isMember("extensions")){
            return this->lights.at(node["name"].asCString());
        }
        std::cout << "ERROR::GLTF::NODE_NOT_FOUND";
        return this->mainCamera;
    };

    for(Json::Value& material : gltf["materials"]){
        Json::Value& mData = material["pbrMetallicRoughness"];
        Json::Value& bcf = mData["baseColorFactor"];
        Vector3 const color = Vector3(bcf[0].asFloat(), bcf[1].asFloat(), bcf[2].asFloat());
        this->materials[material["name"].asCString()] = PBRMetallicRoughness{color, mData["metallicFactor"].asFloat(), mData["roughnessFactor"].asFloat()};
    }
    this->materials["Default"] = PBRMetallicRoughness{};

    for(Json::Value& mesh : gltf["meshes"]) {
        Json::Value& primitive = mesh["primitives"][0];

        auto posArgs = getBufferView(primitive["attributes"]["POSITION"].asUInt());
        auto texArgs = getBufferView(primitive["attributes"]["TEXCOORD_0"].asUInt());
        auto normArgs = getBufferView(primitive["attributes"]["NORMAL"].asUInt());
        auto indexArgs = getBufferView(primitive["indices"].asUInt());

        std::vector<float> pos, tex, norm;
        std::vector<uint16_t> index;

        this->meshes[mesh["name"].asCString()] = Mesh{
                dataFromAccessor<float>(pos, buffers.at(std::get<0>(posArgs)), std::get<1>(posArgs),std::get<2>(posArgs)),
                dataFromAccessor<float>(norm, buffers.at(std::get<0>(normArgs)), std::get<1>(normArgs), std::get<2>(normArgs)),
                dataFromAccessor<float>(tex, buffers.at(std::get<0>(texArgs)), std::get<1>(texArgs), std::get<2>(texArgs)),
                dataFromAccessor<uint16_t>(index, buffers.at(std::get<0>(indexArgs)), std::get<1>(indexArgs), std::get<2>(indexArgs)),
        };
    }

    std::vector<unprocessedPortalLink> unprocessedPortalLinks;
    for(Json::Value& node : gltf["nodes"]){
        const char * name = node["name"].asCString();
        if(node.isMember("mesh")){
            Object3D::Tags tag = Object3D::Tags::def;
            if (node.isMember("extras") && node["extras"].isMember("linked_portal")){
                unprocessedPortalLinks.push_back({node["name"].asCString(), node["extras"]["linked_portal"]["name"].asCString()});
                tag = Object3D::Tags::portal;
            }

            const char* materialName = gltf["meshes"][node["mesh"].asUInt()]["primitives"][0].isMember("material") ?
                    gltf["materials"][gltf["meshes"][node["mesh"].asUInt()]["primitives"][0]["material"].asUInt()]["name"].asCString() :
                    "Default";

            this->objects.emplace(name, Object3D{
                meshes[gltf["meshes"][node["mesh"].asUInt()]["name"].asCString()],
                shader,
                materials.at(materialName),
                tag
            });
            setNodeTransforms(node, this->objects.at(name));
        } else if(node.isMember("camera")){
            Json::Value& camData = gltf["cameras"][node["camera"].asUInt()]["perspective"];

            float const fov = glMath::toDeg(glMath::toYFOV(camData["yfov"].asFloat(), camData["aspectRatio"].asFloat()));
            Camera cam = Camera{fov, Config::aspect, camData["znear"].asFloat(), camData["zfar"].asFloat()};
            setNodeTransforms(node, cam);
            setMainCamera(cam);
        } else if (node.isMember("extensions") && node["extensions"].isMember("KHR_lights_punctual") && this->lights.size() < Config::maxLightsCount){
            Json::Value& lightData = gltf["extensions"]["KHR_lights_punctual"]["lights"][node["extensions"]["KHR_lights_punctual"]["light"].asUInt()];
            auto a = PointLight{parseVector3(lightData["color"]), glMath::toPower(lightData["intensity"].asFloat())};

            this->lights.emplace(name, PointLight{parseVector3(lightData["color"]), glMath::toPower(lightData["intensity"].asFloat())});
            setNodeTransforms(node, this->lights.at(name));
        }
    }

    if(gltf.isMember("animations")) {
        for(Json::Value& animation : gltf["animations"]){
            std::vector<Channel> channels;

            for(const auto& channel : animation["channels"]){
                Json::Value samplerData = animation["samplers"][channel["sampler"].asUInt()];
                std::string targetPath = channel["target"]["path"].asString();
                std::string interpolation = targetPath == "rotation" ? targetPath : samplerData["interpolation"].asString();

                auto inputArgs = getBufferView(samplerData["input"].asUInt());
                auto outputArgs = getBufferView(samplerData["output"].asUInt());

                std::vector<float> input, output;
                Sampler sampler = Sampler(
                    dataFromAccessor<float>(input, buffers.at(std::get<0>(inputArgs)), std::get<1>(inputArgs),std::get<2>(inputArgs)),
                    dataFromAccessor<float>(output, buffers.at(std::get<0>(outputArgs)), std::get<1>(outputArgs),std::get<2>(outputArgs)),
                    interpolation
                );
                channels.emplace_back(getNodeFromIndex(channel["target"]["node"].asUInt()), sampler, targetPath);
            }
            this->animations.emplace_back(channels);
        }
    }

    for(auto& buffer : buffers){
        buffer.close();
    }

    for(const auto& link : unprocessedPortalLinks){
        portalLinks.emplace_back(objects.at(link.master), objects.at(link.link), 0);
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

        Vector3 v = {1, 0, 1};
        const bool collide = Vector3::distance(master.transform.position, mainCamera.transform.position) < master.mesh.boundingRadius(v);

        if(side == 0){
            portalLinks[i].side = newSide;
        } else if(newSide != side && collide) {
            mainCamera.transform.copy(Transform(mainCamera.relativeMirror(master.worldMatrix(), link.worldMatrix()).inverse()));
            for (PortalLink& newLink: portalLinks) {
                newLink.side = Vector3::side(newLink.master.transform.position, mainCamera.transform.position,newLink.master.transform.back());
            }
        }
        portalLinks[i].side = newSide;
    }

    //drawing the insides of the portal(the stencil part)
    for(const auto& [master, link, side] : portalLinks){
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

        glUniformMatrix4fv(glGetUniformLocation(_shader.getId(), "u_projection"), 1, GL_FALSE, proj.entries);
        glUniformMatrix4fv(glGetUniformLocation(_shader.getId(), "u_view"), 1, GL_FALSE, rm.entries);
        Vector3 rmInversePosition = rm.inverse().position();
        glUniform3f(glGetUniformLocation(_shader.getId(), "u_camPos"), rmInversePosition.x, rmInversePosition.y, rmInversePosition.z);
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
        if(exceptionTags.empty() || std::find(exceptionTags.begin(), exceptionTags.end(), obj.tag) == exceptionTags.end()){
            obj.drawObject();
        }
    }
}

void SceneGraph::setMainCamera(Camera& camera) {
    this->mainCamera = camera;
    updateActiveCamera(camera);
}

void SceneGraph::animate(float t) {
    for(auto& animation : this->animations){
        animation.animate(t);
    }
}

void SceneGraph::updateScene(Vector4 clearColor) {
    glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    this->updateActiveCamera(mainCamera);
}

void SceneGraph::updateActiveCamera(Camera &camera) {
    updateActiveCamera(camera.projectionMatrix, camera.viewMat(), camera.transform.position);
}

void SceneGraph::updateActiveCamera(Matrix4 &projection, Matrix4 view, Vector3 &position) {
    glUniformMatrix4fv(glGetUniformLocation(_shader.getId(), "u_projection"), 1, GL_FALSE, projection.entries);
    glUniformMatrix4fv(glGetUniformLocation(_shader.getId(), "u_view"), 1, GL_FALSE, view.entries);
    glUniform3f(glGetUniformLocation(_shader.getId(), "u_cameraPosition"), position.x, position.y, position.z);
}

void SceneGraph::setLights() {
    int len = Config::maxLightsCount * 3;
    float pos[len], color[len];

    int count = 0;
    for(const auto& [key, value] : lights){
        pos[count] = value.transform.position.x;
        pos[count + 1] = value.transform.position.y;
        pos[count + 2] = value.transform.position.z;

        Vector3 scaledColor = value.scaledColor();
        color[count] = scaledColor.x;
        color[count + 1] = scaledColor.y;
        color[count + 2] = scaledColor.z;

        count+=3;
    }
    for(int i = lights.size() * 3; i < len; i+=3){
        pos[i] = 0;
        pos[i + 1] = 0;
        pos[i + 2] = 0;

        color[i] = 0;
        color[i + 1] = 0;
        color[i + 2] = 0;
    }

    glUniform3fv(glGetUniformLocation(_shader.getId(), "u_lightPositions"), len, pos);
    glUniform3fv(glGetUniformLocation(_shader.getId(), "u_lightColors"), len, color);
}

template<typename T>
std::vector<T> SceneGraph::dataFromAccessor(std::vector<T> value, std::ifstream &inFile, unsigned int byteLength, unsigned int byteOffset) {
    unsigned int num = byteLength / sizeof(T);

    value.resize(num);
    inFile.seekg(byteOffset);

    if (!inFile.read((char*)(value.data()), byteLength)) {
        std::cerr << "ERROR::BUFFERS::COULD_NOT_READ_FROM_FILE" << std::endl;
    }
    return value;
}