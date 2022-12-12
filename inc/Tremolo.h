/*
 * Company: Blackaddr Audio
 * Effect Name: Tremolo
 * Description: An easy to use tremolo with mulitple modulation waveforms to choose from.
 *
 * This file was auto-generated by Aviate Audio Effect Creator for the Multiverse.
 */
#pragma once

#include <Audio.h>
#include <arm_math.h>
#include "Aviate/AudioEffectWrapper.h"

//!s - START_USER_INCLUDES - put your #includes below this line before the matching END
#include "Aviate/LibBasicFunctions.h"  // needed for Aviate::LowFrequencyOscillator
//!e - END_USER_INCLUDES

namespace BlackaddrAudio_Tremolo {

//!s - START_USER_EFFECT_TYPES - put your effect types below this line before the matching END
//!e - END_USER_EFFECT_TYPES

class Tremolo : public AudioStream, public Aviate::AudioEffectWrapper {
public:
    static constexpr unsigned NUM_INPUTS  = 1;
    static constexpr unsigned NUM_OUTPUTS = 1;

    // List of effect control names
    enum {
        Bypass_e = 0,
        Waveform_e = 1,
        Rate_e = 2,
        Depth_e = 3,
        Volume_e = 4,
        NUM_CONTROLS
    };

    //!s - START_USER_CLASS_TYPES - put your custom class types below this line before the matching END
    //!e - END_USER_CLASS_TYPES

    Tremolo();

    //!s - START_USER_CONSTRUCTORS - put your custom constructors below this line before the matching END
    //!e - END_USER_CONSTRUCTORS

    virtual ~Tremolo();

    // Standard EFX interface functions - do not change these declaration
    virtual void update(); // main audio processing loop function
    void mapMidiControl(int parameter, int midiCC, int midiChannel = 0) override;
    void processMidi(int channel, int midiCC, int value) override;
    void setParam(int paramIndex, float paramValue) override;
    float getUserParamValue(int paramIndex, float normalizedParamValue);
    const char* getName() override;
    const uint8_t* getRblk() override;

    // control value set functions, must take floats between 0.0f and 1.0f - do not change these declarations
    void waveform(float value);
    void rate(float value);
    void depth(float value);
    void volume(float value) override;

    //!s - START_USER_PUBLIC_MEMBERS - put your public members below this line before the matching END
    void setWaveform(Aviate::Waveform waveform);  // function to set LFO waveform using enums
    //!e - END_USER_PUBLIC_MEMBERS

private:
    audio_block_t *m_inputQueueArray[1]; // required by AudioStream base class, array size is num inputs
    int m_midiConfig[NUM_CONTROLS][2]; // stores the midi parameter mapping

    // m_bypass and m_volume are already provided by the base class AudioEffectWrapper
    float m_waveform = 0.0f;
    float m_rate = 0.0f;
    float m_depth = 0.0f;

    audio_block_t* m_basicInputCheck(audio_block_t* inputAudioBlock, unsigned outputChannel);

    //!s - START_USER_PRIVATE_MEMBERS - put your private members below this line before the matching END
    static constexpr float MAX_RATE_HZ = 20.0f;  // The LFO rate will range from 0 Hz to 20 Hz

    Aviate::LowFrequencyOscillatorVector<float> m_osc;  // instance of an LFO oscillator
    Aviate::Waveform m_waveformType = Aviate::Waveform::SINE;  // store the waveform type as an enum
    //!e - END_USER_PRIVATE_MEMBERS

};

}
