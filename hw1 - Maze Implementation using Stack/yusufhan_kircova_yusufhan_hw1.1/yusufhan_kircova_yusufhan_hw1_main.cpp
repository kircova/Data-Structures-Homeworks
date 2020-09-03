#include <iostream>
#include "Stack.h"
#include <fstream>
#include <random>
#include <vector>
using namespace std;

struct Cell//Each cell of the matrix,
{
	Cell()//Constructor has initial values, which indicates that a cell has 4 walls when created.
	{
		Left = 1;
		Right = 1;
		Up = 1;
		Down = 1;
		IsVisited = false;
	}
	int row;
	int col;
	int Left;
	int Right;
	int Up;
	int Down;
	bool IsVisited;
};

int CreateRandomInt(int min, int max)//A small random number generator function
{
	int m = rand() % max + min;
	return m;
}

bool HasAllVisitedNeigbours(vector<vector<Cell>> matrix, Cell cell, int M, int N)//This function checks if a cell's neighbours cells are all previously visited or not
{
	bool HasAllVisited = false;
	if(cell.row == 0)//Program considers all of the extreme cases(4 edges of the maze) and avoids vector range error.
	{//This complex and long if statement considers all 4 corners and 4 edges of the square, since those cases are most probable of giving an error, program handles with them individually.
		if(cell.col == 0)
		{
			if(matrix[cell.row + 1][cell.col].IsVisited && matrix[cell.row][cell.col + 1].IsVisited)//Checks if the right cell is visited previously 
			{
				HasAllVisited = true;
				return HasAllVisited;
			}
		}
		else if(cell.col == N - 1)
		{
			if(matrix[cell.row + 1][cell.col].IsVisited && matrix[cell.row][cell.col-1].IsVisited)//Checks if the left cell is visited previously 
			{
				HasAllVisited = true;
				return HasAllVisited;
			}
		}
		else
		{
			if(matrix[cell.row + 1][cell.col].IsVisited && matrix[cell.row][cell.col-1].IsVisited && matrix[cell.row][cell.col + 1].IsVisited)//Checks for the rest of the edge if there is a unvisited neighbour
			{
				HasAllVisited = true;
				return HasAllVisited;
			}
		}
	}
	if(cell.row == M - 1)
	{
		if(cell.col == 0)
		{
			if(matrix[cell.row - 1][cell.col].IsVisited && matrix[cell.row][cell.col + 1].IsVisited)//Checks if the right cell is visited previously 
			{
				HasAllVisited = true;
				return HasAllVisited;
			}
		}
		else if(cell.col == N - 1)
		{
			if(matrix[cell.row - 1][cell.col].IsVisited && matrix[cell.row][cell.col - 1].IsVisited)//Checks if the left cell is visited previously 
			{
				HasAllVisited = true;
				return HasAllVisited;
			}
		}
		else
		{
			if(matrix[cell.row][cell.col - 1].IsVisited && matrix[cell.row][cell.col + 1].IsVisited && matrix[cell.row - 1][cell.col].IsVisited)//Checks for the rest of the edge if there is a unvisited neighbour
			{
				HasAllVisited = true;
				return HasAllVisited;
			}
		}
	}
	if(cell.col == N - 1)
	{
		if(cell.row == 0)
		{
			if(matrix[cell.row + 1][cell.col].IsVisited && matrix[cell.row][cell.col - 1].IsVisited)
			{
				HasAllVisited = true;
				return HasAllVisited;
			}
		}
		else if(cell.row == M - 1)
		{
			if(matrix[cell.row - 1][cell.col].IsVisited && matrix[cell.row][cell.col - 1].IsVisited)
			{
				HasAllVisited = true;
				return HasAllVisited;
			}
		}
		else
		{
			if(matrix[cell.row + 1][cell.col].IsVisited && matrix[cell.row - 1][cell.col].IsVisited && matrix[cell.row][cell.col - 1].IsVisited)
			{
				HasAllVisited = true;
				return HasAllVisited;
			}
		}
	}
	if(cell.col == 0)
	{
		if(cell.row == 0)
		{
			if(matrix[cell.row + 1][cell.col].IsVisited && matrix[cell.row][cell.col + 1].IsVisited)
			{
				HasAllVisited = true;
				return HasAllVisited;
			}
		}
		else if(cell.row == M - 1)
		{
			if(matrix[cell.row - 1][cell.col].IsVisited && matrix[cell.row][cell.col + 1].IsVisited)
			{
				HasAllVisited = true;
				return HasAllVisited;
			}
		}
		else
		{
			if(matrix[cell.row + 1][cell.col].IsVisited && matrix[cell.row - 1][cell.col].IsVisited && matrix[cell.row][cell.col + 1].IsVisited)
			{
				HasAllVisited = true;
				return HasAllVisited;
			}
		}
	}
	if(cell.row + 1 < M && cell.row - 1 >= 0 && cell.col +  1 < N && cell.col - 1 >= 0)//If statement checks the rest of the maze, other than edges and cornersi for unvisited neighbours.
	{
		if(matrix[cell.row + 1][cell.col].IsVisited && matrix[cell.row-1][cell.col].IsVisited && matrix[cell.row][cell.col + 1].IsVisited && matrix[cell.row][cell.col-1].IsVisited)
		{
			HasAllVisited = true;
			return HasAllVisited;
		}
	}
	return HasAllVisited;//If there is not a unvisited neighbour function returns true, else false.
}

void RandomMove(Stack<Cell> & stack, vector<vector<Cell>> & matrix, int M, int N)//Function is used to break down walls, and move the cells.
{
	int row, col;
	while(!stack.isEmpty())//This loop continues till the stack became empty, which wont happpen until the whole maze is created.
	{
		Cell xd = stack.top();
		row = xd.row; col = xd.col;
		int rnd = CreateRandomInt(1,4); //1 down, 2 up, 3 right, 4 left

		if(rnd == 1 && xd.row - 1 >= 0 && matrix[xd.row - 1][xd.col].IsVisited == false)//Down movement, 
		{
			matrix[xd.row][xd.col].Down = 0;//Breaking down walls.
			matrix[xd.row - 1][xd.col].Up = 0;//Breaking down walls for the next cell.
			matrix[xd.row - 1][xd.col].IsVisited = true;//Making sure the cell is now visited.
			stack.push(matrix[xd.row - 1][xd.col]);//Pushing the new cell into the matrix
		}
		else if(rnd == 2 && xd.row < M - 1 && matrix[xd.row + 1][xd.col].IsVisited == false)//Up movement, 
		{
			matrix[xd.row][xd.col].Up = 0;
			matrix[xd.row + 1][xd.col].Down = 0;
			matrix[xd.row + 1][xd.col].IsVisited = true;
			stack.push(matrix[xd.row + 1][xd.col]);
		}
		else if(rnd == 3 && xd.col < N -1 && matrix[xd.row][xd.col + 1].IsVisited == false)//Right movement, 
		{
			matrix[xd.row][xd.col].Right = 0;
			matrix[xd.row][xd.col + 1].Left = 0;
			matrix[xd.row][xd.col + 1].IsVisited = true;
			stack.push(matrix[xd.row][xd.col + 1]);
		}
		else if(rnd == 4 && xd.col - 1 >= 0 && matrix[xd.row][xd.col - 1].IsVisited == false)//Left movement, 
		{
			matrix[xd.row][xd.col].Left = 0;
			matrix[xd.row][xd.col - 1].Right = 0;
			matrix[xd.row][xd.col - 1].IsVisited = true;
			stack.push(matrix[xd.row][xd.col - 1]);
		}
		else if(HasAllVisitedNeigbours(matrix,stack.top(),M,N))//If there is not a single visitable neighbour then, we pop one cell from the stack.
		{
			stack.pop();
		}
	}
}

bool HasVisitableNeighbour(vector<vector<Cell>> matrix, Cell cell, int M, int N) //Function is used in SolveMaze Function, is utilized if there is a neighbour cell which is visitable.
{
	if(cell.Up != 1 && !matrix[cell.row + 1][cell.col].IsVisited)//Checking walls and if the next cell is visitable or not.
	{
		return true;//Upper cell
	}
	else if(cell.Down != 1 && !matrix[cell.row -1][cell.col].IsVisited)//Down cell
	{
		return true;
	}
	else if(cell.Left != 1 && !matrix[cell.row][cell.col - 1].IsVisited)//Left cell
	{
		return true;
	}
	else if(cell.Right != 1 && !matrix[cell.row][cell.col + 1].IsVisited)//Right Cell
	{
		return true;
	}
	else
	{
		return false;//Returns falls if there are no cells which is visitable.
	}
	
}

Stack<Cell> SolveMaze(vector<vector<Cell>> matrix, int startX, int startY, int ExitX, int ExitY, int M, int N)
{
	Cell entry = matrix[ExitY][ExitX];//Path starts from the end, since the output starts from 0,0 
	Stack<Cell> temp_Stack;
	temp_Stack.push(entry);
	int row, col;
	while(!(temp_Stack.top().col == startX && temp_Stack.top().row == startY))//Until the program reaches the start point it wont stop
	{
		Cell xd = temp_Stack.top();
		row = xd.row; col = xd.col;
		int rnd = CreateRandomInt(1,4); //1 down, 2 up, 3 rigt, 4 left

		if(rnd == 1 && xd.row - 1 >= 0 && matrix[xd.row - 1][xd.col].IsVisited == false && matrix[xd.row][xd.col].Down != 1)//Checks for walls and if the cell is previously visited.
		{
			matrix[xd.row - 1][xd.col].IsVisited = true;
			temp_Stack.push(matrix[xd.row - 1][xd.col]);
		}
		else if(rnd == 2 && xd.row < M - 1 && matrix[xd.row + 1][xd.col].IsVisited == false && matrix[xd.row][xd.col].Up != 1)
		{
			matrix[xd.row + 1][xd.col].IsVisited = true;
			temp_Stack.push(matrix[xd.row + 1][xd.col]);
		}
		else if(rnd == 3 && xd.col < N -1 && matrix[xd.row][xd.col + 1].IsVisited == false && matrix[xd.row][xd.col].Right != 1)
		{
			matrix[xd.row][xd.col + 1].IsVisited = true;
			temp_Stack.push(matrix[xd.row][xd.col + 1]);
		}
		else if(rnd == 4 && xd.col - 1 >= 0 && matrix[xd.row][xd.col - 1].IsVisited == false && matrix[xd.row][xd.col].Left != 1)
		{
			matrix[xd.row][xd.col - 1].IsVisited = true;
			temp_Stack.push(matrix[xd.row][xd.col - 1]);
		}
		else if(!HasVisitableNeighbour(matrix, temp_Stack.top(), M, N))//If cells has no visitable neighbour it pops.
		{
			temp_Stack.pop();
		}
	}
	return temp_Stack;
}

void WritePath(Stack<Cell> stack, int ID, int startX, int startY, int ExitX, int ExitY)//Writing path into a file.
{
	fstream file; 
	string name;
	name= "maze_";
	name.append(to_string(ID) + "path_" + to_string(startX) + "_" + to_string(startY) + "_" + to_string(ExitX) + "_" + to_string(ExitY) +".txt");
	file.open(name,ios::out); 
	while (!stack.isEmpty())//Pops till the file is ready
	{
		file << stack.top().col << " " << stack.top().row;
		stack.pop();
		file << endl;
	}
	file.close(); 
}

int main()
{
	int K, M, N;
	cout << "Enter the number of mazes: ";
	cin >> K;
	cout << "Enter the number of rows and columns (M and N): ";
	cin >> M >> N;

	vector<vector<vector<Cell>>> Mazes; // A 3D Vector, which is a vector of 2D mazes. List of mazes

	for (int q = 0; q < K; q++)//K times iteration, K mazes created
	{
		vector<vector<Cell>> matrix(M, vector<Cell>(N));//Creating a 2D Vector for the cells
		for (int p = 0; p < M; p++)
		{
			for (int z = 0; z < N; z++)
			{
				Cell temp_Cell; 
				temp_Cell.row = p; temp_Cell.col = z;
				matrix[p][z] = temp_Cell;
			}
		}
		Cell xd; xd.row = 0; xd.col = 0;
		xd.IsVisited = true;//First 0,0 cell is default visited.
		Stack<Cell> temp_Stack;
		temp_Stack.push(xd);
		matrix[0][0].IsVisited = true;
		RandomMove(temp_Stack, matrix, M, N);//Calling the move function to get the stack

		Mazes.push_back(matrix);//Pushing the created maze into, maze list
		fstream file; string name;
		string id = to_string(q + 1);
		name = "maze_";
		name.append(id);
		name.append(".txt");
		file.open(name,ios::out); 
		file << M << " " << N << endl;
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N ; j++)
			{
				file << "x=" << matrix[i][j].col << " ";
				file << "y=" << matrix[i][j].row << " ";
				file << "l=" << matrix[i][j].Left << " ";
				file << "r=" << matrix[i][j].Right << " ";
				file << "u=" << matrix[i][j].Up << " ";
				file << "d=" << matrix[i][j].Down;
				file << endl;
			}
		}
		file.close(); 
	}
	cout << "All mazes are generated." << endl;
	int ID, startX, startY, ExitX, ExitY;
	cout << "Enter a maze ID between 1 to "<< K <<" inclusive to find a path: ";
	cin >> ID;
	cout << "Enter x and y coordinates of the entry points (x,y) or (column,row):";
	cin >> startX >> startY;
	cout << "Enter x and y coordinates of the exit points (x,y) or (column,row):";
	cin >> ExitX >> ExitY;
	
	vector<vector<Cell>> ChosenMaze = Mazes[ID - 1];
	for (int i = 0; i < ChosenMaze.size(); i++)//Clearing the maze so that each cell would be unvisited
	{
		for (int j = 0; j < ChosenMaze[0].size(); j++)
		{
			ChosenMaze[i][j].IsVisited = false;
		}
	}
	Stack<Cell> temp = SolveMaze(ChosenMaze, startX, startY, ExitX, ExitY, M, N);
	WritePath(temp, ID, startX, startY, ExitX, ExitY);

	return 0;
}