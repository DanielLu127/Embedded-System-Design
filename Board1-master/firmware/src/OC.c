#include "OC.h"

void OCInit()  {
    PLIB_PORTS_DirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_E, 0x00FF);
    PLIB_PORTS_DirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_A, 0x0008); //LED
    DRV_OC0_Start(); //OC_ID_1
    DRV_OC1_Start(); //OC_ID_2
    DRV_OC2_Start(); //OC_ID_3
    set_OC1_PWM(0);
    set_OC2_PWM(0);
    set_OC3_PWM(0);
}

void TMRInit() {
    DRV_TMR0_Start(); //Timer ID_2
}


void set_OC1_PWM(float value) {
    int period=DRV_TMR0_PeriodValueGet();
    int val= (int)(value*period/armPeriod);
    PLIB_OC_PulseWidth16BitSet(OC_ID_1,val);
}

void set_OC2_PWM(float value) {
    int period=DRV_TMR0_PeriodValueGet();
    int val=(int)(value*period/armPeriod);
    PLIB_OC_PulseWidth16BitSet(OC_ID_2,val);
}

void set_OC3_PWM(float value) {
    int period=DRV_TMR0_PeriodValueGet();
    int val=(int)(value*period/armPeriod);
    PLIB_OC_PulseWidth16BitSet(OC_ID_3,val);
}

/*void reset()
{
    set_OC1_PWM(1.3);
    set_OC2_PWM(1.6);
    set_OC3_PWM(1);
}*/

void clawClose(float clawClose) {
    set_OC3_PWM(clawClose);
}

void clawOpen() {
    set_OC3_PWM(clawOpenPosition);
}

void forearmRotateForeward(float forearmValue){
        set_OC1_PWM(stop);
        set_OC2_PWM(forearmValue);
    //    set_OC3_PWM(stop);
}  //OC2 start, other OC stop

void forearmRotateBackward() {
        set_OC1_PWM(stop);
        set_OC2_PWM(forearmBackwardPsotion);
      //  set_OC3_PWM(stop);
}

 void baseRotateMiddle()
 {
      set_OC1_PWM(baseMiddlePosition);
      set_OC2_PWM(stop);
   //   set_OC3_PWM(stop);
 }

void baseRotateLeft(float baseValue) {
        set_OC1_PWM(baseValue);
        set_OC2_PWM(stop);
      //  set_OC3_PWM(stop);
}  //OC1 start, other OC stops

void baseRotateRight() {
        set_OC1_PWM(baseRightPosition);
        set_OC2_PWM(stop); 
      //  set_OC3_PWM(stop);
}

void stopAllServos() {
     set_OC1_PWM(stop);
     set_OC2_PWM(stop);
    // set_OC3_PWM(stop);
}


