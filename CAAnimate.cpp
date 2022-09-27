#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"

emp::web::Document doc{"target"};

class CAAnimator : public emp::web::Animate {

// grid width and height
const int num_h_boxes = 30;
const int num_w_boxes = 30;
const double RECT_SIDE = 25;
const double width{num_w_boxes * RECT_SIDE};
const double height{num_h_boxes * RECT_SIDE};


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
            ".....XX.........X..X..........",
            "....X.X........X....X.........",
            "..............X......X........",
            "..X.X.........X......X........",
            "..XX...........X....X.........",
            "................X..X..........",
            ".................XX...........",
            "........XX....................",
            "........XX.......XXX..........",
            ".................XXX..........",
            "......XXXX.......XXX..........",
            "..XX.X....X.........XXX.......",
            "..XX.X..X.X.........XXX.......",
            ".....X...XX.XX......XXX.......",
            ".....X.X..X.XX................",
            "......XXXX...................",
            ".............................",
            "......XX..................XX.............",
            "......XX..................X............",
            "...............X........X.X............",
            "..............XX........XX...............",
            ".........................................",
            ".................XXXXXX.......................",
            ".........................................",
            "..............XX........XX................",
            ".............X.X........X.X..............",
            ".............X............X..............",
            "............XX............XX...............",
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
                //condition for life:
                if(sum(i,j) == 3 || (sum(i,j) ==2 && cells[i][j] == 1)) {
                    cells[i][j] = 1;
                }
                else {
                    cells[i][j] = 0;
                }
            }
        }
       //////doc << "update complete";
    }
    //counts living neighbors:
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