// Battery Status Indicator
// Version: 1.0
// Microcontroller: PIC16F1933

#define _XTAL_FREQ 500000
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

#define LED1 LATCbits.LATC4
#define LED2 LATCbits.LATC5
#define LED3 LATCbits.LATC6
#define LED4 LATCbits.LATC7
#define LED5 LATBbits.LATB0
#define LED6 LATBbits.LATB1
#define LED7 LATBbits.LATB2
#define LED8 LATBbits.LATB3
#define LED9 LATBbits.LATB4
#define LED10 LATBbits.LATB5

#include <xc.h>

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection->INTOSC oscillator: I/O function on CLKIN pin
#pragma config WDTE = OFF    // Watchdog Timer Enable->WDT disabled
#pragma config PWRTE = OFF    // Power-up Timer Enable->PWRT disabled
#pragma config MCLRE = ON    // MCLR Pin Function Select->MCLR/VPP pin function is MCLR
#pragma config CP = OFF    // Flash Program Memory Code Protection->Program memory code protection is disabled
#pragma config CPD = OFF    // Data Memory Code Protection->Data memory code protection is disabled
#pragma config BOREN = ON    // Brown-out Reset Enable->Brown-out Reset enabled
#pragma config CLKOUTEN = OFF    // Clock Out Enable->CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin
#pragma config IESO = ON    // Internal/External Switchover->Internal/External Switchover mode is enabled
#pragma config FCMEN = ON    // Fail-Safe Clock Monitor Enable->Fail-Safe Clock Monitor is enabled

// CONFIG2
#pragma config WRT = OFF    // Flash Memory Self-Write Protection->Write protection off
#pragma config VCAPEN = OFF    // Voltage Regulator Capacitor Enable->All VCAP pin functionality is disabled
#pragma config PLLEN = OFF    // PLL Enable->4x PLL disabled
#pragma config STVREN = ON    // Stack Overflow/Underflow Reset Enable->Stack Overflow or Underflow will cause a Reset
#pragma config BORV = LO    // Brown-out Reset Voltage Selection->Brown-out Reset Voltage (Vbor), low trip point selected.
#pragma config LVP = OFF    // Low-Voltage Programming Enable->High-voltage on MCLR/VPP must be used for programming

/*
                         Main application
 */
void main(void) {
    // variables
    uint16_t convertedValue;

    uint16_t LED1_Value = 724; // 11.6V
    uint16_t LED2_Value = 733; // 11.74V
    uint16_t LED3_Value = 741; // 11.86V
    uint16_t LED4_Value = 748; // 11.98V
    uint16_t LED5_Value = 756; // 12.1V
    uint16_t LED6_Value = 763; // 12.22V
    uint16_t LED7_Value = 771; // 12.34V
    uint16_t LED8_Value = 778; // 12.46V
    uint16_t LED9_Value = 784; // 12.56V
    uint16_t LED10_Value = 793; // 12.7V

    // initialize the device

    // SCS FOSC; SPLLEN disabled; IRCF 500KHz_MF;
    OSCCON = 0x38;
    // TUN 0;
    OSCTUNE = 0x00;
    // SBOREN disabled;
    BORCON = 0x00;

    // Watchdog WDTPS 1:65536; SWDTEN OFF;
    WDTCON = 0x16;

    /**
    LATx registers
     */
    LATE = 0x00;
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;

    /**
    TRISx registers
     */
    TRISE = 0x08;
    TRISA = 0xFF;
    TRISB = 0xC0;
    TRISC = 0x0F;

    /**
    ANSELx registers
     */
    ANSELB = 0x00;
    ANSELA = 0x3F;

    /**
    WPUx registers
     */
    WPUE = 0x00;
    WPUB = 0x00;
    OPTION_REGbits.nWPUEN = 1;

    // Initialise FVR

    // CDAFVR off; FVREN enabled; TSRNG Lo_range; ADFVR 4x; TSEN disabled;
    FVRCON = 0x83;

    // Wait for FVR ready

    while (FVRCONbits.FVRRDY != 1) {

    }

    /**
    APFCONx registers
     */
    APFCON = 0x00;




    // set the ADC to the options selected in the User Interface

    // GO_nDONE stop; ADON enabled; CHS AN0;
    ADCON0 = 0x01;

    // ADFM right; ADNREF VSS; ADPREF FVR; ADCS FOSC/2;
    ADCON1 = 0x83;

    // ADRESL 0;
    ADRESL = 0x00;

    // ADRESH 0;
    ADRESH = 0x00;

    // select the A/D channel
    //ADCON0bits.CHS = channel;
    // Turn on the ADC module
    //ADCON0bits.ADON = 1;

    int x = 0;
    while(x < 10){
        // Start the conversion
        ADCON0bits.GO_nDONE = 1;

        // Wait for ADC Conversion
        while (!ADCON0bits.GO_nDONE) {

        }
        x++;
    }

    convertedValue = (ADRESH << 8) + ADRESL;

	// Turn off LEDs
    LED1 = 0;
    LED2 = 0;
    LED3 = 0;
    LED4 = 0;
    LED5 = 0;
    LED6 = 0;
    LED7 = 0;
    LED8 = 0;
    LED9 = 0;
    LED10 = 0;

	// Check each LED value against the ADC voltage.
	// Turn the LEDs on in sequence until the correct voltage is found.
    if (convertedValue < LED2_Value) {
        LED1 = 1;
    }

    if (convertedValue >= LED2_Value) {
        __delay_ms(50);
        LED1 = 0;
        LED2 = 1;
    }
    if (convertedValue >= LED3_Value) {
        __delay_ms(50);
        LED2 = 0;
        LED3 = 1;
    }
    if (convertedValue >= LED4_Value) {
        __delay_ms(50);
        LED3 = 0;
        LED4 = 1;
    }
    if (convertedValue >= LED5_Value) {
        __delay_ms(50);
        LED4 = 0;
        LED5 = 1;
    }
    if (convertedValue >= LED6_Value) {
        __delay_ms(50);
        LED5 = 0;
        LED6 = 1;
    }
    if (convertedValue >= LED7_Value) {
        __delay_ms(50);
        LED6 = 0;
        LED7 = 1;
    }
    if (convertedValue >= LED8_Value) {
        __delay_ms(50);
        LED7 = 0;
        LED8 = 1;
    }
    if (convertedValue >= LED9_Value) {
        __delay_ms(50);
        LED8 = 0;
        LED9 = 1;
    }
    if (convertedValue >= LED10_Value) {
        __delay_ms(50);
        LED9 = 0;
        LED10 = 1;
    }


    while (1) { // Endless loop
    }

}
