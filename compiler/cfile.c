void* start_ptr = &&state_A;
State_GLOBAL_Struct GLOBAL_S;
unsigned char* data = malloc(sizeof(GLOBAL_S));
GLOBAL_S.test = 0;
GLOBAL_S.uwotm8 = 69;
if(s){
void* ptr = states[state];
goto *ptr;
}
else{
goto *start_ptr;
}
begin:;
state_A:;
State_A_Struct A_S;
A_S.x = -9;
A_S.i;
A_S.y;
A_S.w;

A_S.G_Struct = GLOBAL_S;
GLOBAL_S.Curr_State = 0;
memcpy(data, &GLOBAL_S, sizeof(State_GLOBAL_Struct));
write(sockfd, &GLOBAL_S, sizeof(State_GLOBAL_Struct));
printf("x: %d\n",A_S.x);
for(A_S.i = 0; A_S.i <= 10; A_S.i++){
printf("loop 1a x: %d i: %d\n",A_S.x, A_S.i);
}

printf("Embeded in the code\n");if(1){printf("Inside if\n");}printf("After if\n");	
if(A_S.x <= 9){
printf("if 1a x: %d\n",A_S.x);
}
for(A_S.x = 0; A_S.x <= 10; A_S.x++){
printf("loop 2a x: %d\n",A_S.x);
}
goto state_C;


state_B:;
State_B_Struct B_S;
B_S.q;
B_S.x = 0;

B_S.G_Struct = GLOBAL_S;
GLOBAL_S.Curr_State = 1;
memcpy(data, &GLOBAL_S, sizeof(State_GLOBAL_Struct));
write(sockfd, &GLOBAL_S, sizeof(State_GLOBAL_Struct));
B_S.q = 9;
if(B_S.q <= 9){
printf("if 1b q: %d\n",B_S.q);
}
for(B_S.x = 2; B_S.x <= B_S.q; B_S.x++){
printf("loop 1b x: %d q: %d\n",B_S.x, B_S.q);
}
goto state_A;


state_C:;
State_C_Struct C_S;

C_S.G_Struct = GLOBAL_S;
GLOBAL_S.Curr_State = 2;
memcpy(data, &GLOBAL_S, sizeof(State_GLOBAL_Struct));
write(sockfd, &GLOBAL_S, sizeof(State_GLOBAL_Struct));
goto state_C;



}