## What

(2024-12)

Program memory reading. Arduino library.

Well, we have `pgmspace.h` but it's messy.

Here is no `#ifdef`'s, no macros and only one base function.

## Code

* [Interface][Interface]
* [Implementation][Implementation]
* Examples
  * [Flash dumper][ProgramDumper] - dump whole program memory

## Requirements

  * bash
  * arduino-cli

## Install/remove

Well, no custom-built scripts here, unlike in my previous embedded repos.

You'll need another libraries which are mine separate repos.

Go clone [repo to get all my libraries][GetLibs]. Run shell scripts.
They will download and install all my embedded stuff, including this.

## Compile

Zero-warnings compilation:

```bash
arduino-cli compile --fqbn arduino:avr:uno --quiet --warnings all . --build-property compiler.cpp.extra_flags="-std=c++1z"
```

## See also

* [My other embedded C++ libraries][Embedded]
* [My other repositories][Repos]

[Interface]: src/me_ProgramMemory.h
[Implementation]: src/me_ProgramMemory.cpp
[ProgramDumper]: examples/ProgramDumper/ProgramDumper.ino

[GetLibs]: https://github.com/martin-eden/Embedded-Framework-GetLibs

[Embedded]: https://github.com/martin-eden/Embedded_Crafts
[Repos]: https://github.com/martin-eden/contents
