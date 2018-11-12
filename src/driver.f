c
c* The sample of test driver for FTAN with phase match filter for
c* subroutines aftanpg and aftanipg
c
      integer*4 n, npoints, nfin, nfout1, nfout2, ierr, nprpv
      real*8    t0, dt, delta, vmin, vmax, tmin, tmax
      real*8    snr, tresh, ffact, perc, taperl,fmatch,piover4
      real*4    sei(32768)
      real*8    arr1(8,100),arr2(7,100)
      real*8    tamp, ampo(32768,100), pred(300,2)
      integer*4 nrow, ncol, npred
      real*8    prpvper(300),prpvvel(300)
      character*250 name,cmd
      integer*4 i,i0,sac,nargc,iargc

      sac = 1
      i0  = 1

c---  input command line arguments treatment
      nargc = iargc()
      if(nargc.ne.1) then
          write(*,*) "Usage: aftan4_c_test parameter_file\n"  
          stop
      endif
      call getarg(1,cmd)
      open(10,file=cmd,status='old')
   1  read(10,'(a250)',end=2) cmd
      read(cmd,*,end=2) piover4,vmin,vmax,tmin,tmax,tresh,ffact,taperl,snr,fmatch
      do i = lnblnk(cmd),1,-1
        if(cmd(i:i).eq.' ') then
          i0 = i+1
          goto 9
        endif
      enddo
   9  name = cmd(i0:lnblnk(cmd))
c     write(*,*) piover4,vmin,vmax,tmin,tmax,tresh,ffact,taperl,snr,fmatch,name
      write(*,1000) piover4,vmin,vmax,tmin,tmax
1000  format(1x,'pi/4=',f5.1," vmin=",f6.2," vmax=",f6.2,
     *       " tmin=",f7.2," tmax=",f7.2)
      write(*,1001) tresh,ffact,taperl,snr,fmatch
1001  format(1x,"tresh= ",f7.2," filter factor= ",f6.2," taperl=",f7.2,
     *       " snr= ",f7.2," match = ",f7.2)
      write(*,*) "Data file name= ",name(1:lnblnk(name))
      cmd = name(1:lnblnk(name))//'_PHP'
      write(*,*) "Phase velocity prediction file name= ",cmd(1:lnblnk(cmd))
      open(11,file=cmd,status='old')
      nprpv = 1
  3   read(11,*,end=4) prpvper(nprpv),prpvvel(nprpv) 
      nprpv = nprpv+1
      goto 3
  4   nprpv = nprpv-1
      close(11)
c 
c    read SAC or ascii data 
c  
      call readdata(sac,name,n,dt,delta,t0,sei,ierr)
      nfin    = 64
      npoints = 5
      perc    = 50.0d0
      write(*,*) "t0 = ",t0
      write(*,1002) nfin,perc,npoints
1002  format(1x,"#filters= ",i5," Perc= ",f6.2," npoints= ",i5)
c---  FTAN with phase with phase match filter. First Iteration. 

      write(*,*)"FTAN - the first ineration\n"
      ffact = 1.0d0
      call aftanpg(piover4,n,sei,t0,dt,delta,vmin,vmax,tmin,tmax,tresh,
     *        ffact,perc,npoints,taperl,nfin,snr,nprpv,prpvper,prpvvel,
     *        nfout1,arr1,nfout2,arr2,tamp,nrow,ncol,ampo,ierr)
      call printres(dt,delta,nfout1,arr1,nfout2,arr2,tamp,nrow,ncol,ampo,
     *              ierr,name,"_1")
      if(nfout2 .eq. 0) goto 2
      write(*,*) "Tamp = ",tamp," nrow = ",nrow," ncol = ",ncol

c---  Make prediction based on the first iteration 

      npred = nfout2
      tmin = arr2(2,1)
      tmax = arr2(2,nfout2)
      do i = 1,nfout2 
          pred(i,1) = arr2(2,i)
          pred(i,2) = arr2(3,i)
      enddo

c---  FTAN with phase with phase matching filter. Second Iteration.

      write(*,*) "FTAN - the second iteration (phase match filter)"
      ffact = 1.0d0
      write(*,*) 'Filter factor: ',ffact
      call aftanipg(piover4,n,sei,t0,dt,delta,vmin,vmax,tmin,tmax,tresh,
     *        ffact,perc,npoints,taperl,nfin,snr,fmatch,npred,pred,
     *        nprpv,prpvper,prpvvel,
     *        nfout1,arr1,nfout2,arr2,tamp,nrow,ncol,ampo,ierr)
      call printres(dt,delta,nfout1,arr1,nfout2,arr2,tamp,nrow,ncol,ampo,
     *              ierr,name,"_2")
      write(*,*) "Tamp = ",tamp," nrow = ",nrow," ncol = ",ncol
      goto 1
   2  close(10)
      end
