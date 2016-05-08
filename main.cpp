//
//  main.cpp
//  ST-Dispatch
//
//  Created by Marcel Haupt on 08.03.16.
//  Copyright © 2016 Marcel Haupt. All rights reserved.
//


#ifdef _WIN32
#pragma comment (lib, "glfw3.lib")
#pragma comment (lib, "OpenGL32.lib")
#endif


#include <iostream>
#include <chrono>
#include <cmath>
#include <GLFW/glfw3.h>
#include <unistd.h>
#include "networking.hpp"
#include "database.hpp"
#include "timer_controller.hpp"
#include "client_example.hpp"
#include "client_pfd.hpp"
#include "client_xplane.hpp"
#include "client_anzeigen.hpp"


//Constants
const int WIDTH = 300;
const int HEIGHT = 200;
const double FREQUENCY = 25;
const double RESETWAITTIME = 5; //Sekunden


//init functions
int initGL();
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void draw();
void sim_start_timeout(int run);
void mySleep(int ms);


//global variables
Database db; //used for access to database
TimerController tc;
GLFWwindow * window;



int main () {
    //init window and opengl
    if (initGL()) return -1;
    std::cout << "Window initialized, starting program" << std::endl;
    
    //init database
    db.initData();
    
    //init clients - ip - sendport - recvport
    //ClientExample testClient(&db, "172.31.2.141", 1111, 1112);
    ClientPFD clientPFD(&db, "192.168.178.38", 23004, 0);
    ClientXplane clientXplane(&db, "192.168.178.38", 0, 49001);
    ClientAnzeigen clientAnzeigen(&db, "127.0.0.1", 10001, 0);
    
    //main loop
    do
    {
        //timer start
        std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
        std::chrono::high_resolution_clock::time_point wt1 = std::chrono::high_resolution_clock::now();
        
        //drawing GUI
        draw();
        
        //sending synchron messages
        //testClient.sendInfo();
        clientPFD.sendInfo();
        clientAnzeigen.sendInfo();
        
        //timer stop
        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
        
        //sleeping
        double waittime = 1 / FREQUENCY - duration.count();
        if (waittime > 0)
            mySleep(floor(waittime*0.9*1000));
        
        //timer stop 2
        std::chrono::high_resolution_clock::time_point wt2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> wduration = std::chrono::duration_cast<std::chrono::duration<double>>(wt2 - wt1);
        //std::cout << wduration.count() << std::endl;
        tc.simulationtime(wduration.count());
        
        
    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);
    
    glfwTerminate();
    std::cout << "Shutting down" << std::endl;
    
    return 0;
}




void draw() {
    
    //set draw matrix to identity
    //clear screen
    glLoadIdentity();
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
    
    //draw squares
    //stop
    if (db.sim_running.get())
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
    if (!db.sim_running.get())
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
    if (!db.sim_resetted.get())
        glColor3f(1.0, 1.0, 0.0);
    else
        glColor3f(0.5, 0.5, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(0.50, 0.00, 0.0);
    glVertex3f(1.00, 0.00, 0.0);
    glVertex3f(1.00, 1.00, 0.0);
    glVertex3f(0.50, 1.00, 0.0);
    glEnd();

    //write squares to back buffer
    glFlush();
    
    // Swap buffers - back to front buffer
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


//called when a mouse button is clicked inside the window
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    //only act if its the left mouse button
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double px, py;
        glfwGetCursorPos(window, &px, &py);
        
        //std::cout << "Cursor Position: " << px << " / " << py << std::endl;
        
        //press on start
        if (px < WIDTH/2 && py < HEIGHT/2 && !db.sim_running.get()) {
            std::cout << "starting simulation" << std::endl;
            db.sim_running.set(true);
        }
        
        //press on stop
        if (px < WIDTH/2 && py >= HEIGHT/2 && db.sim_running.get()) {
            std::cout << "stopping simulation" << std::endl;
            db.sim_running.set(false);
        }
        
        //press on reset
        if (px >= WIDTH/2 && !db.sim_resetted.get()) {
            std::cout << "resetting simulation" << std::endl;
            db.sim_resetted.set(true);
            
            //add timer after several seconds, deactivate reset flag
            if (db.sim_running.get()) {
                db.sim_running.set(false);
                tc.addController(sim_start_timeout, 1, RESETWAITTIME);
            } else {
                tc.addController(sim_start_timeout, 0, RESETWAITTIME);
            }
        }
    }
    
}


//reset timer timeout callback
void sim_start_timeout(int run) {
    db.sim_running.set((bool)run);
    db.sim_resetted.set(false);
}


//own platform independend sleep funcion
void mySleep(int ms) {
#ifdef __APPLE__
    usleep(ms * 1000);
#endif
#ifdef _WIN32
    Sleep(ms);
#endif
}