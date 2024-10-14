#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glew.h>
#include <freeglut.h>
#include <math.h>
#include <stdio.h>

unsigned char* iconData;
int imgWidth , imgHeight = 40 , imgChannels;
unsigned char* loadImage(const char* filename, int* width, int* height, int* channels) {
    unsigned char* imgData = stbi_load(filename, width, height, channels, 0);
    if (!imgData) {
        fprintf(stderr, "Failed to load image: %s\n", stbi_failure_reason());
        return NULL;
    }
    return imgData; // Return the loaded image data
}

// Function to flip the image vertically
void flipImageVertically(unsigned char* data, int width, int height, int channels) {
    int rowSize = width * channels;
    unsigned char* flippedData = (unsigned char*)malloc(rowSize * height);

    for (int y = 0; y < height; y++) {
        memcpy(flippedData + (height - 1 - y) * rowSize, data + y * rowSize, rowSize);
    }

    memcpy(data, flippedData, rowSize * height);
    free(flippedData);
}

// Function to draw an icon
void drawIcon(unsigned char* data, int width, int height, float x, float y) {
    glRasterPos2f(x, y); // Set position without flipping Y
    glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, data); // Draw the icon
}

// Draw a half-circle (simulating glass with transparency)
void drawHalfCircle(float sh1,float sh2) {
    float radius = 30.0f; // Radius of the half-circle
    int segments = 100;    // Number of segments for a smoother curve
    float cx = 55.0f+sh1;      // Center x-coordinate
    float cy = 60.0f+sh2;      // Center y-coordinate

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);   // Center of the circle
    for (int i = 0; i <= segments; i++) {
        float theta = M_PI * i / segments;  // Angle from 0 to π radians (half-circle)
        float x = cx + cos(theta) * radius; // Calculate x coordinate
        float y = cy + sin(theta) * radius; // Calculate y coordinate
        glVertex2f(x, y);                   // Define vertex
    }
    glEnd();
}
void drawAlienCraft(float x, float y) {
    // Clear the color and depth buffers
   

    // Draw opaque polygons first
    glColor3f(0.392, 0.392, 0.525);  // Dark color
    glBegin(GL_POLYGON);
    glVertex3f(20.0+x, 60.0+y, 0.0);    // Rectangle-like polygon
    glVertex3f(90.0+x, 60.0+y, 0.0);
    glVertex3f(98.0+x, 50.0+y, 0.0);
    glVertex3f(12.0+x, 50.0+y, 0.0);
    glEnd();

    // Draw another opaque polygon
    glColor3f(0.9098, 0.5098, 0.1098);  // Orange color
    glBegin(GL_POLYGON);
    glVertex3f(20.0+x, 50.0+y, 0.0);
    glVertex3f(90.0+x, 50.0+y, 0.0);
    glVertex3f(80.0+x, 40.0+y, 0.0);
    glVertex3f(30.0+x, 40.0+y, 0.0);
    glEnd();

    // Draw a small opaque square
    glColor3f(0.2353, 0.2235, 0.21176);  // Gray color
    glBegin(GL_POLYGON);
    glVertex3f(45.0+x, 40.0+y, 0.0);
    glVertex3f(65.0+x, 40.0+y, 0.0);
    glVertex3f(65.0+x, 35.0+y, 0.0);
    glVertex3f(45.0+x, 35.0+y, 0.0);
    glEnd();

    // Draw the yellow light
    glColor4f(1.0f, 1.0f, 0.0f, 0.6f);  // Yellow color with low alpha
    glBegin(GL_POLYGON);
    glVertex3f(45.0f+x, 35.0f+y, 0.0);
    glVertex3f(65.0f+x, 35.0f+y, 0.0);
    glVertex3f(110.0f+x, 67.0f, 0.0);
    glVertex3f(0.0f+x, 67.0f, 0.0f);
    glEnd();

    // Enable blending for transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Disable depth writing to handle transparency properly
    glDepthMask(GL_FALSE);

    // Draw the icon if the image is loaded successfully
    if (iconData) {
        drawIcon(iconData, imgWidth, imgHeight, 40.0f+x, 59.0f+y); // Draw icon at position (20, 50)
    }

    // Draw the glass-like half-circle (with transparency)
    glColor4f(0.0f, 1.0f, 1.0f, 0.3f);  // Semi-transparent cyan color
    drawHalfCircle(x, y);

    // Re-enable depth writing
    glDepthMask(GL_TRUE);
    glEnd();

    // Flush the final drawing
   // glFlush();
}
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
void drawRoverBody(float width, float height)
{
    glPushMatrix();
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_QUADS);
    glVertex2f(-width / 2.0f, -height / 2.0f); // Bottom-left corner
    glVertex2f(width / 2.0f, -height / 2.0f);  // Bottom-right corner
    glVertex2f(width / 2.0f, height / 2.0f);   // Top-right corner
    glVertex2f(-width / 2.0f, height / 2.0f);  // Top-left corner
    glEnd();
    glPopMatrix();
}

void drawwheels(float roverWidth, float roverHeight, float radius)
{
    float wheelPositions[2][2] = {
        { roverWidth / 2.5f, -roverHeight / 2.0f - radius},
        {-roverWidth / 2.5f, -roverHeight / 2.0f - radius}
    };

    for (int i = 0; i < 2; ++i) {
        glPushMatrix();
        glTranslatef(wheelPositions[i][0], wheelPositions[i][1], 0.0f);
        drawCircle(0.0f, 0.0f, radius, 32, 1.0f); // Draw a circle with the specified radius
        glPopMatrix();
    }
}

void drawRover(float width, float height, float wheelRadius)
{
    glPushMatrix();
    glTranslatef(220.0f, 70.0f, 0.0f);
    drawRoverBody(width, height);
    drawwheels(width, height, wheelRadius);
    glPopMatrix();
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
   // glFlush();
}

void drawRectangle(float x1, float y1, float x2, float y2) {
    glBegin(GL_POLYGON);

    glVertex3f(x1, y1, 0.0f);
    glVertex3f(x2, y1, 0.0f);
    glVertex3f(x2, y2, 0.0f);
    glVertex3f(x1, y2, 0.0f);

    glEnd();
}

void drawFlag(int base_x, int base_y, int base_z, float scale) {
    // Pole
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.35f, 0.5f);
    glVertex3d(base_x, base_y, base_z);
    glVertex3d(base_x + 2 * scale, base_y, base_z);
    glVertex3d(base_x + 2 * scale, base_y + 40 * scale, base_z);
    glVertex3d(base_x, base_y + 40 * scale, base_z);
    glEnd();

    // Palestine's Flag
    // Uni's flag was too hard to draw

    // Green rectangle
    glBegin(GL_QUADS);
    glColor3f(0.08f, 0.6f, 0.33f);
    glVertex3d(base_x + 2 * scale, base_y + 25 * scale, base_z);
    glVertex3d(base_x + 29 * scale, base_y + 25 * scale, base_z);
    glVertex3d(base_x + 29 * scale, base_y + 29 * scale, base_z);
    glVertex3d(base_x + 2 * scale, base_y + 29 * scale, base_z);
    glEnd();

    // White rectangle
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3d(base_x + 2 * scale, base_y + 29 * scale, base_z);
    glVertex3d(base_x + 29 * scale, base_y + 29 * scale, base_z);
    glVertex3d(base_x + 29 * scale, base_y + 33 * scale, base_z);
    glVertex3d(base_x + 2 * scale, base_y + 33 * scale, base_z);
    glEnd();

    // Black rectangle
    glBegin(GL_QUADS);
    glColor3f(0, 0, 0);
    glVertex3d(base_x + 2 * scale, base_y + 33 * scale, base_z);
    glVertex3d(base_x + 29 * scale, base_y + 33 * scale, base_z);
    glVertex3d(base_x + 29 * scale, base_y + 37 * scale, base_z);
    glVertex3d(base_x + 2 * scale, base_y + 37 * scale, base_z);
    glEnd();

    // Red triangle
    glBegin(GL_TRIANGLES);
    glColor3f(0.89f, 0.19f, 0.17f);
    glVertex3d(base_x + 2 * scale, base_y + 25 * scale, base_z + 1);
    glVertex3d(base_x + 12 * scale, base_y + 31 * scale, base_z + 1);
    glVertex3d(base_x + 2 * scale, base_y + 37 * scale, base_z + 1);
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

    drawFlag(180, 70, 15, 2); 
    drawRover(200.0f, 50.0f, 20.0f);
    drawAlienCraft(250, 180);
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
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);

    // set the initial size of the OpenGL window and the location of its top left corner on the computer screen
    glutInitWindowSize(1000, 700);
    glutInitWindowPosition(200, 200);

    // creates the OpenGL context and its associated window with the specified string parameter as title.
    glutCreateWindow("space.cpp");

    // Load the image
    setup();
    glewExperimental = GL_TRUE;
    glewInit();
    iconData = loadImage("alienIcon.png", &imgWidth, &imgHeight, &imgChannels);

    // Flip the image vertically
    if (iconData) {
        flipImageVertically(iconData, imgWidth, imgHeight, imgChannels);
    }
   
    // callback routines   when the OpenGL window is to be drawn, when it is resized,
    // and when keyboard input is received, respectively
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);

    // initializes GLEW (the OpenGL Extension Wrangler Library) which handles the loading of OpenGL extensions,
    // with the switch set so that extensions implemented even in pre-release drivers are exposed.


    

    // begins the event-processing loop, calling registered callback routines as needed
 
    glutMainLoop();                // Start
    stbi_image_free(iconData);

}
