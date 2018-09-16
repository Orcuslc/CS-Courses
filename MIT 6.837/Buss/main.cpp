#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <vecmath.h>
using namespace std;

// Globals

// This is the list of points (3D vectors)
vector<Vector3f> vecv;
vector<Vector3f> vecn;

vector<vector<unsigned> > vecf;


// Main routine.
// Set up OpenGL, define the callbacks and start the main loop

void keyboardFunc( unsigned char key, int x, int y ) {
	switch ( key ) {
	case 27: // Escape key
		exit(0);
		break;
	default:
		cout << "Unhandled key press " << key << "." << endl;        
	}
	glutPostRedisplay();
}

void drawScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity(); 
	// glColor3f(1.0, 1.0, 1.0);

	// glPointSize(10);
	// glEnable(GL_POINT_SMOOTH);
	// glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glShadeModel(GL_FLAT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// glBegin(GL_POINTS);
	// glVertex3f(0.3, -1, 0.9);
	// glEnd();
	glLineWidth(10);
	// glEnable(GL_LINE_SMOOTH);
	// glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	// glBegin(GL_LINE_LOOP);
	// glBegin(GL_TRIANGLE_FAN);
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.8, 0.8, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(1.0, -0.9, 0.2);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(-1, -0.3, 0.5);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(0, 0, 0);
	glEnd();
	glutSwapBuffers();
}

int main( int argc, char** argv )
{
	glutInit(&argc,argv);

	// We're going to animate it, so double buffer 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

	// Initial parameters for window position and size
	glutInitWindowPosition( 60, 60 );
	glutInitWindowSize( 360, 360 );
	glutCreateWindow("1.1");
	glutKeyboardFunc(keyboardFunc);
	glutDisplayFunc( drawScene );
	glutMainLoop( );
	return 0;	// This line is never reached.
}
