// Program memory access

/*
  Author: Martin Eden
  Last mod.: 2025-08-27
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
  Macro to embed ASCIIZ into program memory segment

  Used as

    Console.PrintProgmem(AsProgmemSeg("Hello"));
*/
#define AsProgmemSeg(Asciiz) \
  ( \
    __extension__ \
    ( \
      { \
        static const TUint_1 ProgmemData[] [[gnu::progmem]] = (Asciiz); \
        \
        TAddressSegment ProgmemSeg = \
          { \
            .Addr = (TAddress) ProgmemData, \
            .Size = sizeof(ProgmemData) - 1 \
          }; \
        ProgmemSeg; \
      } \
    ) \
  )

/*
  2024 # # # # #
  2025-07-12
  2025-08-22
  2025-08-27
*/
