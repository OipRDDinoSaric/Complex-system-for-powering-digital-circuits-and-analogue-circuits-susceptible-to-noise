#include <xc.h>

#include "system.h"

#include "usb.h"
#include "usb_device.h"
#include "usb_device_cdc.h"

#define _XTAL_FREQ 48000000

static uint8_t readBuffer[CDC_DATA_OUT_EP_SIZE];
static uint8_t writeBuffer[CDC_DATA_OUT_EP_SIZE];

MAIN_RETURN main(void)
{
    SYSTEM_Initialize(SYSTEM_STATE_USB_START);
    USBDeviceInit();
    USBDeviceAttach();
    CDCInitEP();
    CDCSetBaudRate(1200);
    
    ANSELB=0x00;
    ANSELC=0x00;
	TRISB=0x00;
	TRISC=0x00;
    PORTCbits.RC2=1; // 24_12 - OFF
    PORTBbits.RB4=0; // 12_5 - OFF
    
    while(1){
        if( USBUSARTIsTxTrfReady() == true){
            RB7=0; // LED - OFF
            __delay_ms(500);
            uint8_t numBytesRead, i;
            numBytesRead = getsUSBUSART(readBuffer, sizeof(readBuffer));
            if(numBytesRead > 0){
                
                RB7 = 1; //LED - ON
                __delay_ms(1000);
                
                
                    switch(readBuffer[0]){
						case 1: // 24_12_OFF
							PORTCbits.RC2=1;
							break;
						case 2: // 24_12_ON
							PORTCbits.RC2=0;
							break;
						case 3: //12_5_OFF
							PORTBbits.RB4=0;
                            //PORTBbits.RB4=0;
							break;
						case 4: //12_5_ON
							PORTBbits.RB4=1;
                            //PORTBbits.RB4=1;
							break;
						default:
                            //LED - blink
                            for(i=0;i<15;i++){
							RB7 = ~RB7;
                            __delay_ms(100);
                            }
							break;
					}
                
            }
        }
        CDCTxService();
    }
}