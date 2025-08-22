// Flash memory access

/*
  Author: Martin Eden
  Last mod.: 2025-08-22
*/

#pragma once

#include <me_BaseTypes.h>

namespace me_ProgramMemory
{
  // Check address
  TBool CheckAddress(TAddress Address);

  // Read byte from program memory
  TBool GetByteFrom(TUint_1 * Byte, TAddress Address);

  // TOperation: Get byte
  TBool Op_GetByte(TAddress Data, TAddress Addr);
}

/*
  2024 # # # # #
  2025-07-12
  2025-08-22
*/
