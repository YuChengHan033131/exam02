#include "mbed.h"
#include "accelerometer.h"
InterruptIn sw2(SW2);
InterruptIn sw3(SW3);
Thread mainThread,thread1,thread2;
EventQueue mainQueue,queue1,queue2;
Timer clock_10s;
DigitalOut led(LED_BLUE);
Serial pc( USBTX, USBRX );

void ledBlink(){
    led=!led;
}
void aceleLoger(){
    //count displacement in every 0.1s
    float x,y,z,dis;
    accelerometer(x,y,z);
    if(z*9.8*0.1*0.1/2*100>5){
        dis=1;
    }else{
        dis=0;
    }
    pc.printf("%f\r\n%f\r\n%f\r\n%f\r\n%f\r\n",x,y,z,clock_10s.read(),dis);
}
void sw2Fall(){
    clock_10s.reset();
    int ID_led=queue2.call_every(1000,ledBlink);
    int ID_acele=queue1.call_every(100,aceleLoger);
    while(clock_10s.read()<10){}
    pc.printf("END\r\n");
    queue2.cancel(ID_led);
    queue1.cancel(ID_acele);
    led=1;
}
int main(){
    clock_10s.start();
    led=1;
    mainThread.start(callback(&mainQueue,&EventQueue::dispatch_forever));
    thread1.start(callback(&queue1,&EventQueue::dispatch_forever));
    thread2.start(callback(&queue2,&EventQueue::dispatch_forever));
    
    
    
    sw2.fall(mainQueue.event(&sw2Fall));
}