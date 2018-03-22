#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

//sys
#include <fcntl.h>
//time measuring
#include <sys/time.h>
#include <sys/resource.h>


char* genRandomString( int size){
    char* charsCollection = "abcdefghijklmnopqrstuvwxyz";
    int charsCollectionLength = strlen(charsCollection);

    char* toRet = (char*) calloc(size, sizeof(char));
    for(int i = 0; i < size-1; i++){
        toRet[i]=charsCollection[rand()%charsCollectionLength];
    }
    toRet[size - 1] = '\n';

    return  toRet;
}

void generate(char* fileName, int recordSize, int recordsNum){
    FILE* file = fopen(fileName, "wb");

    for( int i = 0; i<recordsNum; i++){
        char* randString = genRandomString(recordSize);

        fwrite(randString, sizeof(char), recordSize, file);
        free(randString);
    }

    fclose(file);

}

void sortSys(char* file1Name, int recordSize, int recordsNum){
    fprintf(stderr, "Sys sort\n");

    int fileDesc;
    fileDesc = open(file1Name, O_RDWR | O_CREAT,
            S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);

    if(fileDesc == -1) {
        fprintf(stderr, "sortSys fileDesc err\n");
        exit(1);
    }

    char* bufor1 = (char*) calloc (recordSize, sizeof(char));
    char* bufor2 = (char*) calloc (recordSize, sizeof(char));


    int i;
    int j;

    for (i = 1; i < recordsNum; i++) {
        j = i - 1;

        pread(fileDesc, bufor1, recordSize, i * recordSize);

       while (j >= 0) {

           pread(fileDesc, bufor2, recordSize, j * recordSize);

           if((unsigned char)(bufor2[0])<=(unsigned char)(bufor1[0])){
               break;
           }

           pwrite(fileDesc, bufor2, recordSize, (j+1) * recordSize);

           j--;
       }

        pwrite(fileDesc, bufor1, recordSize, (j+1) * recordSize);

    }

    free(bufor1);
    free(bufor2);

    close(fileDesc);

}

void copySys(char* file1Name, char* file2Name,
             int recordsNum, int recordSize){

    int file1Desc = open(file1Name, O_RDONLY);
    int file2Desc = open(file2Name, O_WRONLY | O_CREAT,
            S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);

    char* buf = (char*)calloc(recordSize, sizeof(char));
    for(int i = 0; i< recordsNum; i++){
        read(file1Desc, buf, recordSize);
        write(file2Desc, buf, recordSize);
    }

    close(file1Desc);
    close(file2Desc);
    free(buf);

}

void copyLib(char* file1Name, char* file2Name,
             int recordsNum, int recordSize){

    FILE* file1 = fopen(file1Name, "r");
    FILE* file2 = fopen(file2Name, "w");

    char* buf = (char*)calloc(recordSize, sizeof(char));
    for(int i = 0; i< recordsNum; i++){
        fread(buf, sizeof(char), recordSize, file1);
        fwrite(buf, sizeof(char), recordSize,file2);
    }

    free(buf);


}

void sortLib(char* file1Name, int recordSize, int recordsNum){

    FILE* file1 = fopen(file1Name, "r+b");

    char* bufor1 = (char*) calloc (recordSize, sizeof(char));
    char* bufor2 = (char*) calloc (recordSize, sizeof(char));

    int i;
    int j;

    for (i = 1; i < recordsNum; i++) {
        j=i-1;

        fseek(file1, i * recordSize, SEEK_SET);
        fread(bufor1, sizeof(char), recordSize, file1); //1bufor tj i



        while (j >= 0) {

            fseek(file1, j * recordSize, SEEK_SET);
            fread(bufor2, sizeof(char), recordSize, file1);

            if((unsigned char)(bufor2[0])<=(unsigned char)(bufor1[0])){
                break;
            }

            fseek(file1, (j+1) * recordSize, SEEK_SET);
            fwrite(bufor2, sizeof(char), recordSize, file1);

            j--;
        }

        fseek(file1, (j+1)*recordSize, SEEK_SET);
        fwrite(bufor1, sizeof(char), recordSize, file1);

    }

    free(bufor1);
    free(bufor2);

    fclose(file1);

}



//zwraca czas w sekundach, najpierw czas poczatkowy
double calcTimeFrom2TimevalVal( struct timeval t0, struct timeval t1){

    double toRet = (t1.tv_sec-t0.tv_sec) + (t1.tv_usec-t0.tv_usec)/1000000.0;

    return toRet;
}


int main(int argc, char* args[]) {

    srand(time(NULL));

    char* optKind = args[1];
    char* file1Name = args[2];
    char* file2Name;

    int recordsNum, recordSize;
    char* modeType;

    if(!strcmp(optKind, "copy")) {
        file2Name = args[3];
        recordsNum = atoi(args[4]);
        recordSize = atoi(args[5]);
        modeType = args[6];
    } else if (!strcmp(optKind, "sort")){
        recordsNum = atoi(args[3]);
        recordSize = atoi(args[4]);  // w bajtach
        modeType = args[5];  // sys or lib

    }else if(!strcmp(optKind, "generate")){
        recordsNum = atoi(args[3]);
        recordSize = atoi(args[4]);
    } else {
        printf("Ni ma opcjuf\n");
        exit(1);
    }

    struct rusage tt0, tt1;
    struct timeval t0, t1;

    getrusage(RUSAGE_SELF, &tt0);
    gettimeofday(&t0, NULL);

    if(!strcmp(optKind, "generate")){
        generate(file1Name, recordSize, recordsNum);

    }else if(!strcmp(optKind, "copy")){
        if(!strcmp(modeType, "sys")){
            copySys(file1Name, file2Name, recordsNum, recordSize);
        }else{
            copyLib(file1Name, file2Name, recordsNum, recordSize);
        }

    }else if(!strcmp(optKind, "sort")){
        if(!strcmp(modeType, "sys")){
            sortSys(file1Name, recordSize, recordsNum);
        }else{
            sortLib(file1Name, recordSize, recordsNum);
        }

    }else{
        fprintf(stderr, "only 3 options: sort, copy and generate\n");
        return -1;
    }

    getrusage(RUSAGE_SELF, &tt1);
    gettimeofday(&t1, NULL);

    double realTime = calcTimeFrom2TimevalVal(t0, t1);
    double userTime = calcTimeFrom2TimevalVal(tt0.ru_utime, tt1.ru_utime);
    double systemTime = calcTimeFrom2TimevalVal(tt0.ru_stime, tt1.ru_stime);

    for(int i = 0; i< argc; i++){
        printf("%s ",args[i]);
    }
    printf("\n");
    printf("real time: %lf s, user time: %lf s, system time: %lf s\n",
           realTime, userTime, systemTime);
    printf("\n");


    return 0;
}