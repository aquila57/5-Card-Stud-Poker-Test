/* poker.h - 5 Card Stud Poker Test header file Version 0.1.0 */
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

/*********************************************************************/
/* This is a 64-bit version of eegl.h.                               */
/* It is based on Version 1.1.0 of eegl.h                            */
/* at http://www.github.com/aquila62/eegl                            */
/*********************************************************************/

/********************************************************/
/* The LFSR in this generator comes from the following  */
/* http://courses.cse.tamu.edu/walker/csce680/          */
/* lfsr_table.pdf                                       */
/* 64 bit LFSR is 64,63,61,60 with low order bit equal  */
/* to 64                                                */
/********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/times.h>
#include <math.h>
#include <errno.h>
#include <gsl/gsl_cdf.h>
#include <gsl/gsl_rng.h>
#include "eegl.h"
#include "etaus.h"

/* SIZE is the number of card decks to sample */

#define SIZE 1000000

#define CLUB 0
#define DIAMOND 1
#define HEART 2
#define SPADE 3

#define ACE 12
#define KING 11
#define QUEEN 10
#define JACK 9
#define TEN 8

#define ROYAL_FLUSH 0
#define STRAIGHT_FLUSH 1
#define FOUR_OF_KIND 2
#define FULL_HOUSE 3
#define FLUSH 4
#define STRAIGHT 5
#define THREE_OF_KIND 6
#define TWO_PAIR 7
#define ONE_PAIR 8
#define HIGH_CARD 9

#define EOFDIE (-999999999.0)

typedef struct xxstruct {
   char *rngname;
   char dieharder_rngname[128];
   char rngtbl[1000][64];
   int generator;
   int eofsw;
   unsigned int maxint;
   int smpls;
   double dblsmpls;
   double count;
   double modulus;
   double maxint_tbl[2048];
   } xxfmt;

/* debugging routine to validate that there are no */
/* duplicate or missing cards in a deck */
void ckdeck(char *deck);

/* display the shuffled deck with suit and rank */
void shwdeck(char *deck, int *suitkount, int *rankkount);

/* count the number of cards by suit and rank */
/* how many cards in the hand for each suit and each rank */
void kounthand(int kard, int *suitkount, int *rankkount);

/* analyze a hand to see if there is a winning combination */
void analhand(char *deck, double *tally,
   int *suitkount, int *rankkount);

/* analyze all 10 hands in a deck of cards */
void analdeck(char *deck, double *tally);

/* perform chi square test by count of winning hands */
void calcchi(double *tally, int decks);

void bld_maxint(xxfmt *xx);
void bld_rngtbl(xxfmt *xx);
void diepfx(xxfmt *xx);
double getdie(xxfmt *xx);
