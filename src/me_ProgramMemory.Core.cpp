// Progmem access core functions

/*
  Author: Martin Eden
  Last mod.: 2026-03-31
*/

#include <me_ProgramMemory.h>

#include <me_BaseTypes.h>

using namespace me_ProgramMemory;

/*
  Get byte from program memory
*/
void Core::GetByteAt(
  TAddress DataPtr,
  TAddress Address
)
{
  asm
  (
    "lpm %[Result], Z"
    : [Result] "=r" (*(TUint_1 *) DataPtr)
    : "z" (Address)
  );
}

/*
  2024 # # # #
  2025 #
  2026-03-31
*/
