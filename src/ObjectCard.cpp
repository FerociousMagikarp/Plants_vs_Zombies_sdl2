#include "ObjectCard.h"

ObjectCard::ObjectCard(SDL_Renderer *renderer, const char* name, int n)
: ObjectClicked(renderer, name, 0, 6)
{
    rect.x = 128 + (rect.w + 1) * n;

    cd = 4.0f;
    m_last_cd_time = 0;
    enable = true;
    in_cd = false;
    has_enough_sun = false;
    sun = 100;
}

ObjectCard::~ObjectCard()
{

}

void ObjectCard::Update(int offset)
{
    ObjectClicked::Update(offset);
    if (in_cd == false && has_enough_sun == true)
    {
        enable = true;
    }
    if (enable == false)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_RenderFillRect(renderer, &rect);
    }
    if (in_cd)
    {
        Uint64 current_time = SDL_GetPerformanceCounter();
        float s = (current_time - m_last_cd_time) / (float)SDL_GetPerformanceFrequency();
        if (s >= cd)
        {
            in_cd = false;
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_Rect mask_rect = rect;
            mask_rect.h = (int)((cd - s) * rect.h / cd);
            SDL_RenderFillRect(renderer, &mask_rect);
        }
    }
}

bool ObjectCard::IsClicked(int x, int y)
{
    if (enable)
    {
        return ObjectClicked::IsClicked(x, y);
    }
    return false;
}

void ObjectCard::StartCD()
{
    if (in_cd == false)
    {
        m_last_cd_time = SDL_GetPerformanceCounter();
        in_cd = true;
        enable = false;
    }
}

bool ObjectCard::HasEnoughSun(int total_sun)
{
    if (total_sun >= sun)
    {
        has_enough_sun = true;
        return true;
    }
    else
    {
        has_enough_sun = false;
        enable = false;
        return false;
    }
}
