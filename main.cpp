#include "SceneManager.h"
#include "ResourceManager.h"

int main(int argc, char** argv)
{
    ResourceManager::GetInstance();
    SceneManager::GetInstance()->Run();
    return 0;
}
