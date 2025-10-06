// main.c

#include "defs.h"
#include <stdio.h>

// Static declares that this function can only be found in this file and not during linking
static void print_menu(int* choice);
static void read_string(char* buffer, int size);

// Forward declarations for menu handler functions
static void handle_add_room(RoomCollection *rc);
static void handle_add_entry(RoomCollection *rc, EntryCollection *ec);
static void handle_print_entries(const EntryCollection *ec);
static void handle_print_rooms(const RoomCollection *rc);


int main(void) {
  RoomCollection  rooms   = { .size = 0 };
  EntryCollection entries = { .size = 0 };
  int choice = -1;

  while (choice != 0) {
    print_menu(&choice);
    switch (choice) {
      case 1: // Load sample data
        load_sample(&rooms, &entries);
        printf("Sample data loaded.\n");
        break;
      case 2: // Print entries
        handle_print_entries(&entries);
        break;
      case 3: // Print rooms
        handle_print_rooms(&rooms);
        break;
      case 4: // Add room
        handle_add_room(&rooms);
        break;
      case 5: // Add entry
        handle_add_entry(&rooms, &entries);
        break;
      case 6: // Test order
        loader_test_order(&entries, 1);
        break;
      case 7: // Test room entries
        loader_test_rooms(&entries, &rooms, 1);
        break;
      case 0: // Exit
        break;
      default:
        printf("Invalid choice.\n");
    }
  }

  printf("Exiting program.\n");
  return 0;
}

// Handler for printing all log entries
void handle_print_entries(const EntryCollection *ec) {
    printf("\n--- All Log Entries (%d) ---\n", ec->size);
    printf("-------------|------------|------------|------------------\n");
    printf("Room         | Timestamp  | Type       | Value\n");
    printf("-------------|------------|------------|------------------\n");
    for (int i = 0; i < ec->size; ++i) {
        entry_print(&ec->entries[i]);
    }
    printf("-------------|------------|------------|------------------\n");
}

// Handler for printing all rooms and their entries
void handle_print_rooms(const RoomCollection *rc) {
    printf("\n--- Printing All Rooms ---\n");
    for (int i = 0; i < rc->size; ++i) {
        room_print(&rc->rooms[i]);
    }
}

// Handler for adding a new room
void handle_add_room(RoomCollection *rc) {
    char name_buffer[MAX_STR];
    printf("Enter room name: ");
    read_string(name_buffer, MAX_STR);

    int result = rooms_add(rc, name_buffer);
    if (result == C_ERR_OK) {
        printf("Room '%s' added successfully.\n", name_buffer);
    } else if (result == C_ERR_DUPLICATE) {
        printf("Error: Room '%s' already exists.\n", name_buffer);
    } else if (result == C_ERR_FULL_ARRAY) {
        printf("Error: Room collection is full.\n");
    } else {
        printf("An unknown error occurred.\n");
    }
}

// Handler for adding a new log entry
void handle_add_entry(RoomCollection *rc, EntryCollection *ec) {
    char name_buffer[MAX_STR];
    printf("Enter room name for the new entry: ");
    read_string(name_buffer, MAX_STR);
    
    Room* room = rooms_find(rc, name_buffer);
    if (!room) {
        printf("Error: Room '%s' not found.\n", name_buffer);
        return;
    }

    int type, timestamp;
    ReadingValue value;
    
    printf("Enter entry type (1-TEMP, 2-DB, 3-MOTION): ");
    scanf("%d", &type);
    while (getchar() != '\n'); // Clear buffer

    printf("Enter timestamp (integer): ");
    scanf("%d", &timestamp);
    while (getchar() != '\n'); // Clear buffer
    
    switch (type) {
        case TYPE_TEMP:
            printf("Enter temperature: ");
            scanf("%f", &value.temperature);
            while (getchar() != '\n');
            break;
        case TYPE_DB:
            printf("Enter decibels: ");
            scanf("%d", &value.decibels);
            while (getchar() != '\n');
            break;
        case TYPE_MOTION:
            printf("Enter motion values (left forward right), e.g., 1 0 1: ");
            scanf("%hhu %hhu %hhu", &value.motion[0], &value.motion[1], &value.motion[2]);
            while (getchar() != '\n');
            break;
        default:
            printf("Invalid type entered.\n");
            return;
    }
    
    int result = entries_create(ec, room, type, value, timestamp);
    if (result == C_ERR_OK) {
        printf("Entry added successfully.\n");
    } else if (result == C_ERR_FULL_ARRAY) {
        printf("Error: A collection is full, cannot add entry.\n");
    } else {
        printf("An unknown error occurred while adding entry.\n");
    }
}


// Prints the main menu and gets user selection
void print_menu(int* choice) {
  int c = -1;
  int rc = 0;
  const int num_options = 7;

  printf("\nMAIN MENU\n");
  printf("  (1) Load sample data\n");
  printf("  (2) Print entries\n");
  printf("  (3) Print rooms\n");
  printf("  (4) Add room\n");
  printf("  (5) Add entry\n");
  printf("  (6) Test order\n");
  printf("  (7) Test room entries\n");
  printf("  (0) Exit\n\n");

  do {
    printf("Please enter a valid selection: ");
    rc = scanf("%d", &c);
    while (getchar() != '\n'); // Clear the input buffer
  } while (rc < 1 || c < 0 || c > num_options);

  *choice = c;
}

// Safely reads a line of text from standard input, removes the newline.
void read_string(char* buffer, int size) {
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = 0; // Find and remove trailing newline
}