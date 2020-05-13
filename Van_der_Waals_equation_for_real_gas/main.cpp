// build and run step (tested on Ubuntu-16.04)
// mkdir -p build && g++ main.cpp -lGL -lGLU -lglut -o build/main
// cd build && ./main
#include<iostream>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<stdio.h>
#include<cstring>
#include<stdlib.h>
#include<cmath>
const double Pi=3.14159, R = 8.314;
using namespace std;
int ww=400,wh=400;
void
bitmap_output(double x, double y,double z, char *string)
{
  int len, i;

  glRasterPos3f(x,y,z);
  len = (int) strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i]);
  }
}
void init1(){
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0,ww,0,wh);
}
void drawArrow(double x,double y,double theta){//theta in degree
  glPushMatrix();
  glTranslatef(x,y,0);
  glRotatef(theta,0,0,1);
  glTranslatef(-x,-y,0);
  glBegin(GL_LINE_STRIP);
    glVertex2d(x-7,y+7);
    glVertex2d(x,y);
    glVertex2d(x-7,y-7);
  glEnd();
  glPopMatrix();
}
void drawIsotherm(double a,double b,double T,char* name){ 
  b*=pow(10.0,-5);
  double list[10000][2],max1=0,max2=0,V=2*b;
  int pos=0;
  for(int i=0;i<10000;i++){
     list[i][0]=(R*T)/(V - b) - a/(V*V);//represents the pressure;
     list[i][1]=(R*T*V)/(V - b) - a/V;//represents the PV
     V+=b/2;
     if(max1<list[i][0]){
        max1=list[i][0];
        pos=i;
     }  
     if(max2<list[i][1])
        max2=list[i][1];
        
  }
  cout<<std::fixed<<list[0][0]<<' '<<max1<<endl;
 
  double xscale=200/(2.5*pow(10.0,7)),yscale=200.0/2270;
  //cout<<xscale<<' '<<yscale<<endl;
  for(int i=0;i<10000;i++){  
     list[i][0]=list[i][0]*xscale+20;
     list[i][1]=list[i][1]*yscale+20;
  }
  glBegin(GL_LINE_STRIP);
    for(int i=0;i<10000;i++)
        glVertex2dv(list[i]);
  glEnd(); 
  if(list[pos][0]<370&&list[pos][1]<370)
  bitmap_output(list[pos][0],list[pos][1],0,name);
  else { for(int i=0;i<10000;i++)
          if(list[i][0]<300&&list[i][1]<300){
             pos=i;
             break;
          }
       bitmap_output(list[pos][0],list[pos][1],0,name);
       }  
           
}   
void display1(void){
  glBegin(GL_LINES);
    glVertex2i(20,20);
    glVertex2i(220,20);
    glVertex2i(20,20);
    glVertex2i(20,220);
  glEnd();
  drawArrow(220,20,0);
  drawArrow(20,220,90);
  drawIsotherm(0.151,3.99,273.15,"CO");
  drawIsotherm(0.228,4.28,273.15,"CH4");
  drawIsotherm(0.364,4.27,273.15,"CO2");
  drawIsotherm(0.0274,2.66,273.15,"H2:273.15K");
  drawIsotherm(0.0274,2.66,125,"H2:125K");
  drawIsotherm(0.0274,2.66,103,"H2:103K");
  drawIsotherm(0.0274,2.66,90,"H2:90K");
  drawIsotherm(0.0274,2.66,73,"H2:73K");



  glFlush();
}
int main(int argc, char* argv[]){
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);
  glutInitWindowPosition(100,100);
  glutInitWindowSize(ww,wh);
  glutCreateWindow("Three-Dimensional Object Representations");
  glutDisplayFunc(display1);
  init1();
  glutMainLoop();
  return 0;
} 
 
