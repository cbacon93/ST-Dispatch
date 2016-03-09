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
bool sim_active = true;
GLFWwindow* window;



int main () {
    
    if (initGL()) return -1;
    std::cout << "Window initialized, starting program" << std::endl;
    
    /*Networking net = Networking();
    net.initSocket("127.0.0.1", 1111, 1111);
    char sendstr[] = "Hallo Welt!";
    char data[32];*/
    
    //main loop
    do {
        if (sim_active)
            glClearColor(0.0f, 1.0f, 0.0f, 0.0f); //clear background screen to green
        else
            glClearColor(1.0f, 0.0f, 0.0f, 0.0f); //clear background screen to red
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
        /*net.sendData(sendstr, strlen(sendstr));
        std::cout << "Sent string: " << sendstr << std::endl;
        size_t n = net.receiveData(data, 32);
        data[31] = 0;
        std::cout << "Received " << n << " bytes: " << data << std::endl;
        sleep(1);*/
        
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);
    
    //net.closeSocket();
    
    return 0;
}



int initGL() {
    // Initialise GLFW
    
    if (!glfwInit())
        
    {
        std::cerr << "Failed to initialize GLFW\n";
        return 1;
    }
    //glEnable(GL_DEPTH_TEST);
    
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
        sim_active = !sim_active;
}