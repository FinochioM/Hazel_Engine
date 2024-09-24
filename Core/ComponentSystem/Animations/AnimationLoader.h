#ifndef HAZELENGINE_ANIMATIONLOADER_H
#define HAZELENGINE_ANIMATIONLOADER_H

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <yyjson.h>

#include "glm/glm.hpp"

struct FrameData{
    int x, y;
    int width, height;
};

struct AnimationCycle{
    std::vector<FrameData> frames;
    bool isLooping;
    float frameDuration;
};

class AnimationLoader {
public:
    bool LoadAnimation(const std::string& csaFile);

    std::string GetTexturePath() const {return texturePath;}
    AnimationCycle GetAnimationCycle(const std::string& name) const;

private:
    std::string texturePath;
    int regionWidth;
    int regionHeight;
    std::map<std::string, AnimationCycle> animationCycles;
    std::vector<FrameData> frameDataList;

    bool LoadJson(const std::string& jsonFile);
};
#endif