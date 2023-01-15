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
#include <iomanip>
#define buffersize 100
using namespace std;
  
int main (int argc, char* argv[]){
    char name1[11];
    double avrgprice=0;
    int buff=atoi(argv[1]);
   /////////////print elements 
    double arr_crudeoil[5]={0,0,0,0,0}, 
   arr_gold[5]={0,0,0,0,0}, 
   arr_silver[5]={0,0,0,0,0}, 
   arr_naturalgas[5]={0,0,0,0,0}, 
   arr_aluminium[5]={0,0,0,0,0}, 
   arr_copper[5]={0,0,0,0,0}, 
   arr_nickel[5]={0,0,0,0,0}, 
   arr_zinc[5]={0,0,0,0,0}, 
   arr_lead[5]={0,0,0,0,0}, 
   arr_menthaoil[5]={0,0,0,0,0}, 
   arr_cotton[5]={0,0,0,0,0};
   
    int i_crudeoil=0,i_gold=0,i_silver=0,i_naturalgas=0,i_aluminium=0,i_copper=0,i_nickel=0,i_zinc=0,i_lead=0,i_menthaoil=0,i_cotton=0;
    double avg_crudeoil=0,avg_gold=0,avg_silver=0,avg_naturalgas=0,avg_aluminium=0,avg_copper=0,avg_nickel=0,avg_zinc=0,avg_lead=0,avg_menthaoil=0,avg_cotton=0;
    double prev_avg_crudeoil=0,prev_avg_gold=0,prev_avg_silver=0,prev_avg_naturalgas=0,prev_avg_aluminium=0,prev_avg_copper=0,prev_avg_nickel=0,prev_avg_zinc=0,prev_avg_lead=0,prev_avg_menthaoil=0,prev_avg_cotton=0;
    double price_crudeoil=0,price_gold=0,price_silver=0,price_naturalgas=0, price_aluminium=0, price_copper=0,price_nickel=0,price_zinc=0,price_lead=0,price_menthaoil=0,price_cotton=0;
    char cname[11]="gold";
    double cprice=12;
    
   ///////////////end print elements
   
    struct input{
        char name[11];
        double price;
    };
    union semun{
        int val;
    };
    struct sembuf sem_buf[1];
    union semun arg;
    struct biginput{
        input arr[buffersize ];
        int index1=0;
    };
    int q=0;
    key_t key = ftok("shmfile",65);
    key_t key1 = ftok("shmfile1",66);
    key_t key2 = ftok("shmfile2",67);
    key_t key3 = ftok("shmfile3",68);
    int n,e,s;
    int shmid = shmget(key,sizeof(struct biginput),0666|IPC_CREAT);
    if (shmid == -1) {
      perror("Shared memory");
      return 1;
    }
    int semid = semget(key1, 1,IPC_CREAT| 0666);
     arg.val=0;
    n =semctl(semid, 0, SETVAL,arg);     
     if (n==-1){
      		shmctl(shmid,IPC_RMID,NULL);
       		semctl(semid,0,IPC_RMID);
    }		
    int semid1 = semget(key2, 1, IPC_CREAT | 0666);
   arg.val=1;
    s = semctl(semid1, 0, SETVAL, arg);
     if (s==-1){
      	shmctl(shmid,IPC_RMID,NULL);
    	semctl(semid1,0,IPC_RMID);
      		}
    int semid2 = semget(key3, 1, IPC_CREAT | 0666);
    arg.val=buffersize;
    	  e = semctl(semid2, 0, SETVAL, arg );
    	  if (e==-1){
    		 shmctl(shmid,IPC_RMID,NULL);
    		 semctl(semid2,0,IPC_RMID);
   }
    struct biginput *array = (struct biginput *) shmat(shmid,0, 0);
    /*if(array==NULL){
    	shmctl(shmid,IPC_RMID,NULL);
    	semctl(semid,0,IPC_RMID);
    	semctl(semid1,0,IPC_RMID);
    	semctl(semid2,0,IPC_RMID);
    }*/
    sem_buf[0].sem_op = 0;
        sem_buf[0].sem_flg = 0;
        sem_buf[0].sem_num = 0;
    while(true)
    { ///////////////////wait(n)
        std::cout << std::fixed;
  	std::cout << std::setprecision(2);
        sem_buf[0].sem_op = -1;
        sem_buf[0].sem_flg = 0;
        sem_buf[0].sem_num = 0;
        semop(semid, sem_buf, 1);
        //cout<<"n before wait"<<semctl(semid, 0, GETVAL, buffersize )<<endl;
     ////////////wait(s)
        sem_buf[0].sem_op = -1;
        sem_buf[0].sem_flg = 0;
        sem_buf[0].sem_num = 0;
        semop(semid1, sem_buf, 1);
        //cout<<"s before wait"<<semctl(semid1, 0, GETVAL, buffersize )<<endl;
////////////////////take/
////////////////////
	   // cout<<array->index1<<endl;
	   //cout<<q<<endl;
            //avrgprice=array->arr[array->index1].price;
             avrgprice=array->arr[q].price;
             cprice=array->arr[q].price;
             if (cprice<0){cprice=cprice*-1;}
            //cout<<avrgprice<<endl;
            //strcpy(name1,array->arr[array->index1].name);
            strcpy(name1,array->arr[q].name);
            strcpy(cname,array->arr[q].name);
            //cout<<name1<<endl;  
            //gold
    if (strcmp(cname,"gold")==0){
    price_gold=cprice;
    prev_avg_gold=avg_gold;
    arr_gold[i_gold]=cprice;
    i_gold++;
    if (i_gold==5){
        i_gold=0;
    }
    for (int ii=0;ii<5;ii++){
        avg_gold=avg_gold+arr_gold[ii];
    }
    avg_gold=avg_gold/5;
   }
    
    //crudeoil
   if (strcmp(cname,"crudeoil")==0){
   price_crudeoil=cprice;
    prev_avg_crudeoil=avg_crudeoil;
    arr_crudeoil[i_crudeoil]=cprice;
    i_crudeoil++;
    if (i_crudeoil==5){
        i_crudeoil=0;
    }
    for (int ii=0;ii<5;ii++){
        avg_crudeoil=avg_crudeoil+arr_crudeoil[ii];
    }
    avg_crudeoil=avg_crudeoil/5;
   }

    // silver
   if (strcmp(cname,"silver")==0){
   price_silver=cprice;
    prev_avg_silver=avg_silver;
   arr_silver[i_silver]=cprice;
    i_silver++;
    if (i_silver==5){
        i_silver=0;
    }
    for (int ii=0;ii<5;ii++){
        avg_silver=avg_silver+arr_silver[ii];
    }
    avg_silver=avg_silver/5;
   }

   //naturalgas
   if (strcmp(cname,"naturalgas")==0){
   price_naturalgas=cprice;
    prev_avg_naturalgas=avg_naturalgas;
  arr_naturalgas[i_naturalgas]=cprice;
    i_naturalgas++;
    if (i_naturalgas==5){
        i_naturalgas=0;
    }
    for (int ii=0;ii<5;ii++){
        avg_naturalgas=avg_naturalgas+arr_naturalgas[ii];
    }
    avg_naturalgas=avg_naturalgas/5;
   }

   //aluminium
   if (strcmp(cname,"aluminium")==0){
   price_aluminium=cprice;
    prev_avg_aluminium=avg_aluminium;
   arr_aluminium[i_aluminium]=cprice;
    i_aluminium++;
    if (i_aluminium==5){
        i_aluminium=0;
    }
    for (int ii=0;ii<5;ii++){
        avg_aluminium=avg_aluminium+arr_aluminium[ii];
    }
    avg_aluminium=avg_aluminium/5;
   }

   //copper
   if (strcmp(cname,"copper")==0){
   price_copper=cprice;
    prev_avg_copper=avg_copper;
    arr_copper[i_copper]=cprice;
    i_copper++;
    if (i_copper==5){
        i_copper=0;
    }
    for (int ii=0;ii<5;ii++){
        avg_copper=avg_copper+arr_copper[ii];
    }
    avg_copper=avg_copper/5;
   }

    //nickel
   if (strcmp(cname,"nickel")==0){
   price_nickel=cprice;
    prev_avg_nickel=avg_nickel;
    arr_nickel[i_nickel]=cprice;
    i_nickel++;
    if (i_nickel==5){
        i_nickel=0;
    }
    for (int ii=0;ii<5;ii++){
        avg_nickel=avg_nickel+arr_nickel[ii];
    }
    avg_nickel=avg_nickel/5;
   }

    //lead
   if (strcmp(cname,"lead")==0){
   price_lead=cprice;
    prev_avg_lead=avg_lead;
    arr_lead[i_lead]=cprice;
    i_lead++;
    if (i_lead==5){
        i_lead=0;
    }
    for (int ii=0;ii<5;ii++){
        avg_lead=avg_lead+arr_lead[ii];
    }
    avg_lead=avg_lead/5;
   }

    //zinc
   if (strcmp(cname,"zinc")==0){
   price_zinc=cprice;
    prev_avg_zinc=avg_zinc;
    arr_zinc[i_zinc]=cprice;
    i_zinc++;
    if (i_zinc==5){
        i_zinc=0;
    }
    for (int ii=0;ii<5;ii++){
        avg_zinc=avg_zinc+arr_zinc[ii];
    }
    avg_zinc=avg_zinc/5;
   }

    //menthaoil
   if (strcmp(cname,"menthaoil")==0){
   price_menthaoil=cprice;
    prev_avg_menthaoil=avg_menthaoil;
    arr_menthaoil[i_menthaoil]=cprice;
    i_menthaoil++;
    if (i_menthaoil==5){
        i_menthaoil=0;
    }
    for (int ii=0;ii<5;ii++){
        avg_menthaoil=avg_menthaoil+arr_menthaoil[ii];
    }
    avg_menthaoil=avg_menthaoil/5;
   }

   //cotton
   if (strcmp(cname,"cotton")==0){
   price_cotton=cprice;
    prev_avg_cotton=avg_cotton;
    arr_cotton[i_cotton]=cprice;
    i_cotton++;
    if (i_cotton==5){
        i_cotton=0;
    }
    for (int ii=0;ii<5;ii++){
        avg_cotton=avg_cotton+arr_cotton[ii];
    }
    avg_cotton=avg_cotton/5;
   } 
             q=(q+1)%buffersize;
         // array->index1=((array->index1)+1)%buffersize;
 ///////////////////signal(s)
        sem_buf[0].sem_op = 1;
        sem_buf[0].sem_flg = 0;
        sem_buf[0].sem_num = 0;
        semop(semid1, sem_buf, 1);
       //cout<<"s after signal"<<semctl(semid1, 0, GETVAL, buffersize )<<endl;
         /////////////signal(e)
        sem_buf[0].sem_op = 1;
        sem_buf[0].sem_flg = 0;
        sem_buf[0].sem_num = 0;
        semop(semid2, sem_buf, 1);
        //cout<<"e after signal"<<semctl(semid2, 0, GETVAL, buffersize )<<endl;
////////////////////////consume---print
	printf("\e[1;1H\e[2J");
	cout << "+----------------------------------------------------+\n";
	cout << "| Currency\t" <<"| price\t\t" << "| Avg price          |\n"; 
	cout << "+----------------------------------------------------+\n";
	
	std::cout << "| CRUDEOIL\t" ;
    if (prev_avg_crudeoil<avg_crudeoil){
    cout<<"\033[;32m" << price_crudeoil <<"↑\033[0m" <<"\t\t" <<  "\033[;32m" << avg_crudeoil <<"↑\033[0m\n";} 
    else if (prev_avg_crudeoil>avg_crudeoil){cout<<"\033[;31m" << price_crudeoil <<"↓\033[0m" <<"\t\t" <<  "\033[;31m" << avg_crudeoil <<"↓\033[0m\n";}
    else cout << "\033[;36m" << price_crudeoil <<"\033[0m" <<"\t\t" <<  "\033[;36m" << avg_crudeoil <<"\033[0m""";
    printf("\033[4;54H");
    cout << "|\n";
   

   std:: cout << "| GOLD\t\t";
   if (prev_avg_gold<avg_gold){ cout<<"\033[;32m" << price_gold <<"↑\033[0m" <<"\t\t" <<  "\033[;32m" << avg_gold <<"↑\033[0m\n";} 
    else if (prev_avg_gold>avg_gold) {cout<<"\033[;31m" << price_gold <<"↓\033[0m" <<"\t\t" <<  "\033[;31m" << avg_gold<<"↓\033[0m\n";}
    else cout << "\033[;36m" << price_gold <<"\033[0m" <<"\t\t" <<  "\033[;36m" << avg_gold <<"\033[0m""\n";
	printf("\033[5;54H");
    cout << "|\n";
    
   std:: cout << "| SILVER\t";
    if (prev_avg_silver<avg_silver){cout<<"\033[;32m" << price_silver <<"↑\033[0m" <<"\t\t" <<  "\033[;32m" << avg_silver <<"↑\033[0m\n";} 
    else if (prev_avg_silver>avg_silver)  {cout<<"\033[;31m" << price_silver <<"↓\033[0m" <<"\t\t" <<  "\033[;31m" << avg_silver <<"↓\033[0m\n";}
   else cout << "\033[;36m" << price_silver <<"\033[0m" <<"\t\t" <<  "\033[;36m" << avg_silver <<"\033[0m""\n";
   printf("\033[6;54H");
    cout << "|\n";

   std:: cout << "| COTTON\t";
    if (prev_avg_cotton<avg_cotton){cout<<"\033[;32m" << price_cotton <<"↑\033[0m" <<"\t\t" <<  "\033[;32m" << avg_cotton <<"↑\033[0m\n";} 
    else if (prev_avg_cotton>avg_cotton){cout<<"\033[;31m" << price_cotton <<"↓\033[0m" <<"\t\t" <<  "\033[;31m" << avg_cotton <<"↓\033[0m\n";}
    else cout << "\033[;36m" << price_cotton <<"\033[0m" <<"\t\t" <<  "\033[;36m" << avg_cotton <<"\033[0m""\n";
    printf("\033[7;54H");
    cout << "|\n";
  
   std:: cout << "| MENTHAOIL\t";
    if (prev_avg_menthaoil<avg_menthaoil){cout<<"\033[;32m" << price_menthaoil <<"↑\033[0m" <<"\t\t" <<  "\033[;32m" << avg_menthaoil <<"↑\033[0m\n";} 
    else if (prev_avg_menthaoil>avg_menthaoil){cout<<"\033[;31m" << price_menthaoil <<"↓\033[0m" <<"\t\t" <<  "\033[;31m" << avg_menthaoil <<"↓\033[0m\n";}
    else cout << "\033[;36m" << price_menthaoil <<"\033[0m" <<"\t\t" <<  "\033[;36m" << avg_menthaoil <<"\033[0m""\n";
    printf("\033[8;54H");
    cout << "|\n";
  
   std:: cout << "| LEAD\t\t";
    if (prev_avg_lead<avg_lead){cout<<"\033[;32m" << price_lead <<"↑\033[0m" <<"\t\t" <<  "\033[;32m" << avg_lead <<"↑\033[0m\n";} 
    else if (prev_avg_lead>avg_lead){cout<<"\033[;31m" << price_lead <<"↓\033[0m" <<"\t\t" <<  "\033[;31m" << avg_lead <<"↓\033[0m\n";}
    else cout << "\033[;36m" << price_lead <<"\033[0m" <<"\t\t" <<  "\033[;36m" << avg_lead <<"\033[0m""\n";
    printf("\033[9;54H");
    cout << "|\n";
   
   std:: cout << "| ZINC\t\t";
    if (prev_avg_zinc<avg_zinc){cout<<"\033[;32m" << price_zinc <<"↑\033[0m" <<"\t\t" <<  "\033[;32m" << avg_zinc <<"↑\033[0m\n";} 
    else if (prev_avg_zinc>avg_zinc){cout<<"\033[;31m" << price_zinc <<"↓\033[0m" <<"\t\t" <<  "\033[;31m" << avg_zinc <<"↓\033[0m\n";}
    else cout << "\033[;36m" << price_zinc <<"\033[0m" <<"\t\t" <<  "\033[;36m" << avg_zinc <<"\033[0m""\n";
    printf("\033[10;54H");
    cout << "|\n";
   
   std:: cout << "| NICKEL\t" ;
    if (prev_avg_nickel<avg_nickel){cout<<"\033[;32m" << price_nickel <<"↑\033[0m" <<"\t\t" <<  "\033[;32m" << avg_nickel <<"↑\033[0m\n";} 
    else if (prev_avg_nickel>avg_nickel){cout<<"\033[;31m" << price_nickel <<"↓\033[0m" <<"\t\t" <<  "\033[;31m" << avg_nickel <<"↓\033[0m\n";}
    else cout << "\033[;36m" << price_nickel <<"\033[0m" <<"\t\t" <<  "\033[;36m" << avg_nickel <<"\033[0m""\n";
    printf("\033[11;54H");
    cout << "|\n";
  
   std:: cout << "| COPPER\t";
    if (prev_avg_copper<avg_copper){cout<<"\033[;32m" << price_copper <<"↑\033[0m" <<"\t\t" <<  "\033[;32m" << avg_copper <<"↑\033[0m\n";} 
    else if (prev_avg_copper>avg_copper){cout<<"\033[;31m" << price_copper <<"↓\033[0m" <<"\t\t" <<  "\033[;31m" << avg_copper <<"↓\033[0m\n";}
    else cout << "\033[;36m" << price_copper <<"\033[0m" <<"\t\t" <<  "\033[;36m" << avg_copper <<"\033[0m""\n";
    printf("\033[12;54H");
    cout << "|\n";
   
   std:: cout << "| ALUMIUIUM\t";
    if (prev_avg_aluminium<avg_aluminium){cout<<"\033[;32m" << price_aluminium <<"↑\033[0m" <<"\t\t" <<  "\033[;32m" << avg_aluminium <<"↑\033[0m\n";} 
    else if (prev_avg_aluminium>avg_aluminium){cout<<"\033[;31m" << price_aluminium <<"↓\033[0m" <<"\t\t" <<  "\033[;31m" << avg_aluminium <<"↓\033[0m\n";}
    else cout << "\033[;36m" << price_aluminium <<"\033[0m" <<"\t\t" <<  "\033[;36m" << avg_aluminium <<"\033[0m""\n";
    printf("\033[13;54H");
    cout << "|\n";

  std::  cout << "| NATURALGAS\t";
   if (prev_avg_naturalgas<avg_naturalgas){cout<<"\033[;32m" << price_naturalgas <<"↑\033[0m" <<"\t\t" <<  "\033[;32m" << avg_naturalgas <<"↑\033[0m\n";} 
    else if (prev_avg_naturalgas>avg_naturalgas){cout<<"\033[;31m" << price_naturalgas <<"↓\033[0m" <<"\t\t" <<  "\033[;31m" << avg_naturalgas <<"↓\033[0m\n";}
    else cout << "\033[;36m" << price_naturalgas <<"\033[0m" <<"\t\t" <<  "\033[;36m" << avg_naturalgas <<"\033[0m""\n";
    printf("\033[14;54H");
    cout << "|\n";
   
   cout << "+----------------------------------------------------+\n"; 
    }
    shmdt(array);
    shmctl(shmid,IPC_RMID,NULL);
    semctl(semid,0,IPC_RMID);
    semctl(semid1,0,IPC_RMID);
    semctl(semid2,0,IPC_RMID);
       
    return 0;
}
