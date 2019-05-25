#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<math.h>
#include<cmath>
#include<iostream>
#include<string.h>

using namespace std;
int NUM_DISKS; 
void restart();
void display();
void mouse(int btn,int mode,int x,int y);
void createGLUTMenus2();
void initialize();
void printfptext(char, int, int, int, int);

void processMenuSolveCompletely(int);
void processMenuRestart(int);

void lighting()
{
	GLfloat shininess[] = {50};
	GLfloat white[] = {0.6,0.6,0.6,1};
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_position[] = {100, 60,  10,  0.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glEnable(GL_LIGHT0);
}


void init()
{
    glClearColor(0.4117,0.4117,0.4117,0); //light gray color 
	glColor3f(1,0,0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-80,350,-10,100,-100,100);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	lighting();

    //glutReshapeWindow(1360,760);

 


}


void reshape(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100,100,-100,100);
    glMatrixMode(GL_MODELVIEW);
}



void printtext(char s[], int x, int y)
{
    int l = (int)strlen(s);
    glRasterPos2i(x,y);
    for(int i = 0;i<l;i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
    }
}

void draw_poly(float a, float b, float c, float d)
{
    glBegin(GL_POLYGON);
    glVertex2f(a,b);
    glVertex2f(a,d);
    glVertex2f(c,d);
    glVertex2f(c,b);
    glEnd();
}


void border()
{
    
    glColor3f(1,1,1);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-90, 90);
        glVertex2f(-90, -90);
        glVertex2f(90, -90);
        glVertex2f(90, 90);
    glEnd();

    glColor3f(1,1,1);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-92, 92);
        glVertex2f(-92, -92);
        glVertex2f(92, -92);
        glVertex2f(92, 92);
    glEnd();

    draw_poly(-65, 20, -30, 5);
    glColor3f(1,0,0);
    printtext((char *)" START SIMULATION   ", -62, 10);
    glColor3f(1,1,1);

    draw_poly(20, 20, 50, 5);
    glColor3f(1,0,0);
    printtext((char *)" EXIT SIMULATION   ", 22, 10);
    glColor3f(1,1,1);

    glutSwapBuffers();
}

int x,y;bool disp = true,solved=false;

void indmouse(int button, int state, int mousex, int mousey)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        x = (float(mousex) - 500)/5;
        y = (700 - float(mousey) - 350)/3.5;
    }
    
    if(disp == true)
    {   
        if(x >= -40 && x <= 40 && y >= 5 && y <= 20)
        {
            //cout<<"run please";
			disp=false;
            
            restart();
			init();
			glutDisplayFunc(display);
			createGLUTMenus2();
			glutMouseFunc(mouse);
        }
        else if(x >= 50 && x <= 80 && y >= 5 && y <= 20)
        {
            exit(0);
        }
    }

   if(disp==false)
    {
        //if(x >= -70 && x <= -50 &&  y >= 70 && y <= 50)
        if(x >= -90 && x <= -70 && y >= 65 && y <= 100)
        {
            cout<<"start\n";
            processMenuSolveCompletely(1);
        }
        else if(x >= -90 && x <= -70 && y >= 20 && y <= 40)
        {
            cout<<"RANDOM\n";
            glClearColor((rand()%100)/100.0,(rand()%100)/100.0,(rand()%100)/100.0,0);
        }
        else if(x >= -90 && x <= -70 &&  y >= -30 && y <= 0)
        {
            cout<<"RESTART\n";
            processMenuRestart(0);
        }
        else if(x >= -90 && x <= -70 && y >= -100 && y <= -40)
        {
            cout<<"EXIT\n";
            exit(0);
        }
        
    }
    
    glutPostRedisplay();
}
