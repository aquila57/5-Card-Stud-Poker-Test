/* lfsrstud.c - 5 Card Stud Poker, LFSR generator Version 0.1.0 */
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

#define MYLFSROUT (out = (((lfsr >> 4) \
   ^ (lfsr >> 3) \
   ^ (lfsr >> 1) \
   ^ (lfsr >> 0)) & 1))

#define MYLFSRLOWBIT (lowbit = major & 1)

#define MYLFSRROLL (major = lfsr0 = \
(major >> 1) | (out << 31))

#define MYLFSRCARRY (minor = lfsr = \
(minor >> 1) | (lowbit << 31))

#define MYLFSR (MYLFSROUT,MYLFSRLOWBIT,MYLFSRROLL,MYLFSRCARRY)

int main(void)
   {
   int i;                /* loop counter for random decks */
   unsigned int lfsr0;
   unsigned int lfsr;
   unsigned int major;
   unsigned int minor;
   int out;;
   int lowbit;;
   int lmt;              /* random number generator limit */
   double dbllmt;        /* random number generator limit */
   double modulus;       /* 2^32 */
   double tally[16];     /* array of counts by winning type */
   char *last;           /* last card in deck */
   char *p,*q;
   char cards[64];       /* sorted deck of cards */
   char deck[64];        /* shuffled deck of cards */
   eefmt *ee;            /* structure for random number generator */
   ee = (eefmt *) eeglinit();    /* initialize RNG */
   lfsr0 = major = eegl(ee);
   lfsr  = minor = eegl(ee);
   out = lowbit = 0;
   free(ee->state);
   free(ee);
   modulus = 65536.0 * 65536.0;      /* 2^32 */
   /* initialize counts by type of winning hand */
   for (i=0;i<16;i++) tally[i] = 0.0;
   i = SIZE;
   while (i--)       /* for each deck of cards shuffled */
      {
      int j;
      /* created a sorted deck of cards */
      for (j=0;j<52;j++) cards[j] = (char) j;
      /* shuffle the sorted deck of cards */
      /* for every card shuffled, the sorted deck gets smaller */
      lmt = 52;                /* random number generator limit */
      dbllmt = (double) lmt;   /* random number generator limit */
      /* point to end of the sorted deck */
      last = (char *) cards + lmt - 1;
      p = (char *) deck;
      /* shuffle the sorted deck from 52 cards to 2 cards */
      while (lmt > 1)
         {
	 double num;
         int indx;        /* pointer to random card */
	 /* pick a random card from the sorted deck */
	 /* calculate the next generation of LFSR */
	 MYLFSR;
	 num = (double) lfsr / modulus;
	 indx = (int) floor(num * dbllmt);
         q = (char *) cards + indx;
	 /* add the random card to the shuffled deck */
         *p++ = *q;
	 /* the sorted deck is one card smaller */
         *q = *last--;
	 lmt--;
	 dbllmt -= 1.0;
         } /* for each card */
      *p++ = cards[0];    /* add the last card to the shuffled deck */
      *p = '\0';    /* make the shuffled deck a string */
      /* analyze the shuffled deck to see if how many */
      /* winning hands there are */
      analdeck(deck, tally);
      } /* for each deal */
   printf("\t\t5 Card Stud Poker Test\n");
   printf("\t\t    LFSR Generator\n");
   /* perform a chi square test on the sampled decks */
   calcchi(tally,SIZE);
   /* end of program */
   return(0);
   } /* main */
