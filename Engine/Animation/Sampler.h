#ifndef OPENGLENGINE_SAMPLER_H
#define OPENGLENGINE_SAMPLER_H


#include <vector>
#include <string>
#include <utility>
#include <cmath>
#include <iostream>

#include "../../Math/Vector3.h"
#include "../../Math/Vector4.h"
#include "../../Math/glMath.h"



class Sampler {
public:
    Sampler(std::vector<float> input, std::vector<float> output, std::string mode = "LINEAR");
    Vector3 getOutput(float globalT);
private:
    std::vector<float> _input;
    std::vector<float> _output;
    std::string _mode;
    float duration;
    float frameLength;

    static Vector3 getVector3(std::vector<float> data, int index);
    static Vector4 getVector4(std::vector<float> data, int index);

    static Vector3 lerp(Vector3 start, Vector3 end, float t);
    static Vector4 lerp(Vector4 start, Vector4 end, float t);
    static Vector3 slerp(Vector4 start, Vector4 end, float t);
};


#endif //OPENGLENGINE_SAMPLER_H