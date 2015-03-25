#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>



/* Function prototypes. */

void resetCoordinates(void);

void drawLine(int x, int y); 
void drawSquare(int x, int y);
void drawTriangle(int x, int y);
void drawCircle(int x, int y);
void drawPoint(int x, int y);

void mouse(int button, int state, int x, int y);

void key(unsigned char key, int x, int y);

void init(void);
void display(void);
void clearScreen(void);

void action_menu(int id);
void color_menu(int id);

void defineMenus(void);



/* Defined types. */ 

/* Pi is used for drawing circles. */

#ifndef PI
#define PI 3.1415926f
#endif

struct Coordinate {
   float x;
   float y;
};

/* Global variables */

GLsizei windowHeight = 500, windowWidth = 500; 

/* Colour variables set by menu's for drawing. */

GLfloat red = 1.0, green = 1.0, blue = 1.0; 

/* Deterines shape to draw, set by menu's. */
int selected_shape = 0;


/*  Used by all drawing functions. */

int draw_count = 0;
struct Coordinate draw_Coordinates[3];


/* Resets the draw coordinates after each shape is drawn. */
void resetCoordinates(void) {
	int i;
	for (i = 0; i < 3; ++i)
	{
		draw_Coordinates[i].x = 0.0;
		draw_Coordinates[i].y = 0.0;
	}
}


void drawLine(int x, int y) 
{
	draw_Coordinates[draw_count].x = x; 
	draw_Coordinates[draw_count].y = windowHeight - y;
	draw_count++;

	glColor3f(red, green, blue);

	if (draw_count == 2)
	{
		glBegin(GL_LINES);
			glVertex2f(draw_Coordinates[0].x, draw_Coordinates[0].y);
			glVertex2f(draw_Coordinates[1].x, draw_Coordinates[1].y);
		glEnd();
		draw_count = 0;
	}	
	glutPostRedisplay();
}


void drawSquare(int x, int y) 
{
	glColor3f(red, green, blue);

	draw_Coordinates[draw_count].x = x; 
	draw_Coordinates[draw_count].y = windowHeight - y;
	draw_count++;

	if (draw_count == 2)
	{
		glRectf(draw_Coordinates[0].x, draw_Coordinates[0].y,
				draw_Coordinates[1].x, draw_Coordinates[1].y);
		draw_count = 0;
	}
	glutPostRedisplay();
}


void drawTriangle(int x, int y) 
{
	glColor3f(red, green, blue);

	draw_Coordinates[draw_count].x = x; 
	draw_Coordinates[draw_count].y = windowHeight - y;
	draw_count++;
		
	if (draw_count == 3)
	{
		glColor3f(red, green, blue);
		glBegin(GL_TRIANGLES);
	      	glVertex2f(draw_Coordinates[0].x, draw_Coordinates[0].y);
	     	glVertex2f(draw_Coordinates[1].x, draw_Coordinates[1].y);
	      	glVertex2f(draw_Coordinates[2].x, draw_Coordinates[2].y);
   		glEnd();
   		draw_count = 0;
	}
	glutPostRedisplay();
}


void drawCircle(int x, int y)
{
	glColor3f(red, green, blue);
	
	draw_Coordinates[draw_count].x = x;
	draw_Coordinates[draw_count].y = windowHeight - y;
	draw_count++;

	if (draw_count == 2)
	{
		int clarity = 25; 
		float x = (draw_Coordinates[0].x - draw_Coordinates[1].x);
		float y = (draw_Coordinates[0].y - draw_Coordinates[1].y);
		/* Using the distance formula. */
		float radius = sqrt((x * x) + (y * y));

		glBegin(GL_LINE_LOOP); 
			int i;
			for(i = 0; i < clarity; i++) 
			{ 
				/* Get the current angle. */
				float theta = 2.0f * PI * (float) i / (float) clarity; 
				float x = radius * cosf(theta);
				float y = radius * sinf(theta);
				glVertex2f(x + draw_Coordinates[0].x, y + draw_Coordinates[0].y);
			} 
		glEnd();
		draw_count = 0;
		glutPostRedisplay();
	} 
}


void drawPoint(int x, int y) 
{
	/* Use the currently selected color variables. */
	glColor3f(red, green, blue);

	x = x;
	y = windowHeight - y;
    glPointSize(4.0);

    glBegin(GL_POINTS);
    	glVertex2f(x ,y);
    glEnd();
    glutPostRedisplay();
}


void mouse(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

		switch(selected_shape)
		{
		    case 1  :
		       drawLine(x,y);
		       break;
		    case 2  :
		       drawSquare(x,y);
		       break;
		    case 3  :
		       drawTriangle(x,y);
		       break;
		   case 4  :
		       drawPoint(x,y);
		       break;
		    case 5:
		    	drawCircle(x,y);
		    default: 
		       break;
		}
		glFlush();
	}
}

void display(void) 
{ 

/* All display functions are called from mouse callback functions. */

}

/* Allows the application to be closed by keystroke. */
void key(unsigned char key, int x, int y)
{
	if (key == 'Q' || key == 'q') 
	{
		exit(-1);
	}
	return;
}

/* Set state. */
void init(void)
{
	/* Setting viewport. */
   glMatrixMode(GL_MODELVIEW);
   glViewport(0, 0, windowWidth, windowHeight);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity(); 
   glOrtho(0.0, windowWidth, 0.0, windowHeight,  -1.0, 1.0);

   clearScreen();
   
}

void clearScreen(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}


/* User actions on menu screen. */
void action_menu(int id)
{
   if (id == 1)
   {
      clearScreen();
   } else
   {
   	  exit(1);
   }
}


/* Sets the global color variables based on menu input. */
void color_menu(int id)
{
	if(id == 1) // Red.
	{
		red = 1.0;
		green = 0.0;
		blue = 0.0;
	}
	else if(id == 2) // Green.
	{ 
      	red = 0.0;
      	green = 1.0;
      	blue = 0.0;
	}
	else if(id == 3) // Blue.
	{
		red = 0.0;
      	green = 0.0;
      	blue = 1.0;
	}
}

void shape_menu(int id)
{
	selected_shape = id;
}


void defineMenus(void)
{

	int color_menu_handle, shape_menu_handle;

	shape_menu_handle = glutCreateMenu(shape_menu);
	glutAddMenuEntry("Line",     1);
   	glutAddMenuEntry("Square",   2);
   	glutAddMenuEntry("Triangle", 3);
   	glutAddMenuEntry("Point",    4);
   	glutAddMenuEntry("Circle",   5);

	color_menu_handle = glutCreateMenu(color_menu);
   	glutAddMenuEntry("Red",     1);
   	glutAddMenuEntry("Green",   2);
   	glutAddMenuEntry("Blue",    3);
   	
    glutCreateMenu(action_menu);
    glutAddSubMenu("Shape", shape_menu_handle);
   	glutAddSubMenu("Color", color_menu_handle);
   	glutAddMenuEntry("Clear", 1);
   	glutAddMenuEntry("Quit",  2);
   	glutAttachMenu(GLUT_RIGHT_BUTTON);

}



int main(int argc, char **argv)
{
	/* Init the glut library should allways be called first. */
	glutInit(&argc, argv);

	/* Creates window of size given in paramaters. */
	glutInitWindowSize(windowHeight,windowWidth);

	glutCreateWindow("Paint Application");

	/* When ever the screen needs to be redrawn display function is called. */
	glutDisplayFunc(display);

	/* Called when a key stroke is entered. */
	glutKeyboardFunc(key);

	/* Called when the mouse is used. */
	glutMouseFunc(mouse);

	/* User defined function to set variables. */
	init();

	/* User defined to hold the menue code. */
	defineMenus();

	/* Main action loop. */
	glutMainLoop();
}