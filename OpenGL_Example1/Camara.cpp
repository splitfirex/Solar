#include "Camara.h"
#include "math.h"
#include <Windows.h>
#include <iostream>

#define PI 3.14159265

int panelH, panelW;


float toRadians(float degrees)
{
	return degrees * (PI / 180.0);
}

void prod_vec (float x1, float y1, float z1, float x2, float y2, float z2, float *x3, float *y3, float *z3)
{
	*x3 = y1*z2-z1*y2;
	*y3 = x1*z2-z1*x2;
	*z3 = x1*y2-y1*x2;
}



double prod_esc (float x1, float y1, float z1, float x2, float y2, float z2)
{
	return  x1*x2 + y1*y2 +z1*z2;
}

double modulo (float x1, float y1, float z1)
{
	return  sqrt(x1*x1 + y1*y1 +z1*z1);

}
double anguloEntreVectores(float x1, float y1, float z1, float x2, float y2, float z2){
	return prod_esc(x1,y1,z1,x2,y2,z2)/(modulo(x1,y1,z1)*modulo(x2,y2,z2));
}


Camara::Camara(double posx, double posy, double posz,  
			   double verx, double very, double verz, 
			   double arx,  double ary,  double arz)
{
	escala = 1;
	cam.arX =arx; cam.arY =ary; cam.arZ =arz;
	cam.veX =verx; cam.veY =very; cam.veZ =verz;
	cam.psX = posx; cam.psY = posy; cam.psZ = posz; 

	ini.arX =arx; ini.arY =ary; ini.arZ =arz;
	ini.veX =verx; ini.veY =very; ini.veZ =verz;
	ini.psX = posx; ini.psY = posy; ini.psZ = posz; 

	anguloY = -atan2f(very-posy,sqrt((very-posy)*(very-posy)+ (verz-posz)*(verz-posz)));
	anguloX = atan2f((verz-posz)*(verz-posz),(verx-posx)*(verx-posx)) - 0,57079633;


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
	float viewX = cam.veX - cam.psX;
	float viewY = cam.veY - cam.psY;
	float viewZ = cam.veZ - cam.psZ;
	float magnitude = sqrt( (viewX * viewX) + (viewY * viewY) + (viewZ * viewZ) );

	/*if(cosf(yaw)*cosf(pitch)*magnitude > 0) {
		cam.arY =1;
	}else{
		cam.arY =-1;
	}*/

	float x2 = cam.veX +  cosf(yaw)*cosf(pitch)*magnitude;
	float y2 = cam.veY + sinf(pitch)*magnitude;
	float z2 = cam.veZ + -sinf(yaw)*cosf(pitch)*magnitude;

	std::cout << "x " << cosf(yaw)*cosf(pitch)*magnitude <<  "y"<< sinf(pitch)*magnitude << "z" <<-sinf(yaw)*cosf(pitch)*magnitude <<std::endl;

	cam.psX = x2;
	cam.psY = y2;
	cam.psZ = z2;
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
	float viewX = cam.veX - cam.psX;
	float viewY = cam.veY - cam.psY;
	float viewZ = cam.veZ - cam.psZ;
	float magnitude = sqrt( (viewX * viewX) + (viewY * viewY) + (viewZ * viewZ) );

	if(cosf(yaw)*cosf(pitch)*magnitude > 0) {
		cam.arY =1;
	}else{
		cam.arY =-1;
	}

	float x2 = cam.veX +  cosf(yaw)*cosf(pitch)*magnitude;
	float y2 = cam.veY + sinf(pitch)*magnitude;
	float z2 = cam.veZ + -sinf(yaw)*cosf(pitch)*magnitude;

	std::cout << "x " << cosf(yaw)*cosf(pitch)*magnitude <<  "y"<< sinf(pitch)*magnitude << "z" <<-sinf(yaw)*cosf(pitch)*magnitude <<std::endl;

	cam.psX = x2;
	cam.psY = y2;
	cam.psZ = z2;


}

void Camara::reset(){
	cam.psX = ini.psX;cam.psY = ini.psY;cam.psZ = ini.psZ;
	cam.veX = ini.veX;cam.veY = ini.veY; cam.veZ = ini.veZ;
	cam.arX = ini.arX;cam.arY = ini.arY; cam.arZ = ini.arZ;
	escala =1;
}

double* Camara::getPosicion(){
	double valor[3];
	valor[0] = cam.psX;
	valor[1] = cam.psY;
	valor[2] = cam.psZ;
	return valor;
}

void Camara::moverDerecha(double escala){
	float viewX = cam.veX - cam.psX;
	float viewY = cam.veY - cam.psY;
	float viewZ = cam.veZ - cam.psZ;

	float x,y,z;
	prod_vec(viewX,viewY,viewZ,cam.arX,cam.arY, cam.arZ,&x,&y,&z);

	float magnitude = sqrt( (x * x) + (y * y) + (z * z) );

	x /= magnitude;
	y /= magnitude;
	z /= magnitude;

	cam.veX += x;
	cam.veY += y;
	cam.veZ += z;

	cam.psX += x;
	cam.psY += y;
	cam.psZ += z;
	std::cout << "pos " << cam.psX << " " << cam.psY << " " << cam.psZ << std::endl;
}

void Camara::moverIzquierda(double escala){
	float viewX = cam.veX - cam.psX;
	float viewY = cam.veY - cam.psY;
	float viewZ = cam.veZ - cam.psZ;

	float x,y,z;
	prod_vec(viewX,viewY,viewZ,cam.arX,cam.arY, cam.arZ,&x,&y,&z);
	float magnitude = sqrt( (x * x) + (y * y) + (z * z) );

	x /= magnitude;
	y /= magnitude;
	z /= magnitude;

	cam.veX -= x;
	cam.veY -= y;
	cam.veZ -= z;

	cam.psX -= x;
	cam.psY -= y;
	cam.psZ -= z;

	std::cout << "pos " << cam.psX << " " << cam.psY << " " << cam.psZ << std::endl;
}

void Camara::moverArriba(double escala){

	float viewX = cam.veX - cam.psX;
	float viewY = cam.veY - cam.psY;
	float viewZ = cam.veZ - cam.psZ;

	float x,y,z;
	float x2,y2,z2;
	prod_vec(viewX,viewY,viewZ,cam.arX,cam.arY, cam.arZ,&x,&y,&z);
	prod_vec(x,y,z,viewX,viewY,viewZ,&x2,&y2,&z2);

	std::cout << "vector " << x << " " << y << " " << z << std::endl;

	float magnitude = sqrt( (x2 * x2) + (y2 * y2) + (z2 * z2) );

	x2 /= magnitude;
	y2 /= magnitude;
	z2 /= magnitude;

	cam.veX -= x2;
	cam.veY -= y2;
	cam.veZ -= z2;

	cam.psX -= x2;
	cam.psY -= y2;
	cam.psZ -= z2;
	std::cout << "pos " << cam.psX << " " << cam.psY << " " << cam.psZ << std::endl;


}


void Camara::moverAbajo(double escala){

	float viewX = cam.veX - cam.psX;
	float viewY = cam.veY - cam.psY;
	float viewZ = cam.veZ - cam.psZ;

	float x,y,z;
	float x2,y2,z2;

	prod_vec(viewX,viewY,viewZ,cam.arX,cam.arY, cam.arZ,&x,&y,&z);
	prod_vec(x,y,z,viewX,viewY,viewZ,&x2,&y2,&z2);


	std::cout << "vector " << x << " " << y << " " << z << std::endl;

	float magnitude = sqrt( (x2 * x2) + (y2 * y2) + (z2 * z2) );

	x2 /= magnitude;
	y2 /= magnitude;
	z2 /= magnitude;

	cam.veX += x2;
	cam.veY += y2;
	cam.veZ += z2;

	cam.psX += x2;
	cam.psY += y2;
	cam.psZ += z2;
	std::cout << "pos " << cam.psX << " " << cam.psY << " " << cam.psZ << std::endl;


}


void Camara::colocarCamara(){

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
			glFrustum(vol.xLeft,vol.xRight, vol.yBot,vol.yTop, 140,vol.zFar);
		}
		//	camara =false;
	}
}

Camara::~Camara(void)
{
}


