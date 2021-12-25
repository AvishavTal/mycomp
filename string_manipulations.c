
#include "string_manipulations.h"
/**
 * trim the whitespaces from the edges of the given string
 * @param str
 * @return
 */
char *trim_whitespace(char *str){
    char *end;
    while(isspace((unsigned char)*str))
        str++;
    if(*str == 0)
        return str;
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end))
        end--;
    end[1] = '\0';/*todo bug here with the input "1"*/

    return str;
}
/**
 * split the given string to several strings
 * @param src the string to split
 * @param dest 2D array to hold the otput strings
 * @param delimiter
 * @return the number of strings
 */
int split(char *src, char **dest, const char *delimiter) {
    int i;
    char *temp;
    i=0;
    temp=strtok(src,delimiter);
    while (temp!=NULL){
        dest=(char **)realloc(dest, (i+1)* sizeof(char *));
        dest[i]=temp;
        temp=strtok(NULL,delimiter);
        i++;
    }

    return i;
}

char is_zeero(char *str) {
    char result=1;
    int i=1;
    char point_flag=0;
    if(*str != '0' && *str !='-' && *str !='+' && *str !='.'){
        result=0;
    }
    if (*str=='.'){
        point_flag=1;
    }
    while (result&&i< strlen(str)){
        if (str[i]=='.'){
            if (point_flag){
                result=0;
            }
            point_flag=1;
        } else if (str[i]){
            result=0;
        }
        ++i;
    }
    return result;
}

int str_to_double(char *str, double *dest) {
    int result=1;
    trim_whitespace(str);
    if(is_zeero(str)){
        *dest= 0;
    } else{
        *dest= atof(str);
        if (!(*dest)){
            result=0;
        }
    }
    return result;
}

