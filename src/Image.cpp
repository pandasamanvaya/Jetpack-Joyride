#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h> 
#include <GLFW/glfw3.h>

GLuint load_image(const char *filename)
{
	// Data read from the header of the BMP file
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     // Position in the file where the actual data begins
	unsigned int width, height;
	unsigned int imageSize;   // = width*height*3
	// Actual RGB data
	unsigned char * data;

	FILE * file = fopen(filename, "rb");
	if (!file){printf("Image could not be opened\n"); return 0;}

	if ( fread(header, 1, 54, file)!=54 ){ // If not 54 bytes read : problem
	    printf("Not a correct BMP file\n");
	    return false;
	}

	if ( header[0]!='B' || header[1]!='M' ){
    	printf("Not a correct BMP file\n");
    	return 0;
	}

	dataPos    = *(int*)&(header[0x0A]);
	imageSize  = *(int*)&(header[0x22]);
	width      = *(int*)&(header[0x12]);
	height     = *(int*)&(header[0x16]);

	if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos==0)      dataPos=54; // The BMP header is done that way

	data = new unsigned char [imageSize];

	// Read the actual data from the file into the buffer
	fread(data,1,imageSize,file);

	//Everything is in memory now, the file can be closed
	fclose(file);
	//printf("%d %d %d", imageSize, width, height);
	GLuint textureID;
	glGenTextures(1, &textureID);
	
	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	// OpenGL has now copied the data. Free our own version
	delete [] data;

	// Poor filtering, or ...
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 

	// ... nice trilinear filtering ...
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// ... which requires mipmaps. Generate them automatically.
	glGenerateMipmap(GL_TEXTURE_2D);

	// Return the ID of the texture we just created
	return textureID; 
}