#include <raylib.h>
#include <iostream>


const int screenWidth = 800;
const int screenHeight = 800;

const int Rows = 20;
const int Cols = 20;

const int cellWidth = screenWidth/Cols;
const int cellHeight = screenHeight/Rows;

typedef struct Cell{

    int xPos;
    int yPos;

    bool isAlive;


} Cell;

Cell grid[Cols][Rows];

void DrawCell(Cell);
bool ValidIndex(int,int);
void SetCellAlive(Cell*);
void SetCellDead(Cell*);

void CheckForAliveCells();


int main()
{

    for (int i = 0; i < Cols; i++)
        {
            for (int j = 0; j < Rows; j++)
            {
                // Draw Rectangles
                grid[i][j] =  Cell{i,j,false};
            }
            
        }
   

    InitWindow(screenWidth, screenHeight, "Drawing a grid!");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        CheckForAliveCells();

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

}