//*********** Author: Nguyen Thanh Phuong***********************
//*********** since 2/11/2017 *********************************

#include "Declare.h"
#include "Effect.h"

unsigned char Layer_Count = 0;
static inline void SPI_Transmit(uint8_t data)
{
  SPDR = data;
  while ((SPSR & 0x80) == 0);
}

void setup()
{
  noInterrupts();
  DDRB |= (1 << SS) | (1 << SCK) | (1 << MOSI);
  PORTB = 0;
  SPI_Master_Init();
  Interrupt_Timer2_Init(200);
  //Bresenham(0,0,0,0,7,1);
  interrupts();
  //********************************************
}


void loop()
{
  Rain_Ver1(65, 20000);
  Rain_Ver2(60, 10000);
  Plane('X', 80);
  Plane_Support('X', 80);
  Set(0);
  Plane('Y', 80);
  Plane_Support('Y', 80);
  Set(0);
  Plane('Z', 70);
  Plane_Support('Z', 80);
  Set(0);

  Plane('X', 80);
  Plane_Support('Y', 80);
  Set(0);
  Plane('Y', 80);
  Plane_Support('Z', 80);
  Set(0);
  Plane('Z', 70);
  Plane_Support('X', 80);
  Set(0);
  SinWave(50, 10000);
  SinWave2(50, 20000);
  Cube_Random(100, 10000, 20);
  Ball_Effect(50, 20000, 3);


  Grow_Shrink(7, 7, 0, 60, SHRINK);
  Grow_Shrink(0, 0, 7, 60, GROW);
  Grow_Shrink(7, 0, 0, 60, SHRINK);
  Grow_Shrink(0, 7, 7, 60, GROW);
  Grow_Shrink(0, 7, 0, 60, SHRINK);
  Grow_Shrink(7, 0, 7, 60, GROW);
  Grow_Shrink(0, 0, 0, 60, SHRINK);
  Grow_Shrink(7, 7, 7, 60, GROW);
  Grow_Shrink(0, 0, 7, 60, SHRINK);
  Grow_Shrink(0, 0, 0, 60, GROW);
  Grow_Shrink(0, 7, 7, 60, SHRINK);
  Grow_Shrink(0, 7, 0, 60, GROW);
  Grow_Shrink(7, 0, 7, 60, SHRINK);
  Grow_Shrink(7, 0, 0, 60, GROW);
  Grow_Shrink(7, 7, 7, 60, SHRINK);
  Grow_Shrink(7, 7, 0, 60, GROW);
  String_Ani(100, "NGUYEN THANH PHUONG");
  Cascade(60);
  delay(500);
  Plane_V3(75, 3);
  delay(800);
}

ISR(TIMER2_COMPA_vect)
{
  if (Layer_Count > 7)
  {
    Layer_Count = 0;
  }
  bitClear(PORTB, SS);
  SPI_Transmit(0x80 >> Layer_Count);
  SPI_Transmit(CUBE[Layer_Count][7]);
  SPI_Transmit(CUBE[Layer_Count][6]);
  SPI_Transmit(CUBE[Layer_Count][5]);
  SPI_Transmit(CUBE[Layer_Count][4]);
  SPI_Transmit(CUBE[Layer_Count][3]);
  SPI_Transmit(CUBE[Layer_Count][2]);
  SPI_Transmit(CUBE[Layer_Count][1]);
  SPI_Transmit(CUBE[Layer_Count][0]);
  bitSet(PORTB, SS);
  Layer_Count++;
}
