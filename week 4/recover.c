#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int CHUNK_SIZE = 512;

int main(int argc, char *argv[])
{
    // Ensure correct number of command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover memory_card.raw\n");
        return 1;
    }

    // Open the raw memory card file
    FILE *rawCardFile = fopen(argv[1], "r");

    if (rawCardFile == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    // Allocate buffer to hold data read from the memory card
    typedef uint8_t BYTE;
    BYTE chunkBuffer[CHUNK_SIZE];

    // Initialize counter for the number of JPEG images found
    int jpegCount = 0;

    // Allocate memory to store the file name for each image
    char *imageFilename = malloc(8 * sizeof(char));

    // Pointer for the output JPEG file
    FILE *currentImage = NULL;

    // Read through the memory card, processing each 512-byte block
    while (fread(chunkBuffer, 1, CHUNK_SIZE, rawCardFile) == CHUNK_SIZE)
    {
        // Check if this block marks the start of a new JPEG image
        if (chunkBuffer[0] == 0xFF && chunkBuffer[1] == 0xD8 && chunkBuffer[2] == 0xFF &&
            (chunkBuffer[3] & 0xF0) == 0xE0)
        {
            // If it's the first JPEG found, begin writing to the first file (e.g., 000.jpg)
            if (jpegCount == 0)
            {
                sprintf(imageFilename, "%03i.jpg", jpegCount);
                currentImage = fopen(imageFilename, "w");
                fwrite(chunkBuffer, 1, CHUNK_SIZE, currentImage);
                jpegCount++;
            }
            else
            {
                // If another JPEG is found, close the current image and start a new file
                fclose(currentImage);
                sprintf(imageFilename, "%03i.jpg", jpegCount);
                currentImage = fopen(imageFilename, "w");
                fwrite(chunkBuffer, 1, CHUNK_SIZE, currentImage);
                jpegCount++;
            }
        }
        // If it's not the start of a new JPEG, continue writing to the current image file
        else if (jpegCount > 0)
        {
            fwrite(chunkBuffer, 1, CHUNK_SIZE, currentImage);
        }
    }

    // Clean up: close the remaining files and free allocated memory
    free(imageFilename);
    fclose(rawCardFile);
    fclose(currentImage);
}
