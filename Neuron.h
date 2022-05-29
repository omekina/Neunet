#pragma once
#include "Array.h"
#include "Random.h"


namespace neunet
{
	class Neuron
	{
	private:
		float learn_rate;

		arr::FloatArr inputs;

		arr::FloatArr weights;
		arr::FloatArr correction_weights;

		float output;
		float correction_output;

		float e = 2.7182818284590452353602874713527;
		
		float logistic_forward(float x)
		{
			float y = x;
			if (y < 0) { y = 0; }
			if (y > 1) { y = 1; }
			return y;
		}
		float logistic_backwards(float x)
		{
			float y = 1;
			if (x < 0 || x > 1) { y = 0; }
			return y;
		}

		void calculate_correction_output(float input_error_total)
		{
			float derivative = input_error_total * logistic_backwards(output);
			correction_output = derivative;
		}
		void clamp_weights()
		{
			for (int i = 0; i < weights.getSize(); ++i)
			{
				if (weights.get(i) > 10e10) { weights.set(i, 1); }
				else if (weights.get(i) < -10e10) { weights.set(i, -1); }
			}
		}
		void calculate_correction_weights()
		{
			for (int i = 0; i < inputs.getSize(); ++i)
			{
				float current_input = inputs.get(i);
				float current_weight = weights.get(i);
				float current_correction = correction_output * current_input * learn_rate * current_weight;
				correction_weights.set(i, current_weight - current_correction);
			}
			float current_weight = weights.get(weights.getSize() - 1);
			float current_correction = correction_output * learn_rate * current_weight;
			correction_weights.set(weights.getSize() - 1, current_weight - current_correction);
		}

		void initialize_weights()
		{
			for (int i = 0; i < weights.getSize(); ++i)
				weights.set(i, random::random());
		}
	public:
		Neuron() {}
		Neuron(float inputLearnRate, int inputInputCount)
		{
			learn_rate = inputLearnRate;
			if (inputInputCount < 0)
				throw;
			inputs = arr::FloatArr(inputInputCount);
			weights = arr::FloatArr(inputInputCount + 1);
			correction_weights = arr::FloatArr(inputInputCount + 1);

			initialize_weights();

			output = 0;
			correction_output = 0;
		}

		void calculateOutput()
		{
			float sum = 0;
			for (int i = 0; i < inputs.getSize(); ++i)
				sum += inputs.get(i) * weights.get(i);
			sum += weights.get(weights.getSize() - 1);
			float sum_logistic = logistic_forward(sum);
			output = sum_logistic;
		}
		void calculateCorrection(float errorTotal)
		{
			calculate_correction_output(errorTotal);
			calculate_correction_weights();
		}

		void setInput(int inputPointer, float inputValue)
		{
			inputs.set(inputPointer, inputValue);
		}
		float getOutput()
		{
			return output;
		}

		float getError(int inputPointer)
		{
			return correction_output * weights.get(inputPointer);
		}

		void update()
		{
			output = correction_output;
			for (int i = 0; i < weights.getSize(); ++i)
				weights.set(i, correction_weights.get(i));
			correction_output = 0;
			clamp_weights();
		}

		void destroy()
		{
			output = 0;
			correction_output = 0;
			inputs.remove();
			weights.remove();
			correction_weights.remove();
		}
	};
}
