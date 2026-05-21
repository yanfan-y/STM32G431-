#include "head.h" 


char text[21];
uint8_t key_down,key_up,key_val,key_old,yichang=0,l_yichang=0,s=0,flag1=0,flag3=0;
uint8_t capture_val_pwm,H=0,M=0,S=0,lcd_page=0,can_b2=0,jain_b2;
uint32_t val_pwm,val_r40,n1,n2,DR=80,DS=1,FR=2000,FS=100,CF,CD,time2,time,YCF,YCD,YDF,YXF,YH,YM,YS,RCF,RCD,RDS,RFS,ff;
double  VA,DF,N,F,XF,capture_val_r;

void  led_show(uint8_t led,uint8_t mode)
{
	HAL_GPIO_WritePin (GPIOD,GPIO_PIN_2,GPIO_PIN_SET );
	if(mode)
			HAL_GPIO_WritePin (GPIOC,GPIO_PIN_8<<(led-1),GPIO_PIN_RESET );
	else 
			HAL_GPIO_WritePin (GPIOC,GPIO_PIN_8<<(led-1),GPIO_PIN_SET );
	HAL_GPIO_WritePin (GPIOD,GPIO_PIN_2,GPIO_PIN_RESET );
}




void lcd_show()
{
		sprintf(text,"    %d       ",ff);
	LCD_DisplayStringLine (Line0 ,(uint8_t*)text);
	if(lcd_page ==0)
	{   
		flag3=1;

					led_show(1,1);	
					if(s==0)
					{
					led_show (2,0);
					sprintf(text,"   ST=UNLOCK        ");
					LCD_DisplayStringLine (Line6 ,(uint8_t*)text);
							led_show(1,1);
					sprintf(text,"       PWM          ");
					LCD_DisplayStringLine (Line1 ,(uint8_t*)text);
					sprintf(text,"   CF=%dHz       ",CF);
					LCD_DisplayStringLine (Line3 ,(uint8_t*)text);
					sprintf(text,"   CD=%d%%          ",CD);
					LCD_DisplayStringLine (Line4 ,(uint8_t*)text);
					sprintf(text,"   DF=%.0lfHz       ",DF);
					LCD_DisplayStringLine (Line5 ,(uint8_t*)text);
						sprintf(text,"   %02dH%02dM%02dS       ",H,M,S);
					LCD_DisplayStringLine (Line7 ,(uint8_t*)text);
					
				
					}

				if(s==1)
				{
					sprintf(text,"       PWM          ");
					LCD_DisplayStringLine (Line1 ,(uint8_t*)text);
					sprintf(text,"   ST=LOCK          ");
					LCD_DisplayStringLine (Line6 ,(uint8_t*)text);
											sprintf(text,"   %02dH%02dM%02dS       ",H,M,S);
					LCD_DisplayStringLine (Line7 ,(uint8_t*)text);
					led_show (2,1);
				}
         
				
				if(n1<1&&DS>DR)
				{
					DS=RDS;
					
				}
				if(n2<1&&FS>FR)
				{
					FS=RFS;
				}
				

						

	}
	
	if(lcd_page ==1)
	{

			led_show(1,0);
	sprintf(text,"       RECD         ");
	LCD_DisplayStringLine (Line1 ,(uint8_t*)text);
	sprintf(text,"   CF=%dHz       ",YCF);
	LCD_DisplayStringLine (Line3 ,(uint8_t*)text);
	sprintf(text,"   CD=%d%%          ",YCD);
	LCD_DisplayStringLine (Line4 ,(uint8_t*)text);
	sprintf(text,"   DF=%dHz       ",YDF);
	LCD_DisplayStringLine (Line5 ,(uint8_t*)text);
	sprintf(text,"   XF=%dHz       ",YXF);
	LCD_DisplayStringLine (Line6 ,(uint8_t*)text);
	sprintf(text,"   %02dH%02dM%02dS       ",YH,YM,YS);
	LCD_DisplayStringLine (Line7 ,(uint8_t*)text);
				if(s==1)
				{				
					led_show (2,1);
				}	
				else
					led_show (2,0);
		if(flag3==1)
			{
				RDS=DS;
				RFS=FS;

			}
		
	}
	
	if(lcd_page ==2)
	{

			led_show(1,0);		
	LCD_ClearLine (Line7 );	
	sprintf(text,"       PARA         ");
	LCD_DisplayStringLine (Line1 ,(uint8_t*)text);
	sprintf(text,"   DS=%d%%       ",DS);
	LCD_DisplayStringLine (Line3 ,(uint8_t*)text);
	sprintf(text,"   DR=%d%%          ",DR);
	LCD_DisplayStringLine (Line4 ,(uint8_t*)text);
	sprintf(text,"   FS=%dHz       ",FS);
	LCD_DisplayStringLine (Line5 ,(uint8_t*)text);
	sprintf(text,"   FR=%dHz       ",FR);
	LCD_DisplayStringLine (Line6 ,(uint8_t*)text);
				if(s==1)
				{				
					led_show (2,1);
				}	
				else
					led_show (2,0);

						
		
  }
}




uint8_t  key_scan()
{
	uint8_t temp=0;
	if(HAL_GPIO_ReadPin (GPIOB,GPIO_PIN_0 )==GPIO_PIN_RESET )    temp=1;
else	if(HAL_GPIO_ReadPin (GPIOB,GPIO_PIN_1 )==GPIO_PIN_RESET )    temp=2;
else	if(HAL_GPIO_ReadPin (GPIOB,GPIO_PIN_2 )==GPIO_PIN_RESET )    temp=3;
else 	if(HAL_GPIO_ReadPin (GPIOA,GPIO_PIN_0 )==GPIO_PIN_RESET )    temp=4;
	
	if(temp!=0)
	{
		HAL_Delay (20);
			if(HAL_GPIO_ReadPin (GPIOB,GPIO_PIN_0 )==GPIO_PIN_RESET )    temp=1;
else	if(HAL_GPIO_ReadPin (GPIOB,GPIO_PIN_1 )==GPIO_PIN_RESET )    temp=2;
else	if(HAL_GPIO_ReadPin (GPIOB,GPIO_PIN_2 )==GPIO_PIN_RESET )    temp=3;
else 	if(HAL_GPIO_ReadPin (GPIOA,GPIO_PIN_0 )==GPIO_PIN_RESET )    temp=4;
	}
	return temp;
}



void key()
{
	key_val =key_scan ();
	key_down=key_val &(key_val ^key_old );
	key_up=~key_val &(key_val ^key_old );
	key_old =key_val ;
	
	if(key_down ==1)
	{
		can_b2 =0;
		lcd_page ++;
		if(lcd_page >2)  lcd_page =0;
		uint8_t last_page=0;
				if(lcd_page == 2 && last_page != 2)
		{
			RDS = DS;
			RFS = FS;
		}
		last_page = lcd_page;

	}
	
	if(lcd_page ==2)
	{		
		

		if(key_down ==2)
		{
   flag3 =0;
			can_b2 ++;
			if(can_b2 >3)
			{
				can_b2 =0;
			}
		}
		else 
			flag3 =1;
		//DS
		 if(can_b2 ==0)
		{
			if(key_down ==3&&DS<100)
			{
				DS=DS+1;
			}
			if(key_down ==4&&DS>0)
			{
				DS=DS-1;
			}
		}
		//DR
		else if(can_b2 ==1)
		{
			if(key_down ==3&&DR<100)
			{
				DR=DR+10;
			}
			if(key_down ==4&&DR>0)
			{
				DR=DR-10;
			}
		}		
		//FS
		else if(can_b2 ==2)
		{
			if(key_down ==3)
			{
				FS=FS+100;
			}
			if(key_down ==4)
			{
				FS=FS-100;
			}
		}	
    //FR		
		else if(can_b2 ==3)
		{
			if(key_down ==3)
			{
				FR=FR+1000;
			}
			if(key_down ==4)
			{
				FR=FR-1000;
			}
		}		
	}
	
	if(lcd_page ==0)
	{
	
		
		
		if(key_down ==2)
		{	
			time =0;
			flag1 =1;
		}
				
		if(key_up ==2&&flag1 ==1)
		{
		if(time<=2000)
			{
				s=!s;
	
				
				
			}		
		
		
	else 
			{
				H=0;
				M=0;
				S=0;
				time2=0;
				
			}
			flag1=0;
		}
		
	}
	


	
	
	
	
	
}




void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef*htim)
{
	if(htim->Instance ==TIM17)
	{
		capture_val_pwm=HAL_TIM_ReadCapturedValue (htim ,TIM_CHANNEL_1 );
		TIM17->CNT=0;
		ff =80000000/(80*capture_val_pwm );
//		CD=TIM15->CCR1;
	}
		
	
	if(htim->Instance ==TIM2)
	{
		capture_val_r=HAL_TIM_ReadCapturedValue (htim,TIM_CHANNEL_1 );
		TIM2->CNT=0;

		DF=80000000/(8*capture_val_r);
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim ->Instance ==TIM3 )
	{
		time++;
		
	}
	
	if(htim ->Instance ==TIM4 )
	{

		{
			time2++;
			if(time2<5900)
			{
			S=time2;
			}
			if(time2>59)
			{
			time2=0;
				M++;
			}
			if(M>59)
			{
			H++;
				M=0;
			}
		}
		
	}
	
}



double get_vol(ADC_HandleTypeDef *hadc)
{
	HAL_ADC_Start (hadc );
	uint32_t adc_val=HAL_ADC_GetValue (hadc);
	return 3.3*adc_val/4096.0; 
	
	
	
}


void  ma()
{
	
		//CD
	
	
	n1=(DR-10)/DS;
	VA=3.3/n1;
if(0<=get_vol (&hadc2 )&&get_vol (&hadc2 )<VA)
		{
			CD=10;
		}
 else  if(VA<=get_vol (&hadc2)&&get_vol (&hadc2 )<=3.3)
	{
		N=get_vol (&hadc2 )/VA;
	   CD=10+N*DS;
		
	}
		
	
	
	
	
	
	//CF
		n2=((double)FR-1000)/FS;
	VA=3.3/n2;
	

	if(0<=get_vol (&hadc1 )&&get_vol (&hadc1 )<VA)
		{
			CF=1000;
		}
if(VA<=get_vol (&hadc1)&&get_vol (&hadc1 )<=3.3)
	{
		F=get_vol (&hadc1 )/VA;
	   CF=1000+F*FS;
		
	}

	

XF = (CF > DF) ? (CF - DF) : (DF - CF);
	uint8_t t_yichang;
if((CF-DF>1000)||(DF-CF >1000) )
{
	t_yichang=1;
	led_show (3,1);

}
else
{
	t_yichang =0;
	led_show (3,0);
}
if(t_yichang ==1&&l_yichang==0)
{
	YCF=CF;
	YCD=CD;
	YDF=DF;
	YXF=XF;
	YH=H;
	YM=M;
	YS=S;
}
l_yichang=t_yichang ;
yichang =t_yichang ;



}




















