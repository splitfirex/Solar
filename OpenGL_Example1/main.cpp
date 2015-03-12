#include <stdio.h>
#include <iostream>
#include <GL/freeglut.h>
#include "Escena.h"
#include <Windows.h>
#include "Practica1.h"
#define  ANCHO 400.0
#define  ALTO  400.0


void Display();
void reshape(int w, int h);
void initGL();
void keyFunc(unsigned char key, int mX, int mY);
void keySp(int key, int mX, int mY);
void timer(int flag);

Escena *actual;

int main(int argc, char *argv[]){

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400,400);
	glutInit(&argc,argv);
	glutCreateWindow("Graficas Practica 1");
	actual = new Practica1();

	glutDisplayFunc(Display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyFunc);
	glutSpecialFunc(keySp);
	timer(0);
	glutMainLoop();

	return 0;
}

void timer(int flag){
	glutPostRedisplay();
	glutTimerFunc(1000/60,timer,0);
}

void Display(){
	actual->dibujar();
	//glFlush();
	glutSwapBuffers();
}

void reshape(int w, int h){
	actual->reshape(w,h);
}


void keyFunc(unsigned char key, int mX, int mY){
	actual->keyboard(key,mX,mY);
}

void keySp(int key, int mX, int mY){
	actual->keyboardSP(key,mX, mY);
}