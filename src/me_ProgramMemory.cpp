// Program memory access

/*
  Author: Martin Eden
  Last mod.: 2025-08-30
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
  if (!Freetown::CheckAddress(Address))
    return false;

  *ByteValue = Freetown::GetByteAt(Address);

  return true;
}

/*
  2024 # # # #
  2025-08-22
  2025-08-30
*/
