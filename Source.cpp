//========================================== Header Section ==============================================

#include <iostream>
#include <string>
#include <stdlib.h>
#include <iomanip>
#include <ctime>
#include <Windows.h>
#include "termcolor.hpp"
using namespace std;
using namespace termcolor;
//=========================================== Global variables ============================================

const int size = 3;
char board[ size ][ size ];

//============================================ User Defined Functions =====================================



int Menu(){
	cout << setw(58) << "1 : Play Game " << endl;
	cout << setw(66) << "2 : Game Instructions " << endl;
	cout << setw(53) << "3 : Exit " << endl;
	int option=0;
	cout << "Choose option ---  ";
	cin >> option;
	return option;
}
void fillBoard(){
	char  k = '1';
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			board[i][j] = k++; 
}
void setConsole(int x,int y){
	HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(screen, pos);
}
void setBoard(){
	cout << "\n\n\n";
		for (int i=0; i < size; i++){
			cout << "\t\t";;
			cout << on_white << "|-------------------------------------------" <<reset<< on_red << "-"<<reset << on_white <<" ---------------------------------- - | " << reset<<endl;
			cout << "\t\t";;
			cout << on_red << "|" << reset;
			cout << "\t\t\t\t\t\t\t\t\t	    " << on_white << "|" << endl;
			cout << "\t\t";; cout << on_white << "|" << reset;
			for (int j = 0; j < size; j++){
				cout << "\t\t";;
				if (board[i][j] == 'X'){
					cout << red;
				}
				else if(board[i][j]=='O'){
					cout << green;
				}
				else{
					cout << white;
				}
				cout << "    " << (board[i][j]) << "    " << reset;
			}
			cout <<"\t    "<< on_red << "|" << reset;
			cout << endl;

		}
		cout << "\t\t";;
		cout << on_white << "|-------------------------------------------" << reset << on_red << "-" << reset << on_white << " ---------------------------------- - | " << reset << endl;

}

bool inDiagonal(char token){
	for (int i = 0; i < size; i++){
		if (board[i][i] != token)
			return false;
	}
	return true;
}
bool inReverseDiagonal(char token){

	for (int i = 0; i < size; i++)
		if (board[size - i - 1][i] != token)
			return false;
	return true;
}
bool inRow(char token){
	bool okay;
	for (int row = 0; row < size; row++){
		okay = true;
		for (int col = 0; col < size;col++){
			if (board[row][col] != token){
				okay = false; break;
			}
		}
		if (okay)
			return true;
	}
	return (okay) ? true : false;
}
bool inColumn(char token){
	bool okay = true;
	for (int i = 0; i < size; i++){
		okay = true;
		for (int j = 0; j < size; j++){
			if (board[j][i] != token){
				okay = false; break;
			}
		}
		if (okay)
			return true;
		
	}
	return (okay) ? true : false;
}
bool win(char token){
	return inDiagonal(token) || inReverseDiagonal(token) || inRow(token) || inColumn(token);
	
}
void fillBoard(char token,int position,char opponent){
	int k = 1;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++, k++)
			if (k == position && board[i][j]!=opponent)
				board[i][j] = token;
				k += 1;
}
bool draw(){
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (board[i][j] == 'X' || board[i][j] == 'O')
				return false;
	return true;
}
bool validLocation(int location){
	int k = 1;
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++, k++){
			if (board[i][j] != 'X' && board[i][j]!='O' && location == k)
				return true;
		}
	}
	return false;
}
void playGame(){
	cout << "Human     ->"<<red<<" X \n"<<reset;
	cout << "Computer  ->"<<green<<" O\n"<<reset;
	char token;
	int location;
	bool isPc = false;
	while (true){
		if (!isPc){
			token = 'X';
			cout << "Human: Select position (1-9) : "; cin >> location;
			cout << "Position selected by Human : " << location << endl; Sleep(2000);
			fillBoard(token, location,'O');
			system("cls");
			setBoard();
			isPc = true;
		}
		else{
			token = 'O';
			srand((unsigned int)time(NULL));
			int location = rand() % (size*size) + 1;
			while (!validLocation(location)){
				srand((unsigned int)time(NULL));
				 location = rand() % (size*size) + 1;
			}
			cout << "Position selected by PC : " << location << endl; Sleep(3000);
			fillBoard(token, location,'X');
			system("cls");
			setBoard();
			isPc = false;
			
		}
		if (win(token)){
			if (token == 'X')
				cout << "Congratulations You ";
			else
				cout << "Computer ";
			cout << " win ..... " << endl;
			break;
		}
		if (draw())
			cout << " Match is Draw ...... \n";
	}

}
void Instruction()  //function to show the game instruction 
{
	cout << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

	cout << "Game Instructions" << endl;
	cout << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "1->: Token for Human   is X " << endl;
	cout << "___________________________" << endl;
	cout << "2->: Token for Computer  is 0 " << endl;
	cout << "___________________________" << endl;
	cout << "3->: Overwritten will be ignored " << endl;
	cout << "________________________________" << endl;
	cout << "4->: In case of no Result Game will be draw " << endl << endl;;
	cout << "******************************" << endl; 
}
void StartGame(int option){
	if (option == 1){
		system("cls");
		fillBoard();  setBoard(); playGame();
	}
	else if (option == 2){
		//view Instructions
		system("cls");
		Instruction();
		cout.put('\n');

	}
	else if (option == 3){
		system("cls");
		cout << "Good bye \nThis game is developed by Muhammad Atif akram\n";
		exit(0);
	}
	else{
		cout << "Invalid option ... \n";
	}
}
bool playAgain(){
	cout << "Want to play Game [Y/y N/n] : ";
	char ch;
	cin >> ch;
	if (ch == 'y' || ch == 'Y')
		return true;
	return false;
}


int main(){
	StartGame(Menu());
	while (playAgain()){
		system("cls");
		StartGame(Menu());
	}
	return 0;
}