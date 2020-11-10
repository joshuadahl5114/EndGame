#include "glxwindow.h"

#include "example.h"


// standard C++ libraries
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <cmath>

GLFWwindow* gWindow = NULL;

void OnError(int errorCode, const char* msg) {
    throw std::runtime_error(msg);
}



int main(int argc, char** argv)
{
    //Set our window settings
    const int windowWidth = 1024;
    const int windowHeight = 768;
    const int windowBPP = 16;
    bool windowFullscreen = false;
    
    glfwSetErrorCallback(OnError);
    if(!glfwInit())
        throw std::runtime_error("glfwInit failed");
    
    // open a window with GLFW
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    //gWindow = glfwCreateWindow(windowWidth, windowHeight, "End Game", NULL, NULL);
    
    //if(!gWindow)
        //throw std::runtime_error("glfwCreateWindow failed. Can your hardware handle OpenGL 3.2?");
    
    // GLFW settings
    //glfwMakeContextCurrent(gWindow);
    
    SimpleGLXWindow programWindow;
    
    
    //Attempt to create the window
    if (!programWindow.create(windowWidth, windowHeight, windowBPP, windowFullscreen))
    {
        //If it fails
        programWindow.destroy(); //Reset the display and exit
        return 1;
    }
    glfwMakeContextCurrent(programWindow.GetWindow());
    // make sure OpenGL version 3.2 API is available
    if(!GLEW_VERSION_3_2)
        throw std::runtime_error("OpenGL 3.2 API is not available.");
    
    // print out some info about the graphics drivers
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    while(glGetError() != GL_NO_ERROR) {}
    
    //programWindow.SetWindow(gWindow);
    //The example OpenGL code
    Example example(&programWindow);
    
    //Attach our example to our window
    programWindow.attachExample(&example);

    if (!example.init()) //Initialize our example
    {
        programWindow.destroy(); //Reset the display and exit
        return 1;
    }
     double lastTime = glfwGetTime();
    
    //This is the mainloop, we render frames until isRunning returns false
    while(!glfwWindowShouldClose(programWindow.GetWindow()))
    {
        glfwPollEvents();
        
        //this might be duped
        programWindow.processEvents();
        
        double thisTime = glfwGetTime();
        //Update((float)(thisTime - lastTime));
        example.prepare((float)(thisTime - lastTime));
        lastTime = thisTime;

        // example.prepare(elapsedTime); //Do any pre-rendering logic
        example.render(); //Render the scene
     
        
         glfwSwapBuffers(programWindow.GetWindow());
        
        //exit program if escape key is pressed
        if(glfwGetKey(programWindow.GetWindow(), GLFW_KEY_ESCAPE))
            glfwSetWindowShouldClose(programWindow.GetWindow(), GL_TRUE);
    }

    example.shutdown(); //Free any resources
    //programWindow.destroy(); //Destroy the program window
    // clean up and exit
    glfwTerminate();
    
    return 0; //Return success
}


