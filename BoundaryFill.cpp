#include <GL/glut.h>
#include <math.h>
using namespace std;
float boncolor[] = { 0, 0, 0 };
float fillcolor[] = { 0, 0, 1 };
void draw_poly() {
	glLineWidth(1);
	glPointSize(1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3fv(boncolor);
	glBegin(GL_LINE_LOOP);
	glVertex2i(250, 100);
	glVertex2i(200, 200);
	glVertex2i(250, 250);
	glEnd();
	glFlush();
}
void boundaryfill(int x, int y, float* fillcolor, float* boncolor) {
	float color[3];
	glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);
	if ((color[0] != boncolor[0] || color[1] != boncolor[1] || color[2] != boncolor[2]) &&
		(color[0] != fillcolor[0] || color[1] != fillcolor[1] || color[2] != fillcolor[2])) {
		glColor3f(fillcolor[0], fillcolor[1], fillcolor[2]);
		glBegin(GL_POINTS);
		glVertex2i(x, y);
		glEnd();
		glFlush();
		boundaryfill(x + 1, y, fillcolor, boncolor);
		boundaryfill(x - 1, y, fillcolor, boncolor);
		boundaryfill(x, y + 1, fillcolor, boncolor);
		boundaryfill(x, y - 1, fillcolor, boncolor);
	}
}
void init() {
	glClearColor(1, 1, 1, 0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 600, 0, 500);
}
void mouse(int btn, int state, int x, int y) {
	y = 500 - y;
	if (btn == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			boundaryfill(x, y, fillcolor, boncolor);
		}
	}
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 500);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Boundary fill 4 connected");
	glutDisplayFunc(draw_poly);
	glutMouseFunc(mouse);
	init();
	glutMainLoop();
	return 0;
}
