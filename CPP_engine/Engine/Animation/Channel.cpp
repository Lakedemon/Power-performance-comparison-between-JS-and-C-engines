#include "Channel.h"

Channel::Channel(EmptyObject& node, Sampler sampler, std::string path) : _node(node), _sampler(std::move(sampler)), _path(std::move(path)){}

void Channel::updateNode(float t){
    if (this->_path == "translation"){
        _node.setPosition(this->_sampler.getOutput(t));
    } else if (this->_path == "rotation") {
        _node.setRotation(this->_sampler.getOutput(t));
    } else if (this->_path == "scale"){
        _node.setScale(this->_sampler.getOutput(t));
    }
}