# **Assignment 1: Ghostly Data Entry in C**

## **Credits**

*   **Author:** Archisman Nath
*   **Student Number:** 101360479

## **Program Description**

This C program serves as a data entry and management tool for the Carleton University Ghost Hunters Society (CUGHS). It is designed to capture and process data from an "EMF Reader" which records paranormal electromagnetic fields.

The application prompts the user to enter pairs of data: a unique Room ID and its corresponding EMF reading. The entered data is validated, stored, and then displayed in both its original (unsorted) and sorted formats. The sorting is done in descending order based on the EMF reading, allowing the ghost hunters to easily identify rooms with the highest paranormal activity.

## **Core Features**

*   **Interactive Data Entry**: Prompts the user to enter Room IDs and EMF readings. The user can enter up to 16 entries or stop early by entering `-1 -1`.
*   **Input Validation**: The program validates each entry to ensure that:
    *   Room IDs are within the valid range of `13300000` to `13379999`.
    *   EMF readings are within the valid range of `0.00` to `5.00`.
    *   Informative error messages are shown for invalid data, prompting the user to try again.
*   **Synchronized Array Storage**: Uses two synchronized arrays to maintain the relationship between each Room ID and its EMF reading.
*   **Formatted Output**: Displays the collected data in a clean, aligned, and readable table format, both before and after sorting.
*   **Descending Sort**: Implements a sorting algorithm to reorder the entries based on the EMF reading, from highest to lowest.

## **Building and Running**

To compile and run this program, you will need the GCC compiler and a Unix-like terminal environment.

### **1. Compile the Program**

Navigate to the directory containing the source files (`main.c`, `readings.c`) and run the following command to compile the code. The `-Wall` flag is used to enable all standard compiler warnings.

```sh
gcc -Wall main.c readings.c -o a1
```

This command will link the two `.c` files and create a single executable file named `a1`.

### **2. Execute the Program**

Once compilation is successful, run the program with the following command:

```sh
./a1
```

The program will then start, and you can begin entering data as prompted.