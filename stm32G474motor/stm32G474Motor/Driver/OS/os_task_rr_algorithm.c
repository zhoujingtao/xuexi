/**
 * @file os_task_rr_algorithm.c
 * @brief  Round-robin scheduling algorithm of task
 * @author {hebin.wang} ({hebing.wang@hzmhst.com})
 * @brief
 * @version
 * @Creat Date : 2024-03-04
 *
 * @copyright Copyright (c) 2024
 *
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/

#include "os_task_rr_algorithm.h"

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

typedef struct
{
    uint16_t Timer;
    uint16_t ItvTime;
    void (*TaskHook)(void);
} TASK_INFO;

typedef struct
{
    uint16_t McuLoadRate;
    uint16_t TaskExpectedCnt;
    uint16_t TaskActualCnt;
    TASK_INFO TaskInfo[CTASK_SUPPORT_NUM];
} TASK_LOAD_RATE;

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

TaskCallBack Task_IdleCallback = NULL;
volatile TASK_LOAD_RATE TaskLoadRate;
volatile OS_TASK_RR_COMPONENTS TaskComps[CTASK_SUPPORT_NUM];

static void OS_TaskScheduling(void);
static void __OS_Task_Idle(void);
static void __OS_Task_IdleIsr(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

static void __OS_Task_Idle(void)
{
    TaskLoadRate.TaskActualCnt++;
	if(!Task_IdleCallback)
	{
    Task_IdleCallback();
	}
}

static void __OS_Task_IdleIsr(void)
{
    TaskLoadRate.TaskExpectedCnt++;
    if (TaskLoadRate.TaskExpectedCnt >= 1000)
    {
        TaskLoadRate.McuLoadRate = 100 - (TaskLoadRate.TaskActualCnt * 100 / TaskLoadRate.TaskExpectedCnt);
        TaskLoadRate.TaskExpectedCnt = 0;
        TaskLoadRate.TaskActualCnt = 0;
    }
}

void OS_TaskInit(void)
{
    TaskLoadRate.McuLoadRate = 0;
    TaskLoadRate.TaskExpectedCnt = 0;
    TaskLoadRate.TaskActualCnt = 0;
    for (uint8_t i = 0; i < CTASK_SUPPORT_NUM; i++)
    {
        TaskLoadRate.TaskInfo[i].Timer = 0;
        TaskLoadRate.TaskInfo[i].ItvTime = 0;
        TaskLoadRate.TaskInfo[i].TaskHook = NULL;
    }
    for (uint8_t i = 0; i < CTASK_SUPPORT_NUM; i++)
    {
        TaskComps[i].IsUsed = OS_TASK_UNUSED;
        TaskComps[i].RunState = OS_TASK_SLEEP;
        TaskComps[i].priority = OS_PRIORITIES_LEVEL_NONE;
        TaskComps[i].Timer = 0;
        TaskComps[i].ItvTime = 0;
        TaskComps[i].TaskHook = NULL;
    }

    OS_TaskCreat("Idle_Task", __OS_Task_Idle, 1, OS_PRIORITIES_LEVEL_10);
//    OS_TaskIsrCreat(__OS_Task_IdleIsr, 1);
}

void OS_TaskIsrCreat(void (*TaskHook)(void), uint16_t Timer)
{
    for (uint8_t i = 0; i < CTASK_SUPPORT_NUM; i++)
    {
        if (TaskLoadRate.TaskInfo[i].TaskHook == NULL)
        {
            TaskLoadRate.TaskInfo[i].Timer = Timer;
            TaskLoadRate.TaskInfo[i].ItvTime = Timer;
            TaskLoadRate.TaskInfo[i].TaskHook = TaskHook;
            break;
        }
    }
}

void OS_TaskIsrVacant(void (*TaskHook)(void))
{
    uint8_t i, j;
    for (i = 0; i < CTASK_SUPPORT_NUM; i++)
    {
        if (TaskLoadRate.TaskInfo[i].TaskHook == TaskHook)
        {
            TaskLoadRate.TaskInfo[i].TaskHook = NULL;

            for (j = i; j < CTASK_SUPPORT_NUM - 1; j++)
            {
                TaskLoadRate.TaskInfo[j] = TaskLoadRate.TaskInfo[j + 1];
            }

            break;
        }
    }
}

void OS_TaskCreat(char *name_ptr, void (*TaskHook)(void), uint16_t Timer, uint8_t priority)
{
    for (uint8_t i = 0; i < CTASK_SUPPORT_NUM; i++)
    {
        if (TaskComps[i].priority <= priority)
        {
            continue;
        }

        if (TaskComps[i].IsUsed)
        {
            for (uint8_t j = CTASK_SUPPORT_NUM - 1; j > i; j--)
            {
                TaskComps[j] = TaskComps[j - 1];
                TaskComps[j - 1].IsUsed = OS_TASK_UNUSED;
            }
        }
        TaskComps[i].TaskName = name_ptr;
        TaskComps[i].IsUsed = OS_TASK_USED;
        TaskComps[i].RunState = OS_TASK_SLEEP;
        TaskComps[i].Timer = Timer;
        TaskComps[i].TaskHook = TaskHook;
        TaskComps[i].ItvTime = Timer;
        TaskComps[i].priority = priority;
        break;
    }
}

void OS_TaskVacant(void (*TaskHook)(void))
{
    for (uint8_t i = 0; i < CTASK_SUPPORT_NUM; i++)
    {
        if (TaskComps[i].TaskHook == TaskHook)
        {
            TaskComps[i].IsUsed = OS_TASK_UNUSED;
            break;
        }
    }
}

static void OS_TaskScheduling(void)
{
    uint8_t idx = 0;
//    while (idx < CTASK_SUPPORT_NUM && TaskComps[idx].TaskHook != NULL)
//    {
//        if (TaskComps[idx].IsUsed && TaskComps[idx].RunState)
//        {
//            TaskComps[idx].TaskHook();
//            TaskComps[idx].RunState = OS_TASK_SLEEP;
//            break;
//        }
//        idx++;
//    }
	for(idx = 0; idx < CTASK_SUPPORT_NUM; idx++ )
	{
		if(TaskComps[idx].TaskHook != NULL)
		{
		if (TaskComps[idx].IsUsed && TaskComps[idx].RunState)
        {
            TaskComps[idx].TaskHook();
            TaskComps[idx].RunState = OS_TASK_SLEEP;
            break;
        }
		}
		else
		{
			continue;
		}
	}
}

void OS_TASK_Start(void)
{

    while (1)
    {
        OS_TaskScheduling();
    }
}

void OS_Task_TimerCallback(void)
{
    uint8_t idx = 0;
  	TaskLoadRate.TaskExpectedCnt++;
//    while ((idx < CTASK_SUPPORT_NUM )&& (TaskComps[idx].TaskHook != NULL))
//    {
//        if (TaskComps[idx].IsUsed)
//        {
//            if (TaskComps[idx].Timer)
//            {
//                TaskComps[idx].Timer--;
//                if (TaskComps[idx].Timer == 0)
//                {
//                    TaskComps[idx].Timer = TaskComps[idx].ItvTime;
//                    TaskComps[idx].RunState = OS_TASK_RUN;
//                }
//            }
//        }
//        idx++;
//    }
	
	for (idx = 0; idx < CTASK_SUPPORT_NUM; idx++)
     {
         if (TaskComps[idx].TaskHook != NULL)
         {
             if (TaskComps[idx].IsUsed)
             {
                 if (TaskComps[idx].Timer)
                 {
                     TaskComps[idx].Timer--;
                     if (TaskComps[idx].Timer == 0)
                     {
                         TaskComps[idx].Timer = TaskComps[idx].ItvTime;
                         TaskComps[idx].RunState = OS_TASK_RUN;
                     }
                 }
             }
         }
         else 
         {
          continue;   
         }
     }
		
//		idx = 0;
//		
//		while(idx < CTASK_SUPPORT_NUM && TaskLoadRate.TaskInfo[idx].TaskHook != NULL)
//		{
//			if(TaskLoadRate.TaskInfo[idx].Timer)
//			{
//				TaskLoadRate.TaskInfo[idx].Timer--;
//				
//				if(TaskLoadRate.TaskInfo[idx].Timer == 0)
//				{
//					TaskLoadRate.TaskInfo[idx].Timer = TaskLoadRate.TaskInfo[idx].ItvTime;
//				  TaskLoadRate.TaskInfo[idx].TaskHook();
//				}
//			}
//		  idx++;
//		}
//    if (TaskLoadRate.TaskExpectedCnt >= 1000)
//    {
//        TaskLoadRate.McuLoadRate = 100 - (TaskLoadRate.TaskActualCnt * 100 / TaskLoadRate.TaskExpectedCnt);
//        TaskLoadRate.TaskExpectedCnt = 0;
//        TaskLoadRate.TaskActualCnt = 0;
//    }
}

void OS_Task_IdleCallback(TaskCallBack TaskHook)
{
    if (TaskHook != NULL)
    {
        Task_IdleCallback = TaskHook;
    }
}

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
