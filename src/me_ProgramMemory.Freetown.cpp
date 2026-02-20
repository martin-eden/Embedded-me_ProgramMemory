// Progmem access core functions

/*
  Author: Martin Eden
  Last mod.: 2025-08-30
*/

#include <me_ProgramMemory.h>

#include <me_BaseTypes.h>

using namespace me_ProgramMemory;

/*
  Get byte from program memory
*/
TUint_1 Freetown::GetByteAt(
  TAddress Address
)
{
  TUint_1 Result;

  asm
  (
    "lpm %[Result], Z"
    : [Result] "=r" (Result)
    : "z" (Address)
  );

  return Result;
}

/*
  2024 # # # #
  2025 #
*/
