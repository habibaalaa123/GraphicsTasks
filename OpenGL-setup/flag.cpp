//
//  flag.cpp
//  OpenGL-setup
//
//  Created by Ibrahim Fateen on 10/12/24.
//

#include <glew.h>
#include <freeglut.h>


void setup() {
    glClearColor(1, 1, 1, 0);
}

void resize(int width, int height) {
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyInput(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);
            break;
            
        default:
            break;
    }
}

void drawFlag() {
    glClear(GL_COLOR_BUFFER_BIT);

    int flag_z = 0;
    
    // Pole
    glBegin(GL_QUADS);
        glColor3f(0.5f, 0.35f, 0.5f);
        glVertex3d(60, 0, flag_z);
        glVertex3d(62, 0, flag_z);
        glVertex3d(62, 40, flag_z);
        glVertex3d(60, 40, flag_z);
    glEnd();
    
    // Palestine's Flag
    // Uni's flag was too hard to draw
    
    // Green rectangle
    glBegin(GL_QUADS);
        glColor3f(0.08f, 0.6f, 0.33f);
        glVertex3d(62, 25, flag_z);
        glVertex3d(89, 25, flag_z);
        glVertex3d(89, 29, flag_z);
        glVertex3d(62, 29, flag_z);
    glEnd();
    
    // White rectangle
    glBegin(GL_QUADS);
        glColor3f(1, 1, 1);
        glVertex3d(62, 29, flag_z);
        glVertex3d(89, 29, flag_z);
        glVertex3d(89, 33, flag_z);
        glVertex3d(62, 33, flag_z);
    glEnd();
    
    // Black rectangle
    glBegin(GL_QUADS);
        glColor3f(0, 0, 0);
        glVertex3d(62, 33, flag_z);
        glVertex3d(89, 33, flag_z);
        glVertex3d(89, 37, flag_z);
        glVertex3d(62, 37, flag_z);
    glEnd();
    
    // Red triangle
    glBegin(GL_TRIANGLES);
        glColor3f(0.89f, 0.19f, 0.17f);
        glVertex3d(62, 25, flag_z + 1);
        glVertex3d(72, 31, flag_z + 1);
        glVertex3d(62, 37, flag_z + 1);
    glEnd();
    
    
    glFlush();
}


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    
    glutInitContextVersion(3, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
    
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(200, 200);
    
    glutCreateWindow("flag");
    
    glutDisplayFunc(drawFlag);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    
    glewExperimental = GL_TRUE;
    glewInit();

    setup();
    
    glutMainLoop();
}
