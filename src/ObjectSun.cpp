#include "ObjectSun.h"
#include <iostream>

using namespace std;

ObjectSun::ObjectSun(SDL_Renderer *renderer, int x, int y, bool from_sky) : ObjectClicked(renderer, "sun", x, 0)
{
    rotate_angel = 0.0;
    center_point.x = rect.w / 2;
    center_point.y = rect.h / 2;
    if (!from_sky)
    {
        rect.y = y;
    }
    des_y = y;
    m_drop_time = 0;

    drop_speed = 120;
    m_going_to_des_time = 0.3f;
    alive_time = 7.0f;

    dying = false;
    opacity = 255;
    going = false;
}

ObjectSun::~ObjectSun()
{

}

void ObjectSun::Update(int offset)
{
    if (is_shown)
    {
        SDL_Rect pos__ = rect;  pos__.x -= offset;
        if (dying)
        {
            opacity -= 17;
            SDL_SetTextureAlphaMod(texture.texture, opacity);
            SDL_RenderCopyEx(renderer, texture.texture, nullptr, &pos__, rotate_angel, &center_point, SDL_FLIP_NONE);
            SDL_SetTextureAlphaMod(texture.texture, 255);
            if (opacity <= 0)
            {
                is_shown = false;
            }
        }
        else
        {
            SDL_RenderCopyEx(renderer, texture.texture, nullptr, &pos__, rotate_angel, &center_point, SDL_FLIP_NONE);
        }
        rotate_angel += 1.0;
        Uint64 current_time = SDL_GetPerformanceCounter();
        if (going)
        {
            float dt = (current_time - m_going_time) / (float) SDL_GetPerformanceFrequency();
            rect.x = m_click_x - (int)(m_going_speed_x * dt);
            rect.y = m_click_y - (int)(m_going_speed_y * dt);
            if (dt >= m_going_to_des_time)
            {
                going = false;
                dying = true;
            }
        }
        else if (rect.y < des_y && !dying)
        {
            if (m_drop_time != 0)
            {
                float dt = (current_time - m_drop_time) / (float) SDL_GetPerformanceFrequency();
                rect.y += (int)(drop_speed * dt);
            }
            m_drop_time = current_time;
        }
        else if (!dying)
        {
            if (m_alive_time == 0)
            {
                m_alive_time = current_time;
            }
            else
            {
                float s = (current_time - m_drop_time) / (float) SDL_GetPerformanceFrequency();
                if (s > alive_time)
                {
                    dying = true;
                }
            }
        }

    }
}

bool ObjectSun::IsClicked(int x, int y)
{
    if (!dying && !going)
    {
        return ObjectClicked::IsClicked(x, y);
    }
    return false;
}

void ObjectSun::Going()
{
    going = true;
    m_going_time = SDL_GetPerformanceCounter();
    int dx = rect.x - 64;
    int dy = rect.y - 10;
    m_going_speed_x = dx / m_going_to_des_time;
    m_going_speed_y = dy / m_going_to_des_time;
    m_click_x = rect.x;
    m_click_y = rect.y;
}
