#ifndef TEXTURE_IMAGE_H
#define TEXTURE_IMAGE_H

#include <iostream>
#include "FreeImage.h"

class TextureImage
{
public:
	TextureImage(const char* imageFilePath);
	~TextureImage();
	unsigned int getWidth();
	unsigned int getHeight();
	BYTE* getBits();
	
private:
	unsigned int width, height;
	//pointer to the image, once loaded
	FIBITMAP *dib;
	//pointer to the image data
	BYTE* bits;
};

#endif // TEXTURE_IMAGE_H