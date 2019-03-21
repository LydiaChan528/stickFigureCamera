#include "glextra.h"
#include "gl.h"
#include "timer.h"
#include "printf.h"
#include "math.h"

struct Circle* head;

#define ROOM_TEMP 22
#define HEAD_RADIUS 5
#define BODY_WIDTH_MARGIN 2
#define BODY_LENGTH_MARGIN 3
#define THERMAL_BACKGROUND_COLOR GL_WHITE
#define abs(x) ((x) > (0) ? (x) : (0))

/*
  Draw circles using the Mid-Point Circle Drawing Algorithm

  @param xCenter  x-coordinate of circle center
  @param yCenter  y-coordinate of circle center
  @param radius   length of radius of circle
  @param color    color to draw circle        
 */
void gl_draw_circle(int xCenter, int yCenter, int radius, color_t color) {
  int x = radius;
  int y = 0;

  //draw 4 outerpoints
  gl_draw_pixel(xCenter+x, yCenter+y, color);
  gl_draw_pixel(xCenter+y, yCenter+x, color);
  gl_draw_pixel(xCenter-x, yCenter-y, color);
  gl_draw_pixel(xCenter-y, yCenter-x, color);
  
  int P = (1-radius);
  while (x > y) {
    y++;

    if (P <= 0) {
      P += (2*y + 1);
    } else {
      x--;
      P += (2*y - 2*x + 1);
    }

    if (x < y) {
      break;
    }

    //draw point in all four quadrants
    gl_draw_pixel(xCenter+x, yCenter+y, color);
    gl_draw_pixel(xCenter-x, yCenter+y, color);
    gl_draw_pixel(xCenter+x, yCenter-y, color);
    gl_draw_pixel(xCenter-x, yCenter-y, color);

    if (x != y) {
      //draw reflected point over y=x in all four quadrants
      gl_draw_pixel(xCenter+y, yCenter+x, color);
      gl_draw_pixel(xCenter-y, yCenter+x, color);
      gl_draw_pixel(xCenter+y, yCenter-x, color);
      gl_draw_pixel(xCenter-y, yCenter-x, color);
    }

  }
}

void drawCircle(struct Circle circle, color_t color) {
  struct Point circleCenter = circle.center;
  int circleRad = circle.radius;
  gl_draw_circle(circleCenter.x, circleCenter.y, circleRad, color);
}

void drawLine(struct Line line, color_t color) {
  struct Point start = line.one;
  struct Point end = line.two;
  gl_draw_line(start.x, start.y, end.x, end.y, color);
}

/*
  Calculate the center of the head from thermal camera data

  @param data     thermal data as a pointer to short
  @param rowSize  size of rows and columns
  @return         reference to circle representing the head    
 */
struct Circle* calculateHead(const short* data, int rowSize){
  // /*to test*/printf("start head\n");
  head->radius = HEAD_RADIUS;

  int row;

  for (row = 0; row < rowSize; row++) {
    // /*to test*/printf("\nR%d:", row);

    int start = -1;
    int end = -1;

    for (int col = 0; col < rowSize; col++) {
      if(*data/4 > ROOM_TEMP){ //warm pixel
        end = col;
        // /*to test*/printf("e%d", col);
        if (start < 0) {
          start = col;
          // /*to test*/printf("start%d", start);
        }
      } else {

        if ((start > 0) && (end > 0)) { //red then blue
          // /*to test*/printf("block. ");

          if ((end - start) >= BODY_WIDTH_MARGIN) {
            // /*to test*/printf("long. ");

            //CHECK THE OTHER ROW FOR WARM BLOCK
            int checkRow = (row + BODY_LENGTH_MARGIN);
            int checkStart = -1;
            int checkEnd = -1;

            for (int checkCol = 0; checkCol < rowSize; checkCol++) {
              if (data[(checkRow*rowSize )+ checkCol]/4 > ROOM_TEMP) {
                // /*to test*/printf("c%d, ", checkRow*rowSize + checkCol);
                checkEnd = checkCol;
                if (checkStart < 0) {
                  checkStart = checkCol;
                }
              } 
            }

            if ((checkEnd - checkStart) >= BODY_WIDTH_MARGIN) {
              int headX = (rowSize - (start+end)/2);
              int headY = (row + HEAD_RADIUS);
              struct Point headCenter = { headX, headY};
              // /*to test*/printf("HEAD at (%d,%d)\n", headX, headY);
              head->center = headCenter;
              return head;
            }
          }
        }

      }
      data++;
    }
  }

  return head;
}

void projectInfraredDataToMonitor(short* infraredData, int rowSize){
  gl_clear(THERMAL_BACKGROUND_COLOR);
  int row = 0;
  //TO:DO GET MATH LIB TO WORK SO THIS BECOMES MORE DYNAMIC, not(col % constant)
  for(int col = 0; col < rowSize*rowSize; col++){
    if(col % rowSize == 0 && col > 0){
      row++;
    }
    //Quik maths
    unsigned char red = 0;
    unsigned char blue = 0;
    if(*infraredData/4 > ROOM_TEMP){
      red = *infraredData;
    }
    else{
      blue = *infraredData;
    }
    gl_draw_pixel(col%rowSize,row,gl_color(red,0,blue));
    infraredData++; 
  }
  gl_swap_buffer();
}



// /* Helper function to drawCircle(). This function draws in all 8 octaves of a 
// circle derived from Bresenham's Circle Algorithm.
//  */
// static void drawOuterPoints(int xc, int yc, int x, int y, color_t color) {
//   gl_draw_pixel(xc+x, yc+y, color);
//   gl_draw_pixel(xc-x, yc+y, color);
//   gl_draw_pixel(xc+x, yc-y, color);
//   gl_draw_pixel(xc-x, yc-y, color);
//   gl_draw_pixel(xc+y, yc+x, color);
//   gl_draw_pixel(xc-y, yc+x, color);
//   gl_draw_pixel(xc+y, yc-x, color);
//   gl_draw_pixel(xc-y, yc-x, color);
// }

// /*Draw circles using Bresenham's algorithm*/
// void drawCircle(int xCenter, int yCenter, int radius, color_t c) {
//   int x = 0;
//   int y = radius;
//   int decision = 3 - (2*radius);
//   drawOuterPoints(xCenter, yCenter, x, y, c);

//   while (y > x) {
//     x++;
//     if (decision > 0) {
//       y--;
//       decision += (4*(x-y) + 10);
//     } else {
//       decision += ((4*x) + 6);
//     }
//     drawOuterPoints(xCenter, yCenter, x, y, c);
//   } 
// }

// struct Circle* calculateHead(const short* data, int rowSize){
//   const short* dataPtr = data;

//   head->radius = HEAD_RADIUS;
//   int headTop = -1;
//   int bodyStart = -1;
//   int bodyEnd = -1;

//   for (int row = 0; row < rowSize; row++) {
//     int start = -1;
//     int end = -1;
//     int col = 0;

//     /*to test*/printf("\nrow %d:", row);

//     //find the warm block (body start and end)
//     while ((col < rowSize)) {
//       // int data[row][col] = currTemp;

//       if (*dataPtr/4 > 22) { //"red"
//         if (start < 0) {
//           start = col;
//           /*to test*/printf("start %d;", start);
//         }
//         end = col;
//         /*to test*/printf("E%d, ", end);
//       }  
//       ///blue or black if <= 22
//       else if ((start > 0) && (end > 0)) {
//         /*to test*/printf("MAYBE FOUND WARM BLOCK! diff = %d\n", (end-start));

//         if ((end-start) >= BODY_ERROR) {

//           //found warm block
//           if (headTop < 0) {
//             /*to test*/printf("STARTING SOMETHING\n");
//             bodyStart = start;
//             bodyEnd = end;
//             headTop = row;
//           } else if ( (abs(bodyStart - start) < BODY_ERROR) && (abs(bodyEnd - end) < BODY_ERROR) ) {
//             // headTop = row-1;
//             /*to test*/printf("ENDING SOMETHING\n");
//             break;
//           } 

//         } else {
//           //reset warm block
//           start = -1;
//           end = -1;
//         }
//       }

//       col++;
//       dataPtr++;
//     }

//   }


//   struct Point headCenter = { (bodyEnd + bodyStart)/2, (headTop+HEAD_RADIUS) };
//   head->center = headCenter;
//   printf("HEAD: (%d,%d)\n", headCenter.x, headCenter.y);
//   return head;
//   /* To be implemented in glextra.c */
// }