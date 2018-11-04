#include <string.h>

int str_cmp(char string1[], char string2[]){
    for (int i = 0; ; i++){
        if (string1[i] != string2[i]){
            if(string1[i]<string2[i])
              return 1;
            return -1;
          }
        if (string1[i] == '\0')
            return 0;
    }
}
