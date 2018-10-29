
#define F_CPU 1000000
#include <inttypes.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "ks0108.c"
#include "arial_bold_14.h"

#include "Bitmap.c"
#include "Bitmap1.c"
#include "Bitmap2.c"

#include <stdlib.h>
#include <math.h>
#define ADC_VREF_TYPE 0x40


char buf[5],a[10],b[10],c[10];
int x,y,z,count=0;
uint8_t xpos,ypos;
int prev_level;
int food;
int high_score1=0,high_score2=0,score1=0,score2=0,score3=0,high_score3=0;
int i,check,Fscore=0,Fscore2,score=0,time1=0,time2=0,time3=0,k;

void initADC()
{
		ADMUX=(1<<REFS0);  // For Aref=AVcc;
		ADCSRA=(1<<ADEN)|(1<<ADIE)|(1<<ADPS2); //Prescalar div factor =16
}

unsigned int read_adc(unsigned char adc_input)		
{
		ADMUX=adc_input | (ADC_VREF_TYPE & 0xff);
		// Delay needed for the stabilization of the ADC input voltage
		_delay_us(10);
		// Start the AD conversion
		ADCSRA|=0x40;			
		// Wait for the AD conversion to complete
		while ((ADCSRA & 0x10)==0);
		ADCSRA|=0x10;
		return ADCW;
}

int k1,k2;
int level=0;		// to denote the level
int v_l,v_r,v_u,v_d;
int time,test_time;	// variable that will give time
int d1,d2,d3;
int sw=0;
int j,event;
int xfood,yfood;  // variables for food 
int xfood2 , yfood2;
int food2;

int main(void) {
	initADC();
	// Wait a little while the display starts up
	
	// Initialize the LCD
		ks0108Init(0);
	
	// Select a font
		ks0108SelectFont(Arial_Bold_14, ks0108ReadFontData, BLACK);
level=0;
DDRB=0B00000011;
PORTB=0B11111100;
prev_level=0;

while(1)
{
if(level==-1)
{
	level=prev_level;	
}
	if(level==0)
	{		
		check_switch();
		Fscore=0;
		score1=0;
		score2=0;
		score3=0;
		score=0;
		ks0108FillRect(0, 0, 128, 64, BLACK);
		OpeningCur('W');
	
		ks0108GotoXY(30,20);
		ks0108Puts_P(PSTR("WELCOME"));

		_delay_ms(500);

		OpeningCur('W');
		level=1;

	}
	if(level== 1)
	{	
		check_switch();
		// printing the screen 
		ks0108ClearScreen();
		ks0108DrawRect(30,15,61,20,BLACK);
		ks0108DrawRect(31,16,59,18,BLACK);
		ks0108GotoXY(35,20);
		ks0108Puts_P(PSTR("LEVEL 1"));
		_delay_ms(200);
		ks0108ClearScreen();

		ks0108GotoXY(60,20);
		ks0108Puts_P(PSTR("3"));
		_delay_ms(200);
		ks0108ClearScreen();
		ks0108GotoXY(60,20);
		ks0108Puts_P(PSTR("2"));
		_delay_ms(200);
		ks0108ClearScreen();
		ks0108GotoXY(60,20);
		ks0108Puts_P(PSTR("1"));
		_delay_ms(200);
		ks0108ClearScreen();

		// displaying the arena OF lEVEL-1
		LoadBitmap(IMAGE);
		// printing L:1
	    CrHBlock(2,60,5);
		CrVBlock(6,58,3);
		CrVBlock(2,56,1);
		CrVBlock(4,56,1);
	    print_num(2,53,1);
		// displaying the ball 
		create_ball_initially(125,3);
		_delay_ms(100);
		clear_ball();
		create_ball_initially(125,3);

		time=100;
		score=0;
		test_time=0;
		d1=0;
		d2=0;
		d3=0;
	
	while(level==1)
	{
	
		    check_switch();
		  	check=surroundings();
		    accelerate();

			// moving the ball right with no rebounding conditions
			 if(y>358 && check%1000>=100 && xpos<=124)
			  {
			  move_ball('r');
			  v_r++;
			  v_u=0;
			  v_d=0;
			  v_l=0;
			  }
  
			  // moving the ball left with no rebounding conditions
			  else if(y<346 && check %10000>=1000 && xpos>=0)
			  {
			  move_ball('l');
			  v_l++;
			  v_d=0;
			  v_r=0;
			  v_u=0;
			  }
 
			  // moving the ball upwards with no rebounding conditions
			  if(x>311 && check%10>=1)
			  {
			  move_ball('u');
			  v_u++;
			  v_d=0;
			  v_l=0;
			  v_r=0;
			  }
 
			  // moving ball down wards
			  else if(x<300 && check %100 >=10 && ypos<=62)
			  {
			  move_ball('d');
			  v_d++;
			  v_u=0;
			  v_l=0;
			  v_r=0;
			  }
			  // rebounding condition 
			  // upwards
			  if(check%10<1 && v_u>10)
			  { 
			  move_ball('b');
			  _delay_ms(50);
			  move_ball('b');
			  _delay_ms(50);
			  move_ball('b');
			   _delay_ms(50);
			  move_ball('b');
			  _delay_ms(50);
			   }
			   // downwards
			   if(check %100<10 && v_d>10)
			   {move_ball('u');
			   _delay_ms(70);
			   move_ball('u');
			   _delay_ms(70);
			   move_ball('u');
			   _delay_ms(70);
			   move_ball('u');
			   _delay_ms(70);
			   }
			   // left 
			   if(check %10000 <1000 && v_l>10)
			   {move_ball('r');
			   _delay_ms(70);
			   move_ball('r');
			   _delay_ms(70);
			   move_ball('r');
			   _delay_ms(70);
			   move_ball('r');
			   _delay_ms(70);  
			   }
			   // right
			   if(check %1000 <100 && v_r>10)
			   {
			   move_ball('l');
			   _delay_ms(70);
			   move_ball('l');
			   _delay_ms(70);
			   move_ball('l');
			   _delay_ms(70);
			   move_ball('l');
			   _delay_ms(70);
			   }
   if(x>330|| y >370 || x<285 || y<330 )
    {
   		_delay_ms(25);
	}
	else 
	{
		_delay_ms(25);
	}


  	// conditin for the level to end 
	if(xpos==10||xpos==9||xpos==8)
	{
		time1=time;
		Fscore=Fscore+71*time;
		ks0108ClearScreen();// clear the screen
		//print the message
		ks0108GotoXY(10,10);
		ks0108Puts_P(PSTR("Level Completed"));
		// print the score
	/*	ks0108GotoXY(15,30);
		ks0108Puts_P(PSTR("Score"));
		ks0108GotoXY(70,30);
		itoa(score1,a,8);
		ks0108Puts(a);
		_delay_ms(500);
	*/	 
		level=2;
	}// end of if

	if(test_time==15)
	{
		time--;
		test_time=0;

		d3=time%10;
		d2=(time/10)%10;
		d1=(time/100);

		if(time%100==99)
		{
			BlockClear(2,21);
			BlockClear(2,16);
			BlockClear(2,11);
			print_num(2,11,d3);
			print_num(2,16,d2);
			print_num(2,21,d1);
		}

		if(time%10==9)
		{
			BlockClear(2,11);
			BlockClear(2,16);
			print_num(2,11,d3);
			print_num(2,16,d2);
			print_num(2,21,d1);
		}
	
		if(d3>=0)
		{
			BlockClear(2,11);
			print_num(2,11,d3);
			print_num(2,16,d2);
			print_num(2,21,d1);
		}
	}
		
	if(time<10)
	{
	PORTB=0B11111101;
	}
	
	if(time<=0)
	{
	PORTB=0B11111100;
	ks0108ClearScreen();
	ks0108GotoXY(10,30);
	ks0108Puts_P(PSTR("!!!..Game Over..!!!"));
	_delay_ms(100);
	ks0108ClearScreen();
	//PRINT SCORE
		ks0108GotoXY(15,20);
		ks0108Puts_P(PSTR("Score -"));
		ks0108GotoXY(70,20);
		itoa(Fscore,a,10);
		ks0108Puts(a);
		_delay_ms(800);
		ks0108ClearScreen();
		menu();

		level=0;
		}
	  test_time++;
	} // END OF while loop for Level-1
	}	// end of if loop having condition level-1
	 
// the 2nd level
		if(level==2)
		{
		check_switch();
		// displaying the messages
		ks0108ClearScreen();
		ks0108DrawRect(30,15,61,20,BLACK);
		ks0108DrawRect(31,16,59,18,BLACK);
		ks0108GotoXY(35,20);
		ks0108Puts_P(PSTR("LEVEL 2"));
		_delay_ms(200);
		ks0108ClearScreen();
		ks0108GotoXY(60,20);
		ks0108Puts_P(PSTR("3"));
		_delay_ms(200);
		ks0108ClearScreen();
		ks0108GotoXY(60,20);
		ks0108Puts_P(PSTR("2"));
		_delay_ms(200);
		ks0108ClearScreen();
		ks0108GotoXY(60,20);
		ks0108Puts_P(PSTR("1"));
		_delay_ms(200);
		ks0108ClearScreen();
		// printing the image
		LoadBitmap1(IMAGE2);
		// printing L:2
		    CrHBlock(120,19,5);
			CrVBlock(124,17,3);
			CrVBlock(121,15,1);
			CrVBlock(123,15,1);
		    print_num(120,10,2);

		ks0108FillRect(70,12,2,40,BLACK);	
		//print key of gate
		create_ball_initially(38,36);
		xfood=xpos;
		yfood=ypos;

		// create ball initially
		// displaying the ball 
			create_ball_initially(3,5);
			_delay_ms(100);
			clear_ball();
			_delay_ms(100);
			create_ball_initially(3,5);

		    event=0;
			time=100;
			test_time=0;
			d1=0;
			d2=0;
			d3=0;

		while(level==2)
		{	
			check_switch();
		  	check=surroundings_level2();
		  	accelerate();
		    if(x>330|| y >370 || x<285 || y<330 )
		   {
		 	 _delay_ms(15);
		   }
		   else
		   {
			   _delay_ms(15);
		   }
		// moving the ball
		// moving the ball right with no rebounding conditions
		  if(y>358 && check%1000>=100 )
		  {
			  if(event<2 &&xpos>=67)
			  {
			  move_ball('s');
			  }
			  else if(event>=1 && (xpos+3==27 && (ypos>=1 && ypos<=10)))
			  {
			  move_ball('s');
			  }
			  else if(event>=1 && (xpos+3==32 && (ypos>=16 && ypos<=12)))
			  {
			  move_ball('s');
			  }
			  else if(xpos+3==43 &&ypos<=k && ypos>=k-7)
			  {
			  move_ball('r');
			  }
			  else
			  {
			  move_ball('r');
			  }
		  } 
		  // moving the ball left with no rebounding conditions
		  else if(y<346 && check %10000>=1000 && xpos>=0)
		  {
			  if(event>=1 && (xpos-1==31 &&(ypos<=3 && ypos>=1)))
			  {
			  move_ball('s');
			  }
			  else if(event>=1 && (xpos-1==27 &&(ypos<=9 && ypos>=4)))
			  {
			  move_ball('s');
			  }
			  else if(event>=1 && (xpos-1==31 &&(ypos<=12 && ypos>=10)))
			  {
			  move_ball('s');
			  }
			  else if(event>=1 && (xpos-1==32 &&(ypos<=16 && ypos>=12)))
			  {
			  move_ball('s');
			  }
			  else if(xpos-1==43 && ypos<=k && ypos>=k-7)
			  {
			  move_ball('s');
			  }
			  else
			  {
			  move_ball('l');
			  }
		  }
		  // moving the ball upwards with no rebounding conditions
		  if(x>311 && check%10>=1)
		  {
			  if(event>=1 && ((ypos-1==3||ypos-1==3)&&(xpos<=32 &&xpos>=27)))
			  {
			  move_ball('s');
			  }
 
			  else
			  {
			  move_ball('u');
			  }
		  }
		  // moving ball down wards
		  else if(x<300 && check %100 >=10 && ypos<=62)
		  {
			  if(event>=1&& ((ypos+3==3||ypos+3==12)&&(xpos<=32&&xpos>=26)))
			  {
			  move_ball('s');
			  }
			  else
			  {move_ball('d');
			  }
		  }

		// else if event=1
		// event-1
		  if(xpos-1>=25 && xpos -1<=35 && ypos+3>60)
		{
			for(i=20;i<=54;i++)
			{
				CrHBlock(25,i,10);
				ErHBlock(25,i-1,10);
			}
			clear_ball();
	
			for(i=25,j=61;j>=10;j--)
			{
				ErHBlock(i,j-5,10);
				CrHBlock(i,j-6,10);
				ErVBlock(i,j-5,5);
				CrVBlock(i,j-6,5);
				ErVBlock(i+9,j-5,5);
				CrVBlock(i+9,j-6,5);
				ErHBlock(i,j,10);
				CrHBlock(i,j-1,10);
				ks0108DrawCircle(i+4, j-3, 1, WHITE);
				ks0108DrawCircle(i+4, j-4, 1, BLACK);
			}
			_delay_ms(150);
	
			for(j=10;j>3;j--)
			{
		    	ErHBlock(25,j,10);			
			}
				CrVBlock(27,3,10);
				CrHBlock(27,3,5);
				CrHBlock(27,12,5);
				CrVBlock(32,3,10);
				create_ball_initially(29,6);
				_delay_ms(200);
	
			for(j=3;j<13;j++)
			{
				CrVBlock(32,j,10);
				ErVBlock(32,j-1,1);
				}
				event=1;
				k=32;
				move_ball('r');
				move_ball('r');

				move_ball('r');
				move_ball('r');
				move_ball('r');
				move_ball('r');
			}
// xpos>32 then the bar present at x=38 securing the key of gate is start moving.	
			if(event>=1) //then the bar start moving
			{
				CrVBlock(43,k,5);
				ErVBlock(43,k,2);
				if(k<61)
				 k++;
				 else
				 k=32;
		     }
		// clear the ball 
		if((xpos==43||xpos==42||xpos==41)&&ypos-1<=k&& ypos-1>=k-3)
		{
			clear_ball();
			create_ball_initially(29,6);
		}

		// DOT to OPEN the GATE are at x=38  y=35 
		//or they are in surroundings condition is also included
		if((xpos==xfood||xpos+1==xfood||xpos+2==xfood)&& (ypos==yfood||ypos+1==yfood||ypos+2==yfood) )
		{
			clear_ball();
			create_ball_initially(38,36);
			event=2;
			for(i=32,j=33;i>12,j<53;i--,j++)
			 {
				 ks0108SetDot(71,i,WHITE);
				 ks0108SetDot(71,j,WHITE);
				 _delay_ms(20);
			 if(j==52)
			{
				_delay_ms(50);
				for(i=32,j=33;i>24,j<41;i--,j++)
				{
					ks0108SetDot(70,i,WHITE);
					ks0108SetDot(72,i,WHITE);
					ks0108SetDot(70,j,WHITE);
					ks0108SetDot(72,j,WHITE);
					_delay_ms(150);
					check_switch();
				}
				break;
				}
			 }
		}

		// conditin for the level to end 
			if(xpos>=114)
			{
				time2=time;
				Fscore=Fscore+71*time;
				ks0108ClearScreen();// clear the screen
				//print the message
					ks0108GotoXY(10,10);
					ks0108Puts_P(PSTR("Level Completed"));
				// print the score
				ks0108GotoXY(15,30);	
				level=3;
			}

		if(test_time==20)
			{
				time--;
				test_time=0;

				d3=time%10;
				d2=(time/10)%10;
				d1=(time/100);

			if(time%100==99)
			{
				BlockClear(120,50);
				BlockClear(120,45);
				BlockClear(120,40);
				print_num(120,40,d3);
				print_num(120,45,d2);
				print_num(120,50,d1);
			}
			if(time%10==9)
			{
				BlockClear(120,40);
				BlockClear(120,45);
				print_num(120,40,d3);
				print_num(120,45,d2);
				print_num(120,50,d1);
			}
			if(d3>=0)
			{
				BlockClear(120,40);
				print_num(120,40,d3);
				print_num(120,45,d2);
				print_num(120,50,d1);
			}
			} // end of if having test_time condition

			if(time<=0)
			{
				ks0108ClearScreen();
				ks0108GotoXY(10,30);
				ks0108Puts_P(PSTR("!!!..Game Over..!!!"));
				_delay_ms(100);
				ks0108ClearScreen();
		//PRINT SCORE
				ks0108GotoXY(15,20);
				ks0108Puts_P(PSTR("Score -"));
				ks0108GotoXY(70,20);
				itoa(Fscore,a,10);
				ks0108Puts(a);
				_delay_ms(800);
				ks0108ClearScreen();
	
			if(Fscore>=high_score1)
			{
				high_score3=high_score2;
				high_score2=high_score1;
				high_score1=Fscore;
				ks0108ClearScreen();
				ks0108GotoXY(15,25);
				ks0108Puts_P(PSTR("!!!!HIGH SCORE!!!!"));
				_delay_ms(500);
				ks0108ClearScreen();
			}
			 if(Fscore>=high_score2 && Fscore< high_score1)
			{
				high_score3=high_score2;
				high_score2=Fscore;
				ks0108ClearScreen();
				ks0108GotoXY(15,25);
				ks0108Puts_P(PSTR("!!!!HIGH SCORE!!!!"));
				_delay_ms(500);
				ks0108ClearScreen();
			}
			if(Fscore>=high_score3 && Fscore<high_score2 && Fscore<high_score1)
			{
				high_score3=Fscore;
				ks0108ClearScreen();
				ks0108GotoXY(15,25);
				ks0108Puts_P(PSTR("!!!!HIGH SCORE!!!!"));
				_delay_ms(500);
				ks0108ClearScreen();
			}	
			    menu();
				level=0;
			}  // end of if having condition time<=0

		test_time++;

		}	// end of while loop of level-2
		}	// end of if condition of level-2

//Level-3 Starts here
		if(level==3)
		{	check_switch();
			// displaying the messages
			ks0108ClearScreen();
			ks0108DrawRect(30,15,61,20,BLACK);
			ks0108DrawRect(31,16,59,18,BLACK);
			ks0108GotoXY(35,20);
			ks0108Puts_P(PSTR("LEVEL 3"));
			_delay_ms(200);
			ks0108ClearScreen();
			ks0108GotoXY(60,20);
			ks0108Puts_P(PSTR("3"));
			_delay_ms(200);
			ks0108ClearScreen();
			ks0108GotoXY(60,20);
			ks0108Puts_P(PSTR("2"));
			_delay_ms(200);
			ks0108ClearScreen();
			ks0108GotoXY(60,20);
			ks0108Puts_P(PSTR("1"));
			_delay_ms(200);
			ks0108ClearScreen();
			// printing the image
			LoadBitmap2(IMAGE3);
			food=0;
			food2=0;
			event=0;
			// creating the food 
			create_ball_initially(25,9);
			xfood=xpos;
			yfood=ypos;
			create_ball_initially(45,12);
			xfood2=xpos;
			yfood2=ypos;
			// creating the ball
			score=0;
			//ERASE and CREATE BLOCK-1 TO BL0CK-2 BRIDGE
			ErHBlock(50,7,20);
			ErHBlock(50,12,20);
			CrVBlock(49,8,5);
			CrVBlock(70,8,5);	
			//ERASE and CREATE BLOCK-3 TO BL0CK-4 BRIDGE
			ErHBlock(50,48,20);
			ErHBlock(50,53,20);
			CrVBlock(49,48,5);
			CrVBlock(70,48,5);
			//ERASE and CREATE BLOCK-2 TO BL0CK-3 BRIDGE
			ErHBlock(57,19,13);
			ErHBlock(50,37,9);
			ErHBlock(50,42,15);
			ErHBlock(63,24,7);
			ErVBlock(57,20,19);
			ErVBlock(63,24,19);
			CrVBlock(70,19,5);
			CrVBlock(49,37,5);
			// printing the last block 
			ErHBlock(109,51,5);
			ErHBlock(109,56,5);
			CrVBlock(109,51,6);
			CrVBlock(113,51,6);
		// printing L:3
			CrHBlock(120,19,5);
			CrVBlock(124,17,3);
			CrVBlock(121,15,1);
			CrVBlock(123,15,1);
		    print_num(120,10,3);
		create_ball_initially(4,5); 
		check=0;
		    time=100;
			test_time=0;
			d1=0;
			d2=0;
			d3=0;

		while(level==3)
		{
			check_switch();
			check=surroundings_level3();
			x=read_adc(0);
			y=read_adc(1);	

		// condition for moving the ball
		// moving the ball right with no rebounding conditions
		if(y>358 && check%1000>=100 )
		  {
			  if(event==0 &&xpos+3==48)
			  {
			  	move_ball('s');
			  }
			  else if(event==2 && xpos+3 >=48 && ypos>=46&& ypos <=52)
			  {
			  	move_ball('s');
			  }
			  else if(event==3 && xpos+3 ==108 )
			  {
			 	 move_ball('s');
			  }
			  else 
			  {
			 	 move_ball('r');
			  } 
		  }
		// moving the ball left with no rebounding conditions
			  else if(y<346 && check %10000>=1000 && xpos>=0)
			  {
				  if(event==1 && xpos-1==49 && ypos>=46 && ypos<=52)
				  {
				  move_ball('s');
				  }
				  else 
				  {
				  move_ball('l');
				  }
			  }
			  // moving the ball upwards with no rebounding conditions
			  if(x>311 && check%10>=1)
			  {
			 		move_ball('u');
			  }
			  // moving ball down wards
			  else if(x<300 && check %100 >=10 && ypos<=62)
			  {
			  	move_ball('d');
			  }
		_delay_ms(15);

		if(event==0)
		{
		// if position of the ball is adjacent to that of food1
		if((xpos==xfood||xpos+1==xfood||xpos+2==xfood||xpos==xfood+1||xpos+1==xfood+1||xpos+2==xfood+1||xpos==xfood+2||xpos+1==xfood+2||xpos+2==xfood+2 )&& (ypos==yfood||ypos+1==yfood||ypos+2==yfood) && food==0 )//or they are in surroundings)    
		{
			clear_ball();
			create_ball_initially(xfood,yfood);
			clear_ball();
			create_ball_initially(xfood,yfood-1);
			food=1;
		}
		// if position of the ball is adjacent to that of food2
		if((xpos==xfood2||xpos+1==xfood2||xpos+2==xfood2||xpos==xfood2+1||xpos+1==xfood2+1||xpos+2==xfood2+1||xpos==xfood2+2||xpos+1==xfood2+2||xpos+2==xfood2+2 )&& (ypos==yfood2||ypos+1==yfood2||ypos+2==yfood2) && food2==0 )//or they are in surroundings)
		{
			clear_ball();
			create_ball_initially(xfood2,yfood2);
			food2=1;
		}
		if(food==1 && food2==1)
		{
		// creating the path
			 ErVBlock(49,7,5);
			 ErVBlock(70,7,5);
			 CrHBlock(49,7,22);
			 CrHBlock(49,12,22);
		 // creating new food positions 
			 xfood=xpos;// temporarily storing the positions
			 yfood=ypos;
			 create_ball_initially(79,19);
			 create_ball_initially(99,18);
			 xpos=xfood;// storing the positions back 
			 ypos=yfood;
			 xfood=79;
			 yfood=19;
			 xfood2=99;
			 yfood2=18;
			 food=0;
			 food2=0;
			 event=1;
			 Fscore=Fscore+300;
		}
		}
// end of if event ==0

		else if(event==1)
		{
		// if position of the ball is adjacent to that of food1
		if((xpos==xfood||xpos+1==xfood||xpos+2==xfood)&& (ypos==yfood||ypos+1==yfood||ypos+2==yfood) )//or they are in surroundings)
		{
			clear_ball();
			create_ball_initially(xfood,yfood);
			food=1;
		}
		// if position of the ball is adjacent to that of food2
		if((xpos==xfood2||xpos+1==xfood2||xpos+2==xfood2)&& (ypos==yfood2||ypos+1==yfood2||ypos+2==yfood2) )//or they are in surroundings)
		{
			clear_ball();
			create_ball_initially(xfood2,yfood2);
			food2=1;
		}
		if(food==1&& food2==1)
		{
		// creating the path
		    CrHBlock(57,19,14);
			CrHBlock(49,37,9);
			CrHBlock(49,42,15);
			CrHBlock(63,24,7);
			CrVBlock(57,20,18);
			CrVBlock(63,24,19);
			ErVBlock(70,20,4);
			ErVBlock(49,38,4);
			 // creating new food positions 
			 xfood=xpos;// temporarily storing the positions
			 yfood=ypos;
			 create_ball_initially(12,55);
			 create_ball_initially(39,52);
			 xpos=xfood;// storing the positions back 
			 ypos=yfood;
			 xfood=12;
			 yfood=55;
			 xfood2=39;
			 yfood2=52;
			 food=0;
			 food2=0;
			 event=2;
			 Fscore=Fscore+500;
		}
		}
// end of event ==1

		else if(event==2)
		{
		// if position of the ball is adjacent to that of food1
		if((xpos==xfood||xpos+1==xfood||xpos+2==xfood||xpos==xfood+1||xpos+1==xfood+1||xpos+2==xfood+1||xpos==xfood+2||xpos+1==xfood+2||xpos+2==xfood+2 )&& (ypos==yfood||ypos+1==yfood||ypos+2==yfood) && food==0 )//or they are in surroundings)
		{
			clear_ball();
			create_ball_initially(xfood,yfood);
			food=1;
		}
		// if position of the ball is adjacent to that of food2
		if((xpos==xfood2||xpos+1==xfood2||xpos+2==xfood2||xpos==xfood2+1||xpos+1==xfood2+1||xpos+2==xfood2+1||xpos==xfood2+2||xpos+1==xfood2+2||xpos+2==xfood2+2 )&& (ypos==yfood2||ypos+1==yfood2||ypos+2==yfood2) && food2==0)//or they are in surroundings)
		{
			clear_ball();
			create_ball_initially(xfood2,yfood2);
			food2=1;
		}
		if(food==1 && food2==1)
		{
		// creating the path
			CrHBlock(50,48,20);
			CrHBlock(50,53,20);
			ErVBlock(49,49,4);
			ErVBlock(70,49,4);
			 // creating new food positions 
			 xfood=xpos;// temporarily storing the positions
			 yfood=ypos;
			 create_ball_initially(72,40);
			 create_ball_initially(92,44);
			 xpos=xfood;// storing the positions back 
			 ypos=yfood;
			 xfood=72;
			 yfood=40;
			 xfood2=92;
			 yfood2=44;
			 food=0;
			 food2=0;
			 event=3;
			 Fscore=Fscore+700;
		}
		}
// end of event == 2

		else if(event==3)
		{
		// if position of the ball is adjacent to that of food1
		if((xpos==xfood||xpos+1==xfood||xpos+2==xfood||xpos==xfood+1||xpos+1==xfood+1||xpos+2==xfood+1||xpos==xfood+2||xpos+1==xfood+2||xpos+2==xfood+2 )&& (ypos==yfood||ypos+1==yfood||ypos+2==yfood) && food==0)//or they are in surroundings)
		{
			clear_ball();
			create_ball_initially(xfood,yfood);
			food=1;
		}
		// if position of the ball is adjacent to that of food2
		if((xpos==xfood2||xpos+1==xfood2||xpos+2==xfood2||xpos==xfood2+1||xpos+1==xfood2+1||xpos+2==xfood2+1||xpos==xfood2+2||xpos+1==xfood2+2||xpos+2==xfood2+2 )&& (ypos==yfood2||ypos+1==yfood2||ypos+2==yfood2)  && food2==0)//or they are in surroundings)
		{
			clear_ball();
			create_ball_initially(xfood2,yfood2);
			food2=1;
		}
		if(food==1&&food2==1)
		{
			Fscore=Fscore+900;
			ErVBlock(109,51,6);
			ErVBlock(113,51,6);
			CrHBlock(109,51,5);
			CrHBlock(109,56,5);
			event=4;
		}
		}
// end of event ==3
//level completed block
		if(xpos>=109&& event==4)
		{
			time3=time;
			Fscore=Fscore+71*time;
			ks0108ClearScreen();// clear the screen
			//print the message
			ks0108GotoXY(10,10);
			ks0108Puts_P(PSTR("Level Completed"));
			// print the score
			ks0108GotoXY(15,30);
	
			ks0108Puts_P(PSTR("Score -"));
			ks0108GotoXY(70,30);
			itoa(Fscore,a,10);
			ks0108Puts(a);
			_delay_ms(500);
			ks0108ClearScreen();

			if(Fscore>=high_score1)
			{
			high_score3=high_score2;
			high_score2=high_score1;
			high_score1=Fscore;
			ks0108ClearScreen();
			ks0108GotoXY(15,25);
			ks0108Puts_P(PSTR("!!!!HIGH SCORE!!!!"));
			_delay_ms(500);
			ks0108ClearScreen();
			}
			 if(Fscore>=high_score2 && Fscore< high_score1)
			{
			high_score3=high_score2;
			high_score2=Fscore;
			ks0108ClearScreen();
			ks0108GotoXY(15,25);
			ks0108Puts_P(PSTR("!!!!HIGH SCORE!!!!"));
			_delay_ms(500);
			ks0108ClearScreen();
			}
			if(Fscore>=high_score3 && Fscore<high_score2 && Fscore<high_score1)
			{
			high_score3=Fscore;
			ks0108ClearScreen();
			ks0108GotoXY(15,25);
			ks0108Puts_P(PSTR("!!!!HIGH SCORE!!!!"));
			_delay_ms(500);
			ks0108ClearScreen();
			}
			menu();	
			level=0;
		}
		if(test_time==20)
			{
				time--;
				test_time=0;

				d3=time%10;
				d2=(time/10)%10;
				d1=(time/100);

			if(time%100==99)
			{
				BlockClear(120,50);
				BlockClear(120,45);
				BlockClear(120,40);
				print_num(120,40,d3);
				print_num(120,45,d2);
				print_num(120,50,d1);
			}

			if(time%10==9)
			{
				BlockClear(120,40);
				BlockClear(120,45);
				print_num(120,40,d3);
				print_num(120,45,d2);
				print_num(120,50,d1);
			}
	
			if(d3>=0)
			{
				BlockClear(120,40);
				print_num(120,40,d3);
				print_num(120,45,d2);
				print_num(120,50,d1);
			}
			}
			if(time<=0)
			{
				ks0108ClearScreen();
				ks0108GotoXY(10,30);
				ks0108Puts_P(PSTR("!!!..Game Over..!!!"));
				_delay_ms(100);
				ks0108ClearScreen();
			//PRINT SCORE
				ks0108GotoXY(15,20);
				ks0108Puts_P(PSTR("Score -"));
				ks0108GotoXY(70,20);
				itoa(Fscore,a,10);
				ks0108Puts(a);
				_delay_ms(800);
				ks0108ClearScreen();

				if(Fscore>=high_score1)
				{
				high_score3=high_score2;
				high_score2=high_score1;
				high_score1=Fscore;
				ks0108ClearScreen();
				ks0108GotoXY(15,25);
				ks0108Puts_P(PSTR("!!!!HIGH SCORE!!!!"));
				_delay_ms(500);
				ks0108ClearScreen();
				}
				 if(Fscore>=high_score2 && Fscore< high_score1)
				{
				high_score3=high_score2;
				high_score2=Fscore;
				ks0108ClearScreen();
				ks0108GotoXY(15,25);
				ks0108Puts_P(PSTR("!!!!HIGH SCORE!!!!"));
				_delay_ms(500);
				ks0108ClearScreen();
				}
				if(Fscore>=high_score3 && Fscore<high_score2 && Fscore<high_score1)
				{
				high_score3=Fscore;
				ks0108ClearScreen();
				ks0108GotoXY(15,25);
				ks0108Puts_P(PSTR("!!!!HIGH SCORE!!!!"));
				_delay_ms(500);
				ks0108ClearScreen();
				}
		 	Fscore=0;
			level=0;
			menu();
			}

		  test_time++;
		}  // end of while loop of level-3
		}// end of if level==3


} // end of while(1)

}  // end of main


//---------------------------------------------------------------
//--------------------FUNCTIONS-------------------------------
//-----------------------------------------------------------------


void create_ball_initially(uint8_t xp,uint8_t yp)
{
	xpos=xp;
	ypos=yp;
	ks0108SetDot(xp,yp+1,BLACK);
	ks0108SetDot(xp+1,yp,BLACK);
	ks0108SetDot(xp+1,yp+2,BLACK);
	ks0108SetDot(xp+2,yp+1,BLACK);
//	ks0108SetDot(xp+1,yp+1,BLACK);
}

void create_ball(uint8_t xp,uint8_t yp)
{
	clear_ball();
	xpos=xp;
	ypos=yp;
	ks0108SetDot(xp,yp+1,BLACK);
	ks0108SetDot(xp+1,yp,BLACK);
	ks0108SetDot(xp+1,yp+2,BLACK);
	ks0108SetDot(xp+2,yp+1,BLACK);
//	ks0108SetDot(xp+1,yp+1,BLACK);
}

void clear_ball()
{
	ks0108SetDot(xpos,ypos+1,WHITE);
	ks0108SetDot(xpos+1,ypos,WHITE);
	ks0108SetDot(xpos+1,ypos+2,WHITE);
	ks0108SetDot(xpos+2,ypos+1,WHITE);
//	ks0108SetDot(xpos+1,ypos+1,WHITE);
}

void move_ball(char dir)
{
		if(dir=='r')// move the ball towards right
		{
		clear_ball();
		xpos=xpos+1;
		create_ball(xpos,ypos);
		ypos=ypos;
		}
		else if(dir =='l')
		{
		clear_ball();
		xpos=xpos-1;
		create_ball(xpos,ypos);
		}
		else if(dir=='u')
		{
		clear_ball();
		ypos=ypos-1;
		create_ball(xpos,ypos);
		}
		else if( dir=='d')
		{
		clear_ball();
		ypos=ypos+1;
		create_ball(xpos,ypos);
		}
		_delay_ms(10);
}

//function to check whether a particular pixel value is 0 or 1 
int cb(unsigned char *bmp,int xc, int yc)
{
	int var,by;
	var=(yc/8)*128+xc;
	by=pgm_read_byte(bmp+var);
	if(bit_is_set(by,(yc%8)))
	{return 1;}
	else if (bit_is_clear(by,(yc%8)))
	{return 0;}
}


// function to set a particular pixel value to 0 to 1
/*
int wb(unsigned char *bmp,int xc,int yc,int val)
{
	int var,by;
	var=(yc/8)*128+xc;
	if(val==1)
	{ 
	*(bmp+var)=255;
	}
	else if(val ==0)
	{
	*(bmp+var)&=~(1<<(yc%8));
	}
}
*/

// function to check the surroundings of the ball
int surroundings ()
{
	int count=0;
	// upward direction 
	if(cb(IMAGE,xpos,ypos-1)==0 && cb(IMAGE,xpos+1,ypos-1)==0 && cb(IMAGE,xpos+2,ypos-1)==0)
	{
	count =count+1;
	}
	// downwards
	if(cb(IMAGE,xpos,ypos+3)==0 && cb(IMAGE,xpos+1,ypos+3)==0 && cb(IMAGE,xpos+2,ypos+3)==0)
	{
	count =count+10;
	}
	// right
	if(cb(IMAGE,xpos+3,ypos)==0 && cb(IMAGE,xpos+3,ypos+1)==0 && cb(IMAGE,xpos+3,ypos+2)==0)
	{
	count =count+100;
	} 
	 // left 
	 if(cb(IMAGE,xpos-1,ypos)==0 && cb(IMAGE,xpos-1,ypos+1)==0 && cb(IMAGE,xpos-1,ypos+2)==0)
	{
	count =count+1000;
	}
	return count;
}

int surroundings_level2 ()
{
	int count=0;
	// upward direction 
	if(cb(IMAGE2,xpos,ypos-1)==0 && cb(IMAGE2,xpos+1,ypos-1)==0 && cb(IMAGE2,xpos+2,ypos-1)==0)
	{
	count =count+1;
	}
	// downwards
	if(cb(IMAGE2,xpos,ypos+3)==0 && cb(IMAGE2,xpos+1,ypos+3)==0 && cb(IMAGE2,xpos+2,ypos+3)==0)
	{
	count =count+10;
	}
	// right
	if(cb(IMAGE2,xpos+3,ypos)==0 && cb(IMAGE2,xpos+3,ypos+1)==0 && cb(IMAGE2,xpos+3,ypos+2)==0)
	{
	count =count+100;
	} 
	 // left 
	 if(cb(IMAGE2,xpos-1,ypos)==0 && cb(IMAGE2,xpos-1,ypos+1)==0 && cb(IMAGE2,xpos-1,ypos+2)==0)
	{
	count =count+1000;
	}
	return count;
}

int surroundings_level3 ()
{
	int count=0;
	// upward direction 
	if(cb(IMAGE3,xpos,ypos-1)==0 && cb(IMAGE3,xpos+1,ypos-1)==0 && cb(IMAGE3,xpos+2,ypos-1)==0)
	{
	count =count+1;
	}
	// downwards
	if(cb(IMAGE3,xpos,ypos+3)==0 && cb(IMAGE3,xpos+1,ypos+3)==0 && cb(IMAGE3,xpos+2,ypos+3)==0)
	{
	count =count+10;
	}
	// right
	if(cb(IMAGE3,xpos+3,ypos)==0 && cb(IMAGE3,xpos+3,ypos+1)==0 && cb(IMAGE3,xpos+3,ypos+2)==0)
	{
	count =count+100;
	} 
	 // left 
	 if(cb(IMAGE3,xpos-1,ypos)==0 && cb(IMAGE3,xpos-1,ypos+1)==0 && cb(IMAGE3,xpos-1,ypos+2)==0)
	{
	count =count+1000;
	}
	return count;
}

// function to open the curtain when the game starts
void OpeningCur(char c)
{	
	int i,k;
	if(c=='W')
	{
	for(i=64,k=63;i>=0,k<=127;i--,k++)
	{	
		ks0108FillRect(i, 1, 1, 61, WHITE);
		ks0108FillRect(k, 1, 1, 61, WHITE);	
	}
	}
	if(c=='B')
	{
	for(i=64,k=64;i>=0,k<=128;i--,k++)
	{
		
		ks0108FillRect(i, 1, 1, 62, BLACK);

		ks0108FillRect(k, 1, 1, 62, BLACK);
	}
	}
}

// functions for  creating lines 
void CrVBlock(int x, int y, int n)
{	int i;
	for(i=0;i<n;i++)
	{
	ks0108SetDot(x,y+i,BLACK);
	}
}

void CrHBlock(int x, int y, int n)
{	int i;
	for(i=0;i<n;i++)
	{
	ks0108SetDot(x+i,y,BLACK);
	}
}

void ErVBlock(int x, int y, int n)
{
	int i;
	for(i=0;i<n;i++)
	{
	ks0108SetDot(x,y+i,WHITE);
	}
}

void ErHBlock(int x, int y, int n)
{
	int i;
	for(i=0;i<n;i++)
	{
	ks0108SetDot(x+i,y,WHITE);
	}
}

// functions to print the number
void print_num(int x, int y, int n)
{
switch(n)
{
	case 0:
	{
	CrHBlock(x,y,5);
	CrHBlock(x,y+3,5);
	CrVBlock(x+4,y,3);
	CrVBlock(x,y,3);
	break;
	}
	case 1:
	{
	CrHBlock(x,y,5);
	CrVBlock(x+4,y-1,3);
	CrVBlock(x,y+1,1);
	break;
	}
	case 2:
	{
	CrVBlock(x,y,3);
	CrHBlock(x,y,3);
	CrVBlock(x+2,y,3);
	CrHBlock(x+2,y+2,3);
	CrVBlock(x+4,y,3);
	break;
	}
	case 3:
	{
	CrHBlock(x,y,5);
	CrVBlock(x,y,3);
	CrVBlock(x+2,y,3);
	CrVBlock(x+4,y,3);
	break;
	}
	case 4:
	{
	CrHBlock(x,y,5);
	CrVBlock(x+3,y-1,4);
	CrVBlock(x+1,y+2,1);
	CrVBlock(x,y,2);
	CrVBlock(x+2,y+3,1);
	break;
	}
	case 5:
	{
	CrHBlock(x,y+2,3);
	CrVBlock(x,y,3);
	CrVBlock(x+2,y,3);
	CrHBlock(x+2,y,3);
	CrVBlock(x+4,y,3);
	break;
	}
	case 6:
	{
	CrHBlock(x,y+2,5);
	CrVBlock(x,y,3);
	CrVBlock(x+4,y,3);
	CrHBlock(x+2,y,3);
	CrVBlock(x+2,y,3);
	break;
	}
	case 7:
	{
	CrHBlock(x,y,5);
	CrVBlock(x,y,3);
	CrHBlock(x,y+2,2);
	break;
	}
	case 8:
	{
	CrHBlock(x,y,5);
	CrVBlock(x,y,3);
	CrVBlock(x+2,y,3);
	CrVBlock(x+4,y,3);
	CrHBlock(x,y+2,5);
	break;
	}
	case 9:
	{
	CrHBlock(x,y,5);
	CrVBlock(x+2,y,3);
	CrVBlock(x,y,3);
	CrVBlock(x+2,y,3);
	CrVBlock(x+4,y,3);
	CrHBlock(x,y+2,3);
	break;
	}
}
}


void numEr(int x, int y, int n)
{
switch(n)
{
	case 0:
	{
	ErHBlock(x,y,5);
	ErHBlock(x,y-3,5);
	ErVBlock(x+4,y-3,3);
	ErVBlock(x,y-3,3);
	break;
	}
	case 1:
	{
	ErHBlock(x,y,5);
	ErVBlock(x+4,y-1,3);
	ErVBlock(x,y+1,1);
	break;
	}
	case 2:
	{
	ErVBlock(x,y,3);
	ErHBlock(x,y,3);
	ErVBlock(x+2,y,3);
	ErHBlock(x+2,y+2,3);
	ErVBlock(x+4,y,3);
	break;
	}
	case 3:
	{
	ErHBlock(x,y,5);
	ErVBlock(x,y,3);
	ErVBlock(x+2,y,3);
	ErVBlock(x+4,y,3);
	break;
	}
	case 4:
	{
	ErHBlock(x,y,5);
	ErVBlock(x+3,y-1,4);
	ErVBlock(x+1,y+2,1);
	ErVBlock(x,y,2);
	ErVBlock(x+2,y+3,1);
	break;
	}
	case 5:
	{
	ErHBlock(x,y+2,3);
	ErVBlock(x,y,3);
	ErVBlock(x+2,y,3);
	ErHBlock(x+2,y,3);
	ErVBlock(x+4,y,3);
	break;
	}
	case 6:
	{
	ErHBlock(x,y+2,5);
	ErVBlock(x,y,3);
	ErVBlock(x+4,y,3);
	ErHBlock(x+2,y,3);
	ErVBlock(x+2,y,3);
	break;
	}
	case 7:
	{
	ErHBlock(x,y,5);
	ErVBlock(x,y,3);
	ErHBlock(x,y+2,2);
	break;
	}
	case 8:
	{
	ErHBlock(x,y,5);
	ErVBlock(x,y,3);
	ErVBlock(x+2,y,3);
	ErVBlock(x+4,y,3);
	ErHBlock(x,y+2,5);
	break;
	}
	case 9:
	{
	ErHBlock(x,y,5);
	ErVBlock(x+2,y,3);
	ErVBlock(x,y,3);
	ErVBlock(x+2,y,3);
	ErVBlock(x+4,y,3);
	ErHBlock(x,y+2,3);
	break;
	}
}
}

void accelerate()
{
		check_switch();
		x=read_adc(0);
		y=read_adc(1);
		if(y>=335 && y<350)
	     {
	     k1=0;
	       }
	     else if(y>=350 && y<365)
	    {
	    k1=1;
	     }
	    else if(y>=365 && y<380)
	   {
	   k1=2;
	   }
	   else if(y>=380 && y<405)
	   {
	   k1=3;
	  }
	   else if(y>=405 )
	  {
	  k1=4;
	   }
	   else if(y>=320 && y<335)
	   {
	  k1=-1;
	   }

	  else if(y>=305 && y<320)
	   {
	  k1=-2;
	   }
	  else if(y>=295 && y<=305)
	  {
	  k1=-3;
	  }
	  else if(y<=295)
	  {
	  k1=-4;
	  }


	  if(x>=335 && x<350)
	  {
	  k2=0;
	  }
	  else if(x>=350 && x<365)
	  {
	  k2=1;
	  }
	  else if(x>=365 && x<380)
	  {
	  k2=2;
	  }
	  else if(x>=380 && x<405)
	 {
	  k2=3;
	  }
	  else if(x>=405 )
	 {
	  k2=4;
	  }
	  else if(x>=320 && x<335)
	  {
	  k2=-1;
	  }

	  else if(x>=305 && x<320)
	  {
	  k2=-2;
	  }
	  else if(x>=295 && x<=305)
	  {
	  k2=-3;
	  }
	  else if(x<=295)
	  {
	  k2=-4;
	  }
}

void check_switch()
{
	switches();// check the switches 
	// if switch 1 is pressed
	if (sw==1)
	{
	level=0;
	sw=0;
	}
	else if(sw==2)
	{
		while(sw==2)
		{
		switches();
		}
	}
	else if(sw==3)
	{
	sw=0;
	}
	else if(sw==4)
	{prev_level=level;
	level=-1;
	sw=0;
	}
}

void switches()
	{
	if(bit_is_clear(PINB,5))
	{
	sw=1;
	}
	else if(bit_is_clear(PINB,6))
	{
	sw=2;
	}
	else if(bit_is_clear(PINB,7))
	{
	sw=3;
	}
	else if(bit_is_clear(PINB,4))
	{
	sw=4;
	}
	else if(bit_is_clear(PINB,2))
	{
	sw=5;
	}
}

// function to print menu 
void menu()
{
		int jeetu=0;
	    while(sw!=1)
   
	   { jeetu++;
	   switches();
     
		 if(jeetu==1)
		 {
	
		ks0108DrawRect(1,1,126,62,BLACK);
		ks0108DrawRect(2,2,124,60,BLACK);
   
	   ks0108GotoXY(38,10);
		ks0108Puts_P(PSTR("Press"));
		ks0108GotoXY(18,25);
		ks0108Puts_P(PSTR("1. Restart"));
		ks0108GotoXY(15,40);
		ks0108Puts_P(PSTR("5. High Scores"));
		}
		if(jeetu==4)
		{
		jeetu=2;
		}

		if(sw==5)
		{ks0108ClearScreen();
		ks0108DrawRect(1,1,126,62,BLACK);
		ks0108DrawRect(2,2,124,60,BLACK);
     
		 ks0108GotoXY(15,10);
		ks0108Puts_P(PSTR("HS1-"));
		itoa(high_score1,a,10);
		ks0108GotoXY(44,10);
		ks0108Puts(a);
	
		ks0108GotoXY(15,25);
		ks0108Puts_P(PSTR("HS2-"));
	    itoa(high_score2,b,10);
		ks0108GotoXY(45,25);
		ks0108Puts(b);

		ks0108GotoXY(15,40);
		ks0108Puts_P(PSTR("HS3-"));
		itoa(high_score3,c,10);
		ks0108GotoXY(45,40);
		ks0108Puts(c);

		_delay_ms(800);
		ks0108ClearScreen();
		sw=7;
		jeetu=0;
		}
		if(sw==1)
		{
		break;
		level=0;
		}
	
		}
}
void BlockClear(int x, int y)
{
	ErHBlock(x,y,5);
	ErHBlock(x,y-1,5);
	ErHBlock(x,y-2,5);
	ErHBlock(x,y+1,5);
	ErHBlock(x,y+2,5);
	ErHBlock(x,y+3,5);
}
