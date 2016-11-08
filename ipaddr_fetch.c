#include <stdio.h>
#define PATH_MAX 1000
main() {

	FILE *fp;
	int status;
	char path[PATH_MAX];

	fp = popen("ping 192.168.1.1", "r");
	if (fp == NULL)
		printf("Ping not reachable\n");
	while (fgets(path, PATH_MAX, fp) != NULL)
       	printf("%s\n",path);
	status = pclose(fp);
	return 0;
}