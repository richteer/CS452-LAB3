#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <stdio.h>

#include "init_stuff.h"

#define NOPE(a) (exit(a))

unsigned int prog;

void init(void)
{
	prog = init_program(4, "vshader.glsl", GL_VERTEX_SHADER , "fshader.glsl", GL_FRAGMENT_SHADER);
	if (prog < 0) {
		fprintf(stderr,"Error: could not initialize program, bailing...\n");
		NOPE(1);
	}

	glUseProgram(prog);
}


// TODO: Finish this
void on_key(unsigned char key, int x, int y)
{
//	printf("c: %c, x: %d, y: %d\n",key,x,y);



}

void show_stuff(void)
{
	int vaoID, vboID;
	glClear(GL_COLOR_BUFFER_BIT);

	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
	
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	

	// DO OBJECT STUFF HERE
	GLfloat vertices[3*6] = {
		-0.25f,-0.5f,0.0f,
		-0.5f,0.0f,0.0f,
		-0.25f,0.5f,0.0f,
		0.25,0.5f,0.0f,
		0.5f,0.0f,0.0f,
		0.25,-0.5f,0.0f};


	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 0, NULL);

	glDrawArrays(GL_POLYGON, 0, 3*6 );


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

