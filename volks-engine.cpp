// cube.cpp
// Compile: clang++ cube.cpp -framework OpenGL -framework GLUT -o cube (Ignore this, you can compile it with anything if you want to.)
// Run:     ./cube
// Really not that easy to work with if you don't know how to do this stuff.
// took me 2 days to make this using AI to tutor me on this.
// This wasn't completely scripted by AI, I just had a lot of trouble doing the proper math.
// Yes, it did write out some example prompts, but I wrote them in my own way.
// Prepare for some overly articulate descriptions on how things function.

#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <cmath>

// Camera position
float camX = 0.0f, camY = 0.0f, camZ = 5.0f;

// Basic camera orientation stuff.
float camYaw = 0.0f;   // Rotate left or right, it's simple stuff.
float camPitch = 0.0f; // Rotate the camera either up or down. It's easy to do this stuff.

// The speed on which the camera moves.
const float speed = 0.1f;
const float turnSpeed = 0.05f; // radians per key press. It's rather simple.

void initGL() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
}
// This is where the cube is drawn. You can easily modify this.
void drawCube() {
    glBegin(GL_QUADS);
        // Front
        glColor3f(1,0,0); glVertex3f(-1,-1, 1);
        glColor3f(0,1,0); glVertex3f(-1, 1, 1);
        glColor3f(0,0,1); glVertex3f( 1, 1, 1);
        glColor3f(1,1,0); glVertex3f( 1,-1, 1);
        // Back
        glColor3f(1,0,1); glVertex3f(-1,-1,-1);
        glColor3f(0,1,1); glVertex3f(-1, 1,-1);
        glColor3f(1,1,1); glVertex3f( 1, 1,-1);
        glColor3f(0,0,0); glVertex3f( 1,-1,-1);
        // Left
        glColor3f(1,0,0); glVertex3f(-1,-1,-1);
        glColor3f(0,1,0); glVertex3f(-1,-1, 1);
        glColor3f(0,0,1); glVertex3f(-1, 1, 1);
        glColor3f(1,1,0); glVertex3f(-1, 1,-1);
        // Right
        glColor3f(1,0,1); glVertex3f(1,-1,-1);
        glColor3f(0,1,1); glVertex3f(1,-1, 1);
        glColor3f(1,1,1); glVertex3f(1, 1, 1);
        glColor3f(0,0,0); glVertex3f(1, 1,-1);
        // Top
        glColor3f(1,0,0); glVertex3f(-1, 1, 1);
        glColor3f(0,1,0); glVertex3f( 1, 1, 1);
        glColor3f(0,0,1); glVertex3f( 1, 1,-1);
        glColor3f(1,1,0); glVertex3f(-1, 1,-1);
        // Bottom
        glColor3f(1,0,1); glVertex3f(-1,-1, 1);
        glColor3f(0,1,1); glVertex3f( 1,-1, 1);
        glColor3f(1,1,1); glVertex3f( 1,-1,-1);
        glColor3f(0,0,0); glVertex3f(-1,-1,-1);
    glEnd();
}
// For the color of the cube faces, I just did what the AI thing said.
// You can easily change the colors, or completely redo this to where it fits your needs.
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Build direction vector from the yaw and the pitch. I guess it works.
    float dirX = cos(camPitch) * sin(camYaw);
    float dirY = sin(camPitch);
    float dirZ = -cos(camPitch) * cos(camYaw);

    // Camera target = position + direction. It's how the camera stuff changes if I'm right.
    gluLookAt(camX, camY, camZ,
              camX + dirX, camY + dirY, camZ + dirZ,
              0.0, 1.0, 0.0);

    drawCube();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)w/h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    // Current forward direction. Go forward.
    float dirX = cos(camPitch) * sin(camYaw);
    float dirY = sin(camPitch);
    float dirZ = -cos(camPitch) * cos(camYaw);

    // Right vector (perpendicular in XZ plane) 
    // shit
    float rightX = cos(camYaw);
    float rightZ = sin(camYaw);

    switch (key) {
        case 'w': // forward.
            camX += dirX * speed;
            camY += dirY * speed;
            camZ += dirZ * speed;
            break;
        case 's': // Go back!
            camX -= dirX * speed;
            camY -= dirY * speed;
            camZ -= dirZ * speed;
            break;
        case 'a': // go left
            camX -= rightX * speed;
            camZ -= rightZ * speed;
            break;
        case 'd': // go right
            camX += rightX * speed;
            camZ += rightZ * speed;
            break;
        case 'q': // down
            camY -= speed;
            break;
        case 'e': // up
            camY += speed;
            break;
        case 27: // Escape. You close the application by doing this.
            exit(0);
    }
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            camYaw -= turnSpeed;
            break;
        case GLUT_KEY_RIGHT:
            camYaw += turnSpeed;
            break;
        case GLUT_KEY_UP:
            camPitch += turnSpeed;
            if (camPitch > 1.5f) camPitch = 1.5f; // clamp ~85 degrees
            break;
        case GLUT_KEY_DOWN:
            camPitch -= turnSpeed;
            if (camPitch < -1.5f) camPitch = -1.5f;
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Camera Fly with Arrow Keys");

    initGL();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);

    glutMainLoop();
    return 0;
}
// All of this is under the MIT license.
// I will be redoing this engine, or at least most of the functions within it.
// Also, if there are any warnings during the compiling of this, I am very sorry.
// The code contained within this would not have been possible without a few youtube tutorials and ChatGPT.
// Before you go out and attack me and the BRIXODE platform, No. This is not an AI generated game engine.
// BRIXODE will not be using this piece of shit engine.
// I'm going to give up if I spend all year on the BRIXODE game engine and get nothing done for the site.
// I would have a lot more luck with this if I had paid attention in my math classes.
