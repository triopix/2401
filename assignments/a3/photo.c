// photo.c

#include <stdio.h>
#include "camera.h"
#include "photo.h"

// Helper function to get the value of a single bit from a packed array.
// This makes multiple other functions much simpler and cleaner.
static int get_bit(const unsigned char packed[], int index) {
    int byte_index = index / 8;
    int bit_in_byte = 7 - (index % 8); // Most significant bit is first
    // Shift the bit we want to the rightmost position and AND with 1 to get its value
    return (packed[byte_index] >> bit_in_byte) & 1;
}

/**
 * See photo.h for function documentation.
 */
int print_ascii(const unsigned char photo[], int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        return ERR_INVALID_PHOTO_SIZE;
    }

    for (int i = 0; i < rows * cols; ++i) {
        if (photo[i] == '1') {
            printf("*");
        } else if (photo[i] == '0') {
            printf(".");
        } else {
            // Invalid character found
            return ERR_UNKNOWN_CHARACTER;
        }

        // Check if we are at the end of a row
        if ((i + 1) % cols == 0) {
            printf("\n");
        }
    }
    return ERR_OK;
}

/**
 * See photo.h for function documentation.
 */
int pack_bits(unsigned char packed[], const unsigned char photo[], int num_chars) {
    if (num_chars <= 0) {
        return ERR_INVALID_PHOTO_SIZE;
    }
    
    int packed_index = 0;
    for (int i = 0; i < num_chars; i += 8) {
        unsigned char current_byte = 0; // Start with all bits as 0
        for (int j = 0; j < 8; ++j) {
            // If we haven't run out of characters
            if (i + j < num_chars) {
                if (photo[i + j] == '1') {
                    // Set the j-th most significant bit
                    // 1 << (7-j) creates a mask, e.g., 10000000, 01000000, etc.
                    current_byte |= (1 << (7 - j));
                } else if (photo[i + j] != '0') {
                    return ERR_UNKNOWN_CHARACTER;
                }
            }
        }
        packed[packed_index++] = current_byte;
    }
    return packed_index; // Return the number of bytes used
}

/**
 * See photo.h for function documentation.
 */
int print_packed_bits(const unsigned char packed[], int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        return ERR_INVALID_PHOTO_SIZE;
    }

    int total_pixels = rows * cols;
    for (int i = 0; i < total_pixels; ++i) {
        if (get_bit(packed, i)) { // Use our helper to check the bit
            printf("+");
        } else {
            printf("-");
        }

        if ((i + 1) % cols == 0) {
            printf("\n");
        }
    }
    return ERR_OK;
}


/**
 * See photo.h for function documentation.
 */
int rle_encode(unsigned char encoded_result[], const unsigned char packed[], int rows, int cols) {
    if (rows > 255 || cols > 255 || rows <= 0 || cols <= 0) {
        return ERR_RLE_LIMIT_EXCEEDED;
    }

    encoded_result[0] = (unsigned char)rows;
    encoded_result[1] = (unsigned char)cols;
    
    int total_pixels = rows * cols;
    if (total_pixels == 0) {
        return 2; // Only header bytes
    }

    int rle_index = 2;
    int pixel_index = 0;
    int current_color_is_black = 1; // RLE starts by counting black pixels (1-bits)

    while (pixel_index < total_pixels) {
        int count = 0;
        // Count the run of the current color
        while (pixel_index < total_pixels && get_bit(packed, pixel_index) == current_color_is_black) {
            count++;
            pixel_index++;
        }

        // Handle runs longer than 255, as per the specification
        while (count > 255) {
            encoded_result[rle_index++] = 255;
            encoded_result[rle_index++] = 0; // Zero of the next color
            count -= 255;
        }
        encoded_result[rle_index++] = (unsigned char)count;
        
        // Flip the color we are looking for
        current_color_is_black = !current_color_is_black;
    }

    return rle_index; // Total bytes used for RLE data
}

/**
 * See photo.h for function documentation.
 */
int print_rle(const unsigned char encoded[]) {
    int rows = encoded[0];
    int cols = encoded[1];

    if (rows <= 0 || cols <= 0) {
        return ERR_INVALID_PHOTO_SIZE;
    }

    int pixels_printed = 0;
    int current_color_is_black = 1;
    int encoded_index = 2;

    // Loop until we've printed all the pixels for the image
    while(pixels_printed < rows * cols){
        int count = encoded[encoded_index++];
        for(int i = 0; i < count; i++){
            if(current_color_is_black){
                printf("#");
            } else {
                printf(" "); // Use a space for white pixels
            }

            pixels_printed++;
            if(pixels_printed % cols == 0){
                printf("\n");
            }
        }
        // Alternate the color for the next run count
        current_color_is_black = !current_color_is_black;
    }
    return ERR_OK;
}