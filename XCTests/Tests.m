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

    MIDIRawData rd = MIDIEncode(msg);
    PrintMIDIRawData(rd);

    MIDIMessage msg_dec = MIDIDecode(rd.data, rd.size);
    PrintMIDIMessage(msg_dec);

    XCTAssert(msg_dec.type == msg.type);
    XCTAssert(msg_dec.value.note.pitch == msg.value.note.pitch);
}
- (void)testCC
{
    MIDIMessage msg = CreateMIDIControlChangeMessage(1, 64, 32);
    PrintMIDIMessage(msg);
    
    MIDIRawData rd = MIDIEncode(msg);
    PrintMIDIRawData(rd);
    
    MIDIMessage msg_dec = MIDIDecode(rd.data, rd.size);
    PrintMIDIMessage(msg_dec);
    
    XCTAssert(msg_dec.type == msg.type);
    XCTAssert(msg_dec.value.note.pitch == msg.value.note.pitch);
}

- (void)testPolyKeyPressure
{
    MIDIMessage msg = CreateMIDIPolyKeyPressureMessage(1, 64, 32);
    PrintMIDIMessage(msg);
    
    MIDIRawData rd = MIDIEncode(msg);
    PrintMIDIRawData(rd);
    
    MIDIMessage msg_dec = MIDIDecode(rd.data, rd.size);
    PrintMIDIMessage(msg_dec);
    
    XCTAssert(msg_dec.type == msg.type);
    XCTAssert(msg_dec.value.note.pitch == msg.value.note.pitch);
}

- (void)testProgramChange
{
    MIDIMessage msg = CreateMIDIProgramChangeMessage(1, 32);
    PrintMIDIMessage(msg);
    
    MIDIRawData rd = MIDIEncode(msg);
    PrintMIDIRawData(rd);
    
    MIDIMessage msg_dec = MIDIDecode(rd.data, rd.size);
    PrintMIDIMessage(msg_dec);
    
    XCTAssert(msg_dec.type == msg.type);
    XCTAssert(msg_dec.value.note.pitch == msg.value.note.pitch);
}


- (void)testAfterTouch
{
    MIDIMessage msg = CreateMIDIAfterTouchMessage(1, 10);
    PrintMIDIMessage(msg);
    
    MIDIRawData rd = MIDIEncode(msg);
    PrintMIDIRawData(rd);
    
    MIDIMessage msg_dec = MIDIDecode(rd.data, rd.size);
    PrintMIDIMessage(msg_dec);
    
    XCTAssert(msg_dec.type == msg.type);
    XCTAssert(msg_dec.value.note.pitch == msg.value.note.pitch);
}


- (void)testPitchBend
{
    MIDIMessage msg = CreateMIDIPitchBendMessage(1, 2048);
    PrintMIDIMessage(msg);
    
    MIDIRawData rd = MIDIEncode(msg);
    PrintMIDIRawData(rd);
    
    MIDIMessage msg_dec = MIDIDecode(rd.data, rd.size);
    PrintMIDIMessage(msg_dec);
    
    XCTAssert(msg_dec.type == msg.type);
    XCTAssert(msg_dec.value.note.pitch == msg.value.note.pitch);
}


@end
