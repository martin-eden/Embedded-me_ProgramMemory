// Print contents of flash memory

/*
  Author: Martin Eden
  Last mod.: 2024-12-10
*/

#include <me_BaseTypes.h>
#include <me_FlashMemory.h>
#include <me_Console.h>
#include <me_Uart.h>
#include <me_UartSpeeds.h>

void DumpFlash()
{
  TUint_2 FlashAddr = 0;

  TUint_1 Value;

  Console.Print("(");
  Console.Indent();
  while (me_FlashMemory::GetByte(&Value, FlashAddr))
  {
    Console.Print(Value);
    ++FlashAddr;
  }
  Console.EndLine();
  Console.Unindent();
  Console.Print(")");
}

void setup()
{
  me_Uart::Init(me_UartSpeeds::Bps_2M);
  DumpFlash();
}

void loop()
{
}

/*
  2024-12-10
*/
