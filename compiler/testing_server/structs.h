typedef struct __state_GLOBAL{int Curr_State;
int Prev_State;
int test;

} State_GLOBAL_Struct;

typedef struct __state_A{State_GLOBAL_Struct G_Struct;

} State_A_Struct;

typedef struct __state_B{State_GLOBAL_Struct G_Struct;

} State_B_Struct;

typedef struct __state_C{State_GLOBAL_Struct G_Struct;

} State_C_Struct;

