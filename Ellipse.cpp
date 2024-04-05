#midpoint for ellipse
#include <GL/glut.h>
#include <math.h>

void writepoints(int x, int y, int pntX1, int pntY1) {
    glBegin(GL_POINTS);
    glVertex2i(x + pntX1, y + pntY1);
    glEnd();
}

void myinit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void midPoint(int pntX1, int pntY1, int a, int b) {
    int a2 = a * a;
    int b2 = b * b;
    int x = 0;
    int y = b;
    float decision = b2 + a2 * (-b + 0.25);

    writepoints(x, y, pntX1, pntY1);
    while (b2 * (x + 1) < a2 * (y - 0.5)) {
        if (decision < 0) {
            decision += b2 * (2 * x + 3);
        } else {
            decision += b2 * (2 * x + 3) + a2 * (-2 * y + 2);
            y--;
        }
        x++;
        writepoints(x, y, pntX1, pntY1);
        writepoints(x, -y, pntX1, pntY1);
        writepoints(-x, y, pntX1, pntY1);
        writepoints(-x, -y, pntX1, pntY1);
    }

    decision = b2 * (x + 0.5) * (x + 0.5) + a2 * (y - 1) * (y - 1) - a2 * b2;
    while (y > 0) {
        if (decision < 0) {
            decision += b2 * (2 * x + 2) + a2 * (-2 * y + 3);
            x++;
        } else {
            decision += a2 * (-2 * y + 3);
        }
        y--;
        writepoints(x, y, pntX1, pntY1);
        writepoints(x, -y, pntX1, pntY1);
        writepoints(-x, y, pntX1, pntY1);
        writepoints(-x, -y, pntX1, pntY1);
    }
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(1.0);
    midPoint(300, 200, 200, 100); // Center at (300, 200), horizontal radius = 200, vertical radius = 100
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Midpoint Ellipse Drawing");
    glutDisplayFunc(display);
    myinit();
    glutMainLoop();
    return 0;
}
