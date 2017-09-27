#include "Circle.h"

Circle::Circle(double radius, int centerX, int centerY, int centerZ){
	this->radius = radius;
	this->centerX = centerX;
	this->centerY = centerY;
	this->centerZ = centerZ;
}

Circle::~Circle(){}

double Circle::getRadius(){
	return this->radius;
}

void Circle::setRadius(double radius){
	this->radius = radius;
}

void Circle::setColor(double colorR, double colorG, double colorB){
	this->colorR = colorR;
	this->colorG = colorG;
	this->colorB = colorB;
}

void Circle::setCenter(int centerX, int centerY, int centerZ){
	this->centerX = centerX;
	this->centerY = centerY;
	this->centerZ = centerZ;
}

void Circle::addCenterX(int centerX){
	this->centerX += centerX;
}

void Circle::addCenterY(int centerY){
	this->centerY += centerY;
}

int Circle::getCenterX(){
	return this->centerX;
}

int Circle::getCenterY(){
	return this->centerY;
}

int Circle::getCenterZ(){
	return this->centerZ;
}

double Circle::getColorR(){
	return this->colorR;
}

double Circle::getColorG(){
	return this->colorG;
}

double Circle::getColorB(){
	return this->colorB;
}
