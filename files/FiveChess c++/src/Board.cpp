#include "board.h"
#include "Resource.h"
#include "ConnectData.h"
#include "Rule.h"
#include "FiveChessDlg.h"

#define MAX_LEN 256				/*定义最大长度*/
//////////////////////////////////////////////////////////////////////////
// 构造函数，初始化棋盘数据以及图像数据
//////////////////////////////////////////////////////////////////////////
CBoard::CBoard()
{
    // 初始化图像列表
    m_iml.Create( 24, 24, ILC_COLOR24 | ILC_MASK, 0, 2 );
    // 载入黑、白棋子掩码位图
    CBitmap bmpBlack, bmpWhite;
    bmpBlack.LoadBitmap( IDB_BMP_BLACK );
    m_iml.Add( &bmpBlack, 0xff00ff );
    bmpWhite.LoadBitmap( IDB_BMP_WHITE );
    m_iml.Add( &bmpWhite, 0xff00ff );
}
//////////////////////////////////////////////////////////////////////////
// 析构函数
//////////////////////////////////////////////////////////////////////////
CBoard::~CBoard()
{

}

// 消息映射表
BEGIN_MESSAGE_MAP( CBoard, CWnd )
	//{{AFX_MSG_MAP(CBoard)
    ON_WM_PAINT()
    ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////
// 处理WM_PAINT消息
//////////////////////////////////////////////////////////////////////////
void CBoard::OnPaint()
{
    CPaintDC dc( this );
    CDC MemDC;
    MemDC.CreateCompatibleDC( &dc );
    // 装载棋盘
    CBitmap bmp;
    CPen pen;
    bmp.LoadBitmap( IDB_BMP_QP );
    pen.CreatePen( PS_SOLID, 1, 0xff );
    MemDC.SelectObject( &bmp );
    MemDC.SelectObject( &pen );
    MemDC.SetROP2( R2_NOTXORPEN );
    // 根据棋盘数据绘制棋子
    int x, y;
    POINT pt;
    for ( y = 0; y < 15; y++ )
    {
        for ( x = 0; x < 15; x++ )
        {
            if ( -1 != m_data[x][y] )
            {
                pt.x = 12 + 25 * x;
                pt.y = 84 + 25 * y;
                m_iml.Draw( &MemDC, m_data[x][y], pt, ILD_TRANSPARENT );
            }
        }
    }
	// 完成绘制
    dc.BitBlt( 0, 0, 395, 472, &MemDC,0, 0, SRCCOPY );
}
//////////////////////////////////////////////////////////////////////////
// 处理左键弹起消息，为玩家落子之用
//////////////////////////////////////////////////////////////////////////
void CBoard::OnLButtonUp( UINT nFlags, CPoint point )
{
	MSGSTRUCT msg;
	CRule  rule;
	CFiveChessDlg * pDlg = (CFiveChessDlg*)AfxGetMainWnd();
	BYTE buf[MAX_LEN] = {0};
	
    if ( m_bWait)
    {
        MessageBeep( MB_OK );
        return;
    }
	if(pDlg->m_bIsConnect)
	{
		int x, y;
		x = ( point.x - 12 ) / 25;
		y = ( point.y - 84 ) / 25;
		// 如果在(0, 0)～(14, 14)范围内，且该坐标没有落子，
		// 则落子于此，否则发声警告并退出过程
		if ( x < 0 || x > 14 || y < 0 || y > 14 || m_data[x][y] != -1 )
		{
			MessageBeep( MB_OK );
			return;
		}
		else
		{
			// 如果位置合法，则落子
			SetData( x, y, m_color );
			msg.color = m_color;
			msg.x = x;
			msg.y = y;
		}
		// 开始等待
		m_bWait = TRUE;
		msg.msgType = MSG_PUTSTEP;
		pDlg->Send(&msg);
		
		if(rule.Win(m_color, msg.x, msg.y) == _WIN)
		{// 胜利
			pDlg->MessageBox( _T("恭喜，您获得了胜利！"), _T("胜利"), MB_ICONINFORMATION );
			pDlg->SetMenuState(TRUE);
		}
		else if(rule.Win(m_color, msg.x, msg.y) == _LOST)
		{//	出现禁手
			pDlg->MessageBox( _T("执黑禁手, 您输了！"), _T("失败"), MB_ICONINFORMATION );
			pDlg->SetMenuState(TRUE);
		}
	}

}
//////////////////////////////////////////////////////////////////////////
// 清空棋盘
//////////////////////////////////////////////////////////////////////////
void CBoard::Clear( BOOL bWait )
{
    int x, y;
    for ( y = 0; y < 15; y++ )
    {
        for ( x = 0; x < 15; x++ )
        {
            m_data[x][y] = -1;
        }
    }
    // 设置等待标志
    m_bWait = bWait;
    Invalidate();
}
//////////////////////////////////////////////////////////////////////////
// 设置玩家颜色
//////////////////////////////////////////////////////////////////////////
void CBoard::SetColor(int color)
{
	m_color = color;
}
//////////////////////////////////////////////////////////////////////////
// 获取玩家颜色
//////////////////////////////////////////////////////////////////////////
int CBoard::GetColor() const
{
	return m_color;
}
//////////////////////////////////////////////////////////////////////////
// 设置等待标志
//////////////////////////////////////////////////////////////////////////
void CBoard::SetWait( BOOL bWait )
{
	m_bOldWait = m_bWait;
	m_bWait = bWait;
}
//////////////////////////////////////////////////////////////////////////
// 设置棋盘数据，并绘制棋子
//////////////////////////////////////////////////////////////////////////
void CBoard::SetData( int x, int y, int color )
{
    m_data[x][y] = color;
    Draw( x, y, color );
}
//////////////////////////////////////////////////////////////////////////
// 在指定棋盘坐标处绘制指定颜色的棋子
//////////////////////////////////////////////////////////////////////////
void CBoard::Draw(int x, int y, int color)
{
    POINT pt;
    pt.x = 12 + 25 * x;
    pt.y = 84 + 25 * y;
    CDC *pDC = GetDC();
    CPen pen;
    pen.CreatePen( PS_SOLID, 1, 0xff );
    pDC->SelectObject( &pen );
    pDC->SetROP2( R2_NOTXORPEN );
    m_iml.Draw( pDC, color, pt, ILD_TRANSPARENT );
    ReleaseDC( pDC );
}
//////////////////////////////////////////////////////////////////////////
// 接收来自对方的数据
//////////////////////////////////////////////////////////////////////////
void CBoard::Receive()
{
	CFiveChessDlg * pDlg = (CFiveChessDlg*)AfxGetMainWnd();
	MSGSTRUCT msg;
	if(pDlg->m_sock.Receive((LPVOID)&msg, sizeof(MSGSTRUCT)) == SOCKET_ERROR)
	{
		AfxGetMainWnd()->MessageBox( _T("接收数据时发生错误，请检查您的网络连接。"), _T("错误"), MB_ICONSTOP );
		return;
	}
	switch(msg.msgType)
	{
	case MSG_PUTSTEP:
		SetData( msg.x, msg.y, msg.color );
		Over(msg.x, msg.y);
		break;
	case MSG_DRAW:
		if ( IDYES == GetParent()->MessageBox( _T("对方请求和棋，接受这个请求吗？"),
			_T("和棋"), MB_ICONQUESTION | MB_YESNO ) )
		{
			// 发送允许和棋消息
			MSGSTRUCT msg;
			msg.msgType = MSG_AGREE_DRAW;
			pDlg->m_sock.Send( (LPCVOID)&msg, sizeof( MSGSTRUCT ) );
			SetWait( TRUE );
			// 使“重玩”菜单生效
			pDlg->SetMenuState(TRUE);
		}
		else
		{
			// 发送拒绝和棋消息
			MSGSTRUCT msg;
			msg.msgType = MSG_REFUSE_DRAW;
			pDlg->m_sock.Send( (LPCVOID)&msg, sizeof( MSGSTRUCT ) );
		}
		break;
	case MSG_AGREE_DRAW:
		pDlg->MessageBox( _T("看来真是棋逢对手，对方接受了您的和棋请求。"), _T("和棋"), MB_ICONINFORMATION );
		// 和棋后，使“重玩”菜单生效
		pDlg->SetMenuState(TRUE);
		break;
	case MSG_REFUSE_DRAW:
		pDlg->MessageBox( _T("看来对方很有信心取得胜利，所以拒绝了您的和棋请求。"),
			_T("和棋"), MB_ICONINFORMATION );
		RestoreWait();
		pDlg->SetMenuState(FALSE);
		break;
	case MSG_EXTERN:
		break;
	default:
		break;
	}

}
//////////////////////////////////////////////////////////////////////////
// 和棋操作
//////////////////////////////////////////////////////////////////////////
void CBoard::DrawGame()
{
	CFiveChessDlg * pDlg = (CFiveChessDlg*)AfxGetMainWnd();
    // 设置等待标志
    SetWait( TRUE );	
    MSGSTRUCT msg;
    msg.msgType = MSG_DRAW;
    pDlg->m_sock.Send( (LPCVOID)&msg, sizeof( MSGSTRUCT ) );
}

//////////////////////////////////////////////////////////////////////////
// 处理对方落子后的工作
//////////////////////////////////////////////////////////////////////////
void CBoard::Over(int x, int y)
{
	CRule rule;
	CFiveChessDlg *pDlg = (CFiveChessDlg *)GetParent();
	// 判断对方是否胜利
    if ( rule.Win( 1 - m_color, x, y ) == _WIN)
    {
       pDlg->MessageBox( _T("您输了，不过不要灰心，失败乃成功之母哦！"), _T("失败"), MB_ICONINFORMATION );
       // 如果是网络对战，则生效“重玩”
       if ( pDlg->m_bIsConnect )
       {
		pDlg->SetMenuState(TRUE);
       }
       return;
    }
	//判断对方是否出现禁手
	else if(rule.Win(1 - m_color, x, y) == _LOST)
	{
		pDlg->MessageBox( _T("恭喜您, 对方出现禁手输了！"), _T("胜利"), MB_ICONINFORMATION );
		// 如果是网络对战，则生效“重玩”
		if ( pDlg->m_bIsConnect )
		{
			pDlg->SetMenuState(TRUE);
		}
		return;		
	}
	m_bWait = FALSE;	
}
//////////////////////////////////////////////////////////////////////////
// 重新设置先前的等待标志
//////////////////////////////////////////////////////////////////////////
void CBoard::RestoreWait()
{
    SetWait( m_bOldWait );
}
