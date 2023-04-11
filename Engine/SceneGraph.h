#ifndef OPENGLENGINE_SCENEGRAPH_H
#define OPENGLENGINE_SCENEGRAPH_H


#include <vector>
#include <jsoncpp/json/value.h>
#include "Camera.h"
#include "Object3D.h"
#include "PointLight.h"
#include "../Math/Vector4.h"
#include "../GL_Helpers/AssetLoader.h"


class SceneGraph {
private:
    Camera mainCamera;
    Shader _shader;

    struct unprocessedPortalLink{
        const char* master;
        const char* link;
    };

    struct PortalLink{
        Object3D& master;
        Object3D& link;
        int side = 0;
    };

    std::vector<enum Object3D::Tags>portalExceptionTags = {Object3D::Tags::portal};
    std::vector<PortalLink> portalLinks;
    std::map<const char*, Object3D> objects;
    std::map<const char*, PointLight> lights;
    std::map<const char*, Mesh> meshes;
    std::map<const char*, PBRMetallicRoughness> materials;

    template<typename T>
    static T* dataFromAccessor(std::vector<char>& data, unsigned int byteLength, unsigned int byteOffset);

    void setMainCamera(Camera& camera);
    void updateActiveCamera(Camera& camera);
    void updateActiveCamera(Matrix4 &projection, Matrix4 &view, Vector3 &position);

    void setLights();
public:
    explicit SceneGraph(Shader &shader);
    SceneGraph(const AssetLoader::gltf& loadedFile, Shader &shader);
    SceneGraph() = default;
    void portalDraw();

    void updateScene(Vector4 clearColor = Vector4{Config::clearColor});
    void defaultDraw(std::vector<enum Object3D::Tags> exceptionTags);
};


#endif //OPENGLENGINE_SCENEGRAPH_H
