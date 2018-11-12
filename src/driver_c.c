/*
 * The sample of test driver for FTAN with phase match filter for
 * subroutines aftanpg and aftanipg
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "aftan.h"


int main (int argc, char *argv[])
{
 static  int n, npoints, nfin, nfout1, nfout2, ierr, nprpv;
 static  double t0, dt, delta, vmin, vmax, tmin, tmax;
 static  double snr, tresh, ffact, perc, taperl,fmatch,piover4;
 static  float sei[32768];
 static  double arr1[100][8],arr2[100][7];
 static  double tamp, ampo[100][32768], pred[2][300];
 static  int nrow, ncol, npred;
 static  double prpvper[300],prpvvel[300]; /* phase vel prediction files  */

  char  *p,name[160],buf[200],phvelname[160],root[160];
  FILE  *in, *inv;
  int   i;
  int   sac = 1; /* =1 - SAC, =0 - ftat files    */

/* input command line arguments treatment   */
  if(argc != 2) {
      printf("Usage: aftan4_c_test parameter_file\n");
      exit(-1);
  }
/* open and read contents of parameter file  */
  if((in = fopen(argv[1],"r")) == NULL) {
      printf("Can not find file %s\n",argv[1]);
      exit(1);
  }
  while((n = fscanf(in,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %s",
            &piover4,&vmin,&vmax,&tmin,&tmax,&tresh,&ffact,&taperl,&snr,&fmatch,
            name)) != EOF) { /* start main loop      */
  strcpy(root,name);
  p = strrchr(root,'.');
  *(p+1) = '\0';
  strcpy(phvelname,root);
  strcat(phvelname,"SAC_PHP");

      if(n == 0 || n != 11) break;

      printf("pi/4= %4.1lf, vmin= %lf, vmax= %lf, tmin= %lf, tmax= %lf\n",
              piover4,vmin,vmax,tmin,tmax);
      printf("Tresh= %lf, Filter factor= %lf, taperl= %lf, SNR= %lf, Match = %lf\nData file name=%s\n",
             tresh,ffact,taperl,snr,fmatch,name);
/* if presents, read phase velocity prediction file
   ---  */
  nprpv = 0;
  if((inv = fopen(phvelname,"r")) == NULL) {
      printf("Can not find file %s.\n",phvelname);
  } else {
  while(fgets(buf,200,inv) != NULL) {
         if((n = sscanf(buf,"%lf %lf",&prpvper[nprpv],&prpvvel[nprpv])) < 2) break;
         nprpv++;
     }
         fclose(inv);
         printf("Phase velocity prediction file name= %s\n",phvelname);
  }

/*
 *   read SAC or ascii data 
 */
      readdata_(&sac,name,&n,&dt,&delta,&t0,sei,&ierr);
  nfin    = 64;
  npoints = 5;          /* only 3 points in jump              */
  perc    = 50.0;       /* 50 % for output segment            */
  printf("#filters= %d, Perc= %6.2f %s, npoints= %d, t0= %6.2f\n",
          nfin,perc,"%",npoints,t0);

  printf("FTAN - the first ineration\n");
/*  nprpv = 0;    */
  ffact =1.0;
  aftanpg_(&piover4,&n,sei,&t0,&dt,&delta,&vmin,&vmax,&tmin,&tmax,&tresh,
        &ffact,&perc,&npoints,&taperl,&nfin,&snr,&nprpv,prpvper,prpvvel,
        &nfout1,arr1,&nfout2,arr2,&tamp,&nrow,&ncol,ampo,&ierr);
  printres_(&dt,&delta,&nfout1,arr1,&nfout2,arr2,&tamp,&nrow,&ncol,
            ampo,&ierr,name,"_1");
  if(nfout2 == 0) continue;   /* break aftan sequence     */
  printf("Tamp = %9.3lf, nrow = %d, ncol = %d\n",tamp,nrow,ncol);

/* Make prediction based on the first iteration               */

  npred = nfout2;
  tmin = arr2[0][1];
  tmax = arr2[nfout2-1][1];
  for(i = 0; i < nfout2; i++) {
      pred[0][i] = arr2[i][1];   /* apparent period  */
      pred[1][i] = arr2[i][2];   /* group velocities */
  }

/* FTAN with phase with phase match filter. Second Iteration. */
  printf("FTAN - the second iteration (phase match filter)\n");
  ffact = 1.0;
  printf("Filter factor=%6.2lf\n",ffact);
  aftanipg_(&piover4,&n,sei,&t0,&dt,&delta,&vmin,&vmax,&tmin,&tmax,&tresh,
        &ffact,&perc,&npoints,&taperl,&nfin,&snr,&fmatch,&npred,pred,
        &nprpv,prpvper,prpvvel,
        &nfout1,arr1,&nfout2,arr2,&tamp,&nrow,&ncol,ampo,&ierr);
  printres_(&dt,&delta,&nfout1,arr1,&nfout2,arr2,&tamp,&nrow,&ncol,
            ampo,&ierr,name,"_2");
  printf("Tamp = %9.3lf, nrow = %d, ncol = %d\n",tamp,nrow,ncol);

  }
  fclose(in);
  return 0;
}
