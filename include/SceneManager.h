#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H


class SceneManager
{
    public:
        static SceneManager* GetInstance();
        virtual ~SceneManager();

        void Run();
        void Quit();

    protected:

    private:
        SceneManager();

        bool m_quit;
};

#endif // SCENEMANAGER_H
