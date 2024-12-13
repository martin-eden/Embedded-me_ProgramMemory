// Print contents of flash memory

/*
  Author: Martin Eden
  Last mod.: 2024-12-12
*/

#include <me_BaseTypes.h>
#include <me_FlashMemory.h>
#include <me_Console.h>
#include <me_Uart.h>
#include <me_UartSpeeds.h>
#include <me_MemorySegment.h>
#include <me_UnoAddresses.h>

using namespace me_FlashMemory;

void DumpFlash()
{
  const TUint_1 NumColumns = 16;

  using
    me_MemorySegment::TMemorySegment,
    me_MemorySegment::Freetown::FromAddrSize,
    me_MemorySegment::TSegmentIterator,
    me_FlashMemory::UnitGetter,
    me_UnoAddresses::FlashSize;

  TSegmentIterator Rator;
  TMemorySegment FlashSeg = FromAddrSize(0, FlashSize);
  TUnit Unit;
  TUint_1 Column;

  Console.Print("(");
  Console.Indent();

  Rator.Init(FlashSeg, UnitGetter);

  Column = 1;

  while (Rator.GetNext(&Unit))
  {
    Console.Print(Unit);

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
