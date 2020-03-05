#include "Object.h"
#include <math.h>

Object::Object(SDL_Renderer *renderer)
{
    this->renderer = renderer;
    current_anim.n = 0;

    anim_fps = 25;
    last_time = 0;
    frame_i = 0;
}

Object::~Object()
{

}

void Object::LoadAnim(const char* name, int n)
{
    AnimInfo info = ResourceManager::GetInstance()->LoadAnim(renderer, name, n);
    anims.push_back(info);
}

void Object::PlayAnim(size_t i)
{
    if (i < anims.size())
    {
        frame_i = 0;
        current_anim = anims[i];
    }
}

void Object::Update(int offset)
{
    if (current_anim.n > 1)
    {
        Uint64 end_time = SDL_GetPerformanceCounter();
        if (last_time == 0)
        {
            last_time = end_time;
            return;
        }
        float ms = (end_time - last_time) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
        float rest_time = floor(1000.0f / anim_fps - ms);

        if (rest_time <= 0)
        {
            if (++frame_i >= current_anim.n)
                frame_i -= current_anim.n;
            last_time = end_time;
        }
    }
}
