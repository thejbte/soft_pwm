/**
 * @file soft_pwm.h
 * @author Julian Bustamante N
 * @brief software pwm driver
 * @version 0.1.0
 * @date 2021-04-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "soft_pwm.h"
#include <stdlib.h>
#include <stdio.h>


static int16_t SFPWM_Rounding(float num);

void SFPWM_Init(SFPWM_data_t *obj, write_pin_fcn _write_pin, float basetiming ,float freq )
{   obj->private.write_pin = _write_pin ; 
    obj->private.frequency = freq;
    obj->private.period = (1 / obj->private.frequency);  //0.1
    obj->private.basetime = basetiming;   //0.001
    obj->private.count = 0;
    obj->private.Tcomparar = (obj->private.period *(1/obj->private.basetime));
}

void SFPWM_Update(SFPWM_data_t *obj){
    ++obj->private.count;
    if (   SFPWM_Rounding( obj->private.Tcomparar )   == obj->private.count ){  // overflow period
        obj->private.count = 0;  // overflow
    }

    obj->statepin = ( SFPWM_GetCount(obj)  < obj->private.dutyc ) ? 1 : 0 ;
    if( obj->private.write_pin != NULL){
        obj->private.write_pin( obj->statepin ); // 10 < 127  
    }
}

uint16_t SFPWM_GetCount(SFPWM_data_t *obj){
    return obj->private.count;
}

uint16_t SFPWM_GetStatePin(SFPWM_data_t *obj){
    return obj->statepin;
}

void SFPWM_SetDuty(SFPWM_data_t *obj , uint16_t duty){
    obj->private.dutyc = SFPWM_Rounding(  ( (duty*( obj->private.Tcomparar ) ) / SFPWM_MAX_PERCENTAGE )  )  ;
}

static int16_t SFPWM_Rounding(float num){
    return num < 0 ? num  - 0.5 : num + 0.5;
}
