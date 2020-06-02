/*
#include "mbed.h"
#define CENTER_BASE 1500
PwmOut servo(D11);
void servo_control(int speed){
    if (speed > 200)       speed = 200;
    else if (speed < -200) speed = -200;
    servo = (CENTER_BASE + speed)/20000.0f;
}
int main() {
    servo.period(.02);
    while(1) {
        servo_control(0);
        wait(2);
        servo_control(0);
        wait(2);
    }
}
*/

#include "mbed.h"
#define CENTER_BASE 1500
Serial pc(USBTX, USBRX);
DigitalIn encoder(D10);
PwmOut servo(D11);
Timer t;
Ticker encoder_ticker;

volatile int steps;
volatile int last;

void servo_control(int speed){
    if (speed > 200)       speed = 200;
    else if (speed < -200) speed = -200;
    servo=(CENTER_BASE + speed)/20000.0f;
}

void encoder_control(){
    int value = encoder;
    if(!last && value) steps++;
    last = value;
}

int main() {
    float time;
    pc.baud(9600);
    encoder_ticker.attach(&encoder_control, .01);
    servo.period(.02);

    while(1) {
    
    servo_control(-25.67573795514996);
    steps = 0;
    t.reset();
    t.start();
    wait(5);
    time = t.read();
    pc.printf("%1.3f\r\n", (float)steps*6.5*3.14/32/time);
    
    servo_control(44.29960867664822);
    steps = 0;
    t.reset();
    t.start();
    wait(5);
    time = t.read();
    pc.printf("%1.3f\r\n", (float)steps*6.5*3.14/32/time);
    }

}

