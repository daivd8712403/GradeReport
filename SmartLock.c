// PROGRAM	: 4-5.c									2013.1024
// FUNCTION	: 4X4 MATRIX KEYPAD DEMO PROGRAM		By Steven
#include <HT66F70A.h>
#include "MyType.h"	
const u8 SEG_TAB[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67, 0x77, 0x7C, 0x58, 0x5E, 0x79, 0x71};

const u8 TAB_Pitch[] = {		   					//音調參數
	_1M/(523*2*10), _1M/(587*2*10),
	_1M/(659*2*10), _1M/(698*2*10),
	_1M/(785*2*10), _1M/(880*2*10),
	_1M/(988*2*10), _1M/(523*2*2*10)};

const u16 TAB_Duration[] = {523 / 2 , 587 / 2, 659 / 2, 698 / 2, 785 / 2, 880 / 2 , 988 / 2 , (523 * 2) / 2}; 

void Pause(u8);
void Delay100us(u16);
u8 ScanKey(void);

void main() {
	u8 Key,a,b,c,d,i;
	u16 j;
	_wdtc=0b10101111;								//關閉看們狗計時器
	SEG_PortC=0x00;									//規劃SEG_Port為輸出模式
	SPK_PortC=0;
	dC0=0;
	dC1=0;
	dC2=0;
	dC3=0;
	d0=0;
	d1=0;
	d2=0;
	d3=0;
	while(1) {	
		a = b = c = d = 0;
		SEG_Port = 0;//關閉七段顯示器			
		do {
			a = Key = ScanKey();
		}while(Key==16);	   		//等待按壓按鍵
		for(j = 0; j <= TAB_Duration[0] * 1; j++) {	
			SPK_Port =! SPK_Port;					
			Pause(TAB_Pitch[0]);				
		}
		SEG_Port=SEG_TAB[Key];					//根據鍵值查表並顯示
		d0 = 1;
		d1 = 0;
		d2 = 0;
		d3 = 0;				      	
		Delay100us(10000);	   						//延遲一秒
		SEG_Port = 0;
		do{
			b=Key=ScanKey();
		}while(Key == 16);
		for(j = 0;j <= TAB_Duration[0] * 1; j++){
			SPK_Port =! SPK_Port;					
			Pause(TAB_Pitch[0]);				
		}
		for(i = 0; i < 40; i++) {
			SEG_Port = SEG_TAB[b];
			d0 = 1;
			d1 = 0;
			d2 = 0;
			d3 = 0;
			Delay100us(100);
			SEG_Port = SEG_TAB[a];
			d0 = 0;
			d1 = 1;
			d2 = 0;
			d3 = 0;
			Delay100us(100);
		}
		SEG_Port = 0;
		do{
			c = Key = ScanKey();
		}while(Key == 16);
		for(j = 0; j <= TAB_Duration[0]*1; j++){
			SPK_Port =! SPK_Port;					
			Pause(TAB_Pitch[0]);				
		}
		for(i = 0; i < 40; i++) {
			SEG_Port = SEG_TAB[c];
			d0 = 1;
			d1 = 0;
			d2 = 0;
			d3 = 0;
			Delay100us(50);
			SEG_Port = SEG_TAB[b];
			d0 = 0;
			d1 = 1;
			d2 = 0;
			d3 = 0;
			Delay100us(50);
			SEG_Port = SEG_TAB[a];
			d0 = 0;
			d1 = 0;
			d2 = 1;
			d3 = 0;
			Delay100us(50);
		}
		SEG_Port = 0;
		do{
			d = Key = ScanKey();
		}while(Key == 16);
		for(j = 0; j <= TAB_Duration[0]*1; j++){
			SPK_Port =! SPK_Port;					
			Pause(TAB_Pitch[0]);				
		}
		for(i = 0; i < 40; i++){
			SEG_Port = SEG_TAB[d];
			d0 = 1;
			d1 = 0;
			d2 = 0;
			d3 = 0;
			Delay100us(50);
			SEG_Port = SEG_TAB[c];
			d0 = 0;
			d1 = 1;
			d2 = 0;
			d3 = 0;
			Delay100us(50);
			SEG_Port = SEG_TAB[b];
			d0 = 0;
			d1 = 0;
			d2 = 1;
			d3 = 0;
			Delay100us(50);
			SEG_Port = SEG_TAB[a];
			d0 = 0;
			d1 = 0;
			d2 = 0;
			d3 = 1;
			Delay100us(50);
		}
		SEG_Port=0;
		if(a == 0 && b == 2 && c == 1 && d == 8) {
			for(j=0;j<=TAB_Duration[0]*3;j++)
			{	SPK_Port=!SPK_Port;					
				Pause(TAB_Pitch[0]);				
			}
			for(j=0;j<=TAB_Duration[2]*3;j++)
			{	SPK_Port=!SPK_Port;					
				Pause(TAB_Pitch[2]);				
			}
			for(j=0;j<=TAB_Duration[4]*3;j++)
			{	SPK_Port=!SPK_Port;					
				Pause(TAB_Pitch[4]);				
			}
		}
		else
		{
			for(j=0;j<=TAB_Duration[0]*3;j++)
			{	SPK_Port=!SPK_Port;					
				Pause(TAB_Pitch[0]);
			}
			Delay100us(1000);
			for(j=0;j<=TAB_Duration[0]*3;j++)
			{	SPK_Port=!SPK_Port;					
				Pause(TAB_Pitch[0]);				
			}
		}
	}	
}
u8 ScanKey()
{	u8 i,key=0;
	u16 j;
	KeyPortC=0xF0; KeyPortPU=0xF0;			   		//I/O Port相關規劃
	KeyPort=0b11111110;					         	//設定KeyPort初值
	for(i=0;i<=3;i++)
	{	if((KeyPort & 1<<7)==0) break;		      	//檢查第0行
		key++;
		if((KeyPort & 1<<6)==0) break;			   	//檢查第1行
		key++;
		if((KeyPort & 1<<5)==0) break;			   	//檢查第2行
		key++;
		if((KeyPort & 1<<4)==0) break;			   	//檢查第3行
		key++;
		GCC_RL(KeyPort); KeyPort|=0b00000001;	   	//更新掃描碼
	}
	return key;	
}
void Delay100us(u16 del)							//延遲del*200指令週期
{	u16 i,j;										//@fSYS=8MH,延遲del*100us
	for(i=0;i<del;i++)
		for(j=0;j<=25;j++) GCC_NOP();
}
void Pause(u8 i)
{	u8 j;
    for(j=0;j<i;j++) GCC_NOP();						//延遲 i*20個指令週期
}
