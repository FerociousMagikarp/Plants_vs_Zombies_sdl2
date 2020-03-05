#include "SceneManager.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include "SceneGame.h"
#include "GlobalValues.h"

#include "ResourceManager.h"

SceneManager::SceneManager()
{
    m_quit = false;
}

SceneManager::~SceneManager()
{

}

SceneManager* SceneManager::GetInstance()
{
    static SceneManager instance;
    return &instance;
}

void SceneManager::Run()
{
    SDL_Event event;
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    SDL_Window *window = SDL_CreateWindow(global_values::Name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          global_values::WindowWidth, global_values::WindowHeight, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // 等着删了
    ResourceManager::GetInstance()->LoadAnim(renderer, "peashooter", 31);
    ResourceManager::GetInstance()->LoadAnim(renderer, "zombie/idle", 31);
    ResourceManager::GetInstance()->LoadAnim(renderer, "zombie/walk", 31);
    ResourceManager::GetInstance()->LoadAnim(renderer, "zombie/eat", 22);
    ResourceManager::GetInstance()->LoadAnim(renderer, "zombie/dead", 19);

    SceneBase *scene = new SceneGame(renderer);
    scene->Start();

    while(!m_quit)
    {
        Uint64 start_time = SDL_GetPerformanceCounter();

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                Quit();
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    scene->MouseButtonLeft(event.motion.x, event.motion.y);
                }
                else if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    scene->MouseButtonRight();
                }
            }
            else
            {
                scene->MousePos(event.motion.x, event.motion.y);
            }
        }

        SDL_RenderClear(renderer);
        scene->Update();
        SDL_RenderPresent(renderer);

        Uint64 end_time = SDL_GetPerformanceCounter();
        float ms = (end_time - start_time) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
        float rest_time = floor(1000.0f / global_values::Fps - ms);
        SDL_Delay(rest_time > 0 ? rest_time : 0);
    }
    delete scene;
    ResourceManager::GetInstance()->DestroyTextures();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

void SceneManager::Quit()
{
    m_quit = true;
}
