/**
 * @file    TransportTask.cpp
 * @brief   传输任务 —— USB CDC 初始化与遥测输出
 * @author  zzm
 * @version 1.2
 * @date    2026-07-11 1.2 移除未使用的 PID tuner
 */

/* Includes ------------------------------------------------------------------*/

#include "sys_debug.h"
#include "usb_device.h"
#include "user_task.h"


/* Private macros ------------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function declarations ---------------------------------------------*/

/* Function prototypes -------------------------------------------------------*/

extern "C" void Transport_Task(void *argument)
{
    float euler[3] = {0};

    MX_USB_DEVICE_Init();
    EricTool_USB.Set_Data(3, (int) &euler[0], (int) &euler[1], (int) &euler[2]);
    for (;;)
    {
        if (Transport_Read_IMU_Euler(euler))
        {
            EricTool_USB.TIM_1ms_Write_PeriodElapsedCallback();
        }
        osDelay(1);
    }
}
