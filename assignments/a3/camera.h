#ifndef CAMERA_H
#define CAMERA_H

#define MAX_PHOTO_SIZE 4096
#define PACKED_PHOTO_SIZE 512
#define ENCODED_PHOTO_SIZE 4096
#define SQ_PHOTO_SIZE 1026
/*
  Pulls the next photo from our simulated camera and returns an array of 
  ASCII characters representing the pixel colours.

  out: dest; An array of size at least MAX_PHOTO which will be populated 
            with the characters from the simulated photograph.
  out: rows; The address of an integer to store the number of rows in 
             picture that was taken.
  out: cols; The address of an integer to store the number of columns 
             in the picture that was taken.

  Return: Integer representing the number of characters in the photograph 
          (equivalent to rows * cols), 0 if no photo was returned 
          (indicating the end of the photographs)
    - Array `dest` is populated with characters,
    - Integers `rows` and `cols` are populated with the number of 
      rows and columns in the photo
*/
int get_next_photo(unsigned char dest[], int *rows, int *cols);

/* 
  These functions will print a message if they identify any incorrect values and return
  the number of bytes which were incorrect in the inputs (0 means no problems).

  camera_test_packed: Tests if your packed[] representation accurately packs photo[]
  camera_test_rle: Tests if your encoded[] representation accurately encodes packed[]; only valid if the previous test passed for packed[]
*/
int camera_test_packed(const unsigned char photo[], const unsigned char packed[], int rows, int cols);
int camera_test_rle(const unsigned char packed[], const unsigned char encoded[], int rows, int cols);

// For Side Quest, Described in Specification
int sq_next_photo(unsigned char photo[]);

#endif // CAMERA_H