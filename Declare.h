

#ifndef _DECLARE_H_
#define _DECLARE_H_

#include "Arduino.h"

#define SS 2
#define SCK 5
#define MOSI 3

void SPI_Master_Init();
void Interrupt_Timer2_Init(unsigned char num);

#endif
