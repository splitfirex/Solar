#include "Practica1.h"
#include "Formas.h"
#include "Imagen.h"
#include <iostream>
#include <GL\freeglut.h>
#include <thread>
#include <string>
#include "Camara.h"
#include <Windows.h>
#include "Malla.h"

int tiempo;
int solEje;
int tierraEje;
int tierraTranslacion;
int lunaEje;
int lunaTranslacion;
int satEje;
int satTranslacion;
int animar;
double panelW, panelH;

bool modoTiling;

GLUquadric  *sol;
GLUquadric  *luna;
GLUquadric  *tierra;
GLuint texturaTierra;
GLuint texturaLuna;
GLuint texturaSol;

GLuint loadTexture(Imagen* image) ;
Camara *camaraActual;
Camara *camaras[4];
Malla satelite;

Practica1::Practica1(void)
{
	modoTiling = false;
	sol=gluNewQuadric();
	luna=gluNewQuadric();
	tierra=gluNewQuadric();

	// Inicializo las 4 camaras
	Camara::Vector3 pos = {100,100,100};
	Camara::Vector3 ver = {0,0,0};
	Camara::Vector3 arr = {0,1,0};

	camaras[0] =  new Camara(pos,ver,arr);
	camaras[0]->proyecion(-200,200,-200,200,-50,1000);
/*
	
	camaras[1] =  new Camara(100.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,1.0,0.0);

	camaras[1]->proyecion(-200,200,-200,200,-100,1000);

	camaras[2] =  new Camara(0.0,100.0,0.0,
		0.0,0.0,0.0,
		1.0,0.0,0.0);

	camaras[2]->proyecion(-200,200,-200,200,-100,1000);


	camaras[3] =  new Camara(0.0,0.0,100.0,
		0.0,0.0,0.0,
		0.0,1.0,0.0);

	camaras[3]->proyecion(-200,200,-200,200,-100,1000);*/
	camaraActual = camaras[0];

	// Establecemos la ilumunacion
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);   
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glEnable (GL_BLEND); 
	//glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0);
	GLfloat LuzDifusa[4]={1, 1, 1, 1.0};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LuzDifusa);
	GLfloat LuzEspecular[4]={1, 1, 1, 1.0};
	glLightfv(GL_LIGHT0, GL_SPECULAR, LuzDifusa);
	GLfloat posLuz0[4]= {0, 0,0, 1.0}; 
	glLightfv(GL_LIGHT0, GL_POSITION, posLuz0); 

	glEnable(GL_LIGHT1);
	GLfloat LuzAmbiente1[4]={0.3, 0.3, 0.3};
	glLightfv(GL_LIGHT1, GL_AMBIENT, LuzAmbiente1);


	//Establezco el valor inicial del tiempo
	tiempo = solEje = tierraEje =  tierraTranslacion = lunaEje = lunaTranslacion = satEje = satTranslacion = 0;
	animar = 0;
	// Se cargan las texturas
	Imagen *imag = loadBMP("bmp//tierra.bmp");
	texturaTierra = loadTexture(imag); 
	delete	imag;
	imag = loadBMP("bmp//sol.bmp");
	texturaSol = loadTexture(imag); 
	delete	imag;
	imag = loadBMP("bmp//luna.bmp");
	texturaLuna = loadTexture(imag); 
	delete imag;

	// INICIALIZAMOS LA MALLA DEL SATELITE
	satelite.cargarMalla("mallas\\sateliteMesh.msh");
	satelite.initGL();
}


void Luz(double x, double y, double z){
	GLfloat posLuz1[4]= {x,y,z, 1.0}; 
	glLightfv(GL_LIGHT1, GL_POSITION, posLuz1);
}

void Practica1::dibujarEscena(){
	//tiempo++;
	//animar = true;
	camaraActual->colocarCamara();
	Luz(camaraActual->getPosicion()[0], camaraActual->getPosicion()[1], camaraActual->getPosicion()[2]);

	glMatrixMode(GL_MODELVIEW);

	// Dibujamos al sol
	glPushMatrix(); // 1
	if(tiempo % 100 == 0 && animar) solEje++; 
	glRotated(solEje,0,1,0);
	glColor3d(1,0.8,0.8);

	glBindTexture(GL_TEXTURE_2D, texturaSol);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	gluQuadricTexture(sol,1);
	Formas::glPlaneta(sol,40);

	glPopMatrix(); // 1

	// Dibujamos la orbita de la tierra
	glPushMatrix(); // 2
	glBindTexture(GL_TEXTURE_2D, 0);
	glColor3d(1,1,1);
	glRotated(90,1,0,0);
	Formas::glDisco(100,101);
	glPopMatrix(); // 2

	// Realizamos el calculo de translacion de la tierra
	glPushMatrix(); // 3
	if(tiempo % 15 == 0 && animar) tierraTranslacion++; 
	glRotated(tierraTranslacion,0,1,0);
	glTranslated(100,0,0);

	// Dibujamos la orbita de la luna
	glPushMatrix(); // 4
	glColor3d(1,1,1);
	glRotated(90,1,0,0);
	Formas::glDisco(35,36);
	glPopMatrix(); // 4

	// Dibujamos la orbita del satelite
	glPushMatrix(); //5
	glColor3d(1,1,1);
	Formas::glDisco(25,26);
	glPopMatrix(); //5


	// Realizamos el calculo de translacion del satelite
	glPushMatrix(); // 6
	if(tiempo % 1 == 0 && animar) satTranslacion++; 
	glRotated(satTranslacion,0,0,1);
	glTranslated(25,0,0);

	//Dibujamos el satelite
	glPushMatrix(); // 7

	glTranslated(0,10,0);
	glRotated(90,1,0,0);
	glPushMatrix(); // 8
	if(tiempo % 10 == 0 && animar) satEje++; 
	glRotated(satEje,0,1,0);
	glColor3d(0.9,0.9,0.9);

	// Satelite antiguo
	//Formas::glSatelite();
	glPushMatrix();
	glScaled(3,3,3);
	satelite.dibujar();
	glPopMatrix();

	glPopMatrix(); // 8
	glPopMatrix(); // 7
	glPopMatrix(); // 6


	//Dibujamos la tierra
	glPushMatrix(); // 9
	if(tiempo % 30 == 0 && animar) tierraEje++; 
	glBindTexture(GL_TEXTURE_2D, texturaTierra);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	gluQuadricTexture(tierra,1);
	glRotated(tierraEje,0,1,0);
	glColor3d(1,1,1);
	Formas::glPlaneta(tierra,20);

	// Realizamos el calculo de translacion de la luna
	glPushMatrix(); // 10
	if(tiempo % 100 == 0 && animar) lunaTranslacion++; 
	glRotated(lunaTranslacion,0,1,0);
	glTranslated(35,0,0);

	//Dibujamos la luna
	glPushMatrix(); // 11 
	if(tiempo % 30 == 0 && animar) lunaEje++; 
	glRotated(lunaEje,0,1,0);
	glColor3d(0.9,0.9,0.9);

	glBindTexture(GL_TEXTURE_2D, texturaLuna);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	gluQuadricTexture(luna,1);

	Formas::glPlaneta(luna,5);
	glPopMatrix(); // 11
	glPopMatrix(); // 10
	glPopMatrix(); // 9
	glPopMatrix(); // 3


	animar= false;
}

void Practica1::dibujar(){


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	if(modoTiling){
		// Calculamos cuantas ventanas entraran en la pantalla
		double columnasW = panelW/4;
		double rate =  panelH / panelW;
		double numFilas  = panelH/columnasW*rate;

		for(int i=0 ; i< 4;i++){
			for(int j = 0 ; j< 4 ; j++){
				glViewport((i*columnasW),(j*columnasW*rate),columnasW,columnasW*rate);
				dibujarEscena();
			}
		}

	}else{
		glViewport(0,0,panelW,panelH);
		dibujarEscena();
	}

}



void Practica1::keyboardSP(int key, int mX, int mY){

}



Practica1::~Practica1(void)
{
}

void Practica1::reshape(int w, int h){

	panelW =w ;
	panelH = h;
	camaraActual->reshape(w,h);
	camaraActual->camara = true;
}

GLuint loadTexture(Imagen* image) {

	GLuint textureId;

	glGenTextures(1, &textureId);

	glBindTexture(GL_TEXTURE_2D, textureId); 
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, image->ancho, image->alto, 0,  
		GL_RGB, GL_UNSIGNED_BYTE, image->pixels);   

	return textureId; 

}


void Practica1::keyboard(unsigned char key, int mX, int mY){

	if(key=='g'){

		camaraActual->rotarV(0.01);
	}

	if(key=='G'){
		camaraActual->rotarV(-0.01);
	}

	if(key=='h'){
		camaraActual->rotarU(0.01);
	}

	if(key=='H'){
		camaraActual->rotarU(-0.01);
	}

	if(key == 's'){
		tiempo+=1;
		animar = true;
	}

	if(key == 'S'){
		tiempo-=1;
		animar = true;
	}
	// tiling
	if(key == 't'){
		modoTiling= modoTiling == true ? false : true;
	}

	if(key == 'x'){
		camaraActual = camaras[1];
		camaraActual->reset();
		camaraActual->reshape(panelW,panelH);
		camaraActual->camara = true;
	}
	if(key == 'y'){
		camaraActual = camaras[2];
		camaraActual->reset();
		camaraActual->reshape(panelW,panelH);
		camaraActual->camara = true;
	}
	if(key == 'z'){
		camaraActual = camaras[3];
		camaraActual->reset();
		camaraActual->reshape(panelW,panelH);
		camaraActual->camara = true;
	}
	if(key == 'i'){
		tiempo = solEje = tierraEje =  tierraTranslacion = lunaEje = lunaTranslacion = satEje = satTranslacion = 0;
		camaraActual = camaras[0];
		camaraActual->reset();
		camaraActual->reshape(panelW,panelH);
		camaraActual->camara = true;
	}

	// Acercamiento
	if(key == 'n')	camaraActual->acercar(1);
	// Alejamiento
	if(key == 'N') camaraActual->alejar(1);
	//Desplazo a la derecha
	if(key == 'u') camaraActual->moverDerecha(1);
	//Desplazo a la izquierda
	if(key == 'U') camaraActual->moverIzquierda(1);
	//Desplazo arriba
	if(key == 'v') camaraActual->moverArriba(1);
	//Desplazo abajo
	if(key == 'V') camaraActual->moverAbajo(1);
	//Cambio de proyeccion
	if(key == 'p'){
		if(camaraActual->modo == MODO_PERSPECTIVA ){
			camaraActual->modo = MODO_ORTOGONAL;
		}else{
			camaraActual->modo = MODO_PERSPECTIVA;
		}
		camaraActual->camara = true;
	}

}