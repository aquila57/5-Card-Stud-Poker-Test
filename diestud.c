/* diestud.c - 5 Card Stud, dieharder generators  Version 0.1.0 */
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

void putstx(char *pgm)
   {
   fprintf(stderr,"5 Card Stud Poker Test, dieharder "
      "random number generators\n");
   fprintf(stderr,"Usage: %s generator\n", pgm);
   fprintf(stderr,"Where generator is the dieharder ");
   fprintf(stderr,"random number generator\n");
   fprintf(stderr,"Example: %s 053\n", pgm);
   fprintf(stderr,"053 is the id for the taus2 generator\n");
   fprintf(stderr,"To see a list of dieharder generators, type:\n");
   fprintf(stderr,"dieharder -g -l\n");
   exit(1);
   } /* putstx */

int main(int argc, char **argv)
   {
   int i;                /* loop counter for random decks */
   int lmt;              /* random number generator limit */
   int decks;            /* number of card decks */
   double dbllmt;        /* random number generator limit */
   double tally[16];     /* array of counts by winning type */
   char *last;           /* last card in deck */
   char *p,*q;
   char cards[64];       /* sorted deck of cards */
   char deck[64];        /* shuffled deck of cards */
   xxfmt *xx;
   /*************************************************************/
   /* Allocate memory for the global structure.                 */
   /* This is a re-entrant program.                             */
   /*************************************************************/
   xx = (xxfmt *) malloc(sizeof(xxfmt));
   if (xx == NULL)
      {
      fprintf(stderr,"main: out of memory "
         "allocating xx\n");
      exit(1);
      } /* out of memory */
   /*************************************************************/
   /* initialize global data                                    */
   /*************************************************************/
   xx->dieharder_rngname[0] = '\0';
   xx->rngname = (char *) NULL;
   xx->generator = -1;
   /*************************************************************/
   /* obtain dieharder generator number parameter               */
   /*************************************************************/
   if (argc != 2) putstx(*argv);
   xx->generator = atoi(*(argv+1));
   if (xx->generator < 0 || xx->generator > 405)
      {
      fprintf(stderr,"main: invalid random "
         "number generator %s\n", *(argv+1));
      putstx(*argv);
      } /* invalid generator */
   /*************************************************************/
   /* initialize numeric fields                                 */
   /*************************************************************/
   bld_maxint(xx);  /* build maxint table for dieharder RNGs */
   bld_rngtbl(xx);  /* build name table for dieharder RNGs */
   if (xx->maxint_tbl[xx->generator] == 0.0)
      {
      fprintf(stderr,"main: invalid random "
         "number generator %s\n", *(argv+1));
      putstx(*argv);
      } /* invalid generator */
   xx->modulus = xx->maxint_tbl[xx->generator];
   xx->maxint  = (unsigned int) xx->modulus;
   xx->smpls      = SIZE;
   xx->dblsmpls   = (double) xx->smpls;
   /***************************************************/
   /* Initialize the dieharder generator              */
   /* Bypass the dieharder prefix                     */
   /***************************************************/
   diepfx(xx);
   /* initialize counts by type of winning hand */
   for (i=0;i<16;i++) tally[i] = 0.0;
   /* dieharder has a limit of 1 million samples */
   /* there are 10 poker hands per card deck */
   decks = SIZE / 52;
   i = decks;
   while (i--)       /* for each deck of cards shuffled */
      {
      int j;
      lmt = 52;                  /* random number generator limit */
      dbllmt = (double) lmt;     /* random number generator limit */
      /* created a sorted deck of cards */
      for (j=0;j<lmt;j++) cards[j] = (char) j;
      /* shuffle the sorted deck of cards */
      /* for every card shuffled, the sorted deck gets smaller */
      /* point to end of the sorted deck */
      last = (char *) cards + lmt - 1;
      p = (char *) deck;
      /* shuffle the sorted deck from 52 cards to 2 cards */
      while (lmt > 1)
         {
	 double num;
         int indx;        /* pointer to random card */
	 /* pick a random card from the sorted deck */
	 num  = getdie(xx);
	 if (xx->eofsw)
	    {
	    fprintf(stderr,"main: end of file "
	       "reading dieharder input\n");
	    exit(1);
	    } /* end of file */
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
   printf("\t      dieharder Generator: %s\n",
      xx->dieharder_rngname);
   /* perform a chi square test on the sampled decks */
   calcchi(tally,decks);
   free(xx);
   /* end of program */
   return(0);
   } /* main */
