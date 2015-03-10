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

int main()
{
    uint16 pwm_signal = 0;
    int16 diffposition = 0;
    uint8 sliderposition = NO_FINGER;
    uint8 lastposition = NO_FINGER;
    uint8 mode = 0;
    uint8 rotation = 1;
    uint8 lastrotation = 1;
    #ifdef DEBUG
    char debug_msg[50];
    uint16 last_pwm_signal;
    #endif
        
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    CyGlobalIntEnable;  /* Uncomment this line to enable global interrupts. */
    PWM_BI_Start();
    Clock_BI_Start();
    CapSense_Start();
    CapSense_InitializeAllBaselines();
    UART_Start();
    #ifdef DEBUG
    sprintf(debug_msg, "Starting this program\r\n");
    UART_UartPutString(debug_msg);
    #endif
    Pin_CCW_Write(!rotation);
    Pin_CW_Write(rotation);
    for(;;)
    {
        CapSense_UpdateEnabledBaselines();
        CapSense_ScanEnabledWidgets();
        while(CapSense_IsBusy()){}
        sliderposition = CapSense_GetCentroidPos(CapSense_LINEARSLIDER0__LS);
        if(sliderposition != NO_FINGER)
        {
            if(mode == 1)
            {
                rotation = (sliderposition < 100 ? 1 : 0);
                if ( rotation != lastrotation)
                {
                    Pin_CW_Write(rotation);
                    Pin_CCW_Write(!rotation);
                    #ifdef DEBUG
                    sprintf(debug_msg, "Going: %d\r\n", rotation);
                    UART_UartPutString(debug_msg);
                    #endif
                }
                lastrotation = rotation;
            }
            
            if(mode == 0)
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
                PWM_BI_WriteCompare(pwm_signal);
                
            }
            
            #ifdef DEBUG
            if (pwm_signal != last_pwm_signal)
            {
                last_pwm_signal = pwm_signal;
                sprintf(debug_msg, "Sliderpostion: %d\r\n", pwm_signal);
                UART_UartPutString(debug_msg);
            }
            #endif
        }
        lastposition = sliderposition;
        if(!Pin_PB_Read())
        {
            while(!Pin_PB_Read());
            mode = !mode;
            #ifdef DEBUG
            sprintf(debug_msg, "Going to mode: %d\r\n", mode);
            UART_UartPutString(debug_msg);
            #endif
        }
    }
    return 0;
}

/* [] END OF FILE */
