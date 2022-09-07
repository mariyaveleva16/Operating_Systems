#include <stdint.h>
#include <stdlib.h>
#include <err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
int bits(int n){
	int count=0;
	while(n>0){
		count++;
		n &=(n-1);
	}
	return count;
}
int main(int argc, char** argv) {
	if (argc != 4)
		errx(1, "Wrong arguments passed!");

	int scl = open(argv[1], O_RDONLY);
	if (scl == -1)
		err(2, "Opening failure!");

	int sdl = open(argv[2], O_RDONLY);
	if (sdl == -1) {
		err(2, "Opening failure!");
	}
	int fd = open(argv[3], O_CREAT | O_WRONLY|O_TRUNC, 0644);
	if (fd == -1) {
		err(2, "Opening failure!");
	}
	
	uint8_t a;

	while((read(scl, &a, sizeof(a)))==sizeof(a)){
		if(a==1)
		{
			write(1, 1, sizeof(1));
		}
		//write(1,&a, sizeof(a));
		write(1, bits(&a), sizeof(bits(a)));
	}
	close(fd);
	close(scl);
	close(sdl);
	exit(0);
}
