#ifndef __P5_DONSAC
#define __P5_DONSAC
#include "stdlib.h"
#include "main.h"
#include "font.h"
// tv ho tro don sac 64x128

#define hangfullmau 64
#define cotfullmau  128  // vi moi byte 8 bit tc la 8 con led
#define R	255
#define G 255
#define B 255

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
uint16_t manght[32][128];
unsigned char mangxuatled[16][5][128];

void giaimap5fullmau(){
	unsigned char hang,ktbit,cot,pixel,pwm;
	for(hang=0;hang<16;hang++){
		 for(pwm=0,pixel=0x01;pwm<5;pixel<<=1,pwm++){
			 for(cot=0;cot<128;cot++){
					   mangxuatled[hang][pwm][cot]=0;
						 if((manght[hang][cot] & (pixel<<11))) {mangxuatled[hang][pwm][cot] |= 0x01;}
						 if((manght[hang+16][cot] & (pixel<<11))) {mangxuatled[hang][pwm][cot] |= 0x02;}
						 if((manght[hang][cot] & (pixel<<5))) {mangxuatled[hang][pwm][cot] |= 0x80;}
						 if((manght[hang+16][cot] & (pixel<<5))) {mangxuatled[hang][pwm][cot] |= 0x08;}
						 if((manght[hang][cot] & pixel)) {mangxuatled[hang][pwm][cot] |= 0x10;}
						 if((manght[hang+16][cot] & pixel)) {mangxuatled[hang][pwm][cot] |= 0x20;}
						 
					/*	 if(manght[hang][cot] & (0x20<<10)) {mangxuatled[hang][pwm][cot] |= 0x80;}
						 if((manght[hang+16][cot] & (0x20<<10))) {mangxuatled[hang][pwm][cot] |= 0x08;}*/
			 }
		 }
	}
}
const unsigned short mangtg[]={40,80,160,320,640,1280,2560,5120};

union tinhieudk
{
	unsigned char bytedk;
  struct 
	{
		int  hang:4;
		int  tgian :3;
		int  chot:1;			
	}thanhphan;
} bytedieukhien;

unsigned char tg,hang;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	    if(htim->Instance ==TIM1)
			{
				 for(int ___i=0;___i<128;___i++)
			   {
					  GPIOB->ODR = mangxuatled[bytedieukhien.thanhphan.hang][bytedieukhien.thanhphan.tgian%5][___i];
					 
					  GPIOB->ODR |= 0x0040;
					 
				 }
				   GPIOA -> ODR |= (1<<5);
					 TIM1->ARR = mangtg[bytedieukhien.thanhphan.tgian];
					 GPIOA -> ODR = bytedieukhien.thanhphan.hang;
					 bytedieukhien.bytedk++;
			}
}



void MATRIX_pixel_color(unsigned char x, unsigned char y,unsigned char r,unsigned char g,unsigned char b){
	
	if(x>=32 || y>127) return;
	if(y<0 || x<0) return;
	manght[x][y]=(((r & 0xF8) | (g >> 5))<<8)|(((g & 0x1C) << 3) | (b  >> 3));
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
					MATRIX_pixel_color(x+i,y+j,r,g,b);
				}
		}
	}
}
void MATRIX_putStr8x8(unsigned char x,unsigned char y,unsigned char a[],unsigned char r,unsigned char g,unsigned char b){
	unsigned char i=0;
	while(a[i]!=0x00){
		 MATRIX_putchar8x8(x,y,a[i],r,g,b);
		 i++;
		 if(a[i] == ' ') y=y+3;
		 else y=y+7;
	}
}
void MATRIX_putchar16x16(unsigned char x,unsigned char y,unsigned char chu,unsigned char r,unsigned char g,unsigned char b){
	 for(int i=0;i<32;i=i+2)
		 for(int j=0;j<16;j++)
		 {
			 if(check_bit(font11[chu][i+j/8],(15-j)%8)){
					if(x+i/2 >128 || x+i/2<0 ) return;
					if(y+j >255 || y+j<0)  return;
				   MATRIX_pixel_color(x+i/2,y+j,r,g,b);
			}		 
		}
}
void MATRIX_putStr16x16(signed int x,signed int y,unsigned char a[],unsigned char r,unsigned char g,unsigned char b){
	unsigned char i=0;
	while(a[i]!=0x00){
		 MATRIX_putchar16x16(x,y,a[i],r,g,b);
		 i++;
		 if(a[i] ==' ') y=y+3;
		 else y=y+13;
	}
}
void MATRIX_putchar16x32(unsigned char x,unsigned char y,unsigned char chu,unsigned char r,unsigned char g,unsigned char b){
	for(int i=0;i<64;i=i+2){
		for(int j=0;j<16;j++){
				if(check_bit(myfont16x32[chu][i+j/8],(15-j)%8)){
					MATRIX_pixel_color(x+i/2,y+j,r,g,b);
				}
		}
	}
}
void MATRIX_putStr16x32(unsigned char x,unsigned char y,unsigned char a[],unsigned char r,unsigned char g,unsigned char b){
	unsigned char i=0;
	while(a[i]!=0x00){
		 MATRIX_putchar16x32(x,y,a[i],r,g,b);
		 i++;
		 if(a[i] == ' ') y=y+10;
		 else y=y+15;
	}
}
void MATRIX_pixel_color565(unsigned char x, unsigned char y,uint16_t mau){
		if(y>63 || x>127) return;
	  if(y<0 || x<0) return;
	  manght[y][x]=mau;
}
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


void matrix_p5fullmau_clear_green(unsigned char x,unsigned char y){
	for(unsigned char i=0;i<x;i++){
		for(unsigned char j=0;j<y;i++){
			MATRIX_pixel_color(i,j,0,0,0);
		}
	}
}
void matrix_p5fullmau_clear_all(){
	for(unsigned char i=0;i<32;i++){
		for(unsigned char j=0;j<128;j++){
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

#endif













