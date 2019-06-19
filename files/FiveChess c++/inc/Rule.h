#ifndef __RULE_H__
#define __RULE_H__

#define _WIN 0x00
#define _LOST 0x01
#define _OTHER 0x02

class CRule
{
public:
	CRule();								//构造函数
	~CRule();								//析构函数

	int Win(int color, int x, int y);		//胜负判断接口函数
	BOOL Ban(int x, int y, int color);		//禁手判断接口函数
private:
	BOOL forbid2(int x, int y);				//非连子禁手判断
	BOOL forbid1(int x, int y);				//连子禁手判断
};

#endif