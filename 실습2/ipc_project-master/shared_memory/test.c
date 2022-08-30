#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define KEY 1235

int main(){
    int shmid;
    int num = 5;
    int **pointer;
    void *memory_segment=NULL;

    if ((shmid = shmget(KEY, sizeof(int), IPC_CREAT|0666)) == -1) return -1;

    printf("shmid : %d\n", shmid);

    if ((memory_segment = shmat(shmid, NULL, 0)) == (void*)-1) return -1;

    pointer = (int**)memory_segment;
    (*pointer) = &num;
    printf("num : %d\n", **pointer);

    return 0;
}