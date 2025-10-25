// main.c

#include <stdio.h>
#include "camera.h"
#include "photo.h"

int main(void) {
    // Arrays for storing photo data in different formats
    unsigned char ascii_photo[MAX_PHOTO_SIZE];
    unsigned char packed_photo[PACKED_PHOTO_SIZE];
    unsigned char rle_photo[ENCODED_PHOTO_SIZE];

    // Variables to store image dimensions
    int rows, cols;
    int size;
    int photo_count = 1;

    // Main loop: get and process photos until there are none left
    printf("--- Starting Photo Processing ---\n\n");
    while ((size = get_next_photo(ascii_photo, &rows, &cols)) > 0) {
        printf("==============================\n");
        printf("      Processing Photo %d\n", photo_count++);
        printf(" Dimensions: %d rows x %d cols\n", rows, cols);
        printf("==============================\n\n");

        // 1. Print the original ASCII photo
        printf("--- ASCII Photo ---\n");
        print_ascii(ascii_photo, rows, cols);
        printf("\n");

        // 2. Pack the bits
        int packed_size = pack_bits(packed_photo, ascii_photo, size);
        if (packed_size < 0) {
            printf("Error packing bits: %d\n", packed_size);
            continue; // Skip to next photo
        }
        
        // Optional: Test the packed bits
        int pack_errors = camera_test_packed(ascii_photo, packed_photo, rows, cols);
        if (pack_errors > 0) {
            printf("WARNING: camera_test_packed found %d incorrect bytes.\n\n", pack_errors);
        } else {
            printf("SUCCESS: camera_test_packed found no errors.\n\n");
        }

        // 3. Print the packed photo
        printf("--- Packed Bits Photo ---\n");
        print_packed_bits(packed_photo, rows, cols);
        printf("\n");


        // 4. Run-Length Encode the packed bits
        int rle_size = rle_encode(rle_photo, packed_photo, rows, cols);
        if (rle_size < 0) {
            printf("Error encoding RLE data: %d\n", rle_size);
            continue; // Skip to next photo
        }
        
        // // Optional: Test the RLE data
        // int rle_errors = camera_test_rle(packed_photo, rle_photo, rows, cols);
        // if (rle_errors > 0) {
        //     printf("WARNING: camera_test_rle found %d incorrect bytes.\n\n", rle_errors);
        // } else {
        //     printf("SUCCESS: camera_test_rle found no errors.\n\n");
        // }

        // 5. Print the RLE photo
        printf("--- RLE Photo ---\n");
        print_rle(rle_photo);
        printf("\n");
    }

    printf("--- All photos processed. ---\n");

    return 0;
}