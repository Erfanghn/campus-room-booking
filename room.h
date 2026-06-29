#ifndef ROOM_H
#define ROOM_H

struct Room {
    char name[50];       
    int capacity;        
    char type[30];       
    int open_hour;       
    int close_hour;      
};

#endif