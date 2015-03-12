#pragma once
#include <GL\freeglut.h>
#define MODO_PERSPECTIVA 1
#define MODO_ORTOGONAL 2

class Camara
{
public:

	int modo;
	bool camara;

	void moverArriba(double escala);
	void moverAbajo(double escala);
	void moverDerecha(double escala);
	void moverIzquierda(double escala);
	void proyecionOrto(double xIzq, double xDer, double yAba, double yArr, double zCer, double zLej);
	double* getPosicion();

	void dibujarPlano();

	void acercar(double escala);
	void alejar(double escala);

	void rotarV(double angulo);
	void rotarU(double angulo);
	void reset();
	void colocarCamara();

	Camara::Camara(double posx, double posy, double posz,  
			   double verx, double very, double verz, 
			   double arx,  double ary,  double arz);

	~Camara(void);

private:

	struct camara{
		GLdouble psX,psY,psZ;
		GLdouble veX,veY,veZ;
		GLdouble arX,arY,arZ;
	} cam;

	struct offset{
		GLdouble x,y,z;
	} off;

	struct ortogonal{
		GLdouble xRight, xLeft;
		GLdouble yTop, yBot;
		GLdouble zNear, zFar;
	} vol;

	struct perspectiva{
		GLdouble fovy;
		GLdouble aspect;
		GLdouble zNear, zFar;
	} per;
};

