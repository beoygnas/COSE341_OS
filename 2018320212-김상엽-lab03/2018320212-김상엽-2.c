#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int* generate_ref_arr(size_t sz, size_t page_max);
int lru(int* ref_arr, size_t ref_arr_sz, size_t frame_sz);


// Driver code
//  Usage: ./program {ref_arr_size} {page_max} {frame_size}
int main(int argc, char** argv) {
    if (argc < 4) return -1;
    
    int ref_arr_sz = atoi(argv[1]);
    int page_max = atoi(argv[2]);
    int frame_sz = atoi(argv[3]);

    int* ref = generate_ref_arr(ref_arr_sz, page_max);
    int page_faults = lru(ref, ref_arr_sz, frame_sz);
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
        ref_arr[i] = rand() % (page_max + 1);
 
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

int lru(int* ref_arr, size_t ref_arr_sz, size_t frame_sz) {
    int i, j;
    int page_faults = 0;
    
    // Initializing frames
    int* frames = (int*) malloc(sizeof(int) * frame_sz);
    for (i=0; i<frame_sz; i++) frames[i] = -1;

    // TODO
    int* ref_bit = (int*) malloc(sizeof(int) * ref_arr_sz); //reference bit를 저장할 circular queue
    for (i=0; i<frame_sz;i++) ref_bit[i] = 0; 
    int idx = 0; //pointer

    for(int i=0 ; i<ref_arr_sz; i++){
        int is_fault = _contains(frames, frame_sz, ref_arr[i]);
        
        if(is_fault == -1){ //pagefault 시
            while(ref_bit[idx] != 0){   //reference bit 0인 page 찾기
                ref_bit[idx] = 0;       // 1 -> 0
                idx = (idx+1) % frame_sz;   // circular
            }
            frames[idx] = ref_arr[i];   //page 바꾸기
            ref_bit[idx] = 1;
            idx = (idx+1) % frame_sz;
            page_faults++;
        }
        else{ //참조 된 경우.
            ref_bit[is_fault] = 1;
        }

        printf("%d | ", ref_arr[i]);   

        for(int j=0;j<frame_sz;j++){
            if(frames[j] == -1) printf(". ");
            else printf("%d ", frames[j]);
        }

        if(is_fault == -1) printf("(fault)");
        // printf("\n\t\t\t pointer : %d\t", idx);
        //     for(int j=0;j<frame_sz;j++)
        //         printf("%d ", ref_bit[j]);
        printf("\n");
    }

    return page_faults;
}

