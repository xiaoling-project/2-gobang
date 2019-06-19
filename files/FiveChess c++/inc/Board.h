#ifndef __BOARD_H__
#define __BOARD_H__

#include "stdafx.h"

class CBoard:public CWnd
{
private:
    CImageList m_iml; // 棋子图像
    int m_color; // 玩家颜色
    BOOL m_bWait; // 等待标志
	BOOL m_bOldWait;	//原来的等待状态
 
public:
	CBoard();
    virtual ~CBoard();
	void RestoreWait();
    void Clear( BOOL bWait );
    void SetColor(int color);
    int  GetColor() const;
    void SetWait( BOOL bWait );
    void SetData( int x, int y, int color );
    void DrawGame();
	void Draw(int x, int y, int color);
	void Receive();
	void Over(int x, int y);

protected:
    afx_msg void OnPaint();
    afx_msg void OnLButtonUp( UINT nFlags, CPoint point );
    DECLARE_MESSAGE_MAP()
};

#endif