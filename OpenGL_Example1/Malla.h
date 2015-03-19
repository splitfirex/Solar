#pragma once
#include "GL/glut.h"
#include <stdio.h>
#include <string>
#include <vector>

class Malla
{
public:

	typedef GLfloat Vec3C[3];

	GLuint* indices; GLuint numI; GLuint numD; 
	Vec3C* vertices, *normales, *colores;

	void cargarMalla(char* ruta);
	void dibujar();
	void initGL();
	void liberarGL();

	Malla(void);
	~Malla(void);
};

