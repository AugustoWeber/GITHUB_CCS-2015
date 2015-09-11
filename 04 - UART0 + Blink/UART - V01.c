/*******************************************************
 * Autor: Augusto Gouvï¿½a Weber
 *
 * Data: 20/Ago/2015
 *
 * Description:
 * 	A Simple program to Turn on the blue led when a UART
 * 	signal are recived and a red led when send.
 */

/*******************************************************
 * Includes
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"

/******************************************************
 * Global Variables
 */

//#define GPIO_LOCK_KEY   0x4C4F434B  // Unlocks the GPIO_CR register
#define SW1			GPIO_PIN_4
#define SW2			GPIO_PIN_0
#define LED			GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3
#define	RED			GPIO_PIN_1
#define GREEN		GPIO_PIN_2
#define BLUE		GPIO_PIN_3
#define TimeDelay	333 		// Time in miliseconds
#define DebounceDl	10			// Time in ms to Debaunce Dellay
#define PeriodVar	20
#define RX0			GPIO_PIN_0
#define	TX0			GPIO_PIN_1
#define RX1			GPIO_PIN_0
#define TX1			GPIO_PIN_1
#define RX2			GPIO_PIN_6
#define TX2			GPIO_PIN_7
#define RX3			GPIO_PIN_6
#define TX3			GPIO_PIN_7
#define RX4			GPIO_PIN_4
#define TX4			GPIO_PIN_5
#define RX5			GPIO_PIN_4
#define TX5			GPIO_PIN_5
#define RX6			GPIO_PIN_4
#define TX6			GPIO_PIN_5
#define RX7			GPIO_PIN_4
#define TX7			GPIO_PIN_5


uint32_t 			Led;		// The color to turn On 2, 4, 8

uint8_t				red_pwm;
uint8_t				green_pwm;
uint8_t				blue_pwm;

/******************************************************
 * Function Prototypes
 */
void Clock_Init(void);
void LED_Init(void);
void mDelay(uint32_t mSec);
void IntSWHandler(void); // Interruption
void UART_Init(void);
void UART_Enable(int x);
void UART0Handler(void);
void UART1Handler(void);
void UART2Handler(void);
void UART3Handler(void);
void UART4Handler(void);
void UART5Handler(void);
void UART6Handler(void);
void UART7Handler(void);
void UARTProcessRxChar(void);
void UARTSend(const uint8_t *pui8Buffer, uint32_t ui32Count);

/******************************************************
 * Clock Config
 */
void Clock_Init(void){
	//
	// Enable lazy stacking for interrupt handlers. This allows floating-point
	// instructions to be used within interrupt handlers, but at the expense of
	// extra stack usage.
	//
	FPUEnable();
	FPULazyStackingEnable();

	//
	// Set the clocking
	//
	SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_INT | SYSCTL_XTAL_16MHZ);
}

/******************************************************
 * LED Config
 */
void LED_Init(){
	// Set GIPO Port F
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

	// Set GPIO Pins 1, 2 and 3 as Output
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, LED);

	// Ascende cada LED por aprox 1s e depois apaga.
	GPIOPinWrite(GPIO_PORTF_BASE, LED, 2);
	mDelay(TimeDelay);
	GPIOPinWrite(GPIO_PORTF_BASE, LED, 4);
	mDelay(TimeDelay);
	GPIOPinWrite(GPIO_PORTF_BASE, LED, 8);
	mDelay(TimeDelay);
	GPIOPinWrite(GPIO_PORTF_BASE, LED, 0);
}


/******************************************************
 * Delay
 */
void mDelay(uint32_t mSec){
	//
	// Delay 100ms
	// Num clk over 1 sec = SysCtlClockGet()/3
	SysCtlDelay(mSec*(SysCtlClockGet()/(3*1000)));
}

/******************************************************
 * UART - RX - TX - TEM NA PLACA
 *
 * UART0 - A0 - A1 - USB
 * UART1 - B0 - B1 - OK
 * UART2 - D6 - D7 - OK
 * UART3 - C6 - C7 - OK
 * UART4 - C4 - C5 - OK
 * UART5 - E4 - E5 - OK
 * UART6 - D4 - D5 - NO PINS
 * UART7 - E0 - E1 - NO PINS
 */
void UART_Init(){

	// Set UART 0
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

	// Set GPIO A0 and A1 as UART pins.
	GPIOPinConfigure(GPIO_PA0_U0RX);
	GPIOPinConfigure(GPIO_PA1_U0TX);
	GPIOPinTypeUART(GPIO_PORTA_BASE, RX0 | TX0);

	// Set configuration: Baud rate 115200, 8 data bits, 1 stop bit, no parity
	UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
			UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);

	// Enable the UART interrupt.
	IntEnable(INT_UART0);
	UARTFIFOEnable(UART0_BASE);
	UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_TX);

}
/******************************************************
 * UART 1 to 7 select witch will be enabled
 */
void UART_Enable(int x){/*
	if(x > 0 && x < 8){
		switch(x){
		case 1:	// UART1
			//UARTDisable(1);
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
			GPIOPinConfigure(GPIO_PB0_U1RX);
			GPIOPinConfigure(GPIO_PB1_U1TX);
			//GPIOPinTypeUART(GPIO_PORTB_BASE, RX1 | TX1);
			//UARTEnable()
			UARTClockSourceSet(UART1_BASE, UART_CLOCK_PIOSC);
			SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
			break;

		case 2: // UART2
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
			GPIOPinConfigure(GPIO_PD6_U2RX);
			GPIOPinConfigure(GPIO_PD7_U2TX);
			GPIOPinTypeUART(GPIO_PORTD_BASE, RX2 | TX2);
			break;

		case 3: // UART3
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
			GPIOPinConfigure(GPIO_PC6_U3RX);
			GPIOPinConfigure(GPIO_PC7_U3TX);
			GPIOPinTypeUART(GPIO_PORTE_BASE, RX3 | TX3);
			break;

		case 4: // UART4
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
			GPIOPinConfigure(GPIO_PC4_U4RX);
			GPIOPinConfigure(GPIO_PC5_U4TX);
			GPIOPinTypeUART(GPIO_PORTE_BASE, RX4 | TX4);
			break;

		case 5: // UART5
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
			GPIOPinConfigure(GPIO_PE4_U5RX);
			GPIOPinConfigure(GPIO_PE5_U5TX);
			GPIOPinTypeUART(GPIO_PORTE_BASE, RX5 | TX5);
			break;

		case 6: // UART6
		case 7: // UART7
		default:
			break;
		}
	}else{
		// Erro de parâmetro
	}*/
}

/******************************************************
 * Send a string to the UART.
 */

void UARTSend(const uint8_t *pui8Buffer, uint32_t ui32Count){
	//
	// Loop while there are more characters to send.
	//
	while(ui32Count--)
	{
		//
		// Write the next character to the UART.
		//
		UARTCharPutNonBlocking(UART0_BASE, *pui8Buffer++);
	}
}

void ProcessRxChar(){

}

/******************************************************
 * UART 0 to 7 Interruption treatment
 */
void UART0Handler(){

	uint32_t IntU0Status;

	// Get the interrrupt status.
	IntU0Status = UARTIntStatus(UART0_BASE, true);

	// Clear the asserted interrupts.
	UARTIntClear(UART0_BASE, IntU0Status);

	// Loop while there are characters in the receive FIFO.
	while(UARTCharsAvail(UART0_BASE))
	{
		// Read the next character from the UART and write it back to the UART.
		UARTCharPutNonBlocking(UART0_BASE, UARTCharGetNonBlocking(UART0_BASE));

		// Blink the LED to show a character transfer is occuring.
		GPIOPinWrite(GPIO_PORTF_BASE, LED, BLUE);

		// Delay for 1 millisecond.
		mDelay(1);

		// Turn off the LED
		GPIOPinWrite(GPIO_PORTF_BASE, LED, 0);
	}
}
void UART1Handler(){

}
void UART2Handler(){

}
void UART3Handler(){

}
void UART4Handler(){

}
void UART5Handler(){

}
void UART6Handler(){

}
void UART7Handler(){

}

/******************************************************
 * SW interruption treatment
 */
void IntSWHandler(){
	uint32_t status=0;

	status = GPIOIntStatus(GPIO_PORTF_BASE,true);
	// Clear the interrupt
	GPIOIntClear(GPIO_PORTF_BASE, SW1 | SW2);
	// Pressed SW1
	if((status & GPIO_INT_PIN_4) == GPIO_INT_PIN_4){
		// Led off

	}
	// Pressed SW2 - Next Color
	if((status & GPIO_INT_PIN_0) == GPIO_INT_PIN_0){
		//GPIOPinWrite(GPIO_PORTF_BASE, LED , 0);

	}
}



/******************************************************
 * MAIN
 */
void main(void) {
	//int i;

	// INITIALIZATION
	Clock_Init();
	IntMasterEnable();
	LED_Init();
	UART_Init();
	/*for(i = 1; i < 6; i++){
		UART_Enable(i);
	}*/

	// LOOP
	while(1){
	}
}
