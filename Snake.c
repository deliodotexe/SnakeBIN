/****************************************************
* @autor Lionardo Wernli
* @file Snake.c
* @title Snake Game
* @note WIP
* @brief Ein Snake Spiel für BIN etc
*****************************************************
* @date 05.04.2019
* @version V0.0
****************************************************/
/*
x/y   (Koordinatenangaben für Display) 
0/320   --------------------------------------- 0/0 \n
*         ¦ Farbe    FELD  ¦   FELD  ¦   FELD   ¦ \n
*         ¦          FELD  ¦   FELD  ¦   FELD   ¦ \n
*         ¦          FELD  ¦   FELD  ¦   FELD   ¦ \n
*         ¦                ¦         ¦          ¦ \n
*         ¦ --->     FELD  ¦   FELD  ¦   FELD   ¦ \n
*         ¦ ZUG      FELD  ¦   FELD  ¦   FELD   ¦ \n
*         ¦ <---     FELD  ¦   FELD  ¦   FELD   ¦ \n
*         ¦                ¦         ¦          ¦ \n
*         ¦          FELD  ¦   FELD  ¦   FELD   ¦ \n
*         ¦          FELD  ¦   FELD  ¦   FELD   ¦ \n
*         ¦ NEU      FELD  ¦   FELD  ¦   FELD   ¦ \n
* 240/320 --------------------------------------- 240/0\n
*/
//---------------------------------------------------
// Libaries
//---------------------------------------------------

//#include <stm32f10x.h>      -Not Used anymore-
 #include "TouchP0P1.h"

//---------------------------------------------------
// Defines
//---------------------------------------------------

 //Controlls
 #define StickLeft     !PD_14
 #define StickUp       !PD_13
 #define StickRight    !PD_12
 #define StickDown     !PD_11
 
 //Start Debug btn_Debug_mode
 #define btn_Debug_mode  PA_0
 
 //Mainmenu
 #define btn_start       !PC_13 

//---------------------------------------------------
// Global Variable
//---------------------------------------------------

//Vereinfachtes Positionssystem
 int pos_X = 15;
 int pos_Y = 13;

 //letzte gewählte richtung
 char direction = 0;

 //ob Gameover
 char game_started = 1;

 int points = 0;

//---------------------------------------------------
// FunctionPrototypes
//---------------------------------------------------

void Spielfeld(void);
void ScoreBoard(char);
void Steuerung(void);
void Position_Head(void);
void delay(int ms);
void gamerule(void);

//---------------------------------------------------
// Main
//---------------------------------------------------

int main(void){
 InitTouchScreen();     //Initialisiere TouchScreen
 setScreenDir(HOR);     //Setze Screen Horizontal
 Spielfeld();			//Spielfeld laden
 while(1)				//Endlos
 {
 	if(game_started == 1) //nicht gameover
 	{
 	 ScoreBoard(points);    
 	 Position_Head();
 	 Steuerung();
 	 gamerule();	
 	}
 	if(btn_start)
 	{
 		pos_X = 15;
 		pos_Y = 13;
 		Spielfeld();
 		game_started = 1;
 		direction = 0;
 		points = 0;
 	} 
 }
}

//---------------------------------------------------
// Spielfeld
//---------------------------------------------------

void Spielfeld(void){
 clearScreen(BLACK);
 //line(x1,y1,x2,y2,thick,color)
 line(0, 0, 319, 0, 1, WHITE); //Horizontal Oben
 line(0, 239, 319, 239, 1, WHITE); //Horizontal Unten
 line(0, 0, 0, 239, 1, WHITE); //Vertikal Links
 line(319, 0, 319, 239, 1, WHITE); //Horizontal Unten
 line(0, 30, 319, 30, 1, WHITE); //Horizontal Mitte
}

void ScoreBoard(char score){
 char ScoreOutput[20];
 sprintf(ScoreOutput, "Punkte: %d", score);
 textxy(ScoreOutput, 3, 20, BRIGHT_YELLOW, BLACK);
}

void Position_Head(void){
 rectan(pos_X*10,pos_Y*10, pos_X*10+10, pos_Y*10+10, 1, WHITE, 1);
 delay(100);
}

void Steuerung(void){
 if(StickLeft && (direction != 2))
 {
 	direction = 1; //left
 }
 if(StickRight && (direction != 1))
 {
 	direction = 2; //right
 }
 if(StickUp && (direction != 4))
 {
 	direction = 3; //up
 }
 if(StickDown && (direction != 3))
 {
 	direction = 4; //down
 }
 delay(100);
 if(direction == 1)
 {
 	pos_X--;
 	points++;
 }
 if(direction == 2)
 {
 	pos_X++;
 	points++;
 }
 if(direction == 3)
 {
 	pos_Y--;
 	points++;
 }
 if(direction == 4)
 {
 	pos_Y++;
 	points++;
 }
}

void delay(int ms){
	long t = 0;
	for(t = ms*12000; t>0; t--);
}

void gamerule(void){
 if((pos_X*10 < 0) || (pos_X*10 > 318))
 {
 	textxy("Game Over", 125, 130, BRIGHT_YELLOW, BLACK);
 	game_started = 0;
 }
 if((pos_Y*10 < 30)|| (pos_Y*10 > 238))
 {
 	textxy("Game Over", 125, 130, BRIGHT_YELLOW, BLACK);
 	game_started = 0;
 }
}
