// photo.h

#ifndef PHOTO_H
#define PHOTO_H

/*
    This file contains all of the forward declarations and definitions required by photos 
    that are NOT part of camera.o requirements, and should be included in each file that
    uses your photo functionality.
*/

// Define success and error codes for function return values
#define ERR_OK                   0
#define ERR_INVALID_PHOTO_SIZE  -1
#define ERR_UNKNOWN_CHARACTER   -2
#define ERR_RLE_LIMIT_EXCEEDED  -3 // For when rows/cols > 255

/**
 * @brief Prints an ASCII representation of a photo to the console.
 * '1' is printed as '*' and '0' as '.'.
 * @param photo The input array of ASCII '0's and '1's.
 * @param rows The number of rows in the image.
 * @param cols The number of columns in the image.
 * @return ERR_OK on success, or an error code on failure.
 */
int print_ascii(const unsigned char photo[], int rows, int cols);

/**
 * @brief Packs an array of ASCII '0's and '1's into a compact bit array.
 * 8 ASCII characters are packed into a single unsigned char.
 * @param packed The destination array for the packed bits.
 * @param photo The source array of ASCII characters.
 * @param num_chars The total number of characters in the photo array (rows * cols).
 * @return The number of bytes used in the packed array on success, or an error code.
 */
int pack_bits(unsigned char packed[], const unsigned char photo[], int num_chars);

/**
 * @brief Prints a bit-packed representation of a photo.
 * 1-bits are printed as '+' and 0-bits as '-'.
 * @param photo The packed bit array.
 * @param rows The number of rows in the image.
 * @param cols The number of columns in the image.
 * @return ERR_OK on success.
 */
int print_packed_bits(const unsigned char packed[], int rows, int cols);

/**
 * @brief Compresses a bit-packed photo array using Run-Length Encoding (RLE).
 * @param encoded_result The destination array for the RLE data.
 * @param packed The source packed bit array.
 * @param rows The number of rows in the image.
 * @param cols The number of columns in the image.
 * @return The number of bytes used in the RLE array on success, or an error code.
 */
int rle_encode(unsigned char encoded_result[], const unsigned char packed[], int rows, int cols);

/**
 * @brief Prints an image from its Run-Length Encoded representation.
 * 1-bits are printed as '#' and 0-bits as a space ' '.
 * @param encoded The source RLE data array.
 * @return ERR_OK on success.
 */
int print_rle(const unsigned char encoded[]);

// Only used for the sidequest. Uncomment if you are attempting the side quest.
// int print_sq_bits(const unsigned char photo[]);

#endif // PHOTO_H