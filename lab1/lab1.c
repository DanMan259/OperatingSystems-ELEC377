/*+
 * lab1.c - Print process information
-*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <strings.h>
#include <ctype.h>

int isProcessDir(const struct dirent*d){
	char *temp = d->d_name;
	while (*temp == "\0"){
		if (!(isdigit(*temp))){
			return 0;
		}
		temp++;
	}	
	return 1;
}

int main(){
	struct dirent ** namelist;
	int n;

	n = scandir("/proc", &namelist, isProcessDir, NULL);
	printf("%c",namelist[0]->d_name[0]);
}
