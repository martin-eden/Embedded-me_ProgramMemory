// Progmem access core functions

/*
  Author: Martin Eden
  Last mod.: 2025-08-30
*/

#include <me_ProgramMemory.h>

#include <me_BaseTypes.h>

using namespace me_ProgramMemory;

/*
  Check address
*/
TBool Freetown::CheckAddress(
  TAddress Address
)
{
  // Program memory last address. For ATmega328
  const TAddress MaxAddress = (TAddress) 32 * 1024 - 1;

  return (Address <= MaxAddress);
}

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
  2025-08-30
*/
