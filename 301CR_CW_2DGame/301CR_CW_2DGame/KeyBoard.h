#pragma once
#include "Input_Sub.h"
class KeyBoard :
    public Input_Sub
{
public:
    KeyBoard();
    virtual ~KeyBoard() {};

   
    void GetInput();
    int GetKey() { return m_key; }

private:
    void HandleButton(int key);
    bool keypressed = false;




};

