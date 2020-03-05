#include "SceneGame.h"
#include "GameControl.h"
#include "GlobalValues.h"
#include <string>
#include <sstream>
#include <iostream>

using namespace std;


SceneGame::SceneGame(SDL_Renderer *renderer) : SceneBase(renderer)
{
    m_game_over_time = 0;
}

SceneGame::~SceneGame()
{
    delete controller;
    TTF_CloseFont(font);
}

void SceneGame::Start()
{
    SceneBase::Start();
    bg = ResourceManager::GetInstance()->LoadTexture(renderer, "bg_day");
    bg_house = ResourceManager::GetInstance()->LoadTexture(renderer, "bg_day_house");
    card_slot = ResourceManager::GetInstance()->LoadTexture(renderer, "card_slot");

    mouse_plants = ResourceManager::GetInstance()->LoadTexture(renderer, "plants/peashooter");
    mouse_shovel = ResourceManager::GetInstance()->LoadTexture(renderer, "shovel");

    game_over_char = ResourceManager::GetInstance()->LoadTexture(renderer, "game_over");

    controller = new GameControl(renderer);

    InitRect(screen_rect, 0, 0, global_values::WindowWidth, global_values::WindowHeight);
    InitRect(bg_rect, 210, 0, global_values::WindowWidth, global_values::WindowHeight);
    InitRect(slot_rect, 50, 0, card_slot.w, card_slot.h);
    InitRect(mouse_rect1, 0, 0, (int)(mouse_plants.w * 0.4f), (int)(mouse_plants.h * 0.4f));
    InitRect(mouse_rect2, 0, 0, (int)(mouse_plants.w * 0.4f), (int)(mouse_plants.h * 0.4f));
    InitRect(sun_number_rect, 67, 54, 48, 20);
    x_offset = 0;

    font = TTF_OpenFont("data/font/arialbd.ttf", 19);
}

void SceneGame::Update()
{
    SceneBase::Update();


    SDL_Rect bg__ = bg_rect; bg__.x += x_offset;
    SDL_RenderCopy(renderer, bg.texture, &bg__, &screen_rect);
    if (!controller->IsGameOver())
    {
        SDL_RenderCopy(renderer, card_slot.texture, nullptr, &slot_rect);
        RenderTTF(controller->GetTotalSun());
    }

    controller->Update(x_offset);

    if (controller->GetRenderShovel())
    {
        SDL_RenderCopy(renderer, mouse_shovel.texture, nullptr, &mouse_rect1);
    }
    if (controller->GetRenderPlant())
    {
        if (controller->GetCanPlant() == true)
        {
            SDL_SetTextureAlphaMod(mouse_plants.texture, 128);
            SDL_RenderCopy(renderer, mouse_plants.texture, nullptr, &mouse_rect2);
            SDL_SetTextureAlphaMod(mouse_plants.texture, 255);
        }
        SDL_RenderCopy(renderer, mouse_plants.texture, nullptr, &mouse_rect1);
    }
    if (controller->IsGameOver())
    {
        SDL_Rect bg_house__ = screen_rect;  bg_house__.x = -x_offset-210;
        SDL_RenderCopy(renderer, bg_house.texture, nullptr, &bg_house__);
        if (x_offset > -210)
            x_offset -= 10;
        else
        {
            Uint64 ct = SDL_GetPerformanceCounter();
            if (m_game_over_time == 0)
            {
                m_game_over_time = ct;
            }
            else
            {
                float s = (ct - m_game_over_time) / (float) SDL_GetPerformanceFrequency();
                if (s > 3.0f)
                {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 196);
                    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                    SDL_RenderFillRect(renderer, &screen_rect);
                    SDL_Rect over_rect__;
                    float scale__ = std::min(s - 3.0f, 1.0f);
                    over_rect__.w = (int)(scale__ * screen_rect.w);
                    over_rect__.h = (int)(scale__ * screen_rect.h);
                    over_rect__.x = (screen_rect.w - over_rect__.w) / 2;
                    over_rect__.y = (screen_rect.h - over_rect__.h) / 2;
                    SDL_RenderCopy(renderer, game_over_char.texture, nullptr, &over_rect__);
                }
            }
        }
    }
}

void SceneGame::Terminate()
{
    SceneBase::Terminate();
}

void SceneGame::MousePos(int x, int y)
{
    SceneBase::MousePos(x, y);
    controller->MouseRect(mouse_rect1, mouse_rect2, x, y);
}

void SceneGame::MouseButtonLeft(int x, int y)
{
    controller->Click(x, y);
}

void SceneGame::MouseButtonRight()
{
    controller->Cancel();
}

void SceneGame::RenderTTF(int num)
{
    SDL_Color color = {0, 0, 0};

    SDL_Rect render_rect = sun_number_rect;

    string s;
    stringstream ss;
    ss << num;
    ss >> s;

    render_rect.w = (int)(render_rect.w * s.length() / 4.0f);
    render_rect.x += (sun_number_rect.w - render_rect.w) / 2;

    SDL_Surface *surface = TTF_RenderText_Blended(font, s.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, nullptr, &render_rect);
    SDL_DestroyTexture(texture);
}
