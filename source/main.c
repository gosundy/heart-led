/*
date:2017-12-09
author:wto
email:1154505362@qq.com
*/

#include <reg51.h>
/*
<-------------total--------------->
<------a---------->
---------P1=1-----|
                  |<--(total-a)--->
				          |-----P1=0-------
*/
int count=0;//��ʱ��
int total=100;//�ܵ���ʱ
const int dus=1000;
int a=0;//p1=1����ʱ ��total-a��P1=0����ʱ
char step=1;//��������
void main(){
	EA=1;
	ET0=1;
	ET1=1;
	TMOD=0X11;//16λ��ʱģʽ
	TR0=1;
	//��ʼ��������ʱ��
	TL0=(65535-1)%256;
	TH0=(65535-1)/256;
	TL1=(65535-1)%256;
	TH1=(65535-1)/256;
	//��ʼ���˿�
	P1=1;
	while(1);
}
void timer0() interrupt 1{
	TL0=(65535-dus)%256;
	TH0=(65535-dus)/256;
	count=count+1;
	//P1=1;
	//delay a*dus
	if (count>=a){
		a=a+step;
		if(a>=total||a<=0){
			step=0-step;
		}
		count=0;
		P1=~P1;
		TR0=0;
		TR1=1;
	}
}
void timer1() interrupt 3{
	TL1=(65535-dus)%256;
	TH1=(65535-dus)/256;
	count=count+1;
	//P1=0;
	//delay (total-a)*dus
	if (count>=(total-a)){
		a=a+step;
		if(a>=total||a<=0){
			step=0-step;
		}
		count=0;
		P1=~P1;
		TR1=0;
		TR0=1;
	}
}