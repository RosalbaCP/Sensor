
// MFCSensorDlg.cpp: archivo de implementación
//

#include "pch.h"
#include "framework.h"
#include "MFCSensor.h"
#include "MFCSensorDlg.h"
#include "afxdialogex.h"
#include "SerialClass.h"
#include <iostream>
#include <fstream>
#include <Windows.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

Serial* Port = new Serial((char*)"COM5");
char recibido[50]; // Guarda los datos de entrada del puerto


// Cuadro de diálogo CAboutDlg utilizado para el comando Acerca de

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Datos del cuadro de diálogo
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV

// Implementación
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cuadro de diálogo de CMFCSensorDlg



CMFCSensorDlg::CMFCSensorDlg(CWnd* pParent /*= nullptr*/)
	: CDialogEx(IDD_MFCSENSOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCSensorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCSensorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_RX, &CMFCSensorDlg::OnBnClickedBtnRx)
	ON_BN_CLICKED(IDC_BTN_DESACTIVAR, &CMFCSensorDlg::OnBnClickedBtnDesactivar)
	ON_EN_CHANGE(IDC_EDT_RX, &CMFCSensorDlg::OnEnChangeEdtRx)
	ON_WM_TIMER()
END_MESSAGE_MAP()




// Controladores de mensajes de CMFCSensorDlg

BOOL CMFCSensorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Agregar el elemento de menú "Acerca de..." al menú del sistema.

	// IDM_ABOUTBOX debe estar en el intervalo de comandos del sistema.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Establecer el icono para este cuadro de diálogo.  El marco de trabajo realiza esta operación
	//  automáticamente cuando la ventana principal de la aplicación no es un cuadro de diálogo
	SetIcon(m_hIcon, TRUE);			// Establecer icono grande
	SetIcon(m_hIcon, FALSE);		// Establecer icono pequeño

	// TODO: agregar aquí inicialización adicional
	CTime TemperaturaHumedad = CTime::GetCurrentTime(); //Obtiene la temperatura y humedad actual
	Port->ReadData(recibido, sizeof(recibido) - 1);
	//CString TemperaturaHumedadTxt = TemperaturaHumedad.Format("");
	SetDlgItemText(IDC_EDT_RX, (LPTSTR)recibido);

	return TRUE;  // Devuelve TRUE  a menos que establezca el foco en un control
}

void CMFCSensorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// Si agrega un botón Minimizar al cuadro de diálogo, necesitará el siguiente código
//  para dibujar el icono.  Para aplicaciones MFC que utilicen el modelo de documentos y vistas,
//  esta operación la realiza automáticamente el marco de trabajo.

void CMFCSensorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Contexto de dispositivo para dibujo

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrar icono en el rectángulo de cliente
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Dibujar el icono
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// El sistema llama a esta función para obtener el cursor que se muestra mientras el usuario arrastra
//  la ventana minimizada.
HCURSOR CMFCSensorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCSensorDlg::OnBnClickedBtnRx()
{
	SetTimer(1, 180, NULL);
}

void CMFCSensorDlg::OnBnClickedBtnDesactivar()
{
	KillTimer(1);
}

void CMFCSensorDlg::OnEnChangeEdtRx()
{
	
}

void CMFCSensorDlg::OnTimer(UINT_PTR nIDEvent)
{
	int a;
	CTime TemperaturaHumedad = CTime::GetCurrentTime(); //Obtiene la temperatura y la humedad actual del sistema
	Port->ReadData(recibido, sizeof(recibido) - 1);//Lee el contenido del puerto serial
	//CString TemperaturaHumedadTxt = TemperaturaHumedad.Format("");
	SetDlgItemText(IDC_EDT_RX, (LPTSTR)recibido);// Coloca texto en un control

	CDialogEx::OnTimer(nIDEvent);
}



