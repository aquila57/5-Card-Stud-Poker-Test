/* kounthand.c - Count cards in a hand  Version 0.1.0 */
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

/* count the number of cards by suit and rank */
/* how many cards in the hand for each suit and each rank */
void kounthand(int kard, int *suitkount, int *rankkount)
   {
   int suit;
   int rank;
   suit = kard / 13;
   rank = kard % 13;
   suitkount[suit]++;
   rankkount[rank]++;
   } /* kounthand */
