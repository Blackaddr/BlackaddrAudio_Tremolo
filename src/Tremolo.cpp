/*
 * Company: Blackaddr Audio
 * Effect Name: Tremolo
 * Description: An easy to use tremolo with mulitple modulation waveforms to choose from.
 *
 * This file was auto-generated by Aviate Audio Effect Creator for the Multiverse.
 */
#include "BlackaddrAudio_Tremolo/Tremolo.h"

using namespace baCore;

namespace BlackaddrAudio_Tremolo {

Tremolo::Tremolo()
: AudioStream(NUM_INPUTS, m_inputQueueArray)
{
    // perform any necessary class initialization here
}

Tremolo::~Tremolo()
{
    // perform any necessary clean up here, though destructors are not
    // called on the hardware, only in the simulator.
}

void Tremolo::update(void)
{
    audio_block_t *inputAudioBlock = receiveWritable(); // get the next block of input samples
    inputAudioBlock = m_basicInputCheck(inputAudioBlock, 0); // check for disable mode, bypass, or invalid inputs. Transmit to channel 0 in bypass
    if (!inputAudioBlock) { return; } // no further processing for this update() call

    // You must call m_updateInputPeak() before processing the audio
    m_updateInputPeak(inputAudioBlock);

    // DO AUDIO EFFECT PROCESSING
    for (auto idx=0; idx<AUDIO_BLOCK_SAMPLES; idx++) {

        float sample = (float)inputAudioBlock->data[idx];

        // do your processing ...

        // last task should be to apply the mandatory volume control
        sample = sample * m_volume;
        inputAudioBlock->data[idx] = (int16_t)sample; // we re-use the input audio block
    }

    m_updateOutputPeak(inputAudioBlock); // you must call m_upateOutputPeak() at the end of update() before transmit
    transmit(inputAudioBlock);
    release(inputAudioBlock);
}

void Tremolo::waveform(float value)
{
    // perform any necessary conversion to user variables, validation, etc.
    m_waveform = value;
}

void Tremolo::rate(float value)
{
    // perform any necessary conversion to user variables, validation, etc.
    m_rate = value;
}

void Tremolo::depth(float value)
{
    // perform any necessary conversion to user variables, validation, etc.
    m_depth = value;
}

void Tremolo::volume(float value)
{
    volumeDb(-40.0f + (value * 50.0f)); // volume knob goes from -40dB to +10dB
}


}
