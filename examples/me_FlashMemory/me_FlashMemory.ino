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
  Console.Write("Addr");
  Console.Print(MemSeg.Addr);
  Console.Write("Size");
  Console.Print(MemSeg.Size);
  Console.EndLine();
}

void PrintSegmentData(
  me_MemorySegment::TMemorySegment MemSeg
)
{
  Console.Write("( ");
  Console.Write(MemSeg);
  Console.Write(" )");
  Console.EndLine();
}

void PrintFlashSegmentData(
  me_MemorySegment::TMemorySegment FlashSeg
)
{
  Console.Write("( ");
  Console.WriteFlash(FlashSeg);
  Console.Write(" )");
  Console.EndLine();
}

void RunTest()
{
  using
    me_MemorySegment::TMemorySegment,
    me_MemorySegment::Freetown::FromAddrSize,
    me_MemorySegment::Freetown::Reserve,
    me_MemorySegment::Freetown::Release,
    me_FlashMemory::GetSegment;

  Console.Print("Flash memory test.");

  static const TUint_1 ReferenceValues[] [[gnu::progmem]] =
    { "Some data in Flash (aka program memory)." };

  TMemorySegment FlashSeg =
    FromAddrSize((TUint_2) ReferenceValues, sizeof(ReferenceValues) - 1);

  Console.Print("Flash segment");
  Console.Indent();
  PrintSegmentWrappings(FlashSeg);
  PrintFlashSegmentData(FlashSeg);
  Console.Unindent();

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

    Console.Print("Memory segment (copy)");
    Console.Indent();
    PrintSegmentWrappings(SramSeg);
    PrintSegmentData(SramSeg);
    Console.Unindent();
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
  2024-12-15
*/
