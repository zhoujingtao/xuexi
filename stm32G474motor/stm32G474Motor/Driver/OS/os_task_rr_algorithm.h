/*******************************************************************************
 * LIC *
 ******************************************************************************/

#ifndef __OS_TASK_RR_ALGORITHM_H__
#define __OS_TASK_RR_ALGORITHM_H__

#ifdef __cplusplus
extern "C"
{
#endif

#define CTASK_SUPPORT_NUM 3
//#include "main.h"

#include <string.h>


    typedef enum
    {
        OS_TASK_UNUSED = 0,
        OS_TASK_USED = !OS_TASK_UNUSED
    } OS_TASKUSED;
    typedef enum
    {
        OS_TASK_SLEEP,
        OS_TASK_RUN = !OS_TASK_SLEEP
    } OS_TASKSTATUS;

    typedef enum
    {
        OS_PRIORITIES_LEVEL_1 = 1,
        OS_PRIORITIES_LEVEL_2 = 2,
        OS_PRIORITIES_LEVEL_3 = 3,
        OS_PRIORITIES_LEVEL_4 = 4,
        OS_PRIORITIES_LEVEL_5 = 5,
        OS_PRIORITIES_LEVEL_6 = 6,
        OS_PRIORITIES_LEVEL_7 = 7,
        OS_PRIORITIES_LEVEL_8 = 8,
        OS_PRIORITIES_LEVEL_9 = 9,
        OS_PRIORITIES_LEVEL_10 = 10,
        OS_PRIORITIES_LEVEL_NONE = 255,
    } OS_PRIORITIES_LEVEL;

    typedef struct
    {
        OS_TASKUSED IsUsed;
        OS_TASKSTATUS RunState;
        char *TaskName;
        uint8_t priority;
        uint16_t Timer;
        uint16_t ItvTime;
        void (*TaskHook)(void);
    } OS_TASK_RR_COMPONENTS;

    typedef void (*TaskCallBack)(void);

    void OS_TaskInit(void);

    void OS_TaskIsrCreat(void (*TaskHook)(void), uint16_t Timer);
    void OS_TaskIsrVacant(void (*TaskHook)(void));

    void OS_TaskCreat(char *name_ptr, void (*TaskHook)(void), uint16_t Timer, uint8_t priority);
    void OS_TaskVacant(void (*TaskHook)(void));

    void OS_TASK_Start(void);
    void OS_Task_TimerCallback(void);

    void OS_Task_IdleCallback(TaskCallBack TaskHook);

#ifdef __cplusplus
}
#endif

#endif /* __OS_TASK_RR_ALGORITHM_H__ */

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
