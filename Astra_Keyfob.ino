// Sends keyfob data for 1999-2004 Holden Astra
// Transmits at 9600 baud using Manchester Encoding (IEEE 802.3)
// keyCode and incrementingCode need to be determined each time, use provided matlab scripts to find them

#define F_CPU 16000000UL

#define TX_PIN 5
#define BUTTON_PIN 2
#define HALF_PERIOD_ZERO 135
#define HALF_PERIOD_ONE 60
#define TIME_PERIOD 200

#define REPEATING_CODE_TIMES 159
#define REPEATING_CODE_ELEM 8
#define INCREMENTING_CODE_ELEM 34
#define KEY_CODE_ELEM 97

uint8_t repeatingCodeOne[REPEATING_CODE_ELEM] = {0,1,1,1,0,0,0,0};
uint8_t repeatingCodeTwo[REPEATING_CODE_ELEM] = {1,1,1,0,0,0,0,0};
uint8_t keyCode[KEY_CODE_ELEM]= {0,0,1,1,0,1,0,0,1,0,1,0,1,1,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,1,1,1,0,1,1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,1,0,0,1,0,1,0,0,1,1,1,0,0,0,1,0,0,1,1,0,0,1,1,1,1,1,0,1,1,1,1,0,1,0,1,1,0,1,1,0,1,1,0};
uint8_t incrementingCode[INCREMENTING_CODE_ELEM] = {1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,0,1,0,0,1,0,0,0,0,0,0,1,1,1,0};
uint8_t lastButtonState = 0;

void sendData(uint8_t* data, uint8_t numberOfBytes);
void openCar(void);

void setup() 
{
    TCCR1B = (1<<CS11);         // TIMER1 with prescaler of 8
    pinMode(TX_PIN,OUTPUT);
    pinMode(BUTTON_PIN, INPUT);
}

void loop() 
{
    // If button is pressed, send commands to open the car
    uint8_t buttonState = digitalRead(BUTTON_PIN);
    if ((buttonState != lastButtonState) && buttonState) openCar();
    delay(500);
    lastButtonState = buttonState;

}

// Replicates keyfob timing and duplicates signal given arrays outlined at top
void openCar()
{
    // Pulse high for 284 us, begins transmission
    digitalWrite(TX_PIN,1);
    delayMicroseconds(284);
    digitalWrite(TX_PIN,0);

    // Send preamble
    for (uint16_t i = 0; i <REPEATING_CODE_TIMES; i++)
    {
        sendData(repeatingCodeOne,REPEATING_CODE_ELEM);
    }

    // Send unique code
    sendData(keyCode, KEY_CODE_ELEM);
    delayMicroseconds(1600);

    // Send unique code, with preamble
    for (uint16_t i = 0; i <4; i++)
    {
        sendData(repeatingCodeTwo,REPEATING_CODE_ELEM);
    }
    sendData(keyCode, KEY_CODE_ELEM);
    delayMicroseconds(1600);

    // Send incrementing code three times. Duplicated for redundancy. 
    sendData(incrementingCode, INCREMENTING_CODE_ELEM);
    delayMicroseconds(5400);
    sendData(incrementingCode, INCREMENTING_CODE_ELEM);
    delayMicroseconds(5400);
    sendData(incrementingCode, INCREMENTING_CODE_ELEM);
    delayMicroseconds(5400);

    // Send unique code and preamble twice to end transmission
    for (uint16_t i = 0; i <4; i++)
    {
        sendData(repeatingCodeTwo,REPEATING_CODE_ELEM);
    }
    sendData(keyCode, KEY_CODE_ELEM);
    delayMicroseconds(1600);
    for (uint16_t i = 0; i <4; i++)
    {
        sendData(repeatingCodeTwo,REPEATING_CODE_ELEM);
    }
    sendData(keyCode, KEY_CODE_ELEM);
}

void sendData(uint8_t data[], uint8_t numberOfBytes)
{
    // Send manchester encoded 0 or 1 depending on value
    // Uses IEEE 802.3 (falling edge = 0)
    for (uint8_t i = 0; i < numberOfBytes; i++)
    { 
        if (data[i])
        {
            while(TCNT1 < HALF_PERIOD_ONE);
            digitalWrite(TX_PIN, 1);
            
            while(TCNT1 < TIME_PERIOD);
            digitalWrite(TX_PIN, 0);
            
            TCNT1 = 0;
        }
        else 
        {
            while(TCNT1 < HALF_PERIOD_ZERO);
            digitalWrite(TX_PIN, 0);
            
            while(TCNT1 < TIME_PERIOD);
            digitalWrite(TX_PIN, 1);
            
            TCNT1 = 0;
        }
    }
    
    // Wait until time period has passed to turn output off
    // As output stays high forever if a 0 was sent
    while (TCNT1 > TIME_PERIOD/2); 
    digitalWrite(TX_PIN, 0);
}