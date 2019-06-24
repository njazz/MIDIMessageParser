//
//  Tests_macOS.m
//  Tests-macOS
//
//  Created by Alex on 12/05/2019.
//

#import <XCTest/XCTest.h>

#include "MIDIParser.h"

@interface Tests_macOS : XCTestCase

@end

@implementation Tests_macOS

- (void)testNote
{
    MIDIMessage msg = CreateMIDINoteMessage(1, 60, 100);
    PrintMIDIMessage(msg);

    MIDIRawBytes rd = MIDIEncode(msg);
    PrintMIDIRawBytes(rd);

    MIDIMessage msg_dec = MIDIDecode(rd.data, rd.size);
    PrintMIDIMessage(msg_dec);

    XCTAssert(msg_dec.type == msg.type);
    XCTAssert(msg_dec.value.note.pitch == msg.value.note.pitch);
    XCTAssert(msg_dec.value.note.velocity == msg.value.note.velocity);
    XCTAssert(msg_dec.value.note.channel == msg.value.note.channel);

    XCTAssert(MIDINoteEquals(msg.value.note, msg_dec.value.note));
}

- (void)testNoteOff
{
    // ?
    MIDIMessage msg = CreateMIDINoteOffMessage(1, 60, 100);
    PrintMIDIMessage(msg);
    
    MIDIRawBytes rd = MIDIEncode(msg);
    PrintMIDIRawBytes(rd);
    
    MIDIMessage msg_dec = MIDIDecode(rd.data, rd.size);
    PrintMIDIMessage(msg_dec);
    
    XCTAssert(msg_dec.type == msg.type);
    XCTAssert(msg_dec.value.note.pitch == msg.value.note.pitch);
    XCTAssert(msg_dec.value.note.velocity == msg.value.note.velocity);
    XCTAssert(msg_dec.value.note.channel == msg.value.note.channel);
    
    XCTAssert(MIDINoteEquals(msg.value.note, msg_dec.value.note));
}

-(void)testEmpty{
    MIDIMessage msg = EmptyMIDIMessage();
    XCTAssert(MIDIMessageIsEmpty(msg));
    
    MIDIRawBytes b = EmptyMIDIRawBytes();
    XCTAssert(MIDIRawBytesIsEmpty(b));
    
    MIDIRawBytes rd = MIDIEncode(msg);
    PrintMIDIRawBytes(rd);
    
    MIDIMessage msg_dec = MIDIDecode(rd.data, rd.size);
    PrintMIDIMessage(msg_dec);
    
    XCTAssert(MIDIMessageIsEmpty(msg_dec));
}

- (void)testCC
{
    MIDIMessage msg = CreateMIDIControlChangeMessage(1, 64, 32);
    PrintMIDIMessage(msg);

    MIDIRawBytes rd = MIDIEncode(msg);
    PrintMIDIRawBytes(rd);

    MIDIMessage msg_dec = MIDIDecode(rd.data, rd.size);
    PrintMIDIMessage(msg_dec);

    XCTAssert(msg_dec.type == msg.type);
    XCTAssert(msg_dec.value.controlChange.cc == msg.value.controlChange.cc);
    XCTAssert(msg_dec.value.controlChange.value == msg.value.controlChange.value);
    XCTAssert(msg_dec.value.controlChange.channel == msg.value.controlChange.channel);

    XCTAssert(MIDIControlChangeEquals(msg.value.controlChange, msg_dec.value.controlChange));
}

- (void)testPolyKeyPressure
{
    MIDIMessage msg = CreateMIDIPolyKeyPressureMessage(1, 64, 32);
    PrintMIDIMessage(msg);

    MIDIRawBytes rd = MIDIEncode(msg);
    PrintMIDIRawBytes(rd);

    MIDIMessage msg_dec = MIDIDecode(rd.data, rd.size);
    PrintMIDIMessage(msg_dec);

    XCTAssert(msg_dec.type == msg.type);
    XCTAssert(msg_dec.value.note.pitch == msg.value.note.pitch);

    XCTAssert(MIDIPolyKeyPressureEquals(msg.value.keyPressure, msg_dec.value.keyPressure));
}

- (void)testProgramChange
{
    MIDIMessage msg = CreateMIDIProgramChangeMessage(1, 32);
    PrintMIDIMessage(msg);

    MIDIRawBytes rd = MIDIEncode(msg);
    PrintMIDIRawBytes(rd);

    MIDIMessage msg_dec = MIDIDecode(rd.data, rd.size);
    PrintMIDIMessage(msg_dec);

    XCTAssert(msg_dec.type == msg.type);
    XCTAssert(msg_dec.value.programChange.value == msg.value.programChange.value);
    XCTAssert(msg_dec.value.programChange.channel == msg.value.programChange.channel);

    XCTAssert(MIDIProgramChangeEquals(msg.value.programChange, msg_dec.value.programChange));
}

- (void)testAfterTouch
{
    MIDIMessage msg = CreateMIDIAfterTouchMessage(1, 10);
    PrintMIDIMessage(msg);

    MIDIRawBytes rd = MIDIEncode(msg);
    PrintMIDIRawBytes(rd);

    MIDIMessage msg_dec = MIDIDecode(rd.data, rd.size);
    PrintMIDIMessage(msg_dec);

    XCTAssert(msg_dec.type == msg.type);
    XCTAssert(msg_dec.value.afterTouch.value == msg.value.afterTouch.value);
    XCTAssert(msg_dec.value.afterTouch.channel == msg.value.afterTouch.channel);

    XCTAssert(MIDIAfterTouchEquals(msg.value.afterTouch, msg_dec.value.afterTouch));
}

- (void)testPitchBend
{
    MIDIMessage msg = CreateMIDIPitchBendMessage(1, 2048);
    PrintMIDIMessage(msg);

    MIDIRawBytes rd = MIDIEncode(msg);
    PrintMIDIRawBytes(rd);

    MIDIMessage msg_dec = MIDIDecode(rd.data, rd.size);
    PrintMIDIMessage(msg_dec);

    XCTAssert(msg_dec.type == msg.type);
    XCTAssert(msg_dec.value.pitchBend.value == msg.value.pitchBend.value);
    XCTAssert(msg_dec.value.pitchBend.channel == msg.value.pitchBend.channel);

    XCTAssert(MIDIPitchBendEquals(msg.value.pitchBend, msg_dec.value.pitchBend));
}

@end
