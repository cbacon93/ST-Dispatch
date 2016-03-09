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


int initGL();
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void draw();

bool sim_reset = false;
bool sim_running = false;
GLFWwindow* window;

const int WIDTH = 300;
const int HEIGHT = 150;


int main () {
    
    if (initGL()) return -1;
    std::cout << "Window initialized, starting program" << std::endl;
    
    
    //main loop
    do
    {
        
        
        draw();
        
        
    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);
    
    glfwTerminate();
    
    return 0;
}




void draw() {
    glLoadIdentity();
    
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
    
    //stop
    if (sim_running)
        glColor3f(1.0, 0.0, 0.0);
    else
        glColor3f(0.5, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(0.00, 0.00, 0.0);
    glVertex3f(0.50, 0.00, 0.0);
    glVertex3f(0.50, 0.50, 0.0);
    glVertex3f(0.00, 0.50, 0.0);
    glEnd();
    
    //start
    if (!sim_running)
        glColor3f(0.0, 1.0, 0.0);
    else
        glColor3f(0.0, 0.5, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(0.00, 0.50, 0.0);
    glVertex3f(0.50, 0.50, 0.0);
    glVertex3f(0.50, 1.00, 0.0);
    glVertex3f(0.00, 1.00, 0.0);
    glEnd();
    
    //reset
    if (!sim_reset)
        glColor3f(1.0, 1.0, 0.0);
    else
        glColor3f(0.5, 0.5, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(0.50, 0.00, 0.0);
    glVertex3f(1.00, 0.00, 0.0);
    glVertex3f(1.00, 1.00, 0.0);
    glVertex3f(0.50, 1.00, 0.0);
    glEnd();

    glFlush();
    
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

    
    window = glfwCreateWindow(WIDTH, HEIGHT, "ST-Dispatch", NULL, NULL);
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
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double px, py;
        glfwGetCursorPos(window, &px, &py);
        
        //std::cout << "Cursor Position: " << px << " / " << py << std::endl;
        
        if (px < WIDTH/2 && py < HEIGHT/2 && !sim_running) {
            std::cout << "starting simulation" << std::endl;
            sim_running = true;
        }
        if (px < WIDTH/2 && py >= HEIGHT/2 && sim_running) {
            std::cout << "stopping simulation" << std::endl;
            sim_running = false;
        }
        if (px >= WIDTH/2 && !sim_reset) {
            std::cout << "resetting simulation" << std::endl;
            sim_reset = true;
        }
    }
    
}