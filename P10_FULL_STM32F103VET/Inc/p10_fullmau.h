#ifndef __P10_FULL
#define __P10_FULL
#include "stdlib.h"
#include "main.h"
#include "font.h"
#include "math.h"
// tv ho tro don sac 64x128

#define hangfullmau 64
#define cotfullmau  128  // vi moi byte 8 bit tc la 8 con led
#define R	255
#define G 255
#define B 255

#define matrix_x 31
#define matrix_y 63

#define setbit(sfr,bit)		(sfr|=(1<<bit))
#define clrbit(sfr,bit)		(sfr&=~(1<<bit))

unsigned char hu_rmap_x,hu_rmap_y;
void hu_rmap_mauchay(){
	
	if(hu_rmap_y==15) hu_rmap_y=0;
	
	hu_rmap_x++;
	if(hu_rmap_x==56)
	{		
		hu_rmap_x=0;
		hu_rmap_y++;
	}
	
}

char check_bit(unsigned char byte,unsigned char bit){
	if((byte&(1<<bit))==0x00){
		return 0;
	}
	else{
		return 1;
	}
}
unsigned char manght[3][32][64];
unsigned char mangxuatled[4][8][256];
void latsoto(char num,char y0,char x0,char offset);
extern unsigned char chay;

void giaimap10fullmau(){
	unsigned char hang,ktbit,pixel,pwm;
	unsigned char cot=0,cot1=0,cot2=0;
	for(hang=0;hang<4;hang++){
		 for(pwm=0,pixel=0x01;pwm<8;pixel<<=1,pwm++){
			 for(cot=0;cot<128;cot++){
				 if(cot<64){
					 
							mangxuatled[hang][pwm][cot%8+cot/8*16]=0;
				     mangxuatled[hang][pwm][cot%8+cot/8*16+8]=0;
						 if((manght[0][hang][cot] & (pixel))) {mangxuatled[hang][pwm][cot%8+cot/8*16] |= 0x01;}
						 if((manght[0][hang+4][cot] & (pixel))) {mangxuatled[hang][pwm][cot%8+cot/8*16+8] |= 0x01;}
						 if((manght[0][hang+8][cot] & (pixel))) {mangxuatled[hang][pwm][cot%8+cot/8*16] |= 0x02;}
						 if((manght[0][hang+12][cot] & (pixel))) {mangxuatled[hang][pwm][cot%8+cot/8*16+8] |= 0x02;}
							 
						 if((manght[1][hang][cot] & (pixel))) {mangxuatled[hang][pwm][cot%8+cot/8*16] |= 0x04;}
						 if((manght[1][hang+4][cot] & (pixel))) {mangxuatled[hang][pwm][cot%8+cot/8*16+8] |= 0x04;}
						 if((manght[1][hang+8][cot] & (pixel))) {mangxuatled[hang][pwm][cot%8+cot/8*16] |= 0x08;}
						 if((manght[1][hang+12][cot] & (pixel))) {mangxuatled[hang][pwm][cot%8+cot/8*16+8] |= 0x8;}
							 
						 if((manght[2][hang][cot] & (pixel))) {mangxuatled[hang][pwm][cot%8+cot/8*16] |= 0x10;}
						 if((manght[2][hang+4][cot] & (pixel))) {mangxuatled[hang][pwm][cot%8+cot/8*16+8] |= 0x10;}
						 if((manght[2][hang+8][cot] & (pixel))) {mangxuatled[hang][pwm][cot%8+cot/8*16] |= 0x20;}
						 if((manght[2][hang+12][cot] & (pixel))) {mangxuatled[hang][pwm][cot%8+cot/8*16+8] |= 0x20;}
					}
				 else{
					   mangxuatled[3-hang][pwm][cot%8+cot/8*16]=0;
				     mangxuatled[3-hang][pwm][cot%8+cot/8*16+8]=0;
						 if((manght[0][hang+16][127-cot] & (pixel))) {mangxuatled[3-hang][pwm][(cot%8+cot/8*16)+8] |= 0x02;}
						 if((manght[0][hang+4+16][127-cot] & (pixel))) {mangxuatled[3-hang][pwm][(cot%8+cot/8*16)] |= 0x02;}
						 if((manght[0][hang+8+16][127-cot] & (pixel))) {mangxuatled[3-hang][pwm][(cot%8+cot/8*16)+8] |= 0x01;}
						 if((manght[0][hang+12+16][127-cot] & (pixel))) {mangxuatled[3-hang][pwm][(cot%8+cot/8*16)] |= 0x01;}
							 
						 if((manght[1][hang+16][127-cot] & (pixel))) {mangxuatled[3-hang][pwm][(cot%8+cot/8*16)+8] |= 0x08;}
						 if((manght[1][hang+4+16][127-cot] & (pixel))) {mangxuatled[3-hang][pwm][(cot%8+cot/8*16)] |= 0x08;}
						 if((manght[1][hang+8+16][127-cot] & (pixel))) {mangxuatled[3-hang][pwm][(cot%8+cot/8*16)+8] |= 0x04;}
						 if((manght[1][hang+12+16][127-cot] & (pixel))) {mangxuatled[3-hang][pwm][(cot%8+cot/8*16)] |= 0x04;}
							 
						 if((manght[2][hang+16][127-cot] & (pixel))) {mangxuatled[3-hang][pwm][(cot%8+cot/8*16)+8] |= 0x20;}
						 if((manght[2][hang+4+16][127-cot] & (pixel))) {mangxuatled[3-hang][pwm][(cot%8+cot/8*16)] |= 0x20;}
						 if((manght[2][hang+8+16][127-cot] & (pixel))) {mangxuatled[3-hang][pwm][(cot%8+cot/8*16)+8] |= 0x10;}
						 if((manght[2][hang+12+16][127-cot] & (pixel))) {mangxuatled[3-hang][pwm][(cot%8+cot/8*16)] |= 0x10;}	
				 }

								
						  	 
							 
							 
							 
						//////////////explain below/////////////////////////	 
						/* if((manght[0][hang][cot] & (pixel))) {mangxuatled[hang][pwm][cot] |= 0x01;}	 
						 if((manght[0][hang][cot+8] & (pixel))) {mangxuatled[hang][pwm][cot+16] |= 0x01;}
						 if((manght[0][hang][cot+16] & (pixel))) {mangxuatled[hang][pwm][cot+32] |= 0x01;}
						 if((manght[0][hang][cot+24] & (pixel))) {mangxuatled[hang][pwm][cot+48] |= 0x01;}
						 
						 
						 if((manght[0][hang+4][cot] & (pixel))) {mangxuatled[hang][pwm][cot+8] |= 0x01;}
						 if((manght[0][hang+4][cot+8] & (pixel))) {mangxuatled[hang][pwm][cot+24] |= 0x01;}
						 if((manght[0][hang+4][cot+16] & (pixel))) {mangxuatled[hang][pwm][cot+40] |= 0x01;}
						 if((manght[0][hang+4][cot+24] & (pixel))) {mangxuatled[hang][pwm][cot+56] |= 0x01;}*/
						 
						 		 
						 
						 
			 }
		 }
	}
}
const unsigned short mangtg[]={40,80,160,320,640,1280,2560};

unsigned char hang=0,tgian=0;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	    if(htim->Instance ==TIM1)
			{
				 for(int ___i=0;___i<128*2;___i++)
			   {
					  GPIOD->ODR = mangxuatled[hang][tgian][___i];			 
					  GPIOD->ODR |= 0x0040;
				 }
				   GPIOA -> ODR |= (1<<4);
					 TIM1->ARR = mangtg[tgian];
					 GPIOA -> ODR = hang;
					 tgian++;
					 if(tgian==8){
						 tgian=0;
						 hang++;
						 if(hang==4) hang=0;
					 }
			}
}

void MATRIX_pixel_color(signed char x,signed char y,unsigned char r,unsigned char g,unsigned char b){

	
		if(x<0 || y<0) return;
	
	  if(x > matrix_x || y> matrix_y) return;
		manght[0][x][y]=r;
		manght[1][x][y]=g;
		manght[2][x][y]=b;
}

void MATRIX_line(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned char r,unsigned char g,unsigned char b,unsigned char hu)
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
				if(hu==0){
					MATRIX_pixel_color(x1, y1, r,g,b);
				}
				else{
					 manght[0][x1][y1]=rd_map_chaychu[0][hu_rmap_y][hu_rmap_x];
					 manght[1][x1][y1]=rd_map_chaychu[0][hu_rmap_y][hu_rmap_x];
					 manght[2][x1][y1]=rd_map_chaychu[0][hu_rmap_y][hu_rmap_x];
				}
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
    	  if(hu==0){
					MATRIX_pixel_color(x1, y1, r,g,b);
				}
				else{
					 manght[0][x1][y1]=rd_map_chaychu[0][hu_rmap_y][hu_rmap_x];
					 manght[1][x1][y1]=rd_map_chaychu[0][hu_rmap_y][hu_rmap_x];
					 manght[2][x1][y1]=rd_map_chaychu[0][hu_rmap_y][hu_rmap_x];
				}

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
    	  MATRIX_line(x-a, y+b, x+a, y+b,r1,g1,b1,0);
    	  MATRIX_line(x-a, y-b, x+a, y-b,r1,g1,b1,0);
    	  MATRIX_line(x-b, y+a, x+b, y+a,r1,g1,b1,0);
    	  MATRIX_line(x-b, y-a, x+b, y-a,r1,g1,b1,0);
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
	

void MATRIX_rect(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, int fill, unsigned char r,unsigned char g,unsigned char b,unsigned char hu)
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
					 if(hu==0){
							MATRIX_pixel_color(xmin, i, r,g,b);
					 }
         }
      }
   }
   else
   {
      MATRIX_line(x1, y1, x2, y1, r,g,b,hu);      // Draw the 4 sides
      MATRIX_line(x1, y2, x2, y2, r,g,b,hu);
      MATRIX_line(x1, y1, x1, y2, r,g,b,hu);
      MATRIX_line(x2, y1, x2, y2, r,g,b,hu);
   }
}
unsigned char MATRIX_putchar8x8(unsigned char x,unsigned char y,unsigned char chu,unsigned char size,unsigned char r,unsigned char g,unsigned char b){
	chu=chu-32;
	signed char max=0,dem=0,check=0;
	
	for(char i=0;i<8*size;i=i+size*1){
		dem=0;
		
				for(char j=0;j<8*size;j=j+size*1){
							if(check_bit(myfont8x8[chu][i/size],j/size)){
								MATRIX_pixel_color(x+i,y+j,r,g,b);
								
								dem=j+1*size;
							}
		     }
		check=1;		
		if(dem>max) max=dem;
	}
	return max;
}
void MATRIX_putStr8x8(unsigned char x,unsigned char y,unsigned char a[],unsigned char size,unsigned char r,unsigned char g,unsigned char b){
	unsigned char i=0;
	unsigned char leng=0;
	while(a[i]!=0x00){
		 leng=MATRIX_putchar8x8(x,y,a[i],size,r,g,b);
		 if(a[i] == ' ') y=y+3;
		 else y=y+leng+1;
		 i++;
	}
}

const unsigned char size_font16[] = //b?ng luu kích c? chi?u dài c?a font, ví d? tr? m s? dài hon ch? i
{
			0,12,12,12,12,12,12,12,12,12,13,12,12,12,12,12,12,
			12,11,10,10,10,10,10,10,11,11,11,11,10,7,7,3,
			7,8,0,9,10,10,4,6,6,7,0,4,7,4,7,9,7,9,
			9,9,9,9,8,9,9,4,4,10,10,10,8,16,12,11,
			11,11,10,10,12,12,7,10,12,10,15,13,12,10,12,12,
			8,11,11,13,17,13,12,11,9,9,9,9,9,7,8,9,
			7,9,7,7,9,9,3,5,10,7,15,10,8,8,8,7,
			6,7,9,9,12,9,9,7,7,5,6,7,7,7,7,12,
			12,12,12,12,12,12,12,12,13,12,13,13,13,13,13,13,
			11,11,11,11,11,12,12,12,12,12,12,13,13,13,13,13,
			8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
			8,9,7,7,7,7,7,7,7,7,7,7,7,3,4,3,
			5,3,9,9,9,8,8,8,8,8,8,8,8,9,9,9,
			9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
			9,9,9,7,15,14,16,16,16,17,17,17,17,
};

void MATRIX_putchar16x16(signed char x,signed char y,unsigned char chu,unsigned char r,unsigned char g,unsigned char b){
	 for(int i=0;i<32;i=i+2)
		 for(int j=0;j<16;j++)
		 {
			 if(check_bit(font16[chu][i+j/8],(15-j)%8)){
					if(x+i/2 >128 || x+i/2<0 ) return;
					if(y+j >255 || y+j<0)  return;
				   MATRIX_pixel_color(x+i/2,y+j,r,g,b);
			}		 
		}
}
int MATRIX_putStr16x16(signed char x,signed char y,unsigned char *a,unsigned char r,unsigned char g,unsigned char b){
	unsigned char i=0;
	unsigned utf8_addr;
	signed char len=0;
	while(*a!=0x00){
	   utf8_addr=UTF8_GetAddr(a,&i);
		 MATRIX_putchar16x16(x,y,utf8_addr,r,g,b);
		 a+=i;
		 y=y+size_font16[utf8_addr];
		 len=len+size_font16[utf8_addr];
	}
	return len;
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
		 if(a[i] == ' ') y=y+5;
		 else y=y+15;
	}
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
			drawPixelRGB565(yy+y,xx+x,a[counter]);
      counter++;
    }
  }
}




void matrix_p10fullmau_clear_all(){
	for(unsigned char i=0;i<32;i++){
		for(unsigned char j=0;j<64;j++){
				manght[0][i][j]=0x00;
				manght[1][i][j]=0x00;
				manght[2][i][j]=0x00;
			
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

unsigned char hang_led,p10_x,p10_y;
char hieuung=0;
#define sonho 0
#define soto  1
void P10_chonvitri(char y,char x)
{
	 p10_x=x;
	 p10_y=y;
}
void P10_sendnumBIG(char num)
{
		for(int mau=0;mau<3;mau++)
			 for(int y=0;y<15;y++)
	       {
					 if(y+p10_y>15)break;
					 for(int x=0;x<10;x++)
							{
								if(x+p10_x>63)break;
							  manght[mau][y+p10_y][x+p10_x]=number_fx[hieuung][num][mau][y][x];				   
					    }
				 }
		p10_x+=11;
}
void P10_sendnumSmall(char num)
{
		for(int mau=0;mau<3;mau++)
			 for(int y=0;y<8;y++)
					 for(int x=0;x<5;x++)
							 manght[mau][y+p10_y][x+p10_x]=number_nho_fx[hieuung][num][mau][y][x];
		p10_x+=6;
}
void P10_DislayNumBIG(char y, char x, char num){
	unsigned char tram,chuc,dv;
	tram=num/100%10;
	chuc=num/10%10;
	dv=num%10;
	if(tram!=0){
		P10_chonvitri(y,x);
		P10_sendnumBIG(tram);
		P10_chonvitri(y,x+11);
		P10_sendnumBIG(chuc);
		P10_chonvitri(y,x+22);
		P10_sendnumBIG(dv);
	}
	else if(chuc!=0){
		P10_chonvitri(y,x);
		P10_sendnumBIG(chuc);
		P10_chonvitri(y,x+11);
		P10_sendnumBIG(dv);	
	}
	else{
		P10_chonvitri(y,x);
		P10_sendnumBIG(dv);	
	}
}
void P10_DislayNumSMALL(char y, char x, char num){
	unsigned char tram,chuc,dv;
	tram=num/100%10;
	chuc=num/10%10;
	dv=num%10;
	if(tram!=0){
		P10_chonvitri(y,x);
		P10_sendnumSmall(tram);
		P10_chonvitri(y,x+5);
		P10_sendnumSmall(chuc);
		P10_chonvitri(y,x+10);
		P10_sendnumSmall(dv);
	}
	else if(chuc!=0){
		P10_chonvitri(y,x);
		P10_sendnumSmall(chuc);
		P10_chonvitri(y,x+5);
		P10_sendnumSmall(dv);	
	}
	else{
		P10_chonvitri(y,x);
		P10_sendnumSmall(dv);	
	}
}

unsigned char mangdongho[3][17][64];
unsigned char P10_x_clock=0,P10_y_clock=0;
void setVitriClock(unsigned char y,unsigned char x){
	P10_x_clock=x;
	P10_y_clock=y;
}
void giaimadongho(){
	for(unsigned char y0=0;y0<17;y0++){
		for(unsigned char x0=0;x0<64;x0++){
			if(P10_x_clock+x0<0||P10_y_clock+y0<0) return;
			if(P10_x_clock+x0>matrix_y||P10_y_clock+y0>matrix_x) return;
			
			manght[0][P10_y_clock+y0][P10_x_clock+x0]=mangdongho[0][y0][x0];
			manght[1][P10_y_clock+y0][P10_x_clock+x0]=mangdongho[1][y0][x0];
			manght[2][P10_y_clock+y0][P10_x_clock+x0]=mangdongho[2][y0][x0];
		}
	}
}
// hien thi dau cham to
void P10_sendRec(unsigned char y_mau,unsigned char x_mau,unsigned char hu)
{
		P10_chonvitri(y_mau,x_mau);
		for(int mau=0;mau<3;mau++)
			 for(int y=0;y<4;y++)
					 for(int x=0;x<4;x++)
							 mangdongho[mau][y+p10_y][x+p10_x]=recfill_fx[hu][mau][y][x];
	giaimadongho();
}
char check_num[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
void latsoto(char num,char y0,char x0,char offset)  //lat xuong so to
{
	char chuc,dv,check=0,dai;
	dv = num%10;
	chuc = num/10;
	dai = x0 + 21;
	if(check_num[offset]!=num){
		for(signed char down=14;down>=0;down--)
		{
		 for(char color=0;color<3;color++)
			 for(char y=y0+14;y>y0;y--)
				 for(char x=x0;x<dai;x++) 
					 mangdongho[color][y][x]=mangdongho[color][y-1][x];
			 for(char color=0;color<3;color++)
				 {
					for(char x=x0;x<x0+10;x++) 
					 mangdongho[color][y0][x]= number_fx[hieuung][chuc][color][down][x-x0];
					for(char x=x0+11;x<dai;x++) 
					 mangdongho[color][y0][x]= number_fx[hieuung][dv][color][down][x-(x0+11)];
				 }
		 giaimadongho();
	   giaimap10fullmau();
	  // lat so tiep theo xuong*/
	  }
		check_num[offset]=num;
	}
	else if(check_num[offset]==num){
		for(signed char down=14;down>=0;down--)
		{
		 for(char color=0;color<3;color++)
			 {
				for(char x=x0;x<x0+10;x++) 
				 mangdongho[color][y0+down][x]= number_fx[hieuung][chuc][color][down][x-x0];
				for(char x=x0+11;x<dai;x++) 
				 mangdongho[color][y0+down][x]= number_fx[hieuung][dv][color][down][x-(x0+11)];
			 }
	  }
	  giaimadongho();
	}
}

char check_numn[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
void latsonho(char num,signed char y0,char x0,char offset)  //lat xuong so nho
{
	char chuc,dv,check=0,dai;
	dv = num%10;
	chuc = num/10;
	
	dai = x0 + 11;
	if(check_numn[offset]!=num){
			for(signed char down=7;down>=0;down--)
			{
			 for(char color=0;color<3;color++)
				 for(char y=y0+7;y>y0;y--)
					 for(char x=x0;x<dai;x++) 
						 mangdongho[color][y][x]=mangdongho[color][y-1][x];

				 for(char color=0;color<3;color++)
					 {
						for(char x=x0;x<x0+5;x++) 
						 mangdongho[color][y0][x]= number_nho_fx[hieuung][chuc][color][down][x-x0];
						for(char x=x0+6;x<dai;x++) 
						 mangdongho[color][y0][x]= number_nho_fx[hieuung][dv][color][down][x-(x0+6)];
					 }
					 giaimadongho();
	         giaimap10fullmau();
			}
			check_numn[offset]=num;
			
	}
  else if(check_numn[offset]==num){
		for(signed char down=7;down>=0;down--)
		{
				for(char color=0;color<3;color++)
				 {
					   for(char x=x0;x<x0+5;x++) 
						 mangdongho[color][y0+down][x]= number_nho_fx[hieuung][chuc][color][down][x-x0];
						 for(char x=x0+6;x<dai;x++) 
						 mangdongho[color][y0+down][x]= number_nho_fx[hieuung][dv][color][down][x-(x0+6)];
				 }
		}
		    giaimadongho();
				giaimap10fullmau();
	}  // lat so tiep theo xuong
}
//dung de xoa man hinh
void DRAW_FillRec(char y,char x,char w,char h,unsigned char r,unsigned char g,unsigned char b)
{
	 int _y,_x;
	 w+=x;
	 h+=y;
	 for(_y=y;_y<h;_y++)
		 for(_x=x;_x<w;_x++)
			  mangdongho[0][_y][_x]=r;
	 for(_y=y;_y<h;_y++)
		 for(_x=x;_x<w;_x++)
			  mangdongho[1][_y][_x]=g;
	 for(_y=y;_y<h;_y++)
		 for(_x=x;_x<w;_x++)
			  mangdongho[2][_y][_x]=b;
	
	  giaimadongho();
}

unsigned char hour,minute,second,giay_tam,day,month,year;
unsigned char ngay_al,thang_al;
RTC_TimeTypeDef sTime;
RTC_DateTypeDef sDate;
extern RTC_HandleTypeDef hrtc;

void initial_clock(){
	HAL_RTC_GetTime(&hrtc,&sTime,RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc,&sDate,RTC_FORMAT_BIN);
	hour=sTime.Hours;
	minute=sTime.Minutes;
	second=sTime.Seconds;
	day=sDate.Date;
	month=sDate.Month;
	year=sDate.Year;
}
void DongHoBig(unsigned char y,unsigned char x){
	
	setVitriClock(y,x);
	signed char x0,y0;
	x0=x;
	y0=y;
	x=0;
	y=0;
	latsoto(hour,y+1,x+1,0);
	latsoto(minute,y+1,x+30,1);
	latsonho(second,y+8,x+52,0);
//	DRAW_FillRec(y+13,x+52,2,2,255,2,0);
	if(second != giay_tam){
		for(char i=0;i<3;i++){
			P10_sendRec(y+2+i,x+24,1);
			P10_sendRec(y+11-i,x+24,1);
			giaimap10fullmau();
			DRAW_FillRec(y+2+i,x+24,4,4,0,0,0);
			DRAW_FillRec(y+11-i,x+24,4,4,0,0,0);
		}
		for(char i=0;i<3;i++){
			P10_sendRec(y+4-i,x+24,1);
			P10_sendRec(y+9+i,x+24,1);
			giaimap10fullmau();
			DRAW_FillRec(y+4-i,x+24,4,4,0,0,0);
			DRAW_FillRec(y+9+i,x+24,4,4,0,0,0);
		}
		P10_sendRec(y+2,x+24,1);
		P10_sendRec(y+11,x+24,1);
		giay_tam=second;	
	}
	
	for(char x1=0;x1<64;x1++){
		mangdongho[0][0][x1]=0xff;
		mangdongho[0][16][x1]=0xff;
	}
	for(char y1=0;y1<16;y1++){
		mangdongho[0][y1][0]=0xff;
		mangdongho[0][y1][63]=0xff;
		giaimadongho();
	}
	giaimadongho();
}

struct MONTH_INFO{
	unsigned int N_AL_DT_DL		:5;
	unsigned int T_AL_DT_DL		:4;
	unsigned int SN_CT_AL		:1;
	unsigned int TN_B_THT		:1;
	unsigned int SN_CT_DL		:2;
};

union LUNAR_RECORD
{
 	unsigned int Word; 
	struct MONTH_INFO Info;
};
void am_lich(unsigned char SolarDay, unsigned char SolarMonth, unsigned int SolarYear)
{	
	unsigned char N_AL_DT_DL; 
	unsigned char T_AL_DT_DL; 
	unsigned char SN_CT_AL;
	unsigned char TN_B_THT;
	unsigned char N_AL_DT_DL_TT;
	unsigned char T_AL_DT_DL_TT;

	union LUNAR_RECORD lr;
        SolarYear+=2000;
        
	lr.Word = LUNAR_CALENDAR_LOOKUP_TABLE[(SolarYear-BEGINNING_YEAR)*12+SolarMonth -1]; 
	N_AL_DT_DL = lr.Info.N_AL_DT_DL;
	T_AL_DT_DL = lr.Info.T_AL_DT_DL;
	SN_CT_AL = lr.Info.SN_CT_AL + 29;
	TN_B_THT =  lr.Info.TN_B_THT;

	lr.Word = LUNAR_CALENDAR_LOOKUP_TABLE[(SolarYear-BEGINNING_YEAR)*12+SolarMonth];
	N_AL_DT_DL_TT = lr.Info.N_AL_DT_DL;
	T_AL_DT_DL_TT = lr.Info.T_AL_DT_DL;

	// Tinh ngay & thang
	if(N_AL_DT_DL == SN_CT_AL && N_AL_DT_DL_TT == 2)
	{
	 	if(SolarDay==1)
		{
		 	ngay_al = N_AL_DT_DL;
			thang_al = T_AL_DT_DL;
		}
		else if(SolarDay==31)
		{
		 	ngay_al = 1;
			thang_al = T_AL_DT_DL_TT;
		}
		else
		{
		 	ngay_al = SolarDay - 1;
			if(TN_B_THT)
			{
				thang_al = T_AL_DT_DL;
			}
			else
			{
			 	thang_al = T_AL_DT_DL==12?1:(T_AL_DT_DL + 1);
			} 
		}
	}
	else
	{
	 	ngay_al = SolarDay + N_AL_DT_DL - 1;
		if(ngay_al<= SN_CT_AL)
		{
		 	thang_al = T_AL_DT_DL;
		}
		else
		{
		 	ngay_al -= SN_CT_AL;

			thang_al = T_AL_DT_DL + 1 - TN_B_THT;
			if(thang_al == 13) thang_al = 1;
		}
	}
}

void amlich_ht(unsigned char y,unsigned char x){
		hu_rmap_mauchay();
	am_lich(day,month,year);
	MATRIX_putchar16x16(y,x,(ngay_al/10+0x30),rd_map_chaychu[0][hu_rmap_y][hu_rmap_x],rd_map_chaychu[1][hu_rmap_y][hu_rmap_x],rd_map_chaychu[2][hu_rmap_y][hu_rmap_x]);
	MATRIX_putchar16x16(y,x+6,(ngay_al%10+0x30),rd_map_chaychu[0][hu_rmap_y][hu_rmap_x+1],rd_map_chaychu[1][hu_rmap_y][hu_rmap_x+1],rd_map_chaychu[2][hu_rmap_y][hu_rmap_x+1]);
	
	MATRIX_putchar16x16(y,x+12,'-',rd_map_chaychu[0][hu_rmap_y][hu_rmap_x+2],rd_map_chaychu[1][hu_rmap_y][hu_rmap_x+2],rd_map_chaychu[2][hu_rmap_y][hu_rmap_x+2]);
	
	MATRIX_putchar16x16(y,x+19,(thang_al/10+0x30),rd_map_chaychu[0][hu_rmap_y][hu_rmap_x+3],rd_map_chaychu[1][hu_rmap_y][hu_rmap_x+3],rd_map_chaychu[2][hu_rmap_y][hu_rmap_x+3]);
	MATRIX_putchar16x16(y,x+28,(thang_al%10+0x30),rd_map_chaychu[0][hu_rmap_y][hu_rmap_x+4],rd_map_chaychu[1][hu_rmap_y][hu_rmap_x+4],rd_map_chaychu[2][hu_rmap_y][hu_rmap_x+4]);
	MATRIX_putchar16x16(y,x+37,12,rd_map_chaychu[0][hu_rmap_y][hu_rmap_x+5],rd_map_chaychu[1][hu_rmap_y][hu_rmap_x+5],rd_map_chaychu[2][hu_rmap_y][hu_rmap_x+5]);
	MATRIX_putchar16x16(y,x+45,'m',rd_map_chaychu[0][hu_rmap_y][hu_rmap_x+6],rd_map_chaychu[1][hu_rmap_y][hu_rmap_x+6],rd_map_chaychu[2][hu_rmap_y][hu_rmap_x+6]);
	
	
}

void MATRIX_circle1(signed int x, signed int y, signed int radius,  unsigned char r1,unsigned char g1,unsigned char b1)
{
	 if(radius <0) return;
	
	 int ran=255;
   signed int  a, b, P;
   a = 0;
   b = radius;
   P = 1 - radius;
   do
   {
	

    	  MATRIX_pixel_color(a+x, b+y, r1,g1,b1);
    	  MATRIX_pixel_color(b+x, a+y, r1,g1,b1);
    	  MATRIX_pixel_color(x-a, b+y, r1,g1,b1);
    	  MATRIX_pixel_color(x-b, a+y, r1,g1,b1);
    	  MATRIX_pixel_color(b+x, y-a, r1,g1,b1);
    	  MATRIX_pixel_color(a+x, y-b, r1,g1,b1);
    	  MATRIX_pixel_color(x-a, y-b, r1,g1,b1);
    	  MATRIX_pixel_color(x-b, y-a, r1,g1,b1);
      if(P < 0){
				 a+=3;
         P += 3 + 2 * a;
			}
      else{
				 a+=2;
				 b-=2;
         P += 5 + 2 * (a++ - b--);
			}
    } while(a <= b);
}
///////////////////////////////////////////////// didital SEGMENT ///////////////////////////////////////////////

unsigned char segHeight = 6;
unsigned char segWidth = 6;
void setupSeg(unsigned char height,unsigned char weight){
	segHeight = height;
	segWidth  = weight;
}
void drawSeg(unsigned char seg,unsigned char x,unsigned char y,unsigned char r,unsigned char g,unsigned char b)
{
  switch (seg) {
    case 'd': MATRIX_line(segHeight * 2 + 2+x,1+y, segHeight * 2 + 2+x, segWidth+y, r,g,b,0); break;
    case 'c': MATRIX_line(segHeight * 2 + 1+x,segWidth + 1+y, segHeight + 2+x,  segWidth + 1+y, r,g,b,0); break;
    case 'g': MATRIX_line(segWidth + 1+x, 1+y, segWidth + 1+x, segHeight+y,r,g,b,0); break;
    case 'f': MATRIX_line(1+x, 0+y, segWidth+x, 0+y,  r,g,b,0); break;
    case 'a': MATRIX_line(0+x, 1+y, 0+x, segHeight+y,  r,g,b,0); break;
    case 'e': MATRIX_line(segHeight * 2 + 1+x, 0+y, segHeight + 2+x,0+y,  r,g,b,0); break;
    case 'b': MATRIX_line(1+x, segHeight + 1+y, segWidth+x, segHeight + 1+y,  r,g,b,0); break;
  }
}
unsigned char digitBits[] = {
  0xfc, // 0 ABCDEF--
  0x60, // 1 -BC-----
  0xda, // 2 AB-DE-G-
  0xf2, // 3 ABCD--G-
  0x66, // 4 -BC--FG-
  0xb6, // 5 A-CD-FG-
  0xbe, // 6 A-CDEFG-
  0xe0, // 7 ABC-----
  0xfe, // 8 ABCDEFG-
  0xf6, // 9 ABCD_FG-
};

void drawDigital(unsigned char value,unsigned char x,unsigned char y,unsigned char r,unsigned char g,unsigned char b){
	for(char i=1;i<=7;i++){
		if(check_bit(digitBits[value],i)){	
			if(i==7) drawSeg('a',x,y,r,g,b);
			if(i==6) drawSeg('b',x,y,r,g,b);
			if(i==5) drawSeg('c',x,y,r,g,b);
			if(i==4) drawSeg('d',x,y,r,g,b);
			if(i==3) drawSeg('e',x,y,r,g,b);
			if(i==2) drawSeg('f',x,y,r,g,b);
			if(i==1) drawSeg('g',x,y,r,g,b);
		}			
	}
}
unsigned char _value[6]={-1},_vt=0;
void Morph1(unsigned char x,unsigned char y,unsigned char r,unsigned char g,unsigned char b) {
 
	drawDigital(0,x,y,r,g,b);
  for (char i = 0; i <= segWidth; i++)
  {
		drawSeg('e',0+x,i+y,0,0,0);
		drawSeg('e',0+x,i+1+y,r,g,b);
		drawSeg('f',0+x,i+y,0,0,0);
		drawSeg('f',0+x,i+1+y,r,g,b);
		MATRIX_pixel_color(0+x,i+y,0,0,0);
		MATRIX_pixel_color(segHeight * 2 + 2+x,i+y,0,0,0);
		giaimap10fullmau();
	}
}
void Morph2(unsigned char x,unsigned char y,unsigned char r,unsigned char g,unsigned char b) {
  // TWO
  for (unsigned char i = 0; i <= segWidth; i++)
  {
	 drawSeg('b',0+x,0+y,r,g,b);
   if (i < segWidth) {
      MATRIX_pixel_color( segHeight * 2 + 2+x,segWidth - i+y, r,g,b);
      MATRIX_pixel_color( segHeight + 1+x,segWidth - i+y, r,g,b);
      MATRIX_pixel_color( 0+x,segWidth - i+y, r,g,b);
    }
	 
   // MATRIX_line(segHeight * 2 + 1,segWidth + 1 - i, segHeight + 2,  segWidth + 1 - i, 0,0,0,0);
   // MATRIX_line(segHeight * 2 + 1,segWidth  - i, segHeight + 2,  segWidth  - i, r,g,b,0);
		drawSeg('c',0+x,-i+y,0,0,0);
		drawSeg('c',0+x,-i-1+y,r,g,b);
		giaimap10fullmau();
		if(i==segWidth)drawDigital(2,0+x,0+y,r,g,b);
  }
}

void Morph3(unsigned char x,unsigned char y,unsigned char r,unsigned char g,unsigned char b) {
  // THREE
	drawDigital(2,0+x,0+y,r,g,b);
  for (char i = 0; i <= segWidth; i++)
  {
		if(i<segWidth){
			drawSeg('e',0+x,i+y,0,0,0); 
			drawSeg('e',0+x,i+1+y,r,g,b);
		}
		else{
			drawSeg('e',0+x,i+y,0,0,0); 
			drawDigital(3,x,y,r,g,b);
		}
		giaimap10fullmau();
  }
}
void Morph4(unsigned char x,unsigned char y,unsigned char r,unsigned char g,unsigned char b) {
  // FOUR
	drawDigital(3,x,y,r,g,b);
  for (char i = 0; i <= segWidth; i++)
  {
		if(i<segWidth){
			MATRIX_pixel_color(0+x, segHeight-i+y, 0,0,0); // Erase A
			drawSeg('b',0+x,-i+y,0,0,0); // Draw as F
			drawSeg('b',0+x,-i-1+y,r,g,b);
			MATRIX_pixel_color(segHeight * 2 + 2+x,i+y, 0,0,0); // Erase D
		
			MATRIX_pixel_color(1+x+i, segHeight + 1+y, r,g,b);
		}
		else{
			  MATRIX_pixel_color(0+x, segHeight-i+y, 0,0,0);
				MATRIX_pixel_color(segHeight * 2 + 2+x,i+y, 0,0,0);
				drawSeg('b',0+x,-i+y,0,0,0);
				drawDigital(4,x,y,r,g,b);
		}
		giaimap10fullmau();

  }
}
void Morph5(unsigned char x,unsigned char y,unsigned char r,unsigned char g,unsigned char b) {
  // FIVE
	drawDigital(4,x,y,r,g,b);
	drawSeg('b',x,y,0,0,0);
  for (char i = 1; i < segWidth-1; i++)
  {
		
    MATRIX_pixel_color(0+x, 1+i+y, r,g,b); // Draw as A
    MATRIX_pixel_color(segHeight * 2 + 2+x,i+y, r,g,b); // Draw D
    giaimap10fullmau();
  }
}
void  Morph6(unsigned char x,unsigned char y,unsigned char r,unsigned char g,unsigned char b){
	
	drawDigital(5,x,y,r,g,b);
	for (int i = 0; i <= segWidth; i++)
  {
		if(i<segWidth){
			drawSeg('c',0+x,-i-1+y,0,0,0); 
			drawSeg('c',0+x,-i-2+y,r,g,b);
		}
		else{
			drawSeg('c',0+x,-i-1+y,0,0,0); 
			drawDigital(6,x,y,r,g,b);
		}
		giaimap10fullmau();
	}
}
void  Morph7(unsigned char x,unsigned char y,unsigned char r,unsigned char g,unsigned char b){
	
	drawDigital(6,x,y,r,g,b);
	for (char i = 0; i <= segWidth; i++)
  {
		
		MATRIX_pixel_color(segWidth + 1+x, i+1+y, 0,0,0);
		MATRIX_pixel_color(segHeight * 2 + 2+x,1+i+y,0,0,0);
		if(i<segWidth){
			drawSeg('f',0+x,i+y,0,0,0); 
			drawSeg('f',0+x,i+1+y,r,g,b);
			drawSeg('e',0+x,i+y,0,0,0); 
			drawSeg('e',0+x,i+1+y,r,g,b);
		}
		else{
			drawSeg('f',0+x,i+y,0,0,0);
		  drawSeg('e',0+x,i+y,0,0,0); 
			drawDigital(7,x,y,r,g,b);
		}
		giaimap10fullmau();
	}
}
void  Morph8(unsigned char x,unsigned char y,unsigned char r,unsigned char g,unsigned char b){
	
	drawDigital(7,x,y,r,g,b);
	for (char i = 0; i <= segWidth; i++)
  {
		
		if(i<segWidth){
			drawSeg('b',0+x,-i-1+y,0,0,0); 
			drawSeg('b',0+x,-i-2+y,r,g,b);
			drawSeg('c',0+x,-i-1+y,0,0,0); 
			drawSeg('c',0+x,-i-2+y,r,g,b);
			MATRIX_pixel_color(segWidth + 1+x, segHeight-i+y, r,g,b);
	  	MATRIX_pixel_color( segHeight * 2 + 2+x, segWidth-i+y,r,g,b);
		}
		else{
			drawDigital(8,x,y,r,g,b);
		}
		giaimap10fullmau();
	}
}
void  Morph9(unsigned char x,unsigned char y,unsigned char r,unsigned char g,unsigned char b){
	
	drawDigital(8,x,y,r,g,b);
	for (char i = 0; i <= segWidth; i++)
  {
		if(i<segWidth){
			drawSeg('e',0+x,i+y,0,0,0); 
			drawSeg('e',0+x,i+1+y,r,g,b);
		}
		else{
			drawSeg('e',0+x,i+y,0,0,0); 
			drawDigital(9,x,y,r,g,b);
		}
		giaimap10fullmau();
	}
}
void  Morph0(unsigned char x,unsigned char y,unsigned char r,unsigned char g,unsigned char b){
	
	if(_value[_vt]==9) drawDigital(9,x,y,r,g,b);
	if(_value[_vt]==5) drawDigital(5,x,y,r,g,b);
	if(_value[_vt]==2) drawDigital(2,x,y,r,g,b);
	for (char i = 0; i <= segWidth; i++)
  {
		if(_value[_vt]==9){
					if(i<segWidth){
						MATRIX_pixel_color(segWidth + 1+x, segHeight-i+y, 0,0,0);
						drawSeg('c',0+x,-i-1+y,0,0,0); 
						drawSeg('c',0+x,-i-2+y,r,g,b);
					}
					else{
						drawDigital(0,x,y,r,g,b);
					}
		 }
		if(_value[_vt]==5){
				MATRIX_pixel_color(segWidth + 1+x, segHeight-i+y, 0,0,0);
			   if(i<segWidth){
						drawSeg('f',0+x,i+y,0,0,0); 
						drawSeg('f',0+x,i+1+y,r,g,b);
					 	drawSeg('c',0+x,-i+1+y,0,0,0); 
						drawSeg('c',0+x,-i+y,r,g,b);
					}
					else{
						drawDigital(0,x,y,r,g,b);
					}
		}
		if(_value[_vt]==2){
				MATRIX_pixel_color(segWidth + 1+x, segHeight-i+y, 0,0,0);
			   if(i<segWidth){
						drawSeg('b',0+x,-i+1+y,0,0,0); 
						drawSeg('b',0+x,-i+y,r,g,b);
					 	drawSeg('e',0+x,i+y,0,0,0); 
						drawSeg('e',0+x,i+1+y,r,g,b);
					}
					else{
						drawDigital(0,x,y,r,g,b);
					}
		}
								
		giaimap10fullmau();
	}
}


void Morph(unsigned char value,unsigned char x,unsigned char y,unsigned char r,unsigned char g,unsigned char b,unsigned char vt){
	
	_vt=vt;
	if(_value[_vt] != value){
	
			switch (value) {
				case 0: Morph0(x,y,r,g,b); break;
				case 1: Morph1(x,y,r,g,b); break;
				case 2: Morph2(x,y,r,g,b); break;
				case 3: Morph3(x,y,r,g,b); break;
				case 4: Morph4(x,y,r,g,b); break;
				case 5: Morph5(x,y,r,g,b); break;
				case 6: Morph6(x,y,r,g,b); break;
				case 7: Morph7(x,y,r,g,b); break;
				case 8: Morph8(x,y,r,g,b); break;
				case 9: Morph9(x,y,r,g,b); break;
			}
	}
	else{
		drawDigital(value,x,y,r,g,b);
	}
	_value[_vt] = value;
}
void DongHo7Seg(unsigned char y,unsigned char x){
	
	setupSeg(6,6);
	
	
	drawDigital(hour/10%10,x,y,255,255,255);
	drawDigital(hour%10,x,y+9,255,255,255);
	
	MATRIX_rect(x+3,y+18,x+5,y+20,1,255,255,255,0);
	MATRIX_rect(x+10,y+18,x+12,y+20,1,255,255,255,0);

	Morph(minute/10%10,x,y+22,255,255,255,2);
	Morph(minute%10,x,y+31,255,255,255,3);
	
	MATRIX_rect(x+3,y+41,x+5,y+43,1,255,255,255,0);
	MATRIX_rect(x+10,y+41,x+12,y+43,1,255,255,255,0);
	
	Morph(second/10%10,x,y+45,255,255,255,4);
	Morph(second%10,x,y+54,255,255,255,5);
	
	//MATRIX_rect(x-1,y,x+15,y+63,0,255,0,0,0);
	
	
}

const signed char  sinetab[256] = {
     0,   2,   5,   8,  11,  15,  18,  21,
    24,  27,  30,  33,  36,  39,  42,  45,
    48,  51,  54,  56,  59,  62,  65,  67,
    70,  72,  75,  77,  80,  82,  85,  87,
    89,  91,  93,  96,  98, 100, 101, 103,
   105, 107, 108, 110, 111, 113, 114, 116,
   117, 118, 119, 120, 121, 122, 123, 123,
   124, 125, 125, 126, 126, 126, 126, 126,
   127, 126, 126, 126, 126, 126, 125, 125,
   124, 123, 123, 122, 121, 120, 119, 118,
   117, 116, 114, 113, 111, 110, 108, 107,
   105, 103, 101, 100,  98,  96,  93,  91,
    89,  87,  85,  82,  80,  77,  75,  72,
    70,  67,  65,  62,  59,  56,  54,  51,
    48,  45,  42,  39,  36,  33,  30,  27,
    24,  21,  18,  15,  11,   8,   5,   2,
     0,  -3,  -6,  -9, -12, -16, -19, -22,
   -25, -28, -31, -34, -37, -40, -43, -46,
   -49, -52, -55, -57, -60, -63, -66, -68,
   -71, -73, -76, -78, -81, -83, -86, -88,
   -90, -92, -94, -97, -99,-101,-102,-104,
  -106,-108,-109,-111,-112,-114,-115,-117,
  -118,-119,-120,-121,-122,-123,-124,-124,
  -125,-126,-126,-127,-127,-127,-127,-127,
  -128,-127,-127,-127,-127,-127,-126,-126,
  -125,-124,-124,-123,-122,-121,-120,-119,
  -118,-117,-115,-114,-112,-111,-109,-108,
  -106,-104,-102,-101, -99, -97, -94, -92,
   -90, -88, -86, -83, -81, -78, -76, -73,
   -71, -68, -66, -63, -60, -57, -55, -52,
   -49, -46, -43, -40, -37, -34, -31, -28,
   -25, -22, -19, -16, -12,  -9,  -6,  -3
};
/*
const float radius1 =65.2, radius2 =92.0, radius3 =163.2, radius4 =176.8,
            centerx1=64.4, centerx2=46.4, centerx3= 93.6, centerx4= 16.4,
            centery1=34.8, centery2=26.0, centery3= 56.0, centery4=-11.6;
float       angle1  = 0.0, angle2  = 0.0, angle3  =  0.0, angle4  =  0.0;
long        hueShift= 0;

void plashma(unsigned char vtx,unsigned char vty,unsigned char w,unsigned char h){
	
	int           x1, x2, x3, x4, y1, y2, y3, y4, sx1, sx2, sx3, sx4;
  unsigned char x, y;
  long          value;

  sx1 = (int)(cos(angle1) * radius1 + centerx1);
  sx2 = (int)(cos(angle2) * radius2 + centerx2);
  sx3 = (int)(cos(angle3) * radius3 + centerx3);
  sx4 = (int)(cos(angle4) * radius4 + centerx4);
  y1  = (int)(sin(angle1) * radius1 + centery1);
  y2  = (int)(sin(angle2) * radius2 + centery2);
  y3  = (int)(sin(angle3) * radius3 + centery3);
  y4  = (int)(sin(angle4) * radius4 + centery4);
	
	 for(y=0; y<h; y++) {
    x1 = sx1; x2 = sx2; x3 = sx3; x4 = sx4;
    for(x=0; x<w; x++) {
      value = hueShift
        + (int8_t) ((sinetab [ (uint8_t)((x1 * x1 + y1 * y1) >> 4)]))
        + (int8_t) ((sinetab [ (uint8_t)((x2 * x2 + y2 * y2) >> 4)]))
        + (int8_t) ((sinetab [ (uint8_t)((x3 * x3 + y3 * y3) >> 5)]))
        + (int8_t) ((sinetab [ (uint8_t)((x4 * x4 + y4 * y4) >> 5)]));
       MATRIX_pixel_color(x+vtx,y+vty,value * 3,255,255);
      x1--; x2--; x3--; x4--;
    }
    y1--; y2--; y3--; y4--;
  }
	angle1   += 0.03;
  angle2   -= 0.07;
  angle3   += 0.13;
  angle4   -= 0.15;
  hueShift += 2;
}*/

unsigned char ball[4][4] = {
  {  3,  0,  1,  1 }, // Initial X,Y pos & velocity for 3 bouncy balls
  { 17, 15,  1, -1 },
  { 27,  4, -1,  1 },
	{ 37,  17, -1,  1 }
};
const unsigned char  ballcolor[4][3] = {
 {80,0,0},
 {0,80,0},
 {0,0,80},
 {0,80,80}
 
};
unsigned char pr_x[4],pr_y[4],checkBall=0;

void ballGreen(unsigned char vtx,unsigned char vty,unsigned char w,unsigned char h,unsigned char r)
{
	
	if(checkBall){
		for(char i=0;i<4;i++){
			  MATRIX_circle( pr_y[i]+vtx,	pr_x[i]+vty, r,1,0,  0, 0);
		}
	}
	unsigned char i;
	 for(i=0; i<4; i++) {
    // Draw 'ball'
		 	MATRIX_circle( ball[i][1]+vtx,ball[i][0]+vty, r,0,ballcolor[i][0],  ballcolor[i][1], ballcolor[i][2]);
		pr_x[i]=ball[i][0];
		pr_y[i]=ball[i][1]; 
    // Update X, Y position
    ball[i][0] += ball[i][2];
    ball[i][1] += ball[i][3];
    // Bounce off edges
    if((ball[i][0] == 0) || (ball[i][0] == (w- 2-r)))
      ball[i][2] *= -1;
    if((ball[i][1] == 0) || (ball[i][1] == (h - 2-r)))
      ball[i][3] *= -1;
  }
	checkBall=1;
}


unsigned char balltext[4][4] = {
  {  3,  0,  1,  1 }, // Initial X,Y pos & velocity for 3 bouncy balls
  { 17, 15,  1, -1 },
  { 27,  4, -1,  1 },
	{ 37,  17, -1,  1 }
};
unsigned char  lengtext[2] = {0,4};
unsigned char pr_xtext[4],pr_ytext[4],checkBalltext=0;


void ballGreentext(unsigned char vtx,unsigned char vty,unsigned char w,unsigned char h,unsigned char a[],unsigned char r,unsigned char g,unsigned char b)
{
	if(checkBalltext){
		for(char i=0;i<1;i++){
			  MATRIX_putStr16x16(pr_ytext[i]+vtx,	pr_xtext[i]+vty,a,0,0,0);
		}
	}
	 for(char i=0; i<1; i++) {
    
	 lengtext[1]=MATRIX_putStr16x16(balltext[i][1]+vtx,balltext[i][0]+vty,a,r,g,b);
		 
		pr_xtext[i]=balltext[i][0];
		pr_ytext[i]=balltext[i][1]; 
    // Update X, Y position
    balltext[i][0] += balltext[i][2];
    balltext[i][1] += balltext[i][3];
    // Bounce off edges
    if((balltext[i][0] == 0) || (balltext[i][0] == (w+3-  lengtext[1])))
      balltext[i][2] *= -1;
    if((balltext[i][1] == 0) || (balltext[i][1] == (h - 9)))
      balltext[i][3] *= -1;
  }
	checkBalltext=1;
}

signed char traightGreen[4][4] = {
  {  -4,  0,  0,  1 }, // Initial X,Y pos & velocity for 3 bouncy balls
  { -4,  31,   0,   -1 },
  { 63,  -4, 0,  1 },
	{0,  -4, 0,  -1 }
};

void green(unsigned char vtx,unsigned char vty,unsigned char w,unsigned char h,unsigned char r,unsigned char g, unsigned char b){
	
	traightGreen[0][1]=0;
	traightGreen[1][1]=h;
	
	traightGreen[2][0]=w;
	traightGreen[3][0]=0;
	
	for(char i=0; i< 4; i++){
		if(i<2){
			for(traightGreen[i][0]=-8;traightGreen[i][0]<=(w+1);traightGreen[i][0] += 8){
				MATRIX_pixel_color(traightGreen[i][1]+vtx,vty+traightGreen[i][0]-traightGreen[i][3]+traightGreen[i][2],	255,255,255);
				MATRIX_pixel_color(traightGreen[i][1]+vtx,vty+traightGreen[i][0]+traightGreen[i][2],	r,g,b);
				MATRIX_pixel_color(traightGreen[i][1]+vtx,vty+traightGreen[i][0]+1*traightGreen[i][3]+traightGreen[i][2],	r,g,b);
				MATRIX_pixel_color(traightGreen[i][1]+vtx,vty+traightGreen[i][0]+2*traightGreen[i][3]+traightGreen[i][2],	r,g,b);
				MATRIX_pixel_color(traightGreen[i][1]+vtx,vty+traightGreen[i][0]+3*traightGreen[i][3]+traightGreen[i][2],	r,g,b);
			  for(char x=1;x<12;x++){
					MATRIX_pixel_color(vtx,w+x+vty,0,0,0);
					MATRIX_pixel_color(vtx,-x+vty,0,0,0);
					MATRIX_pixel_color(vtx+h,vty-x,0,0,0);
				}
			}
		}
		else if(i<4){
			for(traightGreen[i][1]=-8;traightGreen[i][1]<=(h+1);traightGreen[i][1] += 8){
			  MATRIX_pixel_color(traightGreen[i][1]-traightGreen[i][3]+traightGreen[i][2]+vtx,vty+traightGreen[i][0],	255,255,255);
				MATRIX_pixel_color(traightGreen[i][1]+traightGreen[i][2]+vtx,vty+traightGreen[i][0],	r,g,b);
				MATRIX_pixel_color(traightGreen[i][1]+1*traightGreen[i][3]+traightGreen[i][2]+vtx,vty+traightGreen[i][0],	r,g,b);
				MATRIX_pixel_color(traightGreen[i][1]+2*traightGreen[i][3]+traightGreen[i][2]+vtx,vty+traightGreen[i][0],	r,g,b);
				MATRIX_pixel_color(traightGreen[i][1]+3*traightGreen[i][3]+traightGreen[i][2]+vtx,vty+traightGreen[i][0],	r,g,b);
			}
			 for(char x=1;x<12;x++){
					MATRIX_pixel_color(vtx+h+x,w+vty,0,0,0);
					MATRIX_pixel_color(vtx-x,vty+w,0,0,0);
					MATRIX_pixel_color(vtx-x,vty,0,0,0);
				}
		}
			
		traightGreen[i][2]=traightGreen[i][2]+traightGreen[i][3];
		if(traightGreen[i][2]==8||traightGreen[i][2]==-8){
			traightGreen[i][2]=0;
		}	
		
	}
}

int frm=0;
uint16_t aniZoom=0x04, boost=7;
void drawXorFrame(unsigned char vtx,unsigned char vty,unsigned char w,unsigned char h){
    for( int y=0; y<=h; y++ )
        for( int x=0; x<=w; x++ )
            MATRIX_pixel_color(y+vty, x+vtx,  ((x+y+frm)&aniZoom)*boost, ((x-y-frm)&aniZoom)*boost, ((x^y)&aniZoom)*boost);
    if( (frm%1024) == 0 ){
        aniZoom = rand();
        boost   = rand()%9+1;
			  frm=0;
    }
    frm++;
}


#endif













