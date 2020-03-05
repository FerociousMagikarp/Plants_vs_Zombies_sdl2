#include "ObjectCharacter.h"

ObjectCharacter::ObjectCharacter(SDL_Renderer *renderer) : Object(renderer)
{
    x = 0;
    y = 0;
    scale = 0.4f;
    anchor_x = 0.5f;
    anchor_y = 1.0f;
    has_colision = true;

    attack_speed = 1.0f;
    hp = 100;
    attack = 10;
}

ObjectCharacter::~ObjectCharacter()
{

}

void ObjectCharacter::Update(int offset)
{
    Object::Update(offset);
    SDL_Rect rect;
    SDL_Rect rect2;
    rect.x = (int)(current_anim.w * frame_i);
    rect.y = 0;
    rect.w = current_anim.w;
    rect.h = current_anim.h;
    rect2.w = current_anim.w * scale;
    rect2.h = current_anim.h * scale;
    rect2.x = (int)(x - rect2.w * anchor_x) - offset;
    rect2.y = (int)(y - rect2.h * anchor_y);
    SDL_RenderCopy(renderer, current_anim.texture, &rect, &rect2);
}

bool ObjectCharacter::Collision(const ObjectCharacter* object)
{
    if (!(HasColision() && object->HasColision()))
        return false;
    return (GetX() + GetW() > object->GetX() + object->GetW() * 3 / 10 && GetX() < object->GetX() + object->GetW() * 7 / 10);
}

