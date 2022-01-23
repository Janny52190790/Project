#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "stats.h"

void comparator(Stats *stats, uint32_t *A, uint32_t x, uint32_t y){
	if(cmp(stats, A[x], A[y]) == 1){
        	swap(stats, &A[x], &A[y]);
    	}
}

void batcher_sort(Stats *stats, uint32_t *A, uint32_t n){
	if(n == 0){
        	return;
    	}
    	int t = log2(n) + 1;
    	int p = 1 << (t - 1);
    	while (p > 0){
        	int q = 1 << (t - 1);
        	uint32_t r = 0;
        	uint32_t d = p;
        	while (d > 0){
            		uint32_t i;
            		for(i = 0; i < (n - d); i++){
                		if((i & p) == r){
                    		comparator(stats, A, i, i + d);
                		}
            		}
            		d = q - p;
            		q >>= 1;
            		r = p;
        	}
        	p >>= 1;
    	}
}
