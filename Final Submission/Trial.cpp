//cr. code: Sumanta Guha.
////////////////////////

//importing the header files
#include <glew.h>
#include <freeglut.h>
#include <math.h>


void drawCircle(float x, float y, float radius, int numSegments, float aspectRatio) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments; i++) {
        // Calculate the angle for this vertex
        float theta = 2.0f * 3.14159f * float(i) / float(numSegments);

        // Calculate the x and y coordinates, adjusting for aspect ratio
        float dx = radius * cosf(theta);
        float dy = radius * sinf(theta);

        // Adjust the x coordinate by dividing by the aspect ratio
        glVertex3f(x + dx / aspectRatio, y + dy, 0);
    }
    glEnd();
}

void drawStars(float x, float y) {
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);

    glVertex3f(15.0f + x, 25.0f + y, 0.0f);
    glVertex3f(25.0f + x, 25.0f + y, 0.0f);
    glVertex3f(25.0f + x, 15.0f + y, 0.0f);
    glVertex3f(15.0f + x, 15.0f + y, 0.0f);
    // triangle
    glVertex3f(25.0f + x, 25.0f + y, 0.0f);
    glVertex3f(40.0f + x, 20.0f + y, 0.0f);
    glVertex3f(25.0f + x, 15.0f + y, 0.0f);
    // triangle
    glVertex3f(25.0f + x, 15.0f + y, 0.0f);
    glVertex3f(20.0f + x, 0.0f + y, 0.0f);
    glVertex3f(15.0f + x, 15.0f + y, 0.0f);
    // triangle
    glVertex3f(15.0f + x, 15.0f + y, 0.0f);
    glVertex3f(0.0f + x, 20.0f + y, 0.0f);
    glVertex3f(25.0f + x, 15.0f + y, 0.0f);
    // triangle
    glVertex3f(15.0f + x, 25.0 + y, 0.0);
    glVertex3f(20.0f + x, 40.0 + y, 0.0);
    glVertex3f(25.0f + x, 25.0f + y, 0.0);
    glEnd();

    // execute the drawing
    glFlush();
}

void drawRectangle(float x1, float y1, float x2, float y2) {
    glBegin(GL_POLYGON);

    glVertex3f(x1, y1, 0.0f);
    glVertex3f(x2, y1, 0.0f);
    glVertex3f(x2, y2, 0.0f);
    glVertex3f(x1, y2, 0.0f);

    glEnd();
}

void drawFlag(int base_x, int base_y, int base_z) {
    // Pole
    glBegin(GL_QUADS);
        glColor3f(0.5f, 0.35f, 0.5f);
        glVertex3d(base_x + 60, base_y + 0, base_z);
        glVertex3d(base_x + 62, base_y + 0, base_z);
        glVertex3d(base_x + 62, base_y + 40, base_z);
        glVertex3d(base_x + 60, base_y + 40, base_z);
    glEnd();
    
    // Palestine's Flag
    // Uni's flag was too hard to draw
    
    // Green rectangle
    glBegin(GL_QUADS);
        glColor3f(0.08f, 0.6f, 0.33f);
        glVertex3d(base_x + 62, base_y + 25, base_z);
        glVertex3d(base_x + 89, base_y + 25, base_z);
        glVertex3d(base_x + 89, base_y + 29, base_z);
        glVertex3d(base_x + 62, base_y + 29, base_z);
    glEnd();
    
    // White rectangle
    glBegin(GL_QUADS);
        glColor3f(1, 1, 1);
        glVertex3d(base_x + 62, base_y + 29, base_z);
        glVertex3d(base_x + 89, base_y + 29, base_z);
        glVertex3d(base_x + 89, base_y + 33, base_z);
        glVertex3d(base_x + 62, base_y + 33, base_z);
    glEnd();
    
    // Black rectangle
    glBegin(GL_QUADS);
        glColor3f(0, 0, 0);
        glVertex3d(base_x + 62, base_y + 33, base_z);
        glVertex3d(base_x + 89, base_y + 33, base_z);
        glVertex3d(base_x + 89, base_y + 37, base_z);
        glVertex3d(base_x + 62, base_y + 37, base_z);
    glEnd();
    
    // Red triangle
    glBegin(GL_TRIANGLES);
        glColor3f(0.89f, 0.19f, 0.17f);
        glVertex3d(base_x + 62, base_y + 25, base_z + 1);
        glVertex3d(base_x + 72, base_y + 31, base_z + 1);
        glVertex3d(base_x + 62, base_y + 37, base_z + 1);
    glEnd();
}


// Drawing routine.
void drawScene(void)
{
    // clearing the buffer and setting the drawing color
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.1, 0.17, 0.26);

    // Background
    drawRectangle(0, 150, 1000, 700);
    glColor3f(0.57, 0.18, 0.19);
    drawRectangle(0, 0, 1000, 150);

    glColor3f(0.29, 0.57, 0.73);
    // Draw a polygon with specified vertices counterclockwise.
    drawCircle(400.0f, 250.0f, 40.0f, 100, 1000 / 700);
    drawStars(150, 250);
    drawStars(50, 250);
    drawStars(250, 300);
    drawStars(230, 200);
    drawStars(100, 200);

    glEnd();
    
    drawFlag(350, 100, 15);

    // execute the drawing
    glFlush();
}




// Initialization routine.
void setup(void)
{
    //the clearing color of the opengl window (background)
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    // drawing the entire window
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //glOrtho(left, right, bottom, top, near, far)
    //Sets up a viewing box span along the x-axis is from left to right, along the y-axis from bottom to top,
    // and along the z-axis from ?far to ?near.
    glOrtho(0.0, 500.0, 0.0, 350.0, -20.0, 0.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Keyboard input processing routine. x & y are location of the mouse
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
        // ascii of escape key
    case 27:
        exit(0);
        break;
    default:
        break;
    }
}

// Main routine.
int main(int argc, char** argv)
{

    glutInit(&argc, argv);    // initializes the FreeGLUT library.

    // create context, set its version and set backward compatibility.
    // context is the interface between an instance of OpenGL and the rest of the system
    glutInitContextVersion(3, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    // wanting an OpenGL context to support a single-buffered frame, each pixel having red, green, blue and alpha values.
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

    // set the initial size of the OpenGL window and the location of its top left corner on the computer screen
    glutInitWindowSize(1000, 700);
    glutInitWindowPosition(200, 200);

    // creates the OpenGL context and its associated window with the specified string parameter as title.
    glutCreateWindow("space.cpp");

    // callback routines   when the OpenGL window is to be drawn, when it is resized,
    // and when keyboard input is received, respectively
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);

    // initializes GLEW (the OpenGL Extension Wrangler Library) which handles the loading of OpenGL extensions,
    // with the switch set so that extensions implemented even in pre-release drivers are exposed.
    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    // begins the event-processing loop, calling registered callback routines as needed
    glutMainLoop();

}
