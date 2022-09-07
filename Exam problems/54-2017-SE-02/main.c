//ako argc == 1 chete ot stdin
//ako argc == 2 izvejda faila / ako e tire chete ot stdin
//ako argc >= 3 proverqwa dali  argv[1] == -n / ako e tire chete ot stdin ako e fail go izvejda
//


#include<stdlib.h>
#include<sys/types.h>
#include<stdint.h>
#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<err.h>

int main(const int argc, const char* argv[]){
	if( argc == 1){ //da nqma argumenti
		uint8_t a;
		while(read(0, &a, sizeof(a)) ==sizeof(a)){
			write(1, &a, sizeof(a));
		}
	}
	else{
		if ( strcmp(argv[1],"-n") == 0){//nomeriran output
			int i=1;
			if ( argc == 2 ) {
				uint8_t a;
				printf("%d ", i++);
				fflush(NULL);
				while(read(0, &a, sizeof(a)) == sizeof(a)){	
					write(1, &a, sizeof(a));
					if( a ==  '\n'){
						printf("%d ", i++);
						fflush(NULL);				
					}
				}
			}
			else {
				printf("%d ", i++);
				fflush(NULL);
				int arg=2;
				while (arg<argc){
					uint8_t a;
					if(strcmp(argv[arg], "-") ==0){
						while(read(0, &a,sizeof(a))==sizeof(a)){
							write(1, &a,sizeof(a));	
							if( a == '\n'){
								printf("%d ", i++);
								fflush(NULL);
							}
						}
					}
					else{
						int fd;
						if((fd=open(argv[arg], O_RDONLY))== -1){
							err(1,"Err opening");
						}
						while(read(fd, &a, sizeof(a))== sizeof(a)){
							write(1,&a, sizeof(a));
							if( a=='\n'){
								printf("%d ", i++);
								fflush(NULL);
							}
						}	
						close(fd);
					}
					arg++;
				}
			}	
		}
		else{
			int arg=1;
			while(arg<argc){
				uint8_t a;
				if( strcmp( argv[arg], "-") ==0){
					while(read(0, &a, sizeof(a)) == sizeof(a)){
						write(1, &a,sizeof(a));
					}
				}
				else{
					int fd;
					if((fd=open(argv[arg],O_RDONLY)) == -1){
						err(2, "Err opening");
					}
					while(read(fd, &a, sizeof(a)) == sizeof(a)){
						write(1, &a, sizeof(a));
					}
					close(fd);
				}
				arg++;
			}
		}
	}
	exit(0);
}	
