#pragma once
#include <SFML/Audio.hpp>
#include <vector>
#include <cmath>

class Sound {
private:
    sf::SoundBuffer buffer;
    sf::Sound sound;
public:
    void play(float frequency, float duration = 0.02f) {
        const int sampleRate = 44100;
        const int sampleCount = static_cast<int>(duration * sampleRate);
        std::vector<sf::Int16> samples(sampleCount);
        
        const float twoPi = 6.28318f;
        const float amplitude = 3000; // Max amplitude for 16-bit audio

        for (int i = 0; i < sampleCount; ++i) {
            float t = static_cast<float>(i) / sampleRate;
            samples[i] = static_cast<sf::Int16>(amplitude * sin(twoPi * frequency * t));
        }
        buffer.loadFromSamples(samples.data(), sampleCount, 1, sampleRate);
        sound.setBuffer(buffer);
        sound.play();
    }
    float getFrequency(int value, int maxValue) {
        // Map the value to a frequency range (e.g., 20 Hz to 20 kHz)
        float minFreq = 200.0f;
        float maxFreq = 2000.0f;
        return minFreq + (maxFreq - minFreq) * (static_cast<float>(value) / maxValue);  
        
    }

};