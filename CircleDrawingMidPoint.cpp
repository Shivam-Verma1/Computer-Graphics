#include <gl/glut.h>

void writePoints(int x, int y, int pntX, int pntY) {
	glBegin(GL_POINTS);
	glVertex2f(x + pntX, y + pntY);
	glEnd();
}

void myinit() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);

	glPointSize(4.0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluOrtho2D(0.0, 800, 0.0, 600);
}

void midPointCircleAlgo(int pntX, int pntY, int r) {
	int x = 0;
	int y = r;

	float decision = 1 - r;
	writePoints(x, y, pntX, pntX);

	while (y > x) {
		if (decision < 0) {
			x++;
			decision += 2 * x + 3;
		}
		else {
			y--;
			x++;
			decision += 2 * (x - y) + 5;
		}
		writePoints(x, y, pntX, pntY);
		writePoints(x, -y, pntX, pntY);
		writePoints(-x, y, pntX, pntY);
		writePoints(-x, -y, pntX, pntY);
		writePoints(y, x, pntX, pntY);
		writePoints(y, -x, pntX, pntY);
		writePoints(-y, x, pntX, pntY);
		writePoints(-y, -x, pntX, pntY);
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 0);
	glPointSize(1);

	midPointCircleAlgo(300, 300, 200);
	glFlush();
}


int main(int argc, char* argv[], char* envp[]) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Mid Point Algo");

	glutDisplayFunc(display);

	myinit();

	glutMainLoop();
}
