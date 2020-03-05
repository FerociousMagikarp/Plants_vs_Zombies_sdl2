#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include <vector>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_rect.h>
#include <queue>

class ObjectZombie;
class ObjectPlant;
class ObjectClicked;
class ObjectCard;
class ObjectBullet;
class ObjectSun;


class GameControl
{
    public:
        GameControl(SDL_Renderer *renderer);
        virtual ~GameControl();

        void Update(int x_offset);

        void Click(int x, int y);
        void Cancel();

        int GetCellX(int x);
        int GetCellY(int y);

        void AddZombie(int id, int pos_y);
        void AddPlant(int id, int x, int y);
        void PlantDead(ObjectPlant *plant);
        void PlantDead(int cell_x, int cell_y);
        void ZombieDead(ObjectZombie *zombie);

        bool GetCanPlant() const { return can_plant; }
        void SetCanPlant(bool value) { if (can_plant != value) can_plant = value; }
        bool GetRenderShovel() { return (current_status == SELECT_SHOVEL) ? true : false; }
        bool GetRenderPlant() { return (current_status == SELECT_PLANT) ? true : false; }
        int GetTotalSun() const { return total_sun; }
        bool IsGameOver() { return current_status == GAME_OVER; }

        void MouseRect(SDL_Rect &rect1, SDL_Rect &rect2, int x, int y);
        void ChangeSunNum(int delta_sun);

        void EventControl();
        bool TimeEnough(Uint64 &last_time, Uint64 current_time, float s_th);
        void GameOver(ObjectZombie* hero);

    protected:
        SDL_Renderer *renderer;

        ObjectPlant* plants[9][6];
        std::vector<ObjectZombie*> zombies[6];
        std::vector<ObjectBullet*> bullets[6];
        std::vector<ObjectZombie*> deadzombies;

        ObjectClicked* shovel;
        ObjectCard* cards[10];
        std::vector<ObjectSun*> sun_list;

        bool can_plant;
        int selected_card_id;

        int total_sun;

        enum Status { NOTHING, GAME_OVER, SELECT_PLANT, SELECT_SHOVEL };
        Status current_status;

        std::queue<float> zombie_appear_time;

    private:
        Uint64 m_last_zombie_time;
        Uint64 m_last_sun_time;
};

#endif // GAMECONTROL_H
