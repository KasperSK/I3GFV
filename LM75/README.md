I2C Component named TEMPERATUR is needed




```c
#include "LM75.h"
#include <project.h>
#include <stdio.h>

int main()
{
    LM75_t T1 = Create_LM75(0);  //Id set on the dipswitch
    LM75_t T2 = Create_LM75(1);  //Id set on the dipswitch
    
    UART_Start();
    char str[30];
    
    CyGlobalIntEnable;
    
    for(;;)
    {
        LM75_poll(T1);
        CyDelay(300);
        LM75_poll(T2);
        CyDelay(300);
        UART_PutString("\033[2J");
        UART_PutString("\033[0;0H");
        sprintf(str, "T1 = %d.%d T2 = %d.%d", LM75_temperature(T1)/10, LM75_temperature(T1)%10, LM75_temperature(T2)/10, LM75_temperature(T2)%10);
        UART_PutString(str);
    }
}
```
