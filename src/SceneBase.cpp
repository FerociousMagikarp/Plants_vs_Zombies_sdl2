#include "SceneBase.h"
#include <SDL2/SDL_image.h>

SceneBase::SceneBase(SDL_Renderer *renderer)
{
    this->renderer = renderer;
}

SceneBase::~SceneBase()
{
    Terminate();
}

void SceneBase::Start()
{

}

void SceneBase::Update()
{

}

void SceneBase::Terminate()
{

}

void SceneBase::InitRect(SDL_Rect &rect, int x, int y, int w, int h)
{
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
}

void SceneBase::MousePos(int x, int y)
{

}

void SceneBase::MouseButtonLeft(int x, int y)
{

}

void SceneBase::MouseButtonRight()
{

}
