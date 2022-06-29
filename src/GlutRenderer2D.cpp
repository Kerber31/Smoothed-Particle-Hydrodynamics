#include "../include/GlutRenderer2D.h"

void loop(int argc, char **argv) {
    glutInitWindowSize(solver->getWindowWidth(), solver->getWindowHeight());
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInit(&argc, argv);
    glutCreateWindow("SPH");
    glutDisplayFunc(render);
    glutIdleFunc(update);

    initGL();

    glutMainLoop();
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	glOrtho(0, solver->getViewWidth(), 0, solver->getViewHeight(), 0, 1);

	glColor4f(0.2f, 0.6f, 1.f, 1);
	glBegin(GL_POINTS);

	std::vector<Eigen::Vector2d> positions = solver->getPositions();

	for (auto &p : positions) {
		glVertex2f(p(0), p(1));
	}

	glEnd();

	glutSwapBuffers();
}

void update() {
	solver->update();
	glutPostRedisplay(); 
}

void initGL() {
	glClearColor(0.9f, 0.9f, 0.9f, 1);
	glEnable(GL_POINT_SMOOTH);
    glPointSize(solver->getPointSize());
	glMatrixMode(GL_PROJECTION);
}

void setSolver(SphSolver2DPtr solver_) {
    solver = solver_;
}
