// Made by Md. Taufiqur Rahman Shagor
// BUET CSE 23
// Roll:2305096
#include "iGraphics.h"
#include <stdio.h>
#include <string.h>
int name_input = 1, len = 0;
char str1[100];

int x = 300, y = 300, r = 20, dy = 8;
int level = 100, menu = 0, mode = 1, sound = 0;
int x1 = 650, x2 = 820, x3 = 990, x4 = 1160;
int y5 = 380, y2 = 350, y3 = 315, y4 = 380;
int bar1 = 0, bar2 = 1, bar3 = 2, bar4 = 3;
int score = 0, timer1, timer2;
int coinx = x1 + 80, coiny = y5 - 50;
int bombx = 900, bomby = 300, lifex = 1050, lifey = 320;
int life = 3;
char lifeArray[1000];
char scoRe[1000];

char image[3][30] = {"Picture\\1.bmp", "Picture\\2.bmp", "Picture\\3.bmp"};
char bardown[4][50] = {"Picture\\bar1.bmp", "Picture\\bar2.bmp", "Picture\\bar3.bmp", "Picture\\bar4.bmp"};

int im = 0;
int start = 0;

// leaderboard function
void leaderboard()
{

    FILE *read = fopen("leaderboard.txt", "r");
    if (read == NULL)
    {
        printf("Could not open file\n");
        return;
    }
    char temp[1000];
    int i = 0;
    char name[10][100];
    char result[1000] = "";
    int point[10];
    while (fgets(temp, sizeof(temp), read) != NULL && i < 10)
    {
        sscanf(temp, "%s %d", name[i], &point[i]);
        i++;
    }
    fclose(read);

    if (score > point[0])
    {
        strcpy(name[4], name[3]);
        point[4] = point[3];
        strcpy(name[3], name[2]);
        point[3] = point[2];
        strcpy(name[2], name[1]);
        point[2] = point[1];
        strcpy(name[1], name[0]);
        point[1] = point[0];
        strcpy(name[0], str1);
        point[0] = score;
    }
    if (score > point[1] && score < point[0])
    {
        strcpy(name[4], name[3]);
        point[4] = point[3];
        strcpy(name[3], name[2]);
        point[3] = point[2];
        strcpy(name[2], name[1]);
        point[2] = point[1];
        strcpy(name[1], str1);
        point[1] = score;
    }
    else if (score > point[2] && score < point[0] && score < point[1])
    {
        strcpy(name[4], name[3]);
        point[4] = point[3];
        strcpy(name[3], name[2]);
        point[3] = point[2];
        strcpy(name[2], str1);
        point[2] = score;
    }
    else if (score > point[3] && score < point[0] && score < point[1] && score < point[2])
    {
        strcpy(name[4], name[3]);
        point[4] = point[3];
        strcpy(name[3], str1);
        point[3] = score;
    }
    else if (score > point[4] && score < point[1] && score < point[2] && score < point[3] && score < point[0])
    {
        strcpy(name[4], str1);
        point[4] = score;
    }
    int j = 0;

    char fileup[1000] = "";
    while (j < 5)
    {
        sprintf(temp, "        %d%c %s %c %d\n", j + 1, '.', name[j], '-', point[j]);
        strcat(result, temp);
        sprintf(temp, "%s %d \n", name[j], point[j]);
        strcat(fileup, temp);
        j++;
    }
    iSetColor(255, 255, 255);
    iRectangle(90, 90, 450, 80);
    char lead[] = "Leaderboard:";
    iText(250, 150, lead, GLUT_BITMAP_TIMES_ROMAN_24);
    iText(100, 100, result, GLUT_BITMAP_TIMES_ROMAN_24);

    FILE *write = fopen("leaderboard.txt", "w");
    if (write == NULL)
    {
        printf("Could not open file\n");
        return;
    }
    fputs(fileup, write);
    fclose(write);
}

// function iDraw() is called again and again by the system.

void iDraw()
{
    iClear();
    // menu bar

    if (menu == 0)
    {
        iShowBMP(0, 0, "Picture//homebar.bmp");
        iShowBMP(100, 100, "Picture//button.bmp");
        iShowBMP(200, 100, "Picture//mode.bmp");
        iShowBMP(300, 100, "Picture//ins_button.bmp");
        iShowBMP(400, 100, "Picture//about_button.bmp");
        iShowBMP(500, 100, "Picture//sound.bmp");

        iSetColor(255, 255, 255);
        iText(400, 460, "Enter Your Name :", GLUT_BITMAP_TIMES_ROMAN_24);
        iRectangle(495, 450, 160, 30);
        iText(500, 460, str1, GLUT_BITMAP_TIMES_ROMAN_24);
    }

    if (menu == 1)
    {
        iShowBMP(0, 0, "Picture//flappy bird bg.bmp");
        iShowBMP(350, 400, "Picture//easy.bmp");
        iShowBMP(350, 350, "Picture//medium.bmp");
        iShowBMP(350, 300, "Picture//Hard.bmp");
        iShowBMP(100, 100, "Picture//back.bmp");
    }

    if (menu == 3)
    {
        iShowBMP(0, 0, "Picture//instructions.bmp");
        iShowBMP(100, 100, "Picture//back.bmp");
    }

    if (menu == 4)
    {
        iShowBMP(0, 0, "Picture//about.bmp");
        iShowBMP(100, 100, "Picture//back.bmp");
    }

    if (menu == 5)
    {
        iShowBMP(0, 0, "Picture//flappy bird bg.bmp");
        iShowBMP(350, 400, "Picture//On.bmp");
        iShowBMP(350, 300, "Picture//Off.bmp");
        iShowBMP(100, 100, "Picture//back.bmp");
    }
    // Starting Game
    if (start == 1)
    {
        iShowBMP(0, 0, "Picture\\flappy bird bg.bmp");

        iShowBMP2(x, y, image[im], 0);

        iShowBMP(x1, 65, bardown[bar1]);
        iShowBMP(x1, y5, "Picture//bar1d.bmp");

        iShowBMP(x2, 65, bardown[bar2]);
        iShowBMP(x2, y2, "Picture//bar1d.bmp");

        iShowBMP(x3, 65, bardown[bar3]);
        iShowBMP(x3, y3, "Picture//bar1d.bmp");

        iShowBMP(x4, 65, bardown[bar4]);
        iShowBMP(x4, y4, "Picture//bar1d.bmp");

        // coin
        iShowBMP2(coinx, coiny, "Picture//coin-removebg-preview.bmp", 0);

        // bomb
        iShowBMP2(bombx, bomby, "Picture//bomb.bmp", 0);

        // life
        iShowBMP2(lifex, lifey, "Picture//life.bmp", 0);

        // Random Bar access

        if (x1 == 0)
        {
            srand(time(0));
            int barChoose = rand() % 4;
            if (barChoose == 0)
            {
                bar1 = 0;
                y5 = 380;
            }

            if (barChoose == 1)
            {
                bar1 = 1;
                y5 = 350;
            }

            if (barChoose == 2)
            {
                bar1 = 2;
                y5 = 315;
            }

            if (barChoose == 3)
            {
                bar1 = 3;
                y5 = 380;
            }
        }
        // bar 2 access
        if (x2 == 0)
        {
            srand(time(0));
            int barChoose = rand() % 4;
            if (barChoose == 0)
            {
                bar2 = 0;
                y2 = 380;
            }

            if (barChoose == 1)
            {
                bar2 = 1;
                y2 = 350;
            }

            if (barChoose == 2)
            {
                bar2 = 2;
                y2 = 315;
            }

            if (barChoose == 3)
            {
                bar2 = 3;
                y2 = 380;
            }
        }
        // bar 3 access
        if (x3 == 0)
        {
            srand(time(0));
            int barChoose = rand() % 4;
            if (barChoose == 0)
            {
                bar3 = 0;
                y3 = 380;
            }

            if (barChoose == 1)
            {
                bar3 = 1;
                y3 = 350;
            }

            if (barChoose == 2)
            {
                bar3 = 2;
                y3 = 315;
            }

            if (barChoose == 3)
            {
                bar3 = 3;
                y3 = 380;
            }
        }
        // bar 4 access
        if (x4 == 0)
        {
            srand(time(0));
            int barChoose = rand() % 4;
            if (barChoose == 0)
            {
                bar4 = 0;
                y4 = 380;
            }

            if (barChoose == 1)
            {
                bar4 = 1;
                y4 = 350;
            }

            if (barChoose == 2)
            {
                bar4 = 2;
                y4 = 315;
            }

            if (barChoose == 3)
            {
                bar4 = 3;
                y4 = 380;
            }
        }

        sprintf(scoRe, "Score: %d", score);
        iText(650, 450, scoRe, GLUT_BITMAP_HELVETICA_18);
        sprintf(lifeArray, "Life: %d", life);
        iText(650, 430, lifeArray, GLUT_BITMAP_HELVETICA_18);

        if (y < 60 || y > 470)
        {
            if (sound == 1)
            {
                PlaySound(0, 0, 0);
                PlaySound("Picture//death.wav", NULL, SND_ASYNC);
            }
            start = 3;
        }

        if (x1 < 320 && x1 > 240 && (y < (y5 - 120) || y > (y5 - 27)))
        {
            if (sound == 1)
            {
                PlaySound(0, 0, 0);
                PlaySound("Picture//death.wav", NULL, SND_ASYNC);
            }
            start = 3;
        }

        if (x2 < 320 && x2 > 240 && (y < (y2 - 120) || y > (y2 - 27)))
        {
            if (sound == 1)
            {
                PlaySound(0, 0, 0);
                PlaySound("Picture//death.wav", NULL, SND_ASYNC);
            }
            start = 3;
        }

        if (x3 < 320 && x3 > 240 && (y < (y3 - 120) || y > (y3 - 27)))
        {
            if (sound == 1)
            {
                PlaySound(0, 0, 0);
                PlaySound("Picture//death.wav", NULL, SND_ASYNC);
            }
            start = 3;
        }

        if (x4 < 320 && x4 > 240 && (y < (y4 - 120) || y > (y4 - 27)))
        {
            if (sound == 1)
            {
                PlaySound(0, 0, 0);
                PlaySound("Picture//death.wav", NULL, SND_ASYNC);
            }
            start = 3;
        }

        // coin scoring
        if (coinx < 320 && coinx > 250 && (y < 380 && y > 300))
        {

            if (sound == 1)
            {
                PlaySound("Picture//coinsound.wav", NULL, SND_ASYNC);
            }
            coinx = 970;
            score += 10;
        }

        // bomb count
        if (bombx < 315 && bombx > 255 && (y < 350 && y > 270))
        {

            bombx = 970;
            life--;
            if (sound == 1)
            {
                PlaySound("Picture//bombsound.wav", NULL, SND_ASYNC);
            }
            if (life == 0)
            {
                if (sound == 1)
                {
                    PlaySound(0, 0, 0);
                    PlaySound("Picture//death.wav", NULL, SND_ASYNC);
                }
                start = 3;
            }
        }
        // life count
        if (lifex < 320 && lifex > 250 && (y < 370 && y > 290))
        {

            lifex = 970;
            life++;
            if (sound == 1)
            {
                PlaySound("Picture//lifesound.wav", NULL, SND_ASYNC);
            }
        }
    }

    // Game Over
    if (start == 3)
    {
        iShowBMP(0, 0, "Picture\\gameOver.bmp");
        sprintf(scoRe, "Score: %d", score);
        iText(300, 200, scoRe, GLUT_BITMAP_TIMES_ROMAN_24);
        leaderboard();
    }
}

/*
    function iMouseMove() is called when the user presses and drags the mouse.
    (mx, my) is the position where the mouse pointer is.
    */
void iMouseMove(int mx, int my)
{
    printf("x = %d, y= %d\n", mx, my);
    // place your codes here
}

/*
    function iMouse() is called when the user presses/releases the mouse.
    (mx, my) is the position where the mouse pointer is.
    */
void iMouse(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        // place your codes here
        // printf("x = %d, y= %d\n", mx, my);
        if (name_input == 0)
        {
            if (menu == 0 && ((mx >= 226 && mx <= 366) && (my >= -206 && my <= -160)))
            {
                start = 1;
            }

            if (menu == 0 && ((mx >= 440 && mx <= 595) && (my >= -206 && my <= -160)))
            {
                menu = 1;
            }

            if (menu == 0 && ((mx >= 658 && mx <= 814) && (my >= -206 && my <= -160)))
            {
                menu = 3;
            }

            if (menu == 0 && ((mx >= 880 && mx <= 1033) && (my >= -206 && my <= -160)))
            {
                menu = 4;
            }

            if (menu == 0 && ((mx >= 1098 && mx <= 1254) && (my >= -206 && my <= -160)))
            {
                menu = 5;
            }
            // Easy Medium Hard Mode
            if (menu == 1 && ((mx >= 768 && mx <= 924) && (my >= 329 && my <= 372)))
            {
                mode = 1;
                level = 100;
                start = 1;
            }
            if (menu == 1 && ((mx >= 768 && mx <= 924) && (my >= 236 && my <= 281)))
            {
                mode = 2;
                level = 100;
                start = 1;
            }
            if (menu == 1 && ((mx >= 768 && mx <= 924) && (my >= 148 && my <= 189)))
            {
                mode = 3;
                level = 100;
                start = 1;
            }

            // Sound On Off
            if (menu == 5 && ((mx >= 768 && mx <= 924) && (my >= 326 && my <= 373)))
            {
                sound = 1;
                menu = 0;
                // PlaySound("Picture//game_sound.wav", NULL, SND_LOOP | SND_ASYNC);
            }

            if (menu == 5 && ((mx >= 768 && mx <= 924) && (my >= 146 && my <= 194)))
            {
                sound = 0;
                menu = 0;
                PlaySound(0, 0, 0);
            }

            // Back Button
            if ((menu == 1 || menu == 3 || menu == 4 || menu == 5) && ((mx >= 218 && mx <= 377) && (my >= -210 && my <= -159)))
            {
                menu = 0;
            }
        }
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        // place your codes here
    }
}

/*
    function iKeyboard() is called whenever the user hits a key in keyboard.
    key- holds the ASCII value of the key pressed.
    */
void iKeyboard(unsigned char key)
{
    // Uplift of bird
    if (key == ' ')
    {
        y = y + 40;
    }
    // Pause
    if (key == 'p')
    {
        iPauseTimer(timer1);
        iPauseTimer(timer2);
    }
    // Resume
    if (key == 'r')
    {
        iResumeTimer(timer1);
        iResumeTimer(timer2);
    }

    if (name_input == 1)
    {
        if (key == '\r' || key == '\n' || key == ' ')
        {
            name_input = 0;
        }
        else if (key == '\b')
        {
            if (len <= 0)
                len = 0;
            else
                len--;
            str1[len] = '\0';
        }
        else
        {
            str1[len] = key;
            len++;

            str1[len] = '\0';
        }
    }

    // place your codes for other keys here
}

/*
    function iSpecialKeyboard() is called whenver user hits special keys like-
    function keys, home, end, pg up, pg down, arraows etc. you have to use
    appropriate constants to detect them. A list is:
    GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
    GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
    GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
    GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
    */
void iSpecialKeyboard(unsigned char key)
{
    // Uplift of Bird
    if (key == GLUT_KEY_UP)
    {
        y = y + 40;
    }
    // place your codes for other keys here
}
void birdCng()
{
    im++;
    if (im == 3)
        im = 0;
}

void barChange()
{
    if (start == 1)
    {
        // Easy Mode
        if (mode == 1)
        {
            dy = 8;
            y -= dy;
            x1 -= 5;
            x2 -= 5;
            x3 -= 5;
            x4 -= 5;
            coinx -= 5;
            bombx -= 5;
            lifex -= 5;
            if (x1 < 0)
                x1 = 650;
            if (x2 < 0)
                x2 = 650;
            if (x3 < 0)
                x3 = 650;
            if (x4 < 0)
                x4 = 650;
            if (coinx < 0)
                coinx = 650;
            if (bombx < 0)
                bombx = 650;
            if (lifex < 0)
                lifex = 650;

            if (x1 < 240 && x1 >= 235 || x2 < 240 && x2 >= 235 || x3 < 240 && x3 >= 235 || x4 < 240 && x4 >= 235)
            {
                score++;
                // if(score>best)
                // best=score;
            }
        }
        // Medium Mode
        if (mode == 2)
        {
            dy = 10;
            y -= dy;
            x1 -= 8;
            x2 -= 8;
            x3 -= 8;
            x4 -= 8;
            coinx -= 8;
            bombx -= 8;
            lifex -= 8;
            if (x1 < 0)
                x1 = 650;
            if (x2 < 0)
                x2 = 650;
            if (x3 < 0)
                x3 = 650;
            if (x4 < 0)
                x4 = 650;
            if (coinx < 0)
                coinx = 650;
            if (bombx < 0)
                bombx = 650;
            if (lifex < 0)
                lifex = 650;

            if (x1 < 240 && x1 >= 232 || x2 < 240 && x2 >= 232 || x3 < 240 && x3 >= 232 || x4 < 240 && x4 >= 232)
            {
                score += 3;
                // if(score>best)
                // best=score;
            }
        }

        // Hard Mode
        if (mode == 3)
        {
            dy = 12;
            y -= dy;
            x1 -= 10;
            x2 -= 10;
            x3 -= 10;
            x4 -= 10;
            coinx -= 10;
            bombx -= 10;
            lifex -= 10;
            if (x1 < 0)
                x1 = 650;
            if (x2 < 0)
                x2 = 650;
            if (x3 < 0)
                x3 = 650;
            if (x4 < 0)
                x4 = 650;
            if (coinx < 0)
                coinx = 650;
            if (bombx < 0)
                bombx = 650;
            if (lifex < 0)
                lifex = 650;

            if (x1 < 240 && x1 >= 230 || x2 < 240 && x2 >= 230 || x3 < 240 && x3 >= 230 || x4 < 240 && x4 >= 230)
            {
                score += 5;
                // if(score>best)
                // best=score;
            }
        }
    }
}

int main()
{
    // place your own initialization codes here.
    timer1 = iSetTimer(50, birdCng);
    timer2 = iSetTimer(100, barChange);
    iInitialize(700, 500, "Flappy Bird");

    return 0;
}
