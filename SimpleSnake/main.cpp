/*
........................................................................
																	   .				
	Derived from NVtianovic's Simple Snake Game						   .  	
																	   .	
........................................................................
*/


#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

bool gameOver; 
const int width = 20;	//board position
const int height = 20; 

int x, y;		//head position variables
int eggX, eggY;		//egg position variables 

int tailX[100]; 
int tailY[100]; 
int lenTail;


//enum (Enumeration) is a user defined data type where we specify a set of values for a variable and the variable can choose only one of the set of values.
 
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };	//chooses direction of movement


eDirection dir;		//holds direction of the snake

int score;

//Class that sets up game variables

void Setup()
{
	gameOver = false;
	
	dir = STOP;		//default direction = stop
	
	x = width / 2;	//snake at the center of the map
	y = height / 2;

	eggX = rand() % width;	//eggs at random position
	eggY = rand() % height; 

	score = 0;
}

//Class that draws the game board

void Draw() {

	system("cls");	//clear the screen
	
	//prints top border of the board	
	for (int i = 0; i < width+2; i++)
	{
		cout << "#";	
	}
	cout << endl;

	//middle board section
	for (int i = 0; i < height; i++)	//iterates over the height of the board
	{
		for (int j = 0; j < width; j++)		//iterates row by row of the board
		{
			if (j == 0)						
				cout << "#";				//draws border at the edges of the board
				
			if (i == y && j == x)			//prints snake head
				cout << "O";
			else if (i == eggY && j == eggX)
				cout << "F"; 
			else
			{
				bool print = false;
				for (int k = 0; k < lenTail; k++) {

					//print tail or not

					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print) {
					cout << " ";		//if the position is not an edge, draws blank space	
							
				}
								
			}
				
				
				if (j == width - 1)			//draws border at the edges of the board
					cout << "#"; 
		}
		cout << endl;						//moves j to the next row
	}


	//prints bottom border of the board		
	for (int i = 0; i < width+2; i++)
	{
		cout << "#";	
	}
	cout << endl;
	cout << "Score: " << score << endl; 

	if (dir == LEFT || dir == RIGHT)
	{
		if (score <= 10)				
			Sleep(20);
		else if (score > 10)	//Increases snake speed as the score crosses 10 
			Sleep(10);
		else
			Sleep(0);
	}
	if (dir == UP || dir == DOWN)
	{
		if (score <= 10)
			Sleep(80);
		else if (score > 10)	//Increases snake speed as the score crosses 10 
			Sleep(60);

		else
			Sleep(0); 
	}
}

//Class that handles input actions

void Input() 
{
	if (_kbhit())				//keyboard hit
	{
		switch (_getch())		//get character pressed on keyboard
		{
		case 'a' :				//when a is pressed, move snake left
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's': 
			dir = DOWN;
			break;
		case 'x':
			gameOver = true; 
			break;
		}

	}


}

//class with the game logic

void Logic() {

	int prevX = tailX[0];		//remembers previous X and Y coordinates of the tail
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;				//sets tailX and Y first location to follow the head coordinates
	tailY[0] = y;

	for (int i = 1; i < lenTail; i++)
	{
		prev2X = tailX[i];		//remember the current position of the tail segment
		prev2Y = tailY[i]; 

		tailX[i] = prevX;
		tailY[i] = prevY; 
		prevX = prev2X; 
		prevY = prev2Y; 
	}


	switch (dir)
	{
	case LEFT:			//Changes the snake head position coordinates according to its direction of movement
		x--;
		break;

	case RIGHT:
		x++;
		break;

	case UP:
		y--;
		break;

	case DOWN:
		y++;
		break;

	default:
		break;
	}

	//if (x > width || x < 0 || y > height || y < 0) {		//Terminates game if the snake leaves the board
	//	gameOver = true;
	//}

	if (x >= width)					//if the snake goes through the wall, it comes out from the other side
		x = 0;
	else if (x < 0)
		x = width - 1;

	if (y >= height)
		y = 0;
	else if (y < 0)
		y = height - 1;

	for (int i = 0; i < lenTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y)		//if the snake tail touches the head, it dies
			gameOver = true;
	}
	
	if (x == eggX && y == eggY) {		//Increases the score and changes the egg's position after the egg is eaten
		score++;
		eggX = rand() % width;	//eggs at random position
		eggY = rand() % height;
		lenTail++;				///increase tail length after eating fruit
	}

}


//main class

int main() {

	Setup();
	while (!gameOver) {
		Draw(); 
		Input();
		Logic(); 
		
	}

	return 0;
}