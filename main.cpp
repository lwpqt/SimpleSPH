// for linux
/* 
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>	
#include <time.h>
*/

// for OS X
#include <GLUT/glut.h> 
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <cstdlib>

#define HIGH 700.0
#define WIDTH 700.0
#define LENGTH 1.0
#define N 700
#define Particles 10000
#define T 253.0
#define R 8.31445
#define Molar_mass 29.0
#define Pression 101325.0
#define Pi 3.14159265


struct cells {
} cells[N][N];

struct particles {
} particles[Particles];

void reshape(int w, int h) {
		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, w, 0, h);
        glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
}

void display(){	
		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_POINTS);
		glColor3d(1,0,1);
		glVertex3d(350, 350, 0); 
		glEnd();
		glutSwapBuffers();
}

void initialise(){

}

int main (int argc, char * argv[]){
	srand(time(NULL));
	initialise();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowSize(WIDTH, HIGH);
	glutCreateWindow("Particles simaulation");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutMainLoop();
	return 0;
}