#pragma once
#include "Neuron.h"


namespace neunet
{
	class Synaptic
	{
	private:
		float learn_rate;
		float inputs[2];
		int hidden_count = 100;
		Neuron neuron_hidden[100];
		Neuron neuron_output;
		float output;

		void calculate_outputs_hidden()
		{
			for (int h = 0; h < hidden_count; ++h)
			{
				for (int i = 0; i < 2; ++i)
					neuron_hidden[h].setInput(i, inputs[i]);
				neuron_hidden[h].calculateOutput();
			}
		}
		void calculate_output()
		{
			for (int h = 0; h < hidden_count; ++h)
				neuron_output.setInput(h, neuron_hidden[h].getOutput());
			neuron_output.calculateOutput();
			output = neuron_output.getOutput();
		}

		void backpropagate_output(float target)
		{
			neuron_output.calculateCorrection(output - target);
		}
		void backpropagate_hidden()
		{
			for (int h = 0; h < hidden_count; ++h)
				neuron_hidden[h].calculateCorrection(neuron_output.getError(h));
		}
		void update_all()
		{
			neuron_output.update();
			for (int h = 0; h < hidden_count; ++h)
				neuron_hidden[h].update();
		}
	public:
		Synaptic() {}
		Synaptic(float inputLearnRate)
		{
			learn_rate = inputLearnRate;

			inputs[0] = 1;
			inputs[1] = 1;
			for (int i = 0; i < hidden_count; ++i)
				neuron_hidden[i] = Neuron(learn_rate, 2);
			neuron_output = Neuron(learn_rate, hidden_count);
			output = 0;
		}

		void setInput(int inputPointer, float inputValue)
		{
			if (inputPointer >= 2 || inputPointer < 0)
				throw;
			inputs[inputPointer] = inputValue;
		}
		void calculateOutput()
		{
			calculate_outputs_hidden();
			calculate_output();
		}
		float getOutput()
		{
			return output;
		}

		void train(float inputTarget)
		{
			if (inputTarget > 1 || inputTarget < 0)
				throw;
			calculateOutput();
			backpropagate_output(inputTarget);
			backpropagate_hidden();
			update_all();
		}

		void destroy()
		{
			neuron_output.destroy();
			for (int h = 0; h < hidden_count; ++h)
				neuron_hidden[h].destroy();
		}
	};
}
