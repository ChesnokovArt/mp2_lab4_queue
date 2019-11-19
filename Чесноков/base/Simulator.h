#pragma once
#include "TQueue.h"

/* количество циклов процессора на каждую задачу
 * 0 - 1 цикл
 * 1 - 2 цикла
 * 2 - 3 цикла
 * 3 - 1 цикл
 * 4 - 2 цикла
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
	TQueue q;               // очередь команд
	double JobIntens;       // вероятность получения новой задачи на итерации
public:
	TJobStream(int Intens, int queue_size);
	job_t GetNewJob(void);  // получение задачи из потока задач
	// итерация симуляции потока задач (false если новая задача не поместилась в очередь)
	bool Stream_Tick();
	int Size() { return q.Size(); }
	
};

class TProc
{
private:
	job_t JobID;                 // ID выполняемой задачи
	int cycles_of_job_remain;  // осталось циклов для выполнения текущей задачи
	int cycles_remain;         // осталось выполнить циклов
	TJobStream JobStream;      // поток задач для процессора
	int mode;                  // режим 0-быстрый 1-медленный (с распечаткой на каждом цикле)

	bool RunNewJob(void);      // false если нету задач на выполнение
	bool IsProcBusy(void) { return cycles_of_job_remain != 0; }
	void Process(void);        // просчитать один цикл задачи

	// статистические данные
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
// случится ли событие с вероятность percent%
bool Random(int percent);
void Wait(int time);