#ifndef __CONNECT_DATA_H__
#define __CONNECT_DATA_H__

// 落子消息
#define MSG_PUTSTEP     0x01
// 和棋请求消息
#define MSG_DRAW        0x02
// 同意和棋消息
#define MSG_AGREE_DRAW	0x03
// 拒绝和棋消息
#define MSG_REFUSE_DRAW	0x04
// 其他消息
#define MSG_EXTERN		0x05

typedef struct _tagMsgStruct {
    USHORT len;
	// 消息ID
    BYTE msgType;
    // 落子信息
    int x;
    int y;
    int color;
    // 其他消息内容
    BYTE byMsg[128];
} MSGSTRUCT;

#endif