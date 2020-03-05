#ifndef SCENEBASE_H
#define SCENEBASE_H

#include <SDL2/SDL.h>

class SceneBase
{
    public:
        SceneBase(SDL_Renderer *renderer);
        virtual ~SceneBase();

        virtual void Start();
        virtual void Update();
        virtual void Terminate();

        virtual void MousePos(int x, int y);
        virtual void MouseButtonLeft(int x, int y);
        virtual void MouseButtonRight();

        void InitRect(SDL_Rect& rect, int x, int y, int w, int h);

    protected:
        SDL_Renderer *renderer;

    private:
};

#endif // SCENEBASE_H
