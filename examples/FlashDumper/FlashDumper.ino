// Print contents of flash memory

/*
  Author: Martin Eden
  Last mod.: 2024-12-15
*/

#include <me_FlashMemory.h>

#include <me_BaseTypes.h>
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
    me_FlashMemory::GetByte,
    me_UnoAddresses::FlashSize;

  TMemorySegment FlashSeg = FromAddrSize(0, FlashSize);
  TSegmentIterator Rator;
  TUint_1 Column;
  TAddress Addr;
  TUnit Unit;

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
    if (!GetByte(&Unit, Addr))
    {
      Console.Print("Getting byte failed.");
      break;
    }

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
