#include "InputHandler.h"

InputHandler* InputHandler::s_pInstance = nullptr;

InputHandler::InputHandler(void)
{
    
}

bool InputHandler::isKeyDown(SDL_Scancode key)
{
    if(m_keystates != 0)
    {
        if(m_keystates[key] == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

void InputHandler::setKeyStates(const Uint8 *keystates)
{
    m_keystates = keystates;
}

void InputHandler::setKeyPressed(unsigned keyPressed)
{
    _keyPressed = keyPressed;
}

unsigned InputHandler::getKeyPressed() const
{
    return _keyPressed;
}