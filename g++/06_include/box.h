#ifndef BOX_H
#define BOX_H

#include "cup.h"

class Cup;
class Box
{
    public:
        Box();
		~Box();
//		Cup cup;
        Cup *cup;
};

#endif // BOX_H
