/*+
 * lab1.c - Print process information
-*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>

int isProcessDir(const struct dirent*d){
	char *temp = d->d_name;
          while(*temp != '\0'){
		if (!(isdigit(*temp))){
			return 0;
		}
		temp++;
	}	
	return 1;
}

int main(){
	struct dirent ** namelist;
	char buffer [100];
	int n,i;

	n = scandir("/proc", &namelist, isProcessDir, NULL);
    for (i = 0; i < n; i++) {
        sprintf(buffer, "/proc/%d/status",namelist[i]->d_name);
        printf("%s\n",buffer);
	}
}
