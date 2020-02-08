/* analdeck.c - Analyze a deck of cards  Version 0.1.0 */
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

/* analyze all 10 hands in a deck of cards */
void analdeck(char *deck, double *tally)
   {
   int first;    /* first card in a hand */
   int lmt;      /* end of the card deck */
   int card;              /* card id 0-51 */
   int suitkount[8];      /* count by suit */
   int rankkount[16];     /* count by rank */
   first = 0;
   while (first < 50)
      {
      int j;
      for (j=0;j<8;j++) suitkount[j] = 0;
      for (j=0;j<16;j++) rankkount[j] = 0;
      lmt = first + 5;
      if (lmt > 52)
         {
	 fprintf(stderr,"lmt %d\n", lmt);
	 exit(1);
	 } /* limit out of range */
      /* count the cards by suit and rank */
      for (card=first;card<lmt;card++)
         {
	 int kard;
	 kard = deck[card];
	 kounthand(kard, suitkount, rankkount);
         } /* for the first 5 cards */
      // ckdeck(deck);
      /* analyze the hand for winning combinations */
      analhand(deck+first, tally, suitkount, rankkount);
      /* debugging */
      // for (j=0;j<=HIGH_CARD;j++) printf("%.0f ", tally[j]);
      // printf("\n");
      first += 5;       /* point to next hand in the deck */
      } /* for each of 10 hands in the deck */
   } /* analdeck */
