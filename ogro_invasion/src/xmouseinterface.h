#ifndef XMOUSEINTERFACE_H_INCLUDED
#define XMOUSEINTERFACE_H_INCLUDED

#include <stdexcept>
#include <cassert>

#include "mouseinterface.h"

class XMouseInterface : public MouseInterface
{
public:
    XMouseInterface(GLFWwindow* window):
    m_window(window)
    {
        m_buttonState[0] = m_buttonState[1] = 0;
        m_lastButtonState[0] = m_lastButtonState[1] = 0;

    }

    virtual void getMousePos(int& x, int& y)
    {
        x = m_x;
        y = m_y;
    }

    virtual void setMousePos(int x, int y)
    {
        m_x = x;
        m_y = y;
    }

    virtual void showCursor(bool val)
    {
        return true;
    }
    
    virtual void toggleMousebutton(int button, bool pressed)
    {
        if (pressed)
        {
            m_buttonState[button] = 1;
        }
        else
        {
            m_buttonState[button] = 0;
        }
    }
    
    virtual bool isButtonPressed(int button)
    {
        assert(button < 2);
        return (m_lastButtonState[button] == 0 && m_buttonState[button] == 1);
    }

    virtual void update()
    {
        memcpy(m_lastButtonState, m_buttonState, sizeof(short) * 2);

        
    }

private:
    GLFWwindow* m_window;
    //Cursor m_cursor;
    int m_x;
    int m_y;
    
    short m_buttonState[2];
    short m_lastButtonState[2];
};



#endif // XMOUSEINTERFACE_H_INCLUDED
