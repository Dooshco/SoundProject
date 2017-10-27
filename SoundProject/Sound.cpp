#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Synth.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "Synthesizer Demo!");

    sf::SoundBuffer soundBuffer;
    sf::Sound demoSound;
    
    // LASER
    Synth::sEnvelope envelope = { 0.0, 0.0, 0.0, 0.3, 1.0, 1.0 };
    Synth::sTone tone = { Synth::OSC_SAW_DIG, 900.0, 500.0, 0.8 };
    Synth::generate(&soundBuffer, envelope, tone, 20000, 44100);
    demoSound.setBuffer(soundBuffer);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
                demoSound.play();
        }
    }

	return 0;
}