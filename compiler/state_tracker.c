#include <stdlib.h>

typedef enum states_tracker{state_A,
	state_B,
};

void* states[] = {&&state_A, &&state_B};
