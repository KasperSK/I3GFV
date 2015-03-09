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
#include <stdio.h>

#define NO_FINGER 0xFF
#define DEBUG

int main()
{
    uint8 sliderposition= NO_FINGER;
    uint8 lastposition = NO_FINGER;
    
    char Debug[50];
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    CyGlobalIntEnable; /* Uncomment this line to enable global interrupts. */
    PWM_UNI_Start();
    Clock_UNI_Start();
    CapSense_Start();
    CapSense_InitializeAllBaselines();
    UART_Start();
    
    
    #ifdef DEBUG
    sprintf(Debug, "Starting this program\r\n");
    UART_PutString(Debug);
    #endif
    
    for(;;)
    {
        CapSense_UpdateEnabledBaselines();
        CapSense_ScanEnabledWidgets();
        while(CapSense_IsBusy()){}
        sliderposition = CapSense_GetCentroidPos(CapSense_LINEARSLIDER0__LS);
        
        if(sliderposition != NO_FINGER)
        {
            lastposition = sliderposition;
            if(sliderposition < 250)
            {
                PWM_UNI_WriteCompare(sliderposition);
            }
        }
        
        #ifdef DEBUG 
        sprintf(Debug, "Sliderpostion: %d\r\n", sliderposition);
        UART_PutString(Debug);
        #endif
        CyDelay(500);
    }
}

/* [] END OF FILE */
