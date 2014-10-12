#pragma once
#include <algorithm>
using namespace std;


inline float interpolate(float x0, float x1, float alpha)
{
	return x0 * (1.f - alpha) + alpha * x1;
}

float ** perlinNoise(int width, int height, float upperBound = 1.f)
{
	//Calculate octaves number
	int octavesNum = 1;
	int octave = 1;

	int square = std::max(width, height);
	while (octave < square)
	{
		++octavesNum;
		octave <<= 2;
	}

	//Generate octaves
	float *** octaves = new float**[octavesNum];

	//Create matrix of random values between 0.f and 1.f, plus initialize the octave matrix
	float ** randomNoise = new float*[height];
	for (int currentOctave = 0; currentOctave < octavesNum; ++currentOctave)
	{
		octaves[currentOctave] = new float*[height];
		for (int i = 0; i < height; ++i)
			octaves[currentOctave][i] = new float[width];
	}
	for (int i = 0; i < height; ++i)
	{
		randomNoise[i] = new float[width];
		for (int j = 0; j < width; ++j)
			randomNoise[i][j] = float(rand() % 1000) / 1000.f * upperBound;
	}

	//Fill octaves
	for (int currentOctave = 0; currentOctave < octavesNum; ++currentOctave)
	{

		int period = 1 << currentOctave;
		float freq = 1.0f / period;

		//Start sampling
		for (int i = 0; i < height; ++i)
		{
			int vSample0 = (i / period) * period;
			int vSample1 = (vSample0 + period) % height;
			float vBlend = (i - vSample0) * freq;
			for (int j = 0; j < width; ++j)
			{
				int hSample0 = (j / period) * period;
				int hSample1 = (hSample0 + period) % width;
				float hBlend = (j - hSample0) * freq;
				//Blend
				float top = interpolate(randomNoise[vSample0][hSample0],
					randomNoise[vSample1][hSample0], vBlend);
				float bot = interpolate(randomNoise[vSample0][hSample1],
					randomNoise[vSample1][hSample1], vBlend);
				octaves[currentOctave][i][j] = interpolate(top, bot, hBlend);
			}
		}
	}

	//Init returning noise
	float ** ret = new float*[height];
	for (int i = 0; i < height; ++i)
	{
		ret[i] = new float[width];
		fill(ret[i], ret[i] + width, 0.f);
	}

	//Blend octaves together
	float amplitude = 1.0f;
	float totalAmplitude = 0.0f;
	float persistance = 0.5f;

	for (int currentOctave = octavesNum - 1; octave >= 0; --octave)
	{
		amplitude *= persistance;
		totalAmplitude += amplitude;

		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				ret[i][j] += octaves[currentOctave][i][j] * amplitude;
			}
		}
	}

	//Normalization
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			ret[i][j] /= totalAmplitude;
		}
	}



	return ret;
}