  /*
 * sheduler.c
 *
 *  Created on: Nov 21, 2021
 *      Author: Win10
 */
#include "schedule.h"
#include "main.h"

int task_count = 0;
void SCH_Init(void){
	task_count = 0;
	for(int index = 0; index < SCH_MAX_TASKS;index++){
		SCH_Tasks[index].pTask= 0x0000;
		SCH_Tasks[index].Delay= 0;
		SCH_Tasks[index].Period= 0;
		SCH_Tasks[index].Runtime= 0;
	}
}
void SCH_relocate(void (*pFunction)(),int Period){
	for(int index = 0 ;index < task_count-1;index++){
		SCH_Tasks[index].pTask = SCH_Tasks[index+1].pTask;
		SCH_Tasks[index].Delay = SCH_Tasks[index+1].Delay;
		SCH_Tasks[index].Period = SCH_Tasks[index+1].Period;
		SCH_Tasks[index].Runtime = SCH_Tasks[index+1].Runtime;
	}
	SCH_Delete(task_count-1);
	if(Period){
		SCH_Add_Task(pFunction,Period, Period);
	}
}
void SCH_Update(void){
//	for (int i =0; i<SCH_MAX_TASKS; i++){
//		if (SCH_Tasks[i].pTask){
//			if(SCH_Tasks[i].Delay==0){
//				SCH_Tasks[i].Runtime+=1;
//				if (SCH_Tasks[i].Period){
//					SCH_Tasks[i].Delay=SCH_Tasks[i].Period;
//				}
//			} else {
//				SCH_Tasks[i].Delay -=1;
//			}
//		}
//	}
	if(SCH_Tasks[0].pTask){
		if(SCH_Tasks[0].Delay == 0){
			SCH_Tasks[0].Runtime = 1;
		}else{
			SCH_Tasks[0].Delay -=1;
		}
	}
}

void SCH_Add_Task(void (*pFunction)(), int Delay, int Period){
	int i =0;
	if(task_count != 0){
		while ((Delay > SCH_Tasks[i].Delay)&&(i < SCH_MAX_TASKS)){
			i++;
		}
		if (i==SCH_MAX_TASKS){
			return;
		}
		for(int index = i+1; index < SCH_MAX_TASKS;i++){
			SCH_Tasks[index].pTask = SCH_Tasks[index-1].pTask;
			SCH_Tasks[index].Delay = SCH_Tasks[index-1].Delay;
			SCH_Tasks[index].Period = SCH_Tasks[index-1].Period;
			SCH_Tasks[index].Runtime = SCH_Tasks[index-1].Runtime;
		}
		SCH_Tasks[i].Delay = Delay - SCH_Tasks[i-1].Delay;

	}
	else{
		// first
		SCH_Tasks[i].Delay = Delay;
	}
	SCH_Tasks[i].pTask = pFunction;
	SCH_Tasks[i].Period = Period;
	SCH_Tasks[i].Runtime = 0;
	++task_count;
}
void SCH_Dispatcher(void){
		if (SCH_Tasks[0].Runtime > 0){
			(*SCH_Tasks[0].pTask)();
			SCH_Tasks[0].Runtime = 0;
			SCH_relocate(SCH_Tasks[0].pTask, SCH_Tasks[0].Period);
		}
}

void SCH_Delete(int index){
	task_count--;
	SCH_Tasks[index].pTask= 0x0000;
	SCH_Tasks[index].Delay= 0;
	SCH_Tasks[index].Period= 0;
	SCH_Tasks[index].Runtime= 0;
}

