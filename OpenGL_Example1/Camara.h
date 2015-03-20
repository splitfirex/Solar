#pragma once
#include <GL\freeglut.h>

#define MODO_PERSPECTIVA 1
#define MODO_ORTOGONAL 2

class Camara
{
public:

	typedef struct Vector3 { GLfloat x,y,z ; } Vector3;

	int modo;
	bool camara;

	void moverArriba(double escala);
	void moverAbajo(double escala);
	void moverDerecha(double escala);
	void moverIzquierda(double escala);
	void proyecion(double xIzq, double xDer, double yAba, double yArr, double zCer, double zLej);

	double* getPosicion();

	void dibujarPlano();

	void acercar(double escala);
	void alejar(double escala);
	void reshape(int w, int h);


	void rotarV(double angulo);
	void rotarU(double angulo);
	void reset();
	void colocarCamara();
	void colocarLuz();
	Camara::Camara(Vector3 pos, Vector3 ver, Vector3 arr); 
	~Camara(void);

private:

	double escala;
	double anguloY, anguloX;

	struct camara{	Vector3 pos; Vector3 ver; Vector3 arr;
	} cam, ini;

	struct offset{
		GLdouble x,y,z;
	} off;

	struct ortogonal{
		GLdouble xRight, xLeft;
		GLdouble yTop, yBot;
		GLdouble zNear, zFar;
	} vol;

};

