#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "stats.h"

uint32_t max_child(Stats *stats, uint32_t *A, uint32_t first, uint32_t last){
	uint32_t left = 2 * first;
    	uint32_t right = left + 1;
    	if(right <= last  && cmp(stats, A[right - 1], A[left - 1]) == 1){
        	return right;
    	}
        return left;
}

void fix_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last){
	int found = 0;
    	uint32_t mother = first;
    	uint32_t great = max_child(stats, A, mother, last);

    	while(mother <= floor(last / 2) && (!found)){
        	if(cmp(stats, A[mother - 1], A[great - 1]) == -1){
            		swap(stats, &A[mother - 1], &A[great - 1]);
            		mother = great;
            		great = max_child(stats, A, mother, last);
        	} else {
            		found = 1;
        	}	
    	}
}

void build_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last){
	uint32_t father;
    	for(father = floor(last / 2); father > first - 1; father = father - 1){
        	fix_heap(stats, A, father, last);
    	}
}

void heap_sort(Stats *stats, uint32_t *A, uint32_t n){
	int first = 1;
    	build_heap(stats, A, first , n);
    	int leaf;
    	for(leaf = n; leaf > first; leaf = leaf - 1){
        	swap(stats, &A[first - 1], &A[leaf - 1]);
		fix_heap(stats, A, first, (leaf - 1));
    	}
}

