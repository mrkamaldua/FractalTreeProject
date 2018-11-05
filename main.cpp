#include<stdio.h>
#include<windows.h>
#include<GL/glut.h>
#include<math.h>
#define M_PI acos(-1.0)
int a=0;
typedef struct
    {
        double x;
        double y;
    }Point;
typedef struct
    {
        Point*Start;
        Point*End;
    }Trunk;
           void drawTrunkLine(double length,Trunk*ptr,Trunk*leftTrunk,Trunk*rightTrunk)
         {
             int c=0,d=0,k=0;double sum=0;
             double t;
             double x0=ptr->Start->x;double y0=ptr->Start->y;
          double x1=ptr->End->x;double y1=ptr->End->y;
          double m=(y1-y0)/(x1-x0);
          printf("\n%f",m);
          double xt,yt;
          if(!isinf(m))
          {

          xt=x1+length/sqrt(1+pow(m,2));
          t=(xt-x0)/(x1-x0);
          if(t>0&&t<1)
          {
               xt=-xt+2*x1;
              yt=y1-(m*length/sqrt(1+pow(m,2)));

          }
          else
          {
              yt=y1+(m*length/sqrt(1+pow(m,2)));
          }
          }
          else
          {
              xt=x1;
              if(y1>=y0)
              {
              yt=y1+length;
              }
              else
              {
                yt=y1-length;
              }
          }
         //rotation of xt,yt on both sides with respect to x1,y1
         double T1[3][3]={cos(M_PI/6),-sin(M_PI/6),x1*(1-cos(M_PI/6))+y1*sin(M_PI/6),sin(M_PI/6),cos(M_PI/6),y1*(1-cos(M_PI/6))-x1*sin(M_PI/6),0,0,1};
         double T2[3][1]={xt,yt,1};
         double T3[3][1];

            for (c = 0; c < 3; c++) {
             for (d = 0; d < 1; d++) {
             for (k = 0; k < 3; k++) {
              sum = sum + T1[c][k]*T2[k][d];
                         }
                  T3[c][d]=sum;
                    sum = 0;
                 }
                }
                leftTrunk->End->x=T3[0][0];
                leftTrunk->End->y=T3[1][0];
                double T0[3][3]={cos(M_PI/-6),-sin(M_PI/-6),x1*(1-cos(M_PI/-6))+y1*sin(M_PI/-6),sin(M_PI/-6),cos(M_PI/-6),y1*(1-cos(M_PI/-6))-x1*sin(M_PI/-6),0,0,1};
              for (c = 0; c < 3; c++) {
             for (d = 0; d < 1; d++) {
             for (k = 0; k < 3; k++) {
              sum = sum + T0[c][k]*T2[k][d];
                         }
                  T3[c][d]=sum;
                    sum = 0;
                 }
                }
                rightTrunk->End->x=T3[0][0];
                rightTrunk->End->y=T3[1][0];
                if(length<3.0)
                {
                    glColor3ub(30,147,45);
                }
                else
                {
                    glColor3ub(210,105,30);
                }
                glBegin(GL_LINES);
                glVertex2f(leftTrunk->Start->x,leftTrunk->Start->y);
                glVertex2f(leftTrunk->End->x,leftTrunk->End->y);
                glEnd();
                glBegin(GL_LINES);
                glVertex2f(rightTrunk->Start->x,rightTrunk->Start->y);
                glVertex2f(rightTrunk->End->x,rightTrunk->End->y);
                glEnd();
                glFlush();
         }
    void fractalTreeBranch(Trunk*ptr)
        {
          double x1=ptr->Start->x;double y1=ptr->Start->y;
          double x2=ptr->End->x;double y2=ptr->End->y;
          double length=sqrt(pow(y2-y1,2)+pow(x2-x1,2))*0.6;
          Trunk*leftTrunk=(Trunk*)malloc(sizeof(Trunk));
          Trunk*rightTrunk=(Trunk*)malloc(sizeof(Trunk));
          leftTrunk->Start=(Point*)malloc(sizeof(Point));leftTrunk->End=(Point*)malloc(sizeof(Point));
          rightTrunk->Start=(Point*)malloc(sizeof(Point));rightTrunk->End=(Point*)malloc(sizeof(Point));
          leftTrunk->Start->x=x2;leftTrunk->Start->y=y2;
          rightTrunk->Start->x=x2;rightTrunk->Start->y=y2;
          //printf("%f %f %f %f",leftTrunk->End->x,leftTrunk->End->y,rightTrunk->End->x,rightTrunk->End->y);
          drawTrunkLine(length,ptr,leftTrunk,rightTrunk);
           if(length>0.4)
           {

          fractalTreeBranch(leftTrunk);
          fractalTreeBranch(rightTrunk);
           }
     // free(ptr->End);free(ptr->Start);
      //free(leftTrunk->End);free(leftTrunk->Start);
      //free(rightTrunk->End);free(rightTrunk->Start);
      //free(ptr);free(leftTrunk);free(rightTrunk);
//use glColor3ub for the rgb values range of 255
        }

  void display()
    {
       glClear(GL_COLOR_BUFFER_BIT);
       glBegin(GL_LINES);
       glVertex2f(350,50);
       glVertex2f(350,200);
       //glVertex2f(272,245);
       glEnd();
       glFlush();
       Trunk*ptr=(Trunk*)malloc(sizeof(Trunk));
       ptr->Start=(Point*)malloc(sizeof(Point));
       ptr->End=(Point*)malloc(sizeof(Point));
       ptr->Start->x=350;ptr->Start->y=50;
       ptr->End->x=350;ptr->End->y=200;
       fractalTreeBranch(ptr);
    }

        void init()
          {
        glClearColor(1.0,1.0,1.0,1.0);
        glColor3ub(210,105,30);
        gluOrtho2D(0.0f, 700.0f, 0.0f, 500);
        //glPointSize(5.0f) will work only with GL_POINTS not with GL_LINE
        //For gl_LINES you have to use gl_Line_Width
        glLineWidth(100.3f);
        //glEnable(0x8642);
        //glEnable(GL_LINE_SMOOTH);
         }
  int main(int argc,char**argv)
     {
      glutInit(&argc,argv);
      glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
      glutInitWindowSize(700,500);
      glutInitWindowPosition(300,100);
      glutCreateWindow("Fractal Tree Algorithm");
      init();
      glutDisplayFunc(display);
      //glutIdleFunc(display);//to display something over and over again
      glutMainLoop();
      return 0;
    }
