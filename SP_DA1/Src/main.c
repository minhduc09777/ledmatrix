/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "font.h"
#include "stdlib.h"
#include "math.h"
#include "monalisa.h"
#include "banana.h"
#include "stdio.h"
#include "smartc.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
RTC_HandleTypeDef hrtc;

TIM_HandleTypeDef htim1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
static void MX_RTC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

#define setbit(sfr,bit)		(sfr|=(1<<bit))
#define clrbit(sfr,bit)		(sfr&=~(1<<bit))

char check_bit(unsigned char byte,unsigned char bit){
	if((byte&(1<<bit))==0x00){
		return 0;
	}
	else{
		return 1;
	}
}

uint16_t manght[64][128];

unsigned short hang=0,tsb=0x0001,tsg=0x0020,tsr=0x0800,demrgb=0,ts=0x0001,sig=0;
const unsigned short mangtg[]={160,320,640,1280,2560,5120,10240,20480};
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	    if(htim->Instance ==TIM1)
			{
				 for(int ___i=0;___i<256;___i++)
			   {
					 GPIOB->ODR=0;
					 if(___i<128){
							 if((manght[hang][___i] & ts)){GPIOB->ODR|=(0x10<<5);}
							 if((manght[hang+16][___i] & ts)){GPIOB->ODR|=(0x20<<5);}
							 if((manght[hang][___i] & (tsg))){GPIOB->ODR|=(0x04<<5);}
							 if((manght[hang+16][___i] & (tsg))){GPIOB->ODR|=(0x08<<5);}
							 if((manght[hang][___i] & (ts<<11))){GPIOB->ODR|=(0x01<<5);}
							 if((manght[hang+16][___i] & (ts<<11))){GPIOB->ODR|=(0x02<<5);}
					 }
					 else{
						 if((manght[63-hang][127-___i] & ts)) {GPIOB->ODR|=(0x10<<5);}
						 if((manght[47-hang][127-___i] & ts)) {GPIOB->ODR|=(0x20<<5);}
						 if((manght[63-hang][127-___i] & tsg)) {GPIOB->ODR|=(0x04<<5);}
						 if((manght[47-hang][127-___i] & tsg)) {GPIOB->ODR|=(0x08<<5);}
						 if((manght[63-hang][127-___i] & (ts<<11))) {GPIOB->ODR|=(0x01<<5);}
						 if((manght[47-hang][127-___i] & (ts<<11))) {GPIOB->ODR|=(0x02<<5);}		
					 }
						 
					   GPIOB->ODR |= 0x0008;
					 }
				TIM1->ARR = mangtg[demrgb];
				HAL_GPIO_WritePin(GPIOB,OE_Pin,1);
				GPIOA->ODR = hang;
				HAL_GPIO_WritePin(GPIOB,OE_Pin,0);
					 
				hang++;
				 if(hang==16){
					 hang=0;
					 demrgb++;
					 ts<<=1;
					 tsg<<=1;
					 if(tsg>0x0400) tsg=0x0020;
					 if(ts>0x0010) ts=0x0001;
					 if(demrgb==8){ 
						demrgb=0;
					 }

				 }
			}						
}
void MATRIX_pixel_color(unsigned char x, unsigned char y,unsigned char r,unsigned char g,unsigned char b){
		if(y>63 || x>127) return;
	  if(y<0 || x<0) return;
	  manght[y][x]=(((r & 0xF8) | (g >> 5))<<8)|(((g & 0x1C) << 3) | (b  >> 3));
}
void MATRIX_pixel_color565(unsigned char x, unsigned char y,uint16_t mau){
		if(y>63 || x>127) return;
	  if(y<0 || x<0) return;
	  manght[y][x]=mau;
}
void MATRIX_line(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned char r,unsigned char g,unsigned char b)
{
   unsigned int        dy, dx;
   signed int  addx=1, addy=1;
   signed int P, diff;
	
   #ifdef LARGE_LCD
   unsigned int i=0;
   dx = abs((signed int)(x2 - x1));
   dy = abs((signed int)(y2 - y1));
   #else
   unsigned int  i=0;
   dx = abs((signed int)(x2 - x1));
   dy = abs((signed int)(y2 - y1));
   #endif
   if(x1 > x2)
      addx = -1;
   if(y1 > y2)
      addy = -1;
   if(dx >= dy)
   {
      dy *= 2;
      P = dy - dx;
      diff = P - dx;

      for(; i<=dx; ++i)
      {
    	  MATRIX_pixel_color(x1, y1, r,g,b);
         if(P < 0)
         {
            P  += dy;
            x1 += addx;
         }
         else
         {
            P  += diff;
            x1 += addx;
            y1 += addy;
         }
      }
   }
   else
   {
      dx *= 2;
      P = dx - dy;
      diff = P - dy;
      for(; i<=dy; ++i)
      {
    	  MATRIX_pixel_color(x1, y1, r,g,b);

         if(P < 0)
         {
            P  += dx;
            y1 += addy;
         }
         else
         {
            P  += diff;
            x1 += addx;
            y1 += addy;
         }
      }
   }
}
void MATRIX_circle(unsigned int x, unsigned int y, unsigned int radius, int fill,  unsigned char r1,unsigned char g1,unsigned char b1)
{
   signed int  a, b, P;
   a = 0;
   b = radius;
   P = 1 - radius;
   do
   {
      if(fill)
      {
    	  MATRIX_line(x-a, y+b, x+a, y+b,r1,g1,b1);
    	  MATRIX_line(x-a, y-b, x+a, y-b,r1,g1,b1);
    	  MATRIX_line(x-b, y+a, x+b, y+a,r1,g1,b1);
    	  MATRIX_line(x-b, y-a, x+b, y-a,r1,g1,b1);
      }
      else
      {
    	  MATRIX_pixel_color(a+x, b+y, r1,g1,b1);
    	  MATRIX_pixel_color(b+x, a+y, r1,g1,b1);
    	  MATRIX_pixel_color(x-a, b+y, r1,g1,b1);
    	  MATRIX_pixel_color(x-b, a+y, r1,g1,b1);
    	  MATRIX_pixel_color(b+x, y-a, r1,g1,b1);
    	  MATRIX_pixel_color(a+x, y-b, r1,g1,b1);
    	  MATRIX_pixel_color(x-a, y-b, r1,g1,b1);
    	  MATRIX_pixel_color(x-b, y-a, r1,g1,b1);
      }
      if(P < 0)
         P += 3 + 2 * a++;
      else
         P += 5 + 2 * (a++ - b--);
    } while(a <= b);
}
void MATRIX_rect(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, int fill, unsigned char r,unsigned char g,unsigned char b)
{
   if(fill)
   {
      #ifdef LARGE_LCD
      unsigned int i, xmin, xmax, ymin, ymax;
      #else
      unsigned int  i, xmin, xmax, ymin, ymax;
      #endif
      if(x1 < x2)                            //  Find x min and max
      {
         xmin = x1;
         xmax = x2;
      }
      else
      {
         xmin = x2;
         xmax = x1;
      }

      if(y1 < y2)                            // Find the y min and max
      {
         ymin = y1;
         ymax = y2;
      }
      else
      {
         ymin = y2;
         ymax = y1;
      }
      for(; xmin <= xmax; ++xmin)
      {
         for(i=ymin; i<=ymax; ++i)
         {
        	 MATRIX_pixel_color(xmin, i, r,g,b);
         }
      }
   }
   else
   {
      MATRIX_line(x1, y1, x2, y1, r,g,b);      // Draw the 4 sides
      MATRIX_line(x1, y2, x2, y2, r,g,b);
      MATRIX_line(x1, y1, x1, y2, r,g,b);
      MATRIX_line(x2, y1, x2, y2, r,g,b);
   }
}
void MATRIX_putchar8x8(unsigned char x,unsigned char y,unsigned char chu,unsigned char r,unsigned char g,unsigned char b){
	chu=chu-32;
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
				if(check_bit(myfont8x8[chu][i],j)){
					MATRIX_pixel_color(y+j,x+i,r,g,b);
				}
		}
	}
}
void MATRIX_putStr8x8(unsigned char x,unsigned char y,unsigned char a[],unsigned char r,unsigned char g,unsigned char b){
	unsigned char i=0;
	while(a[i]!=0x00){
		 MATRIX_putchar8x8(x,y,a[i],r,g,b);
		 i++;
		 y=y+8;
	}
}
//font cos dau
void MATRIX_putchar16x16(unsigned char x,unsigned char y,unsigned char chu,unsigned char r,unsigned char g,unsigned char b){
	 for(int i=0;i<32;i=i+2)
		 for(int j=0;j<16;j++)
		 {
			 if(check_bit(font11[chu][i+j/8],(15-j)%8)){
					if(x+i/2 >128 || x+i/2<0 ) return;
					if(y+j >255 || y+j<0)  return;
				   MATRIX_pixel_color(y+j,x+i/2,r,g,b);
			}		 
		}
}
void MATRIX_putStr16x16(signed int x,signed int y,unsigned char a[],unsigned char r,unsigned char g,unsigned char b){
	unsigned char i=0;
	while(a[i]!=0x00){
		 MATRIX_putchar16x16(x,y,a[i],r,g,b);
		 i++;
		 y=y+8;
	}
}
void MATRIX_putchar16x32(unsigned char x,unsigned char y,unsigned char chu,unsigned char r,unsigned char g,unsigned char b){
	for(int i=0;i<64;i=i+2){
		for(int j=0;j<16;j++){
				if(check_bit(myfont16x32[chu][i+j/8],(15-j)%8)){
					MATRIX_pixel_color(y+j,x+i/2,r,g,b);
				}
		}
	}
}
void MATRIX_putStr16x32(unsigned char x,unsigned char y,unsigned char a[],unsigned char r,unsigned char g,unsigned char b){
	unsigned char i=0;
	while(a[i]!=0x00){
		 MATRIX_putchar16x32(x,y,a[i],r,g,b);
		 i++;
		 y=y+15;
	}
}
/*unsigned short bufferio[16][128];
void giaima(){
 for( int i=0;i<16;i++)
 {
	 for(int j=0;j<16;j=j+2){
		 for(int k=0;k<8;k++){
			  bufferio[i][j*16+k]=0;
			  bufferio[i][j*16+k+8]=0;
			  if(check_bit(bufferR[i*16+j],k)!=0x00) bufferio[i][j*8+k] |=0x0020;  //chon hang chon 16 cot roi lay tung bit 16 cot
			  if(check_bit(bufferR[i*16+j+1],k)!=0x00) bufferio[i][j*8+k+8] |=0x0020;
			 
			  if(check_bit(bufferR[(16+i)*16+j],k)!=0x00) bufferio[i][j*8+k] |=0x0040;
			  if(check_bit(bufferR[(16+i)*16+j+1],k)!=0x00) bufferio[i][j*8+k+8] |=0x0040;
			 
			  if(check_bit(bufferG[i*16+j],k)!=0x00) bufferio[i][j*8+k] |=0x0080;
			  if(check_bit(bufferG[i*16+j+1],k)!=0x00) bufferio[i][j*8+k+8] |=0x0080;
			 
			 
			  if(check_bit(bufferG[(16+i)*16+j],k%8)!=0x00) bufferio[i][j*8+k] |=0x0100;
		  	if(check_bit(bufferG[(16+i)*16+j+1],k%8)!=0x00) bufferio[i][j*8+k+8] |=0x0100;
			 
			 
			  if(check_bit(bufferB[i*16+j],k%8)!=0x00) bufferio[i][j*8+k] |=0x0200;
			  if(check_bit(bufferB[i*16+j+1],k%8)!=0x00) bufferio[i][j*8+k+8] |=0x0200;
			 
			 
			  if(check_bit(bufferB[(16+i)*16+j],k%8)!=0x00) bufferio[i][j*8+k] |=0x0400;
				if(check_bit(bufferB[(16+i)*16+j+1],k%8)!=0x00) bufferio[i][j*8+k+8] |=0x0400;
		 }
	 }
 }
}*/
void drawPixelRGB565(int16_t x, int16_t y, uint16_t color) {
  uint8_t r = ((((color >> 11) & 0x1F) * 527) + 23) >> 6;
  uint8_t g = ((((color >> 5) & 0x3F) * 259) + 33) >> 6;
  uint8_t b = (((color & 0x1F) * 527) + 23) >> 6;
  MATRIX_pixel_color( x,  y, r, g,b);
}
void drawImage(int x, int y,int w,int h,uint16_t *a)
{
  int imageHeight = h;
  int imageWidth = w;
  int counter = 0;
  for (int yy = 0; yy < imageHeight; yy++)
  {
    for (int xx = 0; xx < imageWidth; xx++)
    {
			MATRIX_pixel_color565(xx+x,yy+y,a[counter]);
      counter++;
    }
  }
}
void matrix_clear_green(unsigned char x,unsigned char y){
	  
		for(int i=0;i<x;i++){
			for(int j=0;j<y;j++){
				manght[i][j]=0;
			}
		}
}
void giaimaanh3(unsigned char *anh, unsigned int dai, unsigned int rong, signed int x, signed int y)
{
  unsigned char n,hang=0,cot=0;
   for(n=0;n<(dai*rong);n++)
   {   
				 MATRIX_pixel_color(y+cot,x+hang,anh[n],anh[dai*rong+n],anh[2*dai*rong+n]);
         cot++;
         if(cot==dai) {cot=0;hang++;}
   }
}
void Chord(int r, float rot)
{
	
  int nodes = 6;
  float x[nodes];
  float y[nodes];
  for (int i=0; i<nodes; i++)
  {
    float a = rot + (3.14*2*i/nodes);
    x[i] = 31+3 + cos(a)*r;
    y[i] = 16 + sin(a)*r;
  }
	
  for (int i=0; i<(nodes-1); i++)
    for (int j=i+1; j<nodes; j++)
      MATRIX_line(15+x[i],15+y[i], 15+x[j],15+y[j], 0,255,0);
	
	
}
int i_chuoi;
float rot;
float rotationSpeed = 3.14/15;
int r_chor=1,tt_chor=0;
void hieuungchord(){
	
		if(tt_chor==0){
				Chord(r_chor, rot+=rotationSpeed);
				r_chor+=3;
				if(r_chor>22){
					r_chor=0;
					tt_chor=1;
				}
		}
		else{
				 Chord(22-r_chor, rot-=rotationSpeed);
				r_chor+=3;
				if(r_chor>22){
					r_chor=0;
					tt_chor=0;
				}
		}
}





unsigned short hang_led,p10_x,p10_y;
char hieuung=0;

void P10_sendnumBIG(char num)
{
			 for(int y=0;y<15;y++)
	       {
					 if(y+p10_y>127)break;
					 for(int x=0;x<10;x++)
							{
								if(x+p10_x>127)break;
							     MATRIX_pixel_color(x+p10_x,y+p10_y,number_fx[hieuung][num][0][y][x],number_fx[hieuung][num][1][y][x],number_fx[hieuung][num][2][y][x]);;				   
					    }
				 }
		p10_x+=11;
}
void P10_chonvitri(char y,char x)
{
	 p10_x=x;
	 p10_y=y;
}
void insoto(char y,char x,char so)
{
	
	P10_chonvitri(y,x);
	P10_sendnumBIG(so/10);
	P10_sendnumBIG(so%10);
}

void P10_sendnumSmall(char num)
{
		for(int mau=0;mau<3;mau++)
			 for(int y=0;y<8;y++)
					 for(int x=0;x<5;x++)
							 MATRIX_pixel_color(y+p10_y,x+p10_x,number_nho_fx[hieuung][num][mau][y][x],number_nho_fx[hieuung][num][mau+1][y][x],number_nho_fx[hieuung][num][mau+2][y][x]);
		p10_x+=6;
}
void insonho(char y,char x,char so)
{
	P10_chonvitri(y,x);
	P10_sendnumSmall(so/10);
	P10_sendnumSmall(so%10);
}





float x2,y2,x3,y3,x4,y4;
float x2_1,y2_1,x3_1,y3_1,x4_1,y4_1;
signed int humau_cir=63,humau_cir1=0;
unsigned char giay_ht,phut_ht,gio_ht;
unsigned char humau_chu=0;

//unsigned char manght_dhs[][][]
signed char down=14;
char gio=3,phut=30,giay=0;
void donghokim(){
	
//	MATRIX_putStr16x16color(0,57,"12",0,humau_chu);
//	MATRIX_putStr16x16color(55,117,"3",55,humau_chu);
//	MATRIX_putStr16x16color(55,4,"9",55,humau_chu);
//	MATRIX_putStr16x16color(112,60,"6",112,humau_chu);
	MATRIX_circle(63,32,31,0,255,255,255);
	humau_chu++;
	if(humau_chu>63){
		humau_chu=0;
	}
	 humau_cir--;
	if(humau_cir==0){
		humau_cir=63;
	}
	humau_cir1++;
	if(humau_cir1>127){
		humau_cir1=32;
	}
		
	 MATRIX_line(64,32,x3,y3,0,255,0);
	 MATRIX_line(64,32,x3_1,y3_1,0,255,0);

	
		MATRIX_line(64,32,x4,y4,255,0,0);
		MATRIX_line(64,32,x4_1,y4_1,255,0,0);
		
		MATRIX_line(64,32,x2,y2,0,0,255);
		MATRIX_line(64,32,x2_1,y2_1,0,0,255);
	
	
	
		x2=64+25*sin(3.14/30*giay);
		y2=32-25*cos(3.14/30*giay);
		x2_1=64+5*sin(3.14/30*((giay+30)%60));
		y2_1=32-5*cos(3.14/30*((giay+30)%60));
	
		x3=64+15*sin(3.14/30*phut);
		y3=32-15*cos(3.14/30*phut);
		x3_1=64+6*sin(3.14/30*((phut+30)%60));
		y3_1=32-6*cos(3.14/30*((phut+30)%60));
	
		x4=64+10*sin((3.14/6*gio)+(phut/10)*3.14/30);
		y4=32-10*cos((3.14/6*gio)+(phut/10)*3.14/30);
		x4_1=64+3*sin((3.14/6*((gio+6)%24))+(phut/10)*3.14/30);
		y4_1=32-3*cos((3.14/6*((gio+6)%24))+(phut/10)*3.14/30);
		
	/*	if(giay_ht != giay){
			 for(char color=0;color<3;color++)
			 {
					for(char x=79;x<79+10;x++) 
					 manght_dhs[color][93%15][x%22]= number_fx[hieuung][giay/10%10][color][down][x-79];
					for(char x=79+11;x<79+21;x++) 
					 manght_dhs[color][93%15][x%22]= number_fx[hieuung][giay%10][color][down][x-(79+11)];
			 }
			 down--;
			 if(down<0){
				 down=14;
				 giay_ht=giay;
			 }
			
			
		for(char color=0;color<3;color++)
		 for(char y=93+14;y>93;y--)
			 for(char x=79;x<79+21;x++) 
				 manght[color][y][x]=manght_dhs[color][y%15][x%22];
			
		}else insoto(93,79,giay);*/


		hieuung=2;
		//latsoto(giay,93,79,5);	
	//	insoto(93,79,giay);		
	//	insonho(93,60,phut);
	//	insonho(93,41,gio);
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
	RTC_TimeTypeDef sTime;
	RTC_DateTypeDef sTime_date;
	

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_RTC_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start_IT(&htim1);
	unsigned char cot=0;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	//	MATRIX_putStr16x32(0,0,"DO 2",255,255,255);
		drawImage(cot,0,64,32,(uint16_t *)mario);
		insoto(32,cot,9);
		cot++;
		if(cot>128) cot=0;
		
		matrix_clear_green(cot,0);
	//	drawImage(0,32,32,32,(uint16_t *)image);
	//	MATRIX_putStr16x32(32,0,"project",255,255,255);
	//	MATRIX_putStr8x8(16,0,"project",0,255,255);
	//	MATRIX_putStr16x16(0,0,"Duc",255,255,0);
//	giaimaanh3((unsigned char *)smartc ,64,32,0,0);
	/*	donghokim();
		giay++;
		if(giay==60) giay=0;*/
		//hieuungchord();
	//	drawImage(0,0,64,32,(uint16_t *)banana_frame_1);
	//	matrix_clear_green(64,128);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */
  /* USER CODE END RTC_Init 0 */

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */
  /**Initialize RTC Only 
  */
  hrtc.Instance = RTC;
  hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_ALARM;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */
	RTC_TimeTypeDef sTime;
	RTC_DateTypeDef sTime_date;
/*	sTime.Seconds=0;
	sTime.Minutes=0;
	sTime.Hours=14;
	HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);*/
	sTime_date.Date=7;
	sTime_date.Month=12;
	sTime_date.Year=19;
	HAL_RTC_SetDate(&hrtc,&sTime_date, RTC_FORMAT_BIN);

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_DOWN;
  htim1.Init.Period = 40;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, A_Pin|B_Pin|C_Pin|D_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, B2_Pin|CLK_Pin|OE_Pin|R1_Pin 
                          |R2_Pin|G1_Pin|G2_Pin|B1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : A_Pin B_Pin C_Pin D_Pin */
  GPIO_InitStruct.Pin = A_Pin|B_Pin|C_Pin|D_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : B2_Pin CLK_Pin OE_Pin R1_Pin 
                           R2_Pin G1_Pin G2_Pin B1_Pin */
  GPIO_InitStruct.Pin = B2_Pin|CLK_Pin|OE_Pin|R1_Pin 
                          |R2_Pin|G1_Pin|G2_Pin|B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
