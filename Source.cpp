/*
Key Points :
1 : I have Initilized  Game Board with locational values in the Constructer
2 : For Player 1 Identification Token is X
2 : For Player 2 Identification Token is O
3 : In Case If No player succeeded to win the game  it will draw .
4 : There are 5 private data members in the class and about 35 functions in the class
5 : Each functionality or features of game is organized into a function .
6 : Error Handling is done on every stage like choosing of board , again play options ,duplicate token insert on board etc
7 : Each features or property of game is organized using functions and modules
*/
//Section for header files 
#include "iostream"
#include "iomanip"
#include "windows.h"
#include "ctime"
#include "string"
#include "fstream"
#include "sstream"
#pragma warning (disable : 4996) //_CRT_SECURE_NO_WARNINGS
#pragma warning (disable : 4715 4800 4668 )
#if defined(__CYGWIN__)
#   undef __STRICT_ANSI__
#   define __STRICT_ANSI__
#endif
#include "termcolor.hpp"
using namespace termcolor;
using namespace std;
class TicTacToi {
private:
	int **GameBoard;    //To declare  The board for playinng game
	int SizeOfBoard;   // To get the size of grid
	int choice;		  // To get choice for menu 	
	bool singlePlayer = false;  // to get Game Player Status either single player or double player 
	char indicator;
public: 
	 void loading()          // function to show startup loader before game 
	{
		for (int i = 6; i >=0; i--)
		{
			Sleep(1000);
			system("cls");
			cout << setw(55)<<"  Wait.. Game is Loading " << i;
		}
		system("cls");
	}
	void GameMenu()            //function to show Game MENU 
	{
		string str;
		
		
		cout << setw(48) << "1 : Play Game " << endl;
		cout << setw(56) << "2 : Game Instructions " << endl;
		cout << setw(43) << "3 : Exit " << endl;
		cout << setw(55) << "________________________" << endl;
		cout << "Choose Option (1 / 2 /3 ) -> : ";
		getline(cin, str);
		for (int i = 0; i < 2; i++)
		{
			if (str == "1" || str == "2" || str == "3")
			{
				break;
			}

			else cout << red << "Please Enter valid option " << endl<<reset;  str.clear(); i--; getline(cin, str);
		}
		system("cls");choice = atoi(str.c_str());
		
	}
	int ShowFirstMenu()
	{
	
		
		cout << cyan<< setw(56) << "1 : Load A Saved Game " << endl<<reset;
		cout << red<< setw(58) << "2 : Delete A Saved Game " << endl<<reset;
		cout << yellow<<setw(55) << "3 : Play A New Game  " << endl<<reset;
		cout <<green<< setw(43) << "4 :`Exit " << endl<<reset;
		cout << setw(55) << "________________________" << endl;
		cout << "Choose Option (1 / 2 /3 ) -> : ";
		string option;takeInputAgain:cin.clear();getline(cin, option);
		if (option == "1")
		{
			if (chooseGameFromFile())
			{
				if (loadGame())
				{
				
					PlayGame();
				}
			}
			else
			{
				cout <<red<< "Sorry No record found " << endl<<reset; Sleep(1000); cout << endl; Restart();
			}
			
		}
		else if (option == "2")
		{
			if (!checkifFileIsEmpty())
			{
				if (deleteGame())
				{
					cout << "Game Deleted Successfully  " << endl; cin.clear(); cin.ignore(); Restart();
				}
				else
					cout << "Sorry Error in file deletion " << endl; 
			}
			else cout << bold << red << "No record Found in file " << reset << endl; Restart();
			
			
			exit(0);
			//return 2;
		}
		else if (option == "3")
		{
			return 1;
		}
		else if (option == "4")
		{
			showEndMessage();
		}
		else cout <<bold<<red<< "Sorry Invalid Input" << endl<<reset;goto takeInputAgain;
		
		

	}
	void  SelectGamePlayer()  // function to select Player Choices for Game play 
	{

		cout << setw(55) << "________________________" << endl;
		cout << setw(68) << "1 :Single Player (Human vs Computer) " << endl;
		cout << setw(61) << "2 :Two Player (Human vs Human)" << endl;
		cout << setw(50) << "3 :Go Back To Menu " << endl;
		cout << setw(40) << "4 : Exit " << endl;
		cout << setw(55) << "________________________" << endl;
		cout << "Choose Option (1 / 2 /3/4 ) -> : ";
		string str;int option;getline(cin, str);
		for (int i = 0; i < 2; i++)
		{
			if (str == "1" || str == "2" || str == "3" || str == "4") break;
			else cout <<bold<<red<< "Please Enter valid Option" << endl<<reset; str.clear(); i--; getline(cin, str);
		}
		option = atoi(str.c_str());
		switch (option)
		{
		case 1:
			 singlePlayer = true; break;
		case 2:
			singlePlayer = false; break;
		case 3:
			system("cls"); TicTacToi();
			break;
		case 4:
			showEndMessage(); break;
		default:
			ShowErrorMessage(); Restart();
			break;
		}
	}
	bool DecideWhatTodo(int ch)    //function to decide what to do after choosing menu 
	{
		switch (ch)
		{
		case 1:
			SelectGamePlayer(); return true;
		// if choice =1 then Call Constructer and play game 
		case 2:
			GameInstruction();  // if choice =2 then Call GameInstruction () to show instruction 
			break;
		case 3:
		showEndMessage();                // If option 3 , then call showEndMessage();
			break;
		default:
			
			ShowErrorMessage();  // if other than (1,2,3) then Show Error Message and Call Restart() function 
			Restart(); 	break;
		}
		return false;
	}

	void selectGrid()        //function to select the playing grid
	{

		cout <<red<<on_white << setw(55)<< "Please Select Playing Grid " <<setw(25)<<" "<< endl<<reset;
		cout << white << setw(45) << "1 - > : 3 x 3"  << reset<< endl;
		cout << white << setw(45) << "2 - > : 4 x 4"  << reset<< endl;
		cout << white << setw(45) << "3 - > : 5 x 5"  << reset<<endl;
		cout << "Choose Option (1 / 2 / 3) -> "; cin >> SizeOfBoard;
	}
	bool CheckSizeOfBoard()
	{
		if (SizeOfBoard == 1 || SizeOfBoard == 2 || SizeOfBoard == 3)   // if(size selection is done accurately )
		{
			SizeOfBoard += 2; return true;
		}
		else          //else show error message 
		{
			cerr << bold << red << "Sorry You Selected an invalid Size " << endl << reset;		return false;
		}
	}
	TicTacToi()          //default constructer to initilize the board with locational values 
	{
		static int c = 0;
		if (c == 0)
		{
			//loading(); 
			c++;   // just to avoid to call loading() function again on call of constructer 
		}
		cin.clear();fflush(stdin);
		if (ShowFirstMenu() == 1)
		{
			GameMenu();
		}
		if (DecideWhatTodo(choice) == true)    // if user want to play game then .......
		{
			    // decide play single or double player game
			selectGrid();              // then select the grid for game 
			if (CheckSizeOfBoard())   // if size is accuratelly selected then intitlize the board with locations 
			{
				GameBoard = new int *[SizeOfBoard];
				for (int i = 0; i < SizeOfBoard; i++)
				{
					GameBoard[i] = new int[SizeOfBoard];
				}
				int k = 0;
				for (int i = 0; i < SizeOfBoard; i++)
				{
					for (int j = 0; j < SizeOfBoard; j++)
					{
						GameBoard[i][j] = k + 1;   
						k++;
					}
				}
				DesignBoard();
				PlayGame();
			}
			else
			{
				
				Restart();     //else provide opportunity to user to play again 
			}
		}   
	}

	void PlayGame()       // Main function to play the game 
	{	
		
		char mark;char start = 'S';srand((unsigned int)time(NULL));
		int location;   //variable to get the location of board by both players
		string t;	
		if (indicator == 'O' && !singlePlayer)
		{
			goto p2;
		}
		else if (indicator == 'X' && !singlePlayer)
		{
			goto p1;
		}
		else if (indicator == 'O' && singlePlayer)
		{
			goto s1;
		}
		
		while (true)   //while true run continuesly for loop
		{
			for (int i = 0; i < 2; i++)               //since there are only 2 players therefore loop used for 2 times
			{
				if (checkIfGameDraw())   // function called to decide if the game is draw or not
				{
					cout << endl << endl;
					cerr << red << on_white << " Sorry ! No Result  - > Game Draw " << endl<<reset;	Restart();
				}
				
				if (i == 0)             //for first iteration enter location by player 1 
				{
				p1:
					i = 0;
					cout << "Player 1 " << endl;
					mark = 'X';	
					cout << "Enter s To save Game or " << endl;
					cout <<" Enter Your location => ";
					again:getline(cin, t);
					bool isUserEnterAvalidNumber = false;
					//cin >> location;
					if (t == "s" || t == "S")
					{

						SaveGameToFile(mark);
						Restart();
					}
					else
					{
						for (int i = 0; i <= SizeOfBoard*SizeOfBoard; i++)
						{
							if (t == to_string(i))
							{
								isUserEnterAvalidNumber = true;
								break;
							}
						}
						if (!isUserEnterAvalidNumber)
						{
							cout << bold << red << "Please Enter a valid Key " << endl << reset ;
							goto again;
						}
						location = stoi(t);
						isUserEnterAvalidNumber = false;
												
					}
					
					fillBoard(location, 'X');   //call fillBoard function to fill the board 
				}
				else if(i == 1)    //  get location by player 2 
				{
					bool isUserEnterAvalidNumber = false;
					if (!singlePlayer)      // if is not single player 
					{
						
						p2:
						i = 1;
						mark = 'O';	cout << "player 2  " << endl;cout << "Enter s To save Game or " << endl;
						cout << " Enter Your location => "; 
						againIn:
						t.clear();
						getline(cin, t);       // get location 
						if (t == "s" || t == "S")
						{
							mark = 'O';
							SaveGameToFile(mark);
							Restart();
						}
						else
						{
							for (int i = 0; i <= SizeOfBoard*SizeOfBoard; i++)
							{
								if (t == to_string(i))
								{
									isUserEnterAvalidNumber = true;
									break;
								}
							}

							if (!isUserEnterAvalidNumber)
							{
								cout << bold << red << "Sorry You Entered Invalid Number " << endl << reset; goto againIn;
							}
							location = atoi(t.c_str());
							
						}						
						fillBoard(location, 'O');  //and call fill board function 
					}
					else if (singlePlayer)     // if Game is for single player then get location by computer 
					{
						s1:
						mark = 's';
					//take location randomly
				   location = rand() %  (SizeOfBoard*SizeOfBoard) + 1;
				   while (validateLocation(location) != true)  // just to avoid overwriting of Computer Token
				   {
					   location = rand() % (SizeOfBoard*SizeOfBoard) + 1;  
				    }
				   cout << location << endl;
				   location = Strategy('O', location); // call strategy function to give tough time to the user
				   cout << "Location is " << location << endl;			  
				   fillBoard(location, 'O');  //and call fill board function 
					}		
			}
		  }
		}
	}
	string GetTime() // function to get Current Date and Time 
	{
		time_t rawtime; struct tm * timeinfo; char buffer[80]; time(&rawtime); timeinfo = localtime(&rawtime);
		strftime(buffer, sizeof(buffer), "%d-%m-%Y %I:%M:%S", timeinfo); std::string str(buffer); return str;
	}
	int getValidId(int id)       // function to get Valid Id for user in order to avoid duplication
	{
		ifstream in("getUserId.dat", ios::binary | ios::app); int ID;
		in.read(reinterpret_cast<char*>(&ID), sizeof(int));
		if (ID == id)
		{
			return false;
		}
		while (!in.eof())
		{
			if (ID == id)
			{
				return false;
			}
			in.read(reinterpret_cast<char*>(&ID), sizeof(int));
		}
		in.close();return true;
	}
	// function to Save Game To file 
	void SaveGameToFile(char mark){
		ofstream idWrite("getUserId.dat", ios::binary | ios::app);
		srand((unsigned int)time(NULL)); int id = rand() % 9999 + 1; idWrite.write(reinterpret_cast<char*>(&id), sizeof(int));
		while (!getValidId(id))
		{
			id = rand() % 9999 + 1;
		}
		string time = GetTime(); int size1; ofstream file("SaveGameToFile.dat", ios::binary|ios::app);int rows = SizeOfBoard; int cols = SizeOfBoard;
		size1 = time.length(); 
		file.write(reinterpret_cast<char*>(&singlePlayer), sizeof(bool));file.write(reinterpret_cast<char*>(&mark), sizeof(char));
		file.write(reinterpret_cast<char*>(&id), sizeof(int));
		file.write(reinterpret_cast<char *>(&size1), sizeof(int)); file.write(time.c_str(), size1); time.clear();
		file.write(reinterpret_cast<char*>(&rows), sizeof(int)); file.write(reinterpret_cast<char*>(&cols), sizeof(int));
		for (int i = 0; i<rows; i++)
		{
		file.write(reinterpret_cast<char*>(GameBoard[i]), sizeof(int)*cols);
		}
		file.close();
		cout << "Game Saved Successfully " << endl;
	}
	//function to check if file is empty or not 
	bool checkifFileIsEmpty()
	{
		ifstream file("SaveGameToFile.dat", ios::binary); 
		if (!file)
		{
			ofstream file("SaveGameToFile.dat", ios::binary); ifstream in("SaveGameToFile.dat", ios::binary);in.seekg(0, ios::end); bool z = in.tellg();
			if (z == 0)	return true; else return false;
		}
		else
		{
			file.seekg(0, ios::end); bool z = file.tellg();
		     if (z == 0) return true; else return false;
		}
	}
	// function to fetch All Games From the file 
	bool chooseGameFromFile()
	{
		if (!checkifFileIsEmpty())
		{
			int **pointer;string text = "";	char mark;  ifstream file("SaveGameToFile.dat", ios::binary);
			int rows; int cols; string x = ""; int size; int id; file.read(reinterpret_cast<char*>(&singlePlayer), sizeof(bool));
			file.read(reinterpret_cast<char*>(&mark), sizeof(char));
			file.read(reinterpret_cast<char*>(&id), sizeof(int)); file.read(reinterpret_cast<char *>(&size), sizeof(int));
			x.resize(size);
			file.read((char *)&x[0], size); file.read(reinterpret_cast<char*>(&rows), sizeof(int)); file.read(reinterpret_cast<char*>(&cols), sizeof(int));
			pointer = new int *[rows];  //int *pointer
			for (int i = 0; i < rows; i++)
			{
				pointer[i] = new int[cols];	// pointer = new int[variable]	
			}
			for (int i = 0; i < rows; i++){
				file.read(reinterpret_cast<char*>(pointer[i]), sizeof(int)*cols);
			}
			cout << setw(50)<<white << on_green << setw(20) << "  User Id" << setw(25) << " Date/Time "<<setw(35)<<"    " << endl << reset ;
			while (!file.eof())
			{
				cout << setw(20) <<on_white<< green <<  id <<reset<< setw(30) <<white<<on_red <<  x <<setw(30)<<" " <<endl << reset;
				size = 0;	x.clear();
				for (int i = 0; i < rows; i++)
				{
					delete[] pointer[i];
				}
				delete[] pointer;
				file.read(reinterpret_cast<char*>(&singlePlayer), sizeof(bool));file.read(reinterpret_cast<char*>(&mark), sizeof(char));
				file.read(reinterpret_cast<char*>(&id), sizeof(int));file.read(reinterpret_cast<char *>(&size), sizeof(int));x.resize(size); file.read((char *)&x[0], size);
				file.read(reinterpret_cast<char*>(&rows), sizeof(int)); file.read(reinterpret_cast<char*>(&cols), sizeof(int)); pointer = new int *[rows];  //int *pointer
				for (int i = 0; i < rows; i++)
				{
					pointer[i] = new int[cols];	// pointer = new int[variable]	
				}
				for (int i = 0; i < rows; i++)
				{
					file.read(reinterpret_cast<char*>(pointer[i]), sizeof(int)*cols);
				}
			}
			return true;
		}
		else
		{
			return false;
		}
	}
	bool CheckIfGameExist(string recevieId)
	{
		int **pointer;string text = "";ifstream file("SaveGameToFile.dat", ios::binary);int rows;int cols;int val = 1;string x = "";int size;bool p;int id;char mark;
		file.read(reinterpret_cast<char*>(&p), sizeof(bool));file.read(reinterpret_cast<char*>(&mark), sizeof(char));
		file.read(reinterpret_cast<char*>(&id), sizeof(int));file.read(reinterpret_cast<char *>(&size), sizeof(int));x.resize(size);file.read((char *)&x[0], size);
		file.read(reinterpret_cast<char*>(&rows), sizeof(int));file.read(reinterpret_cast<char*>(&cols), sizeof(int));pointer = new int *[rows];  //int *pointer
		for (int i = 0; i<rows; i++)
		{
			pointer[i] = new int[cols];	// pointer = new int[variable]	
		}
		for (int i = 0; i<rows; i++){
			file.read(reinterpret_cast<char*>(pointer[i]), sizeof(int)*cols);
		}

		while (!file.eof())
		{
			for (int i = 0; i < rows; i++)
			{
				delete[] pointer[i];
			}
			delete[] pointer;
			if (recevieId == to_string(id))
			{
				return true;
			}
			file.read(reinterpret_cast<char*>(&p), sizeof(bool));file.read(reinterpret_cast<char*>(&mark), sizeof(char));file.read(reinterpret_cast<char*>(&id), sizeof(int));
			file.read(reinterpret_cast<char *>(&size), sizeof(int));x.resize(size);file.read((char *)&x[0], size);file.read(reinterpret_cast<char*>(&rows), sizeof(int));file.read(reinterpret_cast<char*>(&cols), sizeof(int));
			pointer = new int *[rows];  //int *pointer
			for (int i = 0; i<rows; i++)
			{
				pointer[i] = new int[cols];	// pointer = new int[variable]	
			}
			for (int i = 0; i<rows; i++)
			{
				file.read(reinterpret_cast<char*>(pointer[i]), sizeof(int)*cols);
			}
			
		}

		return false; 
	}
	// function to load Game from file 
	bool  loadGame()
	{
		
		string getID; char mark; cout << "Enter Game ID : " << endl;  getline(cin, getID); cin.clear();
			while (!CheckIfGameExist(getID))
			{
				cout << bold << red << "Sorry Invalid Id " << endl << reset;cout << "Enter Correct Game  ID " << endl; cin >> getID; 
			}
			string text = ""; ifstream file("SaveGameToFile.dat", ios::binary);int rows;int cols;string x = "";	int size; file.read(reinterpret_cast<char*>(&singlePlayer), sizeof(bool));
			int id; file.read(reinterpret_cast<char*>(&mark), sizeof(char));	file.read(reinterpret_cast<char*>(&id), sizeof(int)); file.read(reinterpret_cast<char *>(&size), sizeof(int));
			x.resize(size); file.read((char *)&x[0], size);file.read(reinterpret_cast<char*>(&rows), sizeof(int)); file.read(reinterpret_cast<char*>(&cols), sizeof(int));
			
			GameBoard = new int *[rows];  //int *pointer
			for (int i = 0; i < rows; i++)
			{
				GameBoard[i] = new int[cols];	// pointer = new int[variable]	
			}
			for (int i = 0; i < rows; i++){
			file.read(reinterpret_cast<char*>(GameBoard[i]), sizeof(int)*cols);
			}
			while (!file.eof())
			{
				if (getID == to_string(id))
				{
					indicator = mark; SizeOfBoard = rows; system("cls");  show(GameBoard, rows, cols); return true;
				}
				for (int i = 0; i < rows; i++)
				{
					delete[] GameBoard[i];
				}
				delete[] GameBoard; file.read(reinterpret_cast<char*>(&singlePlayer), sizeof(bool));file.read(reinterpret_cast<char*>(&mark), sizeof(char)); file.read(reinterpret_cast<char*>(&id), sizeof(int)); file.read(reinterpret_cast<char *>(&size), sizeof(int)); x.resize(size);
				file.read((char *)&x[0], size);	file.read(reinterpret_cast<char*>(&rows), sizeof(int)); file.read(reinterpret_cast<char*>(&cols), sizeof(int));GameBoard = new int *[rows];
				for (int i = 0; i < rows; i++)
				{
					GameBoard[i] = new int[cols];
				}
				for (int i = 0; i < rows; i++)
				{
					file.read(reinterpret_cast<char*>(GameBoard[i]), sizeof(int)*cols);
				}

			}
			return true;
		}
	// function to show loaded Game Board from file
	void show(int **pointer, int rows, int cols)
	{
		for (int i = 0; i < rows; i++)
		{
			cout <<  on_white << "|-------------------------------------------------------------|" << reset << endl<<endl;
			for (int j = 0; j < cols; j++)
			{
				if (char(GameBoard[i][j] == 'X') )
				{
					cout << "    " << setw(SetWidthForGameBoard()) <<bold << red << char(GameBoard[i][j]) << "   " << setw(4)<<reset;
				}
				else if (char(GameBoard[i][j]) == 'O')
				{
					cout << "    " << setw(SetWidthForGameBoard()) <<bold<< green<< char(GameBoard[i][j]) << "   " << setw(4)<<reset;
				}
				else 
					cout << "    " << setw(SetWidthForGameBoard()) << yellow<<  (GameBoard[i][j]) << "   " << setw(4)<<reset;
			}
			cout << endl<<endl<<endl;
		}
		cout  << on_white << "|-------------------------------------------------------------|" << reset<<endl;
	}
	// function to delete Game From File
	bool deleteGame()
	{
		
			chooseGameFromFile();
			string getID; char mark; cout << "Enter ID : " << endl; getline(cin, getID);
			for (int i = 0; i < 2; i++)
			{
				if (CheckIfGameExist(getID))
				{
					break;
				}
				else cout << bold << red << "Enter Correct Id " << reset << endl; i--;
				cin >> getID;
			}

			string text = ""; bool isDel = false;ifstream file("SaveGameToFile.dat", ios::binary); ofstream temp("temp.dat", ios::binary | ios::app);
			int rows;	int cols;	string x = "";	int size; file.read(reinterpret_cast<char*>(&singlePlayer), sizeof(bool));int id; file.read(reinterpret_cast<char*>(&mark), sizeof(char));
			file.read(reinterpret_cast<char*>(&id), sizeof(int)); file.read(reinterpret_cast<char *>(&size), sizeof(int));x.resize(size); file.read((char *)&x[0], size);
			file.read(reinterpret_cast<char*>(&rows), sizeof(int)); file.read(reinterpret_cast<char*>(&cols), sizeof(int));GameBoard = new int *[rows];  //int *pointer
			for (int i = 0; i < rows; i++)
			{
				GameBoard[i] = new int[cols];	// pointer = new int[variable]	
			}
			for (int i = 0; i < rows; i++){
				file.read(reinterpret_cast<char*>(GameBoard[i]), sizeof(int)*cols);
			}
			while (!file.eof())
			{
				if (getID !=to_string(id))
				{
					temp.write(reinterpret_cast<char*>(&singlePlayer), sizeof(bool)); temp.write(reinterpret_cast<char*>(&mark), sizeof(char));temp.write(reinterpret_cast<char*>(&id), sizeof(int));
					temp.write(reinterpret_cast<char *>(&size), sizeof(int)); temp.write(x.c_str(), size);temp.write(reinterpret_cast<char*>(&rows), sizeof(int)); temp.write(reinterpret_cast<char*>(&cols), sizeof(int));
					for (int i = 0; i < rows; i++){
						temp.write(reinterpret_cast<char*>(GameBoard[i]), sizeof(int)*cols);
					}
				}
				else
				{
					isDel = true;
				}
				for (int i = 0; i < rows; i++)
				{
					delete[] GameBoard[i];
				}
				delete[] GameBoard; file.read(reinterpret_cast<char*>(&singlePlayer), sizeof(bool));
				file.read(reinterpret_cast<char*>(&mark), sizeof(char)); file.read(reinterpret_cast<char*>(&id), sizeof(int)); file.read(reinterpret_cast<char *>(&size), sizeof(int)); x.resize(size);
				file.read((char *)&x[0], size);	file.read(reinterpret_cast<char*>(&rows), sizeof(int)); file.read(reinterpret_cast<char*>(&cols), sizeof(int));GameBoard = new int *[rows];
				for (int i = 0; i < rows; i++)
				{
					GameBoard[i] = new int[cols];
				}
				for (int i = 0; i < rows; i++)
				{
					file.read(reinterpret_cast<char*>(GameBoard[i]), sizeof(int)*cols);
				}
			}

			file.close();temp.close();remove("SaveGameToFile.dat");rename("temp.dat", "SaveGameToFile.dat");
			if (isDel)
			{
				
				return true;
			}
			else 
			return false;
		}
	// Core Function to handle tough time game against Computer 
	int Strategy(char token,int temploc)
	{
		int count = 0;   // variable used to get count of same token location of computer 
		char tokenTwo;
		bool isRowFind = false ;
		int res;
		
		// first check if there is any location in rows where computer is winning
		for (int i = 0; i < SizeOfBoard; i++)
		{
			count = 0;
			for (int j = 0; j < SizeOfBoard; j++)
			{
				if (char(GameBoard[i][j]) == token)
				{
					count++;
					if (count == (SizeOfBoard - 1))   // if there is a location where computer can win the game then return that location
					{
						isRowFind = true;
						tokenTwo = 'X';
						res = SearchLocation(i, token,tokenTwo,temploc); // get that location by calling SearchLocation function to search location in rows
						return res;
					}					
				}
			}
		}
		// Then check if there is any location in columns where computer is winning 
		bool isColumn = false;
		if (isRowFind==false)
		{
		int k = 0;          // to represent column number
		count = 0;
		for (int i = 0; i < SizeOfBoard; i++)
		{
			count = 0;
			for (int j = 0; j < SizeOfBoard; j++)
			{
			if (GameBoard[j][k] ==token)
			{
			count++;
			if (count == (SizeOfBoard - 1))
			{
			tokenTwo = 'X';
			isColumn = true;
			res = SearchLocationInColumn(k, token,tokenTwo,temploc);  //call SearchLocationInColumn () function to return that location
			return res;
			}
			}
			}
		
			k++;
		}
		}
		// else find if there is any location in right diogonals where computer is winning 
		bool isRightDiogonal = false;
		if (isColumn == false)
		{
			int checker = 0;  count = 0;
			for (int i = 0; i < SizeOfBoard; i++)
			{
				if (char(GameBoard[i][i]) == token)
				{
					count++;
				}
			}
			if (count == SizeOfBoard - 1)
			{
				isRightDiogonal = true;
				tokenTwo = 'X';
				for (int i = 0; i < SizeOfBoard; i++)
				{
					if (char(GameBoard[i][i]) != token && char(GameBoard[i][i]) != tokenTwo)
					{
						return i*SizeOfBoard + i + 1;
					}
					else
					{
						isRightDiogonal = false;
					}		
				}
			}	
			}
			// else find if there is any location in inverse diogonals where computer is winning 
		bool isInverseDiogonal = false;
		if (isRightDiogonal == false)
		{
			count = 0;
			int z = SizeOfBoard - 1;
			for (int i = 0; i < SizeOfBoard; i++)
			{
				if (char(GameBoard[i][z]) == token)
				{
					count++;
				}
				z--;
			}
			if (count == SizeOfBoard - 1)
			{
				isInverseDiogonal = true;
				tokenTwo = 'X';
				z = SizeOfBoard - 1;
				for (int i = 0; i < SizeOfBoard; i++, z--)
				{
					if (char(GameBoard[i][z]) != token && char(GameBoard[i][z]) != tokenTwo)
					{
						return i*SizeOfBoard + z + 1;			
					}
					else
					{
						isInverseDiogonal = false;
					}
				}
			}	
		}
		
		// If there is no location in rows / columns or diogonals where computer is winning then search location where user is winning and then put your token there 
		
		bool isUserWinningInRows = false; // search location in rows where user can win the game then 
		
		if (isInverseDiogonal == false)	   
		{
			tokenTwo = 'O';		token = 'X';
			for (int i = 0; i < SizeOfBoard; i++)
			{
				count = 0;
				for (int j = 0; j < SizeOfBoard; j++)
				{
					if (char(GameBoard[i][j]) == token)
					{
						count++;         //count=2
					}
					if (count == SizeOfBoard - 1)     //true
					{
						isUserWinningInRows = true;
						return (SearchLocation(i, 'X', tokenTwo, temploc)); // call function to return location 
					}
				}
			}	
		}
		bool isUserWinningInColumns = false;   // now check if user winning in anywhere in columns then give him tough time 
		if (isUserWinningInRows == false)
		{
			token = 'X';	tokenTwo = 'O';
			int e = 0;
			for (int i = 0; i < SizeOfBoard; i++)
			{
				count = 0;
				for (int j = 0; j < SizeOfBoard; j++)
				{
					if (char(GameBoard[j][e]) == token)
					{
						count++;
						if (count == SizeOfBoard - 1)
						{
							isUserWinningInColumns = true;
							return (SearchLocationInColumn(e, token,tokenTwo,temploc));// call function to get that location 
						}
					}
				}
				e++;
			}
		}
		bool isUserWinningInRightDiogonal = false; // now check if user is winning anywhere in diogonals
		if (isUserWinningInColumns == false)
		{
			token = 'X';tokenTwo = 'O';
			count = 0;
			for (int i = 0; i < SizeOfBoard; i++)
			{
				if (char(GameBoard[i][i]) == token)
				{
					count++;
				}
			}
			if (count == SizeOfBoard - 1)
			{
				isUserWinningInRightDiogonal = true;  // if user winning in right diogonal then give him tough time there 
				for (int j = 0; j < SizeOfBoard; j++)
				{
					if (char(GameBoard[j][j]) != token && char(GameBoard[j][j]) != tokenTwo)
					{
						return j*SizeOfBoard + j + 1;
					}
					else
					{
						isUserWinningInRightDiogonal = false;
					}
				}
			}
		}
		//similary check if there is any location in inverse diogonal where user can win game then give him tough time there 
		bool isUserWinningInInverseDiogonal = false;
		if (isUserWinningInRightDiogonal == false)
		{
			token = 'X';	tokenTwo = 'O';   int x = SizeOfBoard - 1;	count = 0;
			for (int i = 0; i < SizeOfBoard; i++, x--)
			{
				if (char(GameBoard[i][x]) == token)
				{
					count++;
				}
			}
			if (count == SizeOfBoard - 1)
			{
				isUserWinningInInverseDiogonal = true;
				x = SizeOfBoard - 1;
				for (int i = 0; i < SizeOfBoard; i++,x--)
				{
					if (char(GameBoard[i][x]) != token && char(GameBoard[i][x]) != tokenTwo)
					{
						return i*SizeOfBoard + x + 1;
					}
					else
					{
						isUserWinningInInverseDiogonal = false;
					}
				}
			}
		}
		if (isUserWinningInInverseDiogonal == false)    // if no location found then return the same location that was recieved 
		{
			return temploc;
		}
			}
			
	// first it check location for computer in rows where it can win and if not found then it found location where user can win then return that location
	int SearchLocation(int row,char token,char tokenTwo,int loc)
	{
		//row = 0 token = X
		bool isTrue = true;
		for (int i = 0; i < SizeOfBoard; i++)
		{
			if (char(GameBoard[row][i]) != token && char(GameBoard[row][i])!=tokenTwo)
			{
				
				return (row*SizeOfBoard + i + 1);
			}
			else
			{
				isTrue = false;
			}
		}
		if (!isTrue)
		{
			return loc;
		}
	}
		// first it check location for computer in columns where it can win and if not found then it found location where user can win then return that location
	int SearchLocationInColumn(int column, char token,char tokenTwo,int temploc)
	{
		//2 X O 6
		bool isTrue = false;
		for (int i = 0; i < SizeOfBoard; i++)
		{
			if (char(GameBoard[i][column]) != token && char(GameBoard[i][column]) != tokenTwo)
			{
				return (i*SizeOfBoard + column + 1);
			}
			else
			{
				isTrue = true;
			}
		}
		if (isTrue)
		{
			return temploc;
		}
	}
	//function to validate location  just to avoid overwriting of location entered by computer 
	bool validateLocation(int loc)
	{
		int k = 0;
		for (int i = 0; i < SizeOfBoard; i++)
		{
			for (int j = 0; j < SizeOfBoard; j++)
			{
				k++;
				if (k == loc)
				{
					if (GameBoard[i][j] == 'X' || GameBoard[i][j] == 'O')
					{
						return false;
					}
				}
			}
		}
		return true;
	}
	void fillBoard(int position , char token)   // function to fill the board by tokens entered by players
	{

		if (position > 0 && position <= SizeOfBoard*SizeOfBoard)   //if location is within limit  then proceed next
		{
			if (token == 'X')
			{
				system("cls");
				cout << " Human: Select a location = > : " << position << endl;

				getBoard(position, 'X'); // call getBoard function to get the latest board right after the turn of player 1

				// if there are successive enteries either in rows , column or diogonals then player 1 win
				if (DecisionByDiogonal()  || DecisionByRows() || getDecisionByColumns())
				{
					cout << setw(20) << "--------------------" << endl;
					cout << setw(20) << "  HUMAN 1 WIN  |" << endl;
					cout << setw(20) << "--------------------" << endl;
					Restart();       // if HUMAN win the give option to play again 
				}
			}
			else 
			{
				system("cls");
				string player;
				if (singlePlayer == false)
				{
					player = "Human";
					cout << "  Location selected by "<< player <<" 2 is = > :  " << position << endl;
				}
				else
				{
					player = "Computer ";
					cout << "  Location selected by "<< player <<" is = > :  " << position << endl;
				}
				getBoard(position, 'O'); // call getBoard function to get the latest board right after the turn of player 2
				// if there are successive enteries either in rows , column or diogonals then player 2 win
				if (DecisionByDiogonal()  || DecisionByRows()  || getDecisionByColumns())
				{
					cout << setw(20) << "--------------------" << endl;
					cout << setw(20)<< player<<" Win |" << endl;
					cout << setw(20) << "--------------------" << endl;
					Restart();       // if player 2 win the give option to play again 
				}
			}
		}
		else         // if locationn is not in range then then turn is lost 
		{
			cout << "Sorry Location out of range " << endl;
			cout << "Your turn is lost " << endl;
		}
	}
	void getBoard(int loc, char mark)  // function to get the board after player turns 
	{
		
		for (int i = 0; i < SizeOfBoard; i++)
		{
			cout << on_white << "|-------------------------------------------------------------|" << reset << endl<<endl;
			for (int j = 0; j < SizeOfBoard; j++)
			{
				if (GameBoard[i][j] == loc)
				{
					GameBoard[i][j] = mark;
				}

				 if (char(GameBoard[i][j] == 'X' ))
				{
					
					cout << "    " << setw(SetWidthForGameBoard()) << red << char(GameBoard[i][j]) << "   " << setw(4)<<reset;

				}
				else if (char(GameBoard[i][j] == 'O'))
				{
					
					cout << "    " << setw(SetWidthForGameBoard()) <<green<< char(GameBoard[i][j]) << "   " << setw(4)<<reset;

				}
				else
					
					cout << "    " << setw(SetWidthForGameBoard()) << yellow<< (GameBoard[i][j]) << "   " << setw(4)<<reset;
			}
			cout << endl<<endl<<endl;
		}
		cout <<  on_white << "|-------------------------------------------------------------|" << reset << endl;

	}
	
	bool checkIfGameDraw()       //function to check if the game is draw or not
	{
		for (int i = 0; i < SizeOfBoard; i++)
		{
			for (int j = 0; j < SizeOfBoard; j++)
			{
				if (GameBoard[i][j] > 0 && GameBoard[i][j] <= SizeOfBoard*SizeOfBoard)
				{
					return false;
				}
			}
		}
		return true;
	}
	bool  DecisionByDiogonal()   //function to check successive enteries by both player in diogonals
	{
		int checker = 0;
		int k = SizeOfBoard - 1;
		for (int i = 0; i < SizeOfBoard - 1; i++)
		{
			if (GameBoard[i][i] == GameBoard[i + 1][i + 1])
			{
				checker++;
			}
		}
		if (checker == SizeOfBoard - 1)
		{
			return true;
		}
		else
		{
			checker = 0;
			for (int i = 0; i < SizeOfBoard - 1; i++)
			{
				if (GameBoard[i][k] == GameBoard[i + 1][k - 1])
				{
					checker++;
				}
				k--;
			}
			if (checker == SizeOfBoard - 1)
			{
				return true;
			}
		}
		return false;
	}
	//To check if there are n successive token of player 1 or player 2 in Any Row of the board
	bool DecisionByRows()
	{
		int checker = 0;
		for (int i = 0; i < SizeOfBoard; i++)
		{
			checker = 0;
			for (int j = 0; j < SizeOfBoard - 1; j++)
			{
				if (GameBoard[i][j] == GameBoard[i][j + 1])
				{
					checker++;
				}
				if (checker == SizeOfBoard - 1)
				{
					return true;
				}
			}
		}
		return false;
	}
	//function to check if there  are n successive n token of player  1 or player 2 in any column of the board 
	bool getDecisionByColumns()
	{
		int checker = 0;
		int k = 0;
		int count = 0;
		for (int i = 0; i < SizeOfBoard; i++)
		{
			checker = 0;
			for (int j = 0; j < SizeOfBoard - 1; j++)
			{
				if (GameBoard[j][k] == GameBoard[j + 1][k])
				{
					checker++;
					count = checker;
				}
			}
			k++;
			if (count == SizeOfBoard - 1)
			{
				return true;
			}
		}
		return false;
	}
	int SetWidthForGameBoard()   //function to set width for game board according to the grid 
	{
		int SetWidth = 0;
		if (SizeOfBoard == 3)
		{
			SetWidth = 10;
		}
		else if (SizeOfBoard == 4)
		{
			SetWidth = 6;
		}
		else
		{
			SetWidth = 4;
		}
		return SetWidth;
	}
	void DesignBoard()       //function to show Designed Board
	{
		system("cls");
		for (int i = 0; i < SizeOfBoard; i++)
		{
			
			cout <<  on_white << "|-------------------------------------------------------------|" << endl<<endl<<reset;
			for (int j = 0; j < SizeOfBoard; j++)
			{

				cout<< yellow << "    " << setw(SetWidthForGameBoard()) << (GameBoard[i][j]) << "   " << setw(4)<<reset;

			}
			cout << endl<<endl;
		}
		cout <<on_white<< "|-------------------------------------------------------------|" << endl<<reset;
	}
	void GameInstruction()  //function to show the game instruction 
	{
		cout << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

		cout << "Game Instructions" << endl;
		cout << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "1->: Token for player 1 is X " << endl;
		cout << "___________________________" << endl;
		cout << "2->: Token for player 2 is 0 " << endl;
		cout << "___________________________" << endl;
		cout << "3->: Overwritten will be ignored " << endl;
		cout << "________________________________" << endl;
		cout << "4->: In case of no Result Game will be draw " << endl << endl;;
		cout << "******************************" << endl;
		MenuAfterInstruction();      //function to handling process after displaying instruction 
	}
	void MenuAfterInstruction()
	{
		cout << setw(50) << "---------------------------------------" << endl;
		cout << setw(41) << "1 :Go back to Menu" << endl;
		cout << setw(41) << "2 :Exit From Game " << endl;
		cout << setw(50) << "---------------------------------------" << endl;
		int opt;
		cout << "Choose Option (1 / 2 )  -> ";
		cin >> opt;
		if (opt == 1)      // if option is 1 then go back to menu by calling constructer
		{
			system("cls");
			TicTacToi();
		}
		else if (opt == 2)
		{
			showEndMessage();     // if option is 2 then show End message and exit from the game 
			exit(0);
		}
		else  // if option is other than 1 or 2 then give an error message and call restrat function 
		{
			ShowErrorMessage();
			Restart();
		}
	}
	void showEndMessage()  //function to show Ending message 
	{
		cout << "------------------------------------" << endl;
		cout << " * ) " << "Thanks For  Playing Game " << endl;
		cout << "Developed By Muhammad Atif Akram" << endl;
		cout << "Special Thanks to PUCIT Game Development Community " << endl;
		cout << "------------------------------------" << endl;
		exit(0);
	}
	void Restart()  // function to provide opportunity to play again 
	{
		
		string Yes_No_Option;
		cout << "Want to Start Game Setup Again  [Y/N]: " << endl;
		getline(cin, Yes_No_Option);
		if (Yes_No_Option == "Y" || Yes_No_Option == "y")
		{
			system("cls"); 
			TicTacToi();
		}
		else if (Yes_No_Option == "n" || Yes_No_Option == "N")
		{
			showEndMessage();
		}
		else
		{
			ShowErrorMessage();
			exit(0);
		}
		
	}
	void ShowErrorMessage()       //function to show error message 
	{
		cout << "Sorry You Entered Invalid Choice" << endl;
	}
	~TicTacToi()           // destructer to release the memory 
	{
		for (int i = 0; i < SizeOfBoard; i++)
		{
			delete[] GameBoard[i];
		}
		delete[] GameBoard;
	}
};
int main()
{
	HWND console = GetConsoleWindow(); RECT r;GetWindowRect(console, &r);MoveWindow(console, r.left, r.top, 1500, 700, TRUE); 
	TicTacToi();
	return 0;
}
