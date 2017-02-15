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
#define R 4


struct cells {
} cells[N][N];

struct particles {

	float x_old, y_old, v_x_old, v_y_old, m, F_x, F_y;

}particles[Particles];


void reshape(int w, int h) {
		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, w, 0, h);
        glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
}		

float t = 0;

void display(){	


	int i, j;
	float dt = 0.001;


	for(i = 0; i< Particles-1; i++){
		for(j = i+1; j< Particles; j++){

			float F;
			float delt_x, delt_y, L;
			delt_x = abs(particles[i].x_old-particles[j].x_old);
			delt_y = abs(particles[i].y_old-particles[j].y_old);
			L = sqrt(delt_x*delt_x+delt_y*delt_y);
			if(L<=R){

				if (L != 0){ F = 1000/(pow(L, 2))-2000/(pow(L, 3));}
				particles[i].F_x += F*delt_x/L;
				particles[i].F_y += F*delt_y/L;
				particles[j].F_x += -F*delt_x/L;
				particles[j].F_y += -F*delt_y/L;
			}
		}
	}
	for(i = 0; i < Particles; i++){
			//if(sqrt(pow(abs(particles[i].x_old-particles[j].x_old), 2)+pow(abs(particles[i].y_old-particles[j].y_old), 2)) <= R){
			float a_x1, a_y1;
			//if(particles[i].F_y != 0 && particles[i].F_y != 0){
					
				
				a_x1 = particles[i].F_x/particles[i].m;
				particles[i].v_x_old = particles[i].v_x_old + a_x1*dt;
				particles[i].x_old = particles[i].x_old + particles[i].v_x_old*dt + a_x1*dt*dt/2;

				a_y1 = particles[i].F_y/particles[i].m;
				particles[i].v_y_old = particles[i].v_y_old + a_y1*dt;
				particles[i].y_old = particles[i].y_old + particles[i].v_y_old*dt + a_y1*dt*dt/2;
				particles[i].F_y = 0;
				particles[i].F_x = 0; 
			//}
				//printf("%f\n", a_x1);
			//}
		
	}					
	t=t+dt;
	glClear(GL_COLOR_BUFFER_BIT);

	for(i = 0; i < Particles; i++){

			//if(t>=0.01){

				glBegin(GL_POINTS);
				glColor3d(1,1,1);
				glVertex3d(particles[i].x_old,particles[i].y_old , 0);
				glEnd();
				t = 0;
			//}
	}
	glutSwapBuffers();

		
	

}

void initialise(){
	int i=0, j=0;
	while(i<100){
		j = 0;
		while(j<100){
			particles[i*100+j].x_old = 3*j+300;
			particles[i*100+j].y_old = 300+i*3;
			particles[i*100+j].v_x_old = 0;
			particles[i*100+j].v_y_old = 0;
			particles[i*100+j].F_y = 0;
			particles[i*100+j].F_x = 0;
			particles[i*100+j].m = 1;
			j++;
		}
		i++;
	}
	i = 0;
	j = 0;
	while(i<3){
		j = 0;
		while(j<3){
			particles[i*3+j].x_old = 3*j+450;
			particles[i*3+j].y_old = 200+i*3;
			particles[i*3+j].v_x_old = 0;
			particles[i*3+j].v_y_old = 800;
			particles[i*3+j].F_y = 0;
			particles[i*3+j].F_x = 0;
			particles[i*3+j].m = 0.01;
			j++;
		}
		i++;
	}
	/*
	particles[0].x_old = 200;
	particles[1].x_old = 350;
	particles[0].m = 0.001;
	particles[1].m = 0.001;
	particles[0].v_x_old = 20;
	particles[1].v_x_old = -20;
	particles[0].y_old = 250;
	particles[1].y_old = 350;
	particles[0].v_y_old = -20;
	particles[1].v_y_old = 0;
	particles[0].F_x = 0;
	particles[1].F_y = 0;
	particles[1].F_x = 0;
	particles[0].F_y = 0;
	*/

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