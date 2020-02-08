#include "poker.h"

/* This program performs a chi square test on 1 million */
/* random card decks based on how many hands contain any */
/* of 10 types of winning hands in 5 card stud poker */

/* perform chi square test by count of winning hands */
void calcchi(double *tally, int decks)
   {
   int indx;
   double *p,*q,*r;
   double prob[16];
   double totodds;
   double totact;
   double dblsz;
   double diff;
   double diffsq;
   double chisq;
   double df;
   double minchi;
   double maxchi;
   double pvalue;
   printf("\n");
   printf("Hand               Actual         "
      "Expected       Difference\n");
   totodds = 2598960.0;      /* total number of combinations */
   p = (double *) prob;
   /* probabilities by winning combination */
   /* total of these probabilities == 1.0  */
   *p++ = 4.0 / totodds;             /* royal flush */
   *p++ = 36.0 / totodds;            /* straight flush */
   *p++ = 624.0 / totodds;           /* four of kind */
   *p++ = 3744.0 / totodds;          /* full house */
   *p++ = 5108.0 / totodds;          /* flush */
   *p++ = 10200.0 / totodds;         /* straight */
   *p++ = 54912.0 / totodds;         /* three of kind */
   *p++ = 123552.0 / totodds;        /* two pair */
   *p++ = 1098240.0 / totodds;       /* one pair */
   *p++ = 1302540.0 / totodds;       /* high card */
   *p = -999999999.0;
   dblsz = (double) decks;
   indx = 0;          /* initialize degrees of freedom */
   totact = chisq = 0.0;
   p = (double *) tally;
   q = (double *) tally + HIGH_CARD;
   r = (double *) prob;
   while (p <= q)
      {
      double expected;
      totact += *p;         /* total number of actual samples */
      /* there are 10 hands in a deck of cards */
      /* expected = probability x total hands sampled */
      expected = *r * dblsz * 10.0;
      diff = *p - expected;
      diffsq = diff * diff;
      chisq += (diffsq / expected);
      switch (indx)
         {
	 case 0:
	    printf("Royal Flush    ");
	    break;
	 case 1:
	    printf("Straight Flush ");
	    break;
	 case 2:
	    printf("4 Of A Kind    ");
	    break;
	 case 3:
	    printf("Full House     ");
	    break;
	 case 4:
	    printf("Flush          ");
	    break;
	 case 5:
	    printf("Straight       ");
	    break;
	 case 6:
	    printf("3 Of A Kind    ");
	    break;
	 case 7:
	    printf("2 Pairs        ");
	    break;
	 case 8:
	    printf("1 Pair         ");
	    break;
	 case 9:
	    printf("High Card      ");
	    break;
	 default:
	    fprintf(stderr,"Invalid indx %d\n", indx);
	    exit(1);
	 } /* switch indx */
      printf("%10.0f %17.5f %15.5f\n",
         *p, expected, diff);
      indx++;       /* one more degree of freedom */
      r++;
      p++;
      } /* for each tally */
   printf("\n");
   printf("Total samples %d     decks of cards\n", decks);
   printf("Total actual  %.0f  @10 hands "
      "per card deck\n", totact);
   df = (double) (indx - 1);
   minchi = gsl_cdf_chisq_Pinv(0.025,df);
   maxchi = gsl_cdf_chisq_Pinv(0.975,df);
   pvalue = gsl_cdf_chisq_P(chisq,df);
   printf("Chi square %f  P-value %18.15f\n", chisq, pvalue);
   printf("\n");
   printf("At 95%c probability and %.0f degrees of freedom,\n"
      "Chi square ranges from %f to %f\n",
      '%', df, minchi, maxchi);
   } /* calcchi */
