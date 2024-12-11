#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Size of the WAV header (44 bytes)
const int WAV_HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Ensure correct number of arguments are passed
    if (argc != 4)
    {
        printf("Usage: ./adjust_volume input.wav output.wav multiplier\n");
        return 1;
    }

    // Open the input and output files, and determine the volume adjustment factor
    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL)
    {
        printf("Error: Could not open input file.\n");
        return 1;
    }

    FILE *outputFile = fopen(argv[2], "w");
    if (outputFile == NULL)
    {
        printf("Error: Could not open output file.\n");
        fclose(inputFile); // Close the input file before exiting
        return 1;
    }

    float volumeMultiplier = atof(argv[3]);

    // Copy the WAV header from input to output
    uint8_t headerBuffer[WAV_HEADER_SIZE];

    fread(headerBuffer, WAV_HEADER_SIZE, 1, inputFile);
    fwrite(headerBuffer, WAV_HEADER_SIZE, 1, outputFile);

    // Read the audio samples, apply the volume adjustment, and write to output
    int16_t sampleData;

    while (fread(&sampleData, sizeof(int16_t), 1, inputFile))
    {
        // Adjust the sample volume
        sampleData *= volumeMultiplier;
        fwrite(&sampleData, sizeof(int16_t), 1, outputFile);
    }

    // Close the opened files
    fclose(inputFile);
    fclose(outputFile);
}
