// Flash memory access

/*
  Author: Martin Eden
  Last mod.: 2024-12-15
*/

#include <me_FlashMemory.h>

#include <me_BaseTypes.h>
#include <me_MemorySegment.h>
#include <me_UnoAddresses.h>

using
  me_MemorySegment::TMemorySegment,
  me_UnoAddresses::MaxFlashAddr;

/*
  Get byte from program memory

  Fails when address is outside Flash memory.
*/
TBool me_FlashMemory::GetByte(
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
TBool me_FlashMemory::Op_GetByte(
  TAddress Data,
  TAddress Addr
)
{
  return GetByte((TUint_1 *) Data, Addr);
}


/*
  Get memory segment from program memory

  Fails when destination segment is too small
  or when source segment not inside Flash memory.
*/
TBool me_FlashMemory::GetSegment(
  TMemorySegment DestMemSeg,
  TMemorySegment SrcFlashSeg
)
{
  /*
    Well, we can just call GetUnit() in a loop here.
    But ATmega328P has "LPM r, Z+". Indirect load byte
    from flash and increment pointer.

    So we'll craft another piece of asm code.
  */

  TUint_1 Byte;

  if (SrcFlashSeg.Size == 0)
    return true;

  // No memory to hold expected data? Fail.
  if (DestMemSeg.Size < SrcFlashSeg.Size)
    return false;

  // Check that we won't leave flash address space
  {
    TUint_4 FlashEndAddr =
      (TUint_4) SrcFlashSeg.Addr + SrcFlashSeg.Size - 1;

    if (FlashEndAddr > MaxFlashAddr)
      return false;
  }

  asm volatile
  (
    R"(
      DataLoop_Start:

        lpm %[Byte], Z+
        st X+, %[Byte]

        sbiw %[RemainedLength], 1
        brne DataLoop_Start
    )"
    :
    [Byte] "=r" (Byte),
    [RemainedLength] "+w" (SrcFlashSeg.Size)
    :
    [MemAddr] "x" (DestMemSeg.Addr),
    [FlashAddr] "z" (SrcFlashSeg.Addr)
  );

  return true;
}

/*
  2024-12-09
  2024-12-12
  2024-12-15
  2024-12-18
*/
