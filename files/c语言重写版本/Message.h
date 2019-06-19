#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<string.h>


#define oops(x)  {perror(x);exit(1);}//程序出错时候使用

#ifndef MESSAGE_H_
#define MESSAGE_H_


#define HOSTLEN 256  


#define MSG_PUTSTEP 0x01
#define MSG_DRAW 0x02
#define MSG_AGREE_DRAW 0x03
#define MSG_DENY_DRAW 0x04
#define MSG_EXTERN 0x05

typedef struct Message
{
	int len;
	// 消息ID
	unsigned int msgType;
	// 落子信息						
	int x;
	int y;				
//书上的消息体结构，因为只是演示棋子落子，所以只用了msgType,x,y
//有些功能没有实现你们可以先看他的demo视频内容

    int color;
	// 其他消息内容
	char byMsg[128];
	
}MSGSTRUCT;

#endif



