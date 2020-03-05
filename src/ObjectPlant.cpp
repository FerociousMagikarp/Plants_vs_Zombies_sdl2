#include "ObjectPlant.h"
#include "ObjectBullet.h"

ObjectPlant::ObjectPlant(SDL_Renderer *renderer) : ObjectCharacter(renderer)
{
    LoadAnim("peashooter", 31);
    PlayAnim(0);

    attack_speed = 0.7f;
    m_last_atk = 0;
}

ObjectPlant::~ObjectPlant()
{

}

void ObjectPlant::Update(int offset)
{
    ObjectCharacter::Update(offset);
}

ObjectBullet* ObjectPlant::EmitBullet()
{
    Uint64 current_atk_time = SDL_GetPerformanceCounter();
    float s = (current_atk_time - m_last_atk) / (float)SDL_GetPerformanceFrequency();
    if (s > 1 / attack_speed || m_last_atk == 0)
    {
        ObjectBullet *bullet = new ObjectBullet(renderer);
        bullet->InitPos(GetX(), GetY(), GetW(), GetH());
        m_last_atk = current_atk_time;
        return bullet;
    }
    return nullptr;
}
