#include "mandelbrot.hpp"

#include <iostream>
#include <cstdlib>
#include <GL/glut.h>

#define WIDTH 1000
#define HEIGHT 1000

unsigned char *rgbData;
unsigned int iter = 100;

int initialise() {
  int i, j, val;
  rgbData = (unsigned char*) malloc(sizeof(unsigned char) * WIDTH * HEIGHT * 3);

  for (i = 0; i < WIDTH; i++) {
    for (j = 0; j < HEIGHT; j++) {
      rgbData[3 * (j * WIDTH + i)] =
      rgbData[3 * (j * WIDTH + i) + 1] =
      rgbData[3 * (j * WIDTH + i) + 2] = 255 * isMandel((float) (4 * i) / WIDTH - 2, (float) (4 * j) / HEIGHT - 2, iter) / iter;
    }
  }

  return 1;
}

void onReshape(int w, int h) {
  // Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0) h = 1;
	float ratio = 1.0 * w / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

  // Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45, ratio, 1, 100);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void onDisplay() {
  int i;

  glDrawPixels(WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, rgbData);

  glutSwapBuffers();
}

void onKeyPressed(unsigned char key, int x, int y) {
  if (key == 'w') {
    iter++;
    initialise();
    onDisplay();
  }
  if (key == 's') {
    if (iter > 1) {
      iter--;
      initialise();
      onDisplay();
    }
  }
  // Exit on escape key press.
  if (key == 27) {
    exit(0);
  }
}

int main(int argc, char **argv) {
  // Initialise GLUT
  glutInit(&argc, argv);
  glutInitWindowPosition(10, 10);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

  glutCreateWindow("Mandelbrot");

  if (initialise()) {
    glutDisplayFunc(onDisplay);
    glutKeyboardFunc(onKeyPressed);

    // Start
    glutMainLoop();
  }

  free(rgbData);
  return 0;
}
