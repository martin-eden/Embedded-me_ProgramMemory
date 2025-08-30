// Print contents of program memory

/*
  Author: Martin Eden
  Last mod.: 2025-08-30
*/

#include <me_ProgramMemory.h>

#include <me_BaseTypes.h>
#include <me_Console.h>

/*
  Dump program memory contents
*/
void DumpFlash()
{
  TUint_1 Byte;

  for (TAddress Addr = 0; true; ++Addr)
  {
    if (!me_ProgramMemory::GetByteAt(&Byte, Addr))
      break;

    Console.Print(Byte);
  }
  Console.EndLine();
}

void setup()
{
  Console.Init();

  Console.Print("( [me_ProgramMemory] test");

  DumpFlash();

  Console.Print(") Done");
}

void loop()
{
}

/*
  2024 # # #
  2025-08-22
  2025-08-30
*/
