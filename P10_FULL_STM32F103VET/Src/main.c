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
#include "p10_fullmau.h"
#include "mario.h"


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
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM2_Init(void);
static void MX_RTC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */



#define gioihanfirework 35
unsigned char mangbanphao[10]={gioihanfirework,gioihanfirework,gioihanfirework},mangphunphao[10]={0,0,0},pre_y[10],pre_x[10],checkFireWork=0,checkFunfao=0;

void firework(unsigned char x,unsigned char y, unsigned char  vt,unsigned char r,unsigned char g,unsigned char b){
		
	if(checkFireWork==1){
			MATRIX_circle(pre_y[vt],x,1,1,0,0,0);
			MATRIX_pixel_color(pre_y[vt]+1,x,0,0,0);
			MATRIX_pixel_color(pre_y[vt]+2,x,0,0,0);
			MATRIX_pixel_color(pre_y[vt]+3,x,0,0,0);
	}
	MATRIX_circle(mangbanphao[vt],x,1,1,255,255,255);
	MATRIX_pixel_color(mangbanphao[vt]+1,x,50,50,50);
	MATRIX_pixel_color(mangbanphao[vt]+2,x,10,10,10);
	MATRIX_pixel_color(mangbanphao[vt]+3,x,5,5,5);
	
	pre_y[vt]=mangbanphao[vt];
	checkFireWork=1; 
	
	if(mangbanphao[vt]<y){
		MATRIX_circle(mangbanphao[vt],x,1,1,0,0,0);
		MATRIX_pixel_color(mangbanphao[vt]+1,x,0,0,0);
		MATRIX_pixel_color(mangbanphao[vt]+2,x,0,0,0);
		MATRIX_pixel_color(mangbanphao[vt]+3,x,0,0,0);
		MATRIX_circle(mangbanphao[vt],x,1,0,r,g,b);
		
		if(checkFunfao==1){
			MATRIX_line((y-5)-pre_x[vt],x, (y-4)-pre_x[vt],x, 0,0,0,0);
			MATRIX_line((y+2)+pre_x[vt], x, (y+3)+pre_x[vt],x, 0,0,0,0);
			MATRIX_line(y,(x-5)-pre_x[vt], y, (x-4)-pre_x[vt], 0,0,0,0);
			MATRIX_line(y,(x+2)+pre_x[vt], y, (x+3)+pre_x[vt], 0,0,0,0);
			
			MATRIX_line((y+1)+pre_x[vt],(x+1)+pre_x[vt], (y+3)+pre_x[vt], (x+3)+pre_x[vt], 0,0,0,0);
			MATRIX_line((y+1)+pre_x[vt],(x-1)-pre_x[vt], (y+3)+pre_x[vt], (x-3)-pre_x[vt], 0,0,0,0);
			MATRIX_line((y-1)-pre_x[vt],(x+1)+pre_x[vt], (y-3)-pre_x[vt], (x+3)+pre_x[vt], 0,0,0,0);
			MATRIX_line((y-1)-pre_x[vt],(x-1)-pre_x[vt], (y-3)-pre_x[vt], (x-3)-pre_x[vt], 0,0,0,0);
		}
		
		MATRIX_line((y-5)-mangphunphao[vt],x, (y-4)-mangphunphao[vt],x, r,g,b,0);
    MATRIX_line((y+2)+mangphunphao[vt], x, (y+3)+mangphunphao[vt],x, r,g,b,0);
    MATRIX_line(y,(x-5)-mangphunphao[vt], y, (x-4)-mangphunphao[vt], r,g,b,0);
    MATRIX_line(y,(x+2)+mangphunphao[vt], y, (x+3)+mangphunphao[vt], r,g,b,0);
		
		MATRIX_line((y+1)+mangphunphao[vt],(x+1)+mangphunphao[vt], (y+3)+mangphunphao[vt], (x+3)+mangphunphao[vt], r,g,b,0);
    MATRIX_line((y+1)+mangphunphao[vt],(x-1)-mangphunphao[vt], (y+3)+mangphunphao[vt], (x-3)-mangphunphao[vt], r,g,b,0);
    MATRIX_line((y-1)-mangphunphao[vt],(x+1)+mangphunphao[vt], (y-3)-mangphunphao[vt], (x+3)+mangphunphao[vt], r,g,b,0);
    MATRIX_line((y-1)-mangphunphao[vt],(x-1)-mangphunphao[vt], (y-3)-mangphunphao[vt], (x-3)-mangphunphao[vt], r,g,b,0);
		
		pre_x[vt]=mangphunphao[vt];
		
		checkFunfao=1;
		mangphunphao[vt]++;
		if(mangphunphao[vt]>3){
				mangbanphao[vt]=gioihanfirework;
				mangphunphao[vt]=0;
				MATRIX_line((y-5)-pre_x[vt],x, (y-4)-pre_x[vt],x, 0,0,0,0);
				MATRIX_line((y+2)+pre_x[vt], x, (y+3)+pre_x[vt],x, 0,0,0,0);
				MATRIX_line(y,(x-5)-pre_x[vt], y, (x-4)-pre_x[vt], 0,0,0,0);
				MATRIX_line(y,(x+2)+pre_x[vt], y, (x+3)+pre_x[vt], 0,0,0,0);
				
				MATRIX_line((y+1)+pre_x[vt],(x+1)+pre_x[vt], (y+3)+pre_x[vt], (x+3)+pre_x[vt], 0,0,0,0);
				MATRIX_line((y+1)+pre_x[vt],(x-1)-pre_x[vt], (y+3)+pre_x[vt], (x-3)-pre_x[vt], 0,0,0,0);
				MATRIX_line((y-1)-pre_x[vt],(x+1)+pre_x[vt], (y-3)-pre_x[vt], (x+3)+pre_x[vt], 0,0,0,0);
				MATRIX_line((y-1)-pre_x[vt],(x-1)-pre_x[vt], (y-3)-pre_x[vt], (x-3)-pre_x[vt], 0,0,0,0);
		}
	}
	else{
		mangbanphao[vt]--;
	}
	
}
unsigned char anhdongfirechay=0;
void anhdongfire(unsigned char y,unsigned char x){
	if(anhdongfirechay==0)      drawImage(y,x,64,32,(uint16_t *)fire_frame_1);
	else if(anhdongfirechay==1) drawImage(y,x,64,32,(uint16_t *)fire_frame_2);
	else if(anhdongfirechay==2) drawImage(y,x,64,32,(uint16_t *)fire_frame_3);
	else if(anhdongfirechay==3) drawImage(y,x,64,32,(uint16_t *)fire_frame_4);
	else if(anhdongfirechay==4) drawImage(y,x,64,32,(uint16_t *)fire_frame_5);
	else if(anhdongfirechay==5) drawImage(y,x,64,32,(uint16_t *)fire_frame_6);
	else if(anhdongfirechay==6) drawImage(y,x,64,32,(uint16_t *)fire_frame_7);
	else if(anhdongfirechay==7) drawImage(y,x,64,32,(uint16_t *)fire_frame_8);
	else if(anhdongfirechay==8) drawImage(y,x,64,32,(uint16_t *)fire_frame_9);
	
	anhdongfirechay++;
	if(anhdongfirechay>8) anhdongfirechay=0;
}

unsigned char anhdongnyanchay=0;
void anhdongnyancat(unsigned char y,unsigned char x){
	if(anhdongnyanchay==0)      drawImage(y,x,64,32,(uint16_t *)nyan_cat_1);
	else if(anhdongnyanchay==1) drawImage(y,x,64,32,(uint16_t *)nyan_cat_2);
	else if(anhdongnyanchay==2) drawImage(y,x,64,32,(uint16_t *)nyan_cat_3);
	else if(anhdongnyanchay==3) drawImage(y,x,64,32,(uint16_t *)nyan_cat_4);
	else if(anhdongnyanchay==4) drawImage(y,x,64,32,(uint16_t *)nyan_cat_5);
	else if(anhdongnyanchay==5) drawImage(y,x,64,32,(uint16_t *)nyan_cat_6);
	else if(anhdongnyanchay==6) drawImage(y,x,64,32,(uint16_t *)nyan_cat_7);
	else if(anhdongnyanchay==7) drawImage(y,x,64,32,(uint16_t *)nyan_cat_8);
	
	anhdongnyanchay++;
	if(anhdongnyanchay>7) anhdongnyanchay=0;
}
signed char scrollvt[10],checkScroll[10],prexScroll[10],preyScroll[10];
void Scrolltext16x16(unsigned char x,unsigned char y,unsigned char w,unsigned char ttd,unsigned char a[],unsigned char r,unsigned char g,unsigned char b,unsigned char vt){
	
	if(checkScroll[vt]==1){
			MATRIX_putStr16x16(x,y+preyScroll[vt],a,0,0,0);
	}
	MATRIX_putStr16x16(x,y+scrollvt[vt],a,r,g,b);
	preyScroll[vt]=scrollvt[vt];
	
	if(ttd=='p'){
		scrollvt[vt]++;
		if(scrollvt[vt]==w) scrollvt[vt]= - 30;
	}
	else{
		scrollvt[vt]--;
		if(scrollvt[vt]==-w-40) scrollvt[vt]=0;
	}
	
	checkScroll[vt]=1;
	
}
void donghokim(unsigned char vtx,unsigned char vty){
	
	unsigned char offsetx=1,offsety=-3;
	MATRIX_circle(vtx,vty,15,0,255,0,0);
	MATRIX_circle(vtx,vty,14,0,0,0,255);
	
	///////////////////huong 12 gio////////////////////////////
	MATRIX_line(0+offsetx,vty+offsety,2+offsetx,vty+2+offsety,0,255,0,0);
	MATRIX_line(0+offsetx,vty+2+offsety, 2+offsetx,vty+offsety,0,255,0,0);
	MATRIX_line(0+offsetx,0+offsety+vty+4,2+offsetx,0+offsety+vty+4,0,255,0,0);
	MATRIX_line(0+offsetx,0+offsety+vty+6,2+offsetx,0+offsety+vty+6,0,255,0,0);
	////////////////////huong 9 gio/////////////////////////////
	unsigned char offsetx1=-1,offsety1=3;
	MATRIX_line(vtx+offsetx1,offsety1,vtx+2+offsetx1,2+offsety1,0,255,0,0);
	MATRIX_line(vtx+offsetx1,2+offsety1,vtx+2+offsetx1,0+offsety1,0,255,0,0);
	
	MATRIX_line(0+vtx+offsetx1,1,2+vtx+offsetx1,1,0,255,0,0);
	
	///////////////////huong 3 gio////////////////////////////////////////
	MATRIX_line(0+vtx+offsetx1,25,2+vtx+offsetx1,25,0,255,0,0);
	MATRIX_line(0+vtx+offsetx1,27,2+vtx+offsetx1,27,0,255,0,0);
	MATRIX_line(0+vtx+offsetx1,29,2+vtx+offsetx1,29,0,255,0,0);
	
	//////////////////huong 6 gio////////////////////////////////////////
	MATRIX_line(0+offsetx+26,0+offsety+vty+5,2+offsetx+26,0+offsety+vty+5,0,255,0,0);
	MATRIX_line(0+offsetx+26,vty+2+offsety+2, 2+offsetx+26,vty+offsety+2,0,255,0,0);
	MATRIX_line(0+offsetx+26,vty+offsety,2+offsetx+26,vty+2+offsety,0,255,0,0);
	
	
	

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
  MX_RTC_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start_IT(&htim1);
	
	HAL_TIM_Base_Start(&htim2);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,40);
	
	initial_clock();
	unsigned char chay=6;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
			HAL_RTC_GetTime(&hrtc,&sTime,RTC_FORMAT_BIN);
			HAL_RTC_GetDate(&hrtc,&sDate,RTC_FORMAT_BIN);
			hour=sTime.Hours;
			minute=sTime.Minutes;
			second=sTime.Seconds;
			day=sDate.Date;
			month=sDate.Month;
			year=sDate.Year;
		  //drawImage(0,0,64,32,(uint16_t *)mario);
		//	DongHoBig(15,0);
		//	amlich_ht(-2,4);
			//drawImage(0,0,64,32,(uint16_t *)banana_frame_1);
		 //drawImage(0,0,64,32,(uint16_t *)mario);
	   //drawImage(0,0,64,32,(uint16_t *)fire_frame_1);
		 //drawImage(0,0,64,32,(uint16_t *)nyan_cat_1);
		
		 // firework(15,15,0,255,0,0);
		 // firework(30,20,1,255,255,0);
		 // firework(45,6,2,0,0,255);
	  
		 // latsoto(chay,0,10,0);
		 // chay--;
		 // if(chay==0) chay=6;
			//anhdongfire(0,0);
		//anhdongnyancat(0,0);
		//latsonho(chay,0,0,0);*/
		
		
	/*	drawSeg('a',255,0,0);
		drawSeg('b',255,0,0);
		drawSeg('c',255,0,0);
		drawSeg('d',255,0,0);
		drawSeg('e',255,0,0);
		drawSeg('f',255,0,0);
		drawSeg('g',255,0,0);*/
		
		 // drawDigital(second%10,10,10,255,255,255);
		// setupSeg(6,6);
		// Morph(second%10,1,10,255,255,255,0);
	  // DongHo7Seg(0,0);
		 //plashma(0,0,32,64);
		 
		 
	 // ballGreen(3,3,63,31,3);
	 // ballGreentext(-2,1,62,28,"Đức mt",255,255,0);
	  // Scrolltext16x16(0,0,63,'p',"text",0,255,0,0);
		// Scrolltext16x16(16,63,63,'t',"check",0,0,255,1);
		// green(0,0,63,31,255,0,0);
		
		
		
	//	 MATRIX_putStr16x16(0,0,"Đức",0,0,20);
	//	 MATRIX_putStr16x16(0,1,"Đức",0,0,255);
		//MATRIX_putchar8x8(0,0,'O',4,0,255,0);
	//	MATRIX_putStr8x8(0,0,"HCM spkt",chay,0,0,255);
	
	
	
	//	 drawXorFrame(0,0,63,31);
	//	 ballGreentext(-2,1,62,28,"Đức mt",0,255,0);
		

		 giaimap10fullmau();
	///	 matrix_p10fullmau_clear_all();
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
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
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
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

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef DateToUpdate = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */
  /**Initialize RTC Only 
  */
  hrtc.Instance = RTC;
  hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_CALIBCLOCK;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */
    
  /* USER CODE END Check_RTC_BKUP */

  /**Initialize RTC and set the Time and Date 
  */
  sTime.Hours = 12;
  sTime.Minutes = 0;
  sTime.Seconds = 0;

  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  DateToUpdate.WeekDay = RTC_WEEKDAY_TUESDAY;
  DateToUpdate.Month = RTC_MONTH_APRIL;
  DateToUpdate.Date = 7;
  DateToUpdate.Year = 20;

  if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

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
  if (HAL_TIM_OC_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_TIMING;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_OC_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
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
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3 
                          |GPIO_PIN_4, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3 
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_SET);

  /*Configure GPIO pins : PA0 PA1 PA2 PA3 
                           PA4 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3 
                          |GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PD0 PD1 PD2 PD3 
                           PD4 PD5 PD6 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3 
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
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
