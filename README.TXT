     Information about Developer Helper, release 1.0Beta

     The Developer Helper Application Framewien is a framework
written in C++ for use in developing high quality graphical 
applications for the 32 bit OS/2 (versions 2.0 and higher).  Included 
in this framework are objects to assist in developing all types of 
applications (both character based and Presentation Manager), including 
object classes to handle threads, processes, abstract data types and 
user interface.  The overriding design goal behind Developer Helper 
is to provide the most functionality possible, exposing the great 
primitives and API's provided by IBM to the application developer, and 
encapsulating much of the trivial and error prone of setting up the 
base of applications.
     
     To develop with Developer Helper, all a developer has to do is 
concentrate on their application, and not concentrate on wrestling with
 many arcane API calls.   DHO currently supports IBM C-Set++, GCC/2, and
EMX  binaries, with source code available for adaption to other C++
compilers which are available for OS/2.  Included in this package are C++
source and header files, library files, a tutorial, this document and some 
samples.


===========================================================================
Installation:

   The DHO package is contained in a single zip file.  Unzip the file 
passing the decompression software the option to retain directory 
structure.  Assuming the package was decompressed in the root directory
of a disk, all one has to do is to include the dho\include directory 
in your compiler's search path, and link to an approriate library
found in \dho\lib.  Source code is provided for debugging purposes
in \dho\source.  Examples of makefiles for the C-Set, GCC/2 and EMX-
gcc compilers are included in this distribution.


Using DHO in a DLL
     The DHO library can be used in a DLL, but the following two precautions 
should be taken into account.     First, the utility function 
void setModule(char *modName)  must be called in some sort of DLL 
initialization function is the DLL is to access resources which are bound
 to the DLL (use of Dialogs bound to the DLL are one example).  Pass 
setModule the name of the DLL, and all additional resources will 
be loaded from the DLL.  If for some reason the DLL code must use resources 
bound to the executable, pass a NULL string to this function, and DHO will
then load all it's resources from the executable.

     Secondly, if classes are exposed or are passed into funtions located 
in a DLL, care must be taken to ensure that the version of DHO which is 
statically linked into the DLL and the version which is linked 
into the executable are the same.  Again, use of the utility functions 
const char *DHOgetBaseVersion() and const char *DHOgetRev() can be used 
to ensure proper linkage.  An example of this follows.

---------------------------------------------------------
INT main(void)
{
   initDLL(DHOgetBaseVersion(), DHOgetRev());
   return 0;
}

APIRET EXPENTRY initDLL(const char *base, const char *rev)
{
   if ((!strcmp(base, DHOgetBaseVersion())) || 
       (!strcmp(rev, DHOgetRev())))
   {
         // -- handle error condition gracefully
         exit(1);
   }
}

---------------------------------------------------------

     In most cases, if the base version of the DLL matches the base version
of the executable, the program will run properly.  The base version of the 
library changes only when there are interface changes to the libraries.  
The revision number is increased only when there are internal bug fixes and 
enhancements which do not modify any interfaces.   In the future, a DLL 
version of DHO will eliminate this need for version checking since it will be 
possible for the executable and the dll to dynamically link to the DHO 
library at runtime.



===========================================================================
Licensing Information and Disclaimer

   This library is released as is, and carries no warranty.  The author 
assumes no liability for dmamages which may vbe caused by this library,
nor for does the author guarantee that this API will remain contant

   This release (1.0Beta) is provided free to any non-commercial developer
provided that the developer sends comments and criticisms about this class 
library along with a brief description of the product developed with DHO to 
the author.  Commercial Developers may contact the author for terms regarding
DHO's commercial use.  In any circumstance, the notice "portions (c) 1994-95
Tom Bednarz" must appear in the product information dialog box.


===========================================================================
Package Contents:
   This development kit includes binaries for 3 major OS/2 compilers,
header files for use with the library, full source for the library,
a tutorial and a samples.   There are 6 binary libraries included;
they are:

   dhoiccd.lib            --  Debug library for use with IBM C-Set++
   dhoicc.lib             --  Optimized library for use with IBM C-Set++
   dhogccd.lib            --  Debug library for use with GCC/2
   dhogcc.lib             --  Optimized library for use with GCC/2
   dhoemxd.lib            --  Debug library for use with GCC andEMX
   dhoemx.lib             --  Optimized library for use with GCC and EMX


===========================================================================
Known Limitations:

   The method void removeItem(USHORT item) in the class TContainerWindow
   currently does not work properly.  A fix is in the works, and will be available
   in the next release of Developer Helper.

   Please remember that this is a Beta version, and that I will attempt to fix bugs
   and problems which are submitted to me.  It is my goal to create a premier freeware
   application framework which can be used and adapted by developers to create
   high quality OS/2 software.


===========================================================================
Please send any comments, bug reports, or questions to:

           Tom Bednarz
           766 Elm Street
           Somerset, MA 02726

           e-mail: ab150@osfn.rhilinet.gov


this package is  (c) 1994-95 Tom Bednarz, Jr.
C-Set++ and OS/2 are copyrighted trademarks of IBM Corporatrion

