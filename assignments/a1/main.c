#include <stdio.h>

// best practice (instead of copy-pasting everything)
// #include<readings.h>

// These are defined values.
// They do not reserve memory like a variable.
// Instead, the first phase of building - "pre-processing"
// Will essentially find-and-replace with what is written to the right.
// You should define some yourself to avoid "magic numbers",
// unchanging numbers that might need explanation or appear multiple times.
// It's a bit like commenting the value.
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

// These are "forward declarations".
// It tells the rest of the code to expect to find a function
// that works like this somewhere once we compile and link our code.
// We will NOT put the body of the function here, to keep things clean.
// Instead, we will leave this forward declaration untouched,
// and define the functions in another file: `readings.c`.
// These are like promises; "When I link other files, you'll find them"
int get_entries(int ids[], float readings[]);
int print_entries(int ids[], float readings[], int size);
int sort_entries(int ids[], float readings[], int size);
int find_max_index(float readings[], int size);
int invalid_room(int id);
int invalid_reading(float reading);

// compiling using "gcc -Wall main.c readings.c -o a1" allows us to have both
// files interact with each other seamlessly which makes it possible for the
// main file to read the implementation details for readings.c

int main(void) {
    // Define variables and call the functions from readings.c here
    int room_ids[MAX_ENTRIES];
    float emf_readings[MAX_ENTRIES];
    int num_entries;

    // Get user input and store the number of valid entries
    num_entries = get_entries(room_ids, emf_readings);

    // Print the unsorted data
    print_entries(room_ids, emf_readings, num_entries);

    // Sort the data in descending order based on EMF reading
    sort_entries(room_ids, emf_readings, num_entries);

    // Print the sorted data
    print_entries(room_ids, emf_readings, num_entries);

    return 0;
}