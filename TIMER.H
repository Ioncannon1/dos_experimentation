#ifndef INC_TIMER_H
#define INC_TIMER_H

#define TIMER0_PORT 0x40
#define TIMER1_PORT 0x41
#define TIMER2_PORT 0x42
#define TIMER_CONTROL_PORT 0x43

#define ISR_TIMER 0x1C

extern void setTimerFreq(unsigned int);
#endif