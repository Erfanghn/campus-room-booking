# Campus Room Booking Simulator

this programming C project is a text-based application designed to help manage and book different rooms on a university campus. 

## What the Program Does So Far
*   **Organizes Data:** Uses custom structures (`struct`) to hold information about campus rooms and user bookings.
*   **Reads Files:** Automatically opens an external text file (`rooms.txt`) and loads the room data into the program.
*   **Uses Functions:** The code is cleanly split into small, separate functions instead of putting everything in one place.

## How the Input File Works (`rooms.txt`)
The program reads room details from a file named `rooms.txt`. Each line represents one room. To prevent code errors with spaces, underscores are used for room names:
`[Room_Name] [Capacity] [Room_Type] [Opening_Hour] [Closing_Hour]`

Example inside the file:
Classroom_A 30 Lecture 8 18

## How to Compile and Run the Code
1. Open your terminal or command prompt inside this project folder.
2. Compile the code by typing:
   ```bash
   gcc main.c -o simulator