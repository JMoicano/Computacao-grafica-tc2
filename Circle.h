#ifndef _CIRCLE_H_
#define _CIRCLE_H_

class Circle
{
private:
	double radius, colorR, colorG, colorB;
	int centerX, centerY, centerZ;
public:
	Circle(double, int, int, int);
	void setRadius(double);
	double getRadius();
	void setColor(double, double, double);
	void setCenter(int, int, int = 0);
	void addCenterX(int);
	void addCenterY(int);
	int getCenterX();
	int getCenterY();
	int getCenterZ();
	double getColorR();
	double getColorG();
	double getColorB();
	~Circle();
	
};

#endif