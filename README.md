# soft_pwm
software pwm driver

- minimun time for tick : 1ms
- frequency 0 -15.2590 KHz  ( T: 0 - 65.535sg)
- Duty cicle 0 -100 %

Use:
- Example

```
//------------ main.c -------------
int main(void)
{
   setup_mcu();
   SFPWM_Init(&SFPWM_data ,WrapperGpio , 0.001 ,10.0); /*!< 10 Hz */
   SFPWM_SetDuty( &SFPWM_data , 20); /*!< duty cicle 20% */

	while(1){ /* code*/}
}

void WrapperGpio(uint8_t pinvalue){
      if( pinvalue == 1){
            PORTC = (1 << 0);    /*on*/
         }else {
            PORTC = (0 << 0);    /*off*/
         }
}


//---------- interrup.c ------------
ISR(TIMER0_COMPA_vect )
{   
   SFPWM_Update(&SFPWM_data);;
}

```
