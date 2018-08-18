/* 
Ticker based scheduler for Mbed platform
This library doesnot execute functions automatically.
It just toggles a flag once the set time is elapsed

Currently supports only void type executables (funcs that take in nothing and returns nothing)
reference to function pointers https://www.eskimo.com/~scs/cclass/int/sx10a.html
*/
#pragma once
#include "mbed.h"
typedef void (*funcPtr_void)(); // datatype of pointer to function returning void

class scheduler
{
public:
  Ticker tick;
  float executionTimeGap;
  volatile bool executionFlag;
  funcPtr_void executableFunc; //executableFunc is a function pointer

  scheduler(float, funcPtr_void );
  void initialize();
  void flagISR(void);
  int checkAndExecute();
};

void scheduler::flagISR(void)
{
  executionFlag = true;
}
scheduler::scheduler(float timing, funcPtr_void func)
{
  executionTimeGap = timing;
  executableFunc = func; //store the memory address of funtion to execute!
}
void scheduler::initialize()
{
  executionFlag = false;
  tick.attach( callback(this,&scheduler::flagISR), executionTimeGap);
}
int scheduler::checkAndExecute()
{
  if(executionFlag == true){
    executionFlag = false;
    (*executableFunc)();
  }
  return 0;
}

