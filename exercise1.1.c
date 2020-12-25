#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include<sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int fd[0];
int fd1[0];
void readFile2(int fd1,char* namePtrs) {
	int bytes_reads;
	int counts=0;
	char* ops;
	float sums=0;
	int ks=0;
	unsigned char buffers[10];
	//char* namePtrs;
	do{
		bytes_reads=read(fd1,buffers,1);
	       	//printf("%s",buffers);
		if(*buffers==','&& counts>=201){
			ks++;
			if(ks==1){
				printf("Student-ID:(%s)\n",namePtrs);
			}
			if(ks==2){
				printf("Section-Number:(%s)\n",namePtrs);
			}
			if(ks==3){
				printf("Assignment-1:(%d)\n",atoi(namePtrs));
				sums+=atoi(namePtrs);
			}
			if(ks==4){
				printf("Assignment-2(%d)\n",atoi(namePtrs));
				sums+=atoi(namePtrs);
			}
			if(ks==5){
				printf("Assignment-3(%d)\n",atoi(namePtrs));
				sums+=atoi(namePtrs);
			}
			//printf("(%d)",atoi(namePtr));
			//sum+=atoi(namePtr);
			*namePtrs=0;
		}
		if(*buffers!=','){
			strcat(namePtrs,buffers);
		}
		if(*buffers=='\n'){
			if(counts>=201){
				printf("Assignment-4:(%d)\n",atoi(namePtrs));
				sums+=atoi(namePtrs);
				printf("Average ====================(%f)\n",sums/4);
			}
			*namePtrs=0;
			sums=0;
			counts++;
			ks=0;
			printf("\n");
		}
	}
	while(bytes_reads!=0 &&counts<401);	
	//printf("%s","h---------ello");
}


void readFile(int fd) {
	int bytes_read;
	int count=0;
	char* op;
	float sum=0;
	int k=0;
	unsigned char buffer[10];
	 char *namePtr;
	 pid_t p=fork();
	 if(p==0){
		 do{
			 bytes_read=read(fd,buffer,1);
			 //printf("%s",buffer);
			 if(*buffer==','){
				 k++;
				 if(k==1){
					 printf("Student-ID:(%s)\n",namePtr);
				 }
				 if(k==2){
					 printf("Section-Number:(%s)\n",namePtr);
				 }
				 if(k==3){
					 printf("Assignment-1:(%d)\n",atoi(namePtr));
					 sum+=atoi(namePtr);
				 }
				 if(k==4){
					 printf("Assignment-2(%d)\n",atoi(namePtr));
					 sum+=atoi(namePtr);
				 }
				 if(k==5){
					 printf("Assignment-3(%d)\n",atoi(namePtr));
					 sum+=atoi(namePtr);
				 }
				 //printf("(%d)",atoi(namePtr));
				 //sum+=atoi(namePtr);
				 *namePtr=0;
			 }
			 if(*buffer!=','){
				 strcat(namePtr,buffer);
			 }
			 if(*buffer=='\n'){
				 printf("Assignment-4:(%d)\n",atoi(namePtr));
				 sum+=atoi(namePtr);
				 printf("Average ====================(%f)\n",sum/4);
				 *namePtr=0;
				 sum=0;
				 count++;
				 k=0;
				 printf("\n");
			 }

		 }
		 while(bytes_read!=0 && count<201);
		 exit(0);
	 }
	 else{
		 int returnstat;
		 waitpid(p,&returnstat,0);
		 if(returnstat==0){
			 if(access("file.csv",F_OK)==0){
				 fd1[0]=open("file.csv",O_RDONLY);
				 //printf("%d\n",fd1[0]);
			 }
			 *namePtr=0;
			 readFile2(fd1[0],namePtr);
		 }
	 }
}


int main(void) {
	if (access("file.csv", F_OK) == 0) {
		fd[0] = open("file.csv", O_RDONLY);
		//printf("%d\n",fd[0]);
	}
	readFile(fd[0]);
	close(fd[0]);
	//close(fd[1]);
}
