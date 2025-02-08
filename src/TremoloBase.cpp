/*
 * Company: Blackaddr Audio
 * Effect Name: Tremolo
 * Description: An easy to use tremolo with mulitple modulation waveforms to choose from.
 *
 * This file was auto-generated by Aviate Audio Effect Creator for the Multiverse.
 */
#include <cmath>
#include "Aviate/LibBasicFunctions.h"
#include "Tremolo.h"

#define audioBlockReceiveReadOnly receiveReadOnly
#define audioBlockReceiveWritable receiveWritable
#define audioBlockAllocate        allocate

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

void Tremolo::processMidi(int status, int data1, int data2)
{
}

audio_block_t* Tremolo::m_basicInputCheck(audio_block_t* inputAudioBlock, unsigned outputChannel)
{
    // Check if effect is disabled
    if (m_enable == false) {
        // do not transmit or process any audio, return as quickly as possible after releasing the inputs
        if (inputAudioBlock) { AudioStream::release(inputAudioBlock); }
        return nullptr; // disabled, no further EFX processing in update()
    }  // end of enable check

    // check if effect is in bypass
    if (m_bypass == true) {
        // drive input directly to the specified output. ie. bypass
        if (inputAudioBlock != nullptr) {
            // valid input, drive to outputChannel if specified
            if (outputChannel >= 0) {
                AudioStream::transmit(inputAudioBlock, outputChannel); // drive to specified output
            }
            AudioStream::release(inputAudioBlock); // release the input block as we are done with it
        } else { // invalid input block, allocate a block and drive silence if specified
            if (outputChannel >= 0) {
                audio_block_t* silenceBlock = AudioStream::allocate();
                if (silenceBlock) {
                    clearAudioBlock(silenceBlock);  // create silence in the buffer
                    AudioStream::transmit(silenceBlock, outputChannel);
                    AudioStream::release(silenceBlock);
                }
            }
        }
        return nullptr;  // bypassed, no further EFX processing in update()
    }  // end of bypass check

    // If not disabled or bypassed, create silence if the input block is invalid then
    // return the valid audio block so update() can continue.
    if (inputAudioBlock == nullptr) {
        inputAudioBlock = AudioStream::allocate();
        if (inputAudioBlock == nullptr) { return nullptr; } // check if allocate was unsuccessful
        // else
        clearAudioBlock(inputAudioBlock);
    }
    return inputAudioBlock; // inputAudioBLock is valid and ready for update() processing
}

const uint8_t rblk[256] = TEENSY_AUDIO_BLOCK;
const uint8_t* Tremolo::getRblk() { return rblk; }
static constexpr char PROGMEM Tremolo_name[] = {0x42, 0x6c, 0x61, 0x63, 0x6b, 0x61, 0x64, 0x64, 0x72, 0x20, 0x41, 0x75, 0x64, 0x69, 0x6f, 0x3a, 0x54, 0x72, 0x65, 0x6d, 0x6f, 0x6c, 0x6f, 0x0};
const char* Tremolo::getName() { return Tremolo_name; }

}
