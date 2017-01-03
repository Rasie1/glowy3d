#include "Engine.h"
#include <iostream> 

using namespace std;

void init()
{
    cout << "test" << endl;
}

void update()
{

}

int main()
{
    glowy3d::start(init, update);
}
