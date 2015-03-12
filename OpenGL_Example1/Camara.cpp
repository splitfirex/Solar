#include "Camara.h"
#include "math.h"


double magnitudX, magnitudY, magnitudZ;

Camara::Camara(double posx, double posy, double posz,  
			   double verx, double very, double verz, 
			   double arx,  double ary,  double arz)
{
	cam.arX =arx; cam.arY =ary; cam.arZ =arz;
	cam.veX =verx; cam.veY =very; cam.veZ =verz;
	cam.psX = posx; cam.psY = posy; cam.psZ = posz; 


	float viewX = cam.veX - cam.psX;
	float viewY = cam.veY - cam.psY;
    float viewZ = cam.veZ - cam.psZ;

	float x = ((viewY * cam.arZ) - (viewZ * cam.arY));
    float y = ((viewZ * cam.arX) - (viewX * cam.arZ));
    float z = ((viewX * cam.arY) - (viewY * cam.arX));

    float magnitude = sqrt( (x * x) + (y * y) + (z * z) );

    x /= magnitude;
    y /= magnitude;
    z /= magnitude;

	magnitudX = x;
	magnitudY = y;
	magnitudZ = z;

	modo = MODO_ORTOGONAL;
}

void Camara::dibujarPlano(){

}

void Camara::proyecionOrto(double xIzq, double xDer, double yAba, double yArr, double zCer, double zLej){
	vol.xLeft = xIzq; vol.xRight = xDer;
	vol.yBot = yAba; vol.yTop = yArr;
	vol.zNear = zCer; vol.zFar = zLej;
}

void Camara::acercar(double escala){
	vol.xLeft++;
	vol.xRight--;
	vol.yBot++;
	vol.yTop--;
	vol.zNear++;
}

void Camara::alejar(double escala){
	vol.xLeft--;
	vol.xRight++;
	vol.yBot--;
	vol.yTop++;
	vol.zNear--;
}

void Camara::rotarU(double angulo){

}

void Camara::rotarV(double angulo){

}

void Camara::reset(){

}

double* Camara::getPosicion(){
	double valor[3];
	valor[0] = cam.psX;
	valor[1] = cam.psY;
	valor[2] = cam.psZ;
	return valor;
}

void Camara::moverDerecha(double escala){
	cam.psX += magnitudX;
	cam.psY += magnitudY;
	cam.psZ += magnitudZ;
}

void Camara::moverIzquierda(double escala){
	cam.psX -= magnitudX;
	cam.psY -= magnitudY;
	cam.psZ -= magnitudZ;
}

void Camara::moverArriba(double escala){

}


void Camara::moverAbajo(double escala){

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
				gluPerspective(per.fovy,per.aspect,per.zNear,per.zFar);

			}
		//	camara =false;
		}
}

Camara::~Camara(void)
{
}
