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
#define SECOND 100
#define DEBUGUSR

uint8 step = 8;

void stepForward(void)
{
    if(step == 0){
        step = 8;
    }else{
        step >>= 1;
    }
    Pin_Stepper_Write(step);
}

void stepBackward(void)
{
    if(step == 8){
        step = 0;
    }else{
        step <<= 1;
    }
    Pin_Stepper_Write(step);
}

int main()
{
    uint8 sliderposition= NO_FINGER;
    uint8 lastposition = NO_FINGER;
    uint8 mode = 0;
    uint8 fullstep = 0;
    uint8 time = SECOND;
    char Debug[50];
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    /* CyGlobalIntEnable; */ /* Uncomment this line to enable global interrupts. */
    CapSense_Start();
    CapSense_InitializeAllBaselines();
    UART_Start();
    Pin_Stepper_Write(step);
    

    sprintf(Debug, "Starting this program\r\n");
    UART_UartPutString(Debug);

    for(;;)
    {
        /*
        CapSense_UpdateEnabledBaselines();
        CapSense_ScanEnabledWidgets();
        while(CapSense_IsBusy()){}
        sliderposition = CapSense_GetCentroidPos(CapSense_LINEARSLIDER0__LS);
        
        if(sliderposition != NO_FINGER)
        {
            if(lastposition != sliderposition)
            {
                lastposition = sliderposition;
                 
                switch(mode)
                {
                    case 0 :
                        if(lastposition < 120){
                            stepBackward();
                        }
                        if(lastposition > 120){
                            stepForward();
                        }
                        break;
                    case 1 :
                        fullstep = !fullstep;
                        break;
                    case 2 : 
                        break;
                    case 3 :
                        break;
                    default :
                        fullstep = 0;
                        break;
                }
            }            
        }
        if(fullstep)
        {
            stepForward();
            CyDelay(time--);
            if(time > 100){
                time = SECOND;
            }
        }
            
        if(!Pin_PB_Read())
        {
            while(!Pin_PB_Read());
            if(mode < 4)
            {
                ++mode;
            }else{
                mode = 0;
            }
        }*/
        Pin_Stepper_Write(8);
        Pin_TEST_Write(1);
        CyDelay(5000);
        Pin_TEST_Write(0);
    }
}

/* [] END OF FILE */
