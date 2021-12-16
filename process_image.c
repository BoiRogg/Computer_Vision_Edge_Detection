#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <X11/Xlib.h>

#define DIM 512

/******************************************************************/
/* This structure contains the coordinates of a box drawn with    */
/* the left mouse button on the image window.                     */
/* roi.x , roi.y  - left upper corner's coordinates               */
/* roi.width , roi.height - width and height of the box           */
/******************************************************************/
extern XRectangle roi;

int computeConvolution(unsigned char image[DIM][DIM], int i, int j){
    int sum = 0;

    //zero is false
    int isVertical = 1;

    int horizontal [3][3] ={  {-1, 0, 1},
                            {-2, 0, 2},
                            {-1, 0, 1} };
    int vertical [3][3] = {{-1, -2, -1},
                            {0, 0, 0},
                            {1, 2, 1} };
    
    for(int a = 0; a < 3; a++){
        for(int b = 0; b < 3; b++){
            if(isVertical)
                sum += image[i + 1 - a][j + 1 - b] * vertical[a][b];
            else
                sum += image[i + 1 - a][j + 1 - b] * horizontal[a][b];
        }
    }
    return sum;
}

void normalize(proc_img, edge_img, row, column)
unsigned char proc_img[DIM][DIM];
int edge_img[DIM][DIM];
int row;
int column;
{
    int min = INT_MAX;
    int max = INT_MIN;

    for (int i = 0; i < row; i++){
        for (int j = 0; j < column; j++){
            if(edge_img[i][j] < min){
                min = edge_img[i][j];
            }
            if(edge_img[i][j] > max){
                max = edge_img[i][j];
            }
        }
    }

    for (int i = 0; i < row; i++){
        for (int j = 0; j < column; j++){
            proc_img[i][j] = (unsigned char)((edge_img[i][j] - min) * 255 / (max - min));
        }
    }
}


/******************************************************************/
/* Main processing routine. This is called upon pressing the      */
/* Process button of the interface.                               */
/* image  - the original greyscale image                          */
/* size   - the actual size of the image                          */
/* proc_image - the image representation resulting from the       */
/*              processing. This will be displayed upon return    */
/*              from this function.                               */
/******************************************************************/
void process_image(image, size, proc_img)
unsigned char image[DIM][DIM];
int size[2];
unsigned char proc_img[DIM][DIM];
{
    int edge_img[DIM][DIM];

    for(int i = 0; i < DIM; i++){
        for(int j = 0; j < DIM; j++){
            edge_img[i][j] = computeConvolution(image, i, j);
        }
    }

    normalize(proc_img, edge_img, DIM, DIM);
}


