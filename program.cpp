

#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <GL/glut.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <sstream>

using namespace std;

bool keys[256]; //represents keyboard keys (true when pressed)
int mouseX, mouseY, mButton = -1, mState = -1; //mouse info

int health = 170;
int alpacay=-100;
int jumpLimit = 250;
int score = 1;
int level = 1;
int birdx = 600;
int flowerx=600;
int r = 1;

bool Jumping, Falling, JumpOK;
bool startscreens = true;
bool Duck;
bool start, hit, pass;
bool NotDucking = TRUE;
bool GameOver;
bool PlayerStart = false;
bool GameStart = true;

void print_bitmap_string(char* s) {
    while (*s) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *s);
        s++;
    }
}
void print_bitmap_int(char* s, int score) {
    while (*s) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *s);
        s++;
    }
    string scorestring = to_string(score);
    for (int i = 0; i <scorestring.length(); i++) {
       glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scorestring[i]);
    }
}

void drawWinText() {
    char* bitmap_font_names[7] = {"ALPACA ON THE RUN"};
    glColor3f(255,255,255);
    glRasterPos2f(-500, -270);
    print_bitmap_string(bitmap_font_names[0]);
    char* bitmap_font_names1[7] = {"HEALTH:"};
    glColor3f(255,255,255);
    glRasterPos2f(300, 300);
    print_bitmap_string(bitmap_font_names1[0]);
    char* bitmap_font_names2[10000] = {"SCORE:"}; //+ charScore
    glColor3f(255,255,255);
    glRasterPos2f(300, -300);
    print_bitmap_int(bitmap_font_names2[0], score);
     char* bitmap_font_names3[10000] = {"LEVEL:"}; //+IntToChar(level)
        glColor3f(255,255,255);
    glRasterPos2f(-500, -300);
    print_bitmap_int(bitmap_font_names3[0], level);

    if (health <= 0) {
    char* bitmap_font_names3[7] = {"GAME OVER!"}; //+IntToChar(level)
    glColor3f(255,255,255);
    glRasterPos2f(300, 270);
    print_bitmap_string(bitmap_font_names3[0]);
    }
}

void drawStartScreenText() {
    char* bitmap_font_names[7] = {"Welcome to Alpaca on the Run!"};
    glColor3f(255,255,255);
    glRasterPos2f(-200, 300);
    print_bitmap_string(bitmap_font_names[0]);
    char* bitmap_font_names1[7] = {"Press 'X' to begin the game"};
    glColor3f(255,255,255);
    glRasterPos2f(-200, 250);
    print_bitmap_string(bitmap_font_names1[0]);
    char* bitmap_font_names2[10000] = {"Press 'SPACE' to Jump"}; //+ charScore
    glColor3f(255,255,255);
    glRasterPos2f(-200, 200);
    print_bitmap_string(bitmap_font_names2[0]);
     char* bitmap_font_names3[10000] = {"'D' to Duck, 'U' to go back up!"}; //+IntToChar(level)
        glColor3f(255,255,255);
    glRasterPos2f(-200, 150);
    print_bitmap_string(bitmap_font_names3[0]);
}

void drawEndScreenText() {
    char* bitmap_font_names[7] = {"Game Over!"};
    glColor3f(255,255,255);
    glRasterPos2f(-200, 300);
    print_bitmap_string(bitmap_font_names[0]);
    char* bitmap_font_names1[7] = {"SCORE:"};
    glColor3f(255,255,255);
    glRasterPos2f(-200, 250);
    print_bitmap_int(bitmap_font_names1[0], score);
    char* bitmap_font_names3[7] = {"LEVEL:"};
    glColor3f(255,255,255);
    glRasterPos2f(-200, 200);
    print_bitmap_int(bitmap_font_names3[0], level);
    char* bitmap_font_names2[10000] = {"Press 'X' to play again"}; //+ charScore
    glColor3f(255,255,255);
    glRasterPos2f(-200, 100);
    print_bitmap_string(bitmap_font_names2[0]);
}



void healthbox() {
glColor3f(0,0,0);
glBegin(GL_QUADS);
                    glVertex2d(280, 230);
                    glVertex2d(280, 340);
                    glVertex2d(500, 340);
                    glVertex2d(500, 230);
                glEnd();
}

void alpaca(double x, double y, double width, double height) {

glColor3f(255, 255, 255); // neck
glBegin(GL_QUADS);
                    glVertex2d(x-20, y-50); // x -400, y -100, width 100, height 200
                    glVertex2d(x-20, y+height-70); // -400, 100
                    glVertex2d(x+width-60, y+height-70); // -300, 100
                    glVertex2d(x+width-60, y-50); // -300, -100
                glEnd();

glColor3f(255, 255, 255); // face
glBegin(GL_QUADS);
                    glVertex2d(x+40, y+70); // -400, 50
                    glVertex2d(x+40, y+140); // -400, 150
                    glVertex2d(x-40, y+140); // -450, 150
                    glVertex2d(x-40, y+70); // -450, 50
                glEnd();

glColor3f(255, 255, 255); // white ear
glBegin(GL_QUADS);
                    glVertex2d(x-20, y+70); // -400, 50
                    glVertex2d(x-20, y+150); // -400, 150
                    glVertex2d(x-30, y+150); // -450, 150
                    glVertex2d(x-30, y+70); // -450, 50
                glEnd();

glColor3f(160/255.0, 160/255.0, 160/255.0); // grey ear
glBegin(GL_QUADS);
                    glVertex2d(x+10, y+140); // -400, 50
                    glVertex2d(x+10, y+150); // -400, 150
                    glVertex2d(x, y+150); // -450, 150
                    glVertex2d(x, y+140); // -450, 50
                glEnd();

glColor3f(255, 255, 255); // body
glBegin(GL_QUADS);
                    glVertex2d(x-150, y-60); // -700, -100
                    glVertex2d(x-150, y+20); // -700, 50
                    glVertex2d(x+40, y+20); // -300, 50
                    glVertex2d(x+40, y-60); // -300, -100
                glEnd();

// left leg
glColor3f(255, 255, 255);
glBegin(GL_QUADS);
                    glVertex2d(x-140, y); // -700, -100
                    glVertex2d(x-140, y-100); // -700, 50
                    glVertex2d(x-120, y-100); // -300, 50
                    glVertex2d(x-120, y); // -300, -100
                glEnd();

// left leg grey
glColor3f(160/255.0, 160/255.0, 160/255.0);
glBegin(GL_QUADS);
                    glVertex2d(x-110, y-60); // -700, -100
                    glVertex2d(x-110, y-100); // -700, 50
                    glVertex2d(x-90, y-100); // -300, 50
                    glVertex2d(x-90, y-60); // -300, -100
                glEnd();

// right leg
glColor3f(255, 255, 255);
glBegin(GL_QUADS);
                    glVertex2d(x-30, y); // -700, -100
                    glVertex2d(x-30, y-100); // -700, 50
                    glVertex2d(x-10, y-100); // -300, 50
                    glVertex2d(x-10, y); // -300, -100
                glEnd();

// right leg
glColor3f(160/255.0, 160/255.0, 160/255.0);
glBegin(GL_QUADS);
                    glVertex2d(x, y-60); // -700, -100
                    glVertex2d(x, y-100); // -700, 50
                    glVertex2d(x+20, y-100); // -300, 50
                    glVertex2d(x+20, y-60); // -300, -100
                glEnd();

//face skin
glColor3f(204/255.0, 153/255.0, 0);
glBegin(GL_QUADS);
                    glVertex2d(x+40, y+85); // -400, 50
                    glVertex2d(x+40, y+120); // -400, 150
                    glVertex2d(x-10, y+120); // -450, 150
                    glVertex2d(x-10, y+85); // -450, 50
                glEnd();
// second face skin
glBegin(GL_QUADS);
                    glVertex2d(x+50, y+70); // -400, 50
                    glVertex2d(x+50, y+100); // -400, 150
                    glVertex2d(x, y+100); // -450, 150
                    glVertex2d(x, y+70); // -450, 50
                glEnd();
glColor3f(0, 0, 0); // eye
glBegin(GL_QUADS);
                    glVertex2d(x+15, y+110); // -400, 50
                    glVertex2d(x+15, y+100); // -400, 150
                    glVertex2d(x+5, y+100); // -450, 150
                    glVertex2d(x+5, y+110); // -450, 50
                glEnd();

glColor3f(0, 0, 0); // mouth
glBegin(GL_QUADS);
                    glVertex2d(x+20, y+80); // -400, 50
                    glVertex2d(x+20, y+90); // -400, 150
                    glVertex2d(x+50, y+90); // -450, 150
                    glVertex2d(x+50, y+80); // -450, 50
                glEnd();

}

void alpacaduck(double x, double y, double width, double height) {

glColor3f(255, 255, 255); // neck
glBegin(GL_QUADS);
                    glVertex2d(x+10, y-30); // x -400, y -100, width 100, height 200
                    glVertex2d(x+10, y+height-180); // -400, 100
                    glVertex2d(x+width+20, y+height-180); // -300, 100
                    glVertex2d(x+width+20, y-30); // -300, -100
                glEnd();

glColor3f(255, 255, 255); // face
glBegin(GL_QUADS);
                    glVertex2d(x+40+100, y+70-100); // -400, 50
                    glVertex2d(x+40+100, y+140-100); // -400, 150
                    glVertex2d(x-40+100, y+140-100); // -450, 150
                    glVertex2d(x-40+100, y+70-100); // -450, 50
                glEnd();

glColor3f(255, 255, 255); // white ear
glBegin(GL_QUADS);
                    glVertex2d(x-20+100, y+70-100); // -400, 50
                    glVertex2d(x-20+100, y+150-100); // -400, 150
                    glVertex2d(x-30+100, y+150-100); // -450, 150
                    glVertex2d(x-30+100, y+70-100); // -450, 50
                glEnd();

glColor3f(160/255.0, 160/255.0, 160/255.0); // grey ear
glBegin(GL_QUADS);
                    glVertex2d(x+10+100, y+140-100); // -400, 50
                    glVertex2d(x+10+100, y+150-100); // -400, 150
                    glVertex2d(x+100, y+150-100); // -450, 150
                    glVertex2d(x+100, y+140-100); // -450, 50
                glEnd();

glColor3f(255, 255, 255); // body
glBegin(GL_QUADS);
                    glVertex2d(x-150, y-60); // -700, -100
                    glVertex2d(x-150, y+20); // -700, 50
                    glVertex2d(x+40, y+20); // -300, 50
                    glVertex2d(x+40, y-60); // -300, -100
                glEnd();

// left leg
glColor3f(255, 255, 255);
glBegin(GL_QUADS);
                    glVertex2d(x-140, y); // -700, -100
                    glVertex2d(x-140, y-100); // -700, 50
                    glVertex2d(x-120, y-100); // -300, 50
                    glVertex2d(x-120, y); // -300, -100
                glEnd();

// left leg grey
glColor3f(160/255.0, 160/255.0, 160/255.0);
glBegin(GL_QUADS);
                    glVertex2d(x-110, y-60); // -700, -100
                    glVertex2d(x-110, y-100); // -700, 50
                    glVertex2d(x-90, y-100); // -300, 50
                    glVertex2d(x-90, y-60); // -300, -100
                glEnd();

// right leg
glColor3f(255, 255, 255);
glBegin(GL_QUADS);
                    glVertex2d(x-30, y); // -700, -100
                    glVertex2d(x-30, y-100); // -700, 50
                    glVertex2d(x-10, y-100); // -300, 50
                    glVertex2d(x-10, y); // -300, -100
                glEnd();

// right leg
glColor3f(160/255.0, 160/255.0, 160/255.0);
glBegin(GL_QUADS);
                    glVertex2d(x, y-60); // -700, -100
                    glVertex2d(x, y-100); // -700, 50
                    glVertex2d(x+20, y-100); // -300, 50
                    glVertex2d(x+20, y-60); // -300, -100
                glEnd();

//face skin
glColor3f(204/255.0, 153/255.0, 0);
glBegin(GL_QUADS);
                    glVertex2d(x+40+100, y+85-100); // -400, 50
                    glVertex2d(x+40+100, y+120-100); // -400, 150
                    glVertex2d(x-10+100, y+120-100); // -450, 150
                    glVertex2d(x-10+100, y+85-100); // -450, 50
                glEnd();
// second face skin
glBegin(GL_QUADS);
                    glVertex2d(x+50+100, y+70-100); // -400, 50
                    glVertex2d(x+50+100, y+100-100); // -400, 150
                    glVertex2d(x+100, y+100-100); // -450, 150
                    glVertex2d(x+100, y+70-100); // -450, 50
                glEnd();
glColor3f(0, 0, 0); // eye
glBegin(GL_QUADS);
                    glVertex2d(x+15+100, y+110-100); // -400, 50
                    glVertex2d(x+15+100, y+100-100); // -400, 150
                    glVertex2d(x+5+100, y+100-100); // -450, 150
                    glVertex2d(x+5+100, y+110-100); // -450, 50
                glEnd();

glColor3f(0, 0, 0); // mouth
glBegin(GL_QUADS);
                    glVertex2d(x+20+100, y+80-100); // -400, 50
                    glVertex2d(x+20+100, y+90-100); // -400, 150
                    glVertex2d(x+50+100, y+90-100); // -450, 150
                    glVertex2d(x+50+100, y+80-100); // -450, 50
                glEnd();

}

void bird(double x, double y, double width, double height) {
glColor3f(255, 255, 255);
glBegin(GL_QUADS);
                    glVertex2d(birdx, y);
                    glVertex2d(birdx, y+height);
                    glVertex2d(birdx+width-5, y+height);
                    glVertex2d(birdx+width-5, y);
                glEnd();

glBegin(GL_QUADS);
                    glVertex2d(birdx+20, y);
                    glVertex2d(birdx+20, y+height-20);
                    glVertex2d(birdx+width+15, y+height-20);
                    glVertex2d(birdx+width+15, y);
                glEnd();
glBegin(GL_QUADS);
                    glVertex2d(birdx+25, y);
                    glVertex2d(birdx+25, y+height-30);
                    glVertex2d(birdx+width+10, y+height-30);
                    glVertex2d(birdx+width+10, y);
                glEnd();

glBegin(GL_QUADS);
                    glVertex2d(birdx+40, y);
                    glVertex2d(birdx+40, y+height);
                    glVertex2d(birdx+width+35, y+height);
                    glVertex2d(birdx+width+35, y);
                glEnd();

}

void sky(double x, double y, double width, double height) {
glColor3f(0, 204/255.0, 255);
glBegin(GL_QUADS);
                    glVertex2d(x, y);
                    glVertex2d(x, y+height);
                    glVertex2d(x+width, y+height);
                    glVertex2d(x+width, y);
                glEnd();
}

void grass(double x, double y, double width, double height) {
glColor3f(0, 204/255.0, 0);
glBegin(GL_QUADS);
                    glVertex2d(x, y);
                    glVertex2d(x, y+height);
                    glVertex2d(x+width, y+height);
                    glVertex2d(x+width, y);
                glEnd();
}

void flower (double x, double y, double width, double height){

glColor3f(0, 204/255.0, 0); //stem
glBegin(GL_QUADS);
                    glVertex2d(x, y); //stem
                    glVertex2d(x, y+height-20);
                    glVertex2d(x+20, y+height-20);
                    glVertex2d(x+20, y);
                glEnd();

glColor3f(255, 255, 0); //yellow pollen
glBegin(GL_QUADS);
                    glVertex2d(x, y+height-20);
                    glVertex2d(x, y+height);
                    glVertex2d(x+20, y+height);
                    glVertex2d(x+20, y+height-20);
                glEnd();

glColor3f(255, 255, 255); //bottom petal
glBegin(GL_QUADS);
                    glVertex2d(x, y+height-40);
                    glVertex2d(x, y+height-20);
                    glVertex2d(x+20, y+height-20);
                    glVertex2d(x+20, y+height-40);
                glEnd();
glBegin(GL_QUADS); //top petal
                    glVertex2d(x, y+height+20);
                    glVertex2d(x, y+height);
                    glVertex2d(x+20, y+height);
                    glVertex2d(x+20, y+height+20);
                glEnd();
glBegin(GL_QUADS); //left petal
                    glVertex2d(x, y+height-20);
                    glVertex2d(x, y+height);
                    glVertex2d(x-20, y+height);
                    glVertex2d(x-20, y+height-20);
                glEnd();
glBegin(GL_QUADS); //right petal
                    glVertex2d(x+20, y+height-20);
                    glVertex2d(x+20, y+height);
                    glVertex2d(x+40, y+height);
                    glVertex2d(x+40, y+height-20);
                glEnd();


}

void tallflower (double x, double y, double width, double height){

glColor3f(0, 204/255.0, 0); //stem
glBegin(GL_QUADS);
                    glVertex2d(x, y);
                    glVertex2d(x, y+height);
                    glVertex2d(x+width, y+height);
                    glVertex2d(x+width, y);
                glEnd();
glColor3f(255, 255, 0); //yellow pollen
glBegin(GL_QUADS);
                    glVertex2d(x, y+height-20);
                    glVertex2d(x, y+height);
                    glVertex2d(x+20, y+height);
                    glVertex2d(x+20, y+height-20);
                glEnd();

glColor3f(255,20/255.0,147/255.0); //bottom petal
glBegin(GL_QUADS);
                    glVertex2d(x, y+height-40);
                    glVertex2d(x, y+height-20);
                    glVertex2d(x+20, y+height-20);
                    glVertex2d(x+20, y+height-40);
                glEnd();
glBegin(GL_QUADS); //top petal
                    glVertex2d(x, y+height+20);
                    glVertex2d(x, y+height);
                    glVertex2d(x+20, y+height);
                    glVertex2d(x+20, y+height+20);
                glEnd();
glBegin(GL_QUADS); //left petal
                    glVertex2d(x, y+height-20);
                    glVertex2d(x, y+height);
                    glVertex2d(x-20, y+height);
                    glVertex2d(x-20, y+height-20);
                glEnd();
glBegin(GL_QUADS); //right petal
                    glVertex2d(x+20, y+height-20);
                    glVertex2d(x+20, y+height);
                    glVertex2d(x+40, y+height);
                    glVertex2d(x+40, y+height-20);
                glEnd();


}

void bush (double x, double y, double width, double height){

glColor3f(144/255.0, 238/255.0, 144/255.0); //tiny bush
glBegin(GL_QUADS);
                    glVertex2d(x, y);
                    glVertex2d(x, y+height-30);
                    glVertex2d(x+width+50, y+height-30);
                    glVertex2d(x+width+50, y);
                glEnd();
glColor3f(144/255.0, 238/255.0, 144/255.0); //larger bush
glBegin(GL_QUADS);
                    glVertex2d(x+width+30, y);
                    glVertex2d(x+width+30, y+height+10);
                    glVertex2d(x+width+100, y+height+10);
                    glVertex2d(x+width+100, y);
                glEnd();

}

void healthbar (double x, double y, double width, double height) {

glColor3f(124/255.0,252/255.0,0);

if (health <100) {
    glColor3f(255,165/255.0,0);
}

if (health <30) {
    glColor3f(255,0,0);
}

glBegin(GL_QUADS);
                    glVertex2d(x, y);
                    glVertex2d(x, y+height);
                    glVertex2d(x+width, y+height);
                    glVertex2d(x+width, y);
                glEnd();

}

void randomnumgen() {

    srand (time(NULL));
r = rand() % 4 + 1; // random number between 1 and 4s
}

void reshape(int w, int h) {
    GLdouble size;
    GLdouble aspect;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    size = (GLdouble)((w >= h) ? w : h) / 2.0;
    if (w <= h) {
        aspect = (GLdouble)h/(GLdouble)w;
        glOrtho(-size, size, -size*aspect, size*aspect, -100000.0, 100000.0);
    }
    else {
        aspect = (GLdouble)w/(GLdouble)h;
        glOrtho(-size*aspect, size*aspect, -size, size, -100000.0, 100000.0);
    }
    glScaled(aspect, aspect, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void key(unsigned char key, int x, int y) // used for jump, space bar
{
switch(key)
{
case ' ':
if (!Falling && !Jumping) {
    JumpOK = TRUE;
}
if (JumpOK) {
 Jumping = true;
 JumpOK = false;
}
glutPostRedisplay();
break;

case 'd':
Duck = TRUE;
NotDucking = FALSE;
glutPostRedisplay();
break;

case 'u':
Duck = FALSE;
NotDucking = TRUE;
glutPostRedisplay();
break;

case 'x':
    PlayerStart = true;
    GameStart = false;
    GameOver = false;
    glutPostRedisplay();
break;

case 27:
     // glutDestroyWindow ("Alpaca On The Run");
      exit (0);
          glutPostRedisplay();
      break;

}

}
/*void keyUp(unsigned char key, int x, int y) {
    keys[key] = false; //set key state to false when released
}*/

void update(int value) { //moves the flower & jump?

    if (PlayerStart) {
    level = score/500;
    if (level == 0) {
        level = 1;
    }

    //flowerx -=10;
    //birdx -=10;
    if (level>1) {
     flowerx -=10*(level-0.5);
        birdx-=10*(level-0.5);
    }

    else {
             flowerx -=10*(level);
        birdx-=10*(level);
    }

     // tell GLUT that the display has changed
    // tell GLUT to call update again in 25 milliseconds
    if ((r == 1 || r == 2 || r == 3) && flowerx <= -340 && flowerx >= -360 && (!Jumping && !Falling)) { //&& flowerx <= -360
        flowerx=600;
        birdx=600;
        randomnumgen();
        health=health-20;
    }
    else {
        if ((r == 1 || r == 2 || r == 3) && flowerx <= -600) {
        flowerx = 600;
        birdx=600;
        randomnumgen();
        }
    }
        if (r == 4 && birdx <= -340 && birdx >= -380 && !Duck) { //&& flowerx <= -360
        birdx=600;
         flowerx=600;
        randomnumgen();
        health=health-20;
    }

    else {
        if (r == 4 && birdx <= -600) {
            birdx = 600;
             flowerx=600;
            randomnumgen();
        }
    }
    if (Jumping) {
        if (alpacay<=200) {
            alpacay = alpacay+20;
        }

        else if (alpacay<250) {
            alpacay = alpacay+5;
        }

        else {
            Jumping = FALSE;
            Falling = TRUE;
        }
    }
    if (Falling) {
        if (alpacay>0) {
            alpacay=alpacay-5;
        }
        if (alpacay>-100) {
            alpacay=alpacay-15;
        }
        else {
            Falling = FALSE;
            JumpOK = TRUE;
        }
    }
    if (health > 0 && health <= 170) {
    score++;
    }

            if (health <= 0) {
        GameOver = true;
        PlayerStart = false;
    }

glutPostRedisplay();
}
glutTimerFunc(25, update, 0);
}

void obstacles() {

if (r == 1) {
     flower(flowerx,-200,100,100);
}

if (r == 2) {
tallflower(flowerx,-200,20,180);
}

if (r == 3) {
bush(flowerx,-200,20,100);
}

if (r == 4) {
    bird(birdx,0,30,10);
}
}

void display(void) {
    //clear background
    //glMatrixMode();


    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (GameStart) {
        grass(-600,-400,1200,200);
        sky(-600,-200,1200,600);
    drawStartScreenText();
    glutSwapBuffers(); //swap frames
    }

    if (PlayerStart) {
         sky(-600,-200,1200,600);
    grass(-600,-400,1200,200);
    if (NotDucking) {
        alpaca(-400,alpacay,100,200);
    }

    if (Duck) {
        alpacaduck(-400,alpacay,100,200);
    }
    healthbox();
        if (health<=170 && health >=0) {
     healthbar(300,250,health,25);
    obstacles();
        }
    drawWinText();
    //run all game functions
    glutSwapBuffers(); //swap frames

    }

    if (GameOver) {
       sky(-600,-200,1200,600);
    grass(-600,-400,1200,200);
    drawEndScreenText();
    glutSwapBuffers(); //swap frames
    }
}

void mouse(int button, int state, int x, int y) {
    mButton = button;
    mouseX = x-750;
    mouseY = -y+400;
    mState = state;
//if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) cout << "\ndown @ " << x << ", " << y;
//else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) cout << "\nup @ " << x << ", " << y;
}

int main(int argc, char *argv[]) {
    glutInitWindowSize(1200, 800);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
    glutCreateWindow("Alpaca On The Run");
    glutTimerFunc(25, update, 0);
    glutDisplayFunc(display);
    glRasterPos2f(0., 0.); // for the text
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key);
    //glutKeyboardUpFunc(keyUp);
    glutMouseFunc(mouse);
    glViewport(0, 0, 1200, 800);
    glutMainLoop(); //run program
    return 0;
}
