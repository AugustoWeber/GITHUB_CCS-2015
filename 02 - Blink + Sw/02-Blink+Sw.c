/*******************************************************
 * Autor: Augusto Gouv�a Weber
 *
 * Data: 29/jul/2015
 *
 * Description:
 * 	A Simple program to Turn on the led on and off after a time
 * 	When Sw1 pressed the frequency will slow. If Sw2 was pressed,
 * 	the frequency will increase, if both ware pressed, the frequency
 * 	will return to default value.
 */

/*******************************************************
 * Includes
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_nvic.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"



/******************************************************
 * Global Variables
 */

//#define GPIO_LOCK_KEY   0x4C4F434B  // Unlocks the GPIO_CR register
#define SW1			GPIO_PIN_4
#define SW2			GPIO_PIN_0
#define LED			GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3
#define TimeDelay	333 		// Time in miliseconds
#define DebounceDl	10			// Time in ms to Debaunce Dellay
#define PeriodVar	20

uint32_t			Period;		// The period of the led on
uint32_t 			Led;		// The color to turn On 2, 4, 8

//volatile uint32_t   VectorNumber;
//volatile uint32_t 	Vec_SWHandler;

/******************************************************
 * Function Prototypes
 */
void Clock_Init(void);
void mDelay(uint32_t mSec);
void IntSWHandler(void);

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
 * Delay
 */
void mDelay(uint32_t mSec){
	//
	// Delay 100ms
	// Num clk over 1 sec = SysCtlClockGet()/3
	SysCtlDelay(mSec*((SysCtlClockGet()/3)/1000));
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives an unexpected
// interrupt from the Switcher.  This simply change the value os the Period
// acording witch buttom was pressed.
//
//*****************************************************************************
void IntSWHandler(void){
	uint32_t status=0;

	status = GPIOIntStatus(GPIO_PORTF_BASE,true);
	// Clear the interrupt
	GPIOIntClear(GPIO_PORTF_BASE, SW1 | SW2);
	// Pressed SW1
	if( (status & GPIO_INT_PIN_4) == GPIO_INT_PIN_4){
		// Led off
		GPIOPinWrite(GPIO_PORTF_BASE, LED, 0);
		mDelay(3 * Period);
		Led = 2;
	}
	// Pressed SW2 - Next Color
	if( (status & GPIO_INT_PIN_0) == GPIO_INT_PIN_0){
		//GPIOPinWrite(GPIO_PORTF_BASE, LED , 0);
		if(Led == 8){
			Led = 2;
		}else{
			Led=Led*2;
		}
	}


}



/******************************************************
 * Main
 */
int main(void) {
	Clock_Init();

	// Set GIPO Port F
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	// Set GPIO Pins 1, 2 and 3 as Output
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, LED);
	//
	// Set GPIO Pins Sw1 and Sw2 as Input
	//
	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, SW1);
	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, SW2);
	// First open the lock and select the bits we want to modify in the GPIO commit register.
	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
	HWREG(GPIO_PORTF_BASE + GPIO_O_CR) = 0x1;
	// Now modify the configuration of the pins that we unlocked.

	// Enable Weak Pullup Resistor for SW1 and SW2
	GPIOPadConfigSet(GPIO_PORTF_BASE, SW1, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	GPIOPadConfigSet(GPIO_PORTF_BASE, SW2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

	//
	//Enable interrupts for SW1 and SW2
	//
	GPIOIntDisable(GPIO_PORTF_BASE, GPIO_INT_PIN_4);
	GPIOIntDisable(GPIO_PORTF_BASE, GPIO_INT_PIN_0);
	GPIOIntClear(GPIO_PORTF_BASE, GPIO_INT_PIN_0 | GPIO_INT_PIN_4);
	GPIOIntRegister(GPIO_PORTF_BASE, IntSWHandler);
	GPIOIntTypeSet(GPIO_PORTF_BASE, SW1, GPIO_FALLING_EDGE);
	GPIOIntTypeSet(GPIO_PORTF_BASE, SW2, GPIO_BOTH_EDGES);
	GPIOIntEnable(GPIO_PORTF_BASE, SW1 | SW2);

	//
	// Setting Period color on
	//
	Period = TimeDelay;

	//
	// Led On
	//
	Led = 2;
	//
	// Loop
	//
	while(1){

		//
		// Delay
		//
		mDelay(Period);

		//
		// Turn off LED
		//
		GPIOPinWrite(GPIO_PORTF_BASE, LED , 0);
		GPIOPinWrite(GPIO_PORTF_BASE, LED, Led);

		if(Led == 2){
			Led = 8;
		}else{
			Led=Led/2;
		}
	}
}
