// Flash memory access

/*
  Author: Martin Eden
  Last mod.: 2025-08-22
*/

#include <me_ProgramMemory.h>

#include <me_BaseTypes.h>

using namespace me_ProgramMemory;

// Program memory last address. For ATmega328
const TAddress MaxAddress = (TAddress) 32 * 1024 - 1;

/*
  Check address
*/
TBool me_ProgramMemory::CheckAddress(
  TAddress Address
)
{
  return (Address <= MaxAddress);
}

/*
  Get byte from program memory

  Fails when address is outside Flash memory.
*/
TBool me_ProgramMemory::GetByteFrom(
  TUint_1 * ByteValue,
  TAddress FlashAddress
)
{
  if (!CheckAddress(FlashAddress))
    return false;

  asm volatile
  (
    R"(
      lpm %[ByteValue], Z
    )"
    :
    [ByteValue] "=r" (*ByteValue)
    :
    [FlashAddress] "z" (FlashAddress)
  );

  return true;
}

/*
  Get byte in format of TOperation
*/
TBool me_ProgramMemory::Op_GetByte(
  TAddress Data,
  TAddress Address
)
{
  return GetByteFrom((TUint_1 *) Data, Address);
}

/*
  2024 # # # #
  2025-08-22
*/
