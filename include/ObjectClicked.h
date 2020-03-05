#ifndef OBJECTCLICKED_H
#define OBJECTCLICKED_H

#include <Object.h>


class ObjectClicked : public Object
{
    public:
        ObjectClicked(SDL_Renderer *renderer, const char* name, int x, int y);
        virtual ~ObjectClicked();

        virtual void Update(int offset);

        void Show() { is_shown = true; }
        void Hide() { is_shown = false; }
        bool IsShown() const { return is_shown; }
        bool IsClicked(int x, int y);

    protected:
        TextureInfo texture;
        SDL_Rect rect;
        bool is_shown;

    private:
};

#endif // OBJECTCLICKED_H
