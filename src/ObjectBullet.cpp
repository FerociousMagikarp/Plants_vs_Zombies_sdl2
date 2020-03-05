#include "ObjectBullet.h"

ObjectBullet::ObjectBullet(SDL_Renderer *renderer) : ObjectCharacter(renderer)
{
    LoadAnim("pea", 1);
    PlayAnim(0);
    scale = 1.0f;
    anchor_x = anchor_y = 0.5f;
    last_move_time = 0;
    is_shown = true;
    speed = 300;
    delta_x = 0.0f;
    init_x = 0;
    attack = 10;
}

ObjectBullet::~ObjectBullet()
{

}

void ObjectBullet::Update(int offset)
{
    if (is_shown)
    {
        ObjectCharacter::Update(offset);
        Uint64 current_time = SDL_GetPerformanceCounter();
        if (last_move_time == 0)
        {
            last_move_time = current_time;
            return;
        }
        float dt = (current_time - last_move_time) / (float)SDL_GetPerformanceFrequency();
        delta_x += speed * dt;
        x = init_x + (int)delta_x;
        last_move_time = current_time;
        if (x > 820)
            is_shown = false;
    }
}

void ObjectBullet::InitPos(int x, int y, int w, int h)
{
    init_x = x + w;
    this->x = init_x;
    this->y = y + h / 4;
    delta_x = 0.0f;
}
