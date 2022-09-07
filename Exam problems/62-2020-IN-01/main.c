#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<err.h>
#include<unistd.h>

struct header{
	uint32_t magic;//4
	uint8_t hVersion;//1
	uint8_t dataV;//1
	uint16_t count;//2
	uint32_t res1;//4
	uint32_t res2;//4
}__attribute__((packed));

struct v0{
	uint16_t off;//2
	uint8_t org;//1
	uint8_t new;//1
}__attribute__((packed));

struct v1{
	uint32_t off;//4
	uint16_t org;//2
	uint16_t new;//2
}__attribute__((packed));

//patch f1 f2
int main (const int argc, const char* argv[]){
	if (argc != 4){
		errx(1,"Wrong number of prameters"); 
	}
	struct stat stP;
	if(stat(argv[1], &stP)== -1){
		err(2, "Error stating file %s", argv[1]);
	}
	if(stP.st_size==0){
		err(3, "File is empty %s", argv[1]);
	}
	
	struct stat st1;
	if(stat(argv[2], &st1)==-1){
		err(4, "Error stating %s", argv[2]);
	}
	if(st1.st_size==0){
		err(5, "File %s is empty.", argv[2]);
	}

	struct header h;
	//if((stP.st_size-sizeof(h))<0){
	//	err(5, "Even without header");
	//}
		
	int fdP;
	if((fdP=open(argv[1], O_RDONLY))==-1){
		err(6, "Err opening file %s", argv[1]);
	}

	int fd1;
	if((fd1=open(argv[2], O_RDONLY))==-1){
		err(7, "Error opening %s", argv[2]);
	}

	int fd2;
	if((fd2=open(argv[3], O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP)) == -1){
		err(8, "Error opening %s", argv[3]);
	}

	if(read(fdP, &h, sizeof(h)) != sizeof(h)){
		err(9, "Err reading %s" , argv[1]);
	}

	if(h.hVersion == 0x00){
		struct v0 v;
		if(((stP.st_size-sizeof(h))%sizeof(v))!=0){
			err(10, "Wrong file format");			
		}
		read(fdP, &v, sizeof(v));
		uint8_t a;
		uint16_t count=0;
		while(read(fd1, &a, sizeof(a))==sizeof(a)){
			if(count==v.off){
				if(a==v.org){
					write(fd2, &v.new, sizeof(v.new));
					read(fdP, &v, sizeof(v));
				}
				else{
					err(11, "The original byte from file %s is different form the original word form file %s.", argv[2], argv[1]);
				}
			}
			else{
				write(fd2, &a, sizeof(a));
			}
			count++;
		}

	}
	else{
		if(h.hVersion == 0x01){
			struct v1 v;
			if(((stP.st_size-sizeof(h))%sizeof(v)) !=0){
				err(11, "Wrong file format");
			}
			read(fdP, &v, sizeof(v));
			uint16_t a;
			uint32_t count=0;
			while(read(fd1, &a, sizeof(a))==sizeof(a)){
				if(count==v.off){
					if(a==v.org){
						write(fd2, &v.new, sizeof(v.new));
						read(fdP, &v, sizeof(v));
					}
					else{
						err(13, "The original word from file %s is different from the original word from file %s.", argv[2], argv[1]);
					}
				}
				else {
					write(fd2, &a, sizeof(a));
				}
				count++;
			}

		}
		else {
			err(9, "Wrong header version.");
		}
	}
	close(fdP);
	close(fd1);
	close(fd2);
	exit(0);
}
