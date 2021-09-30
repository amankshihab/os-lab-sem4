#include <stdio.h>

struct memory_block {

	int size;
	int remaining_size;
	
	int processes[10];
	int num_process;
};
struct memory_block memory[10];

int processes[10];

int main() {

	printf("\nEnter the no. of memory blocks:");
	int num_memblock;
	scanf("%d", &num_memblock);
	
	for (int i = 0; i < num_memblock; i++) {
	
		printf("\nEnter the size of the memory block:");
		scanf("%d", &memory[i].size);
		memory[i].remaining_size = memory[i].size;
		
		memory[i].num_process = 0;
	}
	
	printf("\nEnter the no. of processes:");
	int num_process;
	scanf("%d", &num_process);
	
	for (int i = 0; i < num_process; i++) {
	
		printf("\nEnter the size of the process:");
		scanf("%d", &processes[i]);
	}
	
	for (int i = 0; i < num_process; i++) {
	
		for (int j = 0; j < num_memblock; j++) {
		
			if (processes[i] <= memory[j].remaining_size) {
			
				memory[j].processes[memory[j].num_process] = processes[i];
				memory[j].remaining_size -= processes[i];
				memory[j].num_process += 1;
				
				break;
			}
		}
	}
	
	for (int i = 0; i < num_memblock; i++) {
	
		printf("\nThe size of block is: %d\n", memory[i].size);
		
		printf("Inside:");
		for (int j = 0; j < memory[i].num_process; j++) {
		
			printf(" %dkb", memory[i].processes[j]);
		}

		printf("\n");
	}

	return 0;
}
