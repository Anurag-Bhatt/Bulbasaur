#include <raylib.h>
#include <iostream>
#include <fstream>


using namespace std;


const int screenWidth = 800;
const int screenHeight = 800;

const int Rows = 20;
const int Cols = 20;

const int cellWidth = screenWidth/Cols;
const int cellHeight = screenHeight/Rows;

const string title = "Mamta Madarchod";
const string debugLogFileName = "debugLog.txt";

fstream debugLog;


bool startAutomata = false;

typedef struct Cell{

    int xPos;
    int yPos;

    bool isAlive;


} Cell;

Cell grid[Cols][Rows], newGrid[Cols][Rows];

void DrawCell(Cell);
bool ValidIndex(int,int);
void SetCellAlive(Cell*);
void SetCellDead(Cell*);

void CheckForAliveCells();

void Intialize();

void switchCell();
int CountNeighbour(int xPos, int yPos);
void CopyGrid();
void cellStatus();

bool isAlive(int, int);

int main()
{
    
    debugLog.open(debugLogFileName,ios::out);

    Intialize();

    while (!WindowShouldClose())
    {

        CheckForAliveCells();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if(startAutomata){
        // Switch  grid status according to the rules;
            switchCell();
            CopyGrid();
            startAutomata = false;
        }

        for (int i = 0; i < Cols; i++)
        {
            for (int j = 0; j < Rows; j++)
            {
               DrawCell(grid[i][j]);
            }
            
        }
        

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void Intialize(){
    for (int i = 0; i < Cols; i++)
        {
            for (int j = 0; j < Rows; j++)
            {
                // Initialize grids
                grid[i][j]      =  Cell{i,j,false};
                newGrid[i][j]   =  Cell{i,j,false};
            }
            
        }
   

    InitWindow(screenWidth, screenHeight, title.c_str());
    SetTargetFPS(60);
}


void DrawCell(Cell cell){
    
    if(cell.isAlive == true)
        DrawRectangle(cell.xPos * cellWidth,cell.yPos * cellHeight, cellWidth, cellHeight, PINK);
    else
        DrawRectangleLines(cell.xPos * cellWidth,cell.yPos * cellHeight, cellWidth, cellHeight, BLACK);
}

bool ValidIndex(int xPos, int yPos){
    
    return xPos >= 0 && xPos < screenWidth && yPos >= 0 && yPos < screenHeight;

}

void SetCellAlive(Cell *cell){

    cell->isAlive = true;
    // Print grid status
    // cellStatus();
}

void SetCellDead(Cell *cell){

    cell->isAlive = false;
    
}

void CheckForAliveCells(){


    Vector2 mPos = GetMousePosition();
    int xIndex = mPos.x/cellWidth;
    int yIndex = mPos.y/cellHeight;

    if(IsKeyPressed(KEY_C)){

        for (int i = 0; i < Cols; i++)
        {
            for (int j = 0; j < Rows; j++)
            {
               SetCellDead(&grid[i][j]);
            }
            
        }

    }


    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        
    debugLog << "X position: " << xIndex << "Y position: " << yIndex << std::endl;

     if(ValidIndex(xIndex,yIndex)){

        SetCellAlive(&grid[xIndex][yIndex]);
                
     }
     }

    if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
  
    debugLog << "X position: " << xIndex << "Y position: " << yIndex << std::endl;

    if(ValidIndex(xIndex,yIndex)){

    if(grid[xIndex][yIndex].isAlive == true)
        SetCellDead(&grid[xIndex][yIndex]);
    }

    }

    if(IsKeyPressed(KEY_SPACE)){

        // start Automata

        startAutomata = true;

    }

}

void switchCell(){

    debugLog << "Switching Cell" << std::endl;

     for (int i = 0; i < Cols; i++)
        {
            for (int j = 0; j < Rows; j++)
            {
                int neightboursAlive = CountNeighbour(i,j);
               switch (neightboursAlive)
               {
               case 0:
               case 1:
                newGrid[i][j].isAlive = false;
                break;
                case 2:
                newGrid[i][j].isAlive = grid[i][j].isAlive;
                break;
                case 3:
                newGrid[i][j].isAlive = true;
                break;
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                newGrid[i][j].isAlive = false;
                break;

                default: 
                newGrid[i][j].isAlive = grid[i][j].isAlive;
                break;
               }
            }
            
        }

}

void CopyGrid(){

    // Copy newGrid into grid

    debugLog << "Copying new grid into main grid" << std::endl;

    for (int i = 0; i < Cols; i++)
        {
            for (int j = 0; j < Rows; j++)
            {
               grid[i][j] = newGrid[i][j];
            }
            
        }


}

int CountNeighbour(int xPos, int yPos){

    // Count neightbour alive

    int NeighboutAlive=0;
    
    debugLog <<"Current is alive: " << grid[xPos][yPos].isAlive << std::endl;

    if(ValidIndex(xPos-1,yPos) && isAlive(xPos-1,yPos) ) 
        NeighboutAlive++;

    if(ValidIndex(xPos+1,yPos) && isAlive(xPos+1,yPos) ) 
        NeighboutAlive++;

    if(ValidIndex(xPos,yPos+1) && isAlive(xPos,yPos+1) ) 
        NeighboutAlive++;

    if(ValidIndex(xPos,yPos-1) && isAlive(xPos,yPos-1) ) 
        NeighboutAlive++;

    if(ValidIndex(xPos-1,yPos-1) && isAlive(xPos-1,yPos-1) ) 
        NeighboutAlive++;

    if(ValidIndex(xPos-1,yPos+1) && isAlive(xPos-1,yPos+1) ) 
        NeighboutAlive++;

    if(ValidIndex(xPos+1,yPos-1) && isAlive(xPos+1,yPos-1) ) 
        NeighboutAlive++;

    if(ValidIndex(xPos+1,yPos+1) && isAlive(xPos+1,yPos+1) ) 
        NeighboutAlive++;


    debugLog << "Current Cell: " << xPos << "  " << yPos << std::endl << 
                "Number of Neighbour alive: " << NeighboutAlive << std::endl;

    return NeighboutAlive;

    
}

void cellStatus(){

    for (int row = 0; row < Rows; row++)
    {
        
        for (int col = 0; col < Cols; col++)
        {
            debugLog    << "x: "  << grid[row][col].xPos << "y: "  << grid[row][col].yPos 
                        << "is Alive? " << "x: "  << grid[row][col].isAlive << endl;
        }
        
    }
    
}

bool isAlive(int xIndex, int yIndex){

    return grid[xIndex][yIndex].isAlive;

}