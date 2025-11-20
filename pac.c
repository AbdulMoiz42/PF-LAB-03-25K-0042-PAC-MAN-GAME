#include <stdio.h>
#include <conio.h>
#include <dos.h>

#define H 15
#define W 40

char playfield[H][W] = {
    "****************************************",
    "* .....................................*",
    "*..*..*..*..*..*..*..*..*..*..*..*..*..*",
    "*..*..*..*..*..*..*..*..*..*..*..*..*..*",
    "*..*..*..*..*..*..*..*..*..*..*..*..*..*",
    "*..*..*..*..*..*..*..*..*..*..*..*..*..*",
    "*..*..*..*..*..*..*..*..*..*..*..*..*..*",
    "*......................................*",
    "*..*..*..*..*..*..*..*..*..*..*..*..*..*",
    "*..*..*..*..*..*..*..*..*..*..*..*..*..*",
    "*..*..*..*..*..*..*..*..*..*..*..*..*..*",
    "*..*..*..*..*..*..*..*..*..*..*..*..*..*",
    "*..*..*..*..*..*..*..*..*..*..*..*..*..*",
    "*......................................*",
    "****************************************"
};

int py = 1, px = 1;
int gy1 = 1, gx1 = 38;
int gy2 = 13, gx2 = 1;

int food_collect = 0;
int game_end = 0;

int ghost_speed = 0;    // SLOW GHOST CONTROL HERE

void draw_playfield()
{
    int i, j;
    printf("\n\n\n");

    for (i = 0; i < H; i++)
    {
        printf("\t\t");
        for (j = 0; j < W; j++)
        {
            if (i == py && j == px)
            {
                textcolor(YELLOW);
                cprintf("#");
            }
            else if ((i == gy1 && j == gx1) || (i == gy2 && j == gx2))
            {
                textcolor(RED);
                cprintf("@");
            }
            else
            {
                textcolor(WHITE);
                cprintf("%c", playfield[i][j]);
            }
        }
        printf("\n");
    }

    textcolor(WHITE);
    printf("Score: %d\n", food_collect);
}

void user_input()
{
	int c = getch(), new_py, new_px;
    if (kbhit())
    {
        c = getch();

        if (c == 0 || c == 224)   // extended key
            c = getch();

        new_py = py, new_px = px;

        switch (c)
        {
        case 72: new_py--; break; // up
        case 80: new_py++; break; // down
        case 75: new_px--; break; // left
        case 77: new_px++; break; // right
        }

        if (playfield[new_py][new_px] != '*')
        {
            py = new_py;
            px = new_px;

            if (playfield[py][px] == '.')
                food_collect++;
        }
    }
}

void move_ghosts()
{
    if (gy1 == 1 && gx1 > 1) gx1--;
    else if (gx1 == 1 && gy1 < 7) gy1++;
    else if (gy1 == 7 && gx1 < 38) gx1++;
    else if (gx1 == 38 && gy1 > 1) gy1--;

    if (gy2 == 13 && gx2 < 38) gx2++;
    else if (gx2 == 38 && gy2 > 7) gy2--;
    else if (gy2 == 7 && gx2 > 1) gx2--;
    else if (gx2 == 1 && gy2 < 13) gy2++;
}

void check_collision()
{
    if (py == gy1 && px == gx1)
        game_end = 1;
    if (py == gy2 && px == gx2)
        game_end = 1;
}

void main()
{
    int tone = 100;

    while (!game_end)
    {
        clrscr();

        sound(tone);
        if (tone < 1000) tone += 100;
        else tone = 100;

        user_input();

        ghost_speed++;
        if (ghost_speed >= 3)   // RECOMMENDED SETTING: 3 (slow nice gameplay)
        {
            move_ghosts();
            ghost_speed = 0;
        }

        check_collision();
        draw_playfield();

        delay(250);   // RECOMMENDED SPEED
    }

    nosound();

    clrscr();
    printf("\n\n\nGame Over!\n");
    printf("Score: %d\n", food_collect);
    getch();
}
