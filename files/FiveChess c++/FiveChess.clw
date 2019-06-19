; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSetupDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "FiveChess.h"

ClassCount=4
Class1=CFiveChessApp
Class2=CFiveChessDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_SETUP_DLG
Resource2=IDR_MAINFRAME
Resource3=IDD_FIVECHESS_DIALOG
Resource4=IDD_ABOUTBOX
Class4=CSetupDlg
Resource5=IDR_MAIN_MENU

[CLS:CFiveChessApp]
Type=0
HeaderFile=FiveChess.h
ImplementationFile=FiveChess.cpp
Filter=N

[CLS:CFiveChessDlg]
Type=0
HeaderFile=inc\fivechessdlg.h
ImplementationFile=src\fivechessdlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CFiveChessDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=FiveChessDlg.h
ImplementationFile=FiveChessDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_FIVECHESS_DIALOG]
Type=1
Class=CFiveChessDlg
ControlCount=0

[MNU:IDR_MAIN_MENU]
Type=1
Class=?
Command1=ID_NEW_GAME_MENU
Command2=ID_DRAW_GAME_MENU
Command3=ID_EXIT_GAME_MENU
CommandCount=3

[DLG:IDD_SETUP_DLG]
Type=1
Class=CSetupDlg
ControlCount=9
Control1=IDC_HOST_OPTION,button,1342177289
Control2=IDC_CLIENT_OPTION,button,1342177289
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_STATIC,button,1342177287
Control6=IDC_IP_ADDRESS_EDIT,SysIPAddress32,1342242816
Control7=IDC_STATIC,static,1342308865
Control8=IDC_STATIC,static,1342308865
Control9=IDC_NET_PORT_EDIT,edit,1350631552

[CLS:CSetupDlg]
Type=0
HeaderFile=inc\setupdlg.h
ImplementationFile=src\setupdlg.cpp
BaseClass=CDialog
LastObject=IDC_CLIENT_OPTION

