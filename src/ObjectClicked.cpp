#include "ObjectClicked.h"
#include "ResourceManager.h"

ObjectClicked::ObjectClicked(SDL_Renderer *renderer, const char* name, int x, int y) : Object(renderer)
{
    texture = ResourceManager::GetInstance()->LoadTexture(renderer, name);
    rect.x = x;
    rect.y = y;
    rect.w = texture.w;
    rect.h = texture.h;
    is_shown = true;
}

ObjectClicked::~ObjectClicked()
{
    //dtor
}

void ObjectClicked::Update(int offset)
{
    if (is_shown)
    {
        SDL_RenderCopy(renderer, texture.texture, nullptr, &rect);
    }
}

bool ObjectClicked::IsClicked(int x, int y)
{
    if (is_shown)
        return (x > rect.x && x < rect.x + rect.w && y > rect.y && y < rect.y + rect.h);
    return false;
}
