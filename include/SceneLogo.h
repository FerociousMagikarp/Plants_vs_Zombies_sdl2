#ifndef SCENELOGO_H
#define SCENELOGO_H

#include <SceneBase.h>


class SceneLogo : public SceneBase
{
    public:
        SceneLogo(SDL_Renderer *renderer);
        virtual ~SceneLogo();

        virtual void Start();
        virtual void Update();
        virtual void Terminate();

    protected:

    private:
        SDL_Texture *m_logo_texture;
        SDL_Rect m_logo_pos;
};

#endif // SCENELOGO_H
