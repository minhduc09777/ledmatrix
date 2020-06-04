#ifndef __P5_DONSAC
#define __P5_DONSAC
#include "stdlib.h"
#include "main.h"
#include "font.h"
// tv ho tro don sac 64x128

#define hangdonsac 64
#define cotdonsac  128  // vi moi byte 8 bit tc la 8 con led
#define mau 3
#define R	1
#define G 1
#define B 1

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
unsigned char bufferR[256];
unsigned char bufferio[4][512];

void giaimap10donsac(){
 for( int i=0;i<4;i++)
 {
	 
	 ///////////////////////////////16x64//////////////////////////////////////////////////////////////////
		/*	 for(int j=0;j<8;j++){
				 for(int k=0;k<8;k++){
						bufferio[i][j*8+k]=0;
						bufferio[i][j*8+k+64]=0;
						bufferio[i][j*8+k+128]=0;
						bufferio[i][j*8+k+192]=0;
						if(check_bit(bufferR[i*8+j],k)!=0x00) bufferio[i][j*8+k] =0x01;  //chon hang chon 16 cot roi lay tung bit 16 cot
					 
						if(check_bit(bufferR[(i+4)*8+j],k)!=0x00) bufferio[i][j*8+k+64] =0x01;// qutt 0 4 8 16     vay cong them 4 byte nhan 16
					 
						if(check_bit(bufferR[(i+8)*8+j],k)!=0x00) bufferio[i][j*8+k+128] =0x01;
				
						if(check_bit(bufferR[(i+12)*8+j],k)!=0x00) bufferio[i][j*8+k+192] =0x01;
				 }
			 } */
	 
	 ///////////////////////////////16x128//////////////////////////////////////////////////////////////////
	 
			 for(int j=0;j<16;j+=2){
				 for(int k=0;k<8;k++){
						bufferio[i][j*8+k]=0;
						bufferio[i][j*8+k+128]=0;
						bufferio[i][j*8+k+256]=0;
						bufferio[i][j*8+k+384]=0;
					 
					 	bufferio[i][j*8+k+8]=0;
						bufferio[i][j*8+k+128+8]=0;
						bufferio[i][j*8+k+256+8]=0;
						bufferio[i][j*8+k+384+8]=0;
					 
					 
						if(check_bit(bufferR[i*16+j],k)!=0x00) bufferio[i][j*8+k] =0x01;  //chon hang chon 16 cot roi lay tung bit 16 cot
					  if(check_bit(bufferR[i*16+j+1],k)!=0x00) bufferio[i][j*8+k+8] =0x01;
					 
						if(check_bit(bufferR[(i+4)*16+j],k)!=0x00) bufferio[i][j*8+k+128] =0x01;// qutt 0 4 8 16     vay cong them 4 byte nhan 16
					  if(check_bit(bufferR[(i+4)*16+j+1],k)!=0x00) bufferio[i][j*8+k+128+8] =0x01;
					 
					 
						if(check_bit(bufferR[(i+8)*16+j],k)!=0x00) bufferio[i][j*8+k+256] =0x01;
					  if(check_bit(bufferR[(i+8)*16+j+1],k)!=0x00) bufferio[i][j*8+k+256+8] =0x01;
					 
				
						if(check_bit(bufferR[(i+12)*16+j],k)!=0x00) bufferio[i][j*8+k+384] =0x01;
					 	if(check_bit(bufferR[(i+12)*16+j+1],k)!=0x00) bufferio[i][j*8+k+384+8] =0x01;
				 }
			 }
			
 }
 
}
const unsigned short mangtg[]={40,80,160,320,640,1280,2560,5120};

unsigned char hang=0,tgian=0;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	    if(htim->Instance ==TIM1)
			{
				GPIOA -> ODR &= (~(1<<6));
				 	for(int ___i=0;___i<512;___i++)
				 {
						GPIOB->ODR = (~(bufferio[3-hang][___i]))&0x01;
						GPIOB->ODR |= 0x80;
				 }
				 
				 TIM1->ARR = mangtg[tgian];
				 GPIOA -> ODR |= (1<<6);
				 
			 
				 GPIOA -> ODR = hang;
				 GPIOA -> ODR |= (1<<5);
				 
				 hang++;
				 if(hang==4){
					 hang=0;
					 tgian++;
					 if(tgian==8) tgian=0;
				 }
				 
			}
}


void MATRIX_pixel_color(unsigned char x, unsigned char y,unsigned char r,unsigned char g,unsigned char b){
	
	
	/*unsigned char tam=x;
	if(tam<4){
		x=(y/8)*4+x%4;
		y=y%8+((tam/4)*128);
	}
	else if(tam<8){
		x=(y/8)*4+x%4;
		y=y%8+((tam/8)*128)+8;
		
	}
	else if(tam<12){
		
		x=(y/8)*4+x%4;
		y=y%8+16+((tam/4)*128);
		
	}
	else if(tam<16){
		
		x=(y/8)*4+x%4;
		y=y%8+24+((tam/16)*128);
		
	}*/
	
	/*unsigned char tam=x;
	if(tam<4){
		x=y/16*3+x%4;
		y=y%8+y/8*32;
	}
	else if(tam<8){
		x=y/16*3+x%4;
		y=y%8+y/8*32+8;
	}
	else if(tam<12){
	  x=y/16*3+x%4;
		y=y%8+y/8*32+16;
		
	}
	else if(tam<16){
		
	  x=y/16*3+x%4;
		y=y%8+y/8*32+24;
		
	}
	*/
 unsigned char tam=y;
 unsigned char tamx=x;
		if(tam<32){
			x=y/32*8+x%4*2;
		
			y=y%8+y/8*32+tamx/4*8;
		}
		else if(tam<64){
			x=y/32*8+x%4*2;
			y=tam-32;
			
			y=y%8+y/8*32+tamx/4*8;
			
		}
		else if(tam<96){
			x=y/32*8+x%4*2;
			y=tam-64;
			
			y=y%8+y/8*32+tamx/4*8;
			
		}
		else if(tam<128){
			x=y/32*8+x%4*2;
			y=tam-96;
			y=y%8+y/8*32+tamx/4*8;
		}
	 if(r==1){
		 setbit(bufferR[x*8+(y/8)], (y%8));   //hang co 64 bit xac dinh hang bang cach dong nhan cho 8 + cot lay nguyen 8
	 }
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
				if(check_bit(myfont8x8[chu][7-i],j)){
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
			 if(check_bit(font11[chu][31-i+j/8],(15-j)%8)){
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
		 else y=y+10;
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
void matrix_p10donsac_clear_green(unsigned char x,unsigned char y){
	for(unsigned char i=0;i<x;i++){
		for(unsigned char j=0;j<y;i++){
			MATRIX_pixel_color(i,j,0,0,0);
		}
	}
}
void matrix_p10donsac_clear_all(){
	for(int i=0;i<256;i++){
				bufferR[i]=0x00;
	}
}

#endif













