#include <stdio.h>
#include <string.h>
#include "room.h"

int load_rooms_from_file(struct Room rooms_array[], int max_limit) {
    int count = 0;
    FILE *file_ptr = fopen("rooms.txt", "r");
    
    if (file_ptr == NULL) {
        printf("[System Error]: Could not open rooms.txt file!\n");
        return 0;
    }

    while (fscanf(file_ptr, "%s %d %s %d %d", 
                  rooms_array[count].name, 
                  &rooms_array[count].capacity, 
                  rooms_array[count].type, 
                  &rooms_array[count].open_hour, 
                  &rooms_array[count].close_hour) == 5) {
        
        count++;
        if (count >= max_limit) {
            break;
        }
    }

    fclose(file_ptr);
    return count;
}

void search_room(struct Room rooms_array[], int room_count) {
    char target_name[50];
    int found = 0;

    printf("\nEnter the room name to search for: ");
    scanf("%s", target_name);

    for (int i = 0; i < room_count; i++) {
        if (strcmp(target_name, rooms_array[i].name) == 0) {
            printf("\n--- Room Found! ---\n");
            printf("Name: %s\n", rooms_array[i].name);
            printf("Capacity: %d seats\n", rooms_array[i].capacity);
            printf("Type: %s\n", rooms_array[i].type);
            printf("Operating Hours: %02d:00 to %02d:00\n", rooms_array[i].open_hour, rooms_array[i].close_hour);
            found = 1;
            break;
        }
    }
    if (found == 0) {
        printf("\nError: Room '%s' not found in the system.\n", target_name);
    }
}

void create_booking(struct Room rooms_array[], int room_count, struct Booking bookings_array[], int *booking_count, int max_bookings) {
    if (*booking_count >= max_bookings) {
        printf("\nError: Booking system memory is full.\n");
        return;
    }

    char target_room[50];
    char input_date[15];
    int start = 0, end = 0;
    int room_index = -1;

    printf("\nEnter room name for the booking: ");
    scanf("%s", target_room);

    for (int i = 0; i < room_count; i++) {
        if (strcmp(target_room, rooms_array[i].name) == 0) {
            room_index = i;
            break;
        }
    }

    if (room_index == -1) {
        printf("Error: Room '%s' does not exist.\n", target_room);
        return;
    }

    printf("Enter date (DD/MM/YYYY): ");
    scanf("%s", input_date);
    printf("Enter start hour (0-23): ");
    scanf("%d", &start);
    printf("Enter end hour (0-23): ");
    scanf("%d", &end);

    if (start >= end) {
        printf("Error: Start hour must be earlier than end hour.\n");
        return;
    }

    if (start < rooms_array[room_index].open_hour || end > rooms_array[room_index].close_hour) {
        printf("Error: Room operating hours are %02d:00 to %02d:00.\n", 
               rooms_array[room_index].open_hour, rooms_array[room_index].close_hour);
        return;
    }

    for (int i = 0; i < *booking_count; i++) {
        if (strcmp(bookings_array[i].room_name, target_room) == 0 && strcmp(bookings_array[i].date, input_date) == 0) {
            if ((start >= bookings_array[i].start_hour && start < bookings_array[i].end_hour) ||
                (end > bookings_array[i].start_hour && end <= bookings_array[i].end_hour) ||
                (start <= bookings_array[i].start_hour && end >= bookings_array[i].end_hour)) {
                printf("Error: Booking conflict detected! This slot overlaps with an existing booking.\n");
                return;
            }
        }
    }

    strcpy(bookings_array[*booking_count].room_name, target_room);
    strcpy(bookings_array[*booking_count].date, input_date);
    bookings_array[*booking_count].start_hour = start;
    bookings_array[*booking_count].end_hour = end;

    (*booking_count)++;
    printf("\nSuccess: Booking recorded successfully!\n");
}

void show_bookings(struct Booking bookings_array[], int booking_count) {
    printf("\n--- Existing Bookings ---\n");
    if (booking_count == 0) {
        printf("No bookings currently scheduled.\n");
        return;
    }
    for (int i = 0; i < booking_count; i++) {
        printf("Booking %d: Room: %s | Date: %s | Time: %02d:00-%02d:00\n", 
               i + 1, bookings_array[i].room_name, bookings_array[i].date, bookings_array[i].start_hour, bookings_array[i].end_hour);
    }
}

int main() {
    struct Room campus_rooms[10];
    struct Booking campus_bookings[50];
    int room_count = load_rooms_from_file(campus_rooms, 10);
    int booking_count = 0;
    int choice = 0;

    while (choice != 5) {
        printf("\n=== Campus Room Booking Menu ===\n");
        printf("1. List all rooms\n");
        printf("2. Search for a room\n");
        printf("3. Create a booking\n");
        printf("4. Show existing bookings\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("\n--- All Rooms ---\n");
            if (room_count == 0) {
                printf("[Notice]: Zero rooms were loaded. Check rooms.txt file contents.\n");
            } else {
                for (int i = 0; i < room_count; i++) {
                    printf("Room %d: %s | Capacity: %d | Hours: %02d:00-%02d:00\n", 
                           i + 1, campus_rooms[i].name, campus_rooms[i].capacity, campus_rooms[i].open_hour, campus_rooms[i].close_hour);
                }
            }
        } 
        else if (choice == 2) {
            search_room(campus_rooms, room_count);
        } 
        else if (choice == 3) {
            create_booking(campus_rooms, room_count, campus_bookings, &booking_count, 50);
        } 
        else if (choice == 4) {
            show_bookings(campus_bookings, booking_count);
        } 
        else if (choice != 5) {
            printf("\nInvalid choice. Try again.\n");
        }
    }
    
    printf("\nExiting program safely. Goodbye!\n");
    return 0;
}