// Flash memory access

/*
  Author: Martin Eden
  Last mod.: 2024-12-15
*/

#include <me_ProgramMemory.h>

#include <me_BaseTypes.h>
#include <me_UnoAddresses.h>

using namespace me_ProgramMemory;

using
  me_MemorySegment::TMemorySegment,
  me_UnoAddresses::MaxFlashAddr;

/*
  Get byte from program memory

  Fails when address is outside Flash memory.
*/
TBool me_ProgramMemory::GetByte(
  TUint_1 * Byte,
  TAddress FlashAddr
)
{
  if (FlashAddr > MaxFlashAddr)
    return false;

  asm volatile
  (
    R"(
      lpm %[Byte], Z
    )"
    :
    [Byte] "=r" (*Byte)
    :
    [FlashAddr] "z" (FlashAddr)
  );

  return true;
}

// TOperation wrapper of GetByte()
TBool me_ProgramMemory::Op_GetByte(
  TAddress Data,
  TAddress Addr
)
{
  return GetByte((TUint_1 *) Data, Addr);
}

/*
  2024-12-09
  2024-12-12
  2024-12-15
  2024-12-18
*/
