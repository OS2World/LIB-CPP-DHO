DHO Sample Programs
=====================================================================
   There are 3 makefiles included with the sample applications:

makefile.icc   -->  for IBM's C-Set+ Compiler
makefile.gcc   -->  for the GCC/2 Compiler
makefile.emx  -->  for the EMX libraries GCC compiler

   to target a particular compiler, pass the -f <makefile> option
to the compiler.

For example: -- to build for IBM's C-Set, type:

nmake -f makefile.icc

To make a single example, execute:

make -f <makefile> <sample>.exe

For Example, to build the LBOXTEXT demo for the EMX libraries, type:

make -f makefile.emx lboxtest.exe

=====================================================================
Program Descriptions:

SIMPLE -- a simple application using a non-modal dialog as the main window

LBOXTEST -- a demo of the list box classes

THREADEX -- a thread example

WINTEST  -- the first DHO test program (justs makes a plain window)

CONTTEST  -- Container class demo

VSETTEST and
VEST2      -- Value set class demos

NBKTEST    -- Notebook class demos

PRGTEST    -- Progress Meter demos


