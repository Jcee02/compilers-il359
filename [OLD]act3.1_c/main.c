/* Standard I/O operations */
#include <stdio.h>
/* String manipulation functions */
#include <string.h>
/* Boolean type support */
#include <stdbool.h>
/* POSIX operating system API */
#include <unistd.h>
/* Standard library functions */
#include <stdlib.h>

/* Maximum number of notes that can be processed in a sequence */
#define MAX_NOTES 12

/* Predefined major scales in Western music
* Each row represents a different major scale starting with its root note
* Includes common major scales: C, A, D, E, F, G, and B major
*/
const char *major_scales[][MAX_NOTES] = {
    {"C", "D", "E", "F", "G", "A", "B"},      /* C major scale */
    {"A", "B", "C#", "D", "E", "F#", "G#"},   /* A major scale */
    {"D", "E", "F#", "G", "A", "B", "C#"},    /* D major scale */
    {"E", "F#", "G#", "A", "B", "C#", "D#"},  /* E major scale */
    {"F", "G", "A", "Bb", "C", "D", "E"},     /* F major scale */
    {"G", "A", "B", "C", "D", "E", "F#"},     /* G major scale */
    {"B", "C#", "D#", "E", "F#", "G#", "A#"}  /* B major scale */
};

/* Predefined natural minor scales in Western music
* Each row represents a different minor scale starting with its root note
* Includes common minor scales: A, C, D, E, F, G, and B minor
*/
const char *minor_scales[][MAX_NOTES] = {
    {"A", "B", "C", "D", "E", "F", "G"},      /* A minor scale */
    {"C", "D", "Eb", "F", "G", "Ab", "Bb"},   /* C minor scale */
    {"D", "E", "F", "G", "A", "Bb", "C"},     /* D minor scale */
    {"E", "F#", "G", "A", "B", "C", "D"},     /* E minor scale */
    {"F", "G", "Ab", "Bb", "C", "Db", "Eb"},  /* F minor scale */
    {"G", "A", "Bb", "C", "D", "Eb", "F"},    /* G minor scale */
    {"B", "C#", "D", "E", "F#", "G", "A"}     /* B minor scale */
};

/* Checks if a given note exists within a specific scale
* @param note: The note to check
* @param scale: Array containing the notes of the scale
* @param size: Number of notes in the scale
* @return: true if the note is found in the scale, false otherwise
*/
bool is_note_in_scale(const char *note, const char *scale[], int size) {
    /* Iterate through each note in the scale */
    for (int i = 0; i < size; i++) {
        /* Compare the given note with current scale note */
        if (strcmp(note, scale[i]) == 0) {
            return true;
        }
    }
    return false;
}

/* Validates if a sequence of notes belongs to a specified scale
* @param key: The root note of the scale (e.g., "C", "D", etc.)
* @param scale_type: The type of scale ("mayor" or "menor")
* @param sequence: Space-separated string of notes to validate
*/
void validate_sequence(const char *key, const char *scale_type, char *sequence) {
    const char **scale = NULL;      /* Pointer to the selected scale */
    int scale_size = 7;             /* Number of notes in a standard scale */
    char *notes[MAX_NOTES];         /* Array to store individual notes from the sequence */
    int num_notes = 0;              /* Counter for number of notes in the sequence */

    /* Split the input sequence into individual notes using space as delimiter */
    char *token = strtok(sequence, " ");
    while (token != NULL && num_notes < MAX_NOTES) {
        /* Store each note in the notes array */
        notes[num_notes++] = token;
        /* Get next note from the sequence */
        token = strtok(NULL, " ");
    }

    /* Find the matching scale based on the key and scale type */
    for (int i = 0; i < 7; i++) {
        /* Check if the key matches a major scale and scale type is "mayor" */
        if (strcmp(key, major_scales[i][0]) == 0 && strcmp(scale_type, "mayor") == 0) {
            scale = major_scales[i];
            break;
        }
        /* Check if the key matches a minor scale and scale type is "menor" */
        if (strcmp(key, minor_scales[i][0]) == 0 && strcmp(scale_type, "menor") == 0) {
            scale = minor_scales[i];
            break;
        }
    }

    if (scale == NULL) {
        printf("Tonalidad no valida.\n");
        return;
    }

    for (int i = 0; i < num_notes; i++) {
        if (!is_note_in_scale(notes[i], scale, scale_size)) {
            printf("Secuencia invalida en %s %s.\n", key, scale_type);
            return;
        }
    }
    printf("Secuencia valida en %s %s.\n", key, scale_type);
}

/* Main program entry point
* Processes command line arguments and initiates scale validation
*/
int main(int argc, char *argv[]) {
    char *key = NULL;         /* Root note of the scale */
    char *scale_type = NULL;  /* Type of scale (mayor/menor) */
    char *sequence = NULL;    /* Sequence of notes to validate */
    int opt;                  /* Store current command line option */

    /* Parse command line options:
    * -k: key (tonalidad)
    * -s: scale type (mayor/menor)
    * -n: note sequence
    */
    while ((opt = getopt(argc, argv, "k:s:n:")) != -1) {
        switch (opt) {
            case 'k':  /* Key option */
                key = optarg;
                break;
            case 's':  /* Scale type option */
                scale_type = optarg;
                break;
            case 'n':  /* Note sequence option */
                sequence = optarg;
                break;
            default:   /* Invalid option */
                fprintf(stderr, "Uso: %s -k <tonalidad> -s <mayor|menor> -n \"nota1 nota2 ...\"\n", argv[0]);
                return 1;
        }
    }

    if (!key || !scale_type || !sequence) {
        fprintf(stderr, "Faltan argumentos. Uso: %s -k <tonalidad> -s <mayor|menor> -n \"nota1 nota2 ...\"\n", argv[0]);
        return 1;
    }

    validate_sequence(key, scale_type, sequence);

    return 0;
}
