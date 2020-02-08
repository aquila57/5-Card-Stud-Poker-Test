/* analhand.c - Analyze hand of cards  Version 0.1.0 */
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

/* analyze a hand to see if there is a winning combination */
void analhand(char *deck, double *tally,
   int *suitkount, int *rankkount)
   {
   int i;
   int minrank;
   int maxrank;
   int rankdiff;
   /********************************************************/
   /* find rank spread  eg. 5-1=4                          */
   /* to look for a straight                               */
   /********************************************************/
   maxrank = 999999999;
   minrank = -999999999;
   for (i=0;i<13;i++)
      {
      if (rankkount[i] == 1)
         {
	 minrank = i;
	 break;
	 } /* found min rank */
      } /* for each rank */
   for (i=12;i>=0;i--)
      {
      if (rankkount[i] == 1)
         {
	 maxrank = i;
	 break;
	 } /* found max rank */
      } /* for each rank */
   rankdiff = maxrank - minrank;
   if (rankdiff == 4)
      {
      for (i=minrank;i<=maxrank;i++)
         {
         if (rankkount[i] != 1)
            {
	    rankdiff = 0;
	    break;
	    } /* not a straight */
         } /* for each card in a straight */
      } /* if possible straight */
   if (suitkount[0] == 5 || suitkount[1] == 5 || 
      suitkount[2] == 5 || suitkount[3] == 5)
      {
      if (rankkount[12] == 1 && rankkount[11] == 1 &&
         rankkount[10] == 1 && rankkount[9] == 1 &&
	 rankkount[8] == 1)
	 {
	 tally[ROYAL_FLUSH] += 1.0;
	 return;
	 } /* if royal flush */
      if (rankdiff == 4)
         {
	 tally[STRAIGHT_FLUSH] += 1.0;
	 return;
	 } /* straight flush */
      } /* if flush */
   for (i=0;i<13;i++)
      {
      if (rankkount[i] == 4)
         {
	 tally[FOUR_OF_KIND] += 1.0;
	 return;
	 } /* 4 of a kind */
      } /* for each rank */
   for (i=0;i<13;i++)
      {
      if (rankkount[i] == 3)
         {
         int j;
	 for (j=0;j<13;j++)
	    {
            if (rankkount[j] == 2)
	       {
	       tally[FULL_HOUSE] += 1.0;
	       return;
	       } /* full house */
	    } /* 2nd pass of the ranks */
	 } /* 3 of a kind, ck if full house */
      } /* for each rank */
   if (suitkount[0] == 5 || suitkount[1] == 5 || 
      suitkount[2] == 5 || suitkount[3] == 5)
      {
      tally[FLUSH] += 1.0;
      return;
      } /* if flush */
   for (i=0;i<13;i++)
      {
      if (rankkount[i] == 1 &&
         rankkount[i+1] == 1 && rankkount[i+2] == 1 &&
         rankkount[i+3] == 1 && rankkount[i+4] == 1)
	 {
         tally[STRAIGHT] += 1.0;
         return;
	 } /* straight found */
      } /* for each rank */
   /**************************************************************/
   /* aces low also count in a straight                          */
   /**************************************************************/
   if (rankkount[12] == 1 &&
      rankkount[0] == 1 && rankkount[1] == 1 &&
      rankkount[2] == 1 && rankkount[3] == 1)
      {
      tally[STRAIGHT] += 1.0;
      return;
      } /* straight found */
   for (i=0;i<13;i++)
      {
      if (rankkount[i] == 3)
         {
	 tally[THREE_OF_KIND] += 1.0;
	 return;
	 } /* 3 of a kind full house  */
      } /* for each rank */
   for (i=0;i<13;i++)
      {
      if (rankkount[i] == 2)
         {
         int j;
         for (j=i+1;j<13;j++)
            {
	    if (rankkount[j] == 2)
	       {
	       tally[TWO_PAIR] += 1.0;
	       return;
	       } /* if maxrank found */
	    } /* second pass for maxrank */
	 tally[ONE_PAIR] += 1.0;
	 return;
	 } /* if at least one pair */
      } /* for each card in hand */
   tally[HIGH_CARD] += 1.0;
   } /* analhand */
