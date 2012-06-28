#ifndef LNET_H
#define LNET_H

unsigned char checksumGood(void);
void processLnetData(void);
unsigned int unstuff_Lnet(unsigned char);
void servicePage(void);
void serviceRx(void);

extern unsigned char lnetMinutes;
extern unsigned char lnetHours;
extern unsigned char lnetHoursShadow;
extern unsigned char lnet24HourTime;
extern unsigned char lnetConnected;
extern unsigned char lnetControllerModel;

#endif
