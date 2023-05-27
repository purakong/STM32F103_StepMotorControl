#include "sys/_stdint.h"

typedef struct
{
	volatile uint32_t CTRL;                   /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
	volatile uint32_t LOAD;                   /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register */
	volatile uint32_t VAL;                    /*!< Offset: 0x008 (R/W)  SysTick Current Value Register */
	volatile const  uint32_t CALIB;                  /*!< Offset: 0x00C (R/ )  SysTick Calibration Register */
} User_sysTick_Type;

#define USER_SCS_BASE            (0xE000E000UL)                            /*!< System Control Space Base Address */

#define USER_SysTick_BASE        (USER_SCS_BASE +  0x0010UL)                    /*!< SysTick Base Address */

#define SYSTICK_LOAD_10MS_VAL	(640000U)
#define SYSTICK_LOAD_MS_VAL		(64000U)
#define SYSTICK_LOAD_US_VAL		(64U)

#define SYSTICK_EN				(1U << 0)
#define SYSTICK_CLK_SRC			(1U << 2)
#define SYSTICK_COUNT_FLAG		(1U << 16)
#define SYSTICK_INT				(1U << 1)

#define USER_SysTick             ((User_sysTick_Type   *)     USER_SysTick_BASE  )   /*!< SysTick configuration struct */

extern void delayUs(uint32_t delay_us);
extern void delayMs(uint32_t delay_ms);
extern void SysTimerSetting(void);

