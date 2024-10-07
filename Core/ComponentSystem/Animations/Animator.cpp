#include "Animator.h"


Animator::Animator(Entity* owner, SpriteRenderer* spriteRenderer, AnimationLoader* loader)
        : Component(owner), spriteRenderer(spriteRenderer), animationLoader(loader),
            currentTime(0.0f), currentFrame(0), isLooping(true),
            inTransition(false), transitionTime(0.0f), transitionDuration(0.0f),
            manualControl(false){}

void Animator::Update(float deltaTime){
    if (inTransition) {
        UpdateTransition(deltaTime);
    } else {
        if (!manualControl) {
            UpdateAnimation(deltaTime);
        }

        if (currentCycle.empty()) {
            RenderFirstFrameIfNoAnimation();
        }

        CheckTransitions();
    }
}

void Animator::UpdateAnimation(float deltaTime){
    if (currentCycle.empty()) return;

    currentTime += deltaTime;

    AnimationCycle cycle = animationLoader->GetAnimationCycle(currentCycle);

    if (cycle.frameDuration > 0.0f && currentTime >= cycle.frameDuration) {
        currentTime = 0.0f;
        currentFrame = (currentFrame + 1) % cycle.frames.size();

        if (!isLooping && currentFrame == 0) {
            currentFrame = cycle.frames.size() - 1;
        }

        auto frame = cycle.frames[currentFrame];
        // Aquí se llama a SetFrame() con los valores específicos del frame actual
        spriteRenderer->SetFrame(frame.x, frame.y, frame.width, frame.height);
    }
}

void Animator::UpdateTransition(float deltaTime) {
    transitionTime += deltaTime;
    float t = transitionTime / transitionDuration;

    if (t >= 1.0f){
        inTransition = false;
        currentCycle = nextCycle;
        currentFrame = 0;
        currentTime = 0.0f;
        spriteRenderer->SetOpacity(1.0f);
        UpdateAnimation(0.0f);
        return;
    }

    AnimationCycle fromCycle = animationLoader->GetAnimationCycle(currentCycle);
    AnimationCycle toCycle = animationLoader->GetAnimationCycle(nextCycle);
    AnimationCycle cycle = animationLoader->GetAnimationCycle(currentCycle);

    if (currentFrame >= cycle.frameDuration){
        currentTime = 0.0f;
        currentFrame = (currentFrame - 1) % maxFrame;

        if (!isLooping && currentFrame == 0){
            currentFrame = maxFrame - 1;
        }

        auto frame = cycle.frames[currentFrame];
        spriteRenderer->SetFrame(frame.x, frame.y, frame.width, frame.height);
    }

    int fromFrameIndex = currentFrame % fromCycle.frames.size();
    int toFrameIndex = currentFrame % toCycle.frames.size();

    FrameData fromFrame = fromCycle.frames[fromFrameIndex];
    FrameData toFrame = toCycle.frames[toFrameIndex];

    spriteRenderer->SetFrame(fromFrame.x, fromFrame.y, fromFrame.width, fromFrame.height);
    spriteRenderer->SetOpacity(1.0f - t);
    spriteRenderer->Render();

    spriteRenderer->SetFrame(toFrame.x, toFrame.y, toFrame.width, toFrame.height);
    spriteRenderer->SetOpacity(t);
    spriteRenderer->Render();

    spriteRenderer->SetOpacity(1.0f);
}

void Animator::CheckTransitions() {
    for (auto& transition : transitions){
        if (transition.from == currentCycle || transition.from == "Any"){
            if (transition.condition && transition.condition()){
                inTransition = true;
                transitionTime = 0.0f;
                transitionDuration = transition.transitionDuration;
                nextCycle = transition.to;
                break;
            }
        }
    }
}

void Animator::PlayAnimation(const std::string &cycleName, bool loop, int startFrame, int endFrame) {
    currentCycle = cycleName;
    currentTime = 0.0f;
    currentFrame = startFrame;
    isLooping = loop;

    AnimationCycle cycle = animationLoader->GetAnimationCycle(currentCycle);
    if (endFrame > 0 && endFrame < cycle.frames.size()){
        maxFrame = endFrame;
    } else {
        maxFrame = cycle.frames.size();
    }


    if (manualControl || startFrame >= 0) {
        if (!cycle.frames.empty() && startFrame >= 0 && startFrame < cycle.frames.size()){
            auto frame = cycle.frames[currentFrame];
            spriteRenderer->SetFrame(frame.x, frame.y, frame.width, frame.height);
            spriteRenderer->Render();
        }
    }
}


void Animator::AddTransition(const AnimationTransition &transition) {
    transitions.push_back(transition);
}

void Animator::NextFrame() {
    AnimationCycle cycle = animationLoader->GetAnimationCycle(currentCycle);
    if (!cycle.frames.empty()){
        currentFrame = (currentFrame + 1) % cycle.frames.size();
        auto frame = cycle.frames[currentFrame];
        spriteRenderer->SetFrame(frame.x, frame.y, frame.width, frame.height);
        spriteRenderer->Render();
    }
}

void Animator::PreviousFrame() {
    AnimationCycle cycle = animationLoader->GetAnimationCycle(currentCycle);
    if (!cycle.frames.empty()){
        currentFrame = (currentFrame - 1 + cycle.frames.size()) % cycle.frames.size();
        auto frame = cycle.frames[currentFrame];
        spriteRenderer->SetFrame(frame.x, frame.y, frame.width, frame.height);
    }
}

void Animator::SetFrame(int frameIndex) {
    AnimationCycle cycle = animationLoader->GetAnimationCycle(currentCycle);
    if (frameIndex >= 0 && frameIndex < cycle.frames.size()){
        currentFrame = frameIndex;
        auto frame = cycle.frames[currentFrame];
        spriteRenderer->SetFrame(frame.x, frame.y, frame.width, frame.height);
        spriteRenderer->Render();
    }
}

void Animator::SetManualControl(bool manual) {
    manualControl = manual;
    if (manualControl) {
        currentTime = 0.0f;
    }
}

void Animator::RenderFirstFrameIfNoAnimation() {
    if (currentCycle.empty()){
        AnimationCycle cycle = animationLoader->GetAnimationCycle("idle");
        if(!cycle.frames.empty()){
            FrameData firstFrame = cycle.frames[0];
            spriteRenderer->SetFrame(firstFrame.x, firstFrame.y, firstFrame.width, firstFrame.height);
            spriteRenderer->Render();
        }
    }
}