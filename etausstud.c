/* etausstud.c - 5 Card Stud Poker, etaus generator  Version 0.1.0 */
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

/* 5 card stud poker test, etaus generator */

#include "poker.h"

int main(void)
   {
   int i;             /* loop counter for random decks */
   int lmt;           /* random number generator limit */
   double tally[16];     /* array of counts by winning type */
   char *last;           /* last card in deck */
   char *p,*q;
   char cards[64];       /* sorted deck of cards */
   char deck[64];        /* shuffled deck of cards */
   etfmt *et;            /* structure for random number generator */
   et = (etfmt *) etausinit();    /* initialize RNG */
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
      lmt = 52;       /* random number generator limit */
      /* point to end of the sorted deck */
      last = (char *) cards + lmt - 1;
      p = (char *) deck;
      /* shuffle the sorted deck from 52 cards to 2 cards */
      while (lmt > 1)
         {
         int indx;        /* pointer to random card */
	 /* pick a random card from the sorted deck */
         indx = etausint(et,lmt--);
         q = (char *) cards + indx;
	 /* add the random card to the shuffled deck */
         *p++ = *q;
	 /* the sorted deck is one card smaller */
         *q = *last--;
         } /* for each card */
      *p++ = cards[0];    /* add the last card to the shuffled deck */
      *p = '\0';    /* make the shuffled deck a string */
      /* analyze the shuffled deck to see if how many */
      /* winning hands there are */
      analdeck(deck, tally);
      } /* for each deal */
   printf("\t\t5 Card Stud Poker Test\n");
   printf("\t\t    etaus Generator\n");
   /* perform a chi square test on the sampled decks */
   calcchi(tally,SIZE);
   /* end of program */
   /* free the heap */
   free(et->state);
   free(et);
   return(0);
   } /* main */
