#ifndef MIDI_H
#define MIDI_H

#include <stdio.h>
#include <stdint.h>

#define MIDI_SUCCESS       0
#define MIDI_NO_FILE       1
#define MIDI_UNSUPPORTED   2
#define MIDI_NO_EVENT      3

// Midi note equivalent of NOTE_C4 on Arduino
#define MIDI_NOTE_C4       60

// Array where a midi note is the index to a string of Arduino notes
extern const char *midi_notes[128];

typedef struct _midi_event {
	unsigned char type;
	unsigned char channel;
	unsigned char param1;
	unsigned char param2;
} midi_event_t;

typedef struct _midi {
	FILE *file;
	struct __attribute__((packed)) midi_header {
		char identifier[4];
		uint32_t chunklen;
		uint16_t format;
		uint16_t ntracks;
		uint16_t tickdiv;
	} header;
	uint32_t tracklen;
	int close_on_finish;
} midi_t;

// Open a file from name
extern int midi_open(midi_t *midi, const char *filename);

// Read a file from an open file handle
extern int midi_from_file(midi_t *midi, FILE *file);

// Close a midi file, when you created it with midi_open
extern void midi_close(midi_t *midi);

#endif
