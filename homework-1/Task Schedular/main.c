#include <stdio.h>
#include "TaskScheduler.h"

void print_task_batch(Task* tasks, int quantity) {
    if (quantity == 0) {
        printf(" 0 \n");
        return;
    }
    for (int i = 0; i < quantity; i++) {
        printf(" Task [ID: %d] Name: '%s' (Next run: %u ms)\n",
            tasks[i].id, tasks[i].name, tasks[i].next_run_ms);
    }
    printf("\n");
}

#define BATCH_SIZE 5

int main(void)
{
    TaskScheduler* TS = TaskScheduler_Create();
    Task t1 = { 1, "A", 1000, 0 };   
    Task t2 = { 2, "B", 500, 0 };      
    Task t3 = { 3, "C", 0, 0 };      
    Task t4 = { 4, "D", 0, 2500 }; 
    Task t5 = { 5, "E", 0, 3000 };
    TaskScheduler_AddTask(TS,t1);
    TaskScheduler_AddTask(TS, t2);
    TaskScheduler_AddTask(TS, t3);
    TaskScheduler_AddTask(TS, t4);
    TaskScheduler_AddTask(TS, t5);
  
    
    Task ready_batch[BATCH_SIZE];
    int quan = 0;

    TaskScheduler_Update(TS, 0);
    quan = TaskScheduler_GetReadyTasks(TS, BATCH_SIZE, ready_batch);
    print_task_batch(ready_batch, quan);

    TaskScheduler_Update(TS, 500);
    quan = TaskScheduler_GetReadyTasks(TS, BATCH_SIZE, ready_batch);
    print_task_batch(ready_batch, quan);

    TaskScheduler_DeleteTask(TS, 2);
    printf("Active: %d\n\n", TaskScheduler_GetActiveQuan(TS));

    TaskScheduler_Update(TS, 1500);
    quan = TaskScheduler_GetReadyTasks(TS, BATCH_SIZE, ready_batch);
    print_task_batch(ready_batch, quan);

    TaskScheduler_Update(TS, 2500);
    quan = TaskScheduler_GetReadyTasks(TS, BATCH_SIZE, ready_batch);
    print_task_batch(ready_batch, quan);

    TaskScheduler_Update(TS, 3000);
    quan = TaskScheduler_GetReadyTasks(TS, BATCH_SIZE, ready_batch);
    print_task_batch(ready_batch, quan);

    Task test_for_info;
    if (TaskScheduler_GetTaskInfo(TS, 4, &test_for_info)==1)
    {
        printf("Error: Task 4 is not deleted\n");
    }
    else
    {
        printf("Task 4 is deleted\n");
    }
    printf("Active tasks: %d\n", TaskScheduler_GetActiveQuan(TS));

    TaskScheduler_Destroy(TS);
    
    printf("\nFinish\n");
    return 0;

}