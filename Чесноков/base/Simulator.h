#pragma once
#include "TQueue.h"

/* ���������� ������ ���������� �� ������ ������
 * 0 - 1 ����
 * 1 - 2 �����
 * 2 - 3 �����
 * 3 - 1 ����
 * 4 - 2 �����
*/
typedef int job_t;
const job_t Jobs_time[5] = { 1, 2, 3, 1, 2 };
enum class Simulation_Exceptions
{
	Negative_Value
};

class TJobStream
{
private:
	TQueue q;               // ������� ������
	double JobIntens;       // ����������� ��������� ����� ������ �� ��������
public:
	TJobStream(int Intens, int queue_size);
	job_t GetNewJob(void);  // ��������� ������ �� ������ �����
	// �������� ��������� ������ ����� (false ���� ����� ������ �� ����������� � �������)
	bool Stream_Tick();
	int Size() { return q.Size(); }
	
};

class TProc
{
private:
	job_t JobID;                 // ID ����������� ������
	int cycles_of_job_remain;  // �������� ������ ��� ���������� ������� ������
	int cycles_remain;         // �������� ��������� ������
	TJobStream JobStream;      // ����� ����� ��� ����������
	int mode;                  // ����� 0-������� 1-��������� (� ����������� �� ������ �����)

	bool RunNewJob(void);      // false ���� ���� ����� �� ����������
	bool IsProcBusy(void) { return cycles_of_job_remain != 0; }
	void Process(void);        // ���������� ���� ���� ������

	// �������������� ������
	int job_missed, waiting, job_count, cycle_count;
public:
	TProc(int JobIntens, int Cycles_of_simulation, int queueSize);
	bool Proc_Tick();
	int JobMissed() { return job_missed; }
	int WaitCount() { return waiting; }
	int JobCount() { return job_count; }
	void PrintStats();
	
};

int RandomNumber(int min, int max);
// �������� �� ������� � ����������� percent%
bool Random(int percent);
void Wait(int time);