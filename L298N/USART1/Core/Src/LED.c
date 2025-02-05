#include "led.h"
#include "time.h"


const uint16_t LedPins[LED_NUMBER] =
{

    GPIO_PIN_0,
    GPIO_PIN_1,
    GPIO_PIN_10

};

//定义3个定时变量
static tsTimeType TimeLeds[LED_NUMBER];

//定义3个指示灯的任务状态
static teLedTaskStatus LedTaskStatus[LED_NUMBER];

//定义LED灯点亮
void LedOn(teLedNums LedNums)
{
    HAL_GPIO_WritePin(GPIOB,LedPins[LedNums],GPIO_PIN_RESET);
}

//定义LED灯熄灭
void LedOff(teLedNums LedNums)
{
    HAL_GPIO_WritePin(GPIOB,LedPins[LedNums],GPIO_PIN_SET);
}

//LED灯初始化，LED灯熄灭
void LedInit(void)
{
    int i;
    for(i = 0; i < LED_NUMBER; i++)
    {
        LedOff(i);
    }
}

//设置任务灯为运行状态
void SetLedRun(teLedNums LedNums)
{
    LedTaskStatus[LedNums] = LED_RUN;
}


//LED灯的任务，当调用SetLedRun().
//LedTask()执行LED的工作
void LedTask(void)
{
    int i;
    //遍历3个LED
    for(i = 0; i < LED_NUMBER; i++)
    {
        //判断是否是运行
        if(LedTaskStatus[i] == LED_RUN)
        {
            //亮100ms，转化状态
            LedOn(i);
            SetTime(&TimeLeds[i],1000);
            LedTaskStatus[i] = LED_DELAY;

        }
        else if(LedTaskStatus[i] == LED_DELAY)
        {
            if(CompareTime(&TimeLeds[i]))
            {
                LedOff(i);
                LedTaskStatus[i] = LED_STOP;
            }

        }

    }

}
