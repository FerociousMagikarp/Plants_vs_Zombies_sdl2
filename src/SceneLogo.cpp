#include "SceneLogo.h"
#include <SDL2/SDL_image.h>
#include "GlobalValues.h"

SceneLogo::SceneLogo(SDL_Renderer *renderer) : SceneBase(renderer)
{

}

SceneLogo::~SceneLogo()
{

}

void SceneLogo::Start()
{
    SceneBase::Start();
    SDL_Surface *surface = IMG_Load("data/pic/logo.png");
    m_logo_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    m_logo_pos.w = m_logo_pos.h = (int)(global_values::WindowHeight / 2.4);
    m_logo_pos.x = (global_values::WindowWidth - m_logo_pos.w) / 2;
    m_logo_pos.y = (global_values::WindowHeight - m_logo_pos.h) / 3;
}

void SceneLogo::Update()
{
    SceneBase::Update();
    SDL_RenderCopy(renderer, m_logo_texture, nullptr, &m_logo_pos);
}

void SceneLogo::Terminate()
{
    SceneBase::Terminate();
    SDL_DestroyTexture(m_logo_texture);
}
