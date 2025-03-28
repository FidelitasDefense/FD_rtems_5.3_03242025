mcf548x
=======
Copyright (C) 2007 embedded brains GmbH & Co. KG

Parts of the code has been derived from the "dBUG source code"
package Freescale is providing for M548X EVBs. The usage of
the modified or unmodified code and it's integration into the
generic mcf548x BSP has been done according to the Freescale
license terms.

The Freescale license terms can be reviewed in the file

   LICENSE.Freescale

The generic mcf548x BSP has been developed on the basic
structures and modules of the av5282 BSP. The license text follows:

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.


Description: Generic mcf548x BSP

The genmcf548x supports several boards based on the Freescale MCF547x/8x
ColdFire microcontrollers


Supported Hardware: mcf5484FireEngine
-----------------------------
```
CPU:         MCF548x, 200MHz
XLB:         100 MHz, which is the main clock for all onchip peripherals
RAM:         64M (m5484FireEngine)
Boot-Flash:  2M (m5484FireEngine)
Code-Flash:  16M (m5484FireEngine)
Core-SRAM:   8K
Core-SysRAM: 32K
Boot-Monitor:None
```


Supported Hardware: COBRA5475
-----------------------------
```
CPU:         MCF5475, 266MHz
XLB:         132 MHz, which is the main clock for all onchip peripherals
RAM:         128M 
Boot-Flash:  32M 
Core-SRAM:   8K
Core-SysRAM: 32K
Boot-Monitor:DBug
```

ACKNOWLEDGEMENTS:
-----------------
This BSP is based on the 

  av5282 BSP

and the work of

  D. Peter Siddons
  Brett Swimley
  Jay Monkman
  Eric Norum
  Mike Bertosh


BSP INFO:
---------
```
BSP NAME:           genmcf548x
BOARD:              various MCF547x/8x based boards
CPU FAMILY:         ColdFire 548x
CPU:                MCF5475/MCF5484
FPU:                MCF548x FPU, context switch supported by RTEMS multitasking
EMAC:               MCF548x EMAC context switch supported by RTEMS multitasking (handeld together with FPU context)
```


PERIPHERALS
-----------
```
TIMERS:             2 slice timers, 4 general purpose timers  (SLT0 is used for RTEMS clock, SLT1 is used for diagnostic pupose)
RESOLUTION:         System tick 10 millieconds (via SLT0) 
SERIAL PORTS:       Internal PSC 0-3
NETWORKING:         Internal 10/100MHz FEC on two channels
```


DRIVER INFORMATION
------------------
```
CLOCK DRIVER:       SLT0
TIMER DRIVER:       SLT1 (diagnostics)
TTY DRIVER:         PSC0-3
```


STDIO
-----
```
PORT:               PSC0 (UART mode) terminal
ELECTRICAL:         RS-232
BAUD:               9600
BITS PER CHARACTER: 8
PARITY:             None
STOP BITS:          1
MODES:              Interrupt driven (polled mode alternatively)
```


Memory map
==========
```
      Memory map of m5484FireEngine as set up by BSP initialization:

          +--------------------------------------------------+
0000 0000 |    64 MByte SDRAM (external)                     | 03FF FFFF
          .                                                  .
          .                                                  .
          .                                                  .
 
          
m5484FireEngine:
          
          
          |                                                  | 0FFF FFFF
          +--------------------------------------------------+
1000 0000 |    internal per. registers via MBAR              | 1003 FFFF
          .                                                  .
          .                                                  .
          .                                                  .
          |                                                  | 
          +--------------------------------------------------+
2000 0000 |    8K core SRAM (internal)                       | 2000 1FFF
          .                                                  .
          .                                                  .
          .                                                  .
          
m5484FireEngine:

          |                                                  | 
          +--------------------------------------------------+
E000 0000 |    16M code flash (external)                     | E0FF FFFF
          .                                                  .
	  .                                                  .
          .                                                  .
          |                                                  | 
          +--------------------------------------------------+          
FF80 0000 | External 8 MByte Flash memory                    | FF9F FFFF
          .                                                  .
	  .                                                  .
          .                                                  .          
          |                                                  | FFFF FFFF
          +--------------------------------------------------+
```

```
      Memory map for COBRA5475 as set up by DBug:

          +--------------------------------------------------+
F000 0000 |   128 MByte SDRAM (external)                     |
          .                                                  .
          .   (first 256KByte reserved for DBug)             .
          .                                                  . F03F FFFF
F040 0000 |                                                  |
          .                                                  .
          .                                                  .
          .                                                  .
          |                                                  | F7FF FFFF
          +--------------------------------------------------+
FC00 0000 |    32M code flash (external)                     |
          .                                                  .
	  .                                                  .
          .                                                  .
          |                                                  | FDFF FFFF 
          +--------------------------------------------------+          
FE00 0000 |    internal per. registers via MBAR              |
          .                                                  .
          .                                                  .
          .                                                  .
          |                                                  | FE03 FFFF 
          +--------------------------------------------------+
FF00 0000 |    8K core SRAM (internal)                       |
          .                                                  .
          .                                                  .
          .                                                  .
          |                                                  | FF00 1FFF 
          +--------------------------------------------------+
```


Interrupt map
=============
```
+-----+-----------------------------------------------------------------------+
|     |                                PRIORITY                               |
+-----+--------+--------+--------+--------+--------+--------+--------+--------+
|LEVEL|    7   |    6   |    5   |    4   |    3   |    2   |    1   |    0   |
+-----+--------+--------+--------+--------+--------+--------+--------+--------+
|  7  |        |        |        |        |        |        |        |        |
+-----+--------+--------+--------+--------+--------+--------+--------+--------+
|  6  |        |        |        |        |        |        |        |        |
+-----+--------+--------+--------+--------+--------+--------+--------+--------+
|  5  |        |        |        |        |        |        |        |        |
+-----+--------+--------+--------+--------+--------+--------+--------+--------+
|  4  |        |        |        |        |        |        |        |  SLT0  |
+-----+--------+--------+--------+--------+--------+--------+--------+--------+
|  3  | PSC 0  | PSC 1  | PSC 2  | PSC 3  |        |        |        |        |
+-----+--------+--------+--------+--------+--------+--------+--------+--------+
|  2  |        |        |        |        | FEC0/1 | MCDMA  |        |        |
+-----+--------+--------+--------+--------+--------+--------+--------+--------+
|  1  |        |        |        |        |        |        |        |        |
+-----+--------+--------+--------+--------+--------+--------+--------+--------+
```


TIMING TESTS
------------

tbd.
