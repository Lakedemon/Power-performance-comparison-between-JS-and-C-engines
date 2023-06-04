#include "Animator.h"

Animator::Animator(std::vector<Channel> channels) : channels(std::move(channels)){}

void Animator::animate(float t) {
    for(auto& channel : channels){
        channel.updateNode(t);
    }
}
