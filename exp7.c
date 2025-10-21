//exp7.c first and follow sets for a given grammar  
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX 20
#define MAX_LEN 100
int count = 0;
char prod[MAX][MAX_LEN];
char first[MAX][MAX_LEN];
char follow[MAX][MAX_LEN];
int isFirstComputed[MAX];
int isFollowComputed[MAX];
int getIndex(char c) {
for (int i = 0; i < count; i++){
if(prod[i][0] == c)
return i;
}
return -1;
}
int contains(char *s, char c){
for(int i = 0; i < strlen(s); i++){
if (s[i] == c) return 1;
}
return 0;
}
void addChar(char *s, char c) {
if (!contains(s, c)) {
int len = strlen(s);
s[len] = c;
s[len+1] = '\0';
}
}
void findFirst(char c){
int i = getIndex(c);
if(i == -1)return;
if(isFirstComputed[i])return;
isFirstComputed[i] = 1;
for(int j = 0; j < count; j++){
if (prod[j][0] == c) {
int k = 2;
if (prod[j][k] == '@'){
addChar(first[i], '@');
} else{
while (prod[j][k] != '\0'){
char sym = prod[j][k];
if (!isupper(sym)){
addChar(first[i], sym);
break;
}else{
findFirst(sym);
int idx = getIndex(sym);
for(int x = 0; x < strlen(first[idx]); x++)
{
                            if (first[idx][x] != '@')
                                addChar(first[i], first[idx][x]);
                        }
                        if (contains(first[idx], '@')) {
                            k++;
                            if (prod[j][k] == '\0')
                                addChar(first[i], '@');
                        } else break;
                    }
                }
            }
        }
    }
}


void findFollow(char c) {
    int i = getIndex(c);
    if (i == -1) return;

    if (isFollowComputed[i]) return;
    isFollowComputed[i] = 1;

    if (i == 0) addChar(follow[i], '$'); 

    for (int j = 0; j < count; j++) {
        for (int k = 2; prod[j][k] != '\0'; k++) {
            if (prod[j][k] == c) {
                int l = k + 1;
                while (prod[j][l] != '\0') {
                    char sym = prod[j][l];
                    if (!isupper(sym)) {
                        addChar(follow[i], sym);
                        break;
                    } else {
                        int idx = getIndex(sym);
                        for (int x = 0; x < strlen(first[idx]); x++) {
                            if (first[idx][x] != '@')
                                addChar(follow[i], first[idx][x]);
                        }
                        if (contains(first[idx], '@')) {
                            l++;
                            if (prod[j][l] == '\0') {
                                if (prod[j][0] != c) {
                                    findFollow(prod[j][0]);
                                    int idx2 = getIndex(prod[j][0]);
                                    for (int y = 0; y < strlen(follow[idx2]); y++) {
                                        addChar(follow[i], follow[idx2][y]);
                                    }
                                }
                            }
                        } else break;
                    }
                }
                if (prod[j][l] == '\0' && prod[j][0] != c) {
                    findFollow(prod[j][0]);
                    int idx2 = getIndex(prod[j][0]);
                    for (int y = 0; y < strlen(follow[idx2]); y++) {
                        addChar(follow[i], follow[idx2][y]);
                    }
                }
            }
        }
    }
}

int main() {
    int n;
    printf("Enter number of productions: ");
    scanf("%d", &n);
    getchar(); 

    count = 0;

    printf("Enter productions (use '|' for multiple alternatives, use '@' for epsilon):\n");
    for (int i = 0; i < n; i++) {
        char line[200];
        fgets(line, sizeof(line), stdin);

       
        line[strcspn(line, "\n")] = 0;

        
        char lhs = line[0];
        char *rhs = strchr(line, '=');
        if (!rhs) {
            printf("Invalid production format!\n");
            return 1;
        }
        rhs++; 

       
        char *token = strtok(rhs, "|");
        while (token != NULL) {
          
            prod[count][0] = lhs;
            prod[count][1] = '=';
            strcpy(&prod[count][2], token);
            prod[count][strlen(token) + 2] = '\0';

          
            int idx = getIndex(lhs);
            if (idx == -1) {
                first[count][0] = '\0';
                follow[count][0] = '\0';
                isFirstComputed[count] = 0;
                isFollowComputed[count] = 0;
            }

            count++;
            token = strtok(NULL, "|");
        }
    }

  
    for (int i = 0; i < count; i++) {
        findFirst(prod[i][0]);
    }

  
    for (int i = 0; i < count; i++) {
        findFollow(prod[i][0]);
    }

    
    printf("\nFIRST sets:\n");
    for (int i = 0; i < count; i++) {
        char c = prod[i][0];
      
        if (getIndex(c) == i) {
            printf("FIRST(%c) = { ", c);
            for (int j = 0; j < strlen(first[i]); j++) {
                if (first[i][j] == '@')
                    printf("epsilon ");
                else
                    printf("%c ", first[i][j]);
            }
            printf("}\n");
        }
    }

    
    printf("\nFOLLOW sets:\n");
    for (int i = 0; i < count; i++) {
        char c = prod[i][0];
        if (getIndex(c) == i) {
            printf("FOLLOW(%c) = { ", c);
            for (int j = 0; j < strlen(follow[i]); j++) {
                printf("%c ", follow[i][j]);
            }
            printf("}\n");
        }
    }

    return 0;
}


/*input:
enter number of productions: 4
enter productions (use '|' for multiple alternatives, use '@' for epsilon):
S=AB|BC
B=b
C=c
A=a|@

*/