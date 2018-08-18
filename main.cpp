#include"mbed.h"
#include "scheduler.h"

Serial pc(USBTX,USBRX);
DigitalOut led(LED1);
Timer tim;
void dataLogger();
void led_function();
void loop();

scheduler uartHandler(0.05, &dataLogger); //Attach the functions to Scheduler objects
scheduler ledHandler(0.100, &led_function);

int main()
{   
    tim.start();
    pc.baud(115200);
    
    uartHandler.initialize(); //Start the ticker
    ledHandler.initialize(); 
    while(1) loop();    
}
    
void loop()
{
    //Keep the functions short!!
    uartHandler.checkAndExecute(); //check for execute flags raised by scheduler-Ticker and execute the function
    ledHandler.checkAndExecute();
}
    
void dataLogger()
{   
    pc.printf("%ld ",tim.read_us());
    pc.printf("hello world\n");
}
void led_function()
{   
    pc.printf("%ld LED\n",tim.read_us());
    led = !led;
}