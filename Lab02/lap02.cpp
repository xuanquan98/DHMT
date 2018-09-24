/* -- INCLUDE FILES ------------------------------------------------------ */
#include <windows.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <GL/glut.h>


/* ----------------------------------------------------------------------- */


void myInit( void )  {
	    glClearColor( 0.0, 0.0, 0.0, 0.0 );
        glColor3f( 1.0, 1.0, 1.0 );
        glPointSize( 3.0 );
        
	
}

static GLfloat spin = 0.0;
void spinDisplay(void)
{
    spin = spin + 2.0;
    if (spin > 360.0)
    spin = spin - 360.0;
    glutPostRedisplay();
}

/*void mouse(int button, int state, int x, int y) 
{
    switch (button) {
    case GLUT_LEFT_BUTTON:
    if (state == GLUT_DOWN){
    	glutIdleFunc(spinDisplay);
	}
    
    break;
    case GLUT_RIGHT_BUTTON:
    if (state == GLUT_DOWN)
    glutIdleFunc(NULL);
    break;
    default:
    break;
    }
}*/

int n=0;
void mouse(int button, int state, int x, int y) 
{
	
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && n%2==0){
    	n++;
    	glutIdleFunc(spinDisplay);
	} else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && n%2!=0){
		n++;
    	glutIdleFunc(NULL);
    }
		
    
}

void RendenScene()  {
	    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); 
	    glLoadIdentity();
        glPushMatrix();	 
	    glRotatef(spin, 0.0, 0.0, 1.0);
        glBegin(GL_TRIANGLES);
            glVertex2f(0.0, 0.0);
            glVertex2f(-4.0, 8.0);
            glVertex2f(-4.0, 4.0);
        glEnd();
        
        glPopMatrix(); 
		glFlush();			
  	    glutSwapBuffers();
   
}
void ReShape( int width, int height){
	//glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glOrtho(-10.0, 10.0, -10.0, 10.0, 10.0, -10.0);
	
}
/* ----------------------------------------------------------------------- */

int main( int argc, char *argv[] )  {
	glutInit( &argc, argv );
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Lap01");
	
	myInit();
	glutReshapeFunc(ReShape);
	glutMouseFunc(mouse);
	glutDisplayFunc(RendenScene);
	glutMainLoop();
 
}

/* ----------------------------------------------------------------------- */


