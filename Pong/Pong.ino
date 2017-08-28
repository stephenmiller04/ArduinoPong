/*
 * Made by: Stephen Miller 
 * If you have any questions, contact me: stephenmiller997@gmail.com
 * www.stephenmiller.hu
 */

#include <TVout.h>
#include <fontALL.h>

#define WHEEL_ONE_PIN 0
#define WHEEL_TWO_PIN 1
#define BUTTON_ONE_PIN 2
#define BUTTON_TWO_PIN 3
 
#define PADDLE_HEIGHT 14
#define PADDLE_WIDTH 1
 
#define RIGHT_PADDLE_X (TV.hres()-4)
#define LEFT_PADDLE_X 2
 
#define IN_GAMEA 0
#define IN_GAMEB 0

#define IN_MENU 1
#define GAME_OVER 2
 
#define LEFT_SCORE_X (TV.hres()/2-15)
#define RIGHT_SCORE_X (TV.hres()/2+10)
#define SCORE_Y 4
 
#define MAX_Y_VELOCITY 600
#define PLAY_TO 9
 
#define LEFT 0
#define RIGHT 1
 
TVout TV;
unsigned char x,y;

boolean button1Status = false;
int wheelOnePosition = 0;
int wheelTwoPosition = 0;
int rightPaddleY = 0;
int leftPaddleY = 0;
unsigned char ballX = 0;
unsigned char ballY = 0;
char ballVolX = 2;
char ballVolY = 2;
int leftPlayerScore = 0;
int rightPlayerScore = 0;
int frame = 0;
int state = IN_MENU;
 
void processInputs()
{
   wheelOnePosition = analogRead(WHEEL_ONE_PIN);
   wheelTwoPosition = analogRead(WHEEL_TWO_PIN);
   button1Status = (digitalRead(BUTTON_ONE_PIN));
  
   delay(60);
}
 
void drawGameScreen()
{
  rightPaddleY = ((wheelOnePosition /8) * (TV.vres()-PADDLE_HEIGHT))/ 128;
  x = RIGHT_PADDLE_X;
  
  for(int i=0; i<PADDLE_WIDTH; i++)
  {
    TV.draw_line(x+i,rightPaddleY,x+i,rightPaddleY+PADDLE_HEIGHT,1);
  }
 
  leftPaddleY = ((wheelTwoPosition /8) * (TV.vres()-PADDLE_HEIGHT))/ 128;
  x = LEFT_PADDLE_X;
  
  for(int i=0; i<PADDLE_WIDTH; i++)
  {
    TV.draw_line(x+i,leftPaddleY,x+i,leftPaddleY+PADDLE_HEIGHT,1);
  }
 
  TV.print_char(LEFT_SCORE_X,SCORE_Y,'0'+leftPlayerScore);
  TV.print_char(RIGHT_SCORE_X,SCORE_Y,'0'+rightPlayerScore);
  TV.set_pixel(ballX, ballY, 2);
}
 
void playerScored(byte player)
{
  if(player == LEFT) leftPlayerScore++;
  if(player == RIGHT) rightPlayerScore++;
 
  if(leftPlayerScore == PLAY_TO || rightPlayerScore == PLAY_TO)
  {
    state = GAME_OVER;
  }
 
  ballVolX = -ballVolX;
}
 
 void drawBox()
 {
  TV.clear_screen();
  //line
  for(int i=1; i<TV.vres() - 4; i+=6)
  {
    TV.draw_line(TV.hres()/2,i,TV.hres()/2,i+3,1);
  }
  //border
  TV.draw_line(0, 0, 0,95,1 );  // left
  TV.draw_line(0, 0, 126,0,1 ); // top
  TV.draw_line(126, 0, 126,95,1 ); // right
  TV.draw_line(0, 95, 126,95,1 ); // bottom

  state = IN_GAMEB;
}
 
void drawMenu()
{
  x = 0;
  y = 0;
  
  char volX = 0;
  char volY = 0;
  
  TV.clear_screen();
  TV.select_font(font8x8);
  TV.print(15, 5, "Arduino Pong");
  TV.select_font(font4x6);
  TV.print(22, 35, "Press Button To Start");
  TV.print(0, 90, "Stephen Miller (c)");
  
  delay(1000);
  
  while(!button1Status)
  {
    processInputs();
  }

  TV.select_font(font4x6);
  state = IN_GAMEA;
}
 
void setup()
{
  x=0;
  y=0;
  TV.begin(_NTSC);
  ballX = TV.hres() / 2;
  ballY = TV.vres() / 2;
}
 
void loop()
{
  processInputs();
 
  if(state == IN_MENU)
  {
    drawMenu();
  }
  
  if(state == IN_GAMEA)
  {
    drawBox();
  }
 
  if(state == IN_GAMEB)
  {
    if(frame % 1 == 0)
    {
      ballX += ballVolX;
      ballY += ballVolY;
 
      if(ballY <= 1 || ballY >= TV.vres()-1)
      {
        ballVolY = -ballVolY;
      }
      
      if(ballVolX < 0 && ballX == LEFT_PADDLE_X+PADDLE_WIDTH-1 && ballY >= leftPaddleY && ballY <= leftPaddleY + PADDLE_HEIGHT)
      {
        ballVolX = -ballVolX;
        ballVolY += 2 * ((ballY - leftPaddleY) - (PADDLE_HEIGHT / 2)) / (PADDLE_HEIGHT / 2);
      }
       
      if(ballVolX > 0 && ballX == RIGHT_PADDLE_X && ballY >= rightPaddleY && ballY <= rightPaddleY + PADDLE_HEIGHT)
      {
        ballVolX = -ballVolX;
        ballVolY += 2 * ((ballY - rightPaddleY) - (PADDLE_HEIGHT / 2)) / (PADDLE_HEIGHT / 2);
      }
 
      if(ballVolY > MAX_Y_VELOCITY)
      {
        ballVolY = MAX_Y_VELOCITY;
      }
      
      if(ballVolY < -MAX_Y_VELOCITY)
      {
        ballVolY = -MAX_Y_VELOCITY;
      }
      
      if(ballX <= 1)
      {
        playerScored(RIGHT); 
      }
      
      if(ballX >= TV.hres() - 1)
      {
        playerScored(LEFT);
      }
    }
 
    drawGameScreen();
  }
  
  if(state == GAME_OVER)
  {
    drawGameScreen();
    TV.select_font(font8x8);
    TV.print(29,25,"GAME");
    TV.print(68,25,"OVER");
    
    while(!button1Status)
    {
      processInputs();
      delay(50);
    }
    
    TV.select_font(font4x6);
    leftPlayerScore = 0;
    rightPlayerScore = 0;
    state = IN_MENU;
  }
 
  TV.delay_frame(1);
  if(++frame == 60) frame = 0;
}
