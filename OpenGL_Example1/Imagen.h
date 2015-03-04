#pragma once
class Imagen
{
public:
	Imagen(char* ps, int w, int h);
	~Imagen(void);

	char* pixels;
	int ancho;
	int alto;
};

Imagen* loadBMP(const char* filename);