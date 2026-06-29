#ifndef BOOKING_H
#define BOOKING_H

struct Booking {
    char room_name[50];  
    char date[11];       
    int start_hour;      
    int end_hour;        
    char purpose[100];   
};

#endif