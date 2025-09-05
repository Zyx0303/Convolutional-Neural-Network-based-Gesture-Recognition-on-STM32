#ifndef __EXIT_H
#define __EXIT_H

void Exit_Init(void);
void KeyStatue_Trun(void);
void EXTI0_IRQHandler (void);
void EXTI2_IRQHandler (void);
void Process_EXTI0_Event(void);
void Process_EXTI2_Event(void);
#endif