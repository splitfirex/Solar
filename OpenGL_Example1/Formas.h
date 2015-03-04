#pragma once
#include <GL\freeglut.h>
class Formas
{
public:

	static void glTriangulo(double base, double altura){
		glPushMatrix();
		glScaled(base,altura,0);
		glBegin(GL_TRIANGLES); 
		glVertex3f(-0.5, 0, 0);
		glVertex3f(0.5, 0, 0);
		glVertex3f(0, 1, 0);
		glEnd();
		glPopMatrix();
	}

	static void glCuadrado(double lado){
		glPushMatrix();
		glScaled(lado,lado,0);
		glBegin(GL_QUADS); 
		glVertex3f(-0.5, 0, 0);
		glVertex3f(0.5, 0, 0);
		glVertex3f(0.5, 1, 0);
		glVertex3f(-0.5, 1, 0);
		glEnd();
		glPopMatrix();
	}

	static void glPiramide( double base){

		glPushMatrix();
		glTranslated(0,0,-base/4); 
		glRotatef(30,1,0,0);
		glTriangulo(base/2,base/2);
		glPopMatrix();

		glPushMatrix();
		glTranslated(0,000,base/4);  
		glRotatef(-30,1,0,0);
		glTriangulo(base/2,base/2);
		glPopMatrix();

		glPushMatrix();
		glTranslated(base/4,0,0);  
		glRotatef(90,0,1,0);
		glRotatef(-30,1,0,0);
		glTriangulo(base/2,base/2);
		glPopMatrix();

		glPushMatrix();
		glTranslated(-base/4,0,0);  
		glRotatef(90,0,1,0);
		glRotatef(30,1,0,0);
		glTriangulo(base/2,base/2);
		glPopMatrix();
	}

	static void glSatelite(){

		glTranslated(0,-43.30,0);

		glPushMatrix();
		glColor3f(0.0,1.0,0.0);
		glPiramide(100);
		glPopMatrix();


		glPushMatrix();
		glColor3f(1.0,0.0,0.0);
		glTranslated(0,86.60,0);
		glScaled(1,-1,1);
		glPiramide(100);
		glPopMatrix();


		glPushMatrix();
		glColor3f(.5,0.5,0.5);
		glTranslated(0,43.30,-25);
		glRotated(90,1,0,0);
		glCuadrado(50);
		glPopMatrix();

		
	}

	static void glPlaneta(GLUquadric *esfera,double radio){
		glPushMatrix();
		glRotated(90,1,0,0);
		glRotated(180,0,0,0);
		gluSphere(esfera,radio,20,10);
		//glRotated(180,0,1,0);
		glPopMatrix();
	}

	static void glDisco(double radio, double radioExterno){
		glPushMatrix();
		gluDisk(gluNewQuadric(),radio,radioExterno, 100, 3);
		glPopMatrix();
	}

	static void axis(){

		glPushMatrix();
		// Drawing axes
		glBegin( GL_LINES );

		glColor3f(1.0, 0.0, 0.0); // red
		glVertex3f(0, 0, 0);      // origin
		glVertex3f(200, 0, 0);	  // x   

		glColor3f(0.0, 1.0, 0.0); // green
		glVertex3f(0, 0, 0);      // center
		glVertex3f(0, 200, 0);	  // y

		glColor3f(0.0, 0.0, 1.0); // blue
		glVertex3f(0, 0, 0);      // origin
		glVertex3f(0, 0, 200);	  // z   
		glRotated(0.1,1,1,0);
		glEnd(); 
		//scene

		glPolygonMode(GL_FRONT, GL_LINE);  
		//glShadeModel(GL_FLAT); 
		glScaled(100, 100, 100);
		glBegin(GL_TRIANGLES);  // triángulo: secuencia de tuplas
		glNormal3f(1.0, 1.0, 1.0);  // normal xyz
		glColor3f(1.0, 0.0, 0.0);   // red
		glVertex3f(1.0, 0.0, 0.0);  // vértice x
		glColor3f(0.0, 1.0, 0.0);   // green
		glVertex3f(0.0, 1.0, 0.0);  // vértice y
		glColor3f(0.0, 0.0, 1.0);   // blue
		glVertex3f(0.0, 0.0, 1.0);  // vértice z
		glEnd();
		glScaled(1.0/100, 1.0/100, 1.0/100);
		glPolygonMode(GL_FRONT, GL_FILL);
		glShadeModel(GL_SMOOTH);
		glPopMatrix();
	}
};