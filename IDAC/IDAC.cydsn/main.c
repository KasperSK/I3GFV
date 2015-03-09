/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>

int main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    char step = 1;
    char value = 0;
    int sleep = 1;
    /* CyGlobalIntEnable; */ /* Uncomment this line to enable global interrupts. */
    IDAC_1_Start();
    for(;;)
    {
        /* Place your application code here. */
        value += step;
        if ((value == 200) || (value == 0)) {
            step = -step;
        }
        IDAC_1_SetValue(value);
        //CyDelay(sleep);
    }
}

/* [] END OF FILE */
