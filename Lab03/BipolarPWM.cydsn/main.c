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
#define DEBUGUSR 5

int main()
{
    uint8 sliderposition= NO_FINGER;
    uint8 lastposition = NO_FINGER;
    uint8 mode = 0;
    char Debug[50];
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    CyGlobalIntEnable;  /* Uncomment this line to enable global interrupts. */
    PWM_BI_Start();
    Clock_BI_Start();
    CapSense_Start();
    CapSense_InitializeAllBaselines();
    UART_Start();

    #ifdef DEBUGUSR
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
            if(lastposition != sliderposition)
            {
                lastposition = sliderposition;   
                if(mode == 0)
                {
                    PWM_BI_WriteCompare(lastposition);

                }
                if(mode == 1)
                {
                    if(sliderposition < 100)
                    {
                        Pin_CCW_Write(0);
                        Pin_CW_Write(1);
                    }
                    if(sliderposition > 140)
                    {
                        Pin_CW_Write(0);
                        Pin_CCW_Write(1);
                    }
                }
            }
        }
        if(!Pin_PB_Read())
        {
            while(!Pin_PB_Read());
            mode = !mode;
        }
    }
}

/* [] END OF FILE */
