# **Assignment 2: Structured Device Information**

## **Author Information**

- **Name:** Archisman Nath
- **Student Number:** 101360479

## **Program Description**

This program is a command-line data management tool developed in C for the Carleton University Ghost Hunters Society (CUGHS). It expands upon the simple data entry of the first assignment by introducing robust data structures to handle multiple types of paranormal sensor readings across various locations.

The application uses `structs`, `unions`, and `pointers` to manage collections of rooms and sensor log entries. Data is kept in a sorted state automatically upon insertion, ordered first by room name (alphabetically), then by sensor type, and finally by timestamp. The user interacts with the system through a menu-driven interface to add new rooms, log new sensor data, print comprehensive reports, and load sample data for testing purposes.

A key feature of the implementation is the sorted insertion algorithm which not only places new data in the correct location but also carefully updates all relevant pointers in the data model. This ensures data integrity and consistency, which is critical when an entry stored in one array is referenced by pointers in another.

## **Core Features**

- **Menu-Driven Interface**: Provides a user-friendly menu to navigate the program's functionalities.
- **Room Management**: Allows users to add new rooms by name. The system prevents the creation of duplicate rooms.
- **Multi-Type Data Logging**: Supports three distinct types of sensor readings using a `union`:
  - `TEMP`: Temperature readings in degrees Celsius.
  - `DB`: Sound level readings in decibels.
  - `MOTION`: Motion sensor data representing detection in three zones.
- **Sorted Insertion**: Automatically inserts new log entries into a global collection in sorted order (Room -> Type -> Timestamp), ensuring data is always organized.
- **Pointer-Based Data Association**: Rooms maintain a list of pointers to their respective log entries, demonstrating efficient data association without duplicating the entry data itself.
- **Formatted Printing**: Offers options to print either a complete list of all sorted entries or a detailed breakdown of entries grouped by room.
- **Sample Data Loader**: Includes functionality to pre-populate the system with sample data for quick testing and demonstration, using the provided `loader.o` object file.

## **Building and Running**

To compile and run this program, you will need a C compiler like GCC and a Unix-like terminal environment. The provided `loader.o` file is required for linking.

### **1. Compile the Program**

Navigate to the directory containing the source files (`main.c`, `manager.c`, `defs.h`) and the object file (`loader.o`). Run the following command to compile and link the code:

```sh
gcc -Wall main.c manager.c loader.o -o a2
```
