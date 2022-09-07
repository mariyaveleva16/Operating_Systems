#include<stdlib.h>
#include<unistd.h>
#include<err.h>

int main(){
	int a[2];
	if(pipe(a)==-1){
		err(1, "Couldn't pipe");
	}
	pid_t child_cut=fork();
	if(child_cut==-1){
		err(2, "Couldn't fork");
	}
	if(child_cut==0){
		close(a[0]);
		if(dup2(a[1],1)==-1){
			err(3, "dup");			
		}
		if(execlp("cut", "cut", "-d:", "-f7", "/etc/passwd",(char*)NULL)==-1){
			err(4, "cut");
		}
	}
	close(a[1]);

	int b[2];
	if(pipe(b)==-1){
		err(5, "");
	}
	pid_t child_sort=fork();
	if(child_sort==-1){
		err(6,"");
	}
	if(child_sort==0){
		if(dup2(a[0],0)==-1){
			err(12,"");
		}
		close(b[0]);
		if(dup2(b[1],1)==-1){
			err(7,"");
		}
		if(execlp("sort", "sort", (char*)NULL)==-1){
			err(8, "");
		}
	}
	close(b[1]);

	int c[2];
	if(pipe(c)==-1){
		err(9, "");
	}
	pid_t child_uniq=fork();
	if(child_uniq==-1){
		err(10, "");
	}
	if(child_uniq==0){
		if(dup2(b[0],0)==-1){
			err(13,"");
		}
		close(c[0]);
		if(dup2(c[1],1)==-1){
			err(11,"");
		}
		if(execlp("uniq", "uniq", "-c", (char*)NULL)==-1){
			err(12, "");
		}
	}
	close(c[1]);
	if(dup2(c[0],0)==-1){
		err(15,"");
	}
	if(execlp("sort", "sort", "-n", (char*)NULL)==-1){
		err(16,"");
	}

	exit(0);
}
