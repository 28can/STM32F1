#include "main.h"
////74HC138操作线
#define LED_A0(val) HAL_GPIO_WritePin(GPIOC,GPIO_PIN_10,(GPIO_PinState)val) //A0地址线
#define LED_A1(val) HAL_GPIO_WritePin(GPIOC,GPIO_PIN_11,(GPIO_PinState)val) //A1地址线
#define LED_A2(val) HAL_GPIO_WritePin(GPIOC,GPIO_PIN_12,(GPIO_PinState)val) //A2地址线

////74HC595操作线
#define LED_DS(val)		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,(GPIO_PinState)val) //数据线
#define LED_LCLK(val)	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,(GPIO_PinState)val) //锁存时钟线
#define LED_SCK(val)	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,(GPIO_PinState)val) //时钟线

extern uint8_t shownums[8];
extern uint8_t smg_num[];
void LED_Refresh(void);
void LED_Write_Data(uint8_t duan,uint8_t wei);
void smg_showint(int num);
void for_delay_us(uint32_t nus);
void smg_addled(uint8_t duan,uint8_t wei);
void smg_showfloat(double num);
void smg_shownum_left(int num);
void smg_shownum_right(int num);
void smg_clear_screen();
void smg_start();
void smg_add();