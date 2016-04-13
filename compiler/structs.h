typedef struct __state_GLOBAL{int Curr_State;
int test;
int var1;
int var2;

} State_GLOBAL_Struct;

typedef struct __state_A{State_GLOBAL_Struct G_Struct;
int x, i;
char y;
double w;

} State_A_Struct;

typedef struct __state_B{State_GLOBAL_Struct G_Struct;
int q, p;

} State_B_Struct;

typedef struct __state_C{State_GLOBAL_Struct G_Struct;

} State_C_Struct;

