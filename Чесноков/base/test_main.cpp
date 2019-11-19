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
			cout << "������� ������������� ����� (0-100%): ";
			cin >> intens;
			cout << "������� ���������� ������ ��������� (>20 � ������� ������): ";
			cin >> cycles;
			cout << "������� ������ ������� �����: ";
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
				cout << "������� ������������� ��������" << endl;
			default:
				break;
			}
		}
		catch (const TStackException e)
		{
			switch (e)
			{
			case TStackException::NegativeSize:
				cout << "������ ������� ������� ������������� �����" << endl;
			default:
				break;
			}
		}
		cout << "������� ����� ������, ����� ���������� ��� q, ����� �����: ";
		cin >> c;
	}
	return 0;
}