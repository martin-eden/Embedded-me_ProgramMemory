// Flash memory access

/*
  Author: Martin Eden
  Last mod.: 2024-12-10
*/

#include <me_FlashMemory.h>

#include <me_BaseTypes.h>
#include <me_MemorySegment.h>

// Flash size minus one. Should move this to some other module.
// (That's also known as FLASHEND macro. But we don't like macros.)
const TUint_2 MaxFlashAddr = (TUint_2) 32 * 1024 - 1;

/*
  Get byte from program memory
*/
TBool me_FlashMemory::GetByte(
  TUint_1 * Byte,
  TUint_2 FlashAddr
)
{
  // Check that address is inside RAM
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

/*
  Get memory segment from program memory
*/
TBool me_FlashMemory::GetSegment(
  me_MemorySegment::TMemorySegment DestMemSeg,
  me_MemorySegment::TMemorySegment SrcFlashSeg
)
{
  /*
    Well, we can just call GetByte() in a loop here.
    But ATmega328P has "LPM r, Z+". Indirect load byte
    from flash and increment pointer.

    So we'll craft another piece of asm code.
  */

  TUint_1 Storage;

  if (SrcFlashSeg.Size == 0)
    return true;

  if (DestMemSeg.Size < SrcFlashSeg.Size)
    return false;

  // Check that we won't leave flash address space
  {
    TUint_4 FlashEndAddr = (TUint_4) SrcFlashSeg.Addr + SrcFlashSeg.Size - 1;
    if (FlashEndAddr > MaxFlashAddr)
      return false;
  }

  asm volatile
  (
    R"(
      DataLoop_Start:

        lpm %[Storage], Z+
        st X+, %[Storage]

        sbiw %[RemainedLength], 1
        brne DataLoop_Start
    )"
    :
    [Storage] "=r" (Storage),
    [RemainedLength] "+w" (SrcFlashSeg.Size)
    :
    [MemAddr] "x" (DestMemSeg.Addr),
    [FlashAddr] "z" (SrcFlashSeg.Addr)
  );

  return true;
}

/*
  2024-12-09
*/
