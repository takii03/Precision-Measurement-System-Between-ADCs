#include <stdint.h>
#include <stdio.h>

void USART2_SendChar(char ch);
void Delay(uint32_t count);

// Address of bus domain
#define AHB1_BASEADDR		0x40020000UL
#define APB1_BASEADDR		0x40000000UL
#define APB2_BASEADDR		0x40010000UL

//Clock address
#define RCC_EN_ADDR			0x40023800UL
#define RCC_CLKEN_AHB1		(RCC_EN_ADDR+0x0030UL)
#define RCC_CLKEN_APB1		(RCC_EN_ADDR+0x0040UL)
#define RCC_CLKEN_APB2		(RCC_EN_ADDR+0x0044UL)


//GPIOx base address
#define GPIOA_BASE_ADDR		0x40020000UL

//
#define ADC1_BASEADDR		0x40012000UL
#define USART2_BASEADDR		0x40004400UL
#define DAC_BASEADDR		0x40007400UL

//GPIOA address
#define GPIOA_MODER			(GPIOA_BASE_ADDR+0x0000UL)
#define GPIOA_PUPDR			(GPIOA_BASE_ADDR+0x000CUL)
#define GPIOA_AFRL			(GPIOA_BASE_ADDR+0x0020UL)

//ADC Address
#define ADC_SR 				(ADC1_BASEADDR+0x0000UL)
#define ADC_DR				(ADC1_BASEADDR+0x004CUL)
#define ADC_CR2				(ADC1_BASEADDR+0x0008UL)
#define ADC_SMPR2			(ADC1_BASEADDR+0x0010UL)
#define ADC_SQR1			(ADC1_BASEADDR+0x002CUL)
#define ADC_SQR3			(ADC1_BASEADDR+0x0034UL)

//USART Address
#define USART_CR1			(USART2_BASEADDR+0x000CUL)
#define USART_SR			(USART2_BASEADDR+0x0000UL)
#define USART_DR			(USART2_BASEADDR+0x0004UL)
#define USART_BRR			(USART2_BASEADDR+0x0008UL)

//DAC Address
#define DAC_CR 				(DAC_BASEADDR+0x0000UL)
#define DAC_DHR12R1			(DAC_BASEADDR+0x0008UL)
#define DAC_DOR1			(DAC_BASEADDR+0x002CUL)


int main(void)
{
	//RCC CLOCK enable
	*(uint32_t*)RCC_CLKEN_AHB1 |=(1<<0);
	*(uint32_t*)RCC_CLKEN_APB1 |=(1<<17);
	*(uint32_t*)RCC_CLKEN_APB1 |=(1<<29);
	*(uint32_t*)RCC_CLKEN_APB2 |=(1<<8);

//GPIOA
	*(volatile uint32_t*)GPIOA_MODER |= (3 << 2);
	*(volatile uint32_t*)GPIOA_MODER |= (2 << 4);
	*(volatile uint32_t*)GPIOA_MODER |= (2 << 6);
	*(volatile uint32_t*)GPIOA_MODER |= (3 << 8);

	//Alternate Function
	*(volatile uint32_t*)GPIOA_AFRL |= (7 << 8);
	*(volatile uint32_t*)GPIOA_AFRL |= (7 << 12);

	//Pull - Push
	*(volatile uint32_t*)GPIOA_PUPDR |= (1 << 6);   //For the RX

//ADC
	*(volatile uint32_t*)ADC_CR2 |= (1 << 0);

	//Sample time selection
	*(volatile uint32_t*)ADC_SMPR2 |= (7 << 3);

	*(volatile uint32_t*)ADC_SQR1 &= ~(0xF << 20);   //1 conversion

	*(volatile uint32_t*)ADC_SQR3 &= ~(0x1F);   //clear
	*(volatile uint32_t*)ADC_SQR3 |= (1 << 0);  //set


//USART
	*(volatile uint32_t*)USART_CR1 |= (1<<3);    // Transmitter enable
	*(volatile uint32_t*)USART_CR1 |= (1<<13);   // USART enable
	*(volatile uint32_t*)USART_CR1 |= (1<<2);    // Receiver enable

	//Baud Rate Register
	*(volatile uint32_t*)USART_BRR = 0x8B;


//DAC
	*(volatile uint32_t*)DAC_CR |= (1 << 0);  //enable the DAC


//    uint32_t dac = 0;


	while(1){

//		*(volatile uint32_t*)DAC_DHR12R1 = dac;  //for test

		*(volatile uint32_t*)ADC_CR2 |= (1 << 30);

		while((*(volatile uint32_t*)ADC_SR & 0x02) == 0);  //Wait until ADC conversion completes

		uint16_t adc = *(volatile uint32_t*)ADC_DR;

		float voltage = (adc * 3.3f) / 4095.0f;

		printf("ADC = %u            Voltage = %.2f V\r\n", adc, voltage);

//		dac += 100;
//		if(dac>4065)
//			dac=0; 

		Delay(1000000);


	}

}

void USART2_SendChar(char ch)
{
    while((*(volatile uint32_t*)USART_SR & (1 << 7)) == 0);

    *(volatile uint32_t*)USART_DR = ch;
}

void Delay(uint32_t count){
	volatile uint32_t i;
	for(i=0;i<count;i++);
}
