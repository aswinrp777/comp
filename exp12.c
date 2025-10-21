//exp12 backend 8086 assembler
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int isnum(const char *s) {
if (*s == '-' || *s == '+')
s++;
if (!*s) return 0;
while (*s) if (!isdigit(*s++)) return 0;
return 1;
}
int main(int argc, char *argv[]) {
FILE *in = stdin;
if (argc > 1) in = fopen(argv[1], "r");
if (!in) { perror("open"); return 1; }

printf("; simple TAC -> 8086 (MASM/TASM-style)\n");
printf(".stack 100h\n.data\n");
printf("a dw 0\nb dw 0\nt1 dw 0\nc dw 0\nd dw 0\n\n");
printf(".code\nstart:\n mov ax,@data\n mov ds,ax\n");
char line[128], left[32], right1[32], right2[32], op;
while (fgets(line, sizeof line, in)) {
if (sscanf(line, "%s = %s %c %s", left, right1, &op, right2) == 4) {
printf(" mov ax,%s\n", right1);
if (op=='+') printf(" add ax,%s\n", right2);
if (op=='-') printf(" sub ax,%s\n", right2);
if (op=='*') {
printf(" mov bx,%s\n", right2);
printf(" imul bx\n");
}
if (op=='/') {
printf(" cwd\n");
printf(" mov bx,%s\n", right2);
printf(" idiv bx\n");
}
printf(" mov %s,ax\n", left);
}
else if (sscanf(line, "%s = %s", left, right1) == 2) {
if (isnum(right1)) printf(" mov %s,%s\n", left, right1);
else {
printf(" mov ax,%s\n", right1);
printf(" mov %s,ax\n", left);
}
}
else if (strncmp(line,"if",2)==0) {
sscanf(line,"if %s > %s goto %s", right1, right2, left);
printf(" mov ax,%s\n", right1);
printf(" cmp ax,%s\n", right2);
printf(" jg %s\n", left);
}
else if (strncmp(line,"goto",4)==0) {
sscanf(line,"goto %s", left);
printf(" jmp %s\n", left);

}
else if (strchr(line,':')) {
printf("%s", line);
}
}
printf(" mov ax,4C00h\n int 21h\nend start\n");
if (in != stdin) fclose(in);
return 0;
}

/*input.tac
a = 10
b = 5
t1 = a + b
t2 = a - b
t3 = a * b
t4 = a / b
if t1 > t2 goto L1
goto L2
L1:
c = t3 + t4
goto L3
L2:
c = t2 - t1
L3:
d = c

gcc exp12.c
./a.out input.tac > output.asm

*/