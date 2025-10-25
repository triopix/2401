# **Assignment #3: An Efficient Camera**

## **Author Information**

*   **Name:** Archisman Nath
*   **Student Number:** 101360479

## **Program Description**

This C program is a data processing tool designed to demonstrate efficient data representation and compression techniques. The program simulates reading image data from an old, inefficient black-and-white camera and processes it through several stages to significantly reduce its storage footprint.

The core of the assignment involves heavy use of **bitwise operations** to manipulate data at the level of individual bits, rather than whole bytes. The program follows a three-stage pipeline:
1.  First, it reads images represented as wasteful ASCII characters ('0' and '1').
2.  Next, it performs **Bit Packing**, converting every eight ASCII characters into a single, compact byte. This achieves an 8x reduction in size.
3.  Finally, it applies **Run-Length Encoding (RLE)** to the packed bits, a compression algorithm that further reduces the size of images with repeating patterns of black or white pixels.

At each stage, the program prints a visual representation of the image to the console, allowing for clear verification of the data transformations.

## **Core Features**

*   **ASCII Photo Printing**: Reads the raw photo data (arrays of '0's and '1's) and renders a human-readable image using `.` for white pixels and `*` for black pixels.
*   **Bit Packing**: Implements a `pack_bits()` function that takes 8 bytes of ASCII data and packs them into a single byte. The implementation correctly places the first pixel in the most-significant bit (MSB) position as required.
*   **Packed Data Printing**: A function `print_packed_bits()` reads the compact bitstream and prints a representation of the image using `-` for white and `+` for black pixels, demonstrating that the packed data is correct.
*   **Run-Length Encoding (RLE)**: The `rle_encode()` function implements the RLE compression scheme. It correctly handles the specified format `[rows][cols][run_black][run_white]...` and includes logic to manage runs longer than 255 pixels.
*   **RLE Decompression Printing**: The `print_rle()` function reads the highly compressed RLE data and decompresses it on-the-fly to print the final image using a space for white pixels and `#` for black pixels.
*   **Modular and Documented Code**: The logic is separated into `photo.c` for implementations and `photo.h` for declarations, while `main.c` handles the high-level control flow. All functions are documented as per the assignment's code style requirements.

## **Building and Running**

To compile and run this program, you will need a C compiler like GCC and a Unix-like terminal environment. The provided `camera.o` object file must be in the same directory as the source files.

### **1. Compile the Program**

Navigate to the directory containing all the files (`main.c`, `photo.c`, `photo.h`, `camera.h`, `camera.o`) and run the following command to compile and link the code:

```sh
gcc -Wall main.c photo.c camera.o -o a3