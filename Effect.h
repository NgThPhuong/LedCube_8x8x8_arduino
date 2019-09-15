
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "Arduino.h"

#define GROW 0
#define SHRINK 1

extern volatile unsigned char CUBE[8][8];
extern unsigned char Buffer[28];

//=============================CHARACTERS=============================================================

const unsigned char Char[][5] = {
  {0x7C, 0x0A, 0x09, 0x0A, 0x7C},
  {0x7F, 0x49, 0x49, 0x49, 0x36},
  {0x3E, 0x41, 0x41, 0x41, 0x22},
  {0x7F, 0x41, 0x41, 0x41, 0x3E},
  {0x7F, 0x49, 0x49, 0x49, 0x41},
  {0x7F, 0x09, 0x09, 0x09, 0x01},
  {0x3E, 0x41, 0x41, 0x49, 0x3A},
  {0x7F, 0x08, 0x08, 0x08, 0x7F},
  {0x41, 0x41, 0x7F, 0x41, 0x41},
  {0x21, 0x41, 0x3F, 0x01, 0x01},
  {0x7F, 0x08, 0x14, 0x22, 0x41},
  {0x7F, 0x40, 0x40, 0x40, 0x40},
  {0x7F, 0x02, 0x04, 0x02, 0x7F},
  {0x7F, 0x02, 0x04, 0x08, 0x7F},
  {0x3E, 0x41, 0x41, 0x41, 0x3E},
  {0x7F, 0x09, 0x09, 0x09, 0x06},
  {0x3E, 0x41, 0x51, 0x61, 0x3E},
  {0x7F, 0x09, 0x19, 0x29, 0x46},
  {0x26, 0x49, 0x49, 0x49, 0x32},
  {0x01, 0x01, 0x7F, 0x01, 0x01},
  {0x3F, 0x40, 0x40, 0x40, 0x3F},
  {0x1F, 0x20, 0x40, 0x20, 0x1F},
  {0x7F, 0x20, 0x18, 0x20, 0x7F},
  {0x63, 0x14, 0x08, 0x14, 0x63},
  {0x03, 0x04, 0x78, 0x04, 0x03},
  {0x61, 0x51, 0x49, 0x45, 0x43}
};

const unsigned char pack_man[][8] = {
  {0x42, 0xA5, 0xA9, 0x91, 0x85, 0x81, 0x42, 0x3C},
  {0x3C, 0x72, 0xB1, 0xB1, 0x85, 0x81, 0x42, 0x3C}
};

class Ball
{
  private:
    float X;
    float Y;
    float Z;
    int Radius;
  public:
    Ball();
    void Set(float x, float y, float z, int r);
    void Set(float x, float y, float z);
    void Set(int r);
    void Draw();
};

//===========================================SUPPORT====================================

void LED(unsigned char x, unsigned char y, unsigned char z, bool stt);
bool Read_Cube(unsigned char x, unsigned char y, unsigned char z);
void Rotate();
void Insert_Col(unsigned char data);
void swap(int &x, int &y);
void Plane_Support(char axis, unsigned int Delay);
void Set(unsigned char data);

//==========================================END_SUPP====================================
//                                          ********
//=========================================EFFECT=======================================
void Ball_Effect(unsigned char Delay, unsigned long ms, unsigned int radius);
void Bresenham(int x1, int y1, int z1, int x2, int y2, int z2);
void cricle(unsigned char ms);
void Plane_V3(unsigned int Delay, unsigned char rain_drops);
void Cascade(unsigned int _delay_);
void Cascade_Supp(unsigned int _delay_, unsigned char y, bool stt);
void Grow_Shrink(uint8_t xo, uint8_t yo, uint8_t zo, unsigned int Delay, bool stt);
void String_Ani(unsigned int delay_, unsigned char *s);
void Rain_Ver2(unsigned int Delay, unsigned int ms);
void Rain_Ver1(unsigned int Delay, unsigned long ms);
void Plane(char axis, unsigned int Delay);
void SinWave(unsigned int Delay, unsigned long ms);
void SinWave2(unsigned int Delay, unsigned int ms);
void Cube_Random(unsigned char Delay, unsigned long ms, unsigned char dot);

//=========================================END_EFFECT====================================
#endif
