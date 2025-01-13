#include <GL/glut.h>
#include <GL/freeglut.h>
using namespace std;



// Struktur untuk transformasi
struct Movement
{
    float rotateX, rotateY, scale, translateX, translateY;
} movement;

bool isMoving = true; 
bool showCartesius = true; 
float lightPos[] = {0.0f, 20.0f, 0.0f, 1.0f}; 

// Prototipe fungsi
void init3D();
void display();
void createMenu();
void update(int value);
void processMenu(int option);
void drawTable();
void drawPlate();
void drawWatermelonSlice();
void drawOrange();
void handleKeyboard(unsigned char key, int x, int y);
void handleSpecialKeyboard(int key, int x, int y);



// Fungsi utama
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Buah-Buahan di Atas Piring");
    init3D();
    glutDisplayFunc(display);
    createMenu();
    glutKeyboardFunc(handleKeyboard); // Tangani input keyboard
    glutSpecialFunc(handleSpecialKeyboard); // Tangani tombol khusus
    glutTimerFunc(1000 / 60, update, 0);
    glutMainLoop();
    return 0;
}

// Gambar meja
void drawTable()
{
    glColor3ub(139, 69, 19); // Warna coklat untuk meja
    glPushMatrix();
    glTranslatef(0.0, -10.0, 0.0);
    glScalef(1.8, 0.1, 1.0);
    glutSolidCube(30.0);
    glPopMatrix();

    float legHeight = 15.0;
    float legSize = 2.0;

    glPushMatrix();
    glTranslatef(-13.0, -25.0, 13.0);
    glScalef(legSize, legHeight, legSize);
    glutSolidCube(2.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(13.0, -25.0, 13.0);
    glScalef(legSize, legHeight, legSize);
    glutSolidCube(2.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-13.0, -25.0, -13.0);
    glScalef(legSize, legHeight, legSize);
    glutSolidCube(2.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(13.0, -25.0, -13.0);
    glScalef(legSize, legHeight, legSize);
    glutSolidCube(2.0);
    glPopMatrix();
}

// Gambar piring
void drawPlate()
{
    glColor3ub(255, 255, 255);

    glPushMatrix();
    glTranslatef(0.0, -7.5, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    glutSolidTorus(1.0, 12.0, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, -7.6, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    glutSolidCylinder(12.0, 0.0, 30, 30);
    glPopMatrix();
}

// Gambar jeruk
void drawOrange()
{
    glColor3ub(255, 165, 0);
    glutSolidSphere(5.0, 30, 30);

    glPushMatrix();
    glColor3ub(139, 69, 19);
    glTranslatef(0.0, 5.5, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    GLUquadric *stem = gluNewQuadric();
    gluCylinder(stem, 0.2, 0.1, 1.5, 12, 6);
    gluDeleteQuadric(stem);
    glPopMatrix();
}



// Gambar semangka
void drawWatermelonSlice()
{
    glPushMatrix();
    glColor3ub(255, 0, 0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    glutSolidCone(5.0, 10.0, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(34, 139, 34);
    glTranslatef(0.0, -0.1, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    glutSolidTorus(0.3, 5.0, 30, 30);
    glPopMatrix();
}

// Gambar sistem kartesius
void drawCartesius()
{
    glLineWidth(1.0); 
    glBegin(GL_LINES);

    // Sumbu X (Merah)
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-40.0, 0.0, 0.0);
    glVertex3f(40.0, 0.0, 0.0);

    // Sumbu Y (Hijau)
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, -40.0, 0.0);
    glVertex3f(0.0, 40.0, 0.0);

    // Sumbu Z (Biru)
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, -40.0);
    glVertex3f(0.0, 0.0, 40.0);

    glEnd();
    glLineWidth(1.0); 
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    glTranslatef(movement.translateX, movement.translateY, -50.0);
    glRotatef(movement.rotateX, 1.0, 0.0, 0.0);
    glRotatef(movement.rotateY, 0.0, 1.0, 0.0);
    glScalef(movement.scale, movement.scale, movement.scale);

    // Tampilkan kartesius hanya jika showCartesius bernilai true
    if (showCartesius)
    {
        drawCartesius();
    }

    drawTable();
    drawPlate();
    // Posisi semangka
    glPushMatrix();
    glTranslatef(-4.0, -7.0, 0.0); // Digeser lebih jauh ke kiri
    drawWatermelonSlice();
    glPopMatrix();

    // Posisi jeruk
    glPushMatrix();
    glTranslatef(5.0, -3.5, 0.0); // Digeser ke kanan
    drawOrange();
    glPopMatrix();

    glutSwapBuffers();
}

void init3D()
{
    movement = {0, 0, 1.0, 0, 0}; // Inisialisasi transformasi
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 3.0f};
    GLfloat diffuseLight[] = {1.0f, 1.0f, 1.0f, 3.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.0, 1.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(1.0, 0.75, 0.8, 1.0);
}
// Fungsi untuk update animasi
void update(int value)
{
    if (isMoving)
        movement.rotateY += 1.0f;

    glutPostRedisplay();
    glutTimerFunc(1000 / 60, update, 0);
}

// Fungsi menu
void processMenu(int option)
{
    switch (option)
    {
    case 1:
        isMoving = !isMoving;
        break;
    case 2:
        exit(0);
        break;
    }
}

// Buat menu
void createMenu()
{
    glutCreateMenu(processMenu);
    glutAddMenuEntry("MANUAL", 1);
    glutAddMenuEntry("Exit", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// Tangani keyboard
void handleKeyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
        movement.translateY += 1.0f;
        break;
    case 's':
        movement.translateY -= 1.0f;
        break;
    case 'a':
        movement.translateX -= 1.0f;
        break;
    case 'd':
        movement.translateX += 1.0f;
        break;
    case '+':
        movement.scale += 0.1f;
        break;
    case '-':
        movement.scale -= 0.1f;
        break;
    case 'r':
        isMoving = !isMoving;
        break;
    case 'c': 
        showCartesius = !showCartesius;
        break;
    case 27: // ESC
        exit(0);
        break;
    }
}

// Tangani keyboard khusus
void handleSpecialKeyboard(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        movement.rotateX -= 5.0f;
        break;
    case GLUT_KEY_DOWN:
        movement.rotateX += 5.0f;
        break;
    case GLUT_KEY_LEFT:
        movement.rotateY -= 5.0f;
        break;
    case GLUT_KEY_RIGHT:
        movement.rotateY += 5.0f;
        break;
    }
}

