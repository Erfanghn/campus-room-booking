#include <stdio.h>
#include "room.h"       
#include "booking.h"

int main() {
    struct Room test_room = {"Classroom A", 30, "Lecture", 8, 18};

    struct Booking test_booking = {"Classroom A", "2026-06-30", 10, 12, "Data Analysis Lecture"};

    printf("Campus Room Booking Simulator Initialized!\n");
    printf("--- Testing Data Structures ---\n");
    printf("Loaded Room: %s (Capacity: %d, Type: %s)\n", test_room.name, test_room.capacity, test_room.type);
    printf("Test Booking: Room %s on %s from %d:00 to %d:00\n", test_booking.room_name, test_booking.date, test_booking.start_hour, test_booking.end_hour);

    return 0;
}