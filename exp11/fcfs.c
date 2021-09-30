#include <stdio.h>
#include <stdlib.h>

int main() {

	printf("\nEnter current position of disk:");
	int curr_pos;
	scanf("%d", &curr_pos);
	
	printf("\nEnter the no. of tracks:");
	int num_tracks;
	scanf("%d", &num_tracks);
	
	int sum = 0;
	
	printf("\nEnter the tracks:");
	int tracks[num_tracks];
	for (int i = 0; i < num_tracks; i++) {
	
		scanf("%d", &tracks[i]);
	}
	
	int curr = curr_pos;
	
	for (int i = 0; i < num_tracks; i++) {
	
		sum += abs(tracks[i]-curr);
	
		curr = tracks[i];
	}
	
	printf("\nSeek time is : %d\n", sum+2);

	return 0;
}
