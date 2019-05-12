/*
Copyright 2019 Alex Nadzharov

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include "stdlib.h"
#include "math.h"
#include "stdio.h"

// -------------------- Data Types --------------------

typedef unsigned char MIDIByte;

inline static int MIDIByteInRange(MIDIByte v, MIDIByte min, MIDIByte max)
{
    return (v >= min) && (v < max);
};

// ---

struct MIDINote {
    MIDIByte pitch;
    MIDIByte velocity;
    MIDIByte channel;
};

inline static short int MIDINoteEquals(struct MIDINote a, struct MIDINote b)
{
    return (a.pitch == b.pitch) && (a.velocity == b.velocity) && (a.channel == b.channel);
};

inline static void PrintMIDINote(struct MIDINote n)
{
    printf("[channel: %i pitch: %i velocity %i]", n.channel, n.pitch, n.velocity);
}

// ---

struct MIDIControlChange {
    MIDIByte cc;
    MIDIByte value;
    MIDIByte channel;
};

inline static short int MIDIControlChangeEquals(struct MIDIControlChange a, struct MIDIControlChange b)
{
    return (a.cc == b.cc) && (a.value == b.value) && (a.channel == b.channel);
};

inline static void PrintMIDIControlChange(struct MIDIControlChange n)
{
    printf("[channel: %i CC: %i value %i]", n.channel, n.cc, n.value);
}

// ---

struct MIDIPolyKeyPressure {
    MIDIByte key;
    MIDIByte value;
    MIDIByte channel;
};

inline static short int MIDIPolyKeyPressureEquals(struct MIDIPolyKeyPressure a, struct MIDIPolyKeyPressure b)
{
    return (a.key == b.key) && (a.value == b.value) && (a.channel == b.channel);
};

inline static void PrintMIDIPolyKeyPressure(struct MIDIPolyKeyPressure n)
{
    printf("[channel: %i key: %i value %i]", n.channel, n.key, n.value);
}

// ---

struct MIDIProgramChange {
    MIDIByte value;
    MIDIByte channel;
};

inline static short int MIDIProgramChangeEquals(struct MIDIProgramChange a, struct MIDIProgramChange b)
{
    return (a.value == b.value) && (a.channel == b.channel);
};

inline static void PrintMIDIProgramChange(struct MIDIProgramChange n)
{
    printf("[channel: %i value %i]", n.channel, n.value);
}

// ---

struct MIDIAfterTouch {
    MIDIByte value;
    MIDIByte channel;
};

inline static short int MIDIAfterTouchEquals(struct MIDIAfterTouch a, struct MIDIAfterTouch b)
{
    return (a.value == b.value) && (a.channel == b.channel);
};

inline static void PrintMIDIAfterTouch(struct MIDIAfterTouch n)
{
    printf("[channel: %i value %i]", n.channel, n.value);
}

// ---

struct MIDIPitchBend {
    unsigned int value;
    MIDIByte channel;
};

inline static short int MIDIPitchBendEquals(struct MIDIPitchBend a, struct MIDIPitchBend b)
{
    return (a.value == b.value) && (a.channel == b.channel);
};

inline static void PrintMIDIPitchBend(struct MIDIPitchBend n)
{
    printf("[channel: %i value %i]", n.channel, n.value);
}
// ---

enum MIDIMessageType {
    mtNothing = 0,
    mtNote,
    mtControlChange,
    mtPolyKeyPressure,
    mtProgramChange,
    mtAfterTouch,
    mtPitchBend
};

union MIDIMessageUnion {
    struct MIDINote note;
    struct MIDIPolyKeyPressure keyPressure;
    struct MIDIControlChange controlChange;
    struct MIDIProgramChange programChange;
    struct MIDIAfterTouch afterTouch;
    struct MIDIPitchBend pitchBend;
};

// -------------------- Message --------------------

typedef struct MIDIMessage {
    enum MIDIMessageType type;
    union MIDIMessageUnion value;
} MIDIMessage;

inline static struct MIDIMessage EmptyMIDIMessage()
{
    struct MIDIMessage ret;
    ret.type = mtNothing;
    return ret;
}

inline static int MIDIMessageIsEmpty(MIDIMessage d)
{
    return d.type == mtNothing;
}

inline static void PrintMIDIMessage(MIDIMessage msg)
{
    printf("MIDI Message: ");

    if (msg.type == mtNothing) {
        printf("[empty]");
    }

    if (msg.type == mtNote) {
        PrintMIDINote(msg.value.note);
    }

    if (msg.type == mtControlChange) {
        PrintMIDIControlChange(msg.value.controlChange);
    }

    if (msg.type == mtPolyKeyPressure) {
        PrintMIDIPolyKeyPressure(msg.value.keyPressure);
    }

    if (msg.type == mtProgramChange) {
        PrintMIDIProgramChange(msg.value.programChange);
    }

    if (msg.type == mtAfterTouch) {
        PrintMIDIAfterTouch(msg.value.afterTouch);
    }

    if (msg.type == mtPitchBend) {
        PrintMIDIPitchBend(msg.value.pitchBend);
    }

    printf("\n");
}

// -------------------- Raw Data --------------------

typedef struct MIDIRawBytes {
    MIDIByte* data;
    int size;
} MIDIRawBytes;

inline static struct MIDIRawBytes newRawData(int size)
{
    MIDIRawBytes ret;
    ret.size = size;
    ret.data = (MIDIByte*)malloc(sizeof(MIDIByte) * size);
    return ret;
}

inline static struct MIDIRawBytes EmptyMIDIRawBytes()
{
    return newRawData(0);
}

inline static int MIDIRawBytesIsEmpty(MIDIRawBytes d)
{
    return d.size == 0;
}

inline static void PrintMIDIRawBytes(MIDIRawBytes d)
{
    printf("MIDIRawBytes: [size: %i] ", d.size);
    for (int i = 0; i < d.size; i++) {
        printf("%i ", d.data[i]);
    }
    printf("\n");
}

// -------------------- Constructors --------------------

inline static MIDIMessage CreateMIDINoteMessage(MIDIByte ch, MIDIByte p, MIDIByte v)
{
    MIDIMessage ret;
    ret.type = mtNote;
    ret.value.note.channel = ch;
    ret.value.note.pitch = p;
    ret.value.note.velocity = v;
    return ret;
}

inline static MIDIMessage CreateMIDIControlChangeMessage(MIDIByte ch, MIDIByte cc, MIDIByte v)
{
    MIDIMessage ret;
    ret.type = mtControlChange;
    ret.value.controlChange.channel = ch;
    ret.value.controlChange.cc = cc;
    ret.value.controlChange.value = v;
    return ret;
}

inline static MIDIMessage CreateMIDIPolyKeyPressureMessage(MIDIByte ch, MIDIByte key, MIDIByte v)
{
    MIDIMessage ret;
    ret.type = mtPolyKeyPressure;
    ret.value.keyPressure.channel = ch;
    ret.value.keyPressure.key = key;
    ret.value.keyPressure.value = v;
    return ret;
}

inline static MIDIMessage CreateMIDIProgramChangeMessage(MIDIByte ch, MIDIByte v)
{
    MIDIMessage ret;
    ret.type = mtProgramChange;
    ret.value.programChange.channel = ch;
    ret.value.programChange.value = v;
    return ret;
}

inline static MIDIMessage CreateMIDIAfterTouchMessage(MIDIByte ch, MIDIByte v)
{
    MIDIMessage ret;
    ret.type = mtAfterTouch;
    ret.value.afterTouch.channel = ch;
    ret.value.afterTouch.value = v;
    return ret;
}

inline static MIDIMessage CreateMIDIPitchBendMessage(MIDIByte ch, unsigned int v)
{
    MIDIMessage ret;
    ret.type = mtPitchBend;
    ret.value.pitchBend.channel = ch;
    ret.value.pitchBend.value = v;
    return ret;
}

// -------------------- Converters --------------------

inline static MIDIMessage MIDIDecode(MIDIByte* data, int len)
{
    MIDIMessage ret;
    if (MIDIByteInRange(data[0], 144, 159)) {
        ret.type = mtNote;
        ret.value.note.pitch = data[1];
        ret.value.note.velocity = data[2];
        ret.value.note.channel = data[0] - 144;
        return ret;
    }

    if (MIDIByteInRange(data[0], 160, 175)) {
        ret.type = mtPolyKeyPressure;
        ret.value.keyPressure.key = data[1];
        ret.value.keyPressure.value = data[2];
        ret.value.keyPressure.channel = data[0] - 160;
        return ret;
    }

    if (MIDIByteInRange(data[0], 176, 191)) {
        ret.type = mtControlChange;
        ret.value.controlChange.cc = data[1];
        ret.value.controlChange.value = data[2];
        ret.value.controlChange.channel = data[0] - 176;
        return ret;
    }

    if (MIDIByteInRange(data[0], 192, 207)) {
        ret.type = mtProgramChange;
        ret.value.programChange.value = data[1];
        ret.value.controlChange.channel = data[0] - 192;
        return ret;
    }

    if (MIDIByteInRange(data[0], 208, 223)) {
        ret.type = mtAfterTouch;
        ret.value.programChange.value = data[1];
        ret.value.controlChange.channel = data[0] - 208;
        return ret;
    }

    if (MIDIByteInRange(data[0], 224, 239)) {
        ret.type = mtPitchBend;
        ret.value.programChange.value = data[1] + data[2] * 127;
        ret.value.controlChange.channel = data[0] - 224;
        return ret;
    }

    return EmptyMIDIMessage();
}

inline static MIDIRawBytes MIDIEncode(MIDIMessage msg)
{
    if (msg.type == mtNothing) {
        return newRawData(0);
    }

    if (msg.type == mtNote) {
        MIDIRawBytes ret = newRawData(3);
        ret.data[0] = 144 + msg.value.note.channel;
        ret.data[1] = msg.value.note.pitch;
        ret.data[2] = msg.value.note.velocity;
        return ret;
    }

    if (msg.type == mtPolyKeyPressure) {
        MIDIRawBytes ret = newRawData(3);
        ret.data[0] = 160 + msg.value.keyPressure.channel;
        ret.data[1] = msg.value.keyPressure.key;
        ret.data[2] = msg.value.keyPressure.value;
        return ret;
    }

    if (msg.type == mtControlChange) {
        MIDIRawBytes ret = newRawData(3);
        ret.data[0] = 176 + msg.value.controlChange.channel;
        ret.data[1] = msg.value.controlChange.cc;
        ret.data[2] = msg.value.controlChange.value;
        return ret;
    }

    if (msg.type == mtProgramChange) {
        MIDIRawBytes ret = newRawData(2);
        ret.data[0] = 192 + msg.value.programChange.channel;
        ret.data[1] = msg.value.programChange.value;
        return ret;
    }

    if (msg.type == mtAfterTouch) {
        MIDIRawBytes ret = newRawData(2);
        ret.data[0] = 208 + msg.value.afterTouch.channel;
        ret.data[1] = msg.value.afterTouch.value;
        return ret;
    }

    if (msg.type == mtPitchBend) {
        MIDIRawBytes ret = newRawData(3);
        ret.data[0] = 224 + msg.value.pitchBend.channel;
        ret.data[1] = msg.value.pitchBend.value % 127;
        ret.data[2] = floor(msg.value.pitchBend.value / 127);
        return ret;
    }

    return EmptyMIDIRawBytes();
};
