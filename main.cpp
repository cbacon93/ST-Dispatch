//
//  main.cpp
//  ST-Dispatch
//
//  Created by Marcel Haupt on 08.03.16.
//  Copyright © 2016 Marcel Haupt. All rights reserved.
//


#include <iostream>
#include <GLFW/glfw3.h>
#include "networking.hpp"
#include "bitmap_image.hpp"


int initGL();
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void draw();

bool sim_reset = false;
bool sim_running = false;
GLFWwindow* window;
bitmap_image image_running, image_stopped;



int main () {
    
    if (initGL()) return -1;
    std::cout << "Window initialized, starting program" << std::endl;
    
    //loading images
    //image_running = bitmap_image("/Users/marcel/Documents/Coding/ST-Dispatch/ST-Dispatch/Running.bmp");
    //image_stopped = bitmap_image("/Users/marcel/Documents/Coding/ST-Dispatch/ST-Dispatch/Stopped.bmp");
    
    //main loop
    do {
        draw();
    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);
    
    glfwTerminate();
    
    return 0;
}




void draw() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //clear background screen to green
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glDrawPixels(image_running.width(), image_running.height(), GL_RGB, GL_UNSIGNED_BYTE, image_running.data());
    
    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
}



int initGL() {
    // Initialise GLFW
    
    if (!glfwInit())
        
    {
        std::cerr << "Failed to initialize GLFW\n";
        return 1;
    }
    
    window = glfwCreateWindow(300, 150, "ST-Dispatch", NULL, NULL);
    if (window == NULL) {
        std::cerr << "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible.\n";
        glfwTerminate();
        return 2;
    }
    glfwMakeContextCurrent(window);
    
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    
    return 0;
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        sim_running = !sim_running;
}