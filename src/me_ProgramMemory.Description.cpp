// Program memory description

/*
  Author: Martin Eden
  Last mod.: 2026-03-31
*/

#include <me_ProgramMemory.h>

using namespace me_ProgramMemory;

/*
  Check address
*/
TBool Description::CheckAddress(
  TAddress Address
)
{
  return (Address <= Description::MaxAddress);
}

/*
  2026-03-31
*/
