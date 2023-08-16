#include <raylib.h>
#include <iostream>

using namespace std;


const int screenWidth = 800;
const int screenHeight = 800;

const int Rows = 20;
const int Cols = 20;

const int cellWidth = screenWidth/Cols;
const int cellHeight = screenHeight/Rows;

const string title = "Mamta Madarchod";

bool start = false;

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
int CountNeighbour(Cell *);
void CopyGrid();


int main()
{

    Intialize();

    while (!WindowShouldClose())
    {

        CheckForAliveCells();


        if(start){
        // Switch  grid status according to the rules;
            switchCell();

        }


        BeginDrawing();
        ClearBackground(RAYWHITE);
      
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
        
    std::cout << "X position: " << xIndex << "Y position: " << yIndex << std::endl;

     if(ValidIndex(xIndex,yIndex)){

        SetCellAlive(&grid[xIndex][yIndex]);
                
     }
     }

    if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
  
    std::cout << "X position: " << xIndex << "Y position: " << yIndex << std::endl;

    if(ValidIndex(xIndex,yIndex)){

    if(grid[xIndex][yIndex].isAlive == true)
        SetCellDead(&grid[xIndex][yIndex]);
    }

    }

    if(IsKeyPressed(KEY_SPACE)){

        // Start Automata

        start = true;

    }

}

void switchCell(){

     for (int i = 0; i < Cols; i++)
        {
            for (int j = 0; j < Rows; j++)
            {
               switch (CountNeighbour(&grid[i][j]))
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
               }
            }
            
        }

    CopyGrid();

}

void CopyGrid(){

    // Copy newGrid into grid

    for (int i = 0; i < Cols; i++)
        {
            for (int j = 0; j < Rows; j++)
            {
               grid[i][j] = newGrid[i][j];
            }
            
        }


}

int CountNeighbour(Cell * cell){

    // Count neightbour alive

}