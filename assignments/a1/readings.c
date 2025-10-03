#include <stdio.h>

// Read `main.c` for information about these forward declarations.
// Do NOT define the functionality here, but instead, define them below.
#define MAX_ENTRIES 16
#define C_OK 0
#define C_ERR_EMPTY_ARRAY -1
#define C_ERR_INVALID_EMF -2
#define C_ERR_INVALID_ROOM -3
#define C_EXIT_CODE -1.0

// defining our min and max ranges for convenience
#define ROOM_MAX 13379999
#define ROOM_MIN 13300000
#define EMF_MIN 0.00
#define EMF_MAX 5.00

// key topic to understand is => "synchronized arrays"

// Do *not* place your function implementations right here; these are
// forward declarations, and are intended to tell the rest of the code
// that these functions will be found. It means we do not have to worry
// about the order that our functions are written in.
// You can use these "prototypes" or "signatures", and copy-paste them to
// write your functions below, similar to the broken "sort_entries" function.
int get_entries(int ids[], float readings[]);
int print_entries(int ids[], float readings[], int size);
int sort_entries(int ids[], float readings[], int size);
int find_max_index(float readings[], int size);
int invalid_room(int id);
int invalid_reading(float reading);

// function implementation below, as instructed
int get_entries(int ids[], float readings[]) {

    // number of elements entered (synchronous accross both arrays pair-wise)
    int count = 0;
    int id;
    float reading;

    while (count < MAX_ENTRIES) {
        // user input
        printf("Enter a Room ID and EMF (-1 -1 to quit): ");
        scanf("%d %f", &id, &reading);

        // Use integer comparison for the exit code, not float constant
        // C_EXIT_CODE
        if (id == -1 && (int)reading == -1) {
            break;
        }

        // seperate case checking
        if (invalid_room(id) != C_OK) {
            printf("Invalid Room ID: %d\n", id);
            continue;
        }
        if (invalid_reading(reading) != C_OK) {
            printf("Invalid EMF value: %f\n", reading);
            continue;
        }
        // at each index, initialize value for both arrays
        ids[count] = id;
        readings[count] = reading;
        count++; // increment
    }
    if (count >= MAX_ENTRIES) {
        printf(
            "Error: arrays are full and the user tries to add a new entry\n");
    }

    return count;
}

int print_entries(int ids[], float readings[], int size) {
    if (size <= 0) {
        return C_OK; // Nothing to print
    }

    printf("\nRoom ID    EMF\n");
    printf("---------- -----\n");
    for (int i = 0; i < size; i++) {
        printf("%-10d %.2f\n", ids[i], readings[i]);
    }
    printf("---------- -----\n");
    printf("Total Entries: %d\n", size);
    return C_OK;
}

int find_max_index(float readings[], int size) {
    if (size <= 0) {
        return C_ERR_EMPTY_ARRAY;
    }
    int max_idx = 0;
    for (int i = 1; i < size; i++) {
        if (readings[i] > readings[max_idx]) {
            max_idx = i;
        }
    }
    return max_idx;
}

int sort_entries(int ids[], float readings[], int size) {
    if (size <= 0) {
        return C_ERR_EMPTY_ARRAY;
    }

    int temp_ids[MAX_ENTRIES];
    float temp_readings[MAX_ENTRIES];

    // 1. Creatie deep copies
    for (int i = 0; i < size; i++) {
        temp_ids[i] = ids[i];
        temp_readings[i] = readings[i];
    }

    // Loopp over each position and find the max from the copies
    for (int i = 0; i < size; i++) {
        int max_idx = find_max_index(temp_readings, size);

        // case where find_max_index might return error
        if (max_idx < 0)
            return C_ERR_EMPTY_ARRAY;

        // Place found max value into the original array at current position
        ids[i] = temp_ids[max_idx];
        readings[i] = temp_readings[max_idx];

        // Mark the used value in the copy with a sentinel value
        temp_readings[max_idx] = -1.0f;
    }
    return C_OK;
}

// checking invalid room using ternary operator shortcut (from related java
// knowledge)
int invalid_room(int id) {
    return ((id >= ROOM_MIN) && (id <= ROOM_MAX)) ? C_OK : C_ERR_INVALID_ROOM;
}

// similar check to room (instead using our EMF pre-processor directives)
int invalid_reading(float reading) {
    return ((reading >= EMF_MIN) && (reading <= EMF_MAX)) ? C_OK
                                                          : C_ERR_INVALID_EMF;
}