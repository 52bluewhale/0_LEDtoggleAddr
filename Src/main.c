/*to turn on the LED, the question is
 * Where is the LED connected?
 * Port:	A
 * Pin:		5
*/
#define PERIPH_BASE				(0x40000000UL)

#define AHB1_PERIPH_OFFSET		(0x00020000UL)
#define AHB1_PERIPH_BASE		(PERIPH_BASE + AHB1_PERIPH_OFFSET)

#define GPIO_A_OFFSET			(0x0000UL)
#define GPIO_A_BASE				(AHB1_PERIPH_BASE + GPIO_A_OFFSET)

#define RCC_OFFSET				(0x3800UL)
#define RCC_BASE				(AHB1_PERIPH_BASE + RCC_OFFSET)

#define AHB1_EN_R_OFFSET		(0x30UL)
#define RCC_AHB1_EN_R			(*(volatile unsigned int *)(RCC_BASE + AHB1_EN_R_OFFSET))

#define GPIO_A_EN				(1U<<0)	//0x0000 0000 0000 0000 0000 0000 0000 0001

#define MODE_R_OFFSET			(0x00UL)
#define GPIO_A_MODE_R			(*(volatile unsigned int *)(GPIO_A_BASE + MODE_R_OFFSET))

#define OD_R_OFFSET				(0x14UL)
#define GPIO_A_OD_R				(*(volatile unsigned int *)(GPIO_A_BASE + OD_R_OFFSET))

#define PIN_5					(1U<<5)
#define LED_PIN					PIN_5

/*
 * (1U<<10) >>>>>>set bit 10 to 1
 * &=~(1U<<11) >>>set bit 11 to 0
 */

/*
 * avoid FRIENDLY FIRE while configuring the RCC_AHB1_EN_R:
 * what if we already had the content of the RCC_AHB1_EN_R like this
 *
 * RCC_AHB1_EN_R = 0x0000 0000 0000 0000 1000 1111 0000 0000
 *
 * and we only want to change the value of bit[0] of the register to 1
 * if we said that:
 * 		RCC_AHB1_EN_R = GPIO_A_EN;
 * it will clear all the content of the register
 *
 * so, we have to use OR operator in order to remain the content of the register:
 * 		RCC_AHB1_EN_R |= GPIO_A_EN;
 *
 * */

int main(void)
{
	/*1. Enable clock for GPIO A*/
	RCC_AHB1_EN_R |= GPIO_A_EN;

	/*2. Set PA5 as output pin*/
	GPIO_A_MODE_R |= (1U<<10);
	GPIO_A_MODE_R &= ~(1U<<11);

	while(1)
	{
		/*3. Set PA5 high*/
		//GPIO_A_OD_R |= LED_PIN;
		/*4. Toggle PA5*/
		GPIO_A_OD_R ^= LED_PIN;
		for (int i=0; i<500000; ++i)
		{

		}
	}
}
