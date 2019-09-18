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

void main(){
	struct dirent ** namelist;
	char buffer [100];
	int n,i;
	FILE *fp;
	char fileBuffer [100], name [50], status [50], number [50], user [50], group [50];
	char *ptr;
	n = scandir("/proc", &namelist, isProcessDir, NULL);
	
	printf("#  Name\tStatus\tUser  Group\n");
    for (i = 0; i < n; i++) {
        sprintf(buffer, "/proc/%s/status",namelist[i]->d_name);
        fp = fopen (buffer, "r");
        while(fgets(fileBuffer, 100, fp)) {
            
            if (strstr(fileBuffer, "Name:")){
                ptr = strtok(fileBuffer, ":\t");
	            ptr = strtok(NULL, "\t");
	            strcpy(name, ptr);
	            if ((ptr=strchr(name, '\n')) != NULL)
                    *ptr = '\0';
	            //printf("%s", name);
            }else if (strstr(fileBuffer, "State:")){
                ptr = strtok(fileBuffer, ":\t");
	            ptr = strtok(NULL, "\t");
	            strcpy(status, ptr);
	            if ((ptr=strchr(status, '\n')) != NULL)
                    *ptr = '\0';
	            //printf("%s", status);
            }/*else if (strstr(fileBuffer, "Pid:")){
                ptr = strtok(fileBuffer, ":\t");
	            ptr = strtok(NULL, "\t");
	            status = ptr;
	            printf("%s", status);
            }else if (strstr(fileBuffer, "Uid:")){
                //printf("Yes3\n");
                //user = strtok(fileBuffer, " ");
            }else if (strstr(fileBuffer, "Gid:")){
                //printf("Yes4\n");
                //group = strtok(fileBuffer, " ");
            }*/
        };
        //sprintf(buffer, "%d\t%s\t%s\t%d  %d\n", *number, *name, *status, *user, *group);
        printf("%s\t%s\n", name, status);
	}
}
