#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int* generate_ref_arr(size_t sz, size_t page_max);
int lru(int* ref_arr, size_t ref_arr_sz, size_t frame_sz, size_t page_max);

void print_bit(int x){
    int bits[8];

    for(int i=0;i<8;i++){
        bits[i] = x%2;
        x = x/2;
    }

    for(int i=7;i>=0;i--)
        printf("%d", bits[i]);
}

// Driver code
//  Usage: ./program {ref_arr_size} {page_max} {frame_size}
int main(int argc, char** argv) {
    if (argc < 4) return -1;
    
    int ref_arr_sz = atoi(argv[1]);
    int page_max = atoi(argv[2]);
    int frame_sz = atoi(argv[3]);

    int* ref = generate_ref_arr(ref_arr_sz, page_max);
    int page_faults = lru(ref, ref_arr_sz, frame_sz, page_max);
    printf("\ntotal page faults : %d\n", page_faults);
    free(ref);

    return 0;
}

int _contains(int* arr, size_t sz, int target) {
    int i = 0;
    for (i=0; i<sz; i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}

int* generate_ref_arr(size_t sz, size_t page_max) {
    int* ref_arr = (int*) malloc(sizeof(int) * sz);
    // TODO :: Generate Random Refernece String
    srand(time(NULL));
    for(int i=0;i<sz;i++)
        ref_arr[i] = rand() % (page_max+1) ;
    
    // ref_arr[0] = 7;
    // ref_arr[1] = 0;
    // ref_arr[2] = 1;
    // ref_arr[3] = 2;
    // ref_arr[4] = 0;
    // ref_arr[5] = 3;
    // ref_arr[6] = 0;
    // ref_arr[7] = 4;
    // ref_arr[8] = 2;
    // ref_arr[9] = 3;
    // ref_arr[10] = 0;
    // ref_arr[11] = 3;
    // ref_arr[12] = 2;
    // ref_arr[13] = 1;
    // ref_arr[14] = 2;
    // ref_arr[15] = 0;
    // ref_arr[16] = 1;
    // ref_arr[17] = 7;
    // ref_arr[18] = 0;
    // ref_arr[19] = 1;

    for(int i=0;i<sz;i++)
        printf("%d ", ref_arr[i]);
    printf("\n\n");

    return ref_arr;
}

int lru(int* ref_arr, size_t ref_arr_sz, size_t frame_sz, size_t page_max) {
    int i, j;
    int page_faults = 0;
    
    // Initializing frames
    int* frames = (int*) malloc(sizeof(int) * frame_sz);
    for (i=0; i<frame_sz; i++) frames[i] = -1;

    // TODO
    int* ref_bit = (int*) malloc(sizeof(int) * page_max);     //reference bits 저장할 배열
    for (i=0; i<=page_max;i++) ref_bit[i] = 0b00000000;

    for(int i=0 ; i<ref_arr_sz; i++){
        int is_fault = _contains(frames, frame_sz, ref_arr[i]);
        printf("%d | ", ref_arr[i]);   
        
        for(int j=0 ; j<=page_max ;j++)
            ref_bit[j] = ref_bit[j] >> 1; //모든 reference bits 1칸씩 옮김.
        
        ref_bit[ref_arr[i]] = ref_bit[ref_arr[i]] | 0b10000000; //참조된 최상위 비트 1

        if(is_fault == -1){     //page_fault 발생한 경우 -> 현재 
            int min = 0b11111111; 
            int lru_idx = 0; 
            for(int j=0; j<frame_sz; j++){
                int page = frames[j];
                if(ref_bit[page] < min){
                    min = ref_bit[page];
                    lru_idx = j;
                }
            }
            frames[lru_idx] = ref_arr[i];
            page_faults++;
        }
        

        for(int i=0;i<frame_sz;i++){
            if(frames[i] == -1) printf(". ");
            else printf("%d ", frames[i]);
        }
        if(is_fault == -1) printf("(fault)");
        else printf("\t");
        // printf("\t page 0 : ");
        // print_bit(ref_bit[0]);
        printf("\n");

        
        // printf("\t\t\t");
        // for(int i=0; i<=page_max; i++)
        //     printf("%d ", i);
        // printf("\n");
        // printf("\t\t\t");
        // for(int i=0; i<=page_max; i++)
        //     printf("%d ", ref_bit[i]);
        
        // printf("\n");
        
    }

    return page_faults;
}

