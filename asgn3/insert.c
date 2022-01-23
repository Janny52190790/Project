#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "stats.h"

void insertion_sort(Stats *stats, uint32_t *A, uint32_t n){
	uint32_t i, j, temp;
	for(i = 1; i < n; i++){
		j = i;
		temp = move(stats,A[i]);
		while((j > 0) && cmp(stats, temp, A[j - 1]) == -1){
			A[j] = move(stats, A[j - 1]);
            		j -= 1;
		}
		A[j] = move(stats, temp);
        	
    	}
}
