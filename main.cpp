#include <iostream>
#include "DynamicIntQueue.h"
#include <conio.h>
#include <stdlib.h>     
#include <Windows.h>
#include "randgen.h"

using namespace std;

enum Direction {RIGHT, LEFT, UP, DOWN};
Direction dir;
const int WIDTH = 45;
const int HEIGTH = 15;



void createPlane(char Plane[HEIGTH][WIDTH])
{
	for (int i = 0; i < WIDTH; i++){
		Plane[0][i] = 'x';
		Plane[HEIGTH-1][i] = 'x';

	}

	for (int i = 1; i < HEIGTH; i++){
		Plane[i][0] = 'x';
		Plane[i][WIDTH-1] = 'x';
	}

	for(int i = 1; i < HEIGTH-1; i++){
		for(int j = 1; j < WIDTH-1; j++){
			Plane[i][j] = ' ';
		}
	}
}

void showCurrent(char Plane[HEIGTH][WIDTH], const int & counter)
{
	for(int i = 0; i < HEIGTH; i++){
		for(int j = 0; j < WIDTH; j++){
			cout << Plane[i][j];
		}
		cout << endl;
	}
	cout << counter<<  " tane yuvarlak yemisin yilancik"; 
}

void createSnake(char Plane[HEIGTH][WIDTH], DynamicIntQueue & memory)
{
	int row, col;
	row = 1;

	for(int i = 1; i < 3; i ++){
		Plane[1][i] = 'o';
		memory.enqueue(row,i);
	}
	Plane[1][4] = 'O';
	memory.enqueue(1,4);
}


bool isAlive(char Plane[HEIGTH][WIDTH], DynamicIntQueue memory)
{
	QueueNode *ptr;
	QueueNode *move;
	ptr = memory.GetRear();
	move = memory.GetFront();

	int row, col;
	while(move->next != NULL){
		if(ptr->col == move->col && ptr->row == move->row){
			return false;
		}
		move = move->next;
	}

	DynamicIntQueue temp(memory);
	ptr = temp.GetRear();
	if(ptr->col == 0 || ptr->col == WIDTH-1 || ptr->row == 0 || ptr->row == HEIGTH-1){
		return false;
	}

	return true;
}

void moveRight(char Plane[HEIGTH][WIDTH], DynamicIntQueue & memory)
{
	int row, col;
	bool control = true;
	DynamicIntQueue temp(memory);
	memory.clear();

	while(!temp.isEmpty()){
		temp.dequeue(row, col);

		if(control){
			Plane[row][col] = ' ';
			control = false;
		}
		else{	
			memory.enqueue(row, col);
		}
	}
	col++;
	memory.enqueue(row, col);
}

void moveLeft(char Plane[HEIGTH][WIDTH], DynamicIntQueue & memory)
{
	int row, col;
	bool control = true;
	DynamicIntQueue temp(memory);
	memory.clear();

	while(!temp.isEmpty()){
		temp.dequeue(row, col);

		if(control){
			Plane[row][col] = ' ';
			control = false;
		}
		else{	
			memory.enqueue(row, col);
		}
	}
	col--;
	memory.enqueue(row, col);
}

void moveUp(char Plane[HEIGTH][WIDTH], DynamicIntQueue & memory)
{
	int row, col;
	bool control = true;
	DynamicIntQueue temp(memory);
	memory.clear();

	while(!temp.isEmpty()){
		temp.dequeue(row, col);

		if(control){
			Plane[row][col] = ' ';
			control = false;
		}
		else{	
			memory.enqueue(row, col);
		}
	}
	row--;
	memory.enqueue(row, col);
}

void moveDown(char Plane[HEIGTH][WIDTH], DynamicIntQueue & memory)
{
	int row, col;
	bool control = true;
	DynamicIntQueue temp(memory);
	memory.clear();

	while(!temp.isEmpty()){
		temp.dequeue(row, col);

		if(control){
			Plane[row][col] = ' ';
			control = false;
		}
		else{	
			memory.enqueue(row, col);
		}
	}
	row++;
	memory.enqueue(row, col);
}

void moveSnake(char Plane[HEIGTH][WIDTH], DynamicIntQueue & memory)
{
	QueueNode *temp = memory.GetFront();
	int row, col;

	while(temp->next != NULL){
		int row = temp->row;
		int col = temp->col;
		Plane[row][col] = 'o';
		temp = temp->next;
	}

	row = temp->row;
	col = temp->col;
	Plane[row][col] = 'O';
}

void input()
{
	if(_kbhit()){
		switch (_getch())
		{
		case 'a': dir = LEFT;
				  break;
		case 'd': dir = RIGHT;
				  break;
		case 'w': dir = UP;
				  break;
		case 's': dir = DOWN;
				  break;
		}
	}
}

void increaseSnakeSize(char Plane[HEIGTH][WIDTH], DynamicIntQueue & memory)
{
	DynamicIntQueue temp(memory);

	int row, col;
	memory.dequeue(row,col);
	row = row - 1;

	memory.clear();
	memory.enqueue(row,col);

	int x, y;
	while(!temp.isEmpty()){
		temp.dequeue(x,y);
		memory.enqueue(x,y);
	}
}

void addFood(char Plane[HEIGTH][WIDTH])
{
	RandGen rand;
	int randRow, randCol;

	randRow = rand.RandInt(1,HEIGTH-2);
	randCol = rand.RandInt(1,WIDTH-2);

	Plane[randRow][randCol] = '#';
}

bool foodExist(char Plane[HEIGTH][WIDTH])
{
	for(int i = 1; i < HEIGTH-1; i++){
		for(int j = 1; j < WIDTH-1; j ++){
			if(Plane[i][j] == '#'){
				return true;
			}
		}
	}
	return false;
}

//void movement(char Plane[20][25], DynamicIntQueue & memory)
//{
//	if(dir == RIGHT){ // move right
//		moveRight(Plane, memory);
//	}
//
//	else if(dir == LEFT){ // move left
//		moveLeft(Plane, memory);
//	}
//
//	else if(dir == UP){ // move up
//		moveUp(Plane, memory);
//	}
//
//	else if(dir == DOWN){ // move down
//		moveDown(Plane, memory);
//	}
//
//	else{	
//		if(dir == RIGHT){ // move right
//			moveRight(Plane, memory);
//		}
//
//		else if(dir == LEFT){ // move left
//			moveLeft(Plane, memory);
//		}
//
//		else if(dir == UP){ // move up
//			moveUp(Plane, memory);
//		}
//
//		else if(dir == DOWN){ // move down
//		}
//	}
//}

void kaybettinmuzigi()
{
    Beep(1568, 100);
    Beep(1568, 100);
    Beep(1568, 100);
    Beep(1245, 1000);
    Beep(1397, 100);
    Beep(1397, 100);
    Beep(1397, 100);
    Beep(1175, 1000);
}


int main()
{
	char Plane[HEIGTH][WIDTH]; //bunu global yapmam daha mantikli olur
	DynamicIntQueue memory;

	Direction temp = RIGHT;
	int counter = -1;

	cout << "Baslamak icin entera basmalisin";
	cin.ignore();
	createPlane(Plane);
	createSnake(Plane, memory);
	showCurrent(Plane, counter);

	bool control = false;
	while(isAlive(Plane, memory)){
		
		system("CLS"); //// deigisiklikleri tek bi duzlem uzerinde gosterebilmek icin
		
		if(!foodExist(Plane)){
			//cout << '\a';
			addFood(Plane);
			counter++;

			if(control) // burayi kaldirabilirim
				Beep(1568,25);
				increaseSnakeSize(Plane, memory);
		}

		input();
		//movement(Plane,memory);
		if(dir == RIGHT){ // move right
			moveRight(Plane, memory);
		}

		else if(dir == LEFT){ // move left
			moveLeft(Plane, memory);
		}

		else if(dir == UP){ // move up
			moveUp(Plane, memory);
		}

		else if(dir == DOWN){ // move down
			moveDown(Plane, memory);
		}

		else{	
			if(dir == RIGHT){ // move right
				moveRight(Plane, memory);
			}

			else if(dir == LEFT){ // move left
				moveLeft(Plane, memory);
			}

			else if(dir == UP){ // move up
				moveUp(Plane, memory);
			}

			else if(dir == DOWN){ // move down
			}
		}

		control = true; 
		temp = dir;

		moveSnake(Plane, memory);
		showCurrent(Plane, counter);	
	}	
	system("CLS");
	cout << endl<<endl;
	cout << "KAYBETTIN YILANCIK"<<endl<<endl<<endl;
	cout << "Skor: "<< counter*10 <<endl<<endl;
	kaybettinmuzigi();

	system("pause");
	return 0;
}