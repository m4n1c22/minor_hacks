/** 
	\file		:	convenience_methods.h 	
	\author 	:	Sreeram Sadasivam
	\brief		:	Convenience methods designed for performing various operations on strings and files.
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#ifndef __CONVENIENCE_METHODS_H__
#define __CONVENIENCE_METHODS_H__

typedef enum 
{
	false=0,
	true=1
}BOOL;

/** Convenience methods... */
void extractStringFromFileAtLine(char *line_string,char filename[],int line_no) {

	FILE *fp = fopen(filename,"r");

	while ((fgets(line_string,1000, fp)!=NULL)&&(line_no>0)) {
		line_no--;
	}
	fclose(fp);
}

void extractWordFromStringAtPosition(char word[],char string[],int pos) {


	char tmpString[1000],*tmp_word;
	strcpy(tmpString,string);
	int index=0;
	tmp_word = strtok(tmpString," ");
	for(;(index<pos)&&(tmp_word != NULL);index++) {

		tmp_word = strtok(NULL," ");
	}
	strcpy(word,tmp_word);
}

int wordContainsInFile(char word[], char filename[]) {

	int line_no = 0;

	char line_string[1000];


	FILE *fp = fopen(filename,"r");

	while ((fgets(line_string,1000, fp)!=NULL)) {
		if(strstr(line_string,word)!=NULL) {
			break;
		}
		line_no++;
	}
	fclose(fp);

	return line_no;
}

void splitStringWithSplitWordAndPosition(char resString[],char mainString[],char splitString[],int position) {

	char tmpString[1000],*tmp_word;
	strcpy(tmpString,mainString);
	int index=0;
	tmp_word = strtok(tmpString,splitString);
	strcpy(resString,tmp_word);
	//printf("%s\n",tmp_word );
	for(;(index<position-1)&&(tmp_word != NULL);index++) {

		strcat(resString,".");
		tmp_word = strtok(NULL,splitString);
		strcat(resString,tmp_word);
	}
	//printf("%s\n",resString);
	//strcpy(word,tmp_word);

}


#endif