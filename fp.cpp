#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<math.h>
#include<cmath>
#include<iostream>
#include<string.h>
void initf()
{
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);
}


void printtextteju(char s[], int x, int y,int state = 1)
{
    int l = (int)strlen(s);
    glRasterPos2i(x,y);
    for(int i = 0;i<l;i++)
    {
        if(state == 1)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
        else if(state == 2)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, s[i]);
        else if(state == 3)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
    }
}
void frontpage()
{
    initf();

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


    glColor3f(1,1,1);
    glColor3f(0,1,1);
    printtextteju((char *)"           VISVESVARAYA TECHNOLOGICAL UNIVERSITY BELGAVI, KARNATAKA - 590018",-60,80);
    //printtextteju((char *)"BELGAVI, KARNATAKA - 590018",-40,70,27);
    glColor3f(1,1,1);
    printtextteju((char *)"           A Minor Project on",-22,60);
    glColor3f(1,0,0);
    printtextteju((char *)"              TOWER OF HANOI SIMULATION",-40,48,3);
    glColor3f(0.76470588235,0.06274509803,0.93725490196);
    printtextteju((char *)"                Submitted in partial fulfullment for the Computer Graphics and Visualization  Laboratory course of",-58,33,2);
    printtextteju((char *)"                                                    Sixth Semester of Bachelor of Engineering in Computer",-60,29,2);
    printtextteju((char *)"                           Science & Engineering during the academic year 2018-19",-47,25,2);
    glColor3f(1,1,1);
    printtextteju((char *)"By",-1,12,2);
    glColor3f(1,0,0);
    printtextteju((char *)"TEJASVI S                                                            4MN16CS045",-35,0);
    printtextteju((char *)"UMEZ ARFATH HASNI                                         4MN16CS047",-35,-8);
    glColor3f(0.929411764,0.56862745,0.027450980);
    printtextteju((char *)"                   ||Under the Guidance of||",-27,-20);
    printtextteju((char *)"                     Prof. Bharath Bharadwaj B S",-31,-30);
    printtextteju((char *)"          Assistant Professor",-12,-34,2);
    printtextteju((char *)"           Dept. of CS&E",-11,-38,2);
    printtextteju((char *)"          MIT Thandavpura",-13,-42,2);
    printtextteju((char *)"          2018-19",-9,-50,7);
    glColor3f(0,1,1);
    printtextteju((char *)"                                              DEPARTMENT OF COMPUTER SCIENCE & ENGINEERING",-70,-60);
    printtextteju((char *)"                                                MAHARAJA INSTITUTE OF TECHNOLOGY THANDAVAPURA",-73,-70);
    printtextteju((char *)"                                  NH 766, Nanjangud Taluk, Mysuru - 571302",-50,-80);
    glColor3f(1,1,1);
    
    glBegin(GL_LINES);
        glVertex2f(-40,46);
        glVertex2f(39,46);
    glEnd();
    
    //FOR Name box
    glBegin(GL_LINE_STRIP);
        glVertex2f(-40,7);
        glVertex2f(-40,-12);
        glVertex2f(43,-12);
        glVertex2f(43,7);
        glVertex2f(-40,7);
    glEnd();
    glutSwapBuffers();
}