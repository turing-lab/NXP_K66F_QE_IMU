#define ARM_MATH_CM4
#include "MK66F18.h"                    // Device header
#include "arm_math.h"                   // ARM::CMSIS:
#include "LEDs.h"
#include "QE_Driver.h"
#include "PIT.h"

/*
ADCC trigger enabled and sources on SIM->SOPT7 
*/

uint16_t ticks1 = 0;
uint16_t ticks2 = 0;
int64_t steps = 0;
uint8_t flag1 = 0;
uint8_t flag2 = 0;
volatile uint8_t TOF;
volatile uint8_t TOFDIR;
volatile uint8_t QUADIR;

QuadratureEncoder QEI_L;
QuadratureEncoder QEI_R;

int main(void){
	
	SystemCoreClockUpdate();
	LEDs_Init();
	QEI_Init(&QEI_L,1);
	QEI_Init(&QEI_R,2);
	PIT_Init(10);
	
	while(1){
		steps = QEI_L.steps;
	}
}

void PIT0_IRQHandler(void){
	PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;
	LED_Toggle(1);
	QEI_Process(&QEI_L,1);
	QEI_Process(&QEI_R,2);
}
