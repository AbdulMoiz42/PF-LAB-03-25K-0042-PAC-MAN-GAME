#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>

#define H 15
#define W 40

char playfield[H][W + 2] = {
    {"****************************************"},
    {"*......................................*"},
    {"*..*..*..*..*..*..*..*..*..*..*..*..*..*"},
    {"*..*..*..*..*..*..*..*..*..*..*..*..*..*"},
    {"*..*..*..*..*..*..*..*..*..*..*..*..*..*"},
    {"*..*..*..*..*..*..*..*..*..*..*..*..*..*"},
    {"*..*..*..*..*..*..*..*..*..*..*..*..*..*"},
    {"*......................................*"},
    {"*..*..*..*..*..*..*..*..*..*..*..*..*..*"},
    {"*..*..*..*..*..*..*..*..*..*..*..*..*..*"},
    {"*..*..*..*..*..*..*..*..*..*..*..*..*..*"},
    {"*..*..*..*..*..*..*..*..*..*..*..*..*..*"},
    {"*..*..*..*..*..*..*..*..*..*..*..*..*..*"},
    {"*......................................*"},
    {"****************************************"}};

int food_collect = 0, game_end = 0;
int py = 1, px = 1;
int gy1 = 1, gx1 = 38, gy2 = 13, gx2 = 1;

void game_result()
{
    clrscr();
    if (food_collect >= 200)
    {
	printf("\n\n\n\n\n\n\n");
	printf("\t\t   Congratulation!\n");
	printf("\t\t   You won the game!\n");
	printf("\t\t   BEST SCORE = %d", food_collect);
    }
    else
    {
	printf("\n\n\n\n\n\n\n");
	printf("\t\t   Game Over!\n");
	printf("\t\t   Better luck next time!\n");
	printf("\t\t   BEST SCORE = %d", food_collect);
    }
}

void move_ghosts()
{
    if (gy1 == 1 && gx1 > 1)
	gx1--;
    else if (gx1 == 1 && gy1 < 7)
	gy1++;
    else if (gy1 == 7 && gx1 < 38)
	gx1++;
    else if (gx1 == 38 && gy1 > 1)
	gy1--;

    if (gy2 == 13 && gx2 < 38)
	gx2++;
    else if (gx2 == 38 && gy2 > 7)
	gy2--;
    else if (gy2 == 7 && gx2 > 1)
	gx2--;
    else if (gx2 == 1 && gy2 < 13)
	gy2++;
}

void move_pacman()
{
    int new_py;
    int new_px;
    if (kbhit())
    {
	int new_py;
	int new_px;
	int ch = getch();
	if (ch == 0 || ch == 224)
	    ch = getch();

	 new_py = py;
	 new_px = px;

	if (ch == 72)
	    new_py--;
	if (ch == 80)
	    new_py++;
	if (ch == 75)
	    new_px--;
	if (ch == 77)
	    new_px++;

	if (new_py >= 0 && new_py < H &&
	    new_px >= 0 && new_px < W)
	{

	    if (playfield[new_py][new_px] != '*')
	    {
		py = new_py;
		px = new_px;
	    }
	}
    }
}

void setup()
{
    int i, j;
    for (i = 0; i < H; i++)
    {
	for (j = 0; j < W; j++)
	{
	    if (playfield[i][j] == 'C')
		playfield[i][j] = ' ';
	    if (playfield[i][j] == '@')
		playfield[i][j] = '.';
	}
    }

    if (playfield[py][px] == '.')
	food_collect++;

    if (playfield[py][px] == '*')
    {
	py = 1;
	px = 1;
    }

    playfield[py][px] = 'C';
    playfield[gy1][gx1] = '@';
    playfield[gy2][gx2] = '@';

    if (playfield[py][px] == '@')
	game_end = 1;

    if (food_collect >= 200)
	game_end = 1;
}

void draw_playfield()
{
    int i, j;
    char ch;
    printf("\n\n");
    for (i = 0; i < H; i++)
    {
	printf("\t");
	for (j = 0; j < W; j++)
	{
	    ch = playfield[i][j];
	    if (ch == 'C')
		textcolor(YELLOW);
	    else if (ch == '@')
		textcolor(RED);
	    else
		textcolor(BLUE);

	    cprintf("%c", playfield[i][j]);
	}
	printf("\n");
    }
    printf("Score: %d", food_collect);
}

void main()
{
    int i = 100;
    int choice;
    printf("\t\t\"PAC-MAN\"\t\t");
    printf("\n\t\tWelcome to PAC-MAN Game...");
    printf("\n");
    do
    {
	printf("\nEnter 1 for start the game\n");
	printf("\nEnter 2 for Exit\n");
	scanf("%d",&choice);
	switch (choice)
	{
	case 1:
	    while (game_end != 1)
	    {
		clrscr();
		sound(i);
		setup();
		move_pacman();
		move_ghosts();
		draw_playfield();
		delay(200);

		if (i < 1000)
		    i += 100;
		else
		    i = 100;
	    }

	    nosound();
	    game_result();
	    getch();
	    break;
	case 2:
	    printf("\nThanks for playing.........");
	    break;

	default:
            break;
        }

    } while (choice != 2);
}
