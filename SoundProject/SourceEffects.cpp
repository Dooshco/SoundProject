#include "SoundEffects.h"

const unsigned SAMPLES = 44100;
const unsigned SAMPLE_RATE = 44100;
const unsigned AMPLITUDE = 30000;
const double TWO_PI = 6.28318;

SoundEffects::SoundEffects()
{

	sf::Int16 raw[SAMPLES];

	// Sine Sample
	double increment = 440. / 44100; // 440 Hz
	double x = 0;
	for (unsigned i = 0; i < SAMPLES; i++) {
		raw[i] = AMPLITUDE * sin(x*TWO_PI);
		x += increment;
	}
	sineBuffer.loadFromSamples(raw, SAMPLES, 1, SAMPLE_RATE);
	sineSound.setBuffer(sineBuffer);

	// LASER
	// Square wave
	double decrement = 1.0 / SAMPLES * 2;
	double v = 1.0;
	int frequency = 100;
	for (unsigned i = 0; i < SAMPLES / 2; i++) {
		if ((i % frequency) < int(frequency / 2))
			raw[i] = AMPLITUDE * v;
		else
			raw[i] = 0;
		v -= decrement;
		frequency = 100 - int(i / 100000);
		//std::cout << v << " A: "<<  raw[i] << std::endl;
	}
	//laserBuffer.loadFromSamples(raw, SAMPLES/2, 1, SAMPLE_RATE);
	laserBuffer.loadFromFile("D:\\laser.wav");
	laserSound.setBuffer(laserBuffer);


	// BEAT1
	// Square wave
	for (unsigned i = 0; i < SAMPLES / 20; i++) {
		if (i % 600 < 300)
			raw[i] = AMPLITUDE / 8;
		else
			raw[i] = AMPLITUDE / 8;

	}
	beat1Buffer.loadFromSamples(raw, SAMPLES / 20, 1, SAMPLE_RATE);
	beat1Sound.setBuffer(beat1Buffer);

	// BEAT2
	// Square wave
	for (unsigned i = 0; i < SAMPLES / 20; i++) {
		if (i % 800 < 400)
			raw[i] = AMPLITUDE / 8;
		else
			raw[i] = AMPLITUDE / 8;

	}
	beat2Buffer.loadFromSamples(raw, SAMPLES / 20, 1, SAMPLE_RATE);
	beat2Sound.setBuffer(beat2Buffer);


	// THRUSTER
	// Builed Noise sample for thruster sound
	for (unsigned i = 0; i < SAMPLES / 200; i++)
	{
		raw[i] = rand() % (AMPLITUDE / 10);
	}

	if (!thrustBuffer.loadFromSamples(raw, SAMPLES / 200, 1, SAMPLE_RATE))
	{
		std::cout << "Loading failed!" << std::endl;
		return;
	}
	thrustSound.setBuffer(thrustBuffer);
	thrustSound.setPitch(0.03f);

	// EXPLOSION
	// Volume is reduced with time
	decrement = 1.0 / SAMPLES * 8;
	v = 1.0;
	for (unsigned i = 0; i < SAMPLES / 8; i++)
	{
		raw[i] = (rand() % AMPLITUDE) * v;
		v -= decrement;
	}

	if (!explosionBuffer.loadFromSamples(raw, SAMPLES / 8, 1, SAMPLE_RATE)) {
		std::cout << "Loading failed!" << std::endl;
		return;
	}
	explosionSound.setBuffer(explosionBuffer);
	explosionSound.setPitch(0.08f);


}

void SoundEffects::Play(SoundEffects::soundType st)
{
	switch (st)
	{
	case THRUST:
		if (thrustSound.getStatus() != sf::Sound::Playing)
		{
			thrustSound.setLoop(true);
			thrustSound.play();
		}
		break;
	case LASER:
		laserSound.play();
		break;
	case EXPLOSION:
		explosionSound.play();
		break;
	case BEAT:
		if (beat1 == true)
		{
			beat1Sound.play();
			beat1 = false;
		}
		else
		{
			beat2Sound.play();
			beat1 = true;
		}
		break;
	}

}

void SoundEffects::Stop(SoundEffects::soundType st)
{
	switch (st)
	{
	case THRUST:
		if (thrustSound.getStatus() == sf::Sound::Playing)
		{
			thrustSound.stop();
		}
		break;
	case LASER:
	case EXPLOSION:
	case BEAT:
		break;
	}

}


SoundEffects::~SoundEffects()
{
}
