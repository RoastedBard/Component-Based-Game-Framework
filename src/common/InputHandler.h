#ifndef _INPUTHANDLER_H_
#define _INPUTHANDLER_H_

#include "SDL.h"
#include "Enums.h"
#include <vector>

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

private:
    InputHandler();
    ~InputHandler() {}
    static InputHandler* s_pInstance;
    const Uint8* m_keystates;
    unsigned _keyPressed;
};
typedef InputHandler TheInputHandler;

#endif