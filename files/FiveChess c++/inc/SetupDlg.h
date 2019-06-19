#if !defined(AFX_SETUPDLG_H__978DA95F_86F1_4C6B_BE9B_5EFD69DADACF__INCLUDED_)
#define AFX_SETUPDLG_H__978DA95F_86F1_4C6B_BE9B_5EFD69DADACF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetupDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetupDlg dialog
#include "stdafx.h"
#include "Resource.h"

class CSetupDlg : public CDialog
{
// Construction
public:
	CSetupDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetupDlg)
	enum { IDD = IDD_SETUP_DLG };
	CIPAddressCtrl	m_ip_addr;
	UINT	m_net_port;
	//}}AFX_DATA

public:
	BOOL m_isHost;		//主机类型，TRUE:主机 FALSE:客户机
	CString m_strHostIP;//IP 地址

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetupDlg)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClientOption();
	afx_msg void OnHostOption();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETUPDLG_H__978DA95F_86F1_4C6B_BE9B_5EFD69DADACF__INCLUDED_)
