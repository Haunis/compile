#include "cup.h"

#include <iostream>

using namespace std;

Cup::Cup()
{
    cout << "Cup 构造调用" << endl;
}

Cup::~Cup()
{
    cout << "Cup 析构调用---->" << endl;
}
