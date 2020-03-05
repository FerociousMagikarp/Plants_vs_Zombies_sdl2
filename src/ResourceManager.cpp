#include "ResourceManager.h"
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

using namespace std;

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{

}

ResourceManager* ResourceManager::GetInstance()
{
    static ResourceManager instance;
    return &instance;
}

AnimInfo ResourceManager::LoadAnim(SDL_Renderer *renderer, const char* name, int n)
{
    if (m_anim_info.find(name) == m_anim_info.end())
    {
        string dir = "data/seq/";
        string complete_name = dir + name + ".png";
        SDL_Surface *surface = IMG_Load(complete_name.c_str());
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        AnimInfo info;
        info.texture = texture;
        info.w = (float)surface->w / n;
        info.h = surface->h;
        info.n = n;
        SDL_FreeSurface(surface);
        m_anim_info[name] = info;
    }
    return m_anim_info[name];
}

TextureInfo ResourceManager::LoadTexture(SDL_Renderer *renderer, const char* filename)
{
    if (m_texture.find(filename) == m_texture.end())
    {
        string dir = "data/pic/";
        string complete_name = dir + filename + ".png";
        SDL_Surface *surface = IMG_Load(complete_name.c_str());
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        TextureInfo info;
        info.texture = texture;
        info.w = surface->w;
        info.h = surface->h;
        SDL_FreeSurface(surface);
        m_texture[filename] = info;
    }
    return m_texture[filename];
}

void ResourceManager::DestroyTextures()
{
    for (map<string, AnimInfo>::iterator iter = m_anim_info.begin(); iter != m_anim_info.end(); iter++)
    {
        SDL_DestroyTexture(iter->second.texture);
    }
    for (map<string, TextureInfo>::iterator iter = m_texture.begin(); iter != m_texture.end(); iter++)
    {
        SDL_DestroyTexture(iter->second.texture);
    }
    m_anim_info.clear();
    m_texture.clear();
}
