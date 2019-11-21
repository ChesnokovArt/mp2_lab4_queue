#include <iostream>
#include <ctime>
#include <locale>
#include "TQueue.h"
#include "Simulator.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");
	char c = 'g';
	while (c != 'q')
	{
		try
		{
			int intens, cycles, queue_size;
			cout << "¬ведите интенсивность задач (0-100%): ";
			cin >> intens;
			cout << "¬ведите количество циклов симул€ции (>20 в быстром режиме): ";
			cin >> cycles;
			cout << "¬ведите размер очереди задач: ";
			cin >> queue_size;
			TProc processor(intens, cycles, queue_size);
			while (processor.Proc_Tick());
			processor.PrintStats();
		}
		catch (const Simulation_Exceptions e)
		{
			switch (e)
			{
			case Simulation_Exceptions::Negative_Value:
				cout << "¬ведены отрицательные значени€" << endl;
			default:
				break;
			}
		}
		catch (const TStackException e)
		{
			switch (e)
			{
			case TStackException::NegativeSize:
				cout << "Ќельз€ создать очередь отрицательной длины" << endl;
			default:
				break;
			}
		}
		cout << "¬ведите любой символ, чтобы продолжить или q, чтобы выйти: ";
		cin >> c;
	}
	return 0;
}