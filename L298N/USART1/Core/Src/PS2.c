#include "PS.h"
#include "adc.h"
#include "stm32f1xx_hal.h"
#include "OLED.h"

uint8_t Med_Ps2_Scan(void)
{
    uint16_t xValue = 0;
    uint16_t yValue = 0;

    xValue  =  Get_xValue();
    yValue  =  Get_yValue();

    if(xValue >= 3600 &&(yValue >= 2000 && yValue <= 4500))
    {
        return Xright;
    }

    if(xValue <= 600 &&(yValue >= 2000 && yValue <= 4500))
    {
        return Xleft;
    }

    if(yValue >= 3300 &&(xValue >= 3200 && xValue <= 4500))
    {
        return Ybefore;
    }

    if(yValue <= 600 &&(xValue >= 1800 && xValue <= 3500))
    {
        return Yaffer;
    }

    if((yValue >= 2900 && yValue <= 3200) &&(xValue >= 2900 && xValue <=  3200))
    {
        return 0;
    }
}

void show_ps2(void)
{
    uint8_t ps2_value = Med_Ps2_Scan();

    if(ps2_value == Xright)
    {
        OLED_ShowString(1,4,"Xright") ;
    }

    if(ps2_value == Xleft)
    {
        OLED_ShowString(1,4,"Xleft") ;
    }

    if(ps2_value == Ybefore)
    {
        OLED_ShowString(1,4,"Ybefore") ;
    }

    if(ps2_value == Yaffer)
    {
        OLED_ShowString(1,4,"Yaffer") ;
    }
    if(ps2_value == 0)
    {
        OLED_ShowString(1,4,"nochang") ;
    }
}

