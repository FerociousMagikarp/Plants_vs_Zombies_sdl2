#ifndef SCENEGAME_H
#define SCENEGAME_H

#include <SceneBase.h>
#include <vector>
#include <SDL2/SDL_ttf.h>
#include "ResourceManager.h"

class GameControl;

class SceneGame : public SceneBase
{
    public:
        SceneGame(SDL_Renderer *renderer);
        virtual ~SceneGame();

        virtual void Start();
        virtual void Update();
        virtual void Terminate();

        virtual void MousePos(int x, int y);
        virtual void MouseButtonLeft(int x, int y);
        virtual void MouseButtonRight();

        void RenderTTF(int num);

    protected:
        TextureInfo bg;
        TextureInfo bg_house;
        TextureInfo card_slot;

        TextureInfo mouse_plants;
        TextureInfo mouse_shovel;

        TextureInfo game_over_char;

        SDL_Rect bg_rect;
        SDL_Rect slot_rect;
        SDL_Rect screen_rect;
        SDL_Rect mouse_rect1, mouse_rect2;
        SDL_Rect sun_number_rect;

        int x_offset;
        GameControl *controller;

        TTF_Font *font;

    private:
        Uint64 m_game_over_time;
};

#endif // SCENEGAME_H
