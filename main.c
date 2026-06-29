#include <stdio.h>
#include "room.h"

int main() {
   
    struct Room campus_rooms[10];
    int room_count = 0; 

    FILE *file_ptr = fopen("rooms.txt", "r");

    
    if (file_ptr == NULL) {
        printf("Error: Could not open rooms.txt file!\n");
        return 1; 
    }

    while (fscanf(file_ptr, "%s %d %s %d %d", 
                  campus_rooms[room_count].name, 
                  &campus_rooms[room_count].capacity, 
                  campus_rooms[room_count].type, 
                  &campus_rooms[room_count].open_hour, 
                  &campus_rooms[room_count].close_hour) == 5) {
        
        room_count++; 
        
        
        if (room_count >= 10) {
            break;
        }
    }

    fclose(file_ptr);
    
    printf("--- Successfully Loaded Rooms from File ---\n");
    for (int i = 0; i < room_count; i++) {
        printf("Room %d: %s | Capacity: %d | Type: %s | Hours: %02d:00-%02d:00\n", 
               i + 1,
               campus_rooms[i].name, 
               campus_rooms[i].capacity, 
               campus_rooms[i].type, 
               campus_rooms[i].open_hour, 
               campus_rooms[i].close_hour);
    }

    return 0;
}