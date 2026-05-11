#include <SFML/Audio.hpp>
#include <iostream>
#include "sound.h"
#include <thread>
#include <chrono>

int main()
{   
    int n = 100;
    while (true) {
        
    
        Sound sound;
        for (int i = 0; i < n; ++i) {
            float frequency = sound.getFrequency(i, n);
            sound.play(frequency);
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
        
    }

    return 0;


}


    