#ifndef OPENGLENGINE_ANIMATOR_H
#define OPENGLENGINE_ANIMATOR_H


#include <vector>
#include <utility>
#include "Channel.h"

class Animator {
private:
    std::vector<Channel> channels;
public:
    explicit Animator(std::vector<Channel> channels);
    void animate(float t);
};

#endif //OPENGLENGINE_ANIMATOR_H
