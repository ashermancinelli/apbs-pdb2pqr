/** 
 * <center>
 * @mainpage APBS Users Guide
 *  
 * APBS was written by Nathan A. Baker.<br>
 * Additional contributing authors listed in the code documentation.
 * </center>
 * 
 *  <hr width="100%">
 *  @section toc   Table of Contents
 *  <ul>
 *  <li> @ref license
 *  <li> @ref intro
 *  <li> @ref installation
 *  <li> @ref tour
 *    <ul>
 *    <li> @ref exec
 *    <li> @ref test
 *    <li> @ref tools
 *    <li> @ref examplecode
 *    </ul>
 *  <li> @ref usage
 *    <ul>
 *    <li> @ref read
 *    <li> @ref elec
 *    <li> @ref print
 *    </ul>
 *  <li> @ref lists
 *  <li> @ref bugs
 *  <li> @ref reading
 *  <li> @ref authors
 *  <li> @ref programming
 *    <ul> 
 *    <li> @ref style
 *    <li> @ref api
 *      <ul>
 *      <li> <a href="modules.html">Modules</a>
 *      <li> <a href="annotated.html">Class list</a>
 *      <li> <a href="functions.html">Class members</a>
 *      <li> <a href="globals.html">Class methods</a>
 *      </ul>
 *    </ul>
 *  </ul>
 * 
 * <hr width="100%">
 * @section license License
 *
 * APBS -- Adaptive Poisson-Boltzmann Solver
 * <br><br>
 * Nathan A. Baker (baker@biochem.wustl.edu) <br>
 * Dept. of Biochemistry and Molecular Biophysics <br>
 * Center for Computational Biology <br>
 * Washington University in St. Louis <br>
 * <br><br>
 * Additional contributing authors listed in the code documentation.
 * <br><br>
 * Copyright (c) 2003.  Washington University in St. Louis.<br>
 * All Rights Reserved.<br>
 * Portions Copyright (c) 1999-2003.  The Regents of the University of
 * California.  <br>
 * Portions Copyright (c) 1995.  Michael Holst.<br>
 * <p>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the <a href="http://www.gnu.org/licenses/gpl.txt">GNU
 * General Public License</a> as published by the Free Software Foundation;
 * either version 2 of the License, or (at your option) any later version.
 * <p>
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * <p>
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
 * 
 *  <hr width="100%">
 *  @section intro Introduction
 *
 * APBS is a software package for the numerical solution of the
 * Poisson-Boltzmann equation (PBE), one of the most popular continuum models
 * for describing electrostatic interactions between molecular solutes in
 * salty, aqueous media. Continuum electrostatics plays an important role in
 * several areas of biomolecular simulation, including:
 * <ul>
 * <li> simulation of diffusional processes to determine ligand-protein and
 * <li> protein-protein binding kinetics,
 * <li> implicit solvent molecular dynamics of biomolecules ,
 * <li> solvation and binding energy calculations to determine 
 *      ligand-protein and protein-protein equilibrium binding constants and 
 *      aid in rational drug design,
 * <li> and biomolecular titration studies.
 * </ul>
 * APBS was designed to efficiently evaluate electrostatic properties for such
 * simulations for a wide range of length scales to enable the investigation of
 * molecules with tens to millions of atoms.
 * 
 *  <p> APBS was primarily written by <a
 *  href="http://www.biochem.wustl.edu/~baker">Nathan
 * Baker</a> during his graduate work with <a
 * href="http://mccammon.ucsd.edu/">J.  Andrew McCammon</a> and <a
 * href="http://www.scicomp.ucsd.edu/~mholst/">Michael Holst</a>.  A complete
 * list of authors is available <a href="#authors">here</a>.  APBS
 * relies several libraries written by Mike Holst and members of the Holst
 * group.  These include <a
 * href="http://scicomp.ucsd.edu/~mholst/codes/pmg/index.html">PMG</a>
 * (multigrid solver for Cartesian mesh discretization), <a
 * href="http://www.fetk.org">FEtk</a> (provides finite element framework,
 * error estimators, and solvers), and <a
 * href="http://scicomp.ucsd.edu/~mholst/codes/maloc/index.html">MALOC</a>
 * (hardware abstraction library for code portability).
 * 
 * <p>
 * <i><b>Please acknowledge your use of APBS</b></i> by citing: <br>
 *   N. A. Baker, D.  Sept, S.  Joseph, M. J. Holst, J. A. McCammon.
 *   Electrostatics of nanosystems: application to microtubules and the
 *   ribosome.  <i>Proc. Natl.  Acad. Sci.  USA</i> <b>98</b>, 10037-10041,
 *   2001.  <a href="http://www.pnas.org/cgi/reprint/181342398v1">(Link to
 *   paper)</a>
 * 
 * <p> 
 * For more information on Poisson-Boltzmann methods and theory, please visit
 * the excellent <a
 * href="http://www.biophysics.org/btol/compute.html#3C">Introduction to
 * Continnuum Electrostatics</a> chapter (by Mike Gilson) of the <a
 * href="http://www.biophysics.org/btol/">Biophysics Textbook On-line</a>.
 * APBS contains a number of <a href="#test">examples</a> which are described
 * in detail <a href="#test">in this document</a>.  I've also prepared a brief
 * but more generic set of notes on PB energy calculations with APBS (avilable
 * in <a href="pb_data.pdf">PDF</a> or <a
 * href="pb_data.ps">Postscript</a>).  Finally, a number of the papers
 * describing APBS are listed in the <a href="#reading">Further Reading</a>
 * section of this document.
 * <p>
 * This version of the APBS code contains sequential and parallel fast
 * multigrid Poisson-Boltzmann solver.  Subsequent releases will include
 * adaptive finite element technology.  This release is primarily intended to
 * allow users to get familiar with the code and break it.  Before going too
 * much farther in this guide, please view the @ref license. 
 *
 * <hr width="100%"> 
 * @section installation Installation
 * 
 * <b>Prerequisites</b>:<br> 
 * You will definitely need
 * <ul>
 * <li> The latest version of <a href="http://agave.wustl.edu/apbs">APBS</a>
 * <li> <a
 * href="http://www.scicomp.ucsd.edu/~mholst/codes/maloc/index.html">MALOC</a>
 * (a hardware abstraction library)
 * </ul>
 * It may also be useful to have
 * <ul>
 * <li> A version of MPI for parallel jobs (try <a
 * href="http://www-unix.mcs.anl.gov/mpi/mpich/">MPICH</a>).  However, this is
 * not necessary if the <a href="#async">async</a> option is used in parallel
 * runs.
 * <li> <a href="http://www.opendx.org/">OpenDX</a> for general visualization
 * <li> <a href="http://www.ks.uiuc.edu/Research/vmd/">VMD</a> for biomolecule
 * visualization
 * </ul>
 * 
 * <b>Directories:</b>
 * These instructions will assume a local (home directory, etc.) installation
 * of APBS.  It may also be worthwhile to check out <a
 * href="#machine-specific">Machine-specific notes</a> prior to starting the
 * installation.
 * <ol>
 * <li> Choose a directory where you'd like APBS and MALOC to be installed,
 * we'll choose <code>/home/nbaker/pbe</code>. Using a Bourne-like shell
 * (<code>bash</code> or <code>sh</code>), do:
 * <pre>
 * # mkdir -p /home/nbaker/pbe /home/nbaker/pbe/dist
 * # TOP=/home/nbaker/pbe; export TOP
 * # FETK_INCLUDE=${TOP}/dist/include; export FETK_INCLUDE
 * # FETK_LIBRARY=${TOP}/dist/lib; export FETK_LIBRARY
 * </pre>
 * or, using a C-shell-like shell (<code>csh</code> or <code>tcsh</code>), do
 * <pre>
 * # mkdir -p /home/nbaker/pbe /home/nbaker/pbe/dist
 * # setenv TOP /home/nbaker/pbe
 * # setenv FETK_INCLUDE ${TOP}/dist/include
 * # setenv FETK_LIBRARY ${TOP}/dist/lib
 * </pre>
 * The <code>dist</code> subdirectory will be used to store header files and
 * libraries for APBS and MALOC.S
 * 
 * <p> If you're planning on using MPI, you'll also need to set some additional
 * environmental variables.  The variable <code>FETK_MPI_INCLUDE</code> points
 * to the directory where the MPI header files reside (<code>mpi.h</code>) and
 * the variable <code>FETK_MPI_LIBRARY</code> gives the directory with the MPI
 * libraries (either <code>libmpi.a</code> or <code>libmpich.a</code>).  These
 * variables need to be defined using commands like
 * <pre>
 * # FETK_MPI_INCLUDE=/usr/share/mpi/include; export FETK_MPI_INCLUDE
 * # FETK_MPI_LIBRARY=/usr/share/mpi/lib; export FETK_MPI_LIBRARY
 * </pre>
 * for a Bourne-like shell and
 * <pre>
 * # setenv FETK_MPI_INCLUDE /usr/share/mpi/include
 * # setenv FETK_MPI_LIBRARY /usr/share/mpi/lib
 * </pre>
 * for a C-shell type of environment.  Note that the paths given in the above
 * example are system-dependent; your variable definitions will likely be
 * different.
 * 
 * <li> Unpack the MALOC and APBS source code:
 * <pre>
 * # cd ${TOP}
 * # gzip -dc maloc.tar.gz | tar xvf -
 * # gzip -dc apbs-0.2.6.tar.gz | tar xvf -
 * </pre>
 * <li> Compile and install the MALOC libraries.  You should read the MALOC
 * installation guide before doing this, but if you just want a simple
 * sequential code, the following should work:
 * <pre>
 * # cd ${TOP}/maloc
 * </pre>
 * If you are not starting from a clean distribution (i.e., the tar file), you
 * need to run <code>make distclean</code> now (and ignore any error messages).
 * There are two common installation options that APBS users will need to
 * choose from:
 *  <ul>
 *  <li> To compile MALOC without MPI (parallel) support, do:
 *      <pre>
 *      # ./configure --prefix=${TOP}/dist
 *      # make
 *      # make install
 *      </pre>
 *  <li> To compile MALOC with MPI (parallel) support, do:
 *      <pre>
 *      # ./configure --prefix=${TOP}/dist --enable-mpi
 *      # make
 *      # make install
 *      </pre>
 *      Be sure to watch the output of the configure script for MPI-related
 *      issues; specifically, both <code>mpi.h</code> and <code>libmpi.h</code>
 *      or <code>libmpich.a</code> should be found.
 *  </ul>
 * With either installation option, you should find the MALOC headers and
 * libraries installed in the directory <code>${TOP}/dist</code>.
 * <li> Compile and install APBS.  There aren't any special configuration
 * options for <i>stable</i> features of APBS.  Therefore, you simply:
 * <pre>
 * # cd ${TOP}/apbs
 * </pre>
 * If you are not starting from a clean distribution (i.e., the tar file), you
 * need to run <code>make distclean</code> now (and ignore any error messages).
 * <pre>
 * # ./configure --prefix=${TOP}/dist
 * # make
 * # make install
 * </pre>
 * <i><b>If you have vendor-supplied BLAS libraries for your
 * platform, set the environmental variable <pre>BLASPATH</pre> to their
 * location and use them with APBS by inkoving the 
 * <pre>--with-blas=${BLASPATH}</pre> flag during configuration.</b></i>
 * <li> You should now find the APBS executable in the
 * <code>${TOP}/dist/bin/${triplet}</code> directory,
 * </ol>
 * where ${triplet} is a machine/compiler/os-specific directory to facilitate
 * compilation across platforms.
 * If at any point you made a mess and need to start over, simply
 * <pre>
 * # make distclean
 * </pre>
 * in the APBS or MALOC package directories and repeat the installation
 * process.
 * 
 * <br><b><a name="machine-specific">Machine-specific notes</a></b>
 * Of course, every machine seems to behave a bit differently.  One general
 * improvement is the use of vendor-provided BLAS libraries via the
 * <code>--with-blas</code> configure flag.  Specifically, if you installed
 * your machine's libblas.a in the directory <code>/blas/is/here</code>, you
 * would configure APBS as:
 * <pre>
 * # ./configure --with-blas=/blas/is/here ...
 * </pre>
 * where the <code>...</code> denotes other configure options you need.  Here
 * are a few additional notes on installing APBS on various platforms; if you
 * encounter any interesting configuration/compilation behavior or useful
 * optimization tricks, please <a href="mailto:apbs-users@cholla.wustl.edu">let
 * me know</a>.  
 * <ul>
 * <li>Intel ix86 processor family (Windows)<br>
 * Currently, APBS compiles runs under the <a
 * href="http://www.cygwin.com">Cygwin Windows UNIX environment</a>, which is
 * available for most flavors of Windows.  You'll need to install the entire
 * Cygwin development "tree" (in the installer GUI) as well as the readline
 * source code in order to get MALOC working.  Also, it is recommended that you
 * upgrade to the latest version of gcc/g77/g++.
 * <li>Intel ix86 processor family (Linux)<br>
 * First, you should go get the BLAS libraries provided by the <a
 * href="http://www.intel.com/software/products/mkl/mkl52">Intel Math Kernel
 * Library</a> (look for the free evaluation version).  Next, you should
 * definitely use the <a
 * href="http://www.intel.com/software/products/compilers/">Intel compilers</a>
 * for Linux (also free!).  If you have access to these compilers, set the
 * following environmental variables
 * <pre>
 *   CC=icc
 *   CXX=icc
 *   F77=ifc
 * </pre>
 * You will also want to set some optimization flags; these vary from system to
 * system and you should read the compiler documentation to find out what's
 * right for your machine.  However, as an example, I use the following for my
 * Pentium III Xeon:
 * <pre>
 *  CFLAGS='-O2 -tpp6'
 *  FFLAGS='-O2 -tpp6'
 * </pre>
 * <b>However, please note that Intel compilers are currently not supported
 * under RedHat 9 and do not seem to work with this OS (without substantial
 * effort).  Therefore, you will need use GNU compilers for these systems.</b>
 * <p>
 * If you use the GNU compilers, you will end up with slower code.
 * However, you will likely want to use the following settings to make it as
 * fast as possible:
 * <pre>
 *   CC=gcc
 *   CXX=g++
 *   F77=g77
 *   CFLAGS='-O2 -ffast-math -m486 -funroll-loops'
 *   FFLAGS='-O2 -ffast-math -m486 -funroll-loops'
 * </pre>
 * <b>Please note that there have been reports that using the -O3 and/or the
 * -march=pentium4 flags can results in versions of APBS which give incorrect
 * numerical results.</b>
 * <li> NPACI IBM RS/6000 Power3 Blue Horizon supercomputer
 * <p>
 * The login nodes (tfXXXi or tflogin) of Blue Horizon recently stopped
 * allowing interactive jobs.  This is bad news for the autoconf-based
 * configure script, since this script runs several executables to test from
 * functionality.  Therefore, this code must be compiled on the interactive
 * nodes (b80login.sdsc.edu).  The following will compile APBS on Blue Horizon:
 * <pre>
 *   BLASPATH=/usr/lib; export BLASPATH
 *   FETK_INCLUDE=${TOP}/dist/include; export FETK_INCLUDE
 *   FETK_LIBRARY=${TOP}/dist/lib; export FETK_LIBRARY
 * 
 *   MP_EUILIB=us
 *   CC=mpcc 
 *   F77=mpxlf95 
 *   CFLAGS="-bmaxdata:0x80000000 -bmaxstack:0x10000000 -L/usr/local/apps/mass -lmass -lessl -O3 -qstrict -qarch=pwr3 -qtune=pwr3 -qmaxmem=-1 -qcache=auto"
 *   FFLAGS="-qfixed=132 -bmaxdata:0x80000000 -bmaxstack:0x10000000 -L/usr/local/apps/mass -lmass -lessl -O3 -qstrict -qarch=pwr3 -qtune=pwr3 -qmaxmem=-1 -qcache=auto"
 *   export MP_EUILIB CC F77 CFLAGS FFLAGS
 * 
 *   cd ${TOP}/maloc
 *   cat configure | sed -e "s/cross_compiling=no/cross_compiling=yes/g" > configure
 *   ./configure --prefix=${TOP}/dist --enable-mpi
 *   make && make install
 * 
 *   cd ${TOP}/apbs
 *   cat configure | sed -e "s/cross_compiling=no/cross_compiling=yes/g" > configure
 *   ./configure --prefix=${TOP}/dist --with-blas=${BLASPATH}
 *   make && make install
 * </pre>
 * and installation (should) proceed normally.  However, I've personally
 * experienced all sorts of strangeness on this machine.  Be sure to watch out
 * for varying OS versions across the login and interactive nodes, undefined
 * poe variables (usually of the form MP_*), and undefined NLSPATH (which pops
 * up in a non-deterministic fashion and can often be fixed by simply logging
 * out, getting some coffee, and logging back in).  Aren't supercomputers
 * great?
 * <p>
 * Note that the actual command line declaration should contain no line breaks
 * and continuations; these seem to screw up sed (used by configure) under
 * AIX.  The bmaxdata linker flag controls the amount of heap the program is
 * allocated to allocate.  It is a hexadecimal number representing the number
 * of bytes available.  The NPACI documentation suggests 0x80000000, which
 * gives 2048 MB of heap space.  While the Blue Horizon nodes do have 8 GB of
 * memory available per 8-processor node, much of this is taken up by the OS.
 * In practice, for 8 tasks per node, about 400 MB of heap space is available
 * to each task (this means OS-related tasks take up nearly 5 GB of memory!) .
 * In any case, -bmaxdata:0x18000000 seems to be a safe choice as it provides
 * 384 MB heap space per task.  The use of vendor-supplied BLAS is also
 * recommended!  
 * <li> Sun <br>
 * If you're compiling this on a Sun platform, you definitely
 * need to use the Sun compilers, GCC generates <i>very slow</i> executables.
 * <li> Alpha <br>
 * If you're compiling this on an Alpha platform (Linux or OSF), you definitely
 * need to use the Alpha compilers:
 * <pre>
 *     CC='ccc'; export CC
 *     CXX='cxx'; export CXX
 *     F77='fort'; export F77
 * </pre>
 * It's also worthwhile to add the '-arch' flag (via the CFLAGS variable) and,
 * <i>as always</i>, use vendor BLAS.
 * </ul>
 * 
 * <hr width="100%">
 * @section tour Quick tour of APBS
 * 
 * @subsection exec Main executable
 * Right now, there is only one executable
 * (<code>${TOP}/dist/bin/${prefix}/apbs</code>) for APBS, where
 * <code>${TOP}</code> is the top-level install directory (see @ref
 * installation section) and <code>${prefix}</code> is
 * a machine/compiler/os-specific string to facilitate compilation across
 * multiple platforms.  The executable invoked with the syntax
 * <pre>
 *    apbs input-path;
 * </pre>
 * where <code>input-path</code> is the path to a specially formatted input
 * file (see @ref usage for more information on the input file).  Besides the
 * output files specified in <code>input-path</code> (i.e., for visualization),
 * APBS writes output to three places:
 * <ul>
 * <li> Standard output (you'll see it on your screen if you don't redirect it
 * somewhere).  This is all the basic information that you'll want to know
 * about each run.
 * <li> Standard error (you'll see it on your screen if you don't redirect it
 * somewhere).  If something goes wrong, a message is printed here.
 * <li> The file <code>io.mc</code> (or <code>io.mc_#</code> for parallel runs,
 * where <code>#</code> is the processor ID).  This gives you detailed
 * information about the progress of the run and is especially useful for
 * monitoring the solver step of the calculation.
 * </ul>
 * 
 * @subsection test Test systems and examples
 * The directory <code>apbs/examples</code> contains several test systems
 * and example scripts which show how to use APBS for binding energy, solvation
 * energy, and force calculations.  The file
 * <code>apbs/examples/README.html</code> contains descriptions of the test
 * cases as well as anticipated results.
 * 
 * @subsection tools Tools, scripts, and parameters
 * <ul>
 * <li> Parameterization
 *   <ul>
 *   <li><a href="http://nbcr.sdsc.edu/pdb2pqr/index.html">PDB2PQR web
 *   service</a><br>
 *   Fix, protonate, and convert a PDB file to PQR format using an
 *   NBCR-supported web portal with a <a
 *   href="http://www.cmbi.kun.nl/whatif/">WHATIF</a> backend.  Provided by
 *   Jens Nielsen and Jerry Greenberg; supported by NBCR.
 *   <li>apbs/tools/conversion/pdb2pqr/pdb2pqr.py<br>
 *   A command line Python script to convert a PDB file to PQR format by 
 *   using a supported forcefield - AMBER02, CHARMM23, or PARSE.
 *   Contributed by Todd Dolinsky, Jens Nielsen, and Nathan Baker.
 *   <li>apbs/tools/conversion/qcd2pqr.awk  <br> 
 *   Convert a QCD file (i.e., UHBD format for a molecule) to PQR format.
 *   Written by Nathan Baker.
 *   <li>apbs/tools/conversion/amber2charmm.sh <br> 
 *   A script which converts a PDB file with AMBER atom names to a PDB file
 *   with CHARMm atom names.  Useful for preprocessing files before converting
 *   with pdb2pqr.  Written by Nathan Baker.
 *   <li>apbs/tools/conversion/WHATIF2AMBER.sed <br> 
 *   A sed script for converting a PDB file with WHATIF atom names to a PDB
 *   file with CHARMm atom names.  Useful for preprocessing files before
 *   converting with pdb2pqr.  Contributed by Chiansan Ma.
 *   </ul>
 * <li> Eigenvalue solver
 *   <ul>
 *   <li>apbs/tools/arpack/driver  <br>
 *   If APBS is linked with ARPACK, this routine will perform eigenvalue
 *   analyses of matrices produced by APBS.  Written by Nathan Baker.
 *   </ul>
 * <li> Analytical electrostatic- and solvation-related properties
 *   <ul>
 *   <li> apbs/tools/manip/acc <br> 
 *   A program for calculating molecular volumes, surface areas, etc. from
 *   molecules in PQR format.  Written by Nathan Baker.
 *   <li> apbs/tools/manip/born <br> 
 *   A crude program for calculating Generalized Born energies.  Written by
 *   Nathan Baker (and not really debugged).
 *   <li>apbs/tools/manip/coulomb <br> 
 *   A simple program for printing out forces and energies as calculated
 *   (analytically) from Coulomb's law.  Written by Nathan Baker.
 *   </ul>
 * <li> Tools for problem setup
 *   <ul>
 *   <li> apbs/tools/manip/asynchronize.sh <br>
 *   Convert a <a href="#mg-para>mg-para</a> calculation into a <a
 *   href="#mg-async">mg-async</a> calculation.
 *   <li> apbs/tools/manip/inputgen.py <br> 
 *   Generate an APBS input file from PQR data using specified parameters.
 *   Contributed by Todd Dolinsky and Nathan Baker.
 *   <li> apbs/tools/manip/psize.py <br> 
 *   Get the dimensions and center of a molecule in PQR format.  Very useful
 *   for setting up input files (i.e., grid dimensions, lengths, spacings,
 *   etc.) for APBS calculations.  Contributed by Todd Dolinsky and
 *   Nathan Baker.  
 *   <li> apbs/tools/manip/psize <br> 
 *   Get the dimensions and center of a molecule in PQR format.  Very useful
 *   for setting up input files (i.e., grid dimensions, lengths, spacings,
 *   etc.) for APBS calculations.  NOTE:  THIS SCRIPT HAS BEEN
 *   SUPERCEDED BY manip/psize.py.  Contributed by Dave Sept; modified by
 *   Nathan Baker and Todd Dolinsky.
 *   <li> apbs/tools/manip/collisions <br> 
 *   Useful for looking for collisions between two molecules when trying to set
 *   up a binding energy calculation.  Contributed by Dave Sept.
 *   <li> apbs/tools/manip/shift <br> 
 *   Move the center of a molecule in PQR format around.  Contributed by Dave
 *   Sept.
 *   </ul>
 * <li> Mesh manipulation and tools
 *   <ul>
 *   <li> apbs/tools/mesh/mgmesh <br> 
 *   List acceptable grid dimensions/multigrid levels combinations for
 *   mg-manual calculations.  Saves considerable headaches with math.
 *   <li> apbs/tools/mesh/dxmath <br> 
 *   Perform arithmetic operations on OpenDX-format grids and scalar
 *   quantities.  Similar to UHBD's <code>gridcalc</code> utility; run code
 *   with no arguments for instructions.
 *   <li> apbs/tools/mesh/norm <br>
 *   Given an OpenDX grid-based dataset, this program produces various norms,
 *   semi-norms, and <a
 *   href="http://s9000.furman.edu/~ejorgens/cheers/archives/normisms.html">Norm-isms</a>
 *   <li> apbs/tools/mesh/value <br>
 *   Given an OpenDX grid-based dataset, this program produces information
 *   about the solution at a given point
 *   <li> apbs/tools/mesh/uhbd_asc2bin <br> 
 *   Converts UHBD-format grid files from ASCII to binary.  Contributed by Dave
 *   Sept.
 *   <li> apbs/tools/opendx/average <br> 
 *   Basically example code for OpenDX manipulation in APBS.  Averages
 *   potential along an axis.  Written by Nathan Baker
 *   <li> apbs/tools/opendx/benchmark <br> 
 *   Calculates time to read/write OpenDX data.  Written by Nathan Baker.
 *   <li> apbs/tools/opendx/read  <br> 
 *   Basic example code for OpenDX manipulation in APBS.  Reads in DX file and
 *   spits out some information.  Written by Nathan Baker.
 *   </ul>
 * <li> Visualization
 *   <ul>
 *   <li> apbs/tools/opendx/potacc.* <br> 
 *   <a href="http://www.opendx.org">OpenDX</a> visual program (*.net) and
 *   accessory files for looking at potentials and molecular surfaces.  Written
 *   by Nathan Baker.
 *   <li> apbs/tools/opendx/pot.* <br> 
 *   <a href="http://www.opendx.org">OpenDX</a> visual program (*.net) and
 *   accessory files for looking at potentials only.  Written by Nathan Baker.
 *   <li> apbs/opendx/multipot.* <br> 
 *   Sample <a href="http://www.opendx.org">OpenDX</a> visual program (*.net)
 *   and accessory files for looking at potentials as output by a parallel
 *   focusing calculation.  Written by Nathan Baker.
 *   <li> apbs/tools/vmd/read_dx 
 *   <br> Tcl commands for visualizing electrostatic potentials in <a
 *   href="http://www.ks.uiuc.edu/Research/vmd/">VMD</a>.  Contributed by Dave
 *   Sept; modified by Nathan Baker.
 *   <li> apbs/tools/vmd/loadstuff.vmd <br> 
 *   Sample command script for visualizing electrostatic potentials in <a
 *   href="http://www.ks.uiuc.edu/Research/vmd/">VMD</a>.  Contributed by Dave
 *   Sept; modified by Nathan Baker
 *   <li> apbs/tools/opendx/dx2mol <br> 
 *   For converting the OpenDX format of the electrostatic potential to the
 *   <a href="http://www.mol.biol.ethz.ch/wuthrich/software/molmol/">
 *   MOLMOL</a> format.  Contributed by Jung-Hsin Lin.
 *   </ul>
 * <li> Python tools and wrappers
 *   <ul>
 *   <li> apbs/tools/python/main.py <br> 
 *   Run APBS in Python using SWIG generated wrappers.  Contains example Python 
 *   driver code for use with the APBS Python library.  Written
 *   by Todd Dolinsky and Nathan Baker with help from Alex Gillet and 
 *   Michel Sanner.
 *   <li> apbs/tools/conversion/pdb2pqr/pdb2pqr.py<br>
 *   A command line Python script to convert a PDB file to PQR format by 
 *   using a supported forcefield - AMBER02, CHARMM23, or PARSE.
 *   Contributed by Todd Dolinsky, Jens Nielsen, and Nathan Baker.
 *   <li> apbs/tools/manip/inputgen.py <br> 
 *   Generate an APBS input file from PQR data using specified parameters.
 *   Contributed by Todd Dolinsky and Nathan Baker.
 *   <li> apbs/tools/manip/psize.py <br> 
 *   Get the dimensions and center of a molecule in PQR format.  Very useful
 *   for setting up input files (i.e., grid dimensions, lengths, spacings,
 *   etc.) for APBS calculations.  Contributed by Todd Dolinsky and
 *   Nathan Baker. 
 *   </ul>
 * </ul>
 * 
 * @subsection examplecode Example code
 * <p>
 * The main driver code <code>bin/main.c</code> and <code>bin/routines.c</code>
 * should provide a starting point for those who wish to integrate APBS into
 * their own applications.  Such users should also become familiar with the
 * APBS @ref programming.
 * 
 * <hr width="100%">
 * @section usage Using the APBS executable
 * 
 * <p> The only executable for APBS is located at
 * <code>${TOP}/dist/bin/${triplet}/apbs</code>, where <code>${TOP}</code> is
 * the top-level install directory (see <a href="#installation">Installation
 * section</a>) and <code>${triplet}</code> is a machine-specific directory
 * that allows the installation of multiple architechtures in the same
 * directory.  The executable is invoked as
 * <pre>
 *   apbs input-path
 * </pre>
 * where <code>input-path</code> is the path to a specially formatted input
 * file.  The syntax of this input file closely resembles UHBD input with a few
 * significant changes and additions.  Input is divided into sections of the
 * form
 * <pre>
 *        READ
 *          ....
 *        END
 *        ELEC
 *          ....
 *        END
 *        PRINT
 *          ....
 *        END
 *        QUIT
 * </pre>
 * where <code>READ</code>, <code>ELEC</code>, and <code>PRINT</code> designate
 * the start of specific sections.  Each section is ended by the
 * <code>END</code> keyword and the entire input file is terminated by the
 * <code>QUIT</code> keyword.  The sections/commands currently available are:
 * <ul>
 * <li> <a href="#read"><code>READ</code></a>:  Read in molecules
 * <li> <a href="#elec"><code>ELEC</code></a>:  Perform electrostatics
 * calculations (solve the PBE, calculate energies and forces, etc.)
 * <li> <a href="#print"><code>PRINT</code></a>:  Do some simple arithmetic on
 * some of the properties calculated in other sections.
 * </ul>
 * These sections can occur in any order, however, they are clearly
 * interdependent.  For example, <code>PRINT</code> requires <code>ELEC</code>
 * and <code>ELEC</code> requires one or more <code>READ</code> sections.
 * Sections
 * can also be repeated; several <code>READ</code> statements may be used to
 * load molecules and multiple <code>ELEC</code> sections would specify various
 * electrostatics calculations on one or more molecules.
 * 
 * @subsection read READ statements
 * One of these sections must be present for every molecule involved in the
 * APBS calculation.   Molecule and "map" IDs are assigned implicitly assigned
 * for each molecule/map read, based on order and starting at 1.  The sections
 * have the following keywords:
 * <ul>
 * <li> <code>mol</code> <i>format</i> <i>path</i> <br>
 * Read in molecular data from the file <i>path</i>.  The acceptable
 * <i>format</i> flags are:
 *  <ul>
 *  <li><code>pqr</code>.  The molecule file is in PQR format (attributed to 
 *  Don Bashford's MEAD package), which has the form
 *       <pre>
 *          ATOM anum aname resname resnum x y z q r
 *       </pre>
 *       where the fields can be delimited by spaces, tabs or newlines and
 *       denote:
 *       <ol>
 *       <li> ATOM <br>
 *            The "ATOM" or "HETATM" string
 *       <li> anum <br>
 *            The integer atom number; ignored
 *       <li> aname <br>
 *            The atom name string; ignored
 *       <li> rname <br>
 *            The residue name string; ignored
 *       <li> rnum <br>
 *            The residue number string; iggored
 *       <li> x <br>
 *            A floating-point number denoting the x-coordinate (in &Aring;)
 *       <li> y <br>
 *            A floating-point number denoting the y-coordinate (in &Aring;)
 *       <li> z <br>
 *            A floating-point number denoting the z-coordinate (in &Aring;)
 *       <li> q <br>
 *            A floating-point number denoting the charge (in e)
 *       <li> r <br>
 *            A floating-point number denoting the radius (in &Aring;)
 *       </ol>
 *       See the <a href="http://nbcr.sdsc.edu/pdb2pqr/index.html">PDB2PQR</a>
 *       web service, the <code>apbs/tools/conversion</code> directory, and the
 *       @ref tools section above for scripts to convert PDB files into PQR
 *       format.
 *  <li><code>pdb</code>.  The molecule file is in PDB format as described at
 *  <a href="http://www.rcsb.org/pdb/info.html#File_Formats_and_Standards">http://www.rcsb.org/pdb/info.html#File_Formats_and_Standards</a>.  
 *  <b>NOTE:
 *  <ol>
 *  <li>PDB input files must be accompanied by a <a href="#read-parm">"READ 
 *  PARM"</a> statement to obtain charge and radius parameters.
 *  <li>We make one significant exception to the PDB format; we require
 *  whitespace-, tab-, or newline-delimited fields.  This exception enables the
 *  study of molecules with coordinates substantially outside the 
 *  \f$\pm 999.0\f$ range. 
 *  </ol>
 *  </b>
 *  </ul>
 * <li> <a name="read-parm"><code>parm</code></a> <i>format</i> <i>path</i><br>
 *  Read in a database from <i>path</i> with charges and radii for use with
 * PDB-format molecule files.  The <i>format</i> can be one of the following:
 *   <ul>
 *   <li> <code>flat</code> <br>
 *        A flat-file database with "#" and "%" comment characters (i.e., text
 *        between these characters and the end of a line is ignored) and
 *        ASCII-based data in the following form:
 *        <pre>
 *           rname  aname  q  r  eps
 *        </pre>
 *        where <code>rname</code> is a string denoting the residue name, 
 *        <code>aname</code> is a string denoting the atom name, <code>q</code>
 *        is the atomic charge (in e), <code>r</code> is the atomic radius (in
 *        &Aring;), and <code>eps</code> is the van der Waals well-depth in
 *        <i>kcal/mol</i> (NOTE:  this a different set of energy units than
 *        used in the rest of APBS but agrees with the format of CHARMM and
 *        AMBER parameter files).  Sample flat-file databases are provided in
 *        <code>apbs/tools/conversion/param/vparam/</code>.
 *   </ul>
 * <li> <a name="read-diel"><code>diel</code></a> <i>format</i> <i>path-x
 * path-y path-z</i>
 * <br> Read in the dielectric function \f$\epsilon(x)\f$ mapped to a
 * Cartesian mesh.  The result is a map of values between the solvent and
 * biomolecular dielectric constants.  The values in this file have no units.
 * Acceptable <i>format</i> keywords include:
 * <ul>
 * <li> <code>dx</code> for OpenDX format
 * </ul>
 * The x-shifted dielectric map is read from <i>path-x</i>, the y-shifted
 * map is read from <i>path-y</i>, and the z-shifted map is read from
 * <i>path-z</i>.  <b>Note:  if you choose this option and a non-zero ionic
 * strength (see <a href="#ion"><code>ion</code></a> statement), then you
 * <i>must</i> also include a <a href="#read-kappa"><code>kappa</code></a>
 * READ statement.</b>
 * <li> <a name="read-kappa"><code>kappa</code></a> <i>format</i> <i>path</i>
 * <br> Read in the \f$\overline{\kappa}^2(x)\f$ map from the file <i>path</i>.
 * The values in this file have units of \f$\AA^{-2}\f$.  Acceptable
 * <i>format</i> keywords include:
 * <ul>
 * <li> <code>dx</code> for OpenDX format
 * </ul>
 * <b>Note:  if you choose this option, then you <i>must</i> also include a <a
 * href="#read-diel"><code>diel</code></a> READ statement.</b>
 * <li> <code>charge</code> <i>format</i> <i>path</i>
 * <br> Read in the molecular charge distribution from the file <i>path</i>.
 * The values in this file have units of <code>e_c</code>, the electron charge
 * (i.e., they are unitless).  Acceptable <i>format</i> keywords include:
 * <ul>
 * <li> <code>dx</code> for OpenDX format
 * </ul>
 * </ul>
 * 
 * @subsection elec ELEC statements
 * 
 * <p> This section is the main component of all APBS runs.  There may be
 * several <code>ELEC</code> sections, operating on different molecules or
 * using different parameters for multiple runs on the same molecule.  Each of
 * the <code>ELEC</code> sections begins with one of the following keywords:
 * <ul>
 * <li> <a href="#mg-auto"><code>mg-auto</code></a> for automatically
 * configured multigrid focusing calculations.  This automatically sets up and
 * performs a string of single-point PBE calculations to "focus" on a region of
 * interest (binding site, etc.) in a system.  It is basically an automated
 * version of <a href="#mg-manual"><code>mg-manual</code></a> designed for
 * easier use.  <i>Most users should probably use this version of ELEC</i>.
 * 
 * <li> <a href="#mg-para"><code>mg-para</code></a> for automatically
 * configured multigrid parallel focusing calculations.  This calculation
 * closely resembles <a href="#mg-auto"><code>mg-auto</code></a> in syntax.
 * However, it is basically designed to perform single-point calculations on
 * systems in a <a href="http://www.pnas.org/cgi/reprint/181342398v1">parallel
 * focusing fashion</a>.  While this method does provide support for decreasing
 * the domain size from a coarse (large) global grid to a fine (smaller) global
 * grid, <i>it should not be used to look at subsets of
 * biomolecules such as titration sites, etc</i>.  Such subset
 * calculations require more complicated energy evaluation which is not yet
 * supported by <code>mg-para</code>.  However, since parallel focusing was
 * designed to provide detailed evaluation of the electrostatic potential on a
 * large scale, such subset calculations are better left to traditional
 * focusing via the <a href="#mg-auto"><code>mg-auto</code></a> keyword.
 * 
 * <li> <a href="#mg-manual"><code>mg-manual</code></a> for manually configured
 * multigrid calculations.  This is the standard single-point PBE calculation
 * performed by most solvers.  The <code>mg-manual</code> calculation offers
 * the most control of parameters to the user.  Several of these calculations
 * can be strung together to perform focusing calculations by judicious choice
 * of the <a href="#bcfl"><code>bcfl</code></a> flag, however, the setup of the
 * focusing is not automated as it is in <a
 * href="#mg-auto"><code>mg-auto</code></a> calculations and parallel focusing
 * (i.e., <a href="#mg-para"><code>mg-para</code></a>) is very difficult with
 * this keyword.  <i><b>This is intended for more experienced
 * users.</b></i>
 * 
 * <li> <a href="#mg-manual"><code>mg-dummy</code></a> has <i>exactly</i> the
 * same syntax as <a href="#mg-manual"><code>mg-manual</code></a>, but simply
 * sets up the problem and skips the solver step.  This is useful for setting
 * up charge, dielectric, etc. grids for use in other runs.
 * 
 * <li> <a href="#fe-manual"><code>fe-manual</code></a> for adaptive finite
 * element calculations.  This function will not be (publicly) available until
 * the release of the Holst group's <a href="htp://www.fetk.org">FEtk</a>
 * software package.
 * </ul>
 * 
 * <br><br><a name="mg-manual"><b>Manual multigrid calculation syntax
 * (mg-manual)</b></a>
 * <br>
 * This section always has the form
 * <pre>
 * elec
 *   mg-manual
 *   ...
 * end
 * </pre>
 * where the <code>...</code> denotes the various parameter keywords listed
 * below.  To avoid confusion during run-time, <i>there are no default
 * parameter values</i>.  Therefore, unless otherwise indicated, all of the
 * following keywords should be specified:
 * <ul> 
 * <li> <a href="#dime">dime</a>
 * <li> <a href="#nlev">nlev</a>
 * <li> <a href="#grid">grid</a> or <a href="#glen">glen</a>
 * <li> <a href="#gcent">gcent</a>
 * <li> <a href="#mol">mol</a>
 * <li> <a href="#lpbe">lpbe</a> or <a href="#npbe">npbe</a>
 * <li> <a href="#bcfl">bcfl</a>
 * <li> <a href="#ion">ion</a> (optional)
 * <li> <a href="#pdie">pdie</a>
 * <li> <a href="#sdie">sdie</a>
 * <li> <a href="#srfm">srfm</a>
 * <li> <a href="#chgm">chgm</a>
 * <li> <a href="#usemap">usemap</a> (optional)
 * <li> <a href="#srad">srad</a> 
 * <li> <a href="#swin">swin</a> 
 * <li> <a href="#temp">temp</a> 
 * <li> <a href="#gamma">gamma</a> 
 * <li> <a href="#calcenergy">calcenergy</a> 
 * <li> <a href="#calcforce">calcforce</a> 
 * <li> <a href="#write">write</a> (optional)
 * <li> <a href="#writemat">writemat</a> (optional)
 * </ul>
 * 
 * <br><br><a name="mg-auto"><b>Automatic multigrid focusing calculation
 * syntax (mg-auto)</b></a> <br>
 * This section always has the form
 * <pre>
 * elec
 *   mg-auto
 *   ...
 * end
 * </pre>
 * where the <code>...</code> denotes the various parameter keywords listed
 * below.  This form of multigrid calculations is most useful for focusing; the
 * user simply provides information about the coarsest and finest meshes
 * desired and the code sets up the rest, including number of focusing levels,
 * centers, dimensions, etc.<br> As before, <i>there are no default parameter
 * values</i>.  Therefore, unless otherwise indicated, all of the following
 * keywords should be specified:
 * <ul>
 * <li> <a href="#dime">dime</a>
 * <li> <a href="#cglen">cglen</a>
 * <li> <a href="#fglen">fglen</a>
 * <li> <a href="#cgcent">cgcent</a>
 * <li> <a href="#fgcent">fgcent</a>
 * <li> <a href="#mol">mol</a>
 * <li> <a href="#lpbe">lpbe</a> or <a href="#npbe">npbe</a>
 * <li> <a href="#bcfl">bcfl</a>
 * <li> <a href="#ion">ion</a> (optional)
 * <li> <a href="#pdie">pdie</a>
 * <li> <a href="#sdie">sdie</a>
 * <li> <a href="#srfm">srfm</a>
 * <li> <a href="#chgm">chgm</a>
 * <li> <a href="#usemap">usemap</a> (optional)
 * <li> <a href="#srad">srad</a>
 * <li> <a href="#swin">swin</a>
 * <li> <a href="#temp">temp</a>
 * <li> <a href="#gamma">gamma</a>
 * <li> <a href="#calcenergy">calcenergy</a>
 * <li> <a href="#calcforce">calcforce</a>
 * <li> <a href="#write">write</a> (optional)
 * <li> <a href="#writemat">writemat</a> (optional)
 * </ul>
 * 
 * <br><br><a name="mg-para"><b>Automatic multigrid parallel focusing
 * calculation syntax (mg-para)</b></a>
 * <br><br>
 * <i>PLEASE NOTE:  In versions 0.2.1 and earlier,
 * parallel focusing should not be used for energy calculations if the fine
 * grid does not completely contain all atoms of interest!</i>
 * <br><br>
 * This section always has the form
 * <pre>
 * elec
 *   mg-para
 *   ...
 * end
 * </pre>
 * where the <code>...</code> denotes the various parameter keywords listed
 * below.  This form of multigrid calculations is most useful for focusing; the
 * user simply provides information about the coarsest and finest meshes
 * desired and the code sets up the rest, including number of focusing levels,
 * centers, dimensions, etc.<br> As before, <i>there are no default parameter
 * values</i>.  Therefore, unless otherwise indicated, all of the following
 * keywords should be specified:
 * <ul>
 * <li> <a href="#pdime">pdime</a>
 * <li> <a href="#ofrac">ofrac</a>
 * <li> <a href="#async">async</a>
 * <li> <a href="#dime">dime</a>
 * <li> <a href="#cglen">cglen</a>
 * <li> <a href="#fglen">fglen</a>
 * <li> <a href="#cgcent">cgcent</a>
 * <li> <a href="#fgcent">fgcent</a>
 * <li> <a href="#mol">mol</a>
 * <li> <a href="#lpbe">lpbe</a> or <a href="#npbe">npbe</a>
 * <li> <a href="#bcfl">bcfl</a>
 * <li> <a href="#ion">ion</a> (optional)
 * <li> <a href="#pdie">pdie</a>
 * <li> <a href="#sdie">sdie</a>
 * <li> <a href="#srfm">srfm</a>
 * <li> <a href="#chgm">chgm</a>
 * <li> <a href="#usemap">usemap</a> (optional)
 * <li> <a href="#srad">srad</a>
 * <li> <a href="#swin">swin</a>
 * <li> <a href="#temp">temp</a>
 * <li> <a href="#gamma">gamma</a>
 * <li> <a href="#calcenergy">calcenergy</a>
 * <li> <a href="#calcforce">calcforce</a>
 * <li> <a href="#write">write</a> (optional)
 * <li> <a href="#writemat">writemat</a> (optional)
 * </ul>
 * 
 * <br><br><a name="fe-manual"><b>Manual finite element calculation syntax
 * (fe-manual)</b></a>
 * <br><br>
 * <i>PLEASE NOTE:  This mode of execution is experimental and does not
 * run very quickly yet.  For performance-sensitive applications, please use
 * the multigrid modes above.</i>
 * <br><br>
 * This section always has the form
 * <pre>
 * elec
 *   fe-manual
 *   ...
 * end
 * </pre>
 * where the <code>...</code> denotes the various parameter keywords listed
 * below.  This form of multigrid calculations is most useful for focusing; the
 * user simply provides information about the coarsest and finest meshes
 * desired and the code sets up the rest, including number of focusing levels,
 * centers, dimensions, etc.<br> As before, <i>there are no default parameter
 * values</i>.  Therefore, unless otherwise indicated, all of the following
 * keywords should be specified:
 * <ul>
 * <li> <a href="#domainLength">domainLength</a>
 * <li> <a href="#etol">etol</a>
 * <li> <a href="#ekey">ekey</a>
 * <li> <a href="#akeyPRE">akeyPRE</a>
 * <li> <a href="#akeySOLVE">akeySOLVE</a>
 * <li> <a href="#targetNum">targetNum</a>
 * <li> <a href="#targetRes">targetRes</a>
 * <li> <a href="#maxsolve">maxsolve</a>
 * <li> <a href="#maxvert">maxvert</a>
 * <li> <a href="#mol">mol</a>
 * <li> <a href="#lpbe">lpbe</a>, <a href="#npbe">npbe</a>, 
 *      <a href="#lrpbe">lrpbe</a>, or <a href="#nrpbe">nrpbe</a>
 * <li> <a href="#bcfl">bcfl</a>
 * <li> <a href="#ion">ion</a> (optional)
 * <li> <a href="#pdie">pdie</a>
 * <li> <a href="#sdie">sdie</a>
 * <li> <a href="#srfm">srfm</a>
 * <li> <a href="#chgm">chgm</a>
 * <li> <a href="#usemap">usemap</a> (optional)
 * <li> <a href="#srad">srad</a>
 * <li> <a href="#swin">swin</a>
 * <li> <a href="#temp">temp</a>
 * <li> <a href="#gamma">gamma</a>
 * <li> <a href="#calcenergy">calcenergy</a>
 * <li> <a href="#calcforce">calcforce</a>
 * <li> <a href="#write">write</a> (optional)
 * <li> <a href="#writemat">writemat</a> (optional)
 * </ul>
 *
 * <br><br><a name="keywords"><b>Keyword definitions</b></a>
 * <br><br>
 * <ul>
 * <li> <a name="dime">dime <i>nx</i> <i>ny</i> <i>nz</i></a> 
 * <br> Number of grid points in the x, y, and z directions.  The <i>nx</i>,
 * <i>ny</i>, and <i>nz</i> are related to the value <i>l</i> specified in the
 * <a href="#nlev"><code>nlev</code></a> keyword by the formula 
 * <pre>
 *   nx = c 2^(l+1) + 1
 * </pre>, where c is an integer.  Use the program
 * <code>apbs/tools/mesh/mgmesh</code> to find the correct values of <i>nx</i>,
 * <i>ny</i>, and <i>nz</i>.  The most common values are 65, 97, and 161 (can
 * be different in each direction); these are all compatible with <code>nlev
 * 4</code>.  If you happen to pick an "bad" value for the dimensions
 * (<i>i.e.</i>, mismatch with <code>nlev</code>), the code will adjust the
 * specified dime <i>downwards</i> to more appropriate values.  
 * <i>This means that "bad" values will typically result in
 * lower resolution/accuracy calculations!</i>
 *  
 * <li> <a name="nlev">nlev <i>l</i></a>
 * <br> The number of levels in the multilevel hierarchy.  Dependent on the
 * values set by the <a href="#dime"><code>dime</code></a> keyword; see
 * discussion.
 * 
 * <li> <a name="grid">grid <i>hx hy hz</i></a>
 * <br> The mesh grid spacing (in &Aring;); may be different in each direction.
 * Either this keyword or <href="#name">glen</a> must be specified.
 *
 * <li> <a name="glen">glen <i>xlen ylen zlen</i></a>
 * <br> The mesh lengths (in &Aring;); may be different in each direction.
 * Either this keyword or <a href="#grid">grid</a> must be specified.
 * 
 * <li> <a name="gcent">gcent</a> {<code>mol</code> <i>id</i> | <i> xcent ycent
 * zcent</i>}
 * <br> The grid center.  If the <code>grid mol</code> is used, * <i>id</i>
 * must be the ID of a molecule read in a previous <a href="#read">READ</a>
 * section.  Molecule IDs are assigned in the order they're read, starting at
 * 1.  If just <code>grid</code> is used, the next three numbers should be the
 * x, y, and z coordinates for the center of the grid.  
 * 
 * <li> <a name="mol">mol</a> <i>id</i>
 * <br> The ID of a molecule read in a previous <a herf="#read">READ</a>
 * section; this is the molecule for which the PBE is solved.
 *
 * <li> <a name="lpbe">lpbe</a> 
 * <br> Specifies that the linearized PBE should be solved.  
 * Either this keyword or one of <a href="#npbe">npbe</a>, <a
 * href="#lrpbe">lrpbe</a>, or <a href="#nrpbe">nrpbe</a> must be present.
 * 
 * <li> <a name="npbe">npbe</a>
 * <br> Specifies that the nonlinear (full) PBE should be solved. 
 * Either this keyword or one of <a href="#npbe">npbe</a>, <a
 * href="#lrpbe">lrpbe</a>, or <a href="#nrpbe">nrpbe</a> must be present.
 *
 * <li> <a name="bcfl">bcfl</a> <i>flag</i>
 * <br> Boundary condition flag; where <i>flag</i> is one of the following:
 *    <ul>
 *    <li> <code>zero</code> or <code>0</code>
 *    <br> Zero boundary conditions.
 *    <li> <code>sdh</code> or <code>1</code>
 *    <br> Boundary conditions assigned using the analytical
 *    (Debye-H&uuml;ckel) expression for a single spherical ion with the
 *    molecule's radius and net charge.
 *    <li> <code>mdh</code> or <code>2</code>
 *    <br> The analytical (Debye-H&uuml;ckel) expression for a single
 *     spherical ion is used for each ion (i.e., superposition) to assign
 *     boundary conditions.  Tends to capture more moments of the molecular
 *     multipole, but is (much) slower to evaluate.
 *    <li> <code>focus</code> or <code>4</code>
 *     <br> The solution from the previous calculation is used to assign
 *     boundary conditions for the current calculation.  Clearly, the domain
 *     for the current calculation must be a subset of the previous domain.
 *     </ul>
 * 
 * <li> <a name="ion">ion</a> <i>charge conc radius</i>
 * <br> These specify the different counterion species present in solution with
 * the given charge (in e), concentration (in M), and radius (in \f$\AA\f$).
 * Several of these keywords can be present to describe a variety of ionic
 * species in solution.  Varying ion valencies and concetrations are taken into
 * account in the mobile ion PBE term, however, only the largest ionic radius
 * is used to determine the ion accessibility function.
 * 
 * <li> <a name="pdie">pdie</a> <i>dielectric</i>
 * <br> Solute dielectric constant (unitless).  Typically 2 to 20.
 * 
 * <li> <a name="sdie">sdie</a> <i>dielectric</i>
 * <br> Solvent dielectric constant (unitless).  Typically 78.54 (water).
 * 
 * <li> <a name="chgm">chgm</a> <i>flag</i>
 * <br> Method used to define the various charge discretization methods:
 * <i>flag</i> is one of the following:
 *     <ul>
 *     <li> <code>spl0</code> or <code>0</code>
 *     <br> Traditional trilinear hat-function discretization (linear splines);
 *          charge is mapped onto nearest-neighbor grid points
 *     <li> <code>spl2</code> or <code>1</code>
 *     <br> Cubic B-spline discretization; charge is mapped onto nearest- and
 *     next-nearest-neighbor grid points
 *     </ul>
 * <li> <a name="srfm">srfm</a> <i>flag</i>
 * <br> Method used to define the various surface-based coefficients;
 * <i>flag</i> is one of the following:
 *     <ul>
 *     <li> <code>mol</code> or <code>0</code>
 *     <br> Ion accessibility (\f$\overline{\kappa}^2(x)\f$) is defined using
 *     inflated van der Waals radii, the dielectric coefficient
 *     (\f$\epsilon(x)\f$) is defined using the molecular (Conolly) surface
 *     definition without smoothing.
 *     <li> <code>smol</code> or <code>1</code>
 *     <br> Ion accessibility (\f$\overline{\kappa}^2(x)\f$) is defined using
 *     inflated van der Waals radii, the dielectric coefficient
 *     (\f$\epsilon(x)\f$) is defined using the molecular (Conolly) surface
 *     definition with a simple harmonic average smoothing.
 *     <li> <code>spl2</code> or <code>2</code>
 *     <br> Spline-based surface definitions.  This is primarily for use with
 *     force calculations, since it requires substantial reparameterization of
 *     radii.  This is based on the work of Im et al, <i>Comp. Phys. Comm.</i>
 *     <b>111</b>, (1998) and uses a cubic spline to define a smoothly varying
 *     characteristic function for the surface-based parameters.  Ion
 *     accessibility (\f$\overline{\kappa}^2(x)\f$) is defined using inflated
 *     van der Waals radii with the spline function and the dielectric
 *     coefficient (\f$\epsilon(x)\f$) is defined using the standard van der
 *     Waals radii with the spline function.
 *     </ul>
 * 
 * <li> <a name="usemap">usemap</a> <i>type ID</i>
 * <br> Use a pre-calculated map(s) (as provided by a <a
 * href="#write">write</a> statement in an earlier calculation and read in with
 * a <a href="#read">READ</a> statement) to set up a calculation.  The
 * <i>type</i> flag refers to the coefficient to be assigned from the map: <ul>
 *  <li> <code>diel</code>
 *  <br> Dielectric function (\f$\epsilon(x)\f$) -- this causes the
 *  <code>srad</code> parameter and the radii/location of atoms in the PQR file
 *  to be ignored
 *  <li> <code>kappa</code>
 *  <br> Ion accessibility  (\f$\overline{\kappa}^2(x)\f$) -- this causes the
 *  <code>ion</code> radius parameter to be ignored
 *  <li> <code>charge</code>
 *  <br> Biomolecule charge distribution -- this causes the charges/locations in
 *       the PQR file to be ignored
 *  </ul>
 *
 * <li> <a name="srad">srad</a> <i>radius</i>
 * <br> Solvent molecular radius (in \f$\AA\f$) used to define molecular
 * surfaces.  Typically 1.4 \f$\AA\f$ (water).
 * 
 * <li> <a name="swin">swin</a> <i>window</i>
 * <br> Spline window (in \f$\AA\f$) used to define surface-based properties.
 * Typically 0.3 \f$\AA\f$.
 * 
 * <li> <a name="temp">temp</a> <i>temperature</i>
 * <br> System tempertature (in K).
 * 
 * <li> <a name="gamma">gamma</a> <i>parameter</i>
 * <br> Surface tension parameter for apolar forces (in kJ/mol/&Aring;).  Often
 * 0.105 kJ/mol/\f$\AA\f$. <i>This parameter is only used if forces are
 * calculated but still must be present for other calculations.</i>
 * 
 * <li> <a name="calcenergy">calcenergy</a> <i>flag</i>
 * <br> OPTIONAL KEYWORD.  Controls electrostatic energy output.  Values for
 *      <i>flag</i> are:
 *      <ul>
 *      <li> <code>no</code> or <code>0</code>
 *      <br> No energies are written.
 *      <li> <code>total</code> or <code>1</code>
 *      <br> Total electrostatic energies are written to stdout.
 *      <li> <code>comps</code> or <code>2</code>
 *      <br> Total electrostatic energies and individual per-atom components
 *      are written to stdout.
 *     </ul>
 *      Note that this option must be used consistently for all calculations
 *      that will appear in subsequent <a href="#print">PRINT</a> statements.
 *      For example, if the statement <code>print energy 1 - 2 end</code>
 *      appears in the input file, then both calculations 1 and 2 must have
 *      <code>calcenergy</code> keywords present with the same values for
 *      <i>flag</i>.
 *
 * <li> <a name="calcforce">calcforce</a> <i>flag</i>
 * <br> OPTIONAL KEYWORD.  Controls electrostatic force output.  Values for
 *      <i>flag</i> are:
 *      <ul>
 *      <li> <code>no</code> or <code>0</code>
 *      <br> No forces are written.
 *      <li> <code>total</code> or <code>1</code>
 *      <br> Net forces on molecule are written to stdout.
 *      <li> <code>comps</code> or <code>2</code>
 *      <br> Forces on each atom are written to stdout.
 *      </ul>
 *      Note that this option must be used consistently for all calculations
 *      that will appear in subsequent <a href="#print">PRINT</a> statements.
 *      For example, if the statement <code>print force 1 - 2 end</code>
 *      appears in the input file, then both calculations 1 and 2 must have
 *      <code>calcforce</code> keywords present with the same values for
 *      <i>flag</i>.

 * <li> <a name="write">write</a> <i>type format stem</i>
 * <br> Controls output of data; all arguments must be present.
 * This keyword can be repeated several times to provide various types of
 * output.
 *      <ul>
 *      <li> <i>type</i>
 *      <br> <ul>
 *           <li> <code>charge</code>  Write out the biomolecular charge
 *           distribution in units of e 
 *           <i>MG only</i>
 *           <li> <code>pot</code>  Write out potential in units of kT/e 
 *           <i>MG and FEM</i>
 *           <li> <code>smol</code> Write out solvent accessibility defined by
 *           molecular/Connolly surface definition (1 = accessible, 0 =
 *           inaccessible) 
 *           <i>MG and FEM</i>
 *           <li> <code>sspl</code> Write out spline-based solvent
 *           accessibility (1 = accessible, 0 = inaccessible) 
 *           <i>MG and FEM</i>
 *           <li> <code>vdw</code> Write out van der Waals-based accessibility
 *           (1 = accessible, 0 = inaccessible) 
 *           <i>MG and FEM</i>
 *           <li> <code>ivdw</code> Write out ion accessibility/inflated van
 *           der Waals (1 = accessible, 0 = inaccessible) 
 *           <i>MG and FEM</i>
 *           <li> <code>lap</code> Write out Laplacian of potential
 *           (kT/e/\f$\AA^2\f$) 
 *           <i>MG only</i>
 *           <li> <code>edens</code> Write out energy density 
 *           \f$\epsilon (\nabla u)^2\f$, where \f$u\f$ is potential
 *           \f$(kT/e/A)^2\f$ 
 *           <i>MG only</i>
 *           <li> <code>ndens</code> Write out ion number density \f$\sum c_i
 *           \exp (-q_i u)^2\f$, where \f$u\f$ is potential (output in M)
 *           <i>MG and FEM</i>
 *           <li> <code>qdens</code> Write out ion charge density \f$\sum q_i
 *           c_i \exp (-q_i u)^2\f$, where \f$u\f$ is potential (output in e_c
 *           M) 
 *           <i>MG and FEM</i>
 *           <li> <code>dielx</code> Write out the x-shifted dielectric map of
 *           the dielectric function \f$\epsilon(x)\f$ for use in subsequent
 *           calculations (see <a href="#read-diel"><code>read diel</code></a>
 *           (unitless)
 *           <i>MG only</i>
 *           <li> <code>diely</code> Write out the y-shifted dielectric map of
 *           the dielectric function \f$\epsilon(x)\f$ for use in subsequent
 *           calculations (see <a href="#read-diel"><code>read diel</code></a>
 *           (unitless)
 *           <i>MG only</i>
 *           <li> <code>dielz</code> Write out the z-shifted dielectric map of
 *           the dielectric function \f$\epsilon(x)\f$ for use in subsequent
 *           calculations (see <a href="#read-diel"><code>read diel</code></a>
 *           (unitless)
 *           <i>MG only</i>
 *           <li> <code>kappa</code> Write out the map of the function
 *           \f$\overline{\kappa}^2(x)\f$ for use in subsequent calculations
 *           (see <a href="#read-kappa"><code>read kappa</code></a> (units of
 *           \f$\AA^{-2}\f$)
 *           <i>MG only</i>
 *           </ul>
 *      <li> <i>format</i>
 *           <ul>
 *           <li><code>dx</code> <a href="http://www.opendx.org">OpenDX</a> 
 *               format
 *               <i>MG and FEM</i>
 *           <li><code>avs</code> <a href="http://www.avs.com">AVS</a> UCD
 *               format
 *               <i>FEM only</i>
 *           <li><code>uhbd</code> <a
 *               href="http://mccammon.ucsd.edu/uhbd.html">UHBD</a> format
 *               <i>MG only</i>
 *           </ul>
 *      <li> <i>stem</i>
 *      <br> The filename will be <i>stem</i>.XXX, where XXX is determined from
 *      the file format.
 *      </ul>
 * 
 * <li> <a name="writemat">writemat</a> <i>type stem</i>
 * <br> Controls output of operator matrix in Harwell-Boeing column-compressed
 *      format.  This keyword is optional.
 *      <ul>
 *      <li> <i>type</i>
 *      <br> <ul>
 *           <li> <code>poisson</code> Write out the operator 
 *             \f[A v = -\nabla \cdot \epsilon v \nabla\f]
 *           corresponding to Poisson's equation.
 *           <li> <code>full</code>  Write out the linearization (functional
 *           derivative) of the full non-linear Poisson-Boltzmann operator
 *            \f[ A v = -\nabla \cdot \epsilon \nabla v + \overline{\kappa}^2
 *            \sum_i c_i q_i^2 e^{-q_i u^*} v \f]
 *           around the current solution \f$u^*\f$.
 *           </ul>
 *      <li> <i>stem</i>
 *      <br> The filename will be <i>stem</i>.mat.
 *      </ul>
 * 
 * <li> <a name="cglen">cglen</a> <i>xlen ylen zlen</i>
 * <br> The coarsest mesh lengths (in \f$\AA\f$); may be different in each
 * direction.  
 * 
 * <li> <a name="fglen">fglen</a> <i>xlen ylen zlen</i>
 * <br> The finest mesh lengths (in \f$\AA\f$); may be different in each
 * direction.  
 * 
 * <li> <a name="cgcent">cgcent</a> {<code>mol</code> <i>id</i> | <i> xcent
 * ycent zcent</i>}
 * <br> The center of the coarsest mesh.  If the <code>grid mol</code> is used,
 * <i>id</i> must be the ID of a molecule read in a previous <code>READ</code>
 * section.  Molecule IDs are assigned in the order they're read, starting at
 * 1.  If just <code>grid</code> is used, the next three numbers should be the
 * x, y, and z coordinates for the center of the grid.
 * 
 * <li> <a name="fgcent">fgcent</a> {<code>mol</code> <i>id</i> | <i> xcent
 * ycent zcent</i>} 
 * <br> The center of the finest mesh.  If the <code>grid mol</code> is used,
 * <i>id</i> must be the ID of a molecule read in a previous <code>READ</code>
 * section.  Molecule IDs are assigned in the order they're read, starting at
 * 1.  If just <code>grid</code> is used, the next three numbers should be the
 * x, y, and z coordinates for the center of the grid.
 *
 * <li> <a name="pdime"><code>pdime</code></a> <i>npx</i> <i>npy</i> <i>npz</i>
 * <br> Array of processors for the calculation; processors are laid out on
 * Cartesian grid over the actual mesh -- this specifies the number of
 * processors in each direction.
 * 
 * <li> <a name="ofrac"><code>ofrac</code></a> <i>fraction</i>
 * <br> The amount of overlap to include between processors' meshes.  This
 * should be between 0 and 1; empirical evidence suggests that 0.1 is a good
 * choice.
 *
 * <li> <a name="async"><code>async</code></a> <i>rank</i>
 * <br> This <b>optional</b> keyword allows users to perform the different
 * tasks in a parallel run asynchronously.  Specifically, a processor
 * masquerades as process <i>rank</i> in a parallel focusing run and provides
 * output (data files and energies/forces) appropriate to that processor's
 * local partition.  The user must then assemble the results after all
 * processes complete.  This option is good for two things:
 *   <ul>
 *   <li>Scheduling on-demand resources:  this makes it easy for users to
 *   backfill into the available processes in a queue
 *   <li>Running on limited resources:  this enables users without access to
 *   large parallel machines to still perform the same calculations.
 *   </ul>
 * 
 * <li> <a name="domainLength"><code>domainLength</code></a> 
 * <i>xlen</i> <i>ylen</i> <i>zlen</i>
 * <br> The domain length in each direction (in &Aring;)
 * 
 * <li> <a name="etol"><code>etol</code></a> <i>etol</i>
 * <br> Error tolerance for adaptive refinement (see <a href="#ekey">ekey</a>)
 * 
 * <li> <a name="ekey"><code>ekey</code></a> <i>key</i>
 * <br> Error tolerance key:
 *   <ul>
 *   <li> <code>simp</code> -- <a href="#etol">etol</a> is interpreted as
 *        per-simplex error tolerance
 *   <li> <code>glob</code> -- <a href="#etol">etol</a> is interpreted as
 *        global error tolerance
 *   <li> <code>frac</code> -- <a href="#etol">etol</a> is interpreted as
 *        fraction of simplices you want refined
 *   </ul>
 * 
 * <li> <a name="akeyPRE"><code>akeyPRE</code></a> <i>key</i>
 * <br> Key for adpative pre-solve refinement:
 *   <ul>
 *   <li> <code>unif</code> -- uniform refinement
 *   <li> <code>geom</code> -- geometry-based refinement
 *   <li> <code>resi</code> -- residual-based refinement
 *   <li> <code>dual</code> -- dual-based refinement
 *   <li> <code>loca</code> -- local-based refinement
 *   </ul>
 *
 * <li> <a name="akeySOLVE"><code>akeySOLVE</code></a> <i>key</i>
 * <br> Key for adpative pre-solve refinement:
 *   <ul>
 *   <li> <code>unif</code> -- uniform refinement
 *   <li> <code>geom</code> -- geometry-based refinement
 *   <li> <code>resi</code> -- residual-based refinement
 *   <li> <code>dual</code> -- dual-based refinement
 *   <li> <code>loca</code> -- local-based refinement
 *   </ul>
 *
 * <li> <a name="targetNum"><code>targetNum</code></a> <i>number</i>
 * <br> Target number of vertices in mesh before starting solver (used for <i>a
 * priori</i> refinement); the mesh is refined with the <a
 * href="#akeyPRE">akeyPRE</a> method until this number of vertices is reached
 * or <a href="#targetRes">targetRes</a> resolution.
 *
 * <li> <a name="targetRes"><code>targetRes</code></a> <i>res</i>
 * <br> Target resolution (in &Aring;) of simplices in mesh; refinment will
 * continue until the longest edge of every candidate simplex is below this
 * value.
 *
 * <li> <a name="maxsolve"><code>maxsolve</code></a> <i>number</i>
 * <br> Number of times to perform the solve-estimate-refine cycle; i.e., the
 * number of times to 
 *   <ol>
 *   <li> solve the problem, 
 *   <li> estimate the error,
 *   <li> and refine the mesh.
 *   </ol>
 * The solve-estimate-refine cycle continues this many times or until <a
 * href="#targetRes">targetRes</a> or <a href="#maxvert">maxvert</a> is
 * reached.
 *
 * <li> <a name="maxvert"><code>maxvert</code></a> <i>number</i>
 * <br> Maximum number of vertices in mesh (see <a
 * href="#maxsolve">maxsolve</a>)
 *
 * <li> <a name="lrpbe"><code>lrpbe</code></a>
 * <br> Specifies the linearized form of the regularized PBE equation (RPBE).
 * The regularized PBE equation replaces the point charge distribution with the
 * corresponding Green's function.  As a result of this replacement, the
 * solution corresponds to the reaction field instead of the total potential;
 * the total potential can be recovered by adding the approrriate Coulombic
 * terms to the solution.  Likewise, this equation immediately yields the
 * solvation energy without the need for reference calculations.  Either this
 * keyword or one of <a href="#npbe">npbe</a>, <a href="#lpbe">lpbe</a>, or <a
 * href="#nrpbe">nrpbe</a> must be present.  
 * <b>NOTE:  this function is only available for FEM-based solvers (i.e., <a
 * href="#fe-manual">fe-manual</a>).</b>
 * 
 * <li> <a name="nrpbe"><code>nrpbe</code></a>
 * <br> Specifies the full form of the regularized PBE equation (RPBE).
 * The regularized PBE equation replaces the point charge distribution with the
 * corresponding Green's function.  As a result of this replacement, the
 * solution corresponds to the reaction field instead of the total potential;
 * the total potential can be recovered by adding the approrriate Coulombic
 * terms to the solution.  Likewise, this equation immediately yields the
 * solvation energy without the need for reference calculations.  Either this
 * keyword or one of <a href="#npbe">npbe</a>, <a href="#lpbe">lpbe</a>, or <a
 * href="#lrpbe">lrpbe</a> must be present.
 * <b>NOTE:  this function is only available for FEM-based solvers (i.e., <a
 * href="#fe-manual">fe-manual</a>).</b>
 * 
 * </ul>
 *  
 * @subsection print PRINT statement
 * 
 * This is a very simple section that allows linear combinations of calculated
 * properties to be written to standard output.  It has the format<br><br>
 *    <code>print</code> <i>keyword</i> <i>id</i> <i>op</i> <i>id</i>
 * <i>op</i> <i>id</i> ... <code>end</code><br><br>
 * where spaces are important and the components are
 * <ul>
 * <li> <i>keyword</i> 
 * <br> Specifies the observable to operate on and is one of the following:
 *   <ul>
 *   <li> <code>energy</code> <br>  Perform the calculations on the total
 *   energy 
 *   <li> <code>force</code> <br>  Perform the calculations on the force
 *   components
 *   </ul>
 *   <li> <i>id</i> 
 *   <br> ELEC statement ID (they are assigned in increasing order of
 *        declaration in the input file, starting at 1)  
 *   <li> <i>op</i>
 *   <br> Is the operation to perform and is one of the following:
 *     <ul>
 *     <li> + <br> Addition
 *     <li> - <br> Subtraction
 *     </ul>
 * </ul>
 * So a typical declaration might look like
 * <pre>
 * print energy 3 - 2 - 1 end
 * </pre>
 * and be interpreted as "subtract the energy from ELEC statements #1 and #2
 * from the energy in ELEC statement #3" (i.e., a binding energy calculation).
 * Alternatively, single energies can also be printed; for example:
 * <pre>
 * print energy 1 end
 * </pre>
 * <br>
 * 
 * <b>NOTE:</b> It is important to realize that, in the case of automatic
 * focusing (mg-auto), PRINT works using ELEC statement numbers, not the
 * calculation numbers which appear while APBS is running.
 * 
 * <hr width="100%">
 * @section lists APBS mailing lists
 * <p> There are two mailing lists available for the APBS software.  
 * <ul>
 * <li> Announcements.  Users can stay informed about APBS-related news
 * (updates, bugs, etc.) on this low-traffic list.<br>
 * <a href="http://cholla.wustl.edu/mailman/listinfo/apbs-announce">List
 * information</a><br>
 * <a href="http://cholla.wustl.edu/pipermail/apbs-announce/">List
 * archives</a>
 * <li> User discussion.  Users can discuss various aspects of APBS and get
 * help with problems on this list.<br>
 * <a href="http://cholla.wustl.edu/mailman/listinfo/apbs-users">List
 * information</a><br>
 * <a href="http://cholla.wustl.edu/pipermail/apbs-users/">List
 * archives</a>
 * </ul>
 * 
 * <hr width="100%">
 * @section bugs Bugs and reporting problems
 * 
 * <p> The following is a list of some of the bugs in APBS, a list of bugs in
 * specific functions can be found <a href="bug.html">here</a>.
 * <ul>
 * <li> When using the molecular surface definitions (<code>srfm 0, 1</code>)
 * for dielectric assignment, the accessibility evaluation routines slow the
 * problem setup down considerably; especially during focusing.  This is
 * essentially a trade-off with being able to handle very large molecules.  We
 * don't ever assemble the Shrake and Rupley solvent-accessible surface due to
 * the possiblity of this being very large for very large molecules.  However,
 * such a surface would allow us to build up the accessibility maps in 
 * O(number of atoms) time rather than O(number of grid points) time.
 * </ul>
 * 
 * <p> Problems can be reported to the APBS User mailing list at <a
 * href="mailto:apbs-users@cholla.wustl..edu">apbs-users@cholla.wustl.edu</a>.
 * To subscribe, simply visit 
 * <a
 * href="http://cholla.wustl.edu/mailman/listinfo/apbs-users">http://cholla.wustl.edu/mailman/listinfo/apbs-users</a>.
 * Archives for the list are available at <a
 * href="http://cholla.wustl.edu/pipermail/apbs-users/">http://cholla.wustl.edu/pipermail/apbs-users/</a>.
 * 
 * <hr width="100%">
 * @section reading Further reading
 * 
 * More detailed information about APBS can be found in the following papers:
 * <ul>
 * <li> N. A. Baker, D. Sept, S. Joseph, M. J. Holst, J. A. McCammon.
 * Electrostatics of nanosystems:  application to microtubules and the
 * ribosome.  <i>Proc. Natl. Acad. Sci. USA</i> <b>98</b>, 10037-10041, 2001.
 * <a href="http://www.pnas.org/cgi/reprint/181342398v1">Paper (at PNAS)</a>
 * <li>  N. A. Baker, D. Sept, M. J. Holst, and J. Andrew McCammon.  The
 * adaptive multilevel finite element solution of the Poisson-Boltzmann
 * equation on massively parallel computers.  <i>IBM Journal of Research and
 * Development.</i> <b>45</b>, 427-438, 2001. <a
 * href="http://www.research.ibm.com/journal/rd/453/baker.pdf">Paper (at
 * IBM)</a>
 * <li> M. Holst, N. Baker, and F. Wang, Adaptive multilevel finite element
 * solution of the Poisson-Boltzmann equation I: algorithms and examples. <i>J.
 * Comput. Chem.</i> <b>21</b>, 1319-1342, 2000.  <a
 * href="http://www3.interscience.wiley.com/cgi-bin/fulltext?ID=73503240&PLACEBO=IE.pdf">Paper
 * (at Wiley site)</a>
 * <li> N. Baker, M. Holst, and F. Wang, Adaptive multilevel finite element
 * solution of the Poisson-Boltzmann equation II: refinement at solvent
 * accessible surfaces in biomolecular systems. <i>J. Comput. Chem.</i>
 * <b>21</b>, 1343-1352, 2000.  <a
 * href="http://www3.interscience.wiley.com/cgi-bin/fulltext?ID=73503235&PLACEBO=IE.pdf">Paper
 * (at Wiley site)</a>
 * </ul>
 * APBS has been featured in:
 * <ul>
 * <li> Chemical and Engineering News Chemistry Highlights 2001 (cover story)
 * <a
 * href="http://pubs.acs.org/cen/coverstory/7950/7950highlights2001.html">Chemical
 * and Engineering News (Vol. 79, No. 50, pp. 45-55  Dec 10, 2001)</a>
 * <li> <a href="http://pubs.acs.org/cen/topstory/7935/7935notw1.html">Chemical
 * and Engineering News (Vol. 79, No. 35, pp. 1  Aug 27, 2001)</a>
 * <li> <a href="http://www.newscientist.com/news/news.jsp?id=ns99991179">New
 * Scientist</a> (top story)
 * <li> <a href="http://www.sciencenews.org/20010901/toc.asp">Science News (Vol.
 * 160, No. 9, Sept. 1, 2001)</a>
 * <li> <a href="http://www.hhmi.org/news/mccammon.html">Howard Hughes Medical
 * Institute news</a>
 * <li> <a
 * href="http://ucsdnews.ucsd.edu/newsrel/science/electriclandscape.htm">UCSD/SDSC
 * news</a>
 * <li> <a
 * href="http://kevxml.infospace.com/info/kevxml?kcfg=upi-article&sin=200108202131220
 * 004838&otmpl=/upi/story.htm&qcat=science&rn=25601&qk=10&passdate=08/20/2001">United
 * Press International</a>
 * <li> <a
 * href="http://www.bio.com/newsfeatures/newsfeatures_research.jhtml;jsessionid=QIRPZ5KRLZYRJR3FQLMSFEQ?sectionId=2&contentType=1&action=view&contentItem=156784&Page=1">Bio.Com</a>
 * <li> <a
 * href="http://www.supercomputingonline.com/article.php?sid=492">Supercomputing
 * Online</a> (article)
 * <li> <a
 * href="http://www.supercomputingonline.com/article.php?sid=526">Supercomputing
 * Online</a> (interview)
 * <li> <a
 * href="http://www.sciencedaily.com/releases/2001/08/010821075855.htm">Science
 * Daily</a>
 * <li> <a href="http://unisci.com/stories/20013/0822011.htm">UniSci</a>
 * <li> <a href="http://www.medserv.dk/print.php?sid=869">MedServ</a>
 * <li> <a
 * href="http://www.ascribe-news.com/cgi-pub/d?asid=20010822.095531">AScribe</a>
 * <li> <a href="http://www.npaci.edu/online/v5.17/mccammon.html">NPACI Online
 * (Vol. 5, No. 17, Aug. 22 2001)</a>
 * <li> <a href="http://www.npaci.edu/envision/v16.3/baker.html">NPACI EnVision
 * (Vol. 16, No. 3, Jul. - Sept. 2000)</a>
 * <li> NPACI EnVision (Vol. 17, No. 4, Oct. - Dec. 2001)
 * <li> <a
 * href="http://www.smalltimes.com/document_display.cfm?document_id=2155">Small
 * Times (Sept. 10, 2001)</a>
 * <li> BioInform
 * </ul>
 * 
 * <hr>
 * @section authors Author List
 * <p>
 * The current author list is:
 * <ul>
 * <li> <a href="http://agave.wustl.edu/">Nathan Baker</a>:  primary author
 * <li> <a href="http://www.scicomp.ucsd.edu/~mholst">Mike Holst</a>:  advisor,
 *      author of several routines scattered about APBS, and author of PMG (the
 *      multigrid library used by this code), author of
 *      MALOC (hardware abstraction library used by this code), author of FEtk
 *      (finite element library incorporated in developmental versions of this
 *      code) 
 * <li> <a href="http://mccammon.ucsd.edu">J. Andrew McCammon</a>:  advisor, 
 *      financial and equipment support
 * <li> Robert Konecny:  contributor (parameters, CHARMM FORTRAN interface)
 * <li> Todd Dolinsky:  contributor (Python wrappers and tools)
 * <li> <a href="http://biomed.wustl.edu/faculty/sept">Dave Sept</a>:
 *      contributor (scripts and tools, VMD compatibility, general suggestions
 *      about functionality) 
 * <li> Chiansan Ma:  contributor (scripts)
 * <li> <a href="http://www.biochem.uiowa.edu/faculty/elcock/">Adrian
 *      Elcock</a>: contributor (parameter files) 
 * <li> Tongye Shen:  contributor (finite element mesh generation)
 * <li> Larry Canino:  contributor (solvent accessibility functions)
 * <li> Jung-Hsin Lin:  contributor (OpenDX to MOLMOL conversion)
 * <li> <a href="http://www.cs.uiuc.edu/people/faculty/bond.html">Steve
*       Bond</a>:  contributor (FEtk finite element library compatibility and
*       Vopot functions)
 * <li> <a href="http://www.ks.uiuc.edu/~justin/">Justin Gullingsgrud</a>:
 *      optimization of the boundary condition calculation functions called by
 *      Vpmg_setup
 * </ul>
 *
 * <hr>
 * @section programming Programmer's Guide
 * <p>
 * This documentation provides information about the programming interface
 * provided by the APBS software and a general guide to linking to the APBS
 * libraries.  Information about installation, configuration, and general usage
 * can be found in the <a href="user.html">User's Guide</a>.
 * 
 *  @subsection style Programming Style
 * 
 *  <p>
 *  APBS was developed following the <a
 *  href="http://scicomp.ucsd.edu/~mholst/codes/maloc/cleanc.html">Clean OO
 *  C</a> style of Mike Holst.  In short, Clean OO C code is written in a
 *  object-oriented, ISO C-compliant fashion, and can be compiled with either a
 *  C or C++ compiler.  <p> Following this formalism, all public data is
 *  enclosed in structures which resemble C++ classes.  These structures and
 *  member functions are then declared in a public header file which provides a
 *  concise description of the interface for the class.  Private functions and
 *  data are included in private header files (or simply the source code files
 *  themselves) which are not distributed.  When using the library, the
 *  end-user only sees the public header file and the compiled library and is
 *  therefore (hopefully) oblivious to the private members and functions.  Each
 *  class is also equipped with a constructor and destructor function which is
 *  responsible for allocating and freeing any memory required by the
 *  instatiated objects.
 * 
 *  <p>
 *  As mentioned above, public data members are enclosed in C structures which
 *  are visible to the end-user.  Public member functions are generated by
 *  mangling the class and function names <i>and</i> passing a pointer to the
 *  object on which the member function is supposed to act.  For example, a
 *  public member function with the C++ declaration 
 *    <pre>
 *   public double Foo::bar(int i, double d)
 *   </pre>
 * would be declared as
 *   <pre>
 *   VEXTERNC double Foo_bar(Foo *thee, int i, double d)
 *   </pre>
 * where <code>VEXTERNC</code> is a compiler-dependent macro, the underscore
 * <code>_</code> replaces the C++ double-colon <code>::</code>, and
 * <code>thee</code> replaces the <code>this</code> variable implicit in all
 * C++ classes.  Since they do not appear in public header files, private
 * functions could be declared in any format pleasing to the user, however, the
 * above declaration convention should generally be used for both public and
 * private functions.  Within the source code, the public and private function
 * declarations/definitions are prefaced by the macros <code>VPUBLIC</code> and
 * <code>VPRIVATE</code>, respectively.  These are macros which reduce global
 * name pollution, similar to encapsulating private data withing C++ classes.
 *  
 * <p>
 * The only C++ functions not explicitly covered by the above declaration
 * scheme are the constructors (used to allocate and initialize class data
 * members) and destructors (used to free allocated memory).  These are
 * declared in the following fashion:  a constructor with the C++ declaration
 *    <pre>
 *    public void Foo::Foo(int i, double d)
 *    </pre>
 * would be declared as
 *     <pre>
 *     VEXTERNC Foo* Foo_ctor(int i, double d)
 *     </pre>
 * which returns a pointer to the newly constructed <code>Foo</code> object.
 * Likewise, a destructor declared as
 *     <pre>
 *     public void Foo::~Foo()
 *     </pre>
 * in C++ would be
 *     <pre>
 *     VEXTERNC void Foo_dtor(Foo **thee)
 *     </pre>
 * in Clean OO C.
 * <p>
 * Finally, inline functions in C++ are simply treated as macros in Clean OO C
 * and declared/defined using <code>#define</code> statements in the public
 * header file.
 * <p>
 * See any of the APBS header files for more information on Clean OO C
 * programming styles.
 * 
 * @subsection api Application programming interface documentation
 * <p>
 * The API documentation for this code was generated by <a
 * href="http://www.doxygen.org">doxygen</a>.  You can either view the API
 * documentation by using the links at the top of this page, or the slight
 * re-worded/re-interpreted list below:
 *    <ul>
 *    <li> <a href="modules.html">Class overview</a>
 *    <li> <a href="annotated.html">Class declarations</a>
 *    <li> <a href="functions.html">Class members</a>
 *    <li> <a href="globals.html">Class methods</a>
 *    </ul>
 * 
 */
