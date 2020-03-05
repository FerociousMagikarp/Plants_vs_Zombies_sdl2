#include "GameControl.h"
#include "ObjectZombie.h"
#include "ObjectPlant.h"
#include "GlobalValues.h"
#include "ObjectClicked.h"
#include "ObjectCard.h"
#include "ObjectBullet.h"
#include "ObjectSun.h"
#include <SDL2/SDL_timer.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

GameControl::GameControl(SDL_Renderer *renderer)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            plants[i][j] = nullptr;
        }
    }
    current_status = NOTHING;
    can_plant = false;
    this->renderer = renderer;

    shovel = new ObjectClicked(renderer, "shovel", 650, 0);
    for (int i=0; i<10; i++)
    {
        cards[i] = new ObjectCard(renderer, "cards/card_peashooter", i);
    }
    total_sun = 0;

    ChangeSunNum(50);

    m_last_zombie_time = m_last_sun_time = 0;

    zombie_appear_time.push(5.0f);
    zombie_appear_time.push(0.3f);
}

GameControl::~GameControl()
{
    for (int i = 0; i < 6; i++)
    {
        for (size_t j = 0; j < zombies[i].size(); j++)
        {
            delete zombies[i][j];
        }
    }
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if (plants[i][j] != nullptr)
            {
                delete plants[i][j];
            }
        }
    }
}

void GameControl::Update(int x_offset)
{
    if (!IsGameOver())
    {
        shovel->Update(x_offset);
        for (int i = 0; i < 10; i++)
        {
            cards[i]->Update(x_offset);
        }
    }
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (plants[j][i] != nullptr)
            {
                plants[j][i]->Update(x_offset);
                if (zombies[i].size() > 0)
                {
                    if (!IsGameOver())
                    {
                        ObjectBullet *bullet = plants[j][i]->EmitBullet();
                        if (bullet != nullptr)
                            bullets[i].push_back(bullet);
                    }
                }
                if (plants[j][i]->GetHP() <= 0)
                {
                    PlantDead(j, i);
                }
            }
        }
        for (size_t j = 0; j < zombies[i].size(); j++)
        {
            ObjectZombie *zombie = zombies[i][j];
            zombie->Update(x_offset);
            if (zombie->GetHP() <= 0)
            {
                if (zombie->IsShown() == false)
                    deadzombies.push_back(zombie);
                else
                    zombie->Dying();
            }
            else   // 吃植物
            {
                int x = zombie->GetX() + zombie->GetW() / 2;
                int cell_x = GetCellX(x);
                if (cell_x <= -2)
                {
                    GameOver(zombie);
                }
                else if (cell_x >= 0 && cell_x < 9)
                {
                    if (plants[cell_x][i] != nullptr)
                    {
                        if (zombie->Collision(plants[cell_x][i])) // 跟植物碰上了
                        {
                            if (zombie->Eating())
                            {
                                plants[cell_x][i]->ReduceHP(zombie->GetAttack());
                            }
                        }
                    }
                    else
                    {
                        zombie->Walking();
                    }
                }
            }
        }
        for (size_t j = 0; j < bullets[i].size(); j++)
        {
            bullets[i][j]->Update(x_offset);
            for (size_t k = 0; k < zombies[i].size(); k++)
            {
                if (bullets[i][j]->Collision(zombies[i][k]))
                {
                    zombies[i][k]->ReduceHP(bullets[i][j]->GetAttack());
                    bullets[i][j]->Hide();
                    break;
                }
            }
            if (bullets[i][j]->IsShown() == false)
            {
                delete bullets[i][j];
                vector<ObjectBullet*>::iterator iter = bullets[i].begin();
                bullets[i].erase(iter + j);
            }
        }
    }

    for (vector<ObjectSun*>::iterator iter = sun_list.begin(); iter != sun_list.end();)
    {
        if ((*iter)->IsShown() == false)
        {
            delete *iter;
            sun_list.erase(iter);
        }
        else
        {
            (*iter)->Update(x_offset);
            iter++;
        }
    }

    if (deadzombies.size() > 0)
    {
        for (size_t i = 0; i < deadzombies.size(); i++)
        {
            ZombieDead(deadzombies[i]);
        }
        deadzombies.clear();
    }
    EventControl();
}

void GameControl::Click(int x, int y)
{
    int cell_x = GetCellX(x);
    int cell_y = GetCellY(y);

    switch (current_status)
    {
    case NOTHING:
        if (sun_list.size() > 0)
        {
            for (size_t i = 0; i < sun_list.size(); i++)
            {
                if (sun_list[i]->IsClicked(x, y))
                {
                    sun_list[i]->Going();
                    ChangeSunNum(25);
                    return;
                }
            }
        }
        if (shovel->IsClicked(x, y))
        {
            shovel->Hide();
            current_status = SELECT_SHOVEL;
        }
        else
        {
            for (int i = 0; i < 10; i++)
            {
                if (cards[i]->IsClicked(x, y))
                {
                    current_status = SELECT_PLANT;
                    selected_card_id = i;
                }
            }
        }
        break;
    case SELECT_PLANT:
        if (can_plant)
        {
            int cell_x = GetCellX(x);
            int cell_y = GetCellY(y);
            AddPlant(0, cell_x, cell_y);
            cards[selected_card_id]->StartCD();
            ChangeSunNum(-cards[selected_card_id]->GetCostSun());
        }
        can_plant = false;
        current_status = NOTHING;
        break;
    case SELECT_SHOVEL:
        PlantDead(plants[cell_x][cell_y]);
        shovel->Show();
        current_status = NOTHING;
        break;
    default:
        break;
    }
}

void GameControl::Cancel()
{
    if (shovel->IsShown() == false)
    {
        shovel->Show();
    }
    current_status = NOTHING;
    can_plant = false;
}

int GameControl::GetCellX(int x)
{
    if (x < 40)
        x -= 80;
    return (x - 40) / 80;
}

int GameControl::GetCellY(int y)
{
    if (y < 90)
        return -1;
    return (y - 90) / 95;
}

void GameControl::AddZombie(int id, int pos_y)
{
    ObjectZombie *zombie = new ObjectZombie(renderer);
    zombie->SetY(global_values::y5[pos_y]);
    zombie->SetRow(pos_y);
    zombies[pos_y].push_back(zombie);
}

void GameControl::AddPlant(int id, int x, int y)
{
    ObjectPlant *plant = new ObjectPlant(renderer);
    plant->SetX(global_values::x9[x]);
    plant->SetY(global_values::y5[y]);
    plant->SetCellX(x);
    plant->SetCellY(y);
    plants[x][y] = plant;
}

void GameControl::PlantDead(ObjectPlant* plant)
{
    if (plant != nullptr)
    {
        plants[plant->GetCellX()][plant->GetCellY()] = nullptr;
        delete plant;
    }
}

void GameControl::PlantDead(int cell_x, int cell_y)
{
    if (plants[cell_x][cell_y] != nullptr)
    {
        delete plants[cell_x][cell_y];
        plants[cell_x][cell_y] = nullptr;
    }
}

void GameControl::ZombieDead(ObjectZombie *zombie)
{
    int row = zombie->GetRow();
    for (vector<ObjectZombie*>::iterator iter = zombies[row].begin(); iter != zombies[row].end(); iter++)
    {
        if (*iter == zombie)
        {
            zombies[row].erase(iter);
            break;
        }
    }
    delete zombie;
}

void GameControl::MouseRect(SDL_Rect &rect1, SDL_Rect &rect2, int x, int y)
{
    if (current_status == SELECT_PLANT)
    {
        rect1.x = x - rect1.w / 2;
        rect1.y = y - rect1.h * 4 / 5;

        int cell_x = GetCellX(x);
        int cell_y = GetCellY(y);

        if (cell_x >= 0 && cell_x < 9 && cell_y >= 0 && cell_y < 5 && plants[cell_x][cell_y] == nullptr)
        {
            rect2.x = global_values::x9[cell_x] - rect2.w / 2;
            rect2.y = global_values::y5[cell_y] - rect2.h;
            SetCanPlant(true);
        }
        else
        {
            SetCanPlant(false);
        }
    }
    else if (current_status == SELECT_SHOVEL)
    {
        rect1.x = x - rect1.w / 5;
        rect1.y = y - rect1.h * 4 / 5;
    }
}

void GameControl::ChangeSunNum(int delta_sun)
{
    total_sun += delta_sun;
    if (total_sun < 0) total_sun = 0;
    else if (total_sun > 9990) total_sun = 9990;
    for (int i = 0; i < 10; i++)
    {
        cards[i]->HasEnoughSun(total_sun);
    }
}

// 本关游戏所有的流程
void GameControl::EventControl()
{
    if (IsGameOver())
        return;
    Uint64 current_time = SDL_GetPerformanceCounter();

    if (TimeEnough(m_last_zombie_time, current_time, zombie_appear_time.front()))
    {
        srand((unsigned int)time(NULL));
        AddZombie(0, rand() % 5);
        m_last_zombie_time = current_time;

        zombie_appear_time.pop();
        zombie_appear_time.push((rand() % 100 + 20) / 50.0f);
    }
    if (TimeEnough(m_last_sun_time, current_time, 3.0f))
    {
        sun_list.push_back(new ObjectSun(renderer, rand() % 400 + 200, rand() % 200 + 300, true));
    }
}

bool GameControl::TimeEnough(Uint64 &last_time, Uint64 current_time, float s_th)
{
    if (last_time == 0)
    {
        last_time = current_time;
        return false;
    }
    float s = (current_time - last_time) / (float)SDL_GetPerformanceFrequency();
    if (s > s_th)
    {
        last_time = current_time;
        return true;
    }
    else
    {
        return false;
    }
}

void GameControl::GameOver(ObjectZombie* hero)
{
    current_status = GAME_OVER;
    for (int i = 0; i < 6; i++)
    {
        for (vector<ObjectZombie*>::iterator iter = zombies[i].begin(); iter != zombies[i].end(); iter++)
        {
            if ((*iter) != hero)
            {
                (*iter)->SetMoving(false);
            }
        }
    }
    hero->SetY((global_values::y5[2] + global_values::y5[3]) / 2);
    hero->ChangeSpeed(40);
}
