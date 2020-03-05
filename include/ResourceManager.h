#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <SDL2/SDL.h>
#include <string>

struct TextureInfo
{
    SDL_Texture *texture;
    int w;
    int h;
};

struct AnimInfo
{
    SDL_Texture *texture;
    float w;
    int h;
    size_t n;
};

class ResourceManager
{
    public:
        static ResourceManager* GetInstance();
        virtual ~ResourceManager();

        AnimInfo LoadAnim(SDL_Renderer *renderer, const char* filename, int n);
        TextureInfo LoadTexture(SDL_Renderer *renderer, const char* filename);

        void DestroyTextures();

    protected:

    private:
        ResourceManager();
        std::map<std::string, AnimInfo> m_anim_info;
        std::map<std::string, TextureInfo> m_texture;
};

#endif // RESOURCEMANAGER_H
