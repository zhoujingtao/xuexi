#include "OS_Task_Scheduling.h"

volatile OS_Task_RR_TypeDef TaskComps[OS_TASK_SUM];

void OS_TaskCreat(uint8_t ID, void (*TaskHook)(void), uint16_t ItvTime, uint16_t Timer, OS_TaskStatusTypeDef RunState);


void OS_Task1(void)
{
//    led_toggle(led_net_blue);
}

void OS_Task2(void)
{
//    led_toggle(led_net_greener);
}

void OS_Task3(void)
{
//		led_toggle(led_pow_blue);
}

void OS_Task4(void)
{
		app_TransducersData_process();
}

void OS_Task5(void)
{
		key_process();
}

void OS_Task6(void)
{

}

void OS_Task7(void)
{

}


void OS_Task8(void)
{

}

void OS_Task9(void)
{

}

void OS_Task10(void)
{

}

void OS_Task11(void)
{

}

void OS_Task12(void)
{

}



/**
 * @brief  Initializes the task scheduler
 * @param  None
 * @retval None
 * @note   This function should be called before creating any task
 */
void OS_TaskInit(void)
{
    for (uint8_t i = 0; i < OS_TASK_SUM; i++)
    {
        TaskComps[i].ItvTime = 0;
        TaskComps[i].TaskHook = NULL;
        TaskComps[i].Timer = 0;
        TaskComps[i].RunState = OS_TASK_SLEEP;
    }

    OS_TaskCreat(OS_TASK0,OS_Task1, 1000, 1000, OS_TASK_RUN);
    OS_TaskCreat(OS_TASK1,OS_Task2, 1000, 1000, OS_TASK_RUN);
    OS_TaskCreat(OS_TASK2,OS_Task3, 1000, 1000, OS_TASK_RUN);
    OS_TaskCreat(OS_TASK3,OS_Task4, 1000, 1000, OS_TASK_RUN);
    OS_TaskCreat(OS_TASK4,OS_Task5, 1000, 1000, OS_TASK_RUN);
    OS_TaskCreat(OS_TASK5,OS_Task6, 1000, 1000, OS_TASK_RUN);
    OS_TaskCreat(OS_TASK6,OS_Task7, 1000, 1000, OS_TASK_RUN);
    OS_TaskCreat(OS_TASK7,OS_Task8, 1000, 1000, OS_TASK_RUN);
    OS_TaskCreat(OS_TASK8,OS_Task9, 1000, 1000, OS_TASK_RUN);
    OS_TaskCreat(OS_TASK9,OS_Task10, 1000, 1000, OS_TASK_RUN);
    OS_TaskCreat(OS_TASK10,OS_Task11, 1000, 1000, OS_TASK_RUN);
    OS_TaskCreat(OS_TASK11,OS_Task12, 1000, 1000, OS_TASK_RUN);


}

/**
 * @brief  Creates a new task
 * @param  ID: task ID
 * @param  TaskHook: pointer to the task function
 * @param  ItvTime: interval time
 * @note  The task will be executed every ItvTime ms
 * @param  Timer: timer value
 * @note  The task will be started after Timer ms
 * @param  RunState: task state
 * @note  The task will be started in the specified state
 * @note  The state can be OS_TASK_RUN or OS_TASK_SLEEP
 * @note  If the state is OS_TASK_SLEEP, the task will not be executed
 * @retval None
 */
void OS_TaskCreat(uint8_t ID, void (*TaskHook)(void), uint16_t ItvTime, uint16_t Timer, OS_TaskStatusTypeDef RunState)
{
    if (!TaskComps[ID].TaskHook)
    {
        TaskComps[ID].ItvTime = ItvTime;
        TaskComps[ID].RunState = RunState;
        TaskComps[ID].TaskHook = TaskHook;
        TaskComps[ID].Timer = Timer;
    }
}

/**
 * @brief  Deletes a task
 * @param  ID: task ID
 * @retval None
 * @note  This function should be called after created all tasks
 */
void OS_TaskStart(void)
{
    uint8_t i;
    while (1)
    {
        for (i = 0; i < OS_TASK_SUM; i++)
        {
            if (TaskComps[i].TaskHook == NULL)
            {
                continue;
            }
            else
            {
                if (TaskComps[i].RunState == OS_TASK_RUN)
                {
                    TaskComps[i].TaskHook();
                    TaskComps[i].RunState = OS_TASK_SLEEP;
                }
            }
        }
    }
}





/**
 * @brief  Deletes a task
 * @param  ID: task ID
 * @retval None
 * @note   This function is called by the 1ms timer interrupt
 */
void OS_Task_TimerCallback(void)
{
    uint8_t i;
    for (i = 0; i < OS_TASK_SUM; i++) 
    {
        if (TaskComps[i].Timer) 
        {
            TaskComps[i].Timer--;        
            if (TaskComps[i].Timer == 0) 
            {
                TaskComps[i].Timer = TaskComps[i].ItvTime; 
                TaskComps[i].RunState = OS_TASK_RUN;       
            }
        }
    }
}
