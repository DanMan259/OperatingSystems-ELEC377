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
	int n,i;
	FILE *fp;
	char buffer [50], fileBuffer [50], name [50], status [50], number [50], user [50], group [50];
	char *ptr;
	n = scandir("/proc", &namelist, isProcessDir, NULL);
	printf("#\tName\tStatus\t\tUser\tGroup\n");
    for (i = 0; i < n; i++) {
        sprintf(buffer, "/proc/%s/status",namelist[i]->d_name);
        fp = fopen (buffer, "r");
        while(fgets(fileBuffer, 100, fp)) {
            
            if (strstr(fileBuffer, "Name:")){
	            strcpy(name, fileBuffer+6);
	            if ((ptr=strchr(name, '\n')) != NULL)
                    *ptr = '\0';
            }else if (strstr(fileBuffer, "State:")){
	            strcpy(status, fileBuffer+7);
	            if ((ptr=strchr(status, '\n')) != NULL)
                    *ptr = '\0';
            }else if (strstr(fileBuffer, "Pid:") && !strstr(fileBuffer, "PPid:") && !strstr(fileBuffer, "TracerPid:")){
	            strcpy(number, fileBuffer+5);
	            if ((ptr=strchr(number, '\n')) != NULL)
                    *ptr = '\0';
            }else if (strstr(fileBuffer, "Uid:")){
                strcpy(user, fileBuffer+5);
                if ((ptr=strchr(user, '\t')) != NULL)
                    *ptr = '\0';
            }else if (strstr(fileBuffer, "Gid:")){
                strcpy(group, fileBuffer+5);
                if ((ptr=strchr(group, '\t')) != NULL)
                    *ptr = '\0';
            }
        };
        printf("%s\t%s\t%s\t%s\t%s\n",number, name, status, user, group);
	}
}