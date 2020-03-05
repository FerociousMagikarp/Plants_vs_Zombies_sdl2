#ifndef OBJECTCHARACTER_H
#define OBJECTCHARACTER_H

#include <Object.h>


class ObjectCharacter : public Object
{
    public:
        ObjectCharacter(SDL_Renderer *renderer);
        virtual ~ObjectCharacter();

        virtual void Update(int offset);
        void SetX(int x) { this->x = x; }
        void SetY(int y) { this->y = y; }
        void SetScale(float scale) { this->scale = scale; }

        int GetW() const { return (int)(current_anim.w * scale); }
        int GetH() const { return (int)(current_anim.h * scale); }
        int GetX() const { return (int)(x - GetW() * anchor_x); }
        int GetY() const { return (int)(y - GetH() * anchor_y); }
        int GetHP() const { return hp; }
        void ReduceHP(int delta) { hp -= delta; }
        int GetAttack() const { return attack; }
        bool HasColision() const { return has_colision; }

        bool Collision(const ObjectCharacter* object);

    protected:
        int x;
        int y;
        float scale;
        float anchor_x;
        float anchor_y;
        bool has_colision;

        float attack_speed;
        int hp;
        int attack;

    private:
};

#endif // OBJECTCHARACTER_H
