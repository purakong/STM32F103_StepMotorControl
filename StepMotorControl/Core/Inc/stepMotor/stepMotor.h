#include "sys/_stdint.h"

#define GPIOC_StepEnA		(1<<2U)
#define GPIOC_StepEnB		(1<<3U)

#define GPIOC_StepPhaseA	(1<<6U)
#define GPIOC_StepPhaseB	(1<<7U)
#define GPIOC_StepPhaseNA	(1<<8U)
#define GPIOC_StepPhaseNB	(1<<9U)

#define STEP_POS_PHASEA		(1U)
#define STEP_POS_PHASEB		(2U)
#define STEP_POS_PHASENA	(3U)
#define STEP_POS_PHASENB	(4U)

//A Phase is high, the others is low
#define STEP_MOTOR_1		(GPIOC_StepPhaseB | GPIOC_StepPhaseNA | GPIOC_StepPhaseNB)
#define STEP_MOTOR_2		(GPIOC_StepPhaseA | GPIOC_StepPhaseNA | GPIOC_StepPhaseNB)
#define STEP_MOTOR_3		(GPIOC_StepPhaseA | GPIOC_StepPhaseB  | GPIOC_StepPhaseNB)
#define STEP_MOTOR_4		(GPIOC_StepPhaseB | GPIOC_StepPhaseNA | GPIOC_StepPhaseA)

#define STEP_ANGLE			(1.8f)

extern void StepMotor_OnePhase_Speed(uint32_t stepHz);
extern void stepMotor_Speed(uint32_t stepHz);
extern void stepMotor_Set_Angle(uint16_t angle);
extern void StepMotor_SetMotorAngle(uint16_t angle, uint32_t stepHz);
extern void StepMotor_SetStartFlag(uint8_t flag);
