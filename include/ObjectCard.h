#ifndef OBJECTCARD_H
#define OBJECTCARD_H

#include <ObjectClicked.h>


class ObjectCard : public ObjectClicked
{
    public:
        ObjectCard(SDL_Renderer *renderer, const char* name, int n);
        virtual ~ObjectCard();

        virtual void Update(int offset);
        virtual bool IsClicked(int x, int y);
        void StartCD();
        bool HasEnoughSun(int total_sun);

        int GetCostSun() const { return sun; }

        bool GetEnable() const { return enable; }

    protected:
        float cd;
        bool enable;
        bool in_cd;
        bool has_enough_sun;
        int sun;

    private:
        Uint64 m_last_cd_time;
};

#endif // OBJECTCARD_H
