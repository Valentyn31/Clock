/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Clock
Version : 1
Date    : 09.05.2020
Author  : Valentyn31
Company : Colledge
Comments: 


Chip type               : ATmega8
Program type            : Application
AVR Core Clock frequency: 4,000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/

#include <mega8.h>
#include <i2c.h>
#include <ds1307.h>
#include <delay.h>
#define OFF_HEX 0b00000000 // константа вимкнення в 16 форматі
#define OFF_DEC 10 // константа вимкнення в десятковому форматі

unsigned char numbers[] = {0b11111100, 0b01100000, 0b11011010, 
                            0b11110010, 0b01100110, 0b10110110, 
                            0b10111110, 0b11100000, 0b111111110, 
                            0b11110110, OFF_HEX}; // масив цифр у 16 форматі
unsigned char hour, min, sec;
unsigned char set;

unsigned char decToHex (unsigned char num) { //функція для перетворення десяткового формату в шістнадцятковий 
    switch (num) {
        case 0:
            num =  numbers[0];
            return num;
        case 1: 
            num = numbers[1];
            return num;
        case 2: 
            num = numbers[2];
            return num;
        case 3: 
            num = numbers[3];
            return num;
        case 4: 
            num = numbers[4];
            return num;
        case 5: 
            num = numbers[5];
            return num;
        case 6: 
            num = numbers[6];
            return num;
        case 7: 
            num = numbers[7];
            return num;
        case 8: 
            num = numbers[8];
            return num;
        case 9: 
            num = numbers[9];
            return num;
        case OFF_DEC:
            num = numbers[10];
            return num;      
    }
    return num;  
};

void timeOutPut(unsigned char hour, unsigned char min) {
    PORTD.3 = 1;
    PORTB = decToHex(hour / 10) ^ 0xFF;
    delay_ms(1);
    PORTD.3 = 0;
    PORTD.4 = 1;
    PORTB = (decToHex(hour % 10) + 1) ^ 0xFF;
    delay_ms(1);
    PORTD.4 = 0;
    PORTD.5 = 1;
    PORTB = decToHex(min / 10) ^ 0xFF;
    delay_ms(1);
    PORTD.5 = 0;
    PORTD.6 = 1;
    PORTB = (decToHex(min % 10) + 1) ^ 0xFF;
    delay_ms(1);
    PORTD.6 = 0;  
};

void main(void) {   // головна функція

DDRB=(1<<DDB7) | (1<<DDB6) | (1<<DDB5) | (1<<DDB4) | (1<<DDB3) | (1<<DDB2) | (1<<DDB1) | (1<<DDB0);
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);
DDRC=0x00; 
PORTC=0xFF;
DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);
TCCR0=(0<<CS02) | (0<<CS01) | (0<<CS00);
TCNT0=0x00;
TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (0<<CS11) | (0<<CS10);
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;
ASSR=0<<AS2;
TCCR2=(0<<PWM2) | (0<<COM21) | (0<<COM20) | (0<<CTC2) | (0<<CS22) | (0<<CS21) | (0<<CS20);
TCNT2=0x00;
OCR2=0x00;
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<TOIE0);
MCUCR=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
UCSRB=(0<<RXCIE) | (0<<TXCIE) | (0<<UDRIE) | (0<<RXEN) | (0<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);
ACSR=(1<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIC) | (0<<ACIS1) | (0<<ACIS0);
SFIOR=(0<<ACME);
ADCSRA=(0<<ADEN) | (0<<ADSC) | (0<<ADFR) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (0<<ADPS1) | (0<<ADPS0);
SPCR=(0<<SPIE) | (0<<SPE) | (0<<DORD) | (0<<MSTR) | (0<<CPOL) | (0<<CPHA) | (0<<SPR1) | (0<<SPR0);
TWCR=(0<<TWEA) | (5<<TWSTA) | (0<<TWSTO) | (0<<TWEN) | (0<<TWIE);
PORTD.7 = 1;


i2c_init();  //ініціалізація шини і2с
rtc_init(3,1,0); // ініціалізація годинника
rtc_write(0, 0);

    while (1) {
        set = 0;
        if (PINC.0 == 0) {
        while (PINC.0 != 1) {
            timeOutPut(hour, min);
        }
            set = 1;
            PORTD.2 = 1;
            delay_ms(10);
            PORTD.2 = 0;
            while (set == 1) {
                if (PINC.1 == 0) {
                    while (PINC.1 != 1) {
                        timeOutPut(hour, min);
                    }
                    hour++;
                    if (hour > 23)
                        hour = 0;      
                }
                if (PINC.2 == 0) {
                    while (PINC.2 != 1) {
                        timeOutPut(hour, min);    
                    }
                    hour--;
                    if (hour == 255)
                        hour = 23;
                }
                timeOutPut(hour, min);  
                if (PINC.0 == 0) {
                    while (PINC.0 != 1) {
                        timeOutPut(hour, min);
                    }
                    set = 2;                    
                }        
            } 
            while (set == 2) {
                if (PINC.1 == 0) {
                while (PINC.1 != 1) {
                    timeOutPut(hour, min);
                }
                    min++;
                    if (min > 59)
                        min = 0;
                }
                if (PINC.2 == 0) {
                while (PINC.2 != 1) {
                    timeOutPut(hour, min);
                }
                    min--;
                    if (min == 255)
                        min = 59;
                }
                timeOutPut(hour, min);              
                if (PINC.0 == 0) {
                    while (PINC.0 != 1) {
                        timeOutPut(hour, min);
                    }
                    set = 3; 
                }           
            }
            if (set == 3) {
                rtc_set_time(hour, min, sec); 
            }       
        }
        rtc_get_time(&hour, &min, &sec);
        timeOutPut(hour, min,);   
    }          
}


