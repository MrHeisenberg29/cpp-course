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
	TaskScheduler* Create_Task_Scheduler();
	void Destroy_Task_Scheduler(TaskScheduler* TS);
	void add_task_to_Scheduler(Task T, TaskScheduler* TS);
	void delete_task_from_Scheduler(int T_id, TaskScheduler* TS);
	int get_info_about_task(int T_id, TaskScheduler* TS, Task* out);
	int get_quantity_of_active_tasks(TaskScheduler* TS);
	void update_time_in_TS(TaskScheduler* TS, int current_time);
	int get_ready_tasks(TaskScheduler* TS, int quan, Task* out);

#ifdef __cplusplus
}
#endif
#endif