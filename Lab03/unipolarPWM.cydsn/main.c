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
#define PWN_SIGNAL_MAX 1024
//#undef DEBUG

int main()
{
    uint16 pwm_signal = 0;
    int16 diffposition = 0;
    uint8 sliderposition = NO_FINGER;
    uint8 lastposition = NO_FINGER;
    
    #ifdef DEBUG
    char DebugStr[50];
    uint16 last_pwm_signal = 0;
    #endif
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    CyGlobalIntEnable; /* Uncomment this line to enable global interrupts. */
    PWM_UNI_Start();
    Clock_UNI_Start();
    CapSense_Start();
    CapSense_InitializeAllBaselines();
    UART_Start();
    
    
    #ifdef DEBUG
    sprintf(DebugStr, "Starting this program\r\n");
    UART_UartPutString(DebugStr);
    #endif
    CapSense_UpdateEnabledBaselines();
    for(;;)
    {
        CapSense_UpdateEnabledBaselines();
        CapSense_ScanEnabledWidgets();
        while(CapSense_IsBusy()){}
        sliderposition = CapSense_GetCentroidPos(CapSense_LINEARSLIDER0__LS);
        
        if(sliderposition != NO_FINGER && sliderposition != lastposition)
        {
            if (lastposition != NO_FINGER) {
                diffposition = sliderposition - lastposition;
                if (-diffposition > pwm_signal) {
                    pwm_signal = 0;
                } else if ( diffposition + pwm_signal > PWN_SIGNAL_MAX) {
                    pwm_signal = PWN_SIGNAL_MAX;
                } else {
                    pwm_signal += diffposition;
                }
            }
            lastposition = sliderposition;
            PWM_UNI_WriteCompare(pwm_signal);
        } else {
            lastposition = NO_FINGER;
        }
        
        #ifdef DEBUG
        if (pwm_signal != last_pwm_signal)
        {
            last_pwm_signal = pwm_signal;
            sprintf(DebugStr, "Sliderpostion: %d\r\n", pwm_signal);
            UART_UartPutString(DebugStr);
        }
        #endif
    }
}

/* [] END OF FILE */
