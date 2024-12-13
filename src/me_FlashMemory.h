// Flash memory access

/*
  Author: Martin Eden
  Last mod.: 2024-12-13
*/

#pragma once

#include <me_BaseTypes.h>
#include <me_MemorySegment.h>

namespace me_FlashMemory
{
  // Read byte from program memory
  TBool GetUnit(
    TUnit * Unit,
    TAddress Address
  );

  // Read segment from program memory
  TBool GetSegment(
    me_MemorySegment::TMemorySegment MemSegCopy,
    me_MemorySegment::TMemorySegment FlashSeg
  ) __attribute__ ((optimize("O1")));

  // Unit getter for iterators
  TBool UnitGetter(
    TAddress DestUnitAddr,
    TAddress SrcUnitAddr
  );
}

/*
  2024-12-09
  2024-12-12
  2024-12-13
*/
