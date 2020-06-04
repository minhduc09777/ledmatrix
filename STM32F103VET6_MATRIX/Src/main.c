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
  * COPYRIGHT(c) 2020 STMicroelectronics
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
#include "banana.h"
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
#define setbit(sfr,bit)		(sfr|=(1<<bit))
#define clrbit(sfr,bit)		(sfr&=~(1<<bit))
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
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
unsigned char manght[3][64][128];
unsigned char mangxuatled[16][8][256];
const unsigned int mangtg[]={40,80,160,320,640,1280,2560,5120};
void giaima(){
	unsigned int hang,ktbit,cot,pixel,pwm;
	for(hang=0;hang<16;hang++){
		 for(pwm=0,pixel=0x01;pwm<8;pixel<<=1,pwm++){
			 for(cot=0;cot<256;cot++){
				 if(cot<128){
					 mangxuatled[hang][pwm][cot]=0;
					 if((manght[0][hang][cot] & pixel)) {mangxuatled[hang][pwm][cot] |= 0x01;}
					 if((manght[0][hang+16][cot] & pixel)) {mangxuatled[hang][pwm][cot] |= 0x02;}
					 if((manght[1][hang][cot] & pixel)) {mangxuatled[hang][pwm][cot] |= 0x04;}
					 if((manght[1][hang+16][cot] & pixel)) {mangxuatled[hang][pwm][cot] |= 0x08;}
					 if((manght[2][hang][cot] & pixel)) {mangxuatled[hang][pwm][cot] |= 0x10;}
					 if((manght[2][hang+16][cot] & pixel)) {mangxuatled[hang][pwm][cot] |= 0x20;}
				 }
				 else{
					 mangxuatled[hang][pwm][cot]=0;
					 if((manght[0][64-hang][128-cot] & pixel)) {mangxuatled[hang][pwm][cot] |= 0x01;}
					 if((manght[0][48-hang][128-cot] & pixel)) {mangxuatled[hang][pwm][cot] |= 0x02;}
					 if((manght[1][64-hang][128-cot] & pixel)) {mangxuatled[hang][pwm][cot] |= 0x04;}
					 if((manght[1][48-hang][128-cot] & pixel)) {mangxuatled[hang][pwm][cot] |= 0x08;}
					 if((manght[2][64-hang][128-cot] & pixel)) {mangxuatled[hang][pwm][cot] |= 0x10;}
					 if((manght[2][48-hang][128-cot] & pixel)) {mangxuatled[hang][pwm][cot] |= 0x20;}
				 }
			 }
		 }
	}
}
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
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim -> Instance == TIM1){
		 for(int __i=0;__i<256;__i++){
			 GPIOD->ODR = (unsigned short) mangxuatled[bytedieukhien.thanhphan.hang][bytedieukhien.thanhphan.tgian][__i];
			 GPIOD->ODR |= 0x0040;
		 }
		 GPIOA -> ODR |= (1<<4);
		 TIM1->ARR = mangtg[bytedieukhien.thanhphan.tgian];
		 GPIOA -> ODR = bytedieukhien.thanhphan.hang;
		 bytedieukhien.bytedk++;
	}
}
void MATRIX_pixel_color(unsigned char x, unsigned char y,unsigned char r,unsigned char g,unsigned char b){
		manght[0][y][x]=r;
		manght[1][y][x]=g;
		manght[2][y][x]=b;
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
      drawPixelRGB565(xx + x , yy + y, a[counter]);
      counter++;
    }
  }
}
void matrix_clear_green(unsigned char x,unsigned char y){
	for(unsigned char k=0;k<3;k++){
		for(int i=0;i<x;i++){
			for(int j=0;j<y;j++){
				manght[k][i][j]=0;
			}
		}
	}
}
void giaimaanh3(unsigned char *anh, unsigned int dai, unsigned int rong, signed int x, signed int y)
{
  unsigned short n,hang=0,cot=0;
   for(n=0;n<(dai*rong);n++)
   {   
				if(anh[n]==0x00&&anh[dai*rong+n]==0x00&&anh[2*dai*rong+n]==0x00){
					cot++;
					if(cot==dai) {cot=0;hang++;}
				}
				else{
						manght[0][x+hang][y+cot]=anh[n]; 
						manght[1][x+hang][y+cot]=anh[dai*rong+n];
						manght[2][x+hang][y+cot]=anh[2*dai*rong+n];
         cot++;
         if(cot==dai) {cot=0;hang++;}
			  }
   }
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

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start(&htim2);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,10);
	HAL_TIM_Base_Start_IT(&htim1);
	unsigned char chay=0;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	//	MATRIX_putStr16x32(0,64,"DO 2",255,255,255);
	//	MATRIX_putStr16x32(32,0,"DO 2",255,255,255);
		MATRIX_circle(64,32,31,1,255,255,255);
		drawImage(chay,16,64,32,(uint16_t *)mario);
		chay++;
		if(chay>128) chay=0;
	//	giaimaanh3((unsigned char *)lennabmp,64,32,0,0);
	//	drawImage(0,0,64,32,(uint16_t *)banana_frame_1);
		giaima();
		matrix_clear_green(64,128);
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

  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
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
  htim1.Init.Prescaler = 5;
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
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 100;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, A_Pin|B_Pin|C_Pin|D_Pin 
                          |LAT_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, R1_Pin|R2_Pin|G1_Pin|G2_Pin 
                          |B1_Pin|B2_Pin|CLK_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : A_Pin B_Pin C_Pin D_Pin 
                           LAT_Pin */
  GPIO_InitStruct.Pin = A_Pin|B_Pin|C_Pin|D_Pin 
                          |LAT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : R1_Pin R2_Pin G1_Pin G2_Pin 
                           B1_Pin B2_Pin CLK_Pin */
  GPIO_InitStruct.Pin = R1_Pin|R2_Pin|G1_Pin|G2_Pin 
                          |B1_Pin|B2_Pin|CLK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

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
