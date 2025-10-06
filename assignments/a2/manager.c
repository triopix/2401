// manager.c

#include "defs.h"

/* ---- entry comparator -------------------------------------------
   Order: room name ASC, then type ASC by #define value, then timestamp ASC
   Returns <0 if a<b, >0 if a>b, 0 if equal.
----------------------------------------------------------------------------- */
int entry_cmp(const LogEntry *a, const LogEntry *b) {
    if (!a || !b || !a->room || !b->room) {
        return 0; // Cannot compare if data is invalid
    }

    // 1. Compare by room name in ascending order
    int room_cmp = strcmp(a->room->name, b->room->name);
    if (room_cmp != 0) {
        return room_cmp;
    }

    // 2. If room names are the same, compare by type in ascending order
    if (a->data.type < b->data.type) {
        return -1;
    }
    if (a->data.type > b->data.type) {
        return 1;
    }

    // 3. If types are also the same, compare by timestamp in ascending order
    if (a->timestamp < b->timestamp) {
        return -1;
    }
    if (a->timestamp > b->timestamp) {
        return 1;
    }

    return 0; // Entries are identical in sorting criteria
}

/* ---- rooms_find ------------------------------------------------------------
   Purpose: Find a room by name.
   Params:
    - rc (in): room collection
    - room_name (in): C-string room name
   Returns: pointer to room or NULL if not found or on error
----------------------------------------------------------------------------- */
Room* rooms_find(RoomCollection *rc, const char *room_name) {
    if (!rc || !room_name) {
        return NULL;
    }

    for (int i = 0; i < rc->size; ++i) {
        if (strcmp(rc->rooms[i].name, room_name) == 0) {
            return &rc->rooms[i]; // Return pointer to the found room
        }
    }

    return NULL; // Room not found
}

/* ---- rooms_add -------------------------------------------------------------
   Purpose: Add a room if it does not already exist.
   Params:
     - rc (in/out): room collection
     - room_name (in): C-string room name
   Returns: C_ERR_OK, C_ERR_NULL_PTR, C_ERR_DUPLICATE, C_ERR_FULL_ARRAY
----------------------------------------------------------------------------- */
int rooms_add(RoomCollection *rc, const char *room_name) {
    if (!rc || !room_name) {
        return C_ERR_NULL_PTR;
    }
    if (rc->size >= MAX_ARR) {
        return C_ERR_FULL_ARRAY;
    }
    if (rooms_find(rc, room_name) != NULL) {
        return C_ERR_DUPLICATE;
    }

    // Add the new room at the end of the array
    Room* new_room = &rc->rooms[rc->size];
    strncpy(new_room->name, room_name, MAX_STR - 1);
    new_room->name[MAX_STR - 1] = '\0'; // Ensure null-termination
    new_room->size = 0; // Initialize room's entry count

    rc->size++;

    return C_ERR_OK;
}

/* ---- entries_create -----------------------------------------------------------
   Purpose: Create a log entry and place it in the global entries (sorted),
            and attach a pointer to it in the owning room (append or sorted, either works)
   Params:
     - ec (in/out): entry collection (owns LogEntry storage)
     - room (in/out): room to attach entry to (must already exist)
     - type (in): TYPE_TEMP|TYPE_DB|TYPE_MOTION
     - value (in): union payload for reading
     - timestamp (in): simple int timestamp
   Returns: C_ERR_OK, C_ERR_NULL_PTR, C_ERR_FULL_ARRAY, C_ERR_INVALID
----------------------------------------------------------------------------- */
int entries_create(EntryCollection *ec, Room *room, int type, ReadingValue value, int timestamp) {
    if (!ec || !room) return C_ERR_NULL_PTR;
    if (ec->size >= MAX_ARR || room->size >= MAX_ARR) return C_ERR_FULL_ARRAY;
    if (type < TYPE_TEMP || type > TYPE_MOTION) return C_ERR_INVALID;

    // 1. Construct the new entry
    LogEntry new_entry;
    new_entry.room = room;
    new_entry.data.type = type;
    new_entry.data.value = value;
    new_entry.timestamp = timestamp;

    // 2. Find insertion position in the global EntryCollection
    int insert_pos = 0;
    while (insert_pos < ec->size && entry_cmp(&new_entry, &ec->entries[insert_pos]) > 0) {
        insert_pos++;
    }

    // 3. Shift existing entries to make space
    for (int i = ec->size; i > insert_pos; --i) {
        ec->entries[i] = ec->entries[i-1];
        // IMPORTANT: Update pointers in the associated room after shifting.
        // The room's entry pointer must now point to the new location.
        Room* moved_entry_room = ec->entries[i].room;
        for (int j = 0; j < moved_entry_room->size; ++j) {
            if (moved_entry_room->entries[j] == &ec->entries[i-1]) {
                moved_entry_room->entries[j] = &ec->entries[i];
                break;
            }
        }
    }

    // 4. Insert the new entry into the global collection
    ec->entries[insert_pos] = new_entry;
    LogEntry* new_entry_ptr = &ec->entries[insert_pos]; // Get a pointer to the newly stored entry
    ec->size++;
    
    // 5. Find insertion position for the pointer in the room's entry list
    int room_insert_pos = 0;
    while(room_insert_pos < room->size && entry_cmp(new_entry_ptr, room->entries[room_insert_pos]) > 0) {
        room_insert_pos++;
    }

    // 6. Shift pointers in the room to make space
    for (int i = room->size; i > room_insert_pos; --i) {
        room->entries[i] = room->entries[i-1];
    }

    // 7. Insert the new pointer into the room's list
    room->entries[room_insert_pos] = new_entry_ptr;
    room->size++;

    return C_ERR_OK;
}

/* ---- entry_print -----------------------------------------------------------
   Purpose: Print one entry in a formatted row.
   Params:
     - e (in): entry to print
   Returns: C_ERR_OK, C_ERR_NULL_PTR if e is NULL, C_ERR_INVALID if room is NULL
----------------------------------------------------------------------------- */
int entry_print(const LogEntry *e) {
    if (!e) return C_ERR_NULL_PTR;
    if (!e->room) return C_ERR_INVALID;

    // Print common data: Room and Timestamp, left-aligned
    printf("%-12s | %-10d | ", e->room->name, e->timestamp);

    // Print type-specific data
    switch (e->data.type) {
        case TYPE_TEMP:
            printf("%-10s | %.2f°C\n", "TEMP", e->data.value.temperature);
            break;
        case TYPE_DB:
            printf("%-10s | %d dB\n", "DB", e->data.value.decibels);
            break;
        case TYPE_MOTION:
            printf("%-10s | [%d,%d,%d]\n", "MOTION", e->data.value.motion[0], e->data.value.motion[1], e->data.value.motion[2]);
            break;
        default:
            printf("UNKNOWN TYPE\n");
    }
    return C_ERR_OK;
}

/* ---- room_print ------------------------------------------------------------
   Purpose: Print a room header and all of its entries (already sorted).
   Params:
     - r (in): room to print
   Returns: C_ERR_OK, C_ERR_NULL_PTR if r is NULL
----------------------------------------------------------------------------- */
int room_print(const Room *r) {
    if (!r) {
        return C_ERR_NULL_PTR;
    }

    printf("\n--- Room: %s (Entries: %d) ---\n", r->name, r->size);
    if (r->size > 0) {
       printf("-------------|------------|------------|------------------\n");
       printf("Room         | Timestamp  | Type       | Value\n");
       printf("-------------|------------|------------|------------------\n");
       for (int i = 0; i < r->size; ++i) {
           entry_print(r->entries[i]);
       }
       printf("-------------|------------|------------|------------------\n");
    } else {
        printf("No entries for this room.\n");
    }

    return C_ERR_OK;
}