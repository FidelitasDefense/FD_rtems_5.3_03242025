pc386
=====

This board support package works with a target PC

This BSP supports a standard Intel/AMD PC on i386 and up CPUs. If on
a Pentium or above, the TSC register is used for timing calibration
purposes rather than relying entirely on the i8254.

Partial support is implemented for more modern PCs which do not have
a complete complement of legacy peripherals.


Console/Printk Device Selection
-------------------------------
The pc386 console device driver supports a variety of devices
including the VGA/keyboard and a number of serial ports. The
default console is selected based on which devices are present
in the following order of priority:

+ VGA and keyboard
+ COM1 through COM4aaa

+ Any COM devices on the PCI bus including IO and memory mapped.

Beyond the dynamic probing for device presence, a combination of
configure and boot time options are available. By default, all devices
are enabled. The configure time options are:

+ BSP_ENABLE_VGA - value of 1 to enable, 0 to disable
+ BSP_ENABLE_COM1_COM4 - value of 1 to enable, 0 to disable
+ BSP_USE_COM1_AS_CONSOLE - value of 1 forces console to COM1

An example of using these to force the console to COM1 is:

```shell
../rtems/configure --target=i386-rtems4.12 \
  USE_COM1_AS_CONSOLE=1 --enable-rtemsbsp=pc386 \
  ... other arguments ...
```

The --console and --printk options can be used to specify the
device associated with stdin, stdout, and stderr as well as
the device associated with kernel debug IO (e.g. printk()/getk()).
Both take the name of a device without the "/dev/" prefix.

The --console argument is interpreted first and assumed to
specify the console and kernel debug IO device. The --printk
is then interpreted to specify the debug kernel IO device.
For example,

```shell
--console=/dev/com1 --printk=/dev/vgacons
```

specifies that com1 is to be used for stdin, stdout, and stderr
while the VGA console is to be used for kernel debug IO.
Note that the lower case com1 is intentional as this maps to
the RTEMS device /dev/com1.

The device name may be followed by a baud rate. The following
example illustrates this:

```shell
--console=/dev/com1,19200 --printk=/dev/vgacons
```

If the specified device is not present, then a suitable fallback
device is selected. The fallback order is based upon the probe
order listed earlier.

PCI UART devices are /dev/pcicom1 etc as they are probed and found.

GDB
---

GDB can be support using:

```
 --gdb=/dev/com1,115200  : where the device and baudrate are selectable.
 --gdb-break             : halt at a break point in the BSP and wait for GDB.
 --gdb-remote-debug      : Output the GDB remote protocol data to printk
```

The GDB stub details and in shared/comm/GDB.HOWTO.


SMP
---
The following files were developed by  Erich Boleyn  <erich@uruk.org>.
The original files were copied from http://www.uruk.org/mps/ and committed
into cvs as is.  These files will be modified for RTEMS smp support,
but the original files are being committed in order to track any file
changes that occur.  We are attempting to keep these changes as minimal
and conainted as possible.

 * start/smp-imps.c
 * ../include/bsp/smp-imps.h
 * ../include/bsp/apic.h


Status
------
There are a wide range of PC configurations.  This BSP has been tested 
on only a handful.  There are configurations which do not yet work.  The
failure is suspected to be video card related.  Here is a list of
successes and failures.

```
SUCCESSES
=========
    GRUB - AMD K6 MMX 200Mhz     + S3 ViRGE
    GRUB - 486 DX 33Mhz          + Cirrus Logic CL-GD540x/542x
    GRUB - Pentium MMX 166Mhz    + S3 Trio 64V2
    GRUB - Pentium (P54C) 120Mhz + S3 Trio 64V+
    GRUB - Pentium-S 133Mhz      + S3 Trio 64V2

FAILURES
========
    GRUB - 486 DX2 66Mhz         + Cirrus Logic CL-GD5428  - reset
    GRUB - PII 333 Mhz           + STB Vision 128          - reset
    GRUB - PII 300 Mhz           + Permedia                - reset
    GRUB - Pentium 60 Mhz        + Mach 32/64              - reset
```


dec21140
--------
The dec21140 network driver is found in libchip/networking.


HOWTO
-----
+-----------------------------------------------------------------------------+
| RTEMS 4.6.0 PC386 BSP HOWTO - 2003/05/08                                    |
|                                                                             |
+-----------------------------------------------------------------------------+
| (C) Copyright 1998 -                                                        |
| - NavIST Group - Real-Time Distributed Systems and Industrial Automation    |
|                                                                             |
| Instituto Superior Tecnico * Lisboa * PORTUGAL                              |
+-----------------------------------------------------------------------------+
| Disclaimer:                                                                 |
|                                                                             |
| This file is provided "AS IS" without warranty of any kind, either          |
| expressed or implied.                                                       |
+-----------------------------------------------------------------------------+
| History:                                                                    |
|  12 June 2000 - Updated to 4.5 (Joel)                                       |
|   8 May  2003 - PXE GRUB (Chris Johns)                                      |
+-----------------------------------------------------------------------------+


1. Introduction
---------------

    This tries to explain how to setup the RTEMS host environment so
that RTEMS applications can be built for and run in a bare PC 386 or
above.

    It covers essentially the aspects of loading images, since
information concerning other issues such as building the development
tools and the RTEMS distribution can be found in the 'RTEMS 4.6.0
On-Line Library' under 'Getting Started with RTEMS for C/C++ Users'.

    Please note that everything in the following text using the
notation '<...>' is just an alias to something and should always be
substituted by the real thing!


2. Building the GNU C/C++ Cross Compiler Toolset
------------------------------------------------

    Obtaining, building and installing the tools for building the
PC386 BSP of RTEMS is covered in detail in the 'RTEMS 4.6.0 On-Line
Library' -> 'Getting Started with RTEMS for C/C++ Users'.  You can
either use pre-built toolset executables or build your own from
the instructions given there.

    This BSP is designed to work only with ELF toolset configurations.
This is format used by the i386-rtems target.


4. Building RTEMS
-----------------
    Obtaining, building and installing the tools for building the
PC386 BSP is covered in detail in the 'RTEMS 4.6.0 On-Line Library' ->
'Getting Started with RTEMS for C/C++ Users' -> 'Building RTEMS'.

    When running configure, use the following values for the listed
options with an i386-rtems toolset:

```shell
          --target=i386-rtems
          --enable-rtemsbsp=pc386
```
 
5. RTEMS Tests
--------------

    If you've completed the last step successfully, you'll find the
RTEMS sample and test files that can be loaded with GRUB in the
'<build_point>/pc386/tests' directory, RTEMS sample and test files in
a format suitable for use with NetBoot in the
'<build_point>/pc386/BootImgs' directory.


6. Loading RTEMS PC386 applications
-----------------------------------

6.1. Unarchiving
----------------

    Files which have been "tarred, gzipped" (i.e. .tar.gz or .tgz
extension) may be unarchived with a command similar to one of the
following:

```shell
      zcat <file>.tgz | tar xvof -
```
    OR

```shell
      gunzip -c <file>.tgz | tar xvof -
```
    OR

```shell
      tar xzvf <file>.tgz
```
    NOTE: gunzip -c is equivalent to zcat. On commercial (non-Linux)
Unices, since the GNU utilities are not the standard 'tar' will be
gtar (GNU tar) and 'zcat' will be 'gzcat'.

    Given that the necessary utility programs are installed, any of
the above commands will extract the contents of <file>.tar.gz into the
current directory. To view the contents of an archive without
restoring any files, use a command similar to the following:

```shell
      zcat <file>.tgz | tar tvf -
```

6.2 Using GRUB to load RTEMS PC386 applications from Floppy
-----------------------------------------------------------

    Using GRUB (GRand Unified Bootloader) is the simplest way to load
and run your PC386 BSP samples, tests and programs. You will need to build GRUB
so you need a working GCC and friends. The online documentation for GRUB lists
what you need:

    - http://www.gnu.org/manual/grub/html_node/index.html

    You can get the latest release of GRUB from its homepage:

    - http://www.gnu.org/software/grub/

    Once you obtain the .tar.gz archive from:

    - ftp://alpha.gnu.org/gnu/grub/

Download the lastest version (grub-0.93.tar.gz), change to a temporary
directory (you won't need the grub files after this and can just go ahead and
delete the whole directory structure that was generated) and unarchive
'grub-0.93.tar.gz' following the instructions given above in [2. Unarchiving].

```shell
      $ cd /tmp
      $ mkdir grub
      $ cd grub
      $ cat grub-0.93.tar.gz | gzip -d | tar xf -
```

after this is done create a build directory and decend into it:

```shell
      $ mkdir build
      $ cd build
``
then configure GRUB with the standard options:

```shell
      $ ../grub-0.93/configure
```

and if successful run make:

```shell
      $ make
```

    Once complete you should have the 'stage1' and 'stage2' files. They will be
in the directories with the same name.

    You should have two (2) formatted diskettes available. One of
these will only be used temporarily to create the other one, and we'll
refer to it as 'RAW GRUB' diskette (you can label it accordingly if
you wish). The other diskette, which we will refer to as 'GRUB FS'
should be high-level formatted with one of GRUB's supported file
systems, which are: DOS FAT, BSD FFS, and Linux ext2fs.

    A DOS FAT diskette can, obviously, be created under DOS with the
'FORMAT' command. Under Linux, the following commands are available to
add file systems to low-level formatted diskettes:

    1. To add a DOS FAT file system to a low-level formatted diskette:

      a) If you have mtools installed:

           'mformat a:'.

      b) Assuming that you are formatting the diskette in the first
         floppy disk drive ('/dev/fd0' under Linux):

           'mkdosfs /dev/fd0' or

           'mkfs.msdos /dev/fd0'.

    2. To add a Linux ext2fs file system to a low-level formatted
       diskette, assuming that you are formatting the diskette in the
       first floppy disk drive ('/dev/fd0' under Linux):

         'mke2fs /dev/fd0' or

         'mkfs.ext2 /dev/fd0'.

   Next we will install using 'rawrite' or 'dd' to the 'GRUB RAW'
diskette.

   NOTE: This will destroy any data currently on the diskette.

   Execute your OS's equivalent of (this should work for recent
FreeBSD versions and Linux just fine):

```shell
     dd if=stage1/stage1 of=/dev/fd0 bs=512 count=1
     dd if=stage2/stage2 of=/dev/fd0 bs=512 seek=1
```

   Under DOS/Windows/NT, courtesy of Eric Hanchrow (erich@microsoft.com):

     * Use the copy /b command to binary concatenate the stage1 and
       stage2 files together via:

```shell
         copy /b stage1\stage1 stage2\stage2 grub.raw
```

     * Use rawrite.exe (which is available in many places on the net and
       in some Linux distributions) to write grub.raw to a diskette.

(CCJ: I am not sure about the Windows location etc)

   Next stage: copy the 'stage1' and 'stage2' files to the 'GRUB FS'
diskette (if you are using Linux you can mount the diskette in an
appropriate mount point and then 'cp' the files to it, if it is either
a DOS FAT or an EXT2FS diskette, or in the case of a DOS FAT diskette
you can use 'mcopy' from 'mtools'.)

   After this is done boot a PC using the 'GRUB RAW' diskette. After
this is done, you will get GRUB's command line interface. Exchange
'GRUB RAW' with the 'GRUB FS' diskette in the drive and issue the
following command from GRUB's prompt:

```shell
     install=(fd0)/stage1 (fd0) (fd0)/stage2 0x8000 (fd0)/grubmenu
```
   This command will make the 'GRUB FS' diskette bootable. After this
is done, you won't require the 'GRUB RAW' diskette anymore and you can
delete the 'stage1' file from the 'GRUB FS' diskette.

   Next copy all the files you wish to load to the diskette. The GRUB
loadable test and sample files in the RTEMS distribution have '.exe'
extension and can be found under the build point in the 'pc386/tests'
directory. You can compress this files with gzip to save space if you
wish. GRUB loads 'gzipped' files transparently.

   Finally you have to create a GRUB menu configuration file. We will
call this file 'grubmenu'. You can call it anything as long as you use
the correct name in the 'install' command where we used 'grubmenu'.

   The 'grubmenu' file, as far as we are interested has the following
syntax:

     title=  Hello World Test
     kernel= (fd0)/hello.exe.gz

   You can add as many of this entries as you want to the 'grubmenu'
file. There should be one for each program you wish to load. The
'title=' line provides a description for the program that will appear
after boot in the GRUB menu for the user to choose and the 'kernel='
line describes where the file can be found by GRUB (you should leave
the '(fd0)/' part and just substitute the rest if you've copied the
files to the root directory of the diskette.

   Just boot the PC with the 'GRUB FS' diskette and you will be able
to choose which program you want to load from GRUB's menu.

   The GRUB documentation is available in HTML format in the 'docs'
directory of the GRUB tree starting with the 'index.html' file.


6.3 Using GRUB to load RTEMS PC386 applications via PXE NetBoot
----------------------------------------------------------------

PXE is the Intel Preboot Execution Environment. A number of PC 
manufactures provide a PXE option in the BIOS. This is usually a 
Net Boot option in a BIOS configuration screen. The simplist way to 
load an RTEMS application via PXE is to use GRUB as a first stage 
loader.

You will need to determine your network card, and have a working
network with a DHCP (or BOOTP), and TFTP server.

You may to find a TFTP server that does not support option 
negotiations. A google search shows a number of PC's have a buggy
PXE loader. Supressing option negotiations seems to make them
work.

You will need to build GRUB for your network card. Follow the
procedure in item 6.2 up to the configure point. At this point
run the following configure command:

```shell
    $ ../grub-0.93/configure --enable-diskless --enable-eepro100
```

for an Etherexpress Pro 100 network card, then run make:

```shell
    $ make
```

    Once complete you should have the 'stage2/pxegrub' file. Copy 
this to your TFTP server's download directory. Configure your
DHCP server to provide an IP address and download the image. For
the ISC server found on operating systems such as Linux something
like the following should do:

```shell
  #
  # PC loading RTEMS via PXE and GRUB
  #

  group
  {
    filename "/tftpboot/pxeboot";
    host rtems-pc { hardware ethernet 00:08:c7:73:41:65; }
  }
```

If all works your PC should boot and load GRUB over the network:

```shell
    GRUB  version 0.93  (639K lower / 64512K upper memory)

  Address: 10.10.10.10
  NetMask: 255.255.255.0
  Server: 10.10.10.1
  Gateway: 10.10.10.1

   [ Minimal BASH-like line editing is supported.  For the first word, TAB
     lists possible command completions.  Anywhere else TAB lists the possible
     completions of a device/filename. ]

  grub>
```
Copy your RTEMS executable to the TFTP server directory then enter 
the following GRUB commands:

```shell
  grub> root (nd)
    Filesystem type is tftp, using whole disk

  grub> kernel ticker.exe
     [Multiboot-elf, <0x100000:0x1e5a4:0x2b08>, shtab=0x122140, entry=0x10000c]

  grub> boot
```

The GRUB documents how to get GRUB to load a configuration file.


6.4 Using NetBoot to load RTEMS PC386 applications
---------------------------------------------------

    To load the '*.bt' files you can

    Alternatively, if you have a PC connected to a network with a
BOOTP server and a TFTP server (this can very well be you're Linux
RTEMS host system), you can use Gero Kuhlmann's NetBoot loader, to
load RTEMS to a diskless PC across a network. You can get it from:

   ftp://sunsite.unc.edu/pub/Linux/system/boot/ethernet/netboot-0.7.3.tar.gz

or in any of Sunsite's mirrors. It is also available from NetBoot's
homepage:

      http://www.han.de/~gero/netboot

    After unarchiving 'netboot-0.7.3.tar.gz' you should change to the
base directory of this and run:

```shell
      ./configure --disable-mknbi-dos --disable-mknbi-linux --disable-mknbi-mgl
```

    Afterwards, you should follow the instructions contained in the
'INSTALL' file also contained in the base directory, on how to setup the
server(s) and to build a boot ROM for the client PC network card, or a
boot diskette, and the PC client should be able to load the '*.bt' files
from the server.

    The important sections to check in the 'INSTALL FILE' are the last two:

    - Setup of the server (only the BOOTP and TFTP parts - ignore NFS).
      ===================

    - Setup of the client including building the bootrom
      ==================================================

all the rest can be safely ignored if you don't care to examine it.

 
7. Technical Information
------------------------

    NOTE: All the following paths are relative to the base directory
of the RTEMS distribution.

    As of the writing of this HOWTO, PC386 images can be loaded either
in low memory 0x10000 (64KB) until 0x97C00 (607K) using NetBoot or in
high memory from 0x100000 (1024KB) until the top of the available
memory using either NetBoot or GRUB.

    If you want to change the default loading address from 1024KB to
something else, just change the value of the variable RELOCADDR in the
'make/custom/pc386.cfg' file to the new value you want (make sure you
follow the instructions indicated before the definition of RELOCADDR).

    Remember that GRUB restricts the loading addresses to values above
0x100000 (1024KB), only NetBoot can load images in low memory.

    After you make any changes to RELOCADDR and if you are using
NetLoader, you'll have to recompile the
'c/src/lib/libbsp/i386/pc386/start/start16.s' file. The easiest way to
achieve this is just to 'make clean' and the 'make all' again. The
quickest way is to change to
'<build_point>/c/src/lib/libbsp/i386/pc386/start' and 'make
RTEMS_BSP=pc386 clean all'.

    When programming interrupt handlers take into account that the PIC
is reprogrammed and so you should use the interface functions provided
in '<build_point>/pc386/lib/include/irq.h> to guarantee that everything
works ok.
