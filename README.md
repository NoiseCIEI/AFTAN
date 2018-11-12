# AFTAN (Automatic Frequency Time Analysis)

INTRODUCTION

The aftan Release 1.1 package provides instruments for Automatic
Frequency_Time Analysis (AFTAN) of cros-correlogram of the
ambient seismic noise [1,2].
The output of programs based on this package are group and phase
velocities of fundamental Rayleigh and Love modes which can be used
in surface wave tomographic studies (e.g.,[6],[7]).
The AFTAN is a modification of previously developed and widely used
FTAN (e.g., [3],[4],[5].
The AFTAN converts time series of cross-correlation functions into
frequency-time diagramms of signal power as a function of frequency
and group time by means of the multiple narrow-band filtering.
Then it provides automatic measurements of group and phase velocities
together with estimates of signal/noise ratios of these measurements.

CONTENTS

1. PACKAGE CONTENTS
2. INSTALLATION
3. SYSTEM REQUIREMENTS
4. TEST ISTALLATION
5. DESCRIPTION OF THE AFTAN-1.1 PACKAGE
   REFERENCES


1. PACKAGE CONTENTS
   ================
The contents of the package are as follows:
README         this file
bin            contains two 64-bit executable programs aftan_c_test and
               aftan_f_test,OS RHEL 5.9
src            contains program source codes
TEST1          contains precomputed example test
TEST2          directory to run your own  installation

2.  INSTALLATION
   ================
   Use the gunzip and tar command to extract distribution contents.

     ...> gunzip aftan-1.1.tgz
     ...> tar xvf aftan-1.1.tar

This will yield a top level directory named aftan-1.1 with an executable,
along with other miscellaneous files.
Go to ancc-1.1/src directory and recompile, if necessary, all programs.
To do that execute the following coomands
   ...> make clean
   ...> make
   ...> make install

The resulting binary modules aftan_c_test and aftan_f_test will be installed
under aftan-1.1/bin directory. In case of problems update Makefile properly.
The gftan-1.1/bin directory originally includes binary modules compiled by
gcc/gfortran v4.1.2 compiler under RHEL 5.9 (RedHat Enterprise Linux 5.9)
Operational System.

The package required installation of the fftw libraries version 3.2.4 or
higher for the Fast Fourier Transformation
fftw's libraries must be installed in system under root user for better
performance. See an example of run in the directory TEST1 and try your own run
in directory TEST2.    

3. SYSTEM REQUIREMENTS
   ===================

   - 64-bit or 32-bit platforms
   - Software:  fftw v.3.2.4 or higher
   - Linux Operation System,
     currently tested on RHEL 5.x, 32 and 64 bit version under
     gcc/gfortran v4.1.2
   - SUN OS Solaris
     currently tested on Solaris rel.5.7/5.8/5.10 cc/f77 WorkShop Compilers 4.2
   - Mac X
     currently tested on OS 10.7 (Snow Leopard), gcc/gfortran v4.6,fftw3.2.2
   - have to work under other Linux OS and compilers with minor changes.

4. TEST INSTALLATION
   =================
   Go to aftan-1.1/TEST1 and after aftan-1.1/TEST2 and follow README files.

5. DESCRIPTION OF THE AFTAN-1.1 PACKAGE
   ====================================

The atan-1.1 package consists of the set of FORTAN subroutines and C
functions. Based on this set, it is possible to write separate
programs or imbed into existing software, which is required FTAN
analysis. The atan-1.1 package offers two programs written on C and
FORTRAN language, that used as testing programs, and might be used
on constant base to permorm automatic FTAN analysys for the huge
scope of cross-correlation functions settled in IRIS Product [1].
Thus, aftan_c_test and aftan_f_test are those testing programs for
aftan-1.1 package. Both programs must produce the same result.
The aftan_c_test program includes main module driver_c.c written
on C language, which is an example of C interface to aftan-1.1 package.
The aftan_f_test program includes main module driver.f, which is the
program interface to the aftan-1.1 package written on FORTRAN language.
You may use any programs mentioned above as for testing purposes or on
regular base.  Also, you can modify or create your own version of the
main programs driver_c.c or driver.f.

5.1 Here we briefly describe the aftan_c_test program for C-interface.

SYNOPSIS
    aftan_c_test param_file
DESCRIPTION
    While starting, aftan_c_test reads line by line the parameter file
    pointed by path param_file. Each line includes subset of the most
    important parameters and path to cross-correlation SAC file. The rest
    parameters must be defined in the driver_c.c module. For example,
    some line look like

    -1.0 1.5 5.0 4.0 30.0 20.0 1.0 1.0 0.2 1.0 ctest/COR_TA.M14A_TA.M17A.SAC

    The line includes values for variables described later in section 5.2.2,
    namely, piover4,vmin,vmax,tmin,tmax,tresh,ffact,taperl,snr,fmatch
    and path name to SAC binary file in form of path_dir/file_name.
    The directory path_dir may be individual for each line that we
    call simply "data dir".
    NOTE: SAC file name must have the extension ".SAC"  .

    The other parameters  sac,nfin,npoints,perc,ffact are initialized
    in the module driver_c.c.
    For each line of the parameter file aftan_c_test does the following
    things:
    a) reads predicted phase velocity file from the data directory,
       if it exists the name has the form "file_name_PHP".
       For example, in our case, the predicted group velocity file name is
       COR_TA.M14A_TA.M17A.SAC_PHP
       NOTE: The ..._PHP file should not be very accurate. The main goal of
             this file to choose the branch of phase velocity. AFTAN alogirithm
             try to estimate right branch at single period only, namely,
             at maximal period of period range. The good approximation
             could be PREM 1D model without water layer or some phase
             dispersion cirve obtained from average regional share velocity
             model.
    b) reads cross-correlation from SAC file by reading data_ function (C) ???
    c) performs basic FTAN  by aftanpg_ subroutine (FORTRAN)
    d) writes results on  screen and into file system inside the data directory
       by printres_ function (C)
    e) makes match-filtering of FTAN diagram by aftanipg_ subroutine (FORTRAN)
    f) writes results on  screen and into file system insides data directory
       by printres_ function (C)

INPUT DATA
    aftan_c_test reads predicted phase velocity (ASCII plane file), if it
    exists, from data directory. It should have the name form of "file_name_PHP".
    The file_name_PHP includes the following lines:

    Line1: Any text size of up to 80 characters
    Lines2-n: per, pha_vel      Format: Unformatted
    where, per is period in sec, and pha_vel is predicted phase
    velocity in km/s

OUTPUT DATA

     aftan_c_test outputs in data dir three type of ASCII flat files.
     If path to SAC file is "XXXX", then aftan_c_test creates the following
     resulting files for base FTAN:
     XXXX01_AMP, XXXX01_DISP.0, XXXX01_DISP.1
     and resulting files for match-filtered FTAN:
     XXXX02_AMP, XXXX02_DISP.0, XXXX02_DISP.1
5.1.1 Format of XXXX01_AMP and XXXX02_AMP xyz grid files
    The files  XXXX01_AMP and XXXX02_AMP  are envelop FTAN diagrams and
    have the same formats. The number of lines in files is nrow*ncol+1,
    see section 5.2.2.
    Line 1: nrow,ncol,dt,delta
    where,
       nrow  - number of periods
       ncol  - number of times
       dt    - time step in sec
       delta - epicentral distance in km
    Lines 2-nrow*ncol+1:  n, tamp, amp
    where,
       n is the reference number to the line in the file XXXX01_DISP.0 for
       XXXX01_AMP or to the line in the file XXXX02_DISP.0 for XXXX02_AMP .
       tamp, is a time of FTAN diagram in sec, and amp if FTAN diagram
       amplitude in Db, max value for each reference number n is 100 Db.

5.1.2 Format of XXXX01_DISP.0 and XXXX02_DISP.0 files.
    The file XXXX01_DISP.0  includes the complete results of the base FTAN
    and XXXX02_DISP.0 include complete results of the match filtering FTAN.
    The number of lines in files is nfout1 for XXXX01_DISP.0
    file, and nfout2 for XXXX02_DISP.0 file.
    Each line of file has 8 fields:
    nf, cper, oper, gvel, pvel, ampl, dfunc, snr
    nf     - filter number, starting from 1 by 1
    cper   - central periods, s
    oper   - observed periods, s
    gvel   - group velocity, km/s
    pvel   - phase velocity, km/s or phase if nphpr=0, rad
    ampl   - amplitudes, Db
    dfunc  - discrimination function, second derivative of group velocity
             by frequence
    snr    - signal/noise ratio, Db

5.1.3 Format of XXXX01_DISP.1 and XXXX02_DISP.1 files.
    The file XXXX01_DISP.1 includes the cleaned results of the base FTAN
    and XXXX02_DISP.1 include cleaned results of the match filtering FTAN.
    The number of lines in files is nfout1 for XXXX01_DISP.1
    file, and nfout2 for XXXX02_DISP.1 file.
    Each line of file has 7 fields:
    nf, cper, oper, gvel, pvel, ampl, snr
    nf     - filter number, starting from 1 by 1
    cper   - central periods, s
    oper   - observed periods, s
    gvel   - group velocity, km/s
    pvel   - phase velocity, km/s or phase if nphpr=0, rad
    ampl   - amplitudes, Db
    snr    - signal/noise ratio, Db


5.2  Here we briefly describe the aftan_f_test program for FORTRAN interface:

SYNOPSIS
    aftan_f_test param_file

The most important subroutine/functions of the aftan package are

5.2.1 C function readdata_ , from module misc.c

NAME
    readdata_ reads  symmetric cross-correlation from SAC file
SYNOPSIS
    void readdata_(int *sac,char *name,int *n,double *dt,double *delta,
                   double *t0,float sei[32768], int *ierr);
DESCRIPTION
  Input formal arguments:
    sac      - should be 1 all the time
    name     - path to the SAC file
  Output  formal arguments:
    n        - length of cross-correlation function
    dt       - sampling step, in sec
    delta    - distance between pair of stations
    t0       - time shift, zero all the time
    sei      - cross-correlation itself
    ierr     - return value, non zero in case some errors

WARNING: The header of the SAC cross-correlation file must be properly
         constructed. If the lag of the cross-correlation function is m,
         e.g. length of the cross-correlation is 2*m+1, than, the header
         field b must be negative and equal to -m*dt, number of
         points should be npts=2*m+1, and the field dist (distance) must be
         properly defined. If you are not sure about dist read and write all
         SAC files in place by sac program before running aftan.

5.2.2 Subroutine aftanpg.f

NAME
    aftanpg - performs FTAN analysis on regular base
SYNOPSIS
      subroutine aftanpg(piover4,n,sei,t0,dt,delta,vmin,vmax,tmin,tmax,
     *           tresh,ffact,perc,npoints,taperl,nfin,fsnr,nphpr,phprper,
     *           phprvel,nfout1,arr1,nfout2,arr2,tamp,nrow,ncol,amp,ierr)
      real*8    piover4
      integer*4 n
      real*4    sei(32768)
      real*8    t0,dt,delta,vmin,vmax,tmin,tmax,tresh,ffact,perc
      integer*4 npoints
      real*8    taperl
      integer*4 nfin
      real*8    fsnr
      integer*4 nphpr
      real*8    phprper(300),phprvel(300)
      integer*4 nfout1
      real*8    arr1(8,100)
      integer*4 nfout2
      real*8    arr2(7,100)
      real*8    tamp
      integer*4 nrow,ncol
      real*8    amp(32768,100)
      integer*4 ierr

DESCRIPTION

Input formal arguments:

  piover4 - factor to pi/4. piover4*pi/4 is a constant phase shift equal to
            "-1.0" for cross-correlation functions and some value for
            other signals. piover4 takes effect on phase velocity only and
            doesn't change group velocity.
  n       - length of input waveform.
  sei     - input cross-correlation function (waveform) length of n,
            the first element of array sei must correspond zero argument
            of the cross-correlation function
  t0      - time of the first sample of input wave form, usually 0.0 , in sec
  dt      - sampling step of waveform, in sec
  dist    - distance between pair of cross-correlates station, or
            between source and station.
  vmin,vmax - minimal and maximal values of group velocity, in km/s
            dist/vmax and dist/vmin cut from array sei segment of data
            for FTAN analysis.
  tmin,tmx - periods range, in sec
  tresh    - threshold for second derivative of group velocity, used
             for jumps detection, usually tresh = 10.0.
  ffact    - factor to width of  FTAN filters, usually  ffact=1
  perc     - minimal length of the output segment relative whole length
             frequency range [tmin,tmax], in %
  npoints  - max number points in jump area
  taperl   - factor for the left end seismogram tapering
  nfin     - starting number of frequencies, nfin <= 100
  fsnr     - NOT USED, for future extensions
  nphpr    - length of phprper and phprvel arrays. If nphpr = 0, aftanpg
             subroutine does not output phase velocity branch, instead of
             it outputs phase.
  phprper  - predicted phase velocity periods, s
  phprvel  - predicted phase velocity for corresponding periods, s

Output formal parameters:

The main output parameters are stored in 2-D arrays arr1 and arr2,
arr1 contains preliminary results and arr2 - final.

  nfout1 - output number of frequencies for arr1, (integer*4)
  arr1   - preliminary results.
           arr1(1,j) -  central periods, s
           arr1(2,j) -  observed periods, s
           arr1(3,j) -  group velocities, km/s
           arr1(4,j) -  phase velocities, km/s or phase if nphpr=0, rad
           arr1(5,j) -  amplitudes, Db
           arr1(6,j) -  discrimination function
           arr1(7,j) -  signal/noise ratio, Db
           arr1(8,j) -  maximum half width, s
where j = 1,...,nfout1

  arr2   - final results
  nfout2 - output number of frequencies for arr2, (integer*4)
           If nfout2 == 0, no final result.
           arr2(1,j) -  central periods, s
           arr2(2,j) -  observed periods, s
           arr2(3,j) -  group velocities, km/sor phase if nphpr=0, rad
           arr2(4,j) -  phase velocities, km/s
           arr2(5,j) -  amplitudes, Db
           arr2(6,j) -  signal/noise ratio, Db
           arr2(7,j) -  maximum half width, s
where j = 1,...,nfout2
           tamp      -  time to the beginning of ampo table+t0, s
           nrow      -  number of rows in grid ampo
           ncol      -  number of columns in grid ampo
           amp       -  2D grid amplitude array, Db, (real*8)
The first index i (columns) of amp(i,j) refers to time , t=t0+(i-1)*dt,
the second j (rows) refer to the array arr1, namely, arr1(:,j).
  ierr   - completion status, =0 - O.K.,           (integer*4)
                              =1 - some problems occurs
                              =2 - no final results

5.2.3 Subroutine aftanipg.f

NAME
    aftanipg - performs phase matching filtering for input signal
               by predicted group velocity dispersion curve and
               later FTAN analysis.
SYNOPSIS
      subroutine aftanipg(piover4,n,sei,t0,dt,delta,vmin,vmax,tmin,tmax,
     *           tresh,ffact,perc,npoints,taperl,nfin,fsnr,fmatch,npred,
     *           pred,nphpr,phprper,phprvel,nfout1,arr1,nfout2,arr2,
     *           tamp,nrow,ncol,amp,ierr)
      real*8    piover4
      integer*4 n
      real*4    sei(32768)
      real*8    t0,dt,delta,vmin,vmax,tmin,tmax,tresh,ffact,perc
      integer*4 npoints
      real*8    taperl
      integer*4 nfin
      real*8    fsnr
      real*8    fmatch
      integer*4 npred
      real*8    pred(300,2)
      integer*4 nphpr
      real*8    phprper(300),phprvel(300)
      integer*4 nfout1
      real*8    arr1(8,100)
      integer*4 nfout2
      real*8    arr2(7,100)
      real*8    tamp
      integer*4 nrow,ncol
      real*8    amp(32768,100)
      integer*4 ierr

DESCRIPTION

The description of all formal arguments for the atanpg subroutine are valid
for the atanipg subroutine with the single exception - fsnr parameters.
   fsnr   - define two cutting points for both end of compressed signal
            by threshold value equal to maximal of signal with factor fsnr.
atanipg subroutine has 3 more additional parameters:
   fmatch - is the factor to compressed signal width defined by two
            cutting points
   nped   - length of predicted group velocity in array  pred(300,2)
   pred   - array including npred group velocity measurements,
            pred(:,1) - periods, in s
            pred(:,2) - group velocity measurements

5.2.4 C function printres_ (in module misc.c)

NAME
    printres_ - output data of aftanpg or aftanipg subroutines
                on a screen and hard drive in ASCII format
SYNOPSIS
    void printres_(double *dt,int *nfout1,double arr1[100][8],int *nfout2,
           double arr2[100][7],double *tamp, int *nrow,int *ncol,
           double amp[100][32768],int *ierr, char *name,char *pref);

DESCRIPTION
All formal parameters are described in the previous sections, except
three the last one.

   ierr - return value from aftanpg or aftanipg subroutines. If ierr = 0
          printres_ prints out results, if ierr != 0, do not print.
   name - path to output file name
   pref - part of extension of output file name    

If name is "XXXX" and pref is "YY",then printres_ create the following
output names:
  XXXXYY_AMP for FTAN amplitude map, array arr1 is reference for periods
  XXXXYY_DISP.0 for array arr1
  XXXXYY_DISP.1 for array arr2

REFERENCES

[1] IRIS DMS Product, Western US Ambient Noise Cross-Correlations,
  by Mikhail Barmine and Michael Rtizwoller, published electronically
  June 2012, Incorporated Research Institutions for Seismology,
  http://www.iris.edu/dms/products/ancc-ciei

[2] Bensen, G.D., M.H. Ritzwoller, M.P. Barmin, A.L. Levshin, F. Lin, M.P.
  Moschetti, N.M. Shapiro, and Y. Yang, Processing seismic ambient noise data
  to obtain reliable broad-band surface wave dispersion measurements,
  Geophys.J.Int., 169,1239-1260,doi: 10.1111/j.1365-246X.2007.03374.x,2007.

[3] Levshin, A.L., Pisarenko, V.F., Pogrebinsky, G.A., 1972. On a frequency-time
  analysis of oscillations, Ann. Geophys.,28, 211-218.

[4] Levshin, A.L.,Yanovskaya, T.B., Lander, A.V., Bukchin,B.G., Barmin, M.P.,
  Ratnikova, L.I. & Its, E.N., 1989. Seismic Surface Waves in a Laterally
  Inhomogeneous Earth, ed. Keilis-Borok, V.I., Kluwer, Norwell, Mass.

[5] Levshin, A., L. Ratnikova, and J. Berger, 1992. Surface rities of surface
  wave propagation across Central Eurasia, Bull. Seism. Soc. Amer., 82, 6, 2464-2493.

[6] Lin, F.-C., M.H. Ritzwoller, and R. Snieder, 2009. Surface wave tomography
  by phase-front tracking across a regional broad-band seismic array, Geophys.
  J. Int., 177(3), 1091-1110.

[7] Shapiro, N. M., M. Campillo, L. Stehly, and M. H. Ritzwoller, 2005.  
  High resolution surface wave tomography from ambient seismic noise, Science,
307(5715), 1615-1618.
