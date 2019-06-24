// #include <pybind11/embed.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

extern "C" {
#include "MIDIParser.h"
}

PYBIND11_MODULE(py_midiparser, m)
{
    py::class_<MIDINote>(m, "MIDINote")
        .def_readwrite("pitch", &MIDINote::pitch)
        .def_readwrite("velocity", &MIDINote::velocity)
        .def_readwrite("channel", &MIDINote::channel);

    py::class_<MIDIControlChange>(m, "MIDIControlChange")
        .def_readwrite("cc", &MIDIControlChange::cc)
        .def_readwrite("value", &MIDIControlChange::value)
        .def_readwrite("channel", &MIDIControlChange::channel);

    py::class_<MIDIPolyKeyPressure>(m, "MIDIPolyKeyPressure")
        .def_readwrite("key", &MIDIPolyKeyPressure::key)
        .def_readwrite("value", &MIDIPolyKeyPressure::value)
        .def_readwrite("channel", &MIDIPolyKeyPressure::channel);

    py::class_<MIDIProgramChange>(m, "MIDIProgramChange")
        .def_readwrite("value", &MIDIProgramChange::value)
        .def_readwrite("channel", &MIDIProgramChange::channel);

    py::class_<MIDIAfterTouch>(m, "MIDIAfterTouch")
        .def_readwrite("value", &MIDIAfterTouch::value)
        .def_readwrite("channel", &MIDIAfterTouch::channel);

    py::class_<MIDIPitchBend>(m, "MIDIPitchBend")
        .def_readwrite("value", &MIDIPitchBend::value)
        .def_readwrite("channel", &MIDIPitchBend::channel);

    // ---

    py::enum_<MIDIMessageType>(m, "MIDIMessageType")
        .value("Nothing", MIDIMessageType::mtNothing)
        .value("Note", MIDIMessageType::mtNote)
        .value("NoteOff", MIDIMessageType::mtNoteOff)
        .value("ControlChange", MIDIMessageType::mtControlChange)
        .value("PolyKeyPressure", MIDIMessageType::mtPolyKeyPressure)
        .value("ProgramChange", MIDIMessageType::mtProgramChange)
        .value("AfterTouch", MIDIMessageType::mtAfterTouch)
        .value("PitchBend", MIDIMessageType::mtPitchBend)
        .export_values();

    py::class_<MIDIMessageUnion>(m, "MIDIMessageUnion")
        .def_property("note",
            [](MIDIMessageUnion& u)->MIDINote& { return u.note; },
            [](MIDIMessageUnion& u, MIDINote n) { u.note = n; })

        .def_property("key_pressure",
            [](MIDIMessageUnion& u)->MIDIPolyKeyPressure& { return u.keyPressure; },
            [](MIDIMessageUnion& u, MIDIPolyKeyPressure n) { u.keyPressure = n; })

        .def_property("control_change",
            [](MIDIMessageUnion& u)->MIDIControlChange& { return u.controlChange; },
            [](MIDIMessageUnion& u, MIDIControlChange n) { u.controlChange = n; })

        .def_property("program_change",
            [](MIDIMessageUnion& u)->MIDIProgramChange& { return u.programChange; },
            [](MIDIMessageUnion& u, MIDIProgramChange n) { u.programChange = n; })

        .def_property("aftertouch",
            [](MIDIMessageUnion& u)->MIDIAfterTouch& { return u.afterTouch; },
            [](MIDIMessageUnion& u, MIDIAfterTouch n) { u.afterTouch = n; })

        .def_property("pitch_bend",
            [](MIDIMessageUnion& u)->MIDIPitchBend& { return u.pitchBend; },
            [](MIDIMessageUnion& u, MIDIPitchBend n) { u.pitchBend = n; })

        // .def_property("hash",
        //     [](MIDIMessageUnion& u)->long& { return u.hash; },
        //     [](MIDIMessageUnion& u, long n) { u.hash = n; })

        // .def_property("bytes",
        //     [](const MIDIMessageUnion& u) {
        //         std::array<MIDIByte, 4> ret;
        //         for (int i = 0; i < 4; i++)
        //             ret[i] = u.bytes[i];
        //         return ret;
        //     },
        //     [](MIDIMessageUnion& u, std::array<MIDIByte, 4> n) {
        //
        //         for (int i = 0; i < 4; i++)
        //             u.bytes[i] = n[i];
        //     });

        ;

    py::class_<MIDIMessage>(m, "MIDIMessage")
        .def_readwrite("type", &MIDIMessage::type)
        .def_readwrite("value", &MIDIMessage::value)

        .def("is_empty", &MIDIMessageIsEmpty)
        .def("print", &PrintMIDIMessage)

        .def("create_empty", &EmptyMIDIMessage)
        .def("create_note", &CreateMIDINoteMessage)
        .def("create_note_off", &CreateMIDINoteOffMessage)
        .def("create_control_change", &CreateMIDIControlChangeMessage)
        .def("create_poly_key_pressure", &CreateMIDIPolyKeyPressureMessage)
        .def("create_program_change", &CreateMIDIProgramChangeMessage)
        .def("create_after_touch", &CreateMIDIAfterTouchMessage)
        .def("create_pitch_bend", &CreateMIDIPitchBendMessage)

        .def("decode", [](std::vector<MIDIByte> d) { return MIDIDecode(d.data(), d.size()); })
        .def("encode", [](MIDIMessage& m) {
            auto d = MIDIEncode(m);
            std::vector<MIDIByte> ret;
            ret.assign(d.data, d.data + d.size);
            return ret;
        })

        ;
}
