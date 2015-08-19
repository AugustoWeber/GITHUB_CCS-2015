/*******************************************************
 * Autor: Augusto Gouvêa Weber
 *
 * Data: 29/jul/2015
 *
 * Description:
 * 	A Simple program to Turn on the led on and off after a time
 */

/*******************************************************
 * Includes
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/tm4c123gh6pm.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

/******************************************************
 * Global Variables
 */

#define Step_timmer		0xFFFFFFFF





/******************************************************
 * Clock Config
 */
void Clock_Init(void){
	//
	// Enable lazy stacking for interrupt handlers. This allows floating-point
	// instructions to be used within interrupt handlers, but at the expense of
	// extra stack usage.
	//
	ROM_FPULazyStackingEnable();

	//
	// Set the clocking
	//
	ROM_SysCtlClockSet(SYSCTL_SYSDIV_64 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
}


/******************************************************
 * Delay
 */

/******************************************************
 * Main
 */
int main(void) {
	uint32_t Aux32_1;
	Clock_Init();

	//
	// Enable the GPIO port that is used for the on-board LED.
	//
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;

	//
	// Do a dummy read to insert a few cycles after enabling the peripheral.
	//
	Aux32_1 = SYSCTL_RCGC2_R;
	Aux32_1 = SysCtlClockGet();
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	ROM_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);

	//
	// Loop
	//
	while(1){

		//
		// Turn on LED
		//
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);

		//
		// Delay 100ms
		// Num clk over 1 sec = SysCtlClockGet()/3
		SysCtlDelay((SysCtlClockGet()/3)/3);

		//
		// Turn off LED
		//
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);

		//
		// Delay 100ms
		//
		SysCtlDelay((SysCtlClockGet()/3)/3);


		//
		// Turn off LED
		//
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);

		//
		// Delay 100ms
		//
		SysCtlDelay((SysCtlClockGet()/3)/3);
	}
}
