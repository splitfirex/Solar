#include "Camara.h"
#include "math.h"
#include <Windows.h>
#include <iostream>

#define PI 3.14159265

int panelH, panelW;

GLfloat modulo(Camara::Vector3 v1){
	return sqrt(v1.x*v1.x + v1.y*v1.y + v1.z*v1.z);
}

GLfloat prodEscalar(Camara::Vector3 v1, Camara::Vector3 v2){
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

Camara::Vector3 prodVectorial(Camara::Vector3 v1, Camara::Vector3 v2){
	Camara::Vector3 resultado;
	resultado.x = v1.y*v2.z - v1.z*v2.y; 
	resultado.y = v1.x*v2.z - v1.z*v2.x;
	resultado.z = v1.x*v2.y - v1.y*v2.x;
	return resultado;
}

Camara::Vector3 normalizar(Camara::Vector3 v1){
	Camara::Vector3 resultado;
	GLfloat mod =  modulo(v1);
	resultado.x = v1.x/mod;
	resultado.y = v1.y/mod;
	resultado.z = v1.z/mod;
	return resultado;
}

Camara::Vector3 getVector(Camara::Vector3 x1, Camara::Vector3 x2){
	Camara::Vector3 resultado;
	resultado.x = x2.x - x1.x; resultado.y = x2.y - x1.y; resultado.z = x2.z - x1.z;
	return resultado;
}

Camara::Vector3 restarVector(Camara::Vector3 x1, Camara::Vector3 x2){
	Camara::Vector3 resultado;
	resultado.x = x1.x - x2.x; resultado.y = x1.y - x2.y; resultado.z = x1.z - x2.z;
	return resultado;
}

Camara::Vector3 sumarVector(Camara::Vector3 x1, Camara::Vector3 x2){
	Camara::Vector3 resultado;
	resultado.x = x2.x + x1.x; resultado.y = x2.y + x1.y; resultado.z = x2.z + x1.z;
	return resultado;
}


Camara::Camara(Vector3 pos, Vector3 ver, Vector3 arr) 
			{
	escala = 1;
	cam.pos = pos; cam.arr = arr; cam.ver = ver;
	ini.pos = pos; ini.arr = arr; cam.ver = ver;

	Vector3 vd = getVector(cam.pos,cam.ver);

	anguloY = -atan2f(vd.y,sqrt((vd.y*vd.y)+ (vd.z*vd.z)));
	anguloX = atan2f(vd.z*vd.z,vd.x*vd.x) + 1,57079633;

	std::cout << "aguloy" << anguloY << "agulox" << anguloX <<std::endl;
		modo = MODO_ORTOGONAL;
}

void Camara::dibujarPlano(){

}

void Camara::proyecion(double xIzq, double xDer, double yAba, double yArr, double zCer, double zLej){
	vol.xLeft = xIzq; vol.xRight = xDer;
	vol.yBot = yAba; vol.yTop = yArr;
	vol.zNear = zCer; vol.zFar = zLej;
}

void Camara::acercar(double es){
	escala += 0.25;
	reshape(panelW,panelH);
}

void Camara::alejar(double es){
	escala -= 0.25;
	reshape(panelW,panelH);
}

void Camara::rotarU(double an){
	std::cout << "aguloy" << anguloY << "agulox" << anguloX;
	anguloX +=an;
	double yaw = anguloX, pitch =anguloY;
	Vector3 view = getVector(cam.pos,cam.ver);
	float magnitude = modulo(view);

	/*if(cosf(yaw)*cosf(pitch)*magnitude > 0) {
		cam.arY =1;
	}else{
		cam.arY =-1;
	}*/

	float x2 = cam.ver.x +  cosf(yaw)*cosf(pitch)*magnitude;
	float y2 = cam.ver.y + sinf(pitch)*magnitude;
	float z2 = cam.ver.z + -sinf(yaw)*cosf(pitch)*magnitude;

	std::cout << "x " << cosf(yaw)*cosf(pitch)*magnitude <<  "y"<< sinf(pitch)*magnitude << "z" <<-sinf(yaw)*cosf(pitch)*magnitude <<std::endl;

	cam.pos.x = x2;
	cam.pos.y = y2;
	cam.pos.z = z2;
}

void Camara::reshape(int w, int h){
	panelW=w;panelH =h;
	vol.xRight = w/ 2.0 / escala; vol.xLeft = -vol.xRight; 
	vol.yTop = h/2.0 / escala;  vol.yBot = -vol.yTop; 
	camara = true;
}

void Camara::rotarV(double an){
	std::cout << "aguloy" << anguloY << "agulox" << anguloX;
	anguloY +=an;
	double yaw = anguloX, pitch =anguloY;
	Vector3 view = getVector(cam.pos,cam.ver);
	Vector3 derecha = prodVectorial(view,cam.arr);
	Vector3 arriba = prodVectorial(view,derecha);
	Vector3 arribaN = normalizar(arriba);
	cam.arr = arribaN;
	std::cout << "y" << arribaN.y << "x" << arribaN.x  << "z" << arribaN.z  <<  std::endl;
	float magnitude =  modulo(view);



	if(cosf(yaw)*cosf(pitch)*magnitude > 0) {
		cam.arr.y =1;
	}else{
		cam.arr.y =-1;
	}

	float x2 = cam.ver.x +  cosf(yaw)*cosf(pitch)*magnitude;
	float y2 = cam.ver.y + sinf(pitch)*magnitude;
	float z2 = cam.ver.z + -sinf(yaw)*cosf(pitch)*magnitude;

	std::cout << "x " << cosf(yaw)*cosf(pitch)*magnitude <<  "y"<< sinf(pitch)*magnitude << "z" <<-sinf(yaw)*cosf(pitch)*magnitude <<std::endl;

	cam.pos.x = x2;
	cam.pos.y = y2;
	cam.pos.z = z2;


}

void Camara::reset(){
	cam = ini;
	escala =1;
}

double* Camara::getPosicion(){
	double valor[3];
	valor[0] = cam.pos.x;
	valor[1] = cam.pos.y;
	valor[2] = cam.pos.z;
	return valor;
}

void Camara::moverDerecha(double escala){
	Vector3 view = getVector(cam.pos,cam.ver);
	Vector3 derecha = prodVectorial(view,cam.arr);
	Vector3 derechaN = normalizar(derecha);
	cam.pos = sumarVector(cam.pos,derechaN);
	cam.ver = sumarVector(cam.ver,derechaN);
}

void Camara::moverIzquierda(double escala){
	Vector3 view = getVector(cam.pos,cam.ver);
	Vector3 derecha = prodVectorial(view,cam.arr);
	Vector3 derechaN = normalizar(derecha);
	cam.pos = restarVector(cam.pos,derechaN);
	cam.ver = restarVector(cam.ver,derechaN);
}

void Camara::moverArriba(double escala){
	Vector3 view = getVector(cam.pos,cam.ver);
	Vector3 derecha = prodVectorial(view,cam.arr);
	Vector3 arriba = prodVectorial(view,derecha);
	Vector3 arribaN = normalizar(arriba);
	cam.pos = sumarVector(cam.pos,arribaN);
	cam.ver = sumarVector(cam.ver,arribaN);
}


void Camara::moverAbajo(double escala){
Vector3 view = getVector(cam.pos,cam.ver);
	Vector3 derecha = prodVectorial(view,cam.arr);
	Vector3 arriba = prodVectorial(view,derecha);
	Vector3 arribaN = normalizar(arriba);
	cam.pos = restarVector(cam.pos,arribaN);
	cam.ver = restarVector(cam.ver,arribaN);
}


void Camara::colocarCamara(){

	if(camara) { 

		glMatrixMode(GL_MODELVIEW);   // VIEW
		glLoadIdentity();
		gluLookAt(cam.pos.x,cam.pos.y,cam.pos.z, 
			cam.ver.x,cam.ver.y,cam.ver.z, 
			cam.arr.x,cam.arr.y,cam.arr.z);

		glMatrixMode(GL_PROJECTION);  // Pr
		if(modo == MODO_ORTOGONAL ){

			glLoadIdentity();
			glOrtho(vol.xLeft,vol.xRight, vol.yBot,vol.yTop, vol.zNear,vol.zFar);

		}else{
			glLoadIdentity();
			glFrustum(vol.xLeft,vol.xRight, vol.yBot,vol.yTop, 140,vol.zFar);
		}
		//	camara =false;
	}
}

Camara::~Camara(void)
{
}


