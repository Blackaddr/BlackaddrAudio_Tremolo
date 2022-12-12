/*
 * Company: Blackaddr Audio
 * Effect Name: Tremolo
 * Description: An easy to use tremolo with mulitple modulation waveforms to choose from.
 *
 * This file was auto-generated by Aviate Audio Effect Creator for the Multiverse.
 */
#include <cmath>
#include "Aviate/EfxPrint.h"
#include "Aviate/LibBasicFunctions.h"
#include "Tremolo.h"

using namespace Aviate;

namespace BlackaddrAudio_Tremolo {

void Tremolo::mapMidiControl(int parameter, int midiCC, int midiChannel)
{
    if (parameter >= NUM_CONTROLS) {
        return ; // Invalid midi parameter
    }
    m_midiConfig[parameter][MIDI_CHANNEL] = midiChannel;
    m_midiConfig[parameter][MIDI_CONTROL] = midiCC;
}

void Tremolo::setParam(int paramIndex, float paramValue)
{
    switch(paramIndex) {
    case 0 : bypass( (paramValue - 0.000000) / (1.000000 - 0.000000) ); break;
    case 1 : waveform( (paramValue - 0.000000) / (4.000000 - 0.000000) ); break;
    case 2 : rate( (paramValue - 0.000000) / (10.000000 - 0.000000) ); break;
    case 3 : depth( (paramValue - 0.000000) / (10.000000 - 0.000000) ); break;
    case 4 : volume( (paramValue - 0.000000) / (10.000000 - 0.000000) ); break;
    default : break;
    }
}

float Tremolo::getUserParamValue(int paramIndex, float normalizedParamValue)
{
    switch(paramIndex) {
    case 0 : return ( ((1.000000 - 0.000000) * normalizedParamValue) + 0.000000 ); // bypass
    case 1 : return ( ((4.000000 - 0.000000) * normalizedParamValue) + 0.000000 ); // waveform
    case 2 : return ( ((10.000000 - 0.000000) * normalizedParamValue) + 0.000000 ); // rate
    case 3 : return ( ((10.000000 - 0.000000) * normalizedParamValue) + 0.000000 ); // depth
    case 4 : return ( ((10.000000 - 0.000000) * normalizedParamValue) + 0.000000 ); // volume
    default : return 0.0f;
    }
}

void Tremolo::processMidi(int channel, int control, int value)
{
    float val = (float)value / 127.0f;

    if ((m_midiConfig[Bypass_e][MIDI_CHANNEL] == channel) && (m_midiConfig[Bypass_e][MIDI_CONTROL] == control)) {
        bypass(val);
        return;
    }

    if ((m_midiConfig[Waveform_e][MIDI_CHANNEL] == channel) && (m_midiConfig[Waveform_e][MIDI_CONTROL] == control)) {
        waveform(val);
        return;
    }

    if ((m_midiConfig[Rate_e][MIDI_CHANNEL] == channel) && (m_midiConfig[Rate_e][MIDI_CONTROL] == control)) {
        rate(val);
        return;
    }

    if ((m_midiConfig[Depth_e][MIDI_CHANNEL] == channel) && (m_midiConfig[Depth_e][MIDI_CONTROL] == control)) {
        depth(val);
        return;
    }

    if ((m_midiConfig[Volume_e][MIDI_CHANNEL] == channel) && (m_midiConfig[Volume_e][MIDI_CONTROL] == control)) {
        volume(val);
        return;
    }

}

audio_block_t* Tremolo::m_basicInputCheck(audio_block_t* inputAudioBlock, unsigned outputChannel)
{
    // Check if effect is disabled
    if (m_enable == false) {
        // do not transmit or process any audio, return as quickly as possible after releasing the inputs
        if (inputAudioBlock) { release(inputAudioBlock); }
        return nullptr; // disabled, no further EFX processing in update()
    }  // end of enable check

    // check if effect is in bypass
    if (m_bypass == true) {
        // drive input directly to the specified output. ie. bypass
        if (inputAudioBlock != nullptr) {
            // valid input, drive to outputChannel if specified
            if (outputChannel >= 0) {
                transmit(inputAudioBlock, outputChannel); // drive to specified output
            }
            release(inputAudioBlock); // release the input block as we are done with it
        } else { // invalid input block, allocate a block and drive silence if specified
            if (outputChannel >= 0) {
                audio_block_t* silenceBlock = allocate();
                if (silenceBlock) {
                    clearAudioBlock(silenceBlock);  // create silence in the buffer
                    transmit(silenceBlock, outputChannel);
                    release(silenceBlock);
                }
            }
        }
        return nullptr;  // bypassed, no further EFX processing in update()
    }  // end of bypass check

    // If not disabled or bypassed, create silence if the input block is invalid then
    // return the valid audio block so update() can continue.
    if (inputAudioBlock == nullptr) {
        inputAudioBlock = allocate();
        if (inputAudioBlock == nullptr) { return nullptr; } // check if allocate was unsuccessful
        // else
        clearAudioBlock(inputAudioBlock);
    }
    return inputAudioBlock; // inputAudioBLock is valid and ready for update() processing
}

const uint8_t rblk[256] = TEENSY_AUDIO_BLOCK;
const uint8_t* Tremolo::getRblk() { return rblk; }
const char* Tremolo::getName() { return "Blackaddr Audio:Tremolo"; }

}
