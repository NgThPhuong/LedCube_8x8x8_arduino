

#include "Declare.h"

void SPI_Master_Init()
{
  SPCR   = (1 << SPE) | (1 << MSTR); //| (1 << DORD);
  // SPE SPI enable cho phep SPI hoat dong
  // MSTR = 1 MCU nhan dien la master
  // DORD = 0 bit có trọng số lớn nhất MSB truyền trước
  SPSR    = (1 << SPI2X);
  // SPI2X bit nhân đôi tốc độ SPI , trong cấu hình này xung nhịp chân SCK là 8Mhz
}
//===================================================================================================
void Interrupt_Timer2_Init(unsigned char num)
{
  TCCR2A = (1 << WGM21); //CTC Mode
  OCR2A = num;           // thời gian giữa hai lần ngắt là 4us * num tần số quét mỗi tầng led là 1/(4us*num*8) vì có 8 tầng led
  TCCR2B = (1 << CS22); //prescaler 64, xung đầu vào 16Mhz từ crystal chia cho 64
  TIMSK2 = (1 << OCIE2A); //Output Compare A Match Interrupt Enable, đếm từ 0 lên khi đến giá trị trong thanh ghi OCR2A xảy ra 1 ngắt và xuất 9 byte ra 9 74HC595
}
//===================================================================================================

