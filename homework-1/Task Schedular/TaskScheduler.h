#ifndef TASKSCHEDULER_H
#define TASKSCHEDULER_H
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
	
	typedef struct {
		int id;
		const char* name;
		uint32_t period_ms;
		uint32_t next_run_ms;
	} Task;

	typedef struct TaskScheduler TaskScheduler;
	TaskScheduler* TaskScheduler_Create();
	void TaskScheduler_Destroy(TaskScheduler* TS);
	void TaskScheduler_AddTask(TaskScheduler* TS,Task T);
	void TaskScheduler_DeleteTask(TaskScheduler* TS, int T_id);
	int TaskScheduler_GetTaskInfo(TaskScheduler* TS,int T_id, Task* out);
	int TaskScheduler_GetActiveQuan(TaskScheduler* TS);
	void TaskScheduler_Update(TaskScheduler* TS, int current_time);
	int TaskScheduler_GetReadyTasks(TaskScheduler* TS, int quan, Task* out);

#ifdef __cplusplus
}
#endif
#endif