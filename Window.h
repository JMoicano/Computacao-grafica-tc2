#ifndef _WINDOW_H_
#define _WINDOW_H_ 

#include <string>

class Window
{
private:
	int width, height;
	double colorR, colorG, colorB;
	std::string title;
public:
	Window(int, int);
	int getWidth();
	int getHeight();
	~Window();
	
};

#endif