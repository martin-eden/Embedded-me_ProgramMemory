// Program memory access

/*
  Author: Martin Eden
  Last mod.: 2026-03-31
*/

#pragma once

#include <me_BaseTypes.h>

namespace me_ProgramMemory
{
  // Read byte from program memory
  TBool GetByteAt(TUint_1 * Byte, TAddress Address);

  namespace Description
  {
    const TAddress MaxAddress = (TAddress) 32 * 1024 - 1;

    TBool CheckAddress(TAddress Address);
  }

  namespace Core
  {
    void GetByteAt(TAddress DataPtr, TAddress);
  }
}

/*
  Macro to embed ASCIIZ into program memory segment

  Used as

    Console.PrintProgmem(M_AsProgmemSeg("Hello"));
*/
#define M_AsProgmemSeg(Asciiz) \
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
  2025 # # # #
  2026-02-20
  2026-03-31
*/
