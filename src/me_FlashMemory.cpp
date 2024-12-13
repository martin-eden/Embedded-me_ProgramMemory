// Flash memory access

/*
  Author: Martin Eden
  Last mod.: 2024-12-12
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
TBool me_FlashMemory::GetUnit(
  TUnit * Unit,
  TAddress FlashAddr
)
{
  if (FlashAddr > MaxFlashAddr)
    return false;

  asm volatile
  (
    R"(
      lpm %[Unit], Z
    )"
    :
    [Unit] "=r" (*Unit)
    :
    [FlashAddr] "z" (FlashAddr)
  );

  return true;
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

  TUnit Unit;

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

        lpm %[Unit], Z+
        st X+, %[Unit]

        sbiw %[RemainedLength], 1
        brne DataLoop_Start
    )"
    :
    [Unit] "=r" (Unit),
    [RemainedLength] "+w" (SrcFlashSeg.Size)
    :
    [MemAddr] "x" (DestMemSeg.Addr),
    [FlashAddr] "z" (SrcFlashSeg.Addr)
  );

  return true;
}

/*
  Unit getter for iterators
*/
TBool me_FlashMemory::UnitGetter(
  TAddress DestUnitAddr,
  TAddress SrcUnitAddr
)
{
  return GetUnit((TUnit *) DestUnitAddr, SrcUnitAddr);
}


/*
  2024-12-09
  2024-12-12
*/
