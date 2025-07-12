// Flash memory access

/*
  Author: Martin Eden
  Last mod.: 2025-07-12
*/

#pragma once

#include <me_BaseTypes.h>
#include <me_MemorySegment.h>

namespace me_ProgramMemory
{
  // ( Program memory addresses span. CPU-dependent
  // Size
  const TUint_2 Size = 32 * 1024L;
  // Minimum address
  const TAddress MinAddr = 0;
  // Maximum address
  const TAddress MaxAddr = Size - 1;
  // )

  // Read byte from program memory
  TBool GetByte(TUint_1 * Byte, TAddress Address);

  // TOperation: Get byte
  TBool Op_GetByte(TAddress Data, TAddress Addr);
}

/*
  2024-12-09
  2024-12-12
  2024-12-13
  2024-12-15
  2024-12-18
  2025-07-12
*/
