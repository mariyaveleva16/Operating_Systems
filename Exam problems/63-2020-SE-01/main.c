#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<err.h>
#include<unistd.h>
#include<fcntl.h>

struct header{
	uint32_t notUsed1;
	uint16_t count;
	uint16_t notUsed2;
	uint64_t notUsed3;
}__attribute__((packed));

struct interval{
	uint16_t start;
	uint16_t length;
}__attribute__((packed));

int main(const int argc, const char* argv[]){
	if( argc != 7){
		errx(1, "Wrong number of parameters.");
	}

	//check affix format
	struct stat stA;
	if(stat(argv[1], &stA) == -1){
		err(2, "Err stating %s", argv[1]);
	}
	if(stA.st_size == 0){
		err(3, "File %s is empty.", argv[1]);
	}
	int fdA;
	if((fdA=open(argv[1], O_RDONLY)) ==-1){
		err(4, "Error opening %s", argv[1]);
	}
	struct header A;
	read(fdA, &A, sizeof(A));
	if(((stA.st_size-sizeof(A))%(A.count))!=0){
		err(5, "Wrong format of %s",argv[1]);
	}

	//check postfix format
	struct stat stPo;
	if(stat(argv[2], &stPo) == -1){
		err(6, "Err stating %s", argv[2]);
	}
	if(stPo.st_size == 0){
		err(7, "File %s is empty.", argv[2]);
	}
	int fdPo;
	if((fdPo=open(argv[2], O_RDONLY))== -1){
		err(8, "Error opening %s", argv[2]);
	}
	read(fdPo, &A, sizeof(A));
	if(((stPo.st_size-sizeof(A))%((uint32_t)A.count)) != 0){
		err(9, "Wrong format of %s",argv[2]);
	}
	
	//check prefix format
	struct stat stPr;
	if(stat(argv[3], &stPr) == -1){
		err(10,"Err stating %s", argv[3]);
	}
	if(stPr.st_size == 0){
		err(11, "File %s is empty.", argv[3]);
	}
	int fdPr;
	if((fdPr=open(argv[3], O_RDONLY))== -1){
		err(12, "Error opening %s", argv[3]);
	}
	read(fdPr, &A, sizeof(A));
	if(((stPr.st_size-sizeof(A))%((uint8_t)A.count)) != 0){
		err(13, "Wrong format of %s",argv[3]);
	}

	//check infix format
	struct stat stI;
	if(stat(argv[4], &stI) == -1){
		err(14,"Err stating %s", argv[4]);
	}
	if(stI.st_size == 0){
		err(15, "File %s is empty.", argv[4]);
	}
	int fdI;
	if((fdI=open(argv[4], O_RDONLY))== -1){
		err(16, "Error opening %s", argv[4]);
	}
	read(fdI, &A, sizeof(A));
	if(((stI.st_size-sizeof(A))%(A.count)) != 0){
		err(17, "Wrong format of %s",argv[4]);
	}
	
	//check suffix format
	struct stat stS;
	if(stat(argv[5], &stS) == -1){
		err(10,"Err stating %s", argv[5]);
	}
	if(stS.st_size == 0){
		err(11, "File %s is empty.", argv[5]);
	}
	int fdS;
	if((fdS=open(argv[5], O_RDONLY))== -1){
		err(12, "Error opening %s", argv[5]);
	}
	read(fdS, &A, sizeof(A));
	if(((stS.st_size-sizeof(A))%((uint64_t)A.count)) != 0){
		err(13, "Wrong format of %s",argv[5]);
	}
	

	int fdC;
	if((fdC=open(argv[6], O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP))== -1){
		err(20, "err");
	}
	
	struct interval i;
	uint16_t count=0;
	uint16_t complekts;
	complekts=(stA.st_size-sizeof(A))/(4*sizeof(i));
	uint16_t comCount=0;
	while(comCount<complekts){
		
		//read for postfix
		read(fdA, &i, sizeof(i));
		if((lseek(fdPo, (i.start*sizeof(uint32_t))+sizeof(A), SEEK_SET))==-1){
			err(14, "err");
		}
		uint32_t p;
		while(count<i.length){
			read(fdPo, &p, sizeof(p));
			write(fdC, &p, sizeof(p));
			count++;
		}
		count=0;
		
		//read for prefix
		read(fdA, &i, sizeof(i));
		if((lseek(fdPr, (i.start*sizeof(uint8_t))+sizeof(A), SEEK_SET))==-1){
			err(14, "err");
		}
		uint8_t pr;
		while(count<i.length){
			read(fdPr, &pr, sizeof(pr));
			write(fdC, &pr, sizeof(pr));
			count++;
		}
		count=0;
		
		//read for infix
		read(fdA, &i, sizeof(i));
		if((lseek(fdI, (i.start*sizeof(uint16_t))+sizeof(A), SEEK_SET))==-1){
			err(14, "err");
		}
		uint16_t in;
		while(count<i.length){
			read(fdI, &in, sizeof(in));
			write(fdC, &in, sizeof(in));
			count++;
		}
		count=0;
	
		//read for sufix
		read(fdA, &i, sizeof(i));
		if((lseek(fdS, (i.start*sizeof(uint64_t))+sizeof(A), SEEK_SET))==-1){
			err(14, "err");
		}
		uint64_t su;
		while(count<i.length){
			read(fdS, &su, sizeof(su));
			write(fdC, &su, sizeof(su));
			count++;
		}
		count=0;
		comCount++;
	}

	close(fdA);
	close(fdPo);
	close(fdPr);
	close(fdI);
	close(fdS);
	close(fdC);
	exit(0);
}
