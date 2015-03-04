#pragma once
#include <Gl/glut.h>
#define MODO_PERSPECTIVA 1
#define MODO_ORTOGONAL 2

class Escena
{
public:

	struct camara{
		GLdouble psX,psY,psZ;
		GLdouble veX,veY,veZ;
		GLdouble arX,arY,arZ;
	} cam;

	struct volumen{
		GLdouble xRight, xLeft;
		GLdouble yTop, yBot;
		GLdouble zNear, zFar;
	} vol;

	struct perspectiva{
		GLdouble fovy;
		GLdouble aspect;
		GLdouble zNear, zFar;
	} per;

	int modo;
	bool camara;
	virtual void dibujar() = 0;

	virtual void keyboard(unsigned char key, int mX, int mY) = 0;
	virtual void keyboardSP(int key, int mX, int mY) = 0;

	void setVisual(){

		if(camara) { 

			glMatrixMode(GL_MODELVIEW);   // VIEW
			glLoadIdentity();
			gluLookAt(cam.psX,cam.psY,cam.psZ, 
				cam.veX,cam.veY,cam.veZ, 
				cam.arX,cam.arY,cam.arZ);


			glMatrixMode(GL_PROJECTION);  // Pr
			if(modo == MODO_ORTOGONAL ){

				glLoadIdentity();
				glOrtho(vol.xLeft,vol.xRight, vol.yBot,vol.yTop, vol.zNear,vol.zFar);

			}else{
				glLoadIdentity();
				gluPerspective(per.fovy,per.aspect,per.zNear,per.zFar);

			}
			camara =false;
		}

	};

	virtual void reshape(int w, int h) = 0;

	Escena(void){
		modo = MODO_ORTOGONAL;
		camara = true;
	}
	~Escena(void){}
};

