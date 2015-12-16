if(argc > 1){
void* ptr = states[atoi(argv[1])];
goto *ptr;
}
State_A_Struct A_S;
A_S.x = 9;
A_S.i;
A_S.y;
A_S.w;
state_A:
printf("x: %d\n",A_S.x);
for(A_S.i = 0; A_S.i <= 10; A_S.i++){
printf("loop 1a x: %d i: %d\n",A_S.x, A_S.i);
}
if(A_S.x <= 9){
printf("if 1a x: %d\n",A_S.x);
}
for(A_S.x = 0; A_S.x <= 10; A_S.x++){
printf("loop 2a x: %d\n",A_S.x);
}
goto state_B;


State_B_Struct B_S;
B_S.q;
B_S.x = 0;
state_B:
B_S.q = 9;
if(B_S.q <= 9){
printf("if 1b q: %d\n",B_S.q);
}
for(B_S.x = 2; B_S.x <= B_S.q; B_S.x++){
printf("loop 1b x: %d q: %d\n",B_S.x, B_S.q);
}
goto state_C;


State_C_Struct C_S;
state_C:
goto state_C;



}