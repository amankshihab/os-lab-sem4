#include <stdio.h>

struct mem_block {

	int size;
	int rem_size;
	int proc[10];
	int num_proc;
};
struct mem_block memory[10];

int main() {

	printf("\nEnter the no. of memory blocks:");
	int num_blocks;
	scanf("%d", &num_blocks);
	
	for (int i = 0; i < num_blocks; i++) {
	
		printf("\nEnter the size of the block:");
		scanf("%d", &memory[i].size);
		memory[i].rem_size = memory[i].size;
		
		memory[i].num_proc = 0;
	}
	
	int processes[10];
	
	printf("\nEnter the no. of processes:");
	int num_proc;
	scanf("%d", &num_proc);
	
	for (int i = 0; i < num_proc; i++) {
	
		printf("\nEnter the size of the process:");
		scanf("%d", &processes[i]);
	}
	
	int high = 0;
	for (int i = 0; i < num_blocks; i++) {
	
		if (high > memory[i].rem_size) {
		
			high = memory[i].rem_size;
		} 
	}
	
	for (int i = 0; i < num_proc; i++) {
	
		int best = high, best_index = -1;
	
		for (int j = 0; j < num_blocks; j++) {
		
			if (processes[i] < memory[j].rem_size && memory[j].rem_size >= best) {
			
				best_index = j;
				best = memory[best_index].rem_size;
			}
		}
		
		if (best_index != -1) {
		
			memory[best_index].proc[memory[best_index].num_proc++] = processes[i];
			
			memory[best_index].rem_size -= processes[i];
		}
	}
	
	for (int i = 0; i < num_blocks; i++) {
	
		printf("\nMemory block: %d", memory[i].size);
		printf("\nProcesses:\n");
		
		for (int j = 0; j < memory[i].num_proc; j++) {
			printf(" %d", memory[i].proc[j]);
		}

		printf("\n");
	}

	return 0;
}
