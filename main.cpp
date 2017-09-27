#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <list>

#include <GL/glut.h>

#include "Window.h"
#include "Circle.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

Circle *player;
Circle *arena[2];
list<Circle*> highObstacles;
list<Circle*> lowObstacles;

int keyFlags[256];

Window *window;

void readParams(char* fileName){
	XMLDocument file;

	string endereco;

	//Read XML file using tinyxml2
	if(file.LoadFile(fileName)){
		cout << "Erro ao ler arquivo XML" << endl;
	}else{
		XMLElement* rootTag = file.FirstChildElement();
		string rootValue;


		//Read parameters
		for(XMLElement* it = rootTag->FirstChildElement(); it != NULL; it = it->NextSiblingElement()){

			rootValue = it->Value();
			
			//Arena file params
			if(rootValue.compare("arquivoDaArena") == 0){

				endereco = it->Attribute("caminho");
				endereco += it->Attribute("nome");
				endereco += + ".";
				endereco += it->Attribute("tipo");
				cout << endereco << endl;
				
			}
		}


	}

	if(file.LoadFile(endereco.c_str())){
		cout << "Erro ao ler arquivo da arena" << endl;
	}else{
		XMLElement* rootTag = file.FirstChildElement();
		string rootValue;


		//Read circle parameters
		for(XMLElement* it = rootTag->FirstChildElement(); it != NULL; it = it->NextSiblingElement()){

			rootValue = it->Value();
			
			//Circle params
			if(rootValue.compare("circle") == 0){
				string cor = it->Attribute("fill");

				int x, y;
				double radius;

				x = it->IntAttribute("cx");
				y = it->IntAttribute("cy");
				radius = it->FloatAttribute("r");

				Circle *c = new Circle(radius, x, y, 0);

				if(cor.compare("red") == 0){
					c->setColor(1, 0, 0);
					highObstacles.push_back(c);
				}else if(cor.compare("black") == 0){
					c->setColor(0, 0, 0);
					lowObstacles.push_back(c);
				}else if(cor.compare("blue") == 0){
					window = new Window(2 * x, 2 * y);
					c->setColor(0, 0, 1);
					arena[0] = c;
				}else if(cor.compare("white") == 0){
					c->setColor(1, 1, 1);
					arena[1] = c;
				}else if(cor.compare("green") == 0){
					c->setColor(0, 1, 0);
					player = c;
				}
			}
		}
	}
}

void initWindow(void)
{
	for (int i = 0; i < 256; ++i)
	{
		keyFlags[i] = 0;
	}
	 // select background color 
	glClearColor (1, 1, 1, 0.0);
	 // inicializar sistema de viz. 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(arena[0]->getCenterX() - arena[0]->getRadius(), arena[0]->getCenterX() + arena[0]->getRadius(), arena[0]->getCenterY() - arena[0]->getRadius(),arena[0]->getCenterY() + arena[0]->getRadius(), -1.0, 1.0);
}

void keyPress(unsigned char key, int x, int y){
	keyFlags[key] = 1;
}

void keyUp(unsigned char key, int x, int y){
	keyFlags[key] = 0;
}

void drawCircle(Circle *circle){
		 // Draw circle as polygon 
	glColor3f (circle->getColorR(), circle->getColorG(), circle->getColorB());
	glBegin(GL_POLYGON);
	glVertex3f(circle->getCenterX(), circle->getCenterY(), 0.0); // center of circle
	int resolution = 64;
	for(int i = 0; i <= resolution;i++) { 
		glVertex3f(
		circle->getCenterX() + (circle->getRadius() * cos(i * 2 * M_PI / resolution) * sin(M_PI / 2)), 
		circle->getCenterY() + (circle->getRadius() * sin(i * 2 * M_PI / resolution) * sin(M_PI / 2)),
		circle->getCenterZ() + (circle->getRadius() * cos(M_PI / 2))
		);
	}
	glEnd();

}

void display(void)
{
	 // Clear pixels 
	glClear (GL_COLOR_BUFFER_BIT);
	
	//Draw arena
	drawCircle(arena[0]);
	drawCircle(arena[1]);
	
	//Draw obstacles
	for (list<Circle*>::iterator iter = highObstacles.begin(); iter != highObstacles.end(); ++iter)
	{
		drawCircle((*iter));
	}
	for (list<Circle*>::iterator iter = lowObstacles.begin(); iter != lowObstacles.end(); ++iter)
	{
		drawCircle((*iter));
	}

	//Draw player
	drawCircle(player);

	/* Dont Wait! */
	glFlush ();
}

void idle(void){
	float delta = window->getWidth()/700;
	
	double distance = sqrt(pow(player->getCenterX() - arena[0]->getCenterX(), 2) + pow(player->getCenterY() - arena[0]->getCenterY(), 2));

	if(keyFlags['a']){
		if((distance < arena[0]->getRadius() - player->getRadius()) || player->getCenterX() > arena[0]->getCenterX()){
			player->addCenterX(-delta);
		}
	}
	if(keyFlags['s']){
		if((distance < arena[0]->getRadius() - player->getRadius()) || player->getCenterY() > arena[0]->getCenterY()){
			player->addCenterY(-delta);
		}
	}
	if(keyFlags['d']){
		if((distance < arena[0]->getRadius() - player->getRadius()) || player->getCenterX() < arena[0]->getCenterX()){
			player->addCenterX(+delta);
		}
	}
	if(keyFlags['w']){
		if((distance < arena[0]->getRadius() - player->getRadius()) || player->getCenterY() < arena[0]->getCenterY()){
			player->addCenterY(+delta);
		}
	}
	glutPostRedisplay();
}

int main(int argc, char** argv){
	readParams(argv[1]);
	argc--;
	argv = &argv[1];
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE |	GLUT_RGB);
	glutInitWindowSize (window->getWidth(), window->getHeight());
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("trabalhocg");
	initWindow();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyPress);
	glutKeyboardUpFunc(keyUp);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}