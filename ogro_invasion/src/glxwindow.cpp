#include <iostream>
#include <string>

#include <sys/time.h>

#include <GL/Glew.h>
#include <GLFW/glfw3.h>

#include "glxwindow.h"
#include "example.h"
#include "xkeyboardinterface.h"
#include "xmouseinterface.h"

using std::string;


unsigned int GetTickCount() {
    struct timeval t;
    gettimeofday(&t, NULL);
    
    unsigned long secs = t.tv_sec * 1000;
    secs += (t.tv_usec / 1000);
    return secs;
}

SimpleGLXWindow* globalWindow;

SimpleGLXWindow::SimpleGLXWindow():
m_example(NULL),
m_isRunning(true),
m_lastTime(0),
m_Window(0),
m_isFullscreen(false),
m_width(0),
m_height(0),
m_bpp(0),
m_GL3Supported(false),
m_keyboard(NULL),
m_mouse(NULL)
{
    globalWindow = this;
    //not sure how to handle the keyboard interface with GLFW
    m_keyboard = new XKeyboardInterface();
}

BOGLGPKeyCode SimpleGLXWindow::TranslateKey(unsigned int code)
{
    return m_keyboard->translateKey(code);
}

void SimpleGLXWindow::SetMousePos(double deltaX, double deltaY)
{
    // std::cout << "X:" << deltaX << " Y:" << deltaY << std::endl;
    m_mouse->setMousePos(deltaX, deltaY);
    
}

static void OnMouseMove(GLFWwindow* window, double xpos, double ypos)
{
    globalWindow->SetMousePos(xpos, ypos);
}

void SimpleGLXWindow::SetMouseButtonClick(int button, bool pressed)
{
    m_mouse->toggleMousebutton(1, pressed);
}

SimpleGLXWindow::~SimpleGLXWindow()
{
    delete m_keyboard;
    delete m_mouse;
}

GLFWwindow* SimpleGLXWindow::GetWindow()
{
    return m_Window;
}

void SimpleGLXWindow::SetWindow(GLFWwindow *window)
{
    //this is not used, just for testing
    m_Window = window;
    
    //something needs to be done here with the mouse handler
    //try and create the mouse poll
    m_mouse = new XMouseInterface(m_Window);
    m_mouse->showCursor(false);
}

bool SimpleGLXWindow::create(int width, int height, int bpp, bool fullscreen)
{
    if(!glfwInit())
        throw std::runtime_error("glfwInit failed");
    
    // open a window with GLFW
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    
    m_Window = glfwCreateWindow(width, height, "Invasion!", NULL, NULL);
    
    if(!m_Window)
        throw std::runtime_error("glfwCreateWindow failed. Can your hardware handle OpenGL 3.2?");
    //glfwSetCursorPosCallback(m_Window, OnMouseMove);
    glfwMakeContextCurrent(m_Window);
    
    glewExperimental = GL_TRUE; //stops glew crashing on OSX :-/
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("glewInit failed");
    
    while(glGetError() != GL_NO_ERROR) {}
    
    m_lastTime = GetTickCount(); //Initialize the time
    
    //try and create the mouse poll
    m_mouse = new XMouseInterface(m_Window);
    m_mouse->showCursor(false);
    
    return true;
}

void SimpleGLXWindow::swapBuffers()
{
     glfwSwapBuffers(m_Window);
}

void SimpleGLXWindow::destroy()
{
    // clean up and exit
    glfwTerminate();
}

void SimpleGLXWindow::HandleMouseInput()
{
    int state = glfwGetMouseButton(m_Window, GLFW_MOUSE_BUTTON_LEFT);
    if (state == GLFW_PRESS)
    {
        m_mouse->toggleMousebutton(0, true);
    }
    else if (state == GLFW_RELEASE)
    {
        m_mouse->toggleMousebutton(0, false);
    }
    double xpos, ypos;
    glfwGetCursorPos(m_Window, &xpos, &ypos);
    m_mouse->setMousePos(xpos, ypos);
    
}

void SimpleGLXWindow::HandleKeyInput()
{
    int state = glfwGetKey(m_Window, GLFW_KEY_SPACE);
    
    if (state == GLFW_PRESS)
    {
        getKeyboard()->handleKeyDown(TranslateKey(1));
    }
    else if (state == GLFW_RELEASE)
    {
        getKeyboard()->handleKeyUp(TranslateKey(1));
    }
    
    state = glfwGetKey(m_Window, GLFW_KEY_UP);
    
    if (state == GLFW_PRESS)
    {
        getKeyboard()->handleKeyDown(TranslateKey(2));
    }
    else if (state == GLFW_RELEASE)
    {
        getKeyboard()->handleKeyUp(TranslateKey(2));
    }
    
    state = glfwGetKey(m_Window, GLFW_KEY_DOWN);
    
    if (state == GLFW_PRESS)
    {
        getKeyboard()->handleKeyDown(TranslateKey(3));
    }
    else if (state == GLFW_RELEASE)
    {
        getKeyboard()->handleKeyUp(TranslateKey(3));
    }
    
    state = glfwGetKey(m_Window, GLFW_KEY_LEFT);
    
    if (state == GLFW_PRESS)
    {
        getKeyboard()->handleKeyDown(TranslateKey(4));
    }
    else if (state == GLFW_RELEASE)
    {
        getKeyboard()->handleKeyUp(TranslateKey(4));
    }
    
    state = glfwGetKey(m_Window, GLFW_KEY_RIGHT);
    
    if (state == GLFW_PRESS)
    {
        getKeyboard()->handleKeyDown(TranslateKey(5));
    }
    else if (state == GLFW_RELEASE)
    {
        getKeyboard()->handleKeyUp(TranslateKey(5));
    }
    
    state = glfwGetKey(m_Window, GLFW_KEY_W);
    
    if (state == GLFW_PRESS)
    {
        getKeyboard()->handleKeyDown(TranslateKey(6));
    }
    else if (state == GLFW_RELEASE)
    {
        getKeyboard()->handleKeyUp(TranslateKey(6));
    }
    
    state = glfwGetKey(m_Window, GLFW_KEY_A);
    
    if (state == GLFW_PRESS)
    {
        getKeyboard()->handleKeyDown(TranslateKey(7));
    }
    else if (state == GLFW_RELEASE)
    {
        getKeyboard()->handleKeyUp(TranslateKey(7));
    }
    
    state = glfwGetKey(m_Window, GLFW_KEY_S);
    
    if (state == GLFW_PRESS)
    {
        getKeyboard()->handleKeyDown(TranslateKey(8));
    }
    else if (state == GLFW_RELEASE)
    {
        getKeyboard()->handleKeyUp(TranslateKey(8));
    }
    
    state = glfwGetKey(m_Window, GLFW_KEY_D);
    
    if (state == GLFW_PRESS)
    {
        getKeyboard()->handleKeyDown(TranslateKey(9));
    }
    else if (state == GLFW_RELEASE)
    {
        getKeyboard()->handleKeyUp(TranslateKey(9));
    }
    
    //exit program if escape key is pressed
    if(glfwGetKey(m_Window, GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(m_Window, GL_TRUE);
}

void SimpleGLXWindow::processEvents()
{
    getKeyboard()->update();
    
    HandleKeyInput();
    HandleMouseInput();
   
    getMouse()->update();
}

bool SimpleGLXWindow::isRunning()
{
    return m_isRunning;
}

void SimpleGLXWindow::attachExample(Example* example)
{
    m_example = example;
}


float SimpleGLXWindow::getElapsedSeconds()
{
    unsigned int currentTime = GetTickCount();
    unsigned int diff = currentTime - m_lastTime;
    m_lastTime = currentTime;
    return float(diff) / 1000.0f;
}
