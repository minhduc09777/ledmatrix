#ifndef __P10_FULL
#define __P10_FULL
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
							 
						 if((manght[1][hang][cot] & (pixel))) {mangxuatled[hang][pwm][cot%8+cot/8*16] |= 0x08;}
						 if((manght[1][hang+4][cot] & (pixel))) {mangxuatled[hang][pwm][cot%8+cot/8*16+8] |= 0x08;}
						 if((manght[1][hang+8][cot] & (pixel))) {mangxuatled[hang][pwm][cot%8+cot/8*16] |= 0x10;}
						 if((manght[1][hang+12][cot] & (pixel))) {mangxuatled[hang][pwm][cot%8+cot/8*16+8] |= 0x10;}
							 
						 if((manght[2][hang][cot] & (pixel))) {mangxuatled[hang][pwm][cot%8+cot/8*16] |= 0x20;}
						 if((manght[2][hang+4][cot] & (pixel))) {mangxuatled[hang][pwm][cot%8+cot/8*16+8] |= 0x20;}
						 if((manght[2][hang+8][cot] & (pixel))) {mangxuatled[hang][pwm][cot%8+cot/8*16] |= 0x40;}
						 if((manght[2][hang+12][cot] & (pixel))) {mangxuatled[hang][pwm][cot%8+cot/8*16+8] |= 0x40;}
					}
				 else{
					   mangxuatled[3-hang][pwm][cot%8+cot/8*16]=0;
				     mangxuatled[3-hang][pwm][cot%8+cot/8*16+8]=0;
						 if((manght[0][hang+16][127-cot] & (pixel))) {mangxuatled[3-hang][pwm][(cot%8+cot/8*16)+8] |= 0x02;}
						 if((manght[0][hang+4+16][127-cot] & (pixel))) {mangxuatled[3-hang][pwm][(cot%8+cot/8*16)] |= 0x02;}
						 if((manght[0][hang+8+16][127-cot] & (pixel))) {mangxuatled[3-hang][pwm][(cot%8+cot/8*16)+8] |= 0x01;}
						 if((manght[0][hang+12+16][127-cot] & (pixel))) {mangxuatled[3-hang][pwm][(cot%8+cot/8*16)] |= 0x01;}
							 
						 if((manght[1][hang+16][127-cot] & (pixel))) {mangxuatled[3-hang][pwm][(cot%8+cot/8*16)+8] |= 0x10;}
						 if((manght[1][hang+4+16][127-cot] & (pixel))) {mangxuatled[3-hang][pwm][(cot%8+cot/8*16)] |= 0x10;}
						 if((manght[1][hang+8+16][127-cot] & (pixel))) {mangxuatled[3-hang][pwm][(cot%8+cot/8*16)+8] |= 0x08;}
						 if((manght[1][hang+12+16][127-cot] & (pixel))) {mangxuatled[3-hang][pwm][(cot%8+cot/8*16)] |= 0x08;}
							 
						 if((manght[2][hang+16][127-cot] & (pixel))) {mangxuatled[3-hang][pwm][(cot%8+cot/8*16)+8] |= 0x40;}
						 if((manght[2][hang+4+16][127-cot] & (pixel))) {mangxuatled[3-hang][pwm][(cot%8+cot/8*16)] |= 0x40;}
						 if((manght[2][hang+8+16][127-cot] & (pixel))) {mangxuatled[3-hang][pwm][(cot%8+cot/8*16)+8] |= 0x20;}
						 if((manght[2][hang+12+16][127-cot] & (pixel))) {mangxuatled[3-hang][pwm][(cot%8+cot/8*16)] |= 0x20;}	
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
					  GPIOB->ODR = mangxuatled[hang][tgian][___i];			 
					  GPIOB->ODR |= 0x0080;
				 }
				   GPIOA -> ODR |= (1<<5);
					 TIM1->ARR = mangtg[tgian];
					 GPIOA -> ODR = hang;
					 tgian++;
					 if(tgian==8){
						 tgian=0;
						 hang++;
						 if(hang==4) hang=0;
					 }
			}
			if(htim->Instance==TIM4)
			{
			}
}

void MATRIX_pixel_color(signed char x,signed char y,unsigned char r,unsigned char g,unsigned char b){

	

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
					 else{
						 manght[0][xmin][i]=rd_map_chaychu[0][hu_rmap_y][hu_rmap_x];
						 manght[1][xmin][i]=rd_map_chaychu[0][hu_rmap_y][hu_rmap_x];
						 manght[2][xmin][i]=rd_map_chaychu[0][hu_rmap_y][hu_rmap_x];
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
		 if(a[i] == ' ') y=y+2;
		 else y=y+8;
	}
}
void MATRIX_putchar16x16(signed char x,signed char y,unsigned char chu,unsigned char r,unsigned char g,unsigned char b){
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
void MATRIX_putStr16x16(signed char x,signed char y,unsigned char a[],unsigned char r,unsigned char g,unsigned char b){
	unsigned char i=0;
	while(a[i]!=0x00){
		 MATRIX_putchar16x16(x,y,a[i],r,g,b);
		 i++;
		 if(a[i] ==' ') y=y+3;
		 else y=y+11;
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
// hien thi dau cham to
void P10_sendRec(unsigned char y_mau,unsigned char x_mau,unsigned char hu)
{
		P10_chonvitri(y_mau,x_mau);
		for(int mau=0;mau<3;mau++)
			 for(int y=0;y<4;y++)
					 for(int x=0;x<4;x++)
							 manght[mau][y+p10_y][x+p10_x]=recfill_fx[hu][mau][y][x];
}
char check_num[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
void latsoto(char num,char y0,char x0,char offset)  //lat xuong so to
{///// nen de trong ngat
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
					 manght[color][y][x]=manght[color][y-1][x];
			 for(char color=0;color<3;color++)
				 {
					for(char x=x0;x<x0+10;x++) 
					 manght[color][y0][x]= number_fx[hieuung][chuc][color][down][x-x0];
					for(char x=x0+11;x<dai;x++) 
					 manght[color][y0][x]= number_fx[hieuung][dv][color][down][x-(x0+11)];
				 }
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
				 manght[color][y0+down][x]= number_fx[hieuung][chuc][color][down][x-x0];
				for(char x=x0+11;x<dai;x++) 
				 manght[color][y0+down][x]= number_fx[hieuung][dv][color][down][x-(x0+11)];
			 }
	  }	
	}
}
char check_numn=-1;
void latsonho(char num,signed char y0,char x0,char offset)  //lat xuong so nho
{
	char chuc,dv,check=0,dai;
	dv = num%10;
	chuc = num/10;
	if(dv != 0)
     {
		    x0=x0+6;
			  dai = x0+5;
		 }
	else 
	   {
			 check=1;
			 dai = x0 + 11;
		 }
	if(check_numn!=num){
			for(signed char down=7;down>=0;down--)
			{
			 for(char color=0;color<3;color++)
				 for(char y=y0+7;y>y0;y--)
					 for(char x=x0;x<dai;x++) 
						 manght[color][y][x]=manght[color][y-1][x];
			 if(check)
				 for(char color=0;color<3;color++)
					 {
						for(char x=x0;x<x0+5;x++) 
						 manght[color][y0][x]= number_nho_fx[hieuung][chuc][color][down][x-x0];
						for(char x=x0+6;x<dai;x++) 
						 manght[color][y0][x]= number_nho_fx[hieuung][dv][color][down][x-(x0+6)];
					 }
			 else 
					for(char color=0;color<3;color++)
					 {
						 for(char x=x0;x<dai;x++) 
						 manght[color][y0][x]= number_nho_fx[hieuung][dv][color][down][x-x0];
					 }
				giaimap10fullmau();
			}  // lat so tiep theo xuong
			check_numn = num;
		}
}
//dung de xoa man hinh
void DRAW_FillRec(char y,char x,char w,char h,unsigned char r,unsigned char g,unsigned char b)
{
	 int _y,_x;
	 w+=x;
	 h+=y;
	 for(_y=y;_y<h;_y++)
		 for(_x=x;_x<w;_x++)
			  manght[0][_y][_x]=r;
	 for(_y=y;_y<h;_y++)
		 for(_x=x;_x<w;_x++)
			  manght[1][_y][_x]=g;
	 for(_y=y;_y<h;_y++)
		 for(_x=x;_x<w;_x++)
			  manght[2][_y][_x]=b;
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
	
	latsoto(hour,y,x,0);
	latsoto(minute,y,x+33,1);
  MATRIX_rect(y-1,x-1,y+15,x+54,0,255,0,0,0);
	if(second != giay_tam){
		for(char i=0;i<3;i++){
			P10_sendRec(y+2+i,x+25,1);
			P10_sendRec(y+11-i,x+25,1);
		//	giaimap10fullmau();
			DRAW_FillRec(y+2+i,x+25,4,4,0,0,0);
			DRAW_FillRec(y+11-i,x+25,4,4,0,0,0);
		}
		for(char i=0;i<3;i++){
			P10_sendRec(y+4-i,x+25,1);
			P10_sendRec(y+9+i,x+25,1);
		//	giaimap10fullmau();
			DRAW_FillRec(y+4-i,x+25,4,4,0,0,0);
			DRAW_FillRec(y+9+i,x+25,4,4,0,0,0);
		}
		P10_sendRec(y+2,x+25,1);
		P10_sendRec(y+11,x+25,1);
		giay_tam=second;	
	}
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

void MATRIX_circle1(signed int x, signed int y, signed int radius, int fill,  unsigned char r1,unsigned char g1,unsigned char b1)
{
	 int ran=255;
   signed int  a, b, P;
   a = 0;
   b = radius;
   P = 1 - radius;
   do
   {
		  ran+=100;
			srand(ran);
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
      if(P < 0){
				 a+=rand()%7;
         P += 2 + 2 * a;
			}
      else{
				 a+=5;
				 b-=5;
         P += 5 + 2 * (a - b);
			}
    } while(a <= b);
}


#endif













