#include <GL/glut.h>
// Compilar con: -L/usr/X11R6/lib/ -lGL -lGLU -lglut
#define WIDTH_PLANO  5
#define HEIGHT_PLANO 5
#define SCALE 1

void waitFor (unsigned int secs) {
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
}

void DrawCircle(float h, float k, float r, int num_segments) 
{
	float x, y;
	int i;

	glBegin(GL_TRIANGLE_FAN);
	
	for (i = 0; i < num_segments; i++){
		x = r * cos(i) + h;
		y = r * sin(i) + k;
		glVertex2f(SCALE*x, SCALE*y);
	}
	glEnd(); 
}

void drawTriangle(float* p1, float* p2, float* p3){
	glLineWidth(2.5);
	glColor3f(0.0, 0.5, 0.7);
	glBegin(GL_LINES);
	glVertex2f(p1[0], p1[1]);
	glVertex2f(p2[0], p2[1]);

	glVertex2f(p2[0], p2[1]);
	glVertex2f(p3[0], p3[1]);
	
	glVertex2f(p3[0], p3[1]);
	glVertex2f(p1[0], p1[1]);
	glEnd();
}

float** levelCurve(int* l_counter, float (*f)(float, float)){
	int MAXX = 600;
	float x, y, val, tmp_points[MAXX][2];
	int counter = 0, i;
	float c, n = MAXX;
	float h = (WIDTH_PLANO*2)/n;
	for (c = -5*WIDTH_PLANO; c < 5*WIDTH_PLANO; c += 5) {
		for (x = -WIDTH_PLANO; x < WIDTH_PLANO; x += h) {
			for (y = -HEIGHT_PLANO; y < HEIGHT_PLANO; y += h) {
				val = f(x, y);
				if (fabs(val - c) < 10e-3 && counter < MAXX) {
					tmp_points[counter][0] = x;
					tmp_points[counter++][1] = y;
				}
			}
		}
	}

	float** points = (float**) malloc (counter * sizeof(float*));

	for (i = 0; i < counter; ++i) {
		points[i] = (float*) malloc (2 * sizeof(float));
		points[i][0] = tmp_points[i][0];
		points[i][1] = tmp_points[i][1];
	}

	*l_counter = counter;

	return points;

}

// void drawTriangle(float* v1, float* v2, float* v2){
// 	drawLine(v1[0], v2[])
// }

void init2D(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0);  
	glMatrixMode (GL_PROJECTION);
	gluOrtho2D (-WIDTH_PLANO,  WIDTH_PLANO,
				-HEIGHT_PLANO, HEIGHT_PLANO);
}