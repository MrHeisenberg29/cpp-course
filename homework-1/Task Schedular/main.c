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
    TaskScheduler* TS = Create_Task_Scheduler();
    Task t1 = { 1, "A", 1000, 0 };   
    Task t2 = { 2, "B", 500, 0 };      
    Task t3 = { 3, "C", 0, 0 };      
    Task t4 = { 4, "D", 0, 2500 }; 
    Task t5 = { 5, "E", 0, 3000 };
    add_task_to_Scheduler(t1,TS);
    add_task_to_Scheduler(t2, TS);
    add_task_to_Scheduler(t3, TS);
    add_task_to_Scheduler(t4, TS);

    
    Task ready_batch[BATCH_SIZE];
    int quan = 0;

    update_time_in_TS(TS, 0);
    quan = get_ready_tasks(TS, BATCH_SIZE, ready_batch);
    print_task_batch(ready_batch, quan);

    update_time_in_TS(TS, 500);
    quan = get_ready_tasks(TS, BATCH_SIZE, ready_batch);
    print_task_batch(ready_batch, quan);

    delete_task_from_Scheduler(2, TS);
    printf("Active: %d\n\n", get_quantity_of_active_tasks(TS));

    update_time_in_TS(TS, 1500);
    quan = get_ready_tasks(TS, BATCH_SIZE, ready_batch);
    print_task_batch(ready_batch, quan);

    update_time_in_TS(TS, 2500);
    quan = get_ready_tasks(TS, BATCH_SIZE, ready_batch);
    print_task_batch(ready_batch, quan);

    update_time_in_TS(TS, 3000);
    quan = get_ready_tasks(TS, BATCH_SIZE, ready_batch);
    print_task_batch(ready_batch, quan);

    Task test_for_info;
    if (get_info_about_task(4, TS, &test_for_info)==1)
    {
        printf("Error: Task 4 is not deleted\n");
    }
    else
    {
        printf("Task 4 is deleted\n");
    }
    printf("Active tasks: %d\n", get_quantity_of_active_tasks(TS));

    Destroy_Task_Scheduler(TS);
    
    printf("\nFinish\n");
    return 0;

}