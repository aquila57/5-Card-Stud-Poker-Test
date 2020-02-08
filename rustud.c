/* rustud.c - 5 card stud test, RANDU generator  Version 0.1.0       */
/* Copyright (C) 2020  aquila57 at github.com                        */

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

/*********************************************************************/
/* This program illustrates how a bad random number generator        */
/* fails the chi square test of the 5 card stud poker test.          */
/*********************************************************************/

#include "poker.h"

#define RANDU (seed *= 65539)

int main(void)
   {
   int i;
   int lmt;
   unsigned int seed;
   double modulus;
   double dbllmt;
   double tally[16];
   char *last;
   char *p,*q;
   char cards[64];
   char deck[64];
   eefmt *ee;
   /***************************************************/
   /* initialize the RANDU random number generator    */
   /***************************************************/
   ee = (eefmt *) eeglinit();
   eegl(ee);
   seed = eegl(ee) | 1;
   free(ee->state);
   free(ee);
   modulus = 65536.0 * 65536.0;
   i = 0;
   p = (char *) cards;
   q = (char *) cards + 52;
   while (p < q) *p++ = i++;
   for (i=0;i<16;i++) tally[i] = 0.0;
   i = SIZE;
   while (i--)
      {
      int j;
      for (j=0;j<52;j++) cards[j] = (char) j;
      lmt = 52;
      dbllmt = (double) lmt;
      last = (char *) cards + lmt - 1;
      p = (char *) deck;
      while (dbllmt > 0.0)
         {
	 double num;
         int indx;
	 RANDU;
	 num = (double) seed / modulus;
         indx = (int) (num * dbllmt);
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
   printf("\t\t    RANDU Generator\n");
   /* perform a chi square test on the sampled decks */
   calcchi(tally,SIZE);
   return(0);
   } /* main */
