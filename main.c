#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <stdio.h>

#include "init_stuff.h"

#define NOPE(a) (exit(a))

#define ANGLE_X 0x0
#define ANGLE_Y 0x1
#define ANGLE_Z 0x2

#define PI 3.141592653589793f

unsigned int prog;
unsigned int step = 10;

typedef struct {
	float x;
	float y;
	float z;
} angle_t;

typedef struct {
	float x;
	float y;
} pos_t;

angle_t rotation = {0};
pos_t pos = {0};
float scale = 1;


void init(void)
{
	prog = init_program(4, "vshader.glsl", GL_VERTEX_SHADER , "fshader.glsl", GL_FRAGMENT_SHADER);
	if (prog < 0) {
		fprintf(stderr,"Error: could not initialize program, bailing...\n");
		NOPE(1);
	}

	glUseProgram(prog);
	glEnable(GL_DEPTH_TEST);

//	pos.x = 0.5f;
//	pos.y = 0.5f;
}


// TODO: Write this
void on_key(unsigned char key, int x, int y)
{
	switch(key) {
		
		// Rotation
		case 'h': rotation.x += step; break;
		case 'l': rotation.x -= step; break;
		case 'j': rotation.y += step; break;
		case 'k': rotation.y -= step; break;
		case 'u': rotation.z += step; break;
		case 'm': rotation.z -= step; break;
	
		// Translation
		case 'w': pos.y += 0.1; break;
		case 's': pos.y -= 0.1; break;
		case 'a': pos.x -= 0.1; break;
		case 'd': pos.x += 0.1; break;

		// Scale
		case 'q': scale -= 0.1; break;
		case 'e': scale += 0.1; break;

	}
	glutPostRedisplay();
}

void show_stuff(void)
{
	int vaoID, vertBuf, elemBuf;
	int rot_pos, pos_pos, sca_pos;
	// DO OBJECT STUFF HERE
	/*GLfloat vertices[3*8] = {
		-0.5f,-0.5f,0.5f,
		-0.5f, 0.5f,0.5f,
		 0.5f, 0.5f,0.5f,
		 0.5f,-0.5f,0.5f,
		
		-0.5f,-0.5f,-0.5f,
		-0.5f, 0.5f,-0.5f,
		 0.5f, 0.5f,-0.5f,
		 0.5f,-0.5f,-0.5f
	};*/

	/*
	GLuint indices[36] = {
		// front
		0, 1, 2,
		0, 3, 2,
		// top
		1, 5, 6,
		1, 2, 6,
		// back
		7, 6, 5,
		7, 4, 5,
		// bottom
		0, 4, 7,
		0, 3, 7,
		// left
		0, 1, 5,
		0, 4, 5,
		// right
		3, 2, 6,
		3, 7, 6,
	};*/

	GLfloat vertices[3*5] = {
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f,-1.0f, 1.0f,
		 0.0f, 1.0f, 0.0f
	};

	GLuint indices[3*6] = {
		// Base
		0,1,2,
		0,3,2,		

		// Pointy bit
		0,4,1,
		1,4,2,
		2,4,3,
		3,4,0
	};


	rot_pos = glGetUniformLocation(prog,"rotate");
	pos_pos = glGetUniformLocation(prog,"pos");
	sca_pos = glGetUniformLocation(prog,"scale");

	if (-1 == rot_pos)
		printf("Warning: rotate not found in shader\n");
	if (-1 == pos_pos)
		printf("Warning: position not found in shader\n");
	if (-1 == sca_pos)
		printf("Warning: scale not found in shader\n");


	glUniform3fv(rot_pos,1,&rotation);
	glUniform2fv(pos_pos,1,&pos);
	glUniform1fv(sca_pos,1,&scale);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
	
	glGenBuffers(1, &vertBuf);
	glGenBuffers(1, &elemBuf);
	
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, NULL);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elemBuf);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
//	glDrawArrays(GL_TRIANGLES, 0, 3*8);

	glFlush();

}


int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutCreateWindow("Lab 2");

	glutInitContextVersion(4,3);
	glutInitContextProfile(GLUT_CORE_PROFILE | GLUT_COMPATIBILITY_PROFILE);

	init();
	
	glutDisplayFunc(show_stuff);
	glutKeyboardFunc(on_key);
	glutMainLoop();

	return 0;
}

