#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <fstream>
#include <iostream>
#include <wtypes.h>
#include <math.h>
#include <vector>
#include <conio.h>
using namespace std;

#define SIZEBOARD 720 // kich thuoc window


typedef GLfloat twodimpoint[2];

vector<GLfloat> listPointX;
vector<GLfloat> listPointY;
int limit = 3; // more than this gets ugly

void initGL() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to black and opaque
    glClearDepth(1.0f);                   // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
    glShadeModel(GL_SMOOTH);   // Enable smooth shading
    gluOrtho2D(-3, 3, -3, 3);
    //GetDesktopResolution();
    //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}
// De Quy
void kochcurve1 (twodimpoint begin, twodimpoint end, int n)
{
  if(n <= 0)
  {
     listPointX.push_back(begin[0]);
     listPointY.push_back(begin[1]);
  }
  else
  {
    // begin
    twodimpoint pointA = {end[0] - begin[0], end[1] - begin[1]}; // vec tor co huong cua begin -> end OA
    // 2/3 of the way
    twodimpoint pointB = { begin[1] - end[1], end[0] - begin[0] }; // vector co huong cua  canh huong len
    // point above line at 1/2 way
    twodimpoint pointC = { begin[0] + (1.0/3.0)*pointA[0], begin[1] + (1.0/3.0)*pointA[1]};
    // 1/3 of the way
    twodimpoint pointD = { begin[0] + (1.0/2.0)*pointA[0] - (sqrt(3)/6.0)*pointB[0],  begin[1] + (1.0/2.0)*pointA[1] - (sqrt(3)/6.0)*pointB[1]};
    // end
    twodimpoint pointE = {begin[0] + (2.0/3.0)*pointA[0], begin[1] + (2.0/3.0)*pointA[1]};

    kochcurve1 (begin, pointC, n-1);
    //line a to b
    kochcurve1 (pointC, pointD, n-1);
    //line b to c
    kochcurve1 (pointD, pointE, n-1);
    //line c to d
    kochcurve1 (pointE, end, n-1);
    //line d to e
  }
}

void kochcurve (twodimpoint begin, twodimpoint end, int n)
{
    // them toa do ban dau vao vector
    listPointX.push_back(begin[0]);
    listPointY.push_back(begin[1]);
    listPointX.push_back(end[0]);
    listPointY.push_back(end[1]);

    while(n > 1){
        vector<GLfloat>::iterator it1, it2;
        int _size = listPointX.size(); // tra ve so diem trong vector
        for(it1 = listPointX.begin(), it2 = listPointY.begin(); _size > 1; _size--){
        begin[0] = *it1;
        begin[1] = *it2;
        end[0] = *(it1 + 1);
        end[1] = *(it2 + 1);
        // tinh toan tuong tu De Quy
        twodimpoint pointA = {end[0] - begin[0], end[1] - begin[1]};
        // 2/3 of the way
        twodimpoint pointB = { begin[1] - end[1], end[0] - begin[0] };
        // point above line at 1/2 way

        twodimpoint pointC = { begin[0] + (1.0/3.0)*pointA[0], begin[1] + (1.0/3.0)*pointA[1]};
            it1 = listPointX.insert(it1 + 1, pointC[0]);
            it2 = listPointY.insert(it2 + 1, pointC[1]);
        // 1/3 of the way
        twodimpoint pointD = { begin[0] + (1.0/2.0)*pointA[0] - (sqrt(3)/6.0)*pointB[0],  begin[1] + (1.0/2.0)*pointA[1] - (sqrt(3)/6.0)*pointB[1]};
            it1 = listPointX.insert(it1 + 1, pointD[0]);
            it2 =  listPointY.insert(it2 + 1, pointD[1]);

        twodimpoint pointE = {begin[0] + (2.0/3.0)*pointA[0], begin[1] + (2.0/3.0)*pointA[1]};
            it1 = listPointX.insert(it1 + 1, pointE[0]);
            it2 = listPointY.insert(it2 + 1, pointE[1]);
            vector<GLfloat>::iterator x, y;
        it1 += 1;
        it2 += 1;
        }
        n--;
    }
}
static long long int n = 0;
void kochsnowflake(twodimpoint point1, twodimpoint point2)
{
    /**
    if(listPointX.size() == 0)
        kochcurve1(point1, point2, limit);
    // dung de quy
    listPointX.push_back(point2[0]);
    listPointY.push_back(point2[1]);
    glColor3f(0.0, 0.0, 0.0);

    glBegin(GL_LINE_STRIP);
    while(!listPointX.empty()){
        glVertex2f(listPointX.back(), listPointY.back());
        listPointX.pop_back();
        listPointY.pop_back();
    }
    glEnd();
    */
   if(listPointX.size() == 0){
        kochcurve(point1, point2, limit);
        n = listPointX.size();
        cout << limit << ": " << n << endl;
   }

    glColor3f(0.0, 0.0, 0.0);

    glBegin(GL_LINE_STRIP);
    for(int i = n - 1; i >= 0; i--)
        glVertex2f(listPointX.at(i), listPointY.at(i));
    glEnd();
} // end of kochsnowflake

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    listPointX.clear();
    listPointY.clear();
    twodimpoint point1 = {-2, 0};
    twodimpoint point2 = {2, 0};
    // ve canh duoi cung
    glPushMatrix();
    glTranslatef(0.0, -2/sqrt(3), 0.0);
    kochsnowflake(point1, point2);
    glPopMatrix();
    // ve canh ben phai
    glPushMatrix();
    glRotated(120, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -2/sqrt(3), 0.0);
    kochsnowflake(point1, point2);
    glPopMatrix();
    // ve canh ben trai
    glPushMatrix();
    glRotated(-120, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -2/sqrt(3), 0.0);
    kochsnowflake(point1, point2);
    glPopMatrix();
    glutSwapBuffers();
}

void keyboard(int key, int x, int y){
    switch(key){
    case GLUT_KEY_DOWN:
        limit--;
        if(limit < 0)
            limit = 0;
        glutPostRedisplay();
        break;
    case GLUT_KEY_UP:
        limit++;
        if(limit > 15)
            limit = 15;
        glutPostRedisplay();
        break;
    }
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(SIZEBOARD, SIZEBOARD);
    glutInitWindowPosition(300, 0);

    glutCreateWindow("Koch SnowFake");
    glutDisplayFunc(display);
    glutSpecialFunc(keyboard);
    initGL();

    glutMainLoop();

}
