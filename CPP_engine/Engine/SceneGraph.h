#ifndef OPENGLENGINE_SCENEGRAPH_H
#define OPENGLENGINE_SCENEGRAPH_H


#include <vector>
#include <jsoncpp/json/value.h>
#include "Camera.h"
#include "Object3D.h"
#include "PointLight.h"
#include "../Math/Vector4.h"
#include "Animation/Animator.h"

class SceneGraph {
private:
    const char *mainCameraName;
    Shader _shader;

    struct unprocessedPortalLink{
        const char* master;
        const char* link;
    };

    struct cmp_str
    {
        bool operator()(char const *a, char const *b) const
        {
            return std::strcmp(a, b) < 0;
        }
    };

    struct PortalLink{
        PortalLink(Object3D& master, Object3D& link, int side) : master(master), link(link), side(side){};

        Object3D& master;
        Object3D& link;
        int side = 0;
    };

    std::vector<enum Object3D::Tags>portalExceptionTags = {Object3D::Tags::portal};
    std::vector<PortalLink> portalLinks;
    std::vector<Animator> animations;
    std::map<const char*, Object3D, cmp_str> objects;
    std::map<const char*, PointLight, cmp_str> lights;
    std::map<const char*, Mesh, cmp_str> meshes;
    std::map<const char*, PBRMetallicRoughness, cmp_str> materials;
    std::map<const char*, Camera, cmp_str> cameras;
    Camera& mainCamera();

    template<typename T>
    std::vector<T> dataFromAccessor(std::vector<T> value, std::ifstream &inFile, unsigned int byteLength, unsigned int byteOffset);
    void setMainCamera(const char* name);
    void updateActiveCamera(Camera& camera);
    void updateActiveCamera(Matrix4 &projection, Matrix4 view, Vector3 &position);
    void setLights();
public:
    explicit SceneGraph(Shader &shader);
    SceneGraph(Json::Value gltf, Shader &shader);
    SceneGraph() = default;

    void animate(float t);
    void updateScene(Vector4 clearColor = Vector4{Config::clearColor});
    void defaultDraw(std::vector<enum Object3D::Tags> exceptionTags);
    void portalDraw();
};


#endif //OPENGLENGINE_SCENEGRAPH_H
