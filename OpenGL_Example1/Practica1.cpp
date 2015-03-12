#include "Practica1.h"
#include "Formas.h"
#include "Imagen.h"
#include <iostream>
#include <GL\freeglut.h>
#include <thread>
#include <string>
#include "Camara.h"
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

GLUquadric  *sol;
GLUquadric  *luna;
GLUquadric  *tierra;
GLuint texturaTierra;
GLuint texturaLuna;
GLuint texturaSol;

GLuint loadTexture(Imagen* image) ;
Camara *camaraActual;
Camara *camaras[4];


Practica1::Practica1(void)
{
	modoTiling = false;
	sol=gluNewQuadric();
	luna=gluNewQuadric();
	tierra=gluNewQuadric();

	// Inicializo las 4 camaras
	camaras[0] =  new Camara(100.0,100.0,100.0,
							 0.0,0.0,0.0,
							 0.0,1.0,0.0);

	camaras[0]->proyecionOrto(-200,200,200,-200,-500,1000);

	camaras[1] =  new Camara(100.0,0.0,0.0,
							 0.0,0.0,0.0,
							 0.0,-1.0,0.0);

	camaras[1]->proyecionOrto(-200,200,200,-200,-500,1000);

	camaras[2] =  new Camara(0.0,100.0,0.0,
							 0.0,0.0,0.0,
							 -1.0,0.0,0.0);

	camaras[2]->proyecionOrto(-200,200,200,-200,-500,1000);

	camaras[3] =  new Camara(0.0,0.0,100.0,
							 0.0,0.0,0.0,
							 0.0,-1.0,0.0);

	camaras[3]->proyecionOrto(-200,200,200,-200,-500,1000);

	camaraActual = camaras[0];

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
	GLfloat LuzDifusa[4]={0.5, 0.5, 0.5, 1.0};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LuzDifusa);
	//GLfloat LuzAmbiente[4]={0.8f, 0.8f, 0.8f, 1.0f};
	//glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbiente);
	GLfloat posLuz0[4]= {0, 0,0, 1.0}; 
	glLightfv(GL_LIGHT0, GL_POSITION, posLuz0); 
	//GLfloat LuzEmission1[4]={1.0, 1.0, 1.0, 0.0};
	//glLightfv(GL_LIGHT0, GL_EMISSION, LuzEmission1);

	glEnable(GL_LIGHT1);
	GLfloat LuzAmbiente1[4]={0.8f, 0.8f, 0.8f, 0.2f};
	glLightfv(GL_LIGHT1, GL_AMBIENT, LuzAmbiente1);
	GLfloat posLuz1[4]= {0,0,0, 1.0}; 
	glLightfv(GL_LIGHT1, GL_POSITION, posLuz1); 

	//Establezco el valor inicial del tiempo
	tiempo = solEje = tierraEje =  tierraTranslacion = lunaEje = lunaTranslacion = satEje = satTranslacion = 0;
	animar = 0;
	// Se cargan las texturas
	Imagen *imag = loadBMP("../tierra.bmp");
	texturaTierra = loadTexture(imag); 
	delete	imag;
	imag = loadBMP("../sol.bmp");
	texturaSol = loadTexture(imag); 
	delete	imag;
	imag = loadBMP("../luna.bmp");
	texturaLuna = loadTexture(imag); 
	delete imag;

}


void Practica1::dibujarEscena(){
	//camaraActual->camara = true;
	camaraActual->colocarCamara();

	glMatrixMode(GL_MODELVIEW);  // MODEL

	Formas::axis();

	//Incremento el tiempo
	//tiempo++;
	//std::cout << tiempo;
	// Dibujamos al sol
	glPushMatrix(); // 1
	if(tiempo % 100 == 0 && animar) solEje++; 
	glRotated(solEje,0,1,0);
	glColor3d(1,0.8,0.8);

	glBindTexture(GL_TEXTURE_2D, texturaSol);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_specular);
	//glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	//glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);

	gluQuadricTexture(sol,1);
	Formas::glPlaneta(sol,40);
	
	glPopMatrix(); // 1
	
	//glDisable(GL_LIGHT0);
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
	glScaled(0.1,0.1,0.1);
	glTranslated(0,25,0);
	glRotated(90,1,0,0);
	glPushMatrix(); // 8
	if(tiempo % 10 == 0 && animar) satEje++; 
	glRotated(satEje,0,1,0);
	glColor3d(0.9,0.9,0.9);
	Formas::glSatelite();
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
	//tiempoRotate++;


	if(modoTiling){
		// Calculamos cuantas ventanas entraran en la pantalla
		double columnasW = panelW/4;
		double rate =  panelW/panelH;
		double numFilas  = panelH/columnasW*rate;
		//	int filasW = 

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
	camaraActual->camara = true;

	panelW =w ;
	panelH = h;
	camaraActual->proyecionOrto(-w/2,w/2,-h/2,h/2,1,1000);
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
		camaraActual->rotarV(1);
	}

	if(key=='G'){
		camaraActual->rotarV(-1);
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
		camaraActual->camara = true;
	}
	if(key == 'y'){
		camaraActual = camaras[2];
		camaraActual->camara = true;
	}
	if(key == 'z'){
		camaraActual = camaras[3];
		camaraActual->camara = true;
	}
	if(key == 'i'){
		camaraActual = camaras[0];
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