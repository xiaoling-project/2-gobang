// SetupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FiveChess.h"
#include "SetupDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetupDlg dialog


CSetupDlg::CSetupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetupDlg)
	m_net_port = 0;
	//}}AFX_DATA_INIT
}


void CSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetupDlg)
	DDX_Control(pDX, IDC_IP_ADDRESS_EDIT, m_ip_addr);
	DDX_Text(pDX, IDC_NET_PORT_EDIT, m_net_port);
	DDV_MinMaxUInt(pDX, m_net_port, 1, 65000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetupDlg, CDialog)
	//{{AFX_MSG_MAP(CSetupDlg)
	ON_BN_CLICKED(IDC_CLIENT_OPTION, OnClientOption)
	ON_BN_CLICKED(IDC_HOST_OPTION, OnHostOption)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetupDlg message handlers

void CSetupDlg::OnOK() 
{
	CString strIP, strPort;

	UpdateData(TRUE);
	m_ip_addr.GetWindowText(strIP);
	m_strHostIP = strIP;
	strPort.Format("%d", m_net_port);
	if(m_isHost)
	{
		WritePrivateProfileString("HOST", "PORT", strPort, ".\\config.ini");
	}
	else
	{
		WritePrivateProfileString("CLIENT", "IP", strIP, ".\\config.ini");
		WritePrivateProfileString("CLIENT", "PORT", strPort, ".\\config.ini");
	}
	
	CDialog::OnOK();
}

void CSetupDlg::OnCancel() 
{
	CDialog::OnCancel();
}

void CSetupDlg::OnClientOption() 
{
	char str[128] = {0};
	m_ip_addr.EnableWindow(TRUE);
	GetPrivateProfileString("CLIENT", "IP", "", str, 127, ".\\config.ini");
	m_ip_addr.SetWindowText(str);
	memset(str,0, 128);
	GetPrivateProfileString("CLIENT", "PORT", "5000", str, 127, ".\\config.ini");
	m_net_port = atoi(str);
	m_isHost = FALSE;
	UpdateData(FALSE);
}

void CSetupDlg::OnHostOption() 
{
	char str[128] = {0};
	m_ip_addr.EnableWindow(FALSE);
	GetPrivateProfileString("HOST", "IP", "", str, 127, ".\\config.ini");
	m_ip_addr.SetWindowText(str);
	memset(str,0, 128);
	GetPrivateProfileString("HOST", "PORT", "5000", str, 127, ".\\config.ini");
	m_net_port = atoi(str);
	m_isHost = TRUE;
	UpdateData(FALSE);	
}

BOOL CSetupDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	((CButton*)GetDlgItem(IDC_HOST_OPTION))->SetCheck(1);
	OnHostOption();
	return TRUE;
}
