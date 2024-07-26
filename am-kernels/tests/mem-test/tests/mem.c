#include "trap.h"

int main() {
	int i, j, ans_idx = 0;
	for(i = 0; i < NR_DATA; i ++) {
		for(j = 0; j < NR_DATA; j ++) {
			check(add(test_data[i], test_data[j]) == ans[ans_idx ++]);
		}
		check(j == NR_DATA);
	}

	check(i == NR_DATA);

	return 0;
}
