#include <glm/glm.hpp>	
#include <GL/glut.h>
#include <memory>
#include "ObjectPool/ShapePool.h"
#include <time.h>
#include <chrono>
#include <iostream>
#include <vector>
#include "SingletonGraphStates.h"
#include "Transform.h"
#include "QuadTree.h"
#include "GameWindow.h"
#include "Timer.h"
#include "Logger.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h" //support for stdout logging - the logging system im using -PC
//// REFERENCES
//// this was created with input from the book RTCD by C.Ericson, as well as much input from
//// Yan Chernikov tutorials, https://www.youtube.com/channel/UCQ-W1KE9EYfdxhL6S4twUNw
//// The Patterns implemented in this project where understood from, Robert Nystroms Game Programming Patterns


int width = 1000; // set to 1k/1k so as to allow a nice distribution of QuadTree -PC
int height = 1000; // this is also terrible practice but hey if I am using a set of globals, necessary by GLUT, I might as well use these -PC


char title[] = "RTCD";
char* ptrTitle = title; // this is quite strange in comparison to the LAB code which seemingly converts implicitly -PC
GameWindow* window = new GameWindow(title, width, height, 0, 0);
EventManager* eventManager = new EventManager();
std::shared_ptr<ShapePool> Pool = std::make_shared<ShapePool>();
Node* root; 
std::shared_ptr<QuadTree> quadTree = std::make_shared<QuadTree>(ShapePool::POOL_SIZE);

// LAB timer -PC
int refreshMillis = 16;
LowResTimer timer;
double oldTime = 0;


void ReshapeWindow(int width, int height) 
{
	window->Reshape(width, height);
}

void reshape(int width, int height)
{
	ReshapeWindow(width, height); 
}

void initGL() 
{
	glClearColor(0.0, 0.0, 0.0, 1.0); // Set background (clear) color to black
}

void update(int value) // value not used here as I am using the global "Display/Update ElapsedDeltaTime" to go over GLUTS API in the timer and display callbacks -PC
{

	quadTree->Clean(root); // clean QT for reinsertion -PC
	
	Pool->Clean();
	for (int i = 0; i < ShapePool::POOL_SIZE; i++)
	{
		quadTree->Insert(root, Pool->shapes[i]); 
	}
	
	Pool->Update(timer.getTime() - oldTime, width, height);
	quadTree->TestAllcollisions(root, eventManager); // test collisions within spacial data structure -PC
	
	for (int i = 0; i< ShapePool::POOL_SIZE; i++) // this is not optimal but will do -PC
	{
		Pool->shapes[i]->CheckBounds();
	}


	glutPostRedisplay();						// Post a paint request to activate display()
	glutTimerFunc(refreshMillis, update, 0);
	oldTime = timer.getTime();
}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT);	// Clear the color buffer
	glMatrixMode(GL_MODELVIEW);		// To operate on the model-view matrix
	Pool->Display(timer.getTime() - oldTime, width, height);
	glutSwapBuffers();				// Swap front and back buffers (of double buffered mode)
}


void GLUTRenderer()
{	
	initGL();
	glutReshapeFunc(reshape);		// Register callback handler for window re-shape
	glutDisplayFunc(display);		
	glutTimerFunc(0, update, 0);	// First timer call immediately
	glutMainLoop();					// Enter event-processing loop 
}

int main(int argc, char** argv)
{

	int stopDepth = 2; // this means MAX_DEPTH = 256 -PC
	
	Logger::Init(); //init logger -PC
	Logger::GetAppLogger()->info("LOGGER initialized!");
	glutInit(&argc, argv); 
	timer.startTimer();
	Pool->create(); 

	root = quadTree->BuildQuadtree(glm::vec2(height / 2, width / 2), width / 2, stopDepth); // init QT, -PC

	SingletonGraphStates::instance();
	SingletonGraphStates::instance().initialise(); // init singleton -PC
	GLUTRenderer(); // This in a similar form - although not the same as LAB`s hence the Param. -PC
	return 0;
}
