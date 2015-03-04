#include "Practica1.h"
#include "Formas.h"
#include "Imagen.h"
#include <iostream>
#include <GL\freeglut.h>
#include <thread>
#include <string>
#include <Windows.h>

int tiempo;
int solEje;
int tierraEje;
int tierraTranslacion;
int lunaEje;
int lunaTranslacion;
int satEje;
int satTranslacion;
int animar;
int panelW, panelH;

bool modoTiling;

GLdouble *zoom;
GLdouble *horizontal;
GLdouble *vertical;

GLUquadric  *sol;
GLUquadric  *luna;
GLUquadric  *tierra;
GLuint texturaTierra;
GLuint texturaLuna;
GLuint texturaSol;


GLuint loadTexture(Imagen* image) ;

Practica1::Practica1(void)
{
	modoTiling = false;
	sol=gluNewQuadric();
	luna=gluNewQuadric();
	tierra=gluNewQuadric();

	cam.psX = 200 ; cam.psY = 200.0; cam.psZ = 200.0;
	cam.veX = cam.veY = cam.veZ = 0.0;
	cam.arX = cam.arZ = 0.0; cam.arY = 1.0;

	// Establecemos la longitud de visual
	vol.xRight = 100 ; vol.xLeft = -100;
	vol.yBot = -400; vol.yTop = 400;
	vol.zNear =1 ; vol.zFar = 1000;

	// Establecemos la perspectiva
	per.aspect = 1;
	per.fovy = 90;
	per.zFar =vol.zFar;
	per.zNear =vol.zNear;

	// Establecemos la ilumunacion
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);   
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glEnable (GL_BLEND); 
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_LIGHT0);
	GLfloat LuzDifusa[4]={1.0, 1.0, 1.0, 0.0};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LuzDifusa);
	//GLfloat LuzAmbiente[4]={0.11f, 0.11f, 0.11f, 1.0f};
	//glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbiente);
	GLfloat posLuz0[4]= {0, 0,0, 1.0}; 
	glLightfv(GL_LIGHT0, GL_POSITION, posLuz0); 
	//GLfloat LuzEmission1[4]={1.0, 1.0, 1.0, 0.0};
	//glLightfv(GL_LIGHT0, GL_EMISSION, LuzEmission1);

	/*glEnable(GL_LIGHT1);
	GLfloat LuzDifusa1[4]={1.0, 1.0, 1.0, 1.0};
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LuzDifusa1);
	GLfloat LuzAmbiente1[4]={0.3f, 0.3f, 0.3f, 1.0f};
	glLightfv(GL_LIGHT1, GL_AMBIENT, LuzAmbiente1);
	GLfloat posLuz1[4]= {cam.psX, cam.psY,cam.psZ, 0.0}; 
	glLightfv(GL_LIGHT1, GL_POSITION, posLuz1); 
	GLfloat LuzEmission2[4]={1.0, 1.0, 1.0, 1.0};
	glLightfv(GL_LIGHT1, GL_EMISSION, LuzEmission2);*/




	//Establezco el valor inicial del tiempo
	tiempo = solEje = tierraEje =  tierraTranslacion = lunaEje = lunaTranslacion = satEje = satTranslacion = 0;

	// Se cargan las texturas
	Imagen *imag = loadBMP("../tierra.bmp");
	texturaTierra = loadTexture(imag); 
	delete	imag;
	imag = loadBMP("../sol.bmp");
	texturaSol = loadTexture(imag); 
	delete	imag;
	imag = loadBMP("../luna.bmp");
	texturaLuna = loadTexture(imag); 
	animar = 1;


	delete imag;

}

void Practica1::dibujarEscena(){
	glMatrixMode(GL_MODELVIEW);  // MODEL
	//glLoadIdentity();
	Formas::axis();

	//Incremento el tiempo
	tiempo++;

	// Dibujamos al sol
	glPushMatrix();
	if(tiempo % 300 == 0) solEje++; 
	glRotated(solEje,0,1,0);
	glColor3d(1,0.8,0.8);

	glBindTexture(GL_TEXTURE_2D, texturaSol);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_specular);
	//glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	//glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	gluQuadricTexture(sol,1);
	Formas::glPlaneta(sol,50);
	glPopMatrix();

	// Dibujamos la orbita de la tierra
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
	glColor3d(1,1,1);
	glRotated(90,1,0,0);
	Formas::glDisco(200,202);
	glPopMatrix();

	// Realizamos el calculo de translacion de la tierra
	glPushMatrix();
	if(tiempo % 60 == 0) tierraTranslacion++; 
	glRotated(tierraTranslacion,0,1,0);
	glTranslated(200,0,0);

	// Dibujamos la orbita de la luna
	glPushMatrix();
	glColor3d(1,1,1);
	glRotated(90,1,0,0);
	Formas::glDisco(50,51);
	glPopMatrix();

	// Dibujamos la orbita del satelite
	glPushMatrix();
	glColor3d(1,1,1);
	Formas::glDisco(30,31);
	glPopMatrix();


	// Realizamos el calculo de translacion del satelite
	glPushMatrix();
	if(tiempo % 5 == 0) satTranslacion++; 
	glRotated(satTranslacion,0,0,1);
	glTranslated(30,0,0);

	//Dibujamos el satelite
	glPushMatrix();
	glScaled(0.1,0.1,0.1);
	glTranslated(0,50,0);
	glRotated(90,1,0,0);
	glPushMatrix();
	if(tiempo % 10 == 0) satEje++; 
	glRotated(satEje,0,1,0);
	glColor3d(0.9,0.9,0.9);
	Formas::glSatelite();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	//Dibujamos la tierra
	glPushMatrix();
	if(tiempo % 30 == 0) tierraEje++; 
	glBindTexture(GL_TEXTURE_2D, texturaTierra);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(tierra,1);
	glRotated(tierraEje,0,1,0);
	glColor3d(1,1,1);
	Formas::glPlaneta(tierra,25);

	// Realizamos el calculo de translacion de la luna
	glPushMatrix();
	if(tiempo % 100 == 0) lunaTranslacion++; 
	glRotated(lunaTranslacion,0,1,0);
	glTranslated(50,0,0);

	//Dibujamos la luna
	glPushMatrix();
	if(tiempo % 30 == 0) lunaEje++; 
	glRotated(lunaEje,0,1,0);
	glColor3d(0.9,0.9,0.9);

	glBindTexture(GL_TEXTURE_2D, texturaLuna);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(luna,1);

	Formas::glPlaneta(luna,10);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	setVisual();
	if(animar % 2 == 0){
		glutPostRedisplay();
	}
}

void Practica1::dibujar(){


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	if(modoTiling){
		// Calculamos cuantas ventanas entraran en la pantalla
		int columnasW = panelW/4;
		double rate =  panelW/panelH;
		int numFilas  = panelH/columnasW*rate;
		//	int filasW = 

		for(int i=0 ; i< 4;i++){
			for(int j = 0 ; j< numFilas ; j++){
				glViewport((i*columnasW),(j*columnasW*rate),columnasW,columnasW*rate);
				dibujarEscena();
			}
		}

	}else{
		glViewport(0,0,panelW,panelH);
		dibujarEscena();
	}

}


void tilingMode(int w, int h){

}

void Practica1::keyboard(unsigned char key, int mX, int mY){

	if(key == 's'){
		animar++;
		glutPostRedisplay();
	}
	// tiling
	if(key == 't'){
		modoTiling= modoTiling == true ? false : true;
	}

	if(key == 'x'){
		cam.psY = cam.psZ = 0; cam.psX = 300;
		cam.arY = 1; cam.arX =0;
		camara = true;
		horizontal = &cam.psZ;
		vertical = &cam.psY;
		glutPostRedisplay();
	}
	if(key == 'y'){
		cam.psX = cam.psZ = 0; cam.psY = 300;
		cam.arX = 1; cam.arY =0;
		camara = true;

		horizontal = &cam.psX;
		vertical = &cam.psZ;
		glutPostRedisplay();
	}
	if(key == 'z'){
		cam.psX = cam.psY = 0; cam.psZ = 300;
		cam.arY = 1; cam.arX =0;
		camara = true;

		horizontal = &cam.psX;
		vertical = &cam.psY;
		glutPostRedisplay();
	}
	if(key == 'i'){
		cam.psX = cam.psY = cam.psZ = 300;
		camara = true;
		glutPostRedisplay();
	}

	// Acercamiento
	if(key == 'n'){
		vol.xLeft++;
		vol.xRight--;
		vol.yBot++;
		vol.yTop--;
		camara = true;
		glutPostRedisplay();
	}

	// Alejamiento
	if(key == 'N'){
		vol.xLeft--;
		vol.xRight++;
		vol.yBot--;
		vol.yTop++;
		camara = true;
		glutPostRedisplay();
	}
	//Desplazo a la derecha
	if(key == 'u'){
		*horizontal += 10;
		camara = true;
		std::cout << (int) *horizontal << std::endl;
		glutPostRedisplay();
	}
	//Desplazo a la izquierda
	if(key == 'U'){
		*horizontal -= 10;
		camara = true;
		std::cout << (int) *horizontal << std::endl;
		glutPostRedisplay();
	}
	//Desplazo arriba
	if(key == 'v'){
		*vertical += 10;
		camara = true;
		std::cout << (int) *horizontal << std::endl;
		glutPostRedisplay();
	}
	//Desplazo abajo
	if(key == 'V'){
		*vertical -= 10;
		camara = true;
		std::cout << (int) *horizontal << std::endl;
		glutPostRedisplay();
	}
	//Cambio de proyeccion
	if(key == 'p'){
		if(modo == MODO_PERSPECTIVA ){
			modo = MODO_ORTOGONAL;
		}else{
			modo = MODO_PERSPECTIVA;
		}
		camara = true;
		glutPostRedisplay();
	}

}

void Practica1::keyboardSP(int key, int mX, int mY){

}



Practica1::~Practica1(void)
{
}

void Practica1::reshape(int w, int h){
	panelH = h; panelW =w;
	vol.xLeft = -w/2;
	vol.xRight = w/2;
	vol.yBot = -h/2;
	vol.yTop = h/2;
	camara = true;
}

GLuint loadTexture(Imagen* image) {

	GLuint textureId;

	glGenTextures(1, &textureId);

	glBindTexture(GL_TEXTURE_2D, textureId); 
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, image->ancho, image->alto, 0,  
		GL_RGB, GL_UNSIGNED_BYTE, image->pixels);   

	return textureId; 

}