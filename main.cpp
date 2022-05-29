#include "Console.h"
#include "Neunet.h"


int main()
{
	float x[4] = {
		0, 1, 0, 1
	};
	float y[4] = {
		0, 0, 1, 1
	};
	float target[4] = {
		0, 1, 1, 0
	};

	neunet::Neunet net = neunet::Neunet(.003);
	for (int r = 0; r < 5; ++r)
	{
		net.train(x, y, target, 10000);

		for (int i = 0; i < 4; ++i)
			console::write(net.predict(x[i], y[i]));
		console::write();
	}
	net.destroy();
	return 0;
}
