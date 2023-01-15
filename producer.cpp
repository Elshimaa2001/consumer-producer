#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include <iostream>
#include <string>
#include <random>
#include <queue>
#include <cstring>
#include <time.h>
#define buffersize 100
using namespace std;
int main (int argc, char* argv[]){
	struct input{
        char name[11];
        double price;
    };
    time_t t;
    struct sembuf sem_buf[1];
    struct biginput{
        input arr[buffersize];
        int index=0;
    };
    string ostring;
    struct timespec ts;
   // clock_gettime(CLOCK_REALTIME,&ts);
    ostring=argv[1];
    float mean=atof(argv[2]);
    float deviation=atof(argv[3]);
    int interval=atoi(argv[4]);
    int buff =atoi(argv[5]);
    default_random_engine generator;
    normal_distribution<double> distribution(mean,deviation);
    key_t key = ftok("shmfile",65);
    key_t key1 = ftok("shmfile1",66);
    key_t key2 = ftok("shmfile2",67);
    key_t key3 = ftok("shmfile3",68);
    int n,s,e;
    int shmid = shmget(key,sizeof(struct biginput),0666|IPC_CREAT);
    if (shmid == -1) {
      perror("Shared memory");
      return 1;
    }
    int semid = semget(key1, 1, 0666);

    int semid1 = semget(key2, 1, 0666);


    int semid2 = semget(key3, 1, 0666);

    struct biginput *array = (struct biginput *) shmat(shmid,0, 0);
    if(array==NULL){
    	shmctl(shmid,IPC_RMID,NULL);
    	semctl(semid,0,IPC_RMID);
    	semctl(semid1,0,IPC_RMID);
    	semctl(semid2,0,IPC_RMID);
    }
    sem_buf[0].sem_op=0;
    sem_buf[0].sem_flg=0;
    sem_buf[0].sem_num=0;
    while(true){
    clock_gettime(CLOCK_REALTIME,&ts);
    	time(&t);
       cout <<"["<<ctime(&t)<<ts.tv_nsec<<"]"<<" "<<ostring.c_str()<<":"<<"sleeping for "<< interval <<"ms"<< endl;
        sleep(interval);
        
        double number = distribution(generator);
        time(&t);
        cout <<"["<<ctime(&t)<<ts.tv_nsec<<"]"<<ostring.c_str()<<":"<<"generated new value"<< number<<endl;
        
        clock_gettime(CLOCK_REALTIME,&ts);
        time(&t);
        
        cout <<"["<<ctime(&t)<<ts.tv_nsec<<"]"<<" "<<ostring.c_str()<<":"<<"trying to get mutex on shared buffer"<< endl;
        /////////////wait(e)
        sem_buf[0].sem_op = -1;
        sem_buf[0].sem_flg = 0;
        sem_buf[0].sem_num = 0;
        semop(semid2, sem_buf, 1);
       // cout<<"e before wait"<<semctl(semid2, 0, GETVAL, buffersize )<<endl;
        ////////////wait(s)
        sem_buf[0].sem_op = -1;
        sem_buf[0].sem_flg = 0;
        sem_buf[0].sem_num = 0;
        semop(semid1, sem_buf, 1);
        //cout<<"s before wait"<<semctl(semid1, 0, GETVAL, buffersize )<<endl;
        /////////////////////////
        clock_gettime(CLOCK_REALTIME,&ts);
        time(&t);
        cout <<"["<<ctime(&t)<<ts.tv_nsec<<"]"<<" "<<ostring.c_str()<<":"<<" placing "  << number << " on shared buffer "<< endl;
         array->arr[array->index].price=number;
         strcpy(array->arr[array->index].name,ostring.c_str());
         //cout<<array->arr[array->index].price<<endl;
         //cout<<array->arr[array->index].name<<endl;
         array->index=((array->index)+1)%buffersize;

        ///////////////////signal(s)
        sem_buf[0].sem_op = 1;
        sem_buf[0].sem_flg = 0;
        sem_buf[0].sem_num = 0;
        semop(semid1, sem_buf, 1);
        // cout<<"s after signal"<<semctl(semid1, 0, GETVAL, buffersize )<<endl;
        ///////////////////signal
        sem_buf[0].sem_op = 1;
        sem_buf[0].sem_flg = 0;
        sem_buf[0].sem_num = 0;
        semop(semid, sem_buf, 1);
        //cout<<"n after signal"<<semctl(semid, 0, GETVAL, buffersize )<<endl;
    }
    shmdt(array);
   return 0;
}
