#include "../../Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xb.h"
#include "../../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_ll_gpio.h"
#include "sys/_stdint.h"
#include "../Inc/stepMotor/stepMotor.h"
#include "../Inc/sys/systick.h"

uint16_t vStepAngle;
uint8_t vStepCurrentPhase;
uint8_t vStep_StartFlag;

/* Step Motor NK243-01AT Property */
/* VOLTAGE : 4V
 * CURRENT : 0.95A (A/Phase)
 * STEP ANGLE : 1.8
 * METHOD : UNIPOLAR (6 Lead)
 * Full Step : 360/1.8 = 200 (Step)
 */

void StepMotor_SetStartFlag(uint8_t flag)
{
	vStep_StartFlag = flag;
}

void StepMotor_Init(void)
{
	vStepCurrentPhase = STEP_POS_PHASEA;
	vStepAngle = 0;
}

void StepMotor_ProcessPhase(uint8_t curPhase)
{
	switch(curPhase)
	{
	case STEP_POS_PHASEA:
		LL_GPIO_WriteOutputPort(GPIOC, GPIOC_StepPhaseB);
		vStepCurrentPhase = STEP_POS_PHASEB;
		break;
	case STEP_POS_PHASEB:
		LL_GPIO_WriteOutputPort(GPIOC, GPIOC_StepPhaseNA);
		vStepCurrentPhase = STEP_POS_PHASENA;
		break;
	case STEP_POS_PHASENA:
		LL_GPIO_WriteOutputPort(GPIOC, GPIOC_StepPhaseNB);
		vStepCurrentPhase = STEP_POS_PHASENB;
		break;
	case STEP_POS_PHASENB:
		LL_GPIO_WriteOutputPort(GPIOC, GPIOC_StepPhaseA);
		vStepCurrentPhase = STEP_POS_PHASEA;
		break;
	}
}

void StepMotor_SetMotorAngle(uint16_t angle, uint32_t stepHz)
{
	uint16_t step;
	uint32_t period;

	step = (uint16_t)(((float)angle / STEP_ANGLE) + 0.5);
	period = (uint32_t)(((1.0 / (float)stepHz) * 1000000.0)/4.0);

	for(uint16_t count = 0; count <step; count++)
	{
		StepMotor_ProcessPhase(vStepCurrentPhase);
		delayUs(period);
	}
	stepMotor_Set_Angle(0);
}

void StepMotor_Speed(uint32_t stepHz)
{
	uint32_t period;

	period = (uint32_t)(((1.0 / (float)stepHz) * 1000000.0)/4.0);
	LL_GPIO_WriteOutputPort(GPIOC, STEP_MOTOR_1);
	delayUs(period);
	LL_GPIO_WriteOutputPort(GPIOC, STEP_MOTOR_2);
	delayUs(period);
	LL_GPIO_WriteOutputPort(GPIOC, STEP_MOTOR_3);
	delayUs(period);
	LL_GPIO_WriteOutputPort(GPIOC, STEP_MOTOR_4);
	delayUs(period);
}

void StepMotor_OnePhase_Speed(uint32_t stepHz)
{
	uint32_t period;

	period = (uint32_t)(((1.0 / (float)stepHz) * 1000000.0)/4.0);
	LL_GPIO_WriteOutputPort(GPIOC, GPIOC_StepPhaseA);
	delayUs(period);
	LL_GPIO_WriteOutputPort(GPIOC, GPIOC_StepPhaseB);
	delayUs(period);
	LL_GPIO_WriteOutputPort(GPIOC, GPIOC_StepPhaseNA);
	delayUs(period);
	LL_GPIO_WriteOutputPort(GPIOC, GPIOC_StepPhaseNB);
	delayUs(period);

}

void stepMotor_Set_Angle(uint16_t angle)
{
	vStepAngle = angle;
}

