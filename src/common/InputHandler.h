#ifndef _INPUTHANDLER_H_
#define _INPUTHANDLER_H_

#include "SDL.h"
#include "Enums.h"
#include <stack>

using namespace std;

class InputHandler
{
public:
    static InputHandler* Instance()
    {
        if(s_pInstance == 0)
        {
            s_pInstance = new InputHandler();
        }

        return s_pInstance;
    }
    void update();
    void clean();

    bool isKeyDown(SDL_Scancode key);
    void setKeyStates(const Uint8 *keystates);

    void setKeyPressed(unsigned keyPressed);
    unsigned getKeyPressed() const;

    stack<unsigned>& getKeyStack();

private:
    InputHandler();
    ~InputHandler() {}
    static InputHandler* s_pInstance;
    const Uint8* m_keystates;
    unsigned _keyPressed;

    stack<unsigned> _keyStack;
};
typedef InputHandler TheInputHandler;

#endif