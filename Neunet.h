#pragma once
#include "Synaptic_test.h"
#include "Random.h"
#include <math.h>


namespace neunet
{
	class Neunet
	{
	private:
		Synaptic net;
		float learn_rate;
		float output;
	public:
		Neunet(float inputLearnRate)
		{
			random::start();
			learn_rate = inputLearnRate;
			output = 0;
			net = Synaptic(learn_rate);
		}
		float predict(float x, float y)
		{
			net.setInput(0, x);
			net.setInput(1, y);
			net.calculateOutput();
			return std::round(net.getOutput());
		}
		void train(float x[4], float y[4], float target[4], float iterations)
		{
			for (int i = 0; i < iterations; ++i)
			{
				for (int j = 0; j < 4; ++j)
				{
					net.setInput(0, x[j]);
					net.setInput(1, y[j]);
					net.train(target[j]);
				}
			}
		}
		void destroy()
		{
			net.destroy();
		}
	};
}