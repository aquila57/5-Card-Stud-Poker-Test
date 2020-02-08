#!/bin/bash
make -f pokerlib.mak clean
make -f 5cdstud.mak clean
make -f etausstud.mak clean
make -f fibostud.mak clean
make -f lfsrstud.mak clean
make -f sinestud.mak clean
make -f rustud.mak clean
make -f gslstud.mak clean
make -f diestud.mak clean
rm -f alldie.out allgsl.out
