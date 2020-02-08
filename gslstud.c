/* gslstud.c - 5 Card Stud Poker, GSL generators Version 0.1.0 */
/* Copyright (C) 2020 aquila57 at github.com */

/* This program is free software; you can redistribute it and/or     */
/* modify it under the terms of the GNU General Public License as    */
/* published by the Free Software Foundation; either version 2 of    */
/* the License, or (at your option) any later version.               */

/* This program is distributed in the hope that it will be useful,   */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of    */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the      */
/* GNU General Public License for more details.                      */

/* You should have received a copy of the GNU General Public License */
/* along with this program; if not, write to:                        */

   /* Free Software Foundation, Inc.                                 */
   /* 59 Temple Place - Suite 330                                    */
   /* Boston, MA 02111-1307, USA.                                    */

#include "poker.h"

int main(void)
   {
   int i;
   int lmt;
   unsigned int dttk;         /* combined date, time #ticks   */
   time_t now;                /* current date and time        */
   clock_t clk;               /* current number of ticks      */
   struct tms t;              /* structure used by times()    */
   const gsl_rng_type *T;     /* RNG name to allocate         */
   gsl_rng *rng;              /* GSL RNG structure            */
   double tally[16];
   char *last;
   char *p,*q;
   char cards[128];
   char deck[128];
   /************************************************************/
   /* Initialize random number generator                       */
   /* Obtain environment variable GSL_RNG_TYPE                 */
   /* Allocate random number generator structure               */
   /* Initialize seed to date and time of day                  */
   /* Print seed in hex to document test.                      */
   /************************************************************/
   gsl_rng_env_setup();
   T = gsl_rng_default;
   /* allocate the random number generator env variable    */
   rng = (gsl_rng *) gsl_rng_alloc(T);
   /* get clock ticks since boot                           */
   clk = times(&t);
   /* get date & time                                      */
   time(&now);
   /* combine date, time, and ticks into a single UINT     */
   dttk = (unsigned int) (now ^ clk);
   /* initialize the GSL RNG                                   */
   /* random number generator to date,time,#ticks              */
   gsl_rng_set(rng, dttk);     /* initialize RNG seed          */
   /************************************************************/
   for (i=0;i<16;i++) tally[i] = 0.0;
   i = SIZE;
   while (i--)
      {
      int j;
      double dbllmt;
      for (j=0;j<52;j++) cards[j] = (char) j;
      lmt = 52;
      dbllmt = (double) lmt;
      last = (char *) cards + lmt - 1;
      p = (char *) deck;
      while (dbllmt > 1.0)
         {
	 double num;
         int indx;
	 num = floor(gsl_rng_uniform(rng) * dbllmt);
	 indx = (int) num;
         q = (char *) cards + indx;
         *p++ = *q;
         *q = *last--;
	 dbllmt -= 1.0;
         } /* for each card */
      *p++ = cards[0];
      *p = '\0';
      analdeck(deck, tally);
      } /* for each deal */
   printf("\t\t5 Card Stud Poker Test\n");
   printf("\t     GNU Scientific Library: %s\n",
      gsl_rng_name(rng));
   calcchi(tally,SIZE);
   gsl_rng_free(rng);
   return(0);
   } /* main */
