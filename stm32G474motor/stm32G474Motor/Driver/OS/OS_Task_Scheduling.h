#ifndef __OS_TASK_SCHEDULING_H__
#define __OS_TASK_SCHEDULING_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include "stdint.h"
#include "stm32g4xx.h"                  // Device header
#include "app.h"
#include "OS_Task_Scheduling.h"



    typedef enum
    {
        OS_TASK0,
        OS_TASK1,
        OS_TASK2,
        OS_TASK3,
        OS_TASK4,
        OS_TASK5,
        OS_TASK6,
        OS_TASK7,
        OS_TASK8,
        OS_TASK9,
        OS_TASK10,
        OS_TASK11,
        OS_TASK12,
        OS_TASK13,
        OS_TASK14,
        OS_TASK15,
        OS_TASK_SUM
    } OS_TaskIDTypeDef;

    typedef enum
    {
        OS_TASK_SLEEP,
        OS_TASK_RUN = !OS_TASK_SLEEP
    } OS_TaskStatusTypeDef;

    typedef struct
    {
        OS_TaskStatusTypeDef RunState; 
        uint16_t Timer;                 
        uint16_t ItvTime;              
        void (*TaskHook)(void);        
    } OS_Task_RR_TypeDef;

    void OS_TaskInit(void);
    void OS_TaskCreat(uint8_t ID, void (*TaskHook)(void), uint16_t ItvTime, uint16_t Timer, OS_TaskStatusTypeDef RunState);
    void OS_TaskStart(void);
    void OS_Task_TimerCallback(void);

#ifdef __cplusplus
}
#endif
	
#endif // __OS_TASK_SCHEDULING_H__
