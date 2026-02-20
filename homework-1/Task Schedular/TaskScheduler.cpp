#include "TaskScheduler.h"
#include <cstring>

struct NodeTask
{
	NodeTask(Task t): is_ready(false), task(t), Next(nullptr) {}
	Task task;
	bool is_ready;
	NodeTask* Next;
	
};

class Queue
{
public:
	Queue() : quantity_of_tasks(0), head(nullptr), tail(nullptr) {}
	int quantity_of_tasks;
	NodeTask* head;
	NodeTask* tail;
	~Queue()
	{
		NodeTask* curr = head;
		while (curr != nullptr)
		{
			NodeTask* next = curr->Next;
			delete curr;
			curr = next;
		}
	}
	void push_task(Task t)
	{
		NodeTask* NewNode = new NodeTask(t);
		if (head == nullptr)
		{
			head = NewNode;
			tail = NewNode;
		}
		else
		{
			tail->Next = NewNode;
			tail = NewNode;
		}
		quantity_of_tasks++;
	}
	void remove_by_id(int id)
	{
		if (head == nullptr) return;
		NodeTask* curr = head;
		NodeTask* prev = nullptr;

		while (curr != nullptr)
		{
			if (curr->task.id == id)
			{
				if (prev == nullptr)
				{
					head = curr->Next;
					if (head == nullptr) tail = nullptr;
				}
				else
				{
					prev->Next = curr->Next;
					if (curr == tail) tail = prev;
				}
				delete curr;
				quantity_of_tasks--;
				return;
			}
			prev = curr;
			curr = curr->Next;
		}
	}

	bool find_by_id(int id, Task* out)
	{
		NodeTask* curr = head;
		while (curr != nullptr)
		{
			if (curr->task.id == id)
			{
				if (out) *out = curr->task;
				return true;
			}
			curr = curr->Next;
		}
		return false;
	}

	bool pop_task(Task* out)
	{
		if (head == nullptr) return false;
		NodeTask* temp = head;
		*out = temp->task;
		head = head->Next;
		if (head == nullptr) tail = nullptr;
		delete temp;
		quantity_of_tasks--;
		return true;
	}
};


class TaskSchedulerImpl
{
public:
	Queue All_Tasks;
	Queue Ready_Tasks;
	void add_task(Task t)
	{
		
		if (All_Tasks.find_by_id(t.id, nullptr) == false)
		{
			All_Tasks.push_task(t);
		}
		
	}
	void delete_task(int id)
	{
		All_Tasks.remove_by_id(id);
	}
	bool get_task_info(int id, Task* out)
	{
		return All_Tasks.find_by_id(id, out);
	}
	int get_quantity_of_active()
	{
		return All_Tasks.quantity_of_tasks;
	}
	void update_scheduler(int curr_time)
	{
		NodeTask* curr = All_Tasks.head;
		NodeTask* prev = nullptr;
		while (curr != nullptr)
		{
			if (curr->task.next_run_ms <= curr_time)
			{
				Ready_Tasks.push_task(curr->task);
				if (curr->task.period_ms > 0)
				{
					curr->task.next_run_ms = curr_time + curr->task.period_ms;
					prev = curr;
					curr = curr->Next;
				}
				else
				{
					NodeTask* to_delete = curr;
					curr = curr->Next;
					if (prev == nullptr)
					{
						All_Tasks.head = curr;
						if (All_Tasks.head == nullptr)
						{
							All_Tasks.tail = nullptr;
						}
					}
					else
					{
						prev->Next = curr;
						if (curr == nullptr) All_Tasks.tail = prev;
					}
					delete to_delete;
					All_Tasks.quantity_of_tasks--;
				}
			}
			else
			{
				prev = curr;
				curr = curr->Next;
			}
		}
	}
	int pop_ready(Task* out_batch, int max_size)
	{
		int popped_tasks = 0;
		while (popped_tasks < max_size && Ready_Tasks.quantity_of_tasks>0)
		{
			Ready_Tasks.pop_task(&out_batch[popped_tasks]);
			popped_tasks++;
		}
		return popped_tasks;
	}
};
	

struct TaskScheduler
{	
	TaskSchedulerImpl* impl;
};

extern "C"
{	
	TaskScheduler* TaskScheduler_Create()
	{
		TaskScheduler* TS = new TaskScheduler();
		TS->impl = new TaskSchedulerImpl();
		return TS;
	}
	void TaskScheduler_Destroy(TaskScheduler* TS)
	{
		if (TS)
		{
			delete TS->impl;
			delete TS;
		}
	}
	void TaskScheduler_AddTask(TaskScheduler* TS, Task T)
	{
		if (TS && TS->impl) TS->impl->add_task(T);
	}
	void TaskScheduler_DeleteTask(TaskScheduler* TS, int T_id )
	{
		if (TS && TS->impl) TS->impl->delete_task(T_id);
	}
	int TaskScheduler_GetTaskInfo(TaskScheduler* TS, int T_id, Task* out)
	{
		if (TS && TS->impl)
		{	
			if (TS->impl->get_task_info(T_id, out)) return 1;
			else return 0;
			
		}
		return 0;
	}
	int TaskScheduler_GetActiveQuan(TaskScheduler* TS)
	{
		if (TS && TS->impl) return TS->impl->get_quantity_of_active();
		return 0;
	}
	void TaskScheduler_Update(TaskScheduler* TS, int current_time)
	{
		if (TS && TS->impl) TS->impl->update_scheduler(current_time);
	}
	int TaskScheduler_GetReadyTasks(TaskScheduler* TS, int quan, Task* out)
	{
		if (TS && TS->impl) return TS->impl->pop_ready(out, quan);
		return 0;
	}
	}