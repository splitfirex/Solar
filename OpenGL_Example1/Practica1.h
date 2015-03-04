#pragma once
#include "Escena.h"
class Practica1 : public Escena
{
public:
	void dibujar();
	void keyboard(unsigned char key, int mX, int mY);
	void keyboardSP(int key, int mX, int mY);
	void reshape(int h, int w);
	void dibujarEscena();

	Practica1(void);
	~Practica1(void);

};
	
