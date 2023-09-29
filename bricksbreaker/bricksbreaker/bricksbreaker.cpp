#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
static GLfloat shooter[5][2] = { {40,10},{80,10},{80,15},{60,19.5},{40,15} };
static GLfloat bul[20][2] = { {0,600},{0,600},{0,600},{0,600},{0,600},{0,600},{0,600},{0,600},{0,600},{0,600},{0,600},{0,600},{0,600},{0,600},{0,600},{0,600},{0,600},{0,600},{0,600},{0,600} };
GLint y00 = 580, y01 = 560;

typedef struct
{
    int x1, y1, x2, y2;
    int color;
    int lives;
}bricktype;
bricktype br[15][29];
GLfloat colorarr[][4] = { {0.8,0.8,0.8},{1.0,0.0,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0} };
int currbullet = 6;

void brick(int x0, int y0, int x1, int y1, int col) {

    br[x0 / 40][y0 / 20].x1 = x0;
    br[x0 / 40][y0 / 20].y1 = y0;
    br[x0 / 40][y0 / 20].x2 = x1;
    br[x0 / 40][y0 / 20].y2 = y1;
    br[x0 / 40][y0 / 20].color = col;
    br[x0 / 40][y0 / 20].lives = col;
}
int brickline(int y0, int y1)
{
    int x0 = 0, x1 = 40, i;
    int x;
    for (i = 0; i < 15; i++)
    {
        x = 1 + rand() % 3;
        brick(x0, y0, x1, y1, x);
        x0 = x0 + 40;
        x1 = x1 + 40;

    }

    return 1;
}
void translatedown()
{
    int x0, y0;
    for (x0 = 0; x0 <= 560; x0 += 40)
        for (y0 = 100; y0 <= 580; y0 += 20)
        {
            br[x0 / 40][(y0 - 20) / 20].x1 = br[x0 / 40][y0 / 20].x1;
            br[x0 / 40][(y0 - 20) / 20].y1 = br[x0 / 40][y0 / 20].y1 - 20;
            br[x0 / 40][(y0 - 20) / 20].x2 = br[x0 / 40][y0 / 20].x2;
            br[x0 / 40][(y0 - 20) / 20].y2 = br[x0 / 40][y0 / 20].y2 - 20;
            br[x0 / 40][(y0 - 20) / 20].color = br[x0 / 40][y0 / 20].color;
            br[x0 / 40][(y0 - 20) / 20].lives = br[x0 / 40][y0 / 20].lives;
        }
}
//static int y0 = 580, y1 = 560;
/*void brickloop(int x)
{


               glutTimerFunc(2000,brickloop,20);
}
*/
void bullet(int currbullet)
{
    currbullet += 1;
    currbullet = currbullet % 20;


    bul[currbullet][0] = shooter[3][0];
    bul[currbullet][1] = shooter[3][1];
    if (currbullet % 2 == 0)
    {
        translatedown();
        brickline(y00, y01);
    }
    glutTimerFunc(1000, bullet, 1);
}
void idle()
{
    int i;
    for (i = 0; i < 10; i++)
    {
        bul[i][1] += 2;
        if ((bul[i][1] < 600) && (br[((int)bul[i][0]) / 40][((int)bul[i][1]) / 20].lives > 0))
        {
            br[((int)bul[i][0]) / 40][((int)bul[i][1]) / 20].lives -= 1;
            //br[((int)bul[i][0])/40][((int)bul[i][1])/20].color=0;
            bul[i][0] = shooter[3][0];
            bul[i][1] = shooter[3][1];
            /*	  bul[i][0]=0;
                  bul[i][1]=600;*/
            glutPostRedisplay();
        }
    }

    glutPostRedisplay();
}
void gun() {
    glColor3f(1.0, 0.6, 0.1);
    glBegin(GL_POLYGON);
    glVertex2f(shooter[0][0], shooter[0][1]);
    glVertex2f(shooter[1][0], shooter[1][1]);
    glVertex2f(shooter[2][0], shooter[2][1]);
    glVertex2f(shooter[3][0], shooter[3][1]);
    glVertex2f(shooter[4][0], shooter[4][1]);
    glEnd();
    glFlush();
}
void drawbricks()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    int x0, y0;
    for (x0 = 0; x0 <= 560; x0 += 40)
        for (y0 = 580; y0 >= 100; y0 -= 20)
        {
            if (br[x0 / 40][y0 / 20].lives >= 1)
            {
                glColor3fv(colorarr[br[x0 / 40][y0 / 20].color]);
                glBegin(GL_POLYGON);
                glVertex2i(br[x0 / 40][y0 / 20].x1, br[x0 / 40][y0 / 20].y1);
                glVertex2i(br[x0 / 40][y0 / 20].x2, br[x0 / 40][y0 / 20].y1);
                glVertex2i(br[x0 / 40][y0 / 20].x2, br[x0 / 40][y0 / 20].y2);
                glVertex2i(br[x0 / 40][y0 / 20].x1, br[x0 / 40][y0 / 20].y2);
                glEnd();
            }
            else {
                glColor3fv(colorarr[0]);
                glBegin(GL_POLYGON);
                glVertex2i(br[x0 / 40][y0 / 20].x1, br[x0 / 40][y0 / 20].y1);
                glVertex2i(br[x0 / 40][y0 / 20].x2, br[x0 / 40][y0 / 20].y1);
                glVertex2i(br[x0 / 40][y0 / 20].x2, br[x0 / 40][y0 / 20].y2);
                glVertex2i(br[x0 / 40][y0 / 20].x1, br[x0 / 40][y0 / 20].y2);
                glEnd();
            }
        }
    gun();
}

void drawString(float x, float y, float z, char* string)
{
    char* c;
    glRasterPos3f(x, y, z);
    for (c = string; *c != '\0'; c++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,  *c);
}
void page1()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 0.0);
    drawString(200, 550, 0,  (char*)"JNN COLLEGE OF ENGINEERING");
    glColor3f(1.0, 1.0, 0.0);
    drawString(160, 515, 0.0, (char*)"DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING");
     glColor3f(1.0, 0.0, 0);
    drawString(225, 460, 0.0, (char*)"A MINI PROJECT ON ");
     glColor3f(1.0, 0.0, 1.0);
    drawString(205, 430, 0.0, (char*)"BRICKS BREAKER GAME");
     glColor3f(1.0, 0.7, 0.8);
     drawString(270, 380, 0.0, (char*)"Submitted by");
     glColor3f(0.0, 1.0, 1.0);
     drawString(200, 355, 0.0, (char*)" Bhavana RM");
     drawString(300, 355, 0.0, (char*)" 4JN20CS022");
     drawString(200, 330, 0.0, (char*)" Dhathri Krishna V");
     drawString(300, 330, 0.0, (char*)" 4JN20CS028");
     drawString(200, 305, 0.0, (char*)" Nisarga S  ");
     drawString(300, 305, 0.0, (char*)" 4JN20CS066");
     drawString(200, 280, 0.0, (char*)" Pooja B ");
     drawString(300, 280, 0.0, (char*)" 4JN20CS069");
     glColor3f(1.0, 0.0, 0.0);
     drawString(225, 240, 0.0, (char*)"Under the Guidance of");
     glColor3f(0.0, 1.0, 1.0);
     drawString(200, 215, 0.0, (char*)"Mrs.Sushma R B");
     drawString(200, 190, 0.0, (char*)"Asst. Proffessor");
     drawString(200, 165, 0.0, (char*)"Dept. of CS&E");
     glColor3f(1.0, 0.0, 0.0);
     drawString(200, 135, 0.0, (char*)"Academic Year 2023-2024");
     glColor3f(1.0, 1.0, 1.0);
     drawString(250, 100, 0.0, (char*)"Press r to continue");
    glFlush();
    glPopMatrix();
    glutSwapBuffers();
    glutPostRedisplay();
}
void page2()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 1.0);
    drawString(225, 430, 0.0, (char*)"BRICKS BREAKER GAME");
    glColor3f(1.0, 1.0, 0.0);
    drawString(250, 380, 0.0, (char*)"Rules");
    glColor3f(0.0, 1.0, 1.0);
    drawString(200, 345, 0.0, (char*)"Press Left Arrow to move ");
    drawString(220, 305, 0.0, (char*)" paddle to left side");
    drawString(200, 260, 0.0, (char*)" Press Right Arrow to move");
    drawString(220, 220, 0.0, (char*)"  paddle to right side");
    glColor3f(1.0, 0.0, 0.0);
    drawString(200, 160, 0.0, (char*)"Press q to QUIT");
    glColor3f(1.0, 0.0, 0.0);
    drawString(200, 120, 0.0, (char*)"Press s to START");
    glFlush();
    glPopMatrix();
    glutSwapBuffers();
    glutPostRedisplay();

}


void page3() {
    glClearColor(0.8, 0.8, 0.8, 1.0);
    drawbricks();
    for (int i = 0; i < 10; i++)
    {
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_POINTS);
        glVertex2d(bul[i][0], bul[i][1]);
        glEnd();
    }
    gun();
    glFlush();
    glPopMatrix();
    glutSwapBuffers();
    glutPostRedisplay();
}

void display()
{
    int i;
    glClear(GL_COLOR_BUFFER_BIT);
    page1();
}
void myinit()
{
    int x0, y0;
    glClearColor(0.0,0.0,0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(7.0);
    gluOrtho2D(0.0, 599.0, 0.0, 599.0);

    for (x0 = 0; x0 <= 560; x0 += 40)
        for (y0 = 580; y0 >= 100; y0 -= 20)
        {
            br[x0 / 40][y0 / 20].x1 = 0;
            br[x0 / 40][y0 / 20].y1 = 0;
            br[x0 / 40][y0 / 20].x2 = 0;
            br[x0 / 40][y0 / 20].y2 = 0;
            br[x0 / 40][y0 / 20].color = 0;
            br[x0 / 40][y0 / 20].lives = 0;
        }
}
void Keys(int key, int x, int y) {
    int j;

    switch (key) {
    case GLUT_KEY_LEFT:if (shooter[0][0] >= 40) {
        for (j = 0; j < 5; j++)
            shooter[j][0] -= 40;
        glutPostRedisplay();
    }break;
    case GLUT_KEY_RIGHT:if (shooter[0][0] < 560) {
        for (j = 0; j < 5; j++)
            shooter[j][0] += 40;
        glutPostRedisplay();
    }break;
    }
}
void keyb(unsigned char key, int x, int y) {
    switch (key) {
    case 's':
        glutDisplayFunc(page3);
        break;
    case 'r':glutDisplayFunc(page2);
        break;
    case 'q':exit(0);
    }
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("brickbreaker");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyb);
    glutTimerFunc(1000, bullet, 1);
    glutIdleFunc(idle);
    glutSpecialFunc(Keys);
    myinit();
    glutMainLoop();
    return 0;
}