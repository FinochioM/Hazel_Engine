#ifndef HAZELENGINE_ANIMATIONTRANSITION_H
#define HAZELENGINE_ANIMATIONTRANSITION_H

#include <string>
#include <functional>

struct AnimationTransition{
    std::string from;
    std::string to;
    std::function<bool()> condition;
    float transitionDuration;
};

#endif