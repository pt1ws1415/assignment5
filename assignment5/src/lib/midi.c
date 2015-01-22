#include <midi.h>
#include <midi_events.h>

#include <length_quantity.h>
#include <swap_endianness.h>

#include <string.h>

#define MIDI_EVENT_FIRST  0x80
#define MIDI_EVENT_LAST   0xEF

#define MIDI_SYSEX_SINGLE 0xF0
#define MIDI_SYSEX_MULTI  0xF7
#define MIDI_META_EVENT   0xFF

#define MIDI_END_TRACK    0x2F

#define EVENT_HAS_SECOND_PARAM(EVENT) ((EVENT).type != MIDI_PROGRAM_CHANGE && (EVENT).type != MIDI_CHANNEL_PRESSURE)

/*----------------------------------------------------------------------*/

static void skip_sysex_event(midi_t *midi)
{
	int length;
	length = read_varlength_quantity(midi->file);
	// Seek forward from current position to skip "length" bytes
	fseek(midi->file, length, SEEK_CUR);
}

static int peek_meta_event(midi_t *midi)
{
	// Read and skip meta event type
	int eventType = fgetc(midi->file);
	// Evil hack: Both, meta and sysex have a length prefix, so reuse the code
	skip_sysex_event(midi);
	if (eventType == MIDI_END_TRACK)
		return MIDI_END_TRACK;
	return MIDI_SUCCESS;
}

static void read_midi_event(midi_t *midi, midi_event_t *event, unsigned char statusByte)
{
	/********************************************************/
	/* 5.I. Fill the passed event pointer accordingly.
	   Parse the type and channel, read the parameter(s) from file.
	   The first byte is already read and in "statusByte".
	   See: http://www.somascape.org/midi/tech/mfile.html#midi

	   Hint: You can use the EVENT_HAS_SECOND_PARAM macro
	   to determine how many parameters to read.
	*/

	/********************************************************/
}

// Skips the header of a new track
static int read_track_header(midi_t *midi)
{
	char trackIdentifier[4];
	uint32_t dummy_length;
	fread(trackIdentifier, sizeof(trackIdentifier), 1, midi->file);
	fread(&dummy_length, sizeof(dummy_length), 1, midi->file);
	if (strncmp(trackIdentifier, "MTrk", 4) != 0)
		return MIDI_UNSUPPORTED;
	return MIDI_SUCCESS;
}


// finds the next midi event, returns its statusByte
// will automatically skip to next track, if the current one finished
// returns MIDI_NO_EVENT in case of error (unknown format or end of file)
static int find_next_event(midi_t *midi, midi_event_t *nextEvent)
{
	int time;
	int nextEventType;
	do {
		time = read_varlength_quantity(midi->file);
		nextEventType = fgetc(midi->file);

		if (MIDI_EVENT_FIRST <= nextEventType && nextEventType <= MIDI_EVENT_LAST) {
			read_midi_event(midi, nextEvent, nextEventType);
			return MIDI_SUCCESS;
		} else if (nextEventType == MIDI_META_EVENT) {
			if (peek_meta_event(midi) == MIDI_END_TRACK && read_track_header(midi) != MIDI_SUCCESS)
				break;
		} else if (nextEventType == MIDI_SYSEX_SINGLE || nextEventType == MIDI_SYSEX_MULTI) {
			skip_sysex_event(midi);
		} else { // Unknown events
			break;
		}
	} while (!feof(midi->file));
	return MIDI_NO_EVENT;
}

/*----------------------------------------------------------------------*/

int midi_open(midi_t *midi, const char *filename)
{
	FILE *file = fopen(filename, "rb");
	if (!file) {
		return MIDI_NO_FILE;
	}
	midi->file = file;
	return midi_from_file(midi, file);
}

int midi_from_file(midi_t *midi, FILE *file)
{
	int status;
	if (midi->file != file) {
		midi->file = file;
		midi->close_on_finish = 0;
	} else {
		midi->close_on_finish = 1;
	}
	fread(&midi->header, sizeof(midi->header), 1, file);

// This works on gcc and clang.
// State your compiler and find some replacement, if it breaks for you
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	swap_endianness_32bit(&midi->header.chunklen);
	swap_endianness_16bit(&midi->header.format);
	swap_endianness_16bit(&midi->header.ntracks);
	swap_endianness_16bit(&midi->header.tickdiv);
#endif
	// Check that we parse format type 1 midi-file, or a single track type 0 file
	if (strncmp(midi->header.identifier, "MThd", 4) != 0
			|| !(midi->header.format == 1 ||
				(midi->header.format == 0 && midi->header.ntracks == 1))) {
		midi_close(midi);
		return MIDI_UNSUPPORTED;
	}

	status = read_track_header(midi);
	if (status != MIDI_SUCCESS)
		midi_close(midi);
	return status;
}

/********************************************************/
/* 5.II. Write a function midi_read_notes, that receives a
   midi_t-pointer, a void-pointer and a callback.

   That callback should be called on every NOTE_ON event on channel 0,
   receiving the current note and the void-pointer, which provides
   some user defined data

   Hint: You can use the find_next_event function, to iterate over
   the file.
*/

/********************************************************/

void midi_close(midi_t *midi)
{
	if (midi->close_on_finish)
		fclose(midi->file);
}

