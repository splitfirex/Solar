#pragma once
#include <Gl/glut.h>


class Escena
{
public:

	virtual void dibujar() = 0;
	virtual void keyboard(unsigned char key, int mX, int mY) = 0;
	virtual void keyboardSP(int key, int mX, int mY) = 0;

	virtual void reshape(int w, int h) = 0;

	Escena(void){};
	~Escena(void){};
};

