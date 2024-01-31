#include "main.h"
#include "tim.h"
#include "gpio.h"
#include "smg.h"
void for_delay_us(uint32_t nus)
{
 uint32_t Delay = nus * 168/4;
 do
 {
  __NOP();
 }
 while (Delay --);
}


void LED_Wei(uint8_t num)//5 101
{
    LED_A0 ((GPIO_PinState)(num & 0x01));
    LED_A1 ((GPIO_PinState)((num & 0x02) >> 1));
    LED_A2 ((GPIO_PinState)((num & 0x04) >> 2));
}

void LED_Write_Data(uint8_t duan,uint8_t wei)//第一个是显示什么，比如空是0，第二个是第几位
{
    uint8_t i;
    for ( i = 0; i < 8; i++) //先送段
    {
        LED_DS((GPIO_PinState)((duan >> i) & 0x01));
        LED_SCK(0);
        for_delay_us(5);
        LED_SCK(1);
    }

    LED_Wei(wei);//后选中位

}
/*数码管刷新显示*/
void LED_Refresh(void)
{
    LED_LCLK(1);//拉高触发
	for_delay_us(5);
    LED_LCLK (0);//拉低准备下一次
}

uint8_t smg_num[] = {0xfc, 0x60, 0xda, 0xf2, 0x66, 0xb6, 0xbe, 0xe0, 0xfe, 0xf6, 0xee, 0x3e, 0x9c, 0x7a, 0x9e, 0x8e, 0x01, 0x00};
uint8_t smg_wei=0; //数码管位选
uint8_t smg_duan;//数码管段选，当前要显示的数字
uint8_t shownums[8]={0,0,0,0,0,0,0,0};//nums里不是数字，而是和smg_num一样的东西
int m=0;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance==TIM1){
		m++;
	}
	if(htim->Instance==TIM2){//这里每次中断只能显示一位
		if(smg_wei==8)smg_wei=0;
		LED_Write_Data(shownums[smg_wei], smg_wei); //数码管显示
		LED_Refresh();//刷新显示
		smg_wei++;

	}     

}
void smg_showint(int num){//显示整数，输入一个整数就可以显示出它
	if(num==0){//如果是0
		shownums[7]=smg_num[0];//第7位显示0
		uint8_t i; 
		for (i = 0; i <= 6; i++) shownums[i]=0;//其他位都不显示
	}	
	else if(num>0){
		uint8_t i; 
		for (i = 1; i <= 8&&num!=0; i++) {//前几位取出数字然后显示
			shownums[8-i]=smg_num[num%10];
			num /= 10;
		}
		for (; i <= 8; i++) shownums[8-i]=0;//其他位不显示
	}
	else{
		uint8_t i; num*=-1;//取正
		for (i = 1; i <= 8&&num!=0; i++) {
			shownums[8-i]=smg_num[num%10];
			num /= 10;
		}
		shownums[8-i]=0x02;i+=1;//显示一个负号
		for (; i <= 8; i++) shownums[8-i]=0;
	}
	
}


//添加一个笔画，比如第三段添加一个点就是smg_addled(3,7);顶部为0，顺时针依次为1，2，3，4，5，中间为6，点为7
void smg_addled(uint8_t duan,uint8_t wei){
	uint8_t i;
	uint8_t tmp=1;//如果wei是7，那tmp就是2^0 如果wei是6，那tmp就是2^1
	for (i = 7-wei; i >0; i--) tmp*=2;
	shownums[duan]|=tmp;//把那一位变成1
}	
void smg_showfloat(double num){//默认四位小数
	if(num==0){
		shownums[3]=0xfd;//第3位显示0.
		uint8_t i; 
		for (i = 4; i <= 7; i++) shownums[i]=smg_num[0];//后面的都显示0
	}
	else if(num>=1||num<=-1){
		smg_showint(num*10000);
		smg_addled(3,7);
	}
	else{
		

		shownums[3]=0xfd;//第3位显示0.
		if(num>0){
			for(uint8_t i=0;i<3;i++)shownums[i]=0;//012不显示
			for(uint8_t i=4;i<8;i++){
				num*=10;
				shownums[i]=smg_num[(int)num];
				num-=(int)num;
			}	
		}
		else{
			for(uint8_t i=0;i<2;i++)shownums[i]=0;//01不显示
			shownums[2]=0x02;//第二位显示 -
			num*=-1;
			for(uint8_t i=4;i<8;i++){
				num*=10;
				shownums[i]=smg_num[(int)num];
				num-=(int)num;//减掉整数部分
			}
		}
	}

}

//在左边显示一个数字，（这个还没加负数的功能）,数码管左四位显示
void smg_shownum_left(int num){
	if(num==0){
		shownums[3]=smg_num[0];//第7位显示0
		uint8_t i; 
		for (i = 0; i <= 2; i++) shownums[i]=0;//其他位都不显示
	}
	else{
		uint8_t i; 
		for (i = 1; i <= 4&&num!=0; i++) {//前几位取出数字然后显示
			shownums[4-i]=smg_num[num%10];
			num /= 10;
		}
		for (; i <= 4; i++) shownums[4-i]=0;//其他位不显示
	}
}

//在右边显示一个数字，（这个还没加负数的功能）数码管右四位显示
void smg_shownum_right(int num){
	if(num==0){
		shownums[7]=smg_num[0];//第7位显示0
		uint8_t i; 
		for (i = 4; i <= 6; i++) shownums[i]=0;//其他位都不显示
	}
	else{
		uint8_t i; 
		for (i = 1; i <= 4&&num!=0; i++) {//前几位取出数字然后显示
			shownums[8-i]=smg_num[num%10];
			num /= 10;
		}
		for (; i <= 4; i++) shownums[8-i]=0;//其他位不显示
	}
}
void smg_clear_screen()
{
	for(int i=0;i<8;i++)
	{
	shownums[i]=0x00;
	
	}
}
void smg_start(){
	for(int i=0;i<4;i++){
		shownums[7-i]=0xfc;
	}
}
//1~9999
int temp;
void smg_add(){
		if(m<10000){//刷新1
			smg_showint(m);
		}
		for(int j=4;j<8;j++){//刷新2
			if(shownums[j]==0){
				shownums[j]=0xfc;
			} 

		}
	HAL_Delay(10);//刷新1和刷新2太快了，数码管会频闪，延迟可消除	
}

