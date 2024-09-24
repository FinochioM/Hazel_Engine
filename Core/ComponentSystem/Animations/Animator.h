#ifndef HAZELENGINE_ANIMATOR_H
#define HAZELENGINE_ANIMATOR_H

#include "Component.h"
#include "SpriteRenderer.h"
#include "AnimationLoader.h"
#include "AnimationTransition.h"
#include <vector>

class Animator : public Component {
public:
    Animator(Entity* owner, SpriteRenderer* spriteRenderer, AnimationLoader* loader);

    void Render() override {}
    void Update(float deltaTime) override;
    void PlayAnimation(const std::string& cycleName, bool loop = true, int startFrame = 0, int endFrame = -1);
    void AddTransition(const AnimationTransition& transition);

    void NextFrame();
    void PreviousFrame();
    void SetFrame(int frameIndex);
    void SetManualControl(bool manual);

    void RenderFirstFrameIfNoAnimation();

    std::string GetTypeName() const override { return "Animator"; }

private:
    void UpdateAnimation(float deltaTime);
    void UpdateTransition(float deltaTime);
    void CheckTransitions();

    SpriteRenderer* spriteRenderer;
    AnimationLoader* animationLoader;

    std::string currentCycle;
    std::string nextCycle;
    float currentTime;
    int currentFrame;
    int maxFrame;
    bool isLooping;

    bool inTransition;
    float transitionTime;
    float transitionDuration;

    bool manualControl;

    std::vector<AnimationTransition> transitions;
};

#endif