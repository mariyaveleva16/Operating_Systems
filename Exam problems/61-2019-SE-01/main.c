#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<err.h>

struct five{
	uint32_t uid;
	uint16_t save1;
	uint16_t save2;
	uint32_t timeS;
	uint32_t timeE;
}__attribute__((packed));

int main(const int argc, const char* argv[]){
	if(argc != 2){
		errx(1, "Wrong number of parameters.");
	}
	struct stat st;
	if(stat(argv[1],&st)== -1){
		err(2, "Error stating file %s", argv[1]);
	}
	if(st.st_size == 0){
		err(3, "File %s is empty", argv[1]);	
	}
	struct five f;
	if((st.st_size%sizeof(f)) != 0){
		err(4, "File %s is with wrong structure.", argv[1]);
	}
	int fd;
	if((fd=open(argv[1],O_RDONLY)) == -1){
		err(5, "Error opening file %s", argv[1]);
	}
	uint32_t timeSum=0;
	int N=0;
	uint32_t timeL=0;
	while((read(fd, &f, sizeof(f)))>0){
		timeL=f.timeE-f.timeS;
		printf("%d=%d-%d\n", timeL, f.timeE, f.timeS); 
		timeSum=timeSum+timeL;
		N++;
	}
	uint32_t timeAvr=0;
	printf("timesum= %d\n", timeSum);
	printf("N= %d\n", N);
	timeAvr=timeSum/(uint32_t)N;
	printf("Avr= %d\n", timeAvr);
	if(lseek(fd, 0 , SEEK_SET) == -1){
		err(6, "Error lseeking");
	}
 	uint32_t* ptr;
   	ptr	= (uint32_t*) malloc (2048*(sizeof(uint32_t)));	
	if(ptr==NULL){
		err(7, "Memmory not allocated");
	}
	uint32_t timeD=0;
	while((read(fd, &f, sizeof(f)))>0){
		timeL=f.timeE-f.timeS;
		printf("L= %d\n", timeL);
		timeD=timeD+((timeL-timeAvr)*(timeL-timeAvr));
		printf("timed= %d\n" , timeD);
		//if(ptr[f.uid]<timeL){
		//	ptr[f.uid]=timeL;
		//}
	}
	uint32_t D=0;
	D=timeD/(uint32_t)N;
	printf("D= %d\n", D);
	if(lseek(fd,0,SEEK_SET)== -1){
		err(8, "Error lseeking");
	}
	uint32_t timeLL=0;
	while((read(fd, &f, sizeof(f)))>0){
		printf("%x\n", f.uid);
		timeL=f.timeE-f.timeS;
		printf("L=%d\n", timeL);
		timeLL=timeL*timeL;
		printf("LL=%d\n", timeLL);
		if(timeLL> D){
	//		timeL=ptr[f.uid];
			printf("Uid of user with session bigger then %d: %x with time %d \n", D, f.uid, timeL);

		}
	}
	free(ptr);	
	close(fd);
	exit(0);
}
