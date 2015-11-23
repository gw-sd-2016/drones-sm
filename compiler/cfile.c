if(argc > 1){
void* ptr = states[atoi(argv[1])];
goto *ptr;
}
int x, i;
char y;
double w;
state_A:
x = 1 + 9;
for(i= 0; i <= 7; i++ ){
printf("loop 1a x: %d i: %d\n",x, i);
}
printf("Embeded in the code\n");
if(x <= 9){
printf("if 1a x: %d\n",x);
}
for(x = 0; x <= 10; x++){
printf("loop 2a x: %d\n",x);
}
goto state_B;


int q;
state_B:
q = 9;
if(q <= 9){
printf("if 1b q: %d\n",q);
}
for(x = 2; x <= q ;x++){
printf("loop 1b x: %d q: %d\n",x, q);
}
goto state_C;


state_C:
goto state_C;



}