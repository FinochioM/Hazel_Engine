#ifndef HAZELENGINE_GLOBAL_H
#define HAZELENGINE_GLOBAL_H

class Global{
public:
    static float deltaTime;

    static void UpdateDeltaTime(float newDeltaTime){
        deltaTime = newDeltaTime;
    }
};

#endif