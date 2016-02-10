void* start_ptr = states[0];
State_GLOBAL_Struct GLOBAL_S;
unsigned char* data = malloc(sizeof(GLOBAL_S));
GLOBAL_S.test = 0;
GLOBAL_S.uwotm8 = 99;
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
A_S.x = 9;
A_S.i;
A_S.y;
A_S.w;
A_S.x = 10;
char* data_x = malloc(sizeof(A_S.x) + sizeof(int));
memcpy(data_x, get_position("x"), sizeof(int));
memcpy(&data_x[4], &A_S.x, sizeof(int));
write(sockfd, &data_x, (sizeof(A_S.x) + sizeof(int)));
A_S.i = 1;
char* data_i = malloc(sizeof(A_S.i) + sizeof(int));
memcpy(data_i, get_position("i"), sizeof(int));
memcpy(&data_i[4], &A_S.i, sizeof(int));
write(sockfd, &data_i, (sizeof(A_S.i) + sizeof(int)));
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

A_S.G_Struct = GLOBAL_S;
GLOBAL_S.Curr_State = 0;
memcpy(data, &GLOBAL_S, sizeof(State_GLOBAL_Struct));
write(sockfd, &GLOBAL_S, sizeof(State_GLOBAL_Struct));
goto state_C;


state_B:;
State_B_Struct B_S;
B_S.q;
B_S.x = 0;
B_S.q = 9;
char* data_q = malloc(sizeof(B_S.q) + sizeof(int));
memcpy(data_q, get_position("q"), sizeof(int));
memcpy(&data_q[4], &B_S.q, sizeof(int));
write(sockfd, &data_q, (sizeof(B_S.q) + sizeof(int)));
if(B_S.q <= 9){
printf("if 1b q: %d\n",B_S.q);
}
for(B_S.x = 2; B_S.x <= B_S.q; B_S.x++){
printf("loop 1b x: %d q: %d\n",B_S.x, B_S.q);
}

B_S.G_Struct = GLOBAL_S;
GLOBAL_S.Curr_State = 1;
memcpy(data, &GLOBAL_S, sizeof(State_GLOBAL_Struct));
write(sockfd, &GLOBAL_S, sizeof(State_GLOBAL_Struct));
goto state_A;


state_C:;
State_C_Struct C_S;

C_S.G_Struct = GLOBAL_S;
GLOBAL_S.Curr_State = 2;
memcpy(data, &GLOBAL_S, sizeof(State_GLOBAL_Struct));
write(sockfd, &GLOBAL_S, sizeof(State_GLOBAL_Struct));
goto state_C;



}