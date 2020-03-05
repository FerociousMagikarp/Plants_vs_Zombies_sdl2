#ifndef OBJECTZOMBIE_H
#define OBJECTZOMBIE_H

#include <ObjectCharacter.h>


class ObjectZombie : public ObjectCharacter
{
    public:
        ObjectZombie(SDL_Renderer *renderer);
        virtual ~ObjectZombie();

        virtual void Update(int offset);

        int GetRow() const { return row; }
        void SetRow(int value) { row = value; }
        void SetMoving(bool value) { is_moving = value; }
        void ChangeSpeed(int speed) { this->speed = speed; }

        bool IsShown() const { return is_shown; }

        bool Eating();
        void Walking();
        void Dying();

    protected:
        int speed;

        float delta_x;
        Uint64 last_time;

        int row;
        int init_x;
        bool is_moving;
        bool is_shown;

        bool is_dying;
        bool is_eating;

    private:
        Uint64 m_last_atk_time;
};

#endif // OBJECTZOMBIE_H
