#include <cstring>
#include <stdlib.h>

#include "Window.h"

Window::Window(int width, int height){
	this->width = width;
	this->height = height;
}

Window::~Window(){}

int Window::getWidth(){
	return this->width;
}

int Window::getHeight(){
	return this->height;
}