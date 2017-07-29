#include "stm32f4xx.h"
#include "LCD.h"
#include "dcmi_OV7670.h"
#include <stdio.h>

DAC_InitTypeDef  DAC_InitStructure;
EXTI_InitTypeDef   var_exti ; 
NVIC_InitTypeDef   var_nvic ;
void Delay(__IO uint32_t nCount);
void TIM6_Config(void);
void DAC_Ch1_NoiseConfig();
void DAC_Ch1_NoiseStop();

int main(void)
{
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
 
  GPIO_InitTypeDef GPIO_InitStructure,LED;
  
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1; //Pin 0 pour la button (Mode Marche arriere) et Pin 1 pour le Capteur 
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;   
  GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
  
  /* Configurer les champs du EXTI*/
  var_exti.EXTI_Line=EXTI_Line0;
  var_exti.EXTI_Mode=EXTI_Mode_Interrupt;
  var_exti.EXTI_Trigger=EXTI_Trigger_Rising;
  var_exti.EXTI_LineCmd=ENABLE;
 
  /*Configurer les champs du NVIC*/
  var_nvic.NVIC_IRQChannel=EXTI0_IRQn;
  var_nvic.NVIC_IRQChannelPreemptionPriority=0x01;
  var_nvic.NVIC_IRQChannelSubPriority=0x01;
  var_nvic.NVIC_IRQChannelCmd=ENABLE;
  
  EXTI_Init(&var_exti );
  NVIC_Init(&var_nvic );
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);
  
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

  GPIO_Init(GPIOA,&GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; //Configuration du DAC sur le channel 2 PIN 5
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

 
   //***************************************************************** 
  uint8_t temp[35]={'B','O','N','J','O','U','R',' ','T','O','U','T',' ','l','E',' ','M','O','N','D','E'};
  uint8_t temp1[20]={'B','i','n','a','r','y',' ','T','e','a','m'};
  uint8_t temp2[20]={'4','S','L','E','A','M'};
  uint8_t temp3[20]={'B','e','n',' ','A','o','u','i','c','h','a',' ','Z','e','i','n','e','b'};
  uint8_t temp4[27]={'Z','n','a','i','d','i',' ','M','o','h','a','m','e','d',' ','A','m','i','n','e'};
  uint8_t temp5[20]={'Z','o','u','a','i',' ','A','m','i','n','e'};
  uint8_t temp6[20]={'D','o','u','k','h',' ','M','a','r','w','e','n'};
  uint8_t temp7[25]={'M','e','s','s','o','u','d',' ','M','o','h','a','m','e','d',' ','A','m','i','n','e'};
  uint8_t temp8[20]={'S','a','t','o','u','r','i',' ','C','h','a','w','k','i'};
  uint8_t temp9[20]={'R','e','a','l','i','s','e',' ','P','a','r'};
  uint8_t temp10[20]={'B','i','n','a','r','y',' ','T','e','a','m'};
  uint8_t temp11[55]={'N','o','t','r','e',' ','p','r','o','j','e','t',' ','C','A','M','E','R','A',' ','D','E',' ','R','E','C','U','L','E'};
  uint8_t temp12[55]={'e','s','t',' ','e','n',' ','c','o','u','r','s',' ','d','e',' ','r','e','a','l','i','s','a','t','i','o','n'};
  uint8_t temp14[10]={'D','a','t','e',':'};
  uint8_t temp15[15]={'1','5','/','1','2','/','2','0','1','6'};
  uint8_t temp16[10]={'H','e','u','r','e',':'};
  uint8_t temp17[10]={'1','0',':','3','0'};
  uint8_t temp18[15]={'T','e','m','p','e','r','a','t','u','r','e',':'};
  uint8_t temp19[10]={'2','3',' ','C'};
  uint8_t temp20[10]={'C','A','M','E','R','A'};
  uint8_t temp21[10]={'D','I','S','T','A','N','C','E'}
  ;
  LCD_Initializtion(); //Initialisation de l'ecran
  
  //afficher ecran d'accueil
 LCD_Clear(White);

 GUI_Text(100,100,(uint8_t*)temp,Red,White);
 Delay(0xFFFFFA);

 
  // afficher les noms
  LCD_Clear(White);
  GUI_Text(120,10,(uint8_t*)temp9,Red,Black);
  GUI_Text(120,200,(uint8_t*)temp10,Red,Black);
  Delay(0xFFFFFA);
  GUI_Text(12,50,(uint8_t*)temp3,Red,White);
  Delay(0xFFFFFA);
  GUI_Text(12,75,(uint8_t*)temp4,Red,White);
  Delay(0xFFFFFA);
  GUI_Text(12,100,(uint8_t*)temp5,Red,White);
  Delay(0xFFFFFA);
  GUI_Text(12,125,(uint8_t*)temp6,Red,White);
  Delay(0xFFFFFA);
  GUI_Text(12,150,(uint8_t*)temp7,Red,White);
  Delay(0xFFFFFA);
  GUI_Text(12,175,(uint8_t*)temp8,Red,White);
  Delay(0xFFFFFF);
  //afficher le nom du projet
  LCD_Clear(White);
  GUI_Text(35,100,(uint8_t*)temp11,Red,Black);
  GUI_Text(35,125,(uint8_t*)temp12,Red,Black);
  Delay(0xFFFFFF);
  //******************************************************************************
  LCD_Clear(White);  
  while (1)
  {
  //afficher l'heure , date et temerature
  GUI_Text(12,50,(uint8_t*)temp14,Red,Black);
  GUI_Text(120,75,(uint8_t*)temp15,Red,White);
  GUI_Text(12,100,(uint8_t*)temp16,Red,Black);
  GUI_Text(120,125,(uint8_t*)temp17,Red,White);
  GUI_Text(12,150,(uint8_t*)temp18,Red,Black);
  GUI_Text(120,175,(uint8_t*)temp19,Red,White);
  }
}

void TIM6_Config(void)
{
  TIM_TimeBaseInitTypeDef    TIM_TimeBaseStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Period = 0x0F;
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);

  TIM_SelectOutputTrigger(TIM6, TIM_TRGOSource_Update);


  TIM_Cmd(TIM6, ENABLE);
}

//activation du speaker*************************************************************************
void DAC_Ch1_NoiseConfig()
{  

    int Ad_value ;
    
  DAC_InitStructure.DAC_Trigger =DAC_Trigger_T6_TRGO ;
  DAC_InitStructure.DAC_WaveGeneration =DAC_WaveGeneration_Triangle;// DAC_WaveGeneration_Noise;
  DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude =DAC_TriangleAmplitude_511;
  DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
  DAC_Init(DAC_Channel_2 , &DAC_InitStructure);

  /* Enable DAC Channel1 */
  DAC_Cmd(DAC_Channel_2 , ENABLE);

  /* Set DAC Channel1 DHR12L register */
  DAC_SetChannel1Data(DAC_Align_12b_L, 0x000F);
  Ad_value=(int)DAC_GetDataOutputValue(DAC_Channel_2 );
  printf("hello ima the vlue cinverted %d \n",Ad_value);


}
//Desactivation du Speaker*********************************************************************
void DAC_Ch1_NoiseStop()
{  

    int Ad_value ;
    
  DAC_InitStructure.DAC_Trigger =DAC_Trigger_T6_TRGO ;
  DAC_InitStructure.DAC_WaveGeneration =DAC_WaveGeneration_Triangle;// DAC_WaveGeneration_Noise;
  DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude =DAC_TriangleAmplitude_511;
  DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
  DAC_Init(DAC_Channel_1, &DAC_InitStructure);

  /* Enable DAC Channel1 */
  DAC_Cmd(DAC_Channel_2, DISABLE);

  /* Set DAC Channel1 DHR12L register */
  DAC_SetChannel1Data(DAC_Align_12b_L, 0x000);
  Ad_value=(int)DAC_GetDataOutputValue(DAC_Channel_2 );
  printf("hello ima the vlue cinverted %d \n",Ad_value);


}

//Fonction d'Interruption "Mode Marche ariere"*************************************************************
void EXTI0_IRQHandler(void)
{ 
  if(EXTI_GetITStatus(EXTI_Line0)!=RESET)
  { 
//Activation Duc camera**********************************************************************************************
LCD_Initializtion();
LCD_Clear(Blue2);
GUI_Text(100,100,"Mode Marche Arriere",Black,White);
TIM6_Config();
DAC_Ch1_NoiseConfig();
Delay(0xFFFFFF);
LCD_Clear(White);
DAC_Ch1_NoiseStop();
OV7670_IDTypeDef OV7670ID;
DCMI_OV7670_Init();
DCMI_OV7670_ReadID(&OV7670ID);
DMA_Cmd(DMA2_Stream1, ENABLE);//Activation du Dma Pour transmmettre les données Du DCMI(Caméra) au FSMC(Ecran Lcd)
DCMI_Cmd(ENABLE);

DCMI_CaptureCmd(ENABLE); //Activation du camera   

while (1)
{ 
if( GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)!=0)
     {
     TIM6_Config();
     DAC_Ch1_NoiseConfig();
     Delay(0xFFF);
     TIM6_Config();
     DAC_Ch1_NoiseStop();

     }
}
}

 }
//Declaration de la Fonction du Delay************************************************************************
void Delay(__IO uint32_t nCount)
{
  while(nCount--)
  {
  }
}

