#ifndef __USER_INTERFACE
#define __USER_INTERFACE

class UserInterface
{
public:
	UserInterface();
    void init();
    void render();

private:
    void mazeGeneration();
    void searchControl();
};

#endif
