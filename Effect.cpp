
#include "Effect.h"

volatile unsigned char CUBE[8][8] = {0};
unsigned char Buffer[28] = {0};

//==================================================================================

void Set(unsigned char data)
{
  for (unsigned char i = 0; i < 8; i++)
  {
    for (unsigned char j = 0; j < 8; j++)
    {
      CUBE[i][j] = data;
    }
  }
}

void LED(unsigned char x, unsigned char y, unsigned char z, bool stt)
{
  bitWrite(CUBE[z][y], x, stt);
}

bool Read_Cube(unsigned char x, unsigned char y, unsigned char z)
{
  return (bitRead(CUBE[z][y], x));
}


//==================================================================================
void Rotate()
{
  unsigned char temp[8];
  for (unsigned char j = 0; j < 8; j++)
  {
    temp[0] = (Buffer[0] >> j) & 0x01; temp[0] <<= 7;
    temp[1] = (Buffer[1] >> j) & 0x01; temp[1] <<= 6;
    temp[2] = (Buffer[2] >> j) & 0x01; temp[2] <<= 5;
    temp[3] = (Buffer[3] >> j) & 0x01; temp[3] <<= 4;
    temp[4] = (Buffer[4] >> j) & 0x01; temp[4] <<= 3;
    temp[5] = (Buffer[5] >> j) & 0x01; temp[5] <<= 2;
    temp[6] = (Buffer[6] >> j) & 0x01; temp[6] <<= 1;
    temp[7] = (Buffer[7] >> j) & 0x01;
    CUBE[j][0] = temp[0] | temp[1] | temp[2] | temp[3] | temp[4] | temp[5] | temp[6] | temp[7];
  }
  for (unsigned char i = 0; i < 8; i++)
  {

    //temp[7] = (Buffer[7] >> i) & 0x01; CUBE[i][1] = temp[7];
    CUBE[i][1] = (Buffer[8] >> i) & 0x01;
    CUBE[i][2] = (Buffer[9] >> i) & 0x01;
    CUBE[i][3] = (Buffer[10] >> i) & 0x01;
    CUBE[i][4] = (Buffer[11] >> i) & 0x01;
    CUBE[i][5] = (Buffer[12] >> i) & 0x01;
    CUBE[i][6] = (Buffer[13] >> i) & 0x01;
    CUBE[i][7] = (Buffer[14] >> i) & 0x01;

  }
  for (unsigned char j = 0; j < 8; j++)
  {
    temp[0] = (Buffer[21] >> j) & 0x01; temp[0] <<= 7;
    temp[1] = (Buffer[20] >> j) & 0x01; temp[1] <<= 6;
    temp[2] = (Buffer[19] >> j) & 0x01; temp[2] <<= 5;
    temp[3] = (Buffer[18] >> j) & 0x01; temp[3] <<= 4;
    temp[4] = (Buffer[17] >> j) & 0x01; temp[4] <<= 3;
    temp[5] = (Buffer[16] >> j) & 0x01; temp[5] <<= 2;
    temp[6] = (Buffer[15] >> j) & 0x01; temp[6] <<= 1;
    //temp[7] = (Buffer[14] >> j) & 0x01; temp[7];
    CUBE[j][7] |= temp[0] | temp[1] | temp[2] | temp[3] | temp[4] | temp[5] | temp[6]; //| temp[7];
  }
  for (unsigned char i = 0; i < 8; i++)
  {
    CUBE[i][6]  |= (Buffer[22] << (7 - i)) & 0x80;
    CUBE[i][5]  |= (Buffer[23] << (7 - i)) & 0x80;
    CUBE[i][4]  |= (Buffer[24] << (7 - i)) & 0x80;
    CUBE[i][3]  |= (Buffer[25] << (7 - i)) & 0x80;
    CUBE[i][2]  |= (Buffer[26] << (7 - i)) & 0x80;
    CUBE[i][1]  |= (Buffer[27] << (7 - i)) & 0x80;
    // temp[6] = (Buffer[21] >> i) & 0x01; CUBE[i][6] |= temp[1] << 7;
    // temp[7] = (Buffer[22] >> i) & 0x01;  CUBE[i][7] |= temp[0] << 7;
  }
}
//==================================================================================
void Insert_Col(unsigned char data)
{
  for (char i = 20; i >= 1; i--)
  {
    Buffer[i] = Buffer[i - 1];
  }
  Buffer[0] = data;
}


void swap(int &x, int &y)
{
  int  temp = x;
  x = y;
  y = temp;
}
//==================================================================================

void Plane_Support(char axis, unsigned int Delay)
{
  for (uint8_t z = 0; z < 8; z++)
  {
    for (byte i = 1; i < 8 - z; i++)
    {
      for (byte x = 0; x < 8; x++)
      {
        for (byte y = 0; y < 8; y++)
        {
          if (axis == 'X')
          {
            if (Read_Cube(7 - i, x, y))
            {
              LED(7 - i + 1, x, y, 1);
              LED(7 - i, x, y, 0);
            }
          }
          else if (axis == 'Y')
          {
            if (Read_Cube(x, 7 - i, y))
            {
              LED(x, 7 - i + 1, y, 1);
              LED(x, 7 - i, y, 0);
            }
          }
          else
          {
            if (Read_Cube( x, y, 7 - i ))
            {
              LED( x, y, 7 - i + 1, 1);
              LED( x, y, 7 - i, 0);
            }
          }
        }
      }
    }
    delay(Delay);
  }
}

//===============================BALL==============================================
Ball::Ball()
{
  X = 3.5;
  Y = 3.5;
  Z = 3.5;
  Radius = 3;
}
void Ball::Set(float x, float y, float z, int r)
{
  X = x;
  Y = y;
  Z = z;
  Radius = r;
}
void Ball::Set(float x, float y, float z)
{
  X = x;
  Y = y;
  Z = z;
}
void Ball::Set(int r)
{
  Radius = r;
}
void Ball::Draw()
{

  int radius = Radius * Radius;
  for (unsigned char x = 0; x < 8; x++)
  {
    for (unsigned char y = 0; y < 8; y++)
    {
      for (unsigned char z = 0; z < 8; z++)
      {
        int RR = pow(x - X, 2) + pow(y - Y, 2) + pow(z - Z, 2);
        if (RR <= radius)
        {
          LED(x, y, z, 1);
        }
        else
        {
          LED(x, y, z, 0);
        }
      }
    }
  }
}
//=======================================END_BALL======================================


//=======================================EFFECT========================================
void Ball_Effect(unsigned char Delay, unsigned long ms, unsigned int radius)
{
  Ball ball;
  char x = 3, y = 3, z = 3;
  ball.Set(x, y, z, radius);
  unsigned long msec = millis();
  unsigned long start = msec;
  while (msec - start < ms)
  {
    randomSeed(msec);
    if (random(1, 10) <= 5)
    {
      x++;
    }
    else
    {
      x--;
    }
    if (random(1, 10) <= 5)
    {
      y++;
    }
    else
    {
      y--;
    }
    if (random(1, 10) <= 5)
    {
      z++;
    }
    else
    {
      z--;
    }
    if (x < 0)
    {
      x += 2;

    }
    else if (x > 7)
    {
      x -= 2;

    }
    if (y < 0)
    {
      y += 2;

    }
    else if (y > 7)
    {
      y -= 2;

    }
    if (z < 0)
    {
      z += 2;

    }
    else if (z > 7)
    {
      z -= 2;

    }
    ball.Set(x, y, z);
    ball.Draw();
    delay(Delay);
    msec = millis();
  }
}

//====================================================================================
void Bresenham(int x1, int y1, int z1, int x2, int y2, int z2)
{
  bool swap_xy = false, swap_xz = false; // Các biến xem việc hoán đổi có xảy ra ko
  if (abs(y2 - y1) > abs(x2 - x1)) { // Abs(a) có nghĩa là lấy giá trị tuyệt đối của a, nếu delta_y > delta_x thì hoán đổi xy
    swap_xy = true;
    swap(x1, y1);
    swap(x2, y2);
  }
  if (abs(z2 - z1) > abs(x2 - x1)) { //  Tương tự vs xz
    swap_xz = true;
    swap(x1, z1);
    swap(x2, z2);
  }
  if (x1 > x2) { // Nếu đường thẳng đi ngược thì chiều x thì hoán đổi 2 điểm
    swap(x1, x2);
    swap(y1, y2);
    swap(z1, z2);
  }

  float deltax = x2 - x1; // Ko cần lấy giá trị tuyệt đối nữa, do đã hoán đổi ở trên
  float deltay = abs(y2 - y1); // Độ chênh lệch y
  float deltaz = abs(z2 - z1); // Độ chênh lệch z

  float drift_xy = deltax / 2; // Sai số tích lũy theo xy (các bạn tham khảo thêm thuật toán Bresenham 2D trên wiki)
  float drift_xz = deltax / 2; // Tương tự vs xz

  int stepy = 1; if (y1 > y2) stepy = -1; // Bước tiến của y, nếu y đi ngược thì bước tiến là âm 1
  int stepz = 1; if (z1 > z2) stepz = -1; // Tương tự

  float y = y1; // Biến y tạm thời
  float z = z1; // Biến z tạm thời
  int cx, cy, cz; // Biến nguyên x, y, z

  for (float x = x1; x <= x2; x++) // Lắp x theo phương x
  {
    cx = (int)x; cy = (int)y; cz = (int)z; // Biến đỏi thành nguyên
    if (cx >= 0)
    {
      if ((cx < 8) && (cy >= 0) && (cy < 8) && (cz >= 0) && (cz < 8))
      { // Xem điểm đó có nằm ở trong cube?
        if (swap_xz)
        {
          swap(cx, cz);
        }// Nếu bị swap xz thì đảo lại (cái nào bị đảo sau thì bây giờ phải đảo trước)
        if (swap_xy)
        {
          swap(cx, cy);
        }// Tương tự vs xy
        LED(cx, cy, cz, 1); // Add điểm sáng đó
      }
      drift_xy -= deltay; // Tích lũy sai số
      drift_xz -= deltaz;

      if (drift_xy < 0)
      { // Nếu sai số âm thì tăng y lên 1, đồng thời reset lại sai số
        y += stepy;
        drift_xy += deltax;

      }
      if (drift_xz < 0)
      {
        z += stepz;
        drift_xz += deltax;
      }
    }
  }
}
//====================================================================================

void cricle(unsigned char ms)
{
  float ro = 10; // Điểm O rất xa LED Cube
  float To = 10; // Chu kỳ quay của O quanh trục
  float xo, yo;
  float t = 0; //Lấy thời gian
  unsigned char x = 4;
  unsigned char y = 3;
  unsigned char z = 4;
  for (t = 0; t < To; t++)
  {
    ro = sqrt(pow(x - xo, 2) + pow(z - yo, 2));
    xo = ro * cos(2 * PI * t / To) + 3.5;
    yo = ro * sin(2 * PI * t / To) + 3.5;
    x = (unsigned char)(xo);
    z = (unsigned char)(yo);
    LED(x, y, z, 1);
    delay(ms);
    Set(0);
  }
}

//====================================================================================
void Plane_V3(unsigned int Delay, unsigned char rain_drops)
{
  unsigned char store[8][8] {0};
  unsigned char count = 0;
  unsigned char loop_counter = 64 / rain_drops;
  for (unsigned char iii = 0 ; iii < loop_counter ; iii++)
  {
    randomSeed(millis());
    if (iii == loop_counter - 1)
    {
      for (unsigned char x = 0; x < 8; x++)
      {
        for (unsigned char y = 0; y < 8; y++)
        {
          if (store[x][y] == 0)
          {

            LED(x, y, 7, 0);
            LED(x, y, 6, 1);
          }
        }
      }
    }
    else
    {
      uint8_t x, y;
      for (uint8_t i = 0; i < rain_drops; i++)
      {
        do
        {
          x = random(0, 8);
          y = random(0, 8);
        } while (store[x][y] == 1);
        store[x][y] = 1;
        LED(x, y, 7, 0);
        LED(x, y, 6, 1);

      }
    }
    for (char z = 0; z <= 5 ; z++)
    {
      for (unsigned char x = 0; x < 8; x++)
      {
        for (unsigned char y = 0; y < 8; y++)
        {
          if (Read_Cube(x, y, z + 1) == 1)
          {
            LED(x, y, z, 1);
            LED(x, y, z + 1, 0);
          }
        }
      }
    }
    delay(Delay);
  }
  for (unsigned char xx = 0; xx < 5; xx++)
  {
    for (char z = 0; z <= 5 ; z++)
    {
      for (unsigned char x = 0; x < 8; x++)
      {
        for (unsigned char y = 0; y < 8; y++)
        {
          if (Read_Cube(x, y, z + 1) == 1)
          {
            LED(x, y, z, 1);
            LED(x, y, z + 1, 0);
          }
        }
      }
    }
    delay(Delay);
  }
}

//====================================================================================
void Cascade(unsigned int _delay_)
{
  for (unsigned char i = 0; i < 8; i++)
  {
    CUBE[0][i] = 255;
  }
  delay(_delay_);
  unsigned char y = 0;
  while (y < 8)
  {
    if (y % 2 == 0)
    {
      Cascade_Supp(_delay_, y, 0);
    }
    else
    {
      Cascade_Supp(_delay_, y, 1);
    }
    y++;
  }
  for (unsigned char z = 0; z < 6; z++)
  {
    CUBE[7][7] |= CUBE[6][7];
    for (char i = 6; i >= z + 1; i--)
    {
      CUBE[i][7] = CUBE[i - 1][7];
    }
    delay(_delay_);
  }
}


//====================================================================================
void Cascade_Supp(unsigned int _delay_, unsigned char y, bool stt)
{
  for (unsigned char z = 0; z < 8; z++)
  {
    for (char x = 0; x <= z; x++)
    {
      unsigned char temp_;
      if (stt)
      {
        temp_ = 7 - x;
      }
      else
      {
        temp_ = x;
      }
      LED(temp_, y, z - x, 0);
      unsigned char temp = z - x + 1;
      if (temp < 8)
      {
        LED(temp_, y, temp, 1);
      }
      else if (temp == 8)
      {
        LED(temp_, y, 7, 1);
      }
    }
    if (y > 0)
    {
      CUBE[7][y - 1] |= CUBE[6][y - 1];
      for (char i = 6; i >= z + 1; i--)
      {
        CUBE[i][y - 1] = CUBE[i - 1][y - 1];
      }
    }
    delay(_delay_);
  }
}
//====================================================================================
void Grow_Shrink(uint8_t xo, uint8_t yo, uint8_t zo, unsigned int Delay, bool stt)
{
  uint8_t xmin, xmax, ymin, ymax, zmin, zmax;
  byte T = 7, t;
  if (stt)
  {
    t = 7;
  }
  else
  {
    t = 0;
  }
  while ((t >= 0) & (t < 8))
  {
    xmin = (xo / T * t);
    xmax = (7 - (7 - xo) / T * t);
    ymin = (yo / T * t);
    ymax = (7 - (7 - yo) / T * t);
    zmin = (zo / T * t);
    zmax = (7 - (7 - zo) / T * t);
    for (char x = xmin; x <= xmax; x++)
    {
      LED(x, ymin, zmin, 1);
      LED(x, ymax, zmin, 1);
      LED(x, ymin, zmax, 1);
      LED(x, ymax, zmax, 1);
    }
    for (char y = ymin; y <= ymax; y++)
    {
      LED(xmin, y, zmin, 1);
      LED(xmax, y, zmin, 1);
      LED(xmin, y, zmax, 1);
      LED(xmax, y, zmax, 1);
    }
    for (char z = xmin; z <= zmax; z++)
    {
      LED(xmin, ymin, z, 1);
      LED(xmax, ymin, z, 1);
      LED(xmin, ymax, z, 1);
      LED(xmax, ymax, z, 1);
    }
    delay(Delay);
    if (stt)
    {
      t--;
    }
    else
    {
      t++;
    }
    for (unsigned char i = 0; i < 8; i++)
    {
      CUBE[i][0] = 0;
      CUBE[i][1] = 0;
      CUBE[i][2] = 0;
      CUBE[i][3] = 0;
      CUBE[i][4] = 0;
      CUBE[i][5] = 0;
      CUBE[i][6] = 0;
      CUBE[i][7] = 0;
    }
  }
}
//====================================================================================
void String_Ani(unsigned int delay_, unsigned char *s)
{
  unsigned int i = 0;
  byte ASCII;
  while (s[i] != 0)
  {
    ASCII = (byte)s[i];
    if (ASCII == ' ')
    {
      Insert_Col(0);
      Insert_Col(0);
      Insert_Col(0);
      Insert_Col(0);
      Rotate();
    }
    else
    {
      for (unsigned char  j = 0; j < 5; j++)
      {
        Insert_Col(Char[ASCII - 65][j]);
        Rotate();
        delay(delay_);
      }
      Insert_Col(0);
      Rotate();
      delay(delay_);
    }
    i++;
  }
  for (unsigned char i = 0; i < 28; i++)
  {
    Insert_Col(0);
    Rotate();
    delay(delay_);
  }
}
//====================================================================================

void Rain_Ver2(unsigned int Delay, unsigned int ms)
{
  unsigned long msec = millis();
  unsigned long start = msec;
  while (msec - start < ms)
  {
    randomSeed(msec);
    byte raindrops = random(1, 20);
    for (uint8_t i = 0; i < raindrops; i++)
    {
      byte x = random(0, 8);
      byte y = random(0, 8);
      LED(x, y, 0, 1);
    }
    delay(Delay);
    for (char z = 0 ; z < 7; z++)
    {
      for (uint8_t y = 0; y < 8; y++)
      {
        CUBE[z + 1][y] = CUBE[z][y];
      }
      delay(Delay);
    }
    for (uint8_t y = 0; y < 8; y++)
    {
      CUBE[0][y] = 0;
    }
    msec = millis();
  }
}
//====================================================================================
void Rain_Ver1(unsigned int Delay, unsigned long ms)
{
  unsigned long msec = millis();
  unsigned long start = msec;
  while (msec - start < ms)
  {
    randomSeed(msec);
    for (uint8_t i = 0; i < 7; i++)
    {
      byte x = random(0, 8);
      byte y = random(0, 8);
      LED(x, y, 0, 1);
    }
    delay(Delay);
    for (char z = 7 ; z >= 1; z--)
    {
      for (uint8_t y = 0; y < 8; y++)
      {
        CUBE[z][y] = CUBE[z - 1][y];
      }
      // delay(Delay);
    }
    for (uint8_t y = 0; y < 8; y++)
    {
      CUBE[0][y] = 0;
    }
    msec = millis();
  }
}

//====================================================================================

void Plane(char axis, unsigned int Delay)
{
  byte store[8][8] {0};
  for (unsigned char x = 0; x < 8; x++)
  {
    for (unsigned char y = 0; y < 8; y++)
    {
      if (axis == 'X')
      {
        LED(0, x, y, 1);
      }
      else if (axis == 'Y')
      {
        LED(x, 0, y, 1);
      }
      else
      {
        LED(x, y, 0, 1);
      }
    }
  }
  delay(Delay * 2);
  for (uint8_t i = 1; i < 8; i++)
  {
    byte count_point = 0;
    while (count_point < 8)
    {
      byte x = random(8);
      byte y = random(8);
      if (store[x][y] == 0)
      {
        store[x][y] = 1;
        count_point++;
      }
    }
    for (uint8_t x = 0; x < 8; x++)
    {
      for (uint8_t y = 0; y < 8; y++)
      {
        if (store[x][y] == 0)
        {
          if (axis == 'X')
          {
            LED(i, x, y, 1);
            LED(i - 1, x, y, 0);
          }
          else if (axis == 'Y')
          {
            LED(x, i, y, 1);
            LED(x, i - 1, y, 0);
          }
          else
          {
            LED(x, y, i, 1);
            LED(x, y, i - 1, 0);
          }
        }
      }
    }
    delay(Delay);
  }
}
//====================================================================================
void SinWave(unsigned int Delay, unsigned long ms)
{
  float L = 7; // Bước sóng
  float T = 1; // Chu kỳ
  float A = 4; // Biên độ
  float xo = 3.5; // Tọa độ điểm gốc O
  float yo = 3.5;
  float t = 0;
  unsigned long msec = millis();
  unsigned long start = msec;
  while (msec - start < ms)
  {
    if (t > 1)
    {
      t = 0;
    }
    for (byte y = 0; y < 8; y++) // Quét Y
    {
      for (byte x = 0; x < 8; x++) // Quét X
      {
        for (unsigned char i = 0; i < 8; i++)
        {
          LED(x, y, i, 0);
        }
        float r = sqrt(pow(x - xo, 2) + pow(y - yo, 2)); // Lấy bán kính, Sqrt là căn bậc 2, Pow(x, y) là x mũ y
        byte z = (byte)(A * cos(2 * PI * t / T - 2 * PI * r / L) + 3.5); // Lấy cao độ z, 3.5 là vị trí cân bằng
        if (x > 7)
        {
          x = 7;
        }
        else if (x < 0)
        {
          x = 0;
        }
        if (y > 7)
        {
          y = 7;
        }
        else if (y < 0)
        {
          y = 0;
        }
        if (z > 7)
        {
          z = 7;
        }
        else if (z < 0)
        {
          z = 0;
        }
        LED(x, y, z, 1);
      }
    }
    delay(Delay);
    t += 0.1;
    msec = millis();
  }
}

//====================================================================================

void SinWave2(unsigned int Delay, unsigned int ms)
{
  float L = 13; // Bước sóng
  float T = 1; // Chu kỳ
  float A = 4; // Biên độ
  float ro = 5000; // Điểm O rất xa LED Cube
  float To = 20; // Chu kỳ quay của O quanh trục
  float xo, yo;
  float t = 0; //Lấy thời gian
  unsigned long msec = millis();
  unsigned long start = msec;
  while (msec - start < ms)
  {
    xo = ro * cos(2 * PI * t / To) + 3.5; // Cho điểm O quay
    yo = ro * sin(2 * PI * t / To) + 3.5;

    for (byte y = 0; y < 8; y++) // Quét Y
    {
      for (byte x = 0; x < 8; x++) // Quét X
      {
        for (unsigned char i = 0; i < 8; i++)
        {
          LED(x, y, i, 0);
        }
        float r = sqrt(pow(x - xo, 2) + pow(y - yo, 2)); // Lấy bán kính, Sqrt là căn bậc 2, Pow(x, y) là x mũ y
        byte z = (byte)(A * cos(2 * PI * t / T - 2 * PI * r / L) + 3.5); // Lấy cao độ z, 3.5 là vị trí cân bằng
        LED(x, y, z, 1); // Lưu vị trí LED sáng
      }
    }

    t += 0.1;
    delay(Delay);
    msec = millis();
  }
}


//====================================================================================
void Cube_Random(unsigned char Delay, unsigned long ms, unsigned char dot)
{
  unsigned long start = millis();
  unsigned long msec = start;
  while (msec - start < ms)
  {
    randomSeed(msec);
    for (uint8_t i = 0; i < dot; i++)
    {
      byte x = random(0, 8);
      byte y = random(0, 8);
      byte z = random(0, 8);
      if (x > 7)
      {
        x = 7;
      }
      else if (x < 0)
      {
        x = 0;
      }
      if (y > 7)
      {
        y = 7;
      }
      else if (y < 0)
      {
        y = 0;
      }
      if (z > 7)
      {
        z = 7;
      }
      else if (z < 0)
      {
        z = 0;
      }
      if (Read_Cube(x, y, z))
      {
        LED(x, y, z, 0);
      }
      else
      {
        LED(x, y, z, 1);
      }
    }
    delay(Delay);
    msec = millis();
  }
}

//====================================================================================



//====================================================================================
