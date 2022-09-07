#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
#include<err.h>
#include<fcntl.h>

int main(const int argc, const char* argv[]){
	if(argc < 3 || argc > 5 || argc == 4){
		errx(1, "Wrong number of param");
	}
	if((strcmp(argv[1], "-c")) == 0){
		if(argc != 3){
			errx(2, "Wrong number of parameters for opiton -c");
		}
		if(strchr(argv[2], '-')==NULL){
			char a;
			ssize_t cnt=0;
			while(read(0, &a, sizeof(a))==sizeof(a)){
				cnt++;
				if(cnt==((ssize_t)argv[2][0]-(ssize_t)'0')){
					write(1,&a, sizeof(a));
					break;
				}		
			}		
		}
		else{
			char a;
			ssize_t cnt=0;
			while(read(0, &a, sizeof(a))==sizeof(a)){
				cnt++;
				if(cnt>=((ssize_t)argv[2][0]-(ssize_t)'0') && cnt<=((ssize_t)argv[2][2]-(ssize_t)'0'))
				{
					write(1, &a, sizeof(a));
				}
			}
		}	
	}
	else{
		if((strcmp(argv[1], "-d")) == 0){
			if(argc != 5){
				errx(3, "Wrong number of parameters for option -d");
			}
			if((strcmp(argv[3], "-f")) != 0){
				err(4, "Invalid third parameter");
			}
			char a;
			ssize_t del=1;
			if(strchr(argv[4], '-')==NULL){
				while((read(0, &a, sizeof(a)))== sizeof(a)){
					if(argv[2][0]==a){
						del++;
					}
					else{
						if(del==((ssize_t)argv[4][0]-(ssize_t)'0')){
							write(1,&a,sizeof(a));
						}
					}			
				}
			}
			else{
				while((read(0,&a,sizeof(a)))==sizeof(a)){
					if(argv[2][0]==a){
						del++;
					}
					else{
						if(del>=((ssize_t)argv[4][0]-(ssize_t)'0') && del<=((ssize_t)argv[4][2]-(ssize_t)'0')){
							write(1,&a,sizeof(a));
						}
					}
				}
			}

		}
		else{
			err(2, "Invalid first parameter");
		}
	}
	printf("\n");
	exit(0);
}
