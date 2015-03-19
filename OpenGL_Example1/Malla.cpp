#include "Malla.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <vector>
#include <list>
#include <iterator>

enum modos {v, n, c, i, datos};
int contVertice= 0, contIndices= 0, contNormales= 0, contColores = 0, contDatos;



Malla::Malla(void)
{
}


Malla::~Malla(void)
{
}


void Malla::cargarMalla(char* valor ){
	std::ifstream infile(valor);
	std::string line;


	modos modo;


	while (!infile.eof())
	{
		getline(infile, line);
		std::istringstream buf(line);
		std::istream_iterator<std::string> beg(buf), end;
		std::vector<std::string> tokens(beg, end); // done!

		float temps[3];
		int contador = 0;
		for(auto& s: tokens){
			if(s == "//"){ std::cout << std::endl ; break; contador = 0; } 
			if(s == "v"){ modo = v;  contador = 0; break;  }
			if(s == "n"){ modo = n; contador = 0; break; }
			if(s == "c"){ modo = c; contador = 0; break; }
			if(s == "d"){ modo = datos; contador = 0; break; }
			if(s == "i"){ modo = i; contador = 0; break; }

			switch (modo)
			{
			case v:
				temps[contador++] = atof(s.c_str());
				if(contador == 3){
					contador = 0;
					*(vertices[contVertice]+0) =temps[0];*(vertices[contVertice]+1) =temps[1];*(vertices[contVertice]+2) =temps[2];
					contVertice++;
				}

				break;
			case n:
				temps[contador++] = atof(s.c_str());
				if(contador == 3){
					contador = 0;
					*(normales[contNormales]+0) =temps[0];*(normales[contNormales]+1) =temps[1];*(normales[contNormales]+2) =temps[2];
					contNormales++;
				}
				
				break;
			case c:
				temps[contador++] = atof(s.c_str());
				if(contador == 3){
					contador = 0;
					*(colores[contColores]+0) =temps[0];*(colores[contColores]+1) =temps[1];*(colores[contColores]+2) =temps[2];
					contColores++;
				}
				
				break;
			case i:
				indices[contIndices++] = atoi(s.c_str());
				numI++;
				break;
			case datos:
				std::cout << '"' << atoi(s.c_str()) << '"' ;
				if(contDatos == 0 ) vertices = new Vec3C[atoi(s.c_str())]();
				if(contDatos == 1) normales = new Vec3C[atoi(s.c_str())]();
				if(contDatos == 2 ) colores = new Vec3C[atoi(s.c_str())]();
				if(contDatos == 3 ) indices = new GLuint[atoi(s.c_str())]();
				contDatos++;
				break;
			default:
				break;
			}
		}
	}
}


void Malla::initGL(){
	glEnableClientState(GL_NORMAL_ARRAY); (GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY); (GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normales);
	glColorPointer(3, GL_FLOAT, 0, colores); 
	glVertexPointer(3, GL_FLOAT, 0, vertices);
}

void Malla::liberarGL(){
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void Malla::dibujar(){
	glDrawElements(GL_TRIANGLES, numI, GL_UNSIGNED_INT, indices);
}