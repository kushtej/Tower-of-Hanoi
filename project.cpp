#include"index.cpp"
#include"fp.cpp"
//#include<windows.h>
#include<GL/glut.h>
#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

using namespace std;
#define LIGHT_ON 0
#define LIGHT_OFF 1
int pos[16] = {10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85};
int peg[3] = {50,150,250};
int moves[10000][3];
int max_moves;
int POLES[3][10];
int top[3]={-1,-1,-1};
bool front = true;

bool fpdone=false;

void reshapefront(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100,100,-100,100);
    glMatrixMode(GL_MODELVIEW);
}
int cnt,counter=1,speed=5;
float ycoordinate;
int lightflag=1,animationFlag=1,randomColorFlag=0;

void push(int p,int disk)
{
	POLES[p][++top[p]] = disk;
}


void pop(int p)
{
	top[p]--;
}

//main logic
void tower(int n,int src,int temp,int dst)
{
	if(n>0)
	{
		tower(n-1,src,dst,temp);
		moves[cnt][0] = n;
		moves[cnt][1] = src;
		moves[cnt][2] = dst;
		cnt++;
		tower(n-1,temp,src,dst);
	}
}

void drawPegs()
{
	int i;
	//glColor3f(0.5,0.0,0.1);
	for(i=0;i<3;i++)
	{
		glPushMatrix();
			glTranslatef(peg[i],5,0);
			glRotatef(-100,1,0,0);
			glutSolidCone(2,70,20,20);
			
			glColor3f(1,0,0);
			glRectd(-60,-40,50,30);
		glPopMatrix();
	}
}

char str[5];
void drawText()
{
	
	// glColor3f(1,1,1);
    // glBegin(GL_LINE_LOOP);
    //     glVertex2f(-90, 90);
    //     glVertex2f(-90, -90);
    //     glVertex2f(90, -90);
    //     glVertex2f(90, 90);
    // glEnd();

    // glColor3f(1,1,1);
    // glBegin(GL_LINE_LOOP);
    //     glVertex2f(-92, 92);
    //     glVertex2f(-92, -92);
    //     glVertex2f(92, -92);
    //     glVertex2f(92, 92);
    // glEnd();
	
	glColor3f(1,1,1);
	draw_poly(-70, 85, -15, 76);
	draw_poly(-70, 65, -15, 56);
	draw_poly(-70, 45, -15, 36);
	draw_poly(-70, 25, -15, 16);

	glColor3f(1,0,0);
    printtext((char *)"     START", -67, 80);
	printtext((char *)" 	RANDOM", -67, 60);
	printtext((char *)"    RESTART", -67, 40);
	printtext((char *)"     EXIT", -67, 20);
	
	
	
	
	
	//temp
	glColor3f(0,1,0);//for color green
    printtext((char *)"No of Rings : ", 270, 90);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, NUM_DISKS + 48);
	
	glColor3f(0,1,0);//color green 

	
	sprintf(str, "%d", counter);
	printtext((char *)"Number of Moves : ",200,0);
	printtext(str,280,0); //Printing count onto display
	
	
	printtext((char *)"Move Disk : ",-50,0);
	char str1[10];
	sprintf(str1, "%d", moves[counter][0]);
	printtext((char *)str1,-10,0);
	
	printtext((char *)"from",-5,0);
	char src[2];
	if(moves[counter][1]==0)strcpy(src,"A");
	else if(moves[counter][1]==1)strcpy(src,"B");
	else strcpy(src,"C");

	printtext((char *)src,12,0);

	printtext((char *)"  to ",15,0);
	char dst[2];
	if(moves[counter][2]==0)strcpy(dst,"A");
	else if(moves[counter][2]==1)strcpy(dst,"B");
	else strcpy(dst,"C");

	printtext((char *)dst,25,0);

	glColor3f(1,0,0);
	glRasterPos3f(peg[0],80,0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'A');
	glRasterPos3f(peg[1],80,0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'B');
	glRasterPos3f(peg[2],80,0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'C');
}

void drawSolved()
{
		glColor3f(1,1,1);
	draw_poly(-70, 85, -15, 76);
	draw_poly(-70, 65, -15, 56);
	draw_poly(-70, 45, -15, 36);
	draw_poly(-70, 25, -15, 16);
    
	glColor3f(1,0,0);
    printtext((char *)"     START", -67, 80);
	printtext((char *)" 	RANDOM", -67, 60);
	printtext((char *)"    RESTART", -67, 40);
	printtext((char *)"     EXIT", -67, 20);
	
	solved=true;
	glColor3f(1,1,0);

	printtext((char *)"Solved !!",-60,90);

	draw_poly(10, 20, 10, 5);  
    glColor3f(1,0,0);
    printtext((char *)"exit", 60,100);
    glColor3f(1,1,1);

	

	printtext((char *)"Number of Moves : ",200,0);
	printtext(str,280,0); //Printing count onto display

	glColor3f(1,0,0);
	glRasterPos3f(peg[0],70,0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'A');
	glRasterPos3f(peg[1],70,0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'B');
	glRasterPos3f(peg[2],70,0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'C');


}

void display()
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
	
	
	int i,j,k;
	if(randomColorFlag)
		glClearColor((rand()%100)/100.0,(rand()%100)/100.0,(rand()%100)/100.0,0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	if(lightflag)glEnable(GL_LIGHTING);	
	glPushMatrix();
	gluLookAt(0,ycoordinate,0,0,0,-1,0,1,0);
	drawPegs();
	for(i=0;i<3;i++)
	{
		k=0;
		for(j=0;j<=top[i];j++)
		{
			glPushMatrix();
			glTranslatef(peg[i],pos[k++],0);
			glRotatef(90,1,0,0);
			glColor3f(0.1*POLES[i][j],0.2*POLES[i][j],0);
			glutSolidTorus(2.0, 4*POLES[i][j], 20, 20);
			glPopMatrix();
		}
	}	
	glPopMatrix();
	glDisable(GL_LIGHTING);	
	if(counter == max_moves)
		{//counter++;
		drawSolved();}
	else
		{drawText();}
	if(lightflag)glEnable(GL_LIGHTING);
	glutSwapBuffers();
}






void animate(int n,int src,int dest)
{
	int i;
	if(speed<=0) speed=1;
	for(i=pos[top[src]+1];i<90;i+=speed)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glPushMatrix();
		glTranslatef(peg[src],i,0);
		glRotatef(85,1,0,0);
		glColor3f(0.1*n,0.2*n,0);
		glutSolidTorus(2.0, 4*n, 20, 20);
		glPopMatrix();
		glutSwapBuffers();
		display();
	}
	if(peg[src]<peg[dest])
		for(i=peg[src];i<=peg[dest];i+=speed)
		{
			glClear(GL_COLOR_BUFFER_BIT);
			glPushMatrix();
			glTranslatef(i,90,0);
			glRotatef(85,1,0,0);
			glColor3f(0.1*n,0.2*n,0);
			glutSolidTorus(2.0, 4*n, 20, 20);
			glPopMatrix();
			glutSwapBuffers();
			display();
		}
	else
		for(i=peg[src];i>=peg[dest];i-=speed)
		{
			glClear(GL_COLOR_BUFFER_BIT);
			glPushMatrix();
			glTranslatef(i,90,0);
			glRotatef(85,1,0,0);
			glColor3f(0.1*n,0.2*n,0);
			glutSolidTorus(2.0, 4*n, 20, 20);
			glPopMatrix();
			glutSwapBuffers();
			display();
		}
	for(i=70;i>pos[top[dest]+1];i-=speed)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glPushMatrix();
		glTranslatef(peg[dest],i,0);
		glRotatef(85,1,0,0);
		glColor3f(0.1*n,0.2*n,0);
		glutSolidTorus(2.0, 4*n, 20, 20);
		glPopMatrix();
		glutSwapBuffers();
		display();
	}
}

void mouse(int btn,int mode,int x,int y)
{
	if(btn == 4 && mode == GLUT_DOWN)
	{
		if(counter<max_moves)
		{
			pop(moves[counter][1]);
			if(animationFlag)
				animate(moves[counter][0],moves[counter][1],moves[counter][2]);
			push(moves[counter][2],moves[counter][0]);
			counter++;	
		}
	}
	if(btn == 3 && mode == GLUT_DOWN)
	{
		if(counter>0)
		{
			counter--;
			pop(moves[counter][2]);
			if(animationFlag)
				animate(moves[counter][0],moves[counter][2],moves[counter][1]);
			push(moves[counter][1],moves[counter][0]);
		}
	}
	glutMouseFunc(indmouse);
	glutPostRedisplay();
}

void restart()
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
	
	
	
	int i;
	memset(POLES,0,sizeof(POLES));
	memset(moves,0,sizeof(POLES));
	memset(top,-1,sizeof(top));
	cnt=0,counter=0;
	ycoordinate=0.1;
	max_moves = pow(2,NUM_DISKS)-1;
	for(i=NUM_DISKS;i>0;i--)
	{
		push(0,i);
	}
	tower(NUM_DISKS,0,1,2);
}

void processMenuLighting(int option)
{
	switch(option)
	{
		case LIGHT_ON:
		glDisable(GL_LIGHTING);
			lightflag=0;
			
		break;
		case LIGHT_OFF:
			glEnable(GL_LIGHTING);
			lightflag=1;
		break;
	}
	glutPostRedisplay();
}
void processMenuMain2(int option)
{
	
}
void processMenuCamera(int option)
{
	switch(option)
	{
		case 0:ycoordinate+=0.1;break;
		case 1:ycoordinate-=0.1;break;
	}
	glutPostRedisplay();
}

void processMenuRestart(int option)
{
	if(option==0)
	{
		restart();
		glutPostRedisplay();
	}
}

void processMenuExit(int option)
{
	if(option==0)exit(0);
}



void processMenuSolveCompletely(int option)
{
	if(option==1)
		animationFlag=0;
	else
		animationFlag=1;
		
	int i,j;
	while(counter<max_moves)
	{
		mouse(4,GLUT_DOWN,0,0);
		display();
		//for slowing execution
		for(i=0;i<100000;i++)
			for(j=0;j<100;j++);
	}
}

void processMenuBgColor(int option)
{
	switch(option)
	{
		case 0:glClearColor(0,0,0,0);randomColorFlag=0;break;
		case 1:glClearColor(0.8784,0.8784,0.8784,0);randomColorFlag=0;break;
		case 3:glClearColor(0,0.2,0,0);randomColorFlag=0;break;
		case 4:glClearColor(0,0,0.4,0);randomColorFlag=0;break;
		case 5:randomColorFlag=1;break;
	}
	glutPostRedisplay();
}

void createGLUTMenus2()
{
	int menu = glutCreateMenu(processMenuLighting);
	glutAddMenuEntry("On",LIGHT_ON);
	glutAddMenuEntry("Off",LIGHT_OFF);
	int menuExit = glutCreateMenu(processMenuExit);
	glutAddMenuEntry("Yes",0);
	glutAddMenuEntry("No",1);
	int menuCamera = glutCreateMenu(processMenuCamera);
	glutAddMenuEntry("+0.1",0);
	glutAddMenuEntry("-0.1",1);
	int menuRestart = glutCreateMenu(processMenuRestart);
	glutAddMenuEntry("Yes",0);
	glutAddMenuEntry("No",1);

	int menuBgColor = glutCreateMenu(processMenuBgColor);
	glutAddMenuEntry("Black",0);
	glutAddMenuEntry("White",1);
	//glutAddMenuEntry("Red",2);
	glutAddMenuEntry("Green",3);
	glutAddMenuEntry("Blue",4);
	glutAddMenuEntry("Random",5);
	int menuSolveCompletely = glutCreateMenu(processMenuSolveCompletely);
	glutAddMenuEntry("Slow",0);
	glutAddMenuEntry("Fast",1);
	glutCreateMenu(processMenuMain2);
	glutAddSubMenu("Lighting",menu);
	glutAddSubMenu("Move Camera",menuCamera);
	//glutAddSubMenu("Animation",menuAnimate);
	glutAddSubMenu("Background Color",menuBgColor);
	glutAddSubMenu("Solve Completely",menuSolveCompletely);
	glutAddSubMenu("Restart",menuRestart);
	glutAddSubMenu("Exit",menuExit);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void processMenuMain1(int option)
{
}

void processMenuNumDisks(int option)
{
	NUM_DISKS=option;
	restart();
	glutPostRedisplay();
}

void createGLUTMenus1()
{
	

	int menuExit = glutCreateMenu(processMenuExit);
	glutAddMenuEntry("Yes",0);
	glutAddMenuEntry("No",1);
	glutCreateMenu(processMenuMain1);
	glutAddSubMenu("Exit",menuExit);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void init_first()
{
	glClearColor(0,0,0,0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,1000,0,1000,-1,1);
	glMatrixMode(GL_MODELVIEW);

}


void keyboard(unsigned char c, int x, int y)
{
	if(front)
	{
		if(c == ' ')
		{
		
			glutReshapeWindow(1360,760);
			glutDisplayFunc(border);
			glutReshapeFunc(reshape);
			front = false;
			fpdone=true;
			disp=true;

		}
	}
	if(fpdone==true)
	{
		switch(c)
		{
		case 13:
			restart();
			init();
			glutDisplayFunc(display);
			createGLUTMenus2();
			glutMouseFunc(mouse);
		break;
		}
	}
	
	glutPostRedisplay();
}

int main(int argc,char** argv)
{
	cout<<"Number of Rings (1 to 10) : ";
	cin>>NUM_DISKS;
	if(NUM_DISKS<1 || NUM_DISKS>10 || (NUM_DISKS>='a'&& NUM_DISKS<='z') || (NUM_DISKS>='A' && NUM_DISKS<='Z'))
	{
		cout<<"--------------"<<endl;
		cout<<"INVALID INPUT"<<endl;
		cout<<"--------------\n\n"<<endl;
		cout<<"Try again!"<<endl;
		exit(0);
	}
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	//glutInitWindowSize(700,700);
	glutInitWindowSize(1360,760);
	//glutInitWindowSize(1000,500);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Tower Of Hanoi Implimentation");
	init_first();
	glutDisplayFunc(frontpage);
	glutReshapeFunc(reshapefront);
	createGLUTMenus1();
	glutKeyboardFunc(keyboard);
	glutMouseFunc(indmouse);
	glutMainLoop();
	return 0;
}
