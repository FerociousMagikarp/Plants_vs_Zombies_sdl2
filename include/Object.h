#ifndef OBJECT_H
#define OBJECT_H

#include <SDL2/SDL.h>
#include <vector>
#include "ResourceManager.h"

class Object
{
    public:

        Object(SDL_Renderer *renderer);
        virtual ~Object();

        void LoadAnim(const char* name, int n);
        void PlayAnim(size_t i);

        virtual void Update(int offset);

    protected:

        SDL_Renderer *renderer;
        AnimInfo current_anim;
        std::vector<AnimInfo> anims;

        int anim_fps;
        Uint64 last_time;
        size_t frame_i;

    private:
};

#endif // OBJECT_H
