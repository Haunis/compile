#include "box.h"

#include <iostream>

using namespace std;

Box::Box()
{
    cout << "Box 构造调用" << endl;
}

Box::~Box()
{
    cout << "Box 析构调用---->" << endl;
}
