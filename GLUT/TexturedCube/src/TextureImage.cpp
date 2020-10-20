#include "TextureImage.h"

TextureImage::TextureImage(const char* imageFilePath)
{
	#ifdef FREEIMAGE_LIB
		FreeImage_Initialise();
	#endif
	
	//image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	
	//check the file signature and deduce its format
	fif = FreeImage_GetFileType(imageFilePath, 0);
	if(fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(imageFilePath);
	//if still unkown, return failure
	if(fif == FIF_UNKNOWN)
		std::cerr<<"File Type for \""<<imageFilePath<<"\" is UNKNOWN"<<std::endl;
	
	//check that the plugin has reading capabilities and load the file
	if(FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, imageFilePath);
	//if the image failed to load, return failure
	if(!dib)
		std::cerr<<"Failed to load \""<<imageFilePath<<"\""<<std::endl;
	
	//retrieve the image data
	bits = FreeImage_GetBits(dib);
	//get the image width and height
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);
	
	//if this somehow one of these failed (they shouldn't), return failure
	if((bits == 0) || (width == 0) || (height == 0))
		std::cerr<<"Something is wrong with \""<<imageFilePath<<"\""<<std::endl;
}

unsigned int TextureImage::getWidth()
{
	return width;
}

unsigned int TextureImage::getHeight()
{
	return height;
}

BYTE* TextureImage::getBits()
{
	return bits;
}

TextureImage::~TextureImage()
{
	FreeImage_Unload(dib);
	#ifdef FREEIMAGE_LIB
		FreeImage_DeInitialise();
	#endif
}