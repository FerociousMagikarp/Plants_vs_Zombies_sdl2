#ifndef OBJECTSUN_H
#define OBJECTSUN_H

#include <ObjectClicked.h>


class ObjectSun : public ObjectClicked
{
    public:
        ObjectSun(SDL_Renderer *renderer, int x, int y, bool from_sky);
        virtual ~ObjectSun();

        virtual void Update(int offset);
        virtual bool IsClicked(int x, int y);

        void Going();

    protected:
        int drop_speed;
        float alive_time;

        double rotate_angel;
        SDL_Point center_point;

        int des_y;

        bool dying;
        int opacity;
        bool going;

    private:
        Uint64 m_drop_time;
        Uint64 m_alive_time;
        Uint64 m_going_time;
        float m_going_to_des_time;
        float m_going_speed_x;
        float m_going_speed_y;
        int m_click_x;
        int m_click_y;
};

#endif // OBJECTSUN_H
