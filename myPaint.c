#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glut.h>


/* Global variables */

GLsizei windowHeight = 700, windowWidth = 700; 

GLfloat red = 1.0, green = 1.0, blue = 1.0;    

int fillFlag = 0;	

static const int number_of_shapes = 5;


void addIcon(char* icon) 
{



}


void display(void) 
{ 
	/* Create white area for drawing. */
	float left_bound = -1.5f;
 	
	glBegin(GL_QUADS);
		glVertex2f(left_bound, -2.0f); // The bottom left corner  
   		glVertex2f(left_bound, 2.0f); // The top left corner  
    	glVertex2f(2.0f, 2.0f); // The top right corner  
    	glVertex2f(2.0f, -2.0f); // The bottom right corner  
    glEnd();


    int i;
    float shape_y = 1.6f;
    char *icons[] = {"LINE", "SQUARE", "RECTANGLE", "CIRCLE", "TRIANGLE"};

 	/* Draw areas for shape options to go. */
    glBegin(GL_LINES);
    	for (i = 0; i < number_of_shapes; ++i)
    	{
    		glVertex2f(left_bound, shape_y);
    		glVertex2f(left_bound - 0.5, shape_y);
    		shape_y -= 0.4;
    		addIcon(icons[i - 1]);
    	}
    glEnd();
    glFlush();
}




/* Reshapes all objects when the viewport is changed. */
void Reshape(GLsizei width, GLsizei height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (width <= height)
	{
		gluOrtho2D(-2.0, 2.0, -2.0 * (GLfloat) height / (GLfloat) width,
								 2.0 * (GLfloat) height / (GLfloat) width);
	}
	else 
	{
		gluOrtho2D(-2.0, 2.0, -2.0 * (GLfloat) width / (GLfloat) height,
								 2.0 * (GLfloat) width / (GLfloat) height);
	}
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, width, height);
	windowHeight = width;
	windowWidth = height;

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}


/* Postpones the display callback until glutPostRedisplay() is executed. */
void idle() 
{
	glutPostRedisplay();
	return;
}


/* Takes keyinput to end application. */
void keyInput(unsigned char key, int x, int y)
{
	if (key == 'Q' || key == 'q') {
		exit(0);
	}
	return;
}


void init(void)
{
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity(); 
   glOrtho(0.0, (GLdouble) windowWidth , 0.0, (GLdouble) windowHeight , -1.0, 1.0);

   glClearColor (0.0, 0.0, 0.0, 1.0);
   glClear(GL_COLOR_BUFFER_BIT);

   glFlush();
}


int main(int argc, char **argv)
{
	
	glutInit(&argc, argv);
	glutInitWindowSize(windowWidth, windowHeight);

	glutInitWindowPosition(500,200);
	glutCreateWindow("My paint application.");

	init();

	glutIdleFunc(idle);
	glutKeyboardFunc(keyInput);
	glutReshapeFunc(Reshape);
	glutDisplayFunc(display);

	glutMainLoop();
	return 0;
}
   