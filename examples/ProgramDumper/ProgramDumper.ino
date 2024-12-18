// Print contents of program memory

/*
  Author: Martin Eden
  Last mod.: 2024-12-18
*/

#include <me_ProgramMemory.h>

#include <me_BaseTypes.h>
#include <me_Console.h>
#include <me_Uart.h>
#include <me_UartSpeeds.h>
#include <me_MemorySegment.h>
#include <me_UnoAddresses.h>

void DumpFlash()
{
  const TUint_1 NumColumns = 16;

  using
    me_MemorySegment::TMemorySegment,
    me_MemorySegment::Freetown::FromAddrSize,
    me_MemorySegment::TSegmentIterator,
    me_ProgramMemory::GetByte;

  TMemorySegment FlashSeg = FromAddrSize(0, me_ProgramMemory::Size);
  TSegmentIterator Rator;
  TUint_1 Column;
  TAddress Addr;
  TUint_1 Byte;

  if (!Rator.Init(FlashSeg))
  {
    Console.Print("Iterator initialization failed.");
    return;
  }

  Console.Print("(");
  Console.Indent();

  Column = 1;

  while (Rator.GetNext(&Addr))
  {
    if (!GetByte(&Byte, Addr))
    {
      Console.Print("Getting byte failed.");
      break;
    }

    Console.Print(Byte);

    ++Column;

    if (Column > NumColumns)
    {
      Console.EndLine();
      Column = 1;
    }
  }

  Console.EndLine();
  Console.Unindent();
  Console.Print(")");
}

void setup()
{
  me_Uart::Init(me_UartSpeeds::Bps_115k);
  DumpFlash();
}

void loop()
{
}

/*
  2024-12-10
  2024-12-12
*/
