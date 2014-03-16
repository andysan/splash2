SPLASH 2 Benchmarks
===================

This is an unofficial version of the original SPLASH2 [1] benchmarks
modified to work on modern systems and tool chains. Please note that
this is SPLASH distribution is not made by the original authors of
SPLASH. However, we strive to only make minimal changes to the
applications and benchmarks to enable them to build and run on modern
systems without affecting their overall behavior.

**Warning:** This is work in progress! Some benchmarks do not work
 reliably on 64-bit machines since they make assumptions that are
 illegal according to new C standards. For example, long, int, and
 pointers are sometimes considered to be of the same length. It is our
 long-term goal to fix-up such bugs to make the benchmarks usable on
 64-bit machines.


ANL Macros
==========
This SPLASH distribution contains two sets of parallelization
macros. These macros are known as the "ANL macros" since originated
from Argonne National Laboratories. 

c.m4.null
---------
These are the default ANL macros distributed with SPLASH2. They do not
provide any support for parallelization and can be used to generate
binaries for single-threaded reference runs.


c.m4.posix
----------
These macros implement support for the standard POSIX threading
API. They are used by default when building this modified version of
SPLASH2.

Despite support for barriers in recent POSIX standard, these ANL
macros provide their own implementation using locks and conditional
variables. There are two reasons for this design decision: First, this
maintains backwards compatibility with the old ANL macros which only
specify the number of threads waiting on barrier when entering the
barrier. POSIX requires this to be known when instantiating the
barrier. Second, POSIX barriers are optional and not supported on some
systems (e.g., MacOS X).


Build System
============

All benchmarks are built from a central makefile in the codes
directory. Individual benchmarks can be built by specifying the target
binary's name relative to the build directory (e.g., `make
apps/fmm/fmm`) or by using one of the target/group specific build
targets (see the makefile).

Build parameters should normally be specified in the global
makefile. The default parameters have are known to work on gcc on
Linux, your system might require some tweaking. See the
`CFLAGS`/`LDFLAGS`/`LIBS` variables in the makefile. Additionally, the
compiler flags of individual benchmarks can be manipulated in the main
makefile using benchmark-specific variables (e.g., LU_CFLAGS). For
details, see the Rules.mk file in the application's source directory.


Bibliography
============
1. S. C. Woo, M. Ohara, E. Torrie, J. P. Singh, and A. Gupta, 
"The SPLASH-2 programs: characterization and methodological considerations," in
Proc. International Symposium on Computer Architecture (ISCA), 1995
