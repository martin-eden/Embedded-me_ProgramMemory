// Program memory access

/*
  Author: Martin Eden
  Last mod.: 2026-02-20
*/

#include <me_ProgramMemory.h>

#include <me_BaseTypes.h>

using namespace me_ProgramMemory;

/*
  Check address
*/
TBool me_ProgramMemory::CheckAddress(
  TAddress Address
)
{
  // Program memory last address. For ATmega328
  const TAddress MaxAddress = (TAddress) 32 * 1024 - 1;

  return (Address <= MaxAddress);
}

/*
  Get byte from program memory

  Fails when address is outside memory.
*/
TBool me_ProgramMemory::GetByteAt(
  TUint_1 * ByteValue,
  TAddress Address
)
{
  if (!CheckAddress(Address))
    return false;

  *ByteValue = Freetown::GetByteAt(Address);

  return true;
}

/*
  2024 # # # #
  2025 # #
*/
