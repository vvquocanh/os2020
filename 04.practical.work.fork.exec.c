#include <stdio.h>
#include <unistd.h>

int main() {
	int pid1 = fork();
	int pid2 = fork();
	if (pid1 == 0 && pid2 == 0) {
		return 0;
	} else if (pid1 == 0) {
		printf("I am child after fork(), launching ps -ef\n");
		char *args[]= { "/bin/ps", "-ef" , NULL};
		execvp("/bin/ps", args);
	} else if (pid2 == 0) {
		printf("I am child after fork(), launching free -h\n");
		char *args[] = {"usr/bin/free", "-h", NULL};
		execvp("/usr/bin/free", args);
	} else {
		printf("I'm parent\n");
	}
	return 0;
}
