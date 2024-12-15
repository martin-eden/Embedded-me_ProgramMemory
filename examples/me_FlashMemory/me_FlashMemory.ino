// [Test/demo] Flash memory access

/*
  Author: Martin Eden
  Last mod.: 2024-12-15
*/

#include <me_BaseTypes.h>
#include <me_Uart.h>
#include <me_UartSpeeds.h>
#include <me_Console.h>

#include <me_FlashMemory.h>
#include <me_MemorySegment.h>

void PrintSegmentWrappings(
  me_MemorySegment::TMemorySegment MemSeg
)
{
  Console.Indent();
  Console.Write("Addr");
  Console.Print(MemSeg.Addr);
  Console.Write("Size");
  Console.Print(MemSeg.Size);
  Console.EndLine();
  Console.Unindent();
}

void PrintSegmentData(
  me_MemorySegment::TMemorySegment MemSeg
)
{
  using
    me_MemorySegment::TSegmentIterator;

  TSegmentIterator Rator;
  TAddress Addr;
  TUnit Unit;

  Console.Indent();

  if (!Rator.Init(MemSeg))
  {
    Console.Print("Iterator initialization failed.");
    return;
  }

  while (Rator.GetNext(&Addr))
  {
    Unit = *(TUnit *) Addr;

    Console.Print(Unit);
  }

  Console.Unindent();

  Console.EndLine();
}

void RunTest()
{
  Console.Print("Flash memory test.");

  static const TUint_1 ReferenceValues[] [[gnu::progmem]] =
    { 31, 32, 33 };

  using
    me_MemorySegment::TMemorySegment,
    me_MemorySegment::Freetown::FromAddrSize,
    me_MemorySegment::Freetown::Reserve,
    me_MemorySegment::Freetown::Release,
    me_FlashMemory::GetByte,
    me_FlashMemory::GetSegment;

  TMemorySegment FlashSeg =
    FromAddrSize((TUint_2) ReferenceValues, sizeof(ReferenceValues));

  Console.Print("Reference segment");
  PrintSegmentWrappings(FlashSeg);

  {
    TUint_1 Value;
    TBool IsDone;

    IsDone = GetByte(&Value, FlashSeg.Addr);

    if (!IsDone)
    {
      Console.Print("Getting byte failed.");
      return;
    }

    Console.Print("Got byte");
    Console.Print(Value);
    Console.EndLine();
  }

  TMemorySegment SramSeg;

  if (!Reserve(&SramSeg, FlashSeg.Size))
  {
    Console.Print("No memory for flash segment copy.");
    return;
  }

  {
    TBool IsDone;

    IsDone = GetSegment(SramSeg, FlashSeg);

    if (!IsDone)
    {
      Console.Print("Getting segment failed.");
      Release(&SramSeg);
      return;
    }

    Console.Print("Memory copy segment");
    PrintSegmentWrappings(SramSeg);
    PrintSegmentData(SramSeg);
  }

  Release(&SramSeg);
}

// --

void setup()
{
  me_Uart::Init(me_UartSpeeds::Bps_115k);

  Console.Print("[me_FlashMemory] Start.");
  RunTest();
  Console.Print("[me_FlashMemory] Done.");
}

void loop()
{
}

/*
  2024-12-09
*/
