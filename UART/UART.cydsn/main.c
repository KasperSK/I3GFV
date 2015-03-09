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
    uint8 ch;
    UART_1_Start();
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    UART_1_UartPutString("Initializing: Done\n");
    /* CyGlobalIntEnable; */ /* Uncomment this line to enable global interrupts. */
    for(;;)
    {
        ch = UART_1_UartGetChar();
        
        if (0u != ch) {
            UART_1_UartPutChar(ch);   
        }
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
