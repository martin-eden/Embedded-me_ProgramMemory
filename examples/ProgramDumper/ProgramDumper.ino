// Print contents of program memory

/*
  Author: Martin Eden
  Last mod.: 2025-08-29
*/

#include <me_ProgramMemory.h>

#include <me_BaseTypes.h>
#include <me_BaseInterfaces.h>
#include <me_Console.h>

/*
  Dump program memory contents
*/
void DumpFlash()
{
  /*
    Idea in pseudocode is

      addr = 0
      while GetByte(b, addr)
        print b
        addr = addr + 1
  */

  const TUint_1 NumColumns = 16;

  TAddressSegment FlashSeg = { .Addr = 0, .Size = TUint_2_Max };
  TAddressIterator Rator;

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
