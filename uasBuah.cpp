#include <iostream>
#include <GL/glut.h>
#include <GL/freeglut.h>
using namespace std;

// Struktur untuk rotasi
struct Movement
{
    float rotate;
} fruitRotation;

bool isMoving = true; // Status rotasi
float lightPos[] = {10.0f, 10.0f, 10.0f, 1.0f}; // Posisi cahaya

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
void drawApple();
void drawGrapes();

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
    glutTimerFunc(1000 / 60, update, 0);
    glutMainLoop();
    return 0;
}

void drawTable()
{
    glColor3ub(139, 69, 19); // Warna coklat untuk meja
    glPushMatrix();
    glTranslatef(0.0, -10.0, 0.0); // Posisi meja
    glScalef(1.8, 0.1, 1.0);       // Skala meja
    glutSolidCube(30.0);           // Bentuk meja (kubus besar)
    glPopMatrix();

    // Gambar kaki meja
    float legHeight = 15.0;
    float legSize = 2.0;
    glPushMatrix();
    glTranslatef(-13.0, -25.0, 13.0); // Posisi kaki pertama
    glScalef(legSize, legHeight, legSize);
    glutSolidCube(2.0); // Kaki pertama
    glPopMatrix();

    glPushMatrix();
    glTranslatef(13.0, -25.0, 13.0); // Posisi kaki kedua
    glScalef(legSize, legHeight, legSize);
    glutSolidCube(2.0); // Kaki kedua
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-13.0, -25.0, -13.0); // Posisi kaki ketiga
    glScalef(legSize, legHeight, legSize);
    glutSolidCube(2.0); // Kaki ketiga
    glPopMatrix();

    glPushMatrix();
    glTranslatef(13.0, -25.0, -131.0); // Posisi kaki keempat
    glScalef(legSize, legHeight, legSize);
    glutSolidCube(2.0); // Kaki keempat
    glPopMatrix();
}

// Fungsi menggambar piring
void drawPlate()
{
    glColor3ub(255, 255, 255); // Warna putih untuk piring
    
    // Bagian atas piring (donat)
    glPushMatrix();
    glTranslatef(0.0, -7.5, 0.0);      // Posisi piring di atas meja
    glRotatef(-90.0, 1.0, 0.0, 0.0);   // Piring dalam posisi datar
    glutSolidTorus(2.0, 12.0, 30, 30); // Ukuran torus diperbesar (donat)
    glPopMatrix();
    
    // Bagian bawah piring (disk solid)
    glColor3ub(255, 255, 255);         // Warna putih untuk bagian bawah piring
    glPushMatrix();
    glTranslatef(0.0, -7.6, 0.0);      // Posisi bagian bawah piring
    glRotatef(-90.0, 1.0, 0.0, 0.0);   // Piring dalam posisi datar
    glutSolidCylinder(12.0, 0.0, 30, 30); // Menggambar bagian bawah piring lebih besar
    glPopMatrix();
}



// Fungsi menggambar jeruk
void drawOrange()
{
    glColor3ub(255, 165, 0); // Warna oranye
    glutSolidSphere(5.0, 30, 30); // Ukuran diperkecil

    glPushMatrix();
    glColor3ub(139, 69, 19); // Warna coklat untuk tangkai
    glTranslatef(0.0, 5.5, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    GLUquadric *stem = gluNewQuadric();
    gluCylinder(stem, 0.2, 0.1, 1.5, 12, 6); // Tangkai lebih kecil
    gluDeleteQuadric(stem);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(34, 139, 34); // Warna hijau untuk daun
    glTranslatef(0.4, 6.0, 0.0);
    glRotatef(45.0, 0.0, 1.0, 0.0);
    glScalef(1.5, 0.05, 0.75); // Daun diperkecil
    glutSolidSphere(0.5, 20, 20);
    glPopMatrix();
}

void drawWatermelonSlice()
{
    // Bagian daging semangka (merah)
    glPushMatrix();
    glColor3ub(255, 0, 0); // Warna merah untuk daging semangka
    glRotatef(-90.0, 1.0, 0.0, 0.0); // Rotasi agar kerucut datar
    glutSolidCone(5.0, 10.0, 30, 30); // Kerucut dengan radius 5 dan tinggi 10
    glPopMatrix();

    // Bagian kulit semangka (hijau)
    glPushMatrix();
    glColor3ub(34, 139, 34); // Warna hijau untuk kulit semangka
    glTranslatef(0.0, -0.1, 0.0); // Sedikit di bawah daging semangka
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    glutSolidTorus(0.3, 5.0, 30, 30); // Torus tipis untuk kulit semangka
    glPopMatrix();

    // Biji semangka (hitam)
    for (float x = -2.0; x <= 2.0; x += 1.0)
    {
        for (float z = -3.0; z <= 1.0; z += 1.5)
        {
            glPushMatrix();
            glColor3ub(0, 0, 0); // Warna hitam untuk biji
            glTranslatef(x, 3.0 - z, z); // Posisi biji di atas daging
            glutSolidSphere(0.2, 10, 10); // Biji kecil
            glPopMatrix();
        }
    }
}

// Fungsi menggambar apel
void drawApple()
{
    glColor3ub(255, 0, 0); // Warna merah
    glutSolidSphere(4.0, 30, 30); // Ukuran diperkecil

    glPushMatrix();
    glColor3ub(139, 69, 19); // Warna coklat untuk tangkai
    glTranslatef(0.0, 4.5, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    GLUquadric *stem = gluNewQuadric();
    gluCylinder(stem, 0.1, 0.05, 1.0, 12, 6); // Tangkai lebih kecil
    gluDeleteQuadric(stem);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(34, 139, 34); // Warna hijau untuk daun
    glTranslatef(-0.3, 4.5, 0.0);
    glRotatef(30.0, 0.0, 1.0, 0.0);
    glScalef(1.5, 0.05, 0.6); // Daun diperkecil
    glutSolidSphere(0.5, 20, 20);
    glPopMatrix();
}

// Fungsi menggambar anggur
void drawGrapes()
{
    glColor3ub(128, 0, 128); // Warna ungu

    // Gambar kelompok anggur
    for (float x = -1.0; x <= 1.0; x += 0.8)
    {
        for (float y = -0.5; y <= 1.0; y += 0.8)
        {
            glPushMatrix();
            glTranslatef(x * 1.5, y * 1.5, 0.0); // Rapatkan posisi anggur
            glutSolidSphere(1.0, 20, 20); // Ukuran diperkecil
            glPopMatrix();
        }
    }

    // Gambar tangkai anggur
    glPushMatrix();
    glColor3ub(139, 69, 19); // Warna coklat
    glTranslatef(0.0, 3.0, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    GLUquadric *stem = gluNewQuadric();
    gluCylinder(stem, 0.1, 0.05, 2.0, 12, 6); // Tangkai lebih kecil
    gluDeleteQuadric(stem);
    glPopMatrix();

    // Gambar daun
    glPushMatrix();
    glColor3ub(34, 139, 34); // Warna hijau
    glTranslatef(0.2, 3.5, 0.0);
    glRotatef(30.0, 0.0, 1.0, 0.0);
    glScalef(1.5, 0.05, 0.75); // Daun diperkecil
    glutSolidSphere(0.5, 20, 20);
    glPopMatrix();
}

    
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    // Gambar meja
    drawTable();

    // Gambar piring di atas meja
    drawPlate();

    // Gambar semangka (pindahkan sebelum jeruk)
    glPushMatrix();
    glTranslatef(-5.0, -5.0, 0.0); // Letakkan semangka sebelum jeruk
    drawWatermelonSlice();
    glPopMatrix();

    // Gambar jeruk
    glPushMatrix();
    glTranslatef(0.0, -5.0, 0.0); // Letakkan jeruk di sebelah semangka
    drawOrange();
    glPopMatrix();

    // Gambar apel
    glPushMatrix();
    glTranslatef(5.0, -5.0, 0.0); // Letakkan apel di atas piring
    drawApple();
    glPopMatrix();

    // Gambar anggur
    glPushMatrix();
    glTranslatef(10.0, -5.0, 0.0); // Letakkan anggur di sebelah apel
    drawGrapes();
    glPopMatrix();

    glutSwapBuffers();
}


// Inisialisasi pencahayaan dan pengaturan 3D
void init3D()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
    GLfloat diffuseLight[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.0, 1.0, 1.0, 100.0);
    gluLookAt(30.0, 30.0, 50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(1.0, 1.0, 1.0, 1.0); 
}

// Fungsi proses menu
void processMenu(int option) {
    switch (option) {
    case 1:
        isMoving = !isMoving;
        break;
    case 2:
        exit(0);
    }
    glutPostRedisplay();
}

// Fungsi untuk membuat menu
void createMenu() {
    glutCreateMenu(processMenu);
    glutAddMenuEntry("Hentikan/Putar Rotasi", 1);
    glutAddMenuEntry("Keluar", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// Fungsi untuk memperbarui rotasi
void update(int value) {
    if (isMoving) {
        fruitRotation.rotate += 0.15;
    }
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, update, 0);
}
