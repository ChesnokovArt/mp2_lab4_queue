#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Simulator.h"
#ifdef _WIN32
#include "windows.h"
#endif 
#ifdef __linux__
#include "unistd.h"
#endif

using namespace std;

int RandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

// �������� �� ������� � ����������� percent%
bool Random(int percent)
{
	if (percent < 0) percent = 0;
	else if (percent > 100) percent = 100;
	return (RandomNumber(0, 100) <= percent);
}

void Wait(int time)  // time - �������� ���� �������
{
#ifdef _WIN32
	Sleep(time);
#endif 
#ifdef __linux__
	sleep(time / 1000);
#endif
}

TJobStream::TJobStream(int Intens, int queue_size) : q(queue_size)
{
	srand(static_cast<unsigned int>(time(0)));
	JobIntens = Intens;
}

job_t TJobStream::GetNewJob(void)
{
	// ���� � ������� ���� ����� ������������ ��� �������
	if (q.isEmpty()) return -1;
	return q.Get();
}

bool TJobStream::Stream_Tick()
{
	if (Random(JobIntens))
	{
		// �� ������� ����� � �����
		if (q.isFull()) return false;
		job_t job = RandomNumber(0, 4);
		q.Put(job);
		return true;
	}
	else return true;
}

bool TProc::RunNewJob(void)
{
	job_t job = JobStream.GetNewJob();
	if (job == -1) return false;
	else
	{
		JobID = job;
		cycles_of_job_remain = Jobs_time[job];
		return true;
	}
}

void TProc::Process(void)
{
	if (cycles_of_job_remain)
	{
		if (mode)
		{
			cout << "����������� ������ � ������� " << JobID 
				<< ", ������ ��������: " << cycles_of_job_remain << endl;
		}
		cycles_of_job_remain--;
	}
	if (cycles_of_job_remain == 0 && JobID != -1)
	{
		if (mode)
		{
			cout << "������ � ������� " << JobID
				<< " �����������" << endl;
		}
		job_count++;
		JobID = -1;  // -1 ������ �� ���������
		//(������������� ��� JobID == -1 --> cycles_of_job_remain == 0)
	}
}

TProc::TProc(int JobIntens = 50, int Cycles_of_simulation = 25, int queueSize = 5)
	: JobStream(JobIntens, queueSize),
	cycles_remain(Cycles_of_simulation), JobID(-1), cycles_of_job_remain(0)
{
	if (JobIntens < 0 || Cycles_of_simulation < 0) throw Simulation_Exceptions::Negative_Value;
	//  ���� ������ ��������� ������ 20 �� ����������� � ������� ������
	if (Cycles_of_simulation > 20) mode = 0; else mode = 1;
	job_missed = 0; waiting = 0; job_count = 0; cycle_count = 0;
}

bool TProc::Proc_Tick()
{
	cycle_count++;
	// � ��������� ������ ��������� ���������� � ����� ����� ���������
	if (mode)
	{
		cout << "------������ ����� " << cycle_count << "------" << endl;
	}
	if (!JobStream.Stream_Tick())
	{
		job_missed++;
		if (mode)
		{
			cout << "����� �� ���������� � ������� ������ (������� �����������)" << endl;
		}
	}
	if (!IsProcBusy())
	{
		if (RunNewJob())
		{
			if (mode)
			{
				cout << "�������� ����������� ������ � ����� " << JobID << endl;
			}
		}
		else
		{
			waiting++;
			if (mode)
			{
				cout << "��������� ����������� �� ������ �����" << endl;
			}
		}
	}
	Process();
	
	if (mode)
	{
		cout << "------����� ����� ����������------" << endl;
		cout << "������ ��������� �������� "<< cycles_remain << endl;
		Wait(1200);
	}
	return --cycles_remain;
}

void TProc::PrintStats()
{
	cout.precision(2);
	cout << "��������� ��������� � ������������:" << endl;
	cout << "������� ����������� �����: " << job_count << endl;
	cout << "������� ���������: " << job_missed 
		<< "(" << (float)(job_missed * 100) / job_count << "%)" << endl;
	cout << "���������� ������ ���������: " << cycle_count << endl;
	cout << "���������� ������ �������: " << waiting
		<< "(" << (float)(waiting * 100 / cycle_count) << "%)" << endl;
	cout << "������� ���������� ������ �� �������: " << (float)(cycle_count - waiting) / job_count << endl;
}
