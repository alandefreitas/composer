#ifndef COMPOSER_SYNTHESIZER_H
#define COMPOSER_SYNTHESIZER_H

#include <q/synth/sin.hpp>
#include <q/synth/square.hpp>
#include <q/synth/triangle.hpp>
#include <q/synth/saw.hpp>
#include <q/support/literals.hpp>
#include <q_io/audio_stream.hpp>
#include <vector>

namespace q = cycfi::q;
using namespace q::literals;

struct synth : q::port_audio_stream
{
    synth(int timbre = 0)
        : port_audio_stream( 0, 2)
        , _timbre(timbre)
    {}

    void process(out_channels const& out);

    void set(q::frequency const &freq, int const &dur);

    void play(std::vector<std::pair<int,q::frequency>> &notes);

    q::phase_iterator   phase;   // The phase iterator
    int                 _timbre;
};

#endif // COMPOSER_SYNTHESIZER_H