//Source code by ~Waqar Asghar~
//L1S21BSSE0119
 
#include <iostream>
#include <fstream>
#include <conio.h>
using namespace std;

void helloUser(ofstream & , string *);
int mainMenu(string);
void Run(int , int [] , int , int);
void newgame(ifstream & , int & , int & , int  );
void resumegame();
void levels();
//void highRecord();
int calculateRowsInFile(ifstream &);
int calculateColumnsInFile(ifstream & ,int &);
void saveGridToArray(ifstream &file1 , char **grid , int &R , int &C);
bool foundInDictionary(ifstream & );
void displayGrid(char ** ,int , int );
int highRecord(ifstream &, int * , int  , int );
void copyData(int * , int * , int );

int main()
{
	ofstream playerNames("players.txt" , ios::app);
	string name;
	helloUser(playerNames , &name);
	playerNames.close();
	int totalScores = 0 ;
	int  size = 1 ;
	int *scores = new int [size];
	int choice = 0;
	choice = mainMenu(name);
	Run(choice , scores , totalScores , size);
	system("pause");
    return 0; 
}

void helloUser(ofstream &playerNames , string *name )
{
	cout<<"Hi , please enter your name: \n";
	getline(cin , *name);
	playerNames<<*name;
	playerNames<<endl;
	
}

int mainMenu(string name)
{
	int x;
	menu:
	cout<<"Hi , " <<name <<" please select an option \n";
	cout<<"1. New Game \n";
	cout<<"2. Resume Game \n";
	cout<<"3. Levels \n";
	cout<<"4. High Record \n";
	cout<<"5. Exit \n";
	cin>>x;
	if(x<1 || x>5)
	{
		cout<<"Please select a correct value from given menu. Try Again! \n";
		system("pause");
		system("cls");
		goto menu;
	}
	return x;
}
void Run(int choice , int *scores , int totalScores , int size )
{
	if(choice==1)
	{
		int rows = 0 , cols = 0 ;
		ifstream file("board.txt");
		newgame(file , rows , cols , totalScores);
		file.close();
	}
	else if(choice==2)
	{
		resumegame();
	}
	else if(choice==3)
	{
		levels();
	}
	else if(choice==4)
	{
		ifstream scorefile("score.txt");
		int highestScore = highRecord(scorefile , scores , totalScores , size);
		cout<<"Highest Score is : " <<highestScore;
	}
	else{
		//exit
	}
}

void newgame(ifstream &file , int &R , int &C , int totalScores )
{
	R =  calculateRowsInFile(file);
	C = calculateColumnsInFile(file , R);
	char **grid = new char*[R];
	for(int i=0;i<R;i++)
	{
		grid[i] = new char[C];
	}
	int score = 0  , attempts = 3;
	ifstream file1("board.txt");
	saveGridToArray(file1 , grid , R , C);
	DISPLAY:
	displayGrid(grid , R , C);
	cout<<endl;
	cout<<" SCORE : " <<score <<" |  Remaining Attempts : " <<attempts <<endl;
	
	ifstream dictionary("dictionary.txt");
	bool found = foundInDictionary(dictionary);
	bool find = true;
	if(found)
	{
		cout<<"Word found \n";
		{
			score++;
			system("cls");
			goto DISPLAY;
			
		}
	}
	else
	{
		cout<<"Word not found \n";
		attempts--;
		system("cls");
		if(attempts>0)
		{
			goto DISPLAY;
		}
		else
		{
			cout<<" Try Again Next time \n";
			cout<<" Your High Score : " <<score;
			ofstream scores("Score.txt" , ios::app ) ;
			scores<<score;
			scores<<endl;
			scores.close();
			totalScores++;
		}
		
		
	}
}

void resumegame()
{
	cout<<endl;
}

void levels()
{
	cout<<endl;
}

//void highRecord()
//{
//	cout<<endl;
//}

int calculateRowsInFile(ifstream &file)
{
	int rows = 0;
	string row;
	while(!file.eof())
	{
		getline(file , row);
		rows++;
	}
	return rows-1;
}

int calculateColumnsInFile(ifstream &file ,int &R)
{
	int count = 0;
	char a;
	for(int i=0;i<R;i++)
	{
		file>>a;
		if(a!='\n')
		{
			count++;
		}
	}
	
	return count;
}

void saveGridToArray(ifstream &file1 , char **grid , int &R , int &C)
{
	char a;
	for(int i=0;i<R;i++)
	{
		file1>>a;
		for(int j=0;j<C;j++)
		{
			grid[i][j] = a;
			file1>>a;
		}
	}
}

bool foundInDictionary(ifstream &dictionary )
{
	string word;
	cout<<"Enter a word to search : " ;
	cin>>word;
	string data;
	while(!dictionary.eof())
	{
		dictionary>>data;
		if(data==word)
		{
			return true;
			break;
		}
		else{
			continue;
		}
		
	}
	
	return false;
}

void displayGrid(char **grid ,int R , int C)
{
	for(int i=0;i<R;i++)
	{
		for(int j=0;j<C;j++)
		{
			cout<<grid[i][j] <<"  ";
		}
		cout<<endl;
	}
}

int highRecord(ifstream &scorefile , int *scores , int totalScores , int size )
{
	int hs;
	int sizeOfArray = size;
	for(int i=0;i<totalScores;i++)
	{
		if(i>=sizeOfArray)
		{
			sizeOfArray *= 2;
			int *temp = new int [sizeOfArray];
			copyData(scores , temp , size);
		}
	
	scorefile>>scores[i];
	hs = scores[i];
	if(hs<scores[i])
	{
		hs = scores[i];
	}
		
	}
	
	
	return hs;
}

void copyData(int *scores , int *temp , int size)
{
	for(int i=0 ;i<size;i++ )
	{
		temp[i]=scores[i];
	}
	delete []scores;
	scores = temp;
}
