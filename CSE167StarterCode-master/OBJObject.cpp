#include "OBJObject.h"
#include <iostream>


OBJObject::OBJObject(const char *filepath) 
{
	toWorld = glm::mat4(1.0f);
	parse(filepath);
	tranX = 0;
	tranY = 0;
	tranZ = 0;
	scale = 1;
	orbit = 1;
}

void OBJObject::parse(const char *filepath) 
{
	FILE* fp;     // file pointer
	float x, y, z;  // vertex coordinates
	float r, g, b;  // vertex color
	int c1, c2;    // characters read from file

	fp = fopen(filepath, "rb");  // make the file name configurable so you can load other files
	if (fp == NULL) { std::cerr << "error loading file" << std::endl; exit(-1); }  // just in case the file can't be found or is corrupt


	while (1) {
		c1 = fgetc(fp);
		if (c1 == EOF) {
			break;
		}
		c2 = fgetc(fp);
		//vertices
		if ((c1 == 'v') && (c2 == ' '))
		{
			fscanf(fp, "%f %f %f %f %f %f", &x, &y, &z, &r, &g, &b);
			glm::vec3 v2Add = glm::vec3(x, y, z); //create vector out of points
			vertices.push_back(v2Add); //push vector onto vertices
		}
		//vertex normals
		else if ((c1 == 'v') && (c2 == 'n'))
		{
			fscanf(fp, "%f %f %f", &x, &y, &z);
			glm::vec3 vn2Add = glm::vec3(x, y, z);
			normals.push_back(vn2Add);
		}
	}

	fclose(fp);
}

void OBJObject::draw() 
{
	glMatrixMode(GL_MODELVIEW);

	// Push a save state onto the matrix stack, and multiply in the toWorld matrix
	glPushMatrix();
	glMultMatrixf(&(toWorld[0][0]));

	glBegin(GL_POINTS);
	// Loop through all the vertices of this OBJ Object and render them
	for (unsigned int i = 0; i < vertices.size(); ++i) 
	{
		//set color
		glm::vec3 color = glm::normalize(normals[i]);
		glColor3f((color.x + 1) / 2, (color.y + 1) / 2, (color.z + 1) / 2);

		//set points
		glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
	}
	glEnd();

	// Pop the save state off the matrix stack
	// This will undo the multiply we did earlier
	glPopMatrix();
}
void OBJObject::update()
{
	spin(1.0f);
}


void OBJObject::spin(float deg)
{

	glm::mat4 currM = this->toWorld;
	this->angle += deg;
	if (this->angle > 360.0f || this->angle < -360.0f) this->angle = 0.0f;
	// This creates the matrix to rotate the cube
	this->toWorld = glm::rotate(glm::mat4(1.0f), this->angle / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	this->toWorld = glm::rotate(glm::mat4(1.0f), this->orbit /360.0f * glm::pi<float>(), glm::vec3(0, 0, 1)) *this->toWorld;

	this->toWorld = glm::translate(glm::mat4(1.0f), glm::vec3(tranX, tranY, tranZ)) * this->toWorld;
	this->toWorld = glm::scale(glm::mat4(1.0f), glm::vec3(scale, scale, scale)) * this -> toWorld;


}

void OBJObject::rasterize() {
	//loop over all points


}
std::vector<glm::vec3> OBJObject::getVert() {
	return this->vertices;
}
std::vector<glm::vec3> OBJObject::getNorm() {
	return this->normals;
}
