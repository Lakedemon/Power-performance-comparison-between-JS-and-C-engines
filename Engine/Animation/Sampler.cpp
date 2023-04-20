#include "Sampler.h"

Sampler::Sampler(std::vector<float> input, std::vector<float> output, std::string mode) : _input(std::move(input)), _output(std::move(output)), _mode(std::move(mode)) {
    duration = _input.back() - _input.front();
    frameLength = duration / _input.size();
    this->_input[0] = 0;
}

Vector3 Sampler::getOutput(float globalT) {
    float localT = std::fmod(globalT, this->duration);

    int index = (int)(localT / this->frameLength);
    index = index >= this->_input.size() - 1 ? this->_input.size() - 1 : index;

    while (!(this->_input.at(index) <= localT && this->_input.at(index + 1) >= localT)){
        index += this->_input.at(index) <= localT ? 1 : -1;
        if(index >= this->_input.size() - 1){
            index = 0;
        }
    }
    float t = (localT - this->_input.at(index)) / (this->_input.at(index + 1) - this->_input.at(index));

    if(this->_mode == "LINEAR"){
        return lerp(getVector3(_output, index), getVector3(_output, index + 1), t);
    } else if (this->_mode == "STEP"){
        return getVector3(_output, index);
    } else if (this->_mode == "rotation"){
        return slerp(getVector4(_output, index), getVector4(_output, index), t);
    } else {
        std::cout << "ERROR:SAMPLER:INTERPOLATION_MODE_NOT_SUPPORTED" << std::endl;
        return Vector3::zero;
    }
}

Vector3 Sampler::lerp(Vector3 start, Vector3 end, float t) {
    return start * (1 - t) + end * t;
}

Vector4 Sampler::lerp(Vector4 start, Vector4 end, float t) {
    return start * (1 - t) + end * t;
}

Vector3 Sampler::slerp(Vector4 start, Vector4 end, float t) {
    float dot = Vector4::dot(start, end);

    if(dot >= 0.9995){
        return Vector3::QuaternionToEuler(Sampler::lerp(start, end, t).normalized());
    }

    int s = glMath::sign(dot);
    float a = std::acos(std::abs(dot));

    if(a <= glMath::EPSILON){
        return Vector3::QuaternionToEuler(Sampler::lerp(start, end, t).normalized());
    }

    float r_sa = 1 / std::sin(a);
    Vector4 vt = start * (std::sin(a * (1 - t)) * r_sa) + end * (s * std::sin(a * t) * r_sa);
    return Vector3::QuaternionToEuler(vt);
}

Vector3 Sampler::getVector3(std::vector<float> data, int index) {
    index *= 3;
    return {data.at(index), data.at(index + 1), data.at(index + 2)};
}

Vector4 Sampler::getVector4(std::vector<float> data, int index) {
    index *= 4;
    return {data.at(index), data.at(index + 1), data.at(index + 2), data.at(index + 3)};
}
