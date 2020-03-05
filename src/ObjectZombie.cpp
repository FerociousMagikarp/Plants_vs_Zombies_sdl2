#include "ObjectZombie.h"

ObjectZombie::ObjectZombie(SDL_Renderer *renderer) : ObjectCharacter(renderer)
{
    LoadAnim("zombie/walk", 31);
    LoadAnim("zombie/idle", 31);
    LoadAnim("zombie/dead", 19);
    LoadAnim("zombie/eat", 22);
    PlayAnim(0);

    speed = 10;
    hp = 100;
    attack = 25;

    last_time = 0;
    delta_x = 0.0f;
    init_x = 820;
    x = init_x;

    attack_speed = 1.14f;

    m_last_atk_time = 0;

    is_moving = true;
    is_shown = true;
    is_dying = false;
    is_eating = false;
}

ObjectZombie::~ObjectZombie()
{

}

void ObjectZombie::Update(int offset)
{
    if (is_shown)
    {
        ObjectCharacter::Update(offset);
    }

    if (is_moving)
    {
        Uint64 end_time = SDL_GetPerformanceCounter();
        if (last_time == 0)
        {
            last_time = end_time;
            return;
        }
        float dt = (end_time - last_time) / (float)SDL_GetPerformanceFrequency();
        delta_x += speed * dt;
        x = (int)(init_x - delta_x);
        last_time = end_time;
    }
    if (is_dying)
    {
        if (frame_i == 10)
        {
            has_colision = false;
        }
        else if (frame_i == 18)
        {
            is_shown = false;
        }
    }
}

void ObjectZombie::Dying()
{
    if (is_dying == false)
    {
        is_dying = true;
        is_moving = false;
        PlayAnim(2);
        anim_fps = 15;
    }
}

bool ObjectZombie::Eating()
{
    if (is_eating == false)
    {
        is_moving = false;
        last_time = 0;  // 防止僵尸跳跃
        PlayAnim(3);
        is_eating = true;
        m_last_atk_time = SDL_GetPerformanceCounter();
        return false;
    }
    Uint64 current_time = SDL_GetPerformanceCounter();
    float s = (current_time - m_last_atk_time) / (float)SDL_GetPerformanceFrequency();
    if (1 / attack_speed < s)
    {
        m_last_atk_time = current_time;
        return true;
    }
    return false;
}

void ObjectZombie::Walking()
{
    if (is_eating == true && frame_i == 21)
    {
        is_moving = true;
        PlayAnim(0);
        is_eating = false;
    }
}
