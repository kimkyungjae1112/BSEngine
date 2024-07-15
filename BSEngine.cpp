#include "BSEngine.h"

double OBSEngine::GetCurrentTime()
{
    return static_cast<double>(clock()) * 1000.0 / CLOCKS_PER_SEC;
}

void OBSEngine::Update()
{
    //std::cout << "Update State" << std::endl;
}

void OBSEngine::Render()
{
    //std::cout << "Render State" << std::endl;
}
