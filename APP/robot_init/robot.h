#ifndef ROBOT_H 
#define ROBOT_H 

#ifdef __cplusplus
extern "C"{
#endif

/*----------------------------------include-----------------------------------*/
#include "com_config.h"
#include "bsp_can.h"
#include "robot_task.h"
/*-----------------------------------macro------------------------------------*/

/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/

/*----------------------------------function----------------------------------*/
void Robot_Init();

#ifdef __cplusplus
}
#endif

#endif	/* ROBOT_H */