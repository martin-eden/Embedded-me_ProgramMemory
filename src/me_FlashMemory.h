// Flash memory access

/*
  Author: Martin Eden
  Last mod.: 2024-12-10
*/

#pragma once

#include <me_BaseTypes.h>
#include <me_MemorySegment.h>

namespace me_FlashMemory
{
  // Read byte from program memory
  TBool GetByte(
    TUint_1 * Value,
    TUint_2 FlashAddress
  );

  // Read segment from program memory
  TBool GetSegment(
    me_MemorySegment::TMemorySegment MemSegCopy,
    me_MemorySegment::TMemorySegment FlashSeg
  ) __attribute__ ((optimize("O1")));
}

/*
  2024-12-09
*/
