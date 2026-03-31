// Program memory access

/*
  Author: Martin Eden
  Last mod.: 2026-02-20
*/

#include <me_ProgramMemory.h>

#include <me_BaseTypes.h>

using namespace me_ProgramMemory;

/*
  Get byte from program memory

  Fails when address is outside memory.
*/
TBool me_ProgramMemory::GetByteAt(
  TUint_1 * ByteValue,
  TAddress Address
)
{
  if (!Description::CheckAddress(Address))
    return false;

  Core::GetByteAt((TAddress) ByteValue, Address);

  return true;
}

/*
  2024 # # # #
  2025 # #
*/
