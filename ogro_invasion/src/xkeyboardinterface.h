#ifndef XKEYBOARDINTERFACE_H_INCLUDED
#define XKEYBOARDINTERFACE_H_INCLUDED

#include <cstring>
#include "keyboardinterface.h"

class XKeyboardInterface : public KeyboardInterface {
public:
    XKeyboardInterface()
    {
        for (int i = 0; i < KC_MAX_KEYS; ++i) {
            m_keyState[i] = 0;
            m_lastKeyState[i] = 0;
        }
    }

    virtual bool isKeyPressed(BOGLGPKeyCode code)
    {
        return (m_lastKeyState[code] == 0 && m_keyState[code] == 1);
    }

    virtual bool isKeyHeldDown(BOGLGPKeyCode code)
    {
        return (m_lastKeyState[code] && m_keyState[code]);
    }

    virtual void   handleKeyDown(BOGLGPKeyCode code)
    {
        m_keyState[code] = 1;
    }

    virtual void handleKeyUp(BOGLGPKeyCode code)
    {
        m_keyState[code] = 0;
    }

    BOGLGPKeyCode translateKey(unsigned int code)
    {
      
        switch(code)
        {
            case 1:
                return KC_SPACE;
            break;
            case 2:
                return KC_UP;
            break;
            case 3:
                return KC_DOWN;
            break;
            case 4:
                return KC_LEFT;
            break;
            case 5:
                return KC_RIGHT;
            break;
            case 6:
                return KC_w;
            break;
            case 7:
                return KC_a;
            break;
            case 8:
                return KC_s;
            break;
            case 9:
                return KC_d;
            break;
        
            default:
                std::cout << "Pressed untranslatable key." << std::endl;
                return KC_INVALID;
        }
        
    }

    void update()
    {
        //Copy the current key state to the last key state
        memcpy(m_lastKeyState, m_keyState, sizeof(short) * KC_MAX_KEYS);
    }

private:
    short m_keyState[KC_MAX_KEYS];
    short m_lastKeyState[KC_MAX_KEYS];
};



#endif // XKEYBOARDINTERFACE_H_INCLUDED
