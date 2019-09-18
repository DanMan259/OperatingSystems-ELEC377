/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

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
	struct dirent *temp = namelist;
	while (temp != NULL){
	    for (int i = 0; i < strlen(temp->d_name); i++) 
	        if (temp->d_name[i] == "\0"){
	            printf("\n");
	        }else{
	            printf("%c",temp->d_name[i]);
	        }
	    temp++;
	}
}
