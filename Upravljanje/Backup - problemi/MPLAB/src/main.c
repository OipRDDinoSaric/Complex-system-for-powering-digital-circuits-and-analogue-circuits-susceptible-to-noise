#include <xc.h>

#include "system.h"
#include "usb.h"
#include "usb_device.h"
#include "usb_device_cdc.h"

#include "mcc_generated_files/mcc.h"

//#include "spi.h"

#define _XTAL_FREQ 48000000

static uint8_t readBuffer[CDC_DATA_OUT_EP_SIZE];
static uint8_t writeBuffer[CDC_DATA_IN_EP_SIZE];

MAIN_RETURN main(void)
{
    SYSTEM_Initialize(SYSTEM_STATE_USB_START);
    USBDeviceInit();
    USBDeviceAttach();
    CDCInitEP();
    CDCSetBaudRate(1200);
    
    TRISB7=0; //RB7 - OUTPUT
    TRIS=0; //RB7 - OUTPUT
    TRISB7=0; //RB7 - OUTPUT
    RC2=1; // 24_12 - OFF
    RB4=0; // 12_5 - ON
    
    
    while(1){
        RB7=1; // LED - ON
        if( USBUSARTIsTxTrfReady() == true){
                       
            uint8_t i, numBytesRead, a;
            
            
            numBytesRead = getsUSBUSART(readBuffer, sizeof(readBuffer));

            if(numBytesRead > 0){
                __delay_ms(1000);
                RB7 = 0; //LED - OFF
                
                a=*readBuffer;
                switch(a){
                    case 10: // 24_12_OFF
                        RC2=1;
                        break;
                    case 11: // 24_12_ON
                        RC2=0;
                        break;
                    case 20: //12_5_OFF
                        RB4=0;
                        break;
                    case 21: //12_5_ON
                        RB4=1;
                        break;
                    default:
                        break;
                }
            }
        }
        CDCTxService();
    }
}
