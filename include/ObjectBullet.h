#ifndef OBJECTBULLET_H
#define OBJECTBULLET_H

#include <ObjectCharacter.h>

class ObjectBullet : public ObjectCharacter
{
    public:
        ObjectBullet(SDL_Renderer *renderer);
        virtual ~ObjectBullet();

        virtual void Update(int offset);

        void InitPos(int x, int y, int w, int h);

        bool IsShown() const { return is_shown; }
        void Show() { is_shown = true; }
        void Hide() { is_shown = false; }

    protected:
        bool is_shown;
        int speed;

        Uint64 last_move_time;
        float delta_x;
        int init_x;

    private:
};

#endif // OBJECTBULLET_H
