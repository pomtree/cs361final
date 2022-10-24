#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"
#include <random>

emp::web::Document doc{"target"};

class CAAnimator : public emp::web::Animate {

// grid width and height
const int num_h_boxes = 30;
const int num_w_boxes = 30;
const double RECT_SIDE = 25;
const double width{num_w_boxes * RECT_SIDE};
const double height{num_h_boxes * RECT_SIDE};

std::vector<std::vector<double> > table1;

//some vectors to hold information about the CA
std::vector<std::vector<int> > cells;
std::vector<std::vector<int> > old_cells;
        

// where we'll draw
emp::web::Canvas canvas{width, height, "canvas"};

public:
    CAAnimator() {
       //////doc << "caa start";
        // shove canvas into the div
        // along with some control buttons
        doc << canvas;
         doc << GetToggleButton("Toggle");
         doc << GetStepButton("Step");
        //fill the vectors with 0 to start
        cells.resize(num_w_boxes, std::vector<int>(num_h_boxes, 0));
        old_cells.resize(num_w_boxes, std::vector<int>(num_h_boxes, 0));

        table1.resize(2,std::vector<double>(5, 0));
        
        table1[0][0] = 1.000;
        table1[0][1] = 0.987;
        table1[0][2] = 0.976;
        table1[0][3] = 0.954;
        table1[0][4] = 0.979;

        table1[1][0] = 0.124;
        table1[1][1] = 0.041;
        table1[1][2] = 0.016;
        table1[1][3] = 0.008;
        table1[1][4] = 0.002;

        //showing how to set a cell to 'alive'
        // cells[0][0] = 1;
        // cells[10][10] = 1;
        // cells[10][11] = 1;
        // cells[10][12] = 1;
        // cells[11][10] = 1;
        // cells[11][10] = 1;
        // cells[12][10] = 1;
        //"begin doframe";
        createStartingCells();
    }
    void createStartingCells() {
        //ensure size here matches num_h_cells (must be hard-coded in both locations)
        std::string basic_gliders[30] = {
            "..............................",
            "..............................",
            "..............................",
            "..............................",
            "......X.......................",
            ".......X......................",
            ".....XXX......................",
            "..............................",
            ".....................X........",
            "......................X.......",
            "....................XXX.......",
            "..............................",
            "........X.....................",
            ".........X....................",
            ".......XXX....................",
            "..............................",
            "..............................",
            "..............................",
            ".....................X........",
            "......................X.......",
            "....................XXX.......",
            ".........X....................",
            "..........X...................",
            "........XXX...................",
            "..............................",
            "..............................",
            "..............................",
            "..............X...............",
            "...............X..............",
            ".............XXX.............."
            };
        //source: https://conwaylife.com/w/images/2/22/Hwss.png
        std::string spaceship[30] = {
            "..............................",
            "....XX........................",
            "..X....X......................",
            ".X............................",
            ".X.....X......................",
            ".XXXXXX.......................",
            "..............XX..............",
            "............X....X............",
            "...........X..................",
            "...........X.....X............",
            "...........XXXXXX.............",
            "..............................",
            "..............................",
            "..............................",
            ".......................XX.....",
            ".....................X....X...",
            "....................X.........",
            "....................X.....X...",
            "....................XXXXXX....",
            "........XX....................",
            "......X....X..................",
            ".....X........................",
            ".....X.....X.......XX.........",
            ".....XXXXXX......X....X.......",
            "................X.............",
            "................X.....X.......",
            "................XXXXXX........",
            "..............................",
            "..............................",
            ".............................."
            };
        std::string osc[30] = {
            ".................XX...........",
            ".....XX.........X..X.......X..",
            "....X.X........X....X......X..",
            "..............X......X.....X..",
            "..X.X.........X......X........",
            "..XX...........X....X.........",
            "................X..X..........",
            ".................XX...........",
            "........XX....................",
            "........XX....................",
            "..............................",
            "......XXXX....................",
            "..XX.X....X...................",
            "..XX.X..X.X...................",
            ".....X...XX.XX................",
            ".....X.X..X.XX................",
            "......XXXX....................",
            "..............................",
            "......XX....XX............XX..",
            "......XX.....X............X...",
            ".............X.X........X.X...",
            "..............XX........XX....",
            "..............................",
            "...XXX...........XXXXXX.......",
            "..............................",
            "..............XX........XX....",
            "....X........X.X........X.X...",
            "....X........X............X...",
            "....X.......XX............XX..",
            ".............................."
            };
       
        for(int i = 0; i < num_h_boxes; i++) {
            for(int j = 0; j < num_w_boxes; j++) {
                //pick your starting layout here:
                cells[j][i] = osc[i].at(j) == 'X';
            }
        }
   
    }
    void DoFrame() override {
        //"begin doframe";
        canvas.Clear();
        for (int x = 0; x < num_w_boxes; x++){
             for (int y = 0; y < num_h_boxes; y++) {
                if (cells[x][y] == 0) {
                    //Draw a rectangle on the canvas filled with white and outlined in black
                    canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "white", "black");
                } else {
                    //Draw a rectangle filled with black
                    canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "black", "black");
                }
            }
        }
       //////doc << "Calling updating cells...";
        //Place to update the values of all the cells based on CA rules
        updateCells();
    }
    void updateCells() {
       //////doc << "Updating cells...";
        //std::vector<std::vector<int> > old_cells;
       old_cells = cells;
        for(int i = 0; i < num_w_boxes; i++) {
            for(int j = 0; j < num_h_boxes; j++) {
                //doc << "update calling...";
                cells[i][j] = updateCell(i,j);
                //condition for life:
                //OLD Conway Rules
                /*if(sum(i,j) == 3 || (sum(i,j) ==2 && cells[i][j] == 1)) {
                    cells[i][j] = 1;
                }
                else {
                    cells[i][j] = 0;
                }
                */
               //NEW Rules function:

            }
        }
       //////doc << "update complete";
    }
    //NEW Update Cell Rules/probabilities
    int updateCell(int i, int j) {
        //doc << doubleRand();
        if(table1[cells[i][j]][fourNeighbors(i,j)] < doubleRand()) {
            //doc << "update cell to 1";
            return 1;
        }
        else {
            //doc << "update cell to 0";
            return 0;
        }


        
    }
    //NEW count neigbors:
    int fourNeighbors(int i, int j) {
        int c = 0;
        //center left:
        c += old_cells[minus(i,num_w_boxes)][j];        
        //center right:
        c += old_cells[plus(i,num_w_boxes)][j];
        //lower center:
        c += old_cells[i][plus(j,num_h_boxes)];        
        //upper center:
        c += old_cells[i][minus(j,num_h_boxes)];
        return c;
    }
    double doubleRand() {
    return double(rand()) / (double(RAND_MAX) + 1.0);
    }
    //OLD counts living neighbors:
    int sum(int i, int j) {
       ////////doc << "sum running\n";
        int c = 0;
     
     
     
        // MIN MAX, NEGATIVES
     
     
        //upper left:
        c += old_cells[minus(i,num_w_boxes)][minus(j,num_h_boxes)];
        //center left:
        c += old_cells[minus(i,num_w_boxes)][j];
        //lower left:
        c += old_cells[minus(i,num_w_boxes)][plus(j,num_h_boxes)];
        //upper center:
        c += old_cells[i][minus(j,num_h_boxes)];
        //lower center:
        c += old_cells[i][plus(j,num_h_boxes)];
        //upper right:
        c += old_cells[plus(i,num_w_boxes)][minus(j,num_h_boxes)];
        //center right:
        c += old_cells[plus(i,num_w_boxes)][j];
        //lower right:
        c += old_cells[plus(i,num_w_boxes)][plus(j,num_h_boxes)];
        //doc << i << ", " << j << " count = " << c;
        return c;
    }
    int minus(int i, int max) {
        if(i - 1 >= 0)
            return i - 1;
        return max - 1;
    }
    int plus(int i, int max) {
        if(i + 1 < max)
            return i + 1;
        return 0;
    }
};

CAAnimator animator;
int main() {
    //Have animator call DoFrame once to start
    animator.Step();
}