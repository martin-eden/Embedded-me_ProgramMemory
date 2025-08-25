// Print contents of program memory

/*
  Author: Martin Eden
  Last mod.: 2025-08-25
*/

#include <me_ProgramMemory.h>

#include <me_BaseTypes.h>
#include <me_Console.h>
#include <me_MemorySegment.h>

/*
  Dump program memory contents
*/
void DumpFlash()
{
  /*
    Idea in pseudocode is

      a = 0
      forever
        if not GetByte(b, a)
          break
        print b
        a = a + 1
  */

  using
    me_MemorySegment::TMemorySegment,
    me_MemorySegment::Freetown::FromAddrSize,
    me_MemorySegment::TSegmentIterator;

  const TUint_1 NumColumns = 16;

  TMemorySegment FlashSeg = FromAddrSize(0, TUint_2_Max);
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

  while (Rator.GetNextAddr(&Addr))
  {
    if (!me_ProgramMemory::GetByteFrom(&Byte, Addr))
      break;

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
  Console.Init();

  DumpFlash();
}

void loop()
{
}

/*
  2024 # # #
  2025-08-22
*/
