#ifndef OBJECTPLANT_H
#define OBJECTPLANT_H

#include <ObjectCharacter.h>

class ObjectBullet;

class ObjectPlant : public ObjectCharacter
{
    public:
        ObjectPlant(SDL_Renderer *renderer);
        virtual ~ObjectPlant();

        virtual void Update(int offset);

        int GetCellX() const { return cell_x; }
        int GetCellY() const { return cell_y; }
        void SetCellX(int value) { cell_x = value; }
        void SetCellY(int value) { cell_y = value; }

        ObjectBullet* EmitBullet();

    protected:
        int cell_x;
        int cell_y;

    private:
        Uint64 m_last_atk;
};

#endif // OBJECTPLANT_H
