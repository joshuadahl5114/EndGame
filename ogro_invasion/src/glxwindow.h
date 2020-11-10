#ifndef GLXWINDOW_H_INCLUDED
#define GLXWINDOW_H_INCLUDED

#define GLX_GLXEXT_LEGACY //Must be declared so that our local glxext.h is picked up, rather than the system one
#include <GL/Glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <ctime>

#include "boglgpwindow.h"
#include "keyboardinterface.h"

class Example; //Declare our Example class
class KeyboardInterface;

class SimpleGLXWindow : public BOGLGPWindow
{
public:
    SimpleGLXWindow(); //default constructor
    virtual ~SimpleGLXWindow();

    bool create(int width, int height, int bpp, bool fullscreen);
    void destroy();
    void processEvents();
    void attachExample(Example* example);

    bool isRunning(); //Is the window running?

    void swapBuffers();
    void SetWindow(GLFWwindow* window);
    void SetMousePos(double deltaX, double deltaY);
    void SetMouseButtonClick(int button, bool pressed);
    BOGLGPKeyCode TranslateKey(unsigned int code);
    void HandleKeyInput();
    void HandleMouseInput();
    
    GLFWwindow* GetWindow();
    
    float getElapsedSeconds();

    KeyboardInterface* getKeyboard() const { return m_keyboard; }
    MouseInterface* getMouse() const { return m_mouse; }
private:
    Example* m_example; //A link to the example program
    bool m_isRunning; //Is the window still running?


    Example* getAttachedExample() { return m_example; }

    unsigned int m_lastTime;

    GLFWwindow* m_Window;
    
    bool m_isFullscreen;
    unsigned int m_width;
    unsigned int m_height;
    unsigned int m_bpp;

    bool m_GL3Supported;

    KeyboardInterface* m_keyboard;
    MouseInterface* m_mouse;
};

#endif // GLXWINDOW_H_INCLUDED
