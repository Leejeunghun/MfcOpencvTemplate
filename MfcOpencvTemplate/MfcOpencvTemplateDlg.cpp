
// MfcOpencvTemplateDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MfcOpencvTemplate.h"
#include "MfcOpencvTemplateDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 디버그 명령어
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")


// CMfcOpencvTemplateDlg 대화 상자



CMfcOpencvTemplateDlg::CMfcOpencvTemplateDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCOPENCVTEMPLATE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMfcOpencvTemplateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PC_1, m_Picture_1);
	DDX_Control(pDX, IDC_BTN_CLOSE, m_btn_close);
	DDX_Text(pDX, IDC_ED_LOG, m_log);
	DDX_Control(pDX, IDC_ED_LOG, m_ed_log);
}

BEGIN_MESSAGE_MAP(CMfcOpencvTemplateDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_IMSHOSW, &CMfcOpencvTemplateDlg::OnBnClickedBtnImshosw)
	ON_BN_CLICKED(IDC_BTN_MouseEvent, &CMfcOpencvTemplateDlg::OnBnClickedBtnMouseevent)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_VIDEO, &CMfcOpencvTemplateDlg::OnBnClickedBtnVideo)
	ON_BN_CLICKED(IDC_BTN_VIDEOSTOP, &CMfcOpencvTemplateDlg::OnBnClickedBtnVideostop)
	ON_BN_CLICKED(IDC_BTN_CLICK, &CMfcOpencvTemplateDlg::OnBnClickedBtnClick)
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CMfcOpencvTemplateDlg::OnBnClickedBtnClose)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_SETTING, &CMfcOpencvTemplateDlg::OnBnClickedBtnSetting)
	ON_BN_CLICKED(IDC_BTN_LEDCHECK, &CMfcOpencvTemplateDlg::OnBnClickedBtnLedcheck)
	ON_BN_CLICKED(IDC_BTN_LOG, &CMfcOpencvTemplateDlg::OnBnClickedBtnLog)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BTN_TEST, &CMfcOpencvTemplateDlg::OnBnClickedBtnTest)
	ON_BN_CLICKED(IDC_BTN_RECORD, &CMfcOpencvTemplateDlg::OnBnClickedBtnRecord)
END_MESSAGE_MAP()


// CMfcOpencvTemplateDlg 메시지 처리기

BOOL CMfcOpencvTemplateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	//버튼 디자인 시작
	SettingButton();
	SettingLEDStatus();
	SettingLED_Default();


	//로그 세팅
	create_log_file();
	write_log_file("-----------프로그램 시작-----------");

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMfcOpencvTemplateDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMfcOpencvTemplateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMfcOpencvTemplateDlg::OnBnClickedBtnImshosw()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ImshowTest();
}

void CMfcOpencvTemplateDlg::ImshowTest()
{
	TCHAR chFilePath[256] = { 0, };
	GetModuleFileName(NULL, chFilePath, 256);

	CString strFolderPath(chFilePath);
	strFolderPath = strFolderPath.Left(strFolderPath.ReverseFind('\\'));
	strFolderPath += "\\aloeL.jpg";

	cv::Mat img; // 이미지 처리를 위해 Mat 클래스 선언
	img = cv::imread(string(CT2CA(strFolderPath))); // 이미지 읽기

	// 이미지가 없을 경우 예외 처리
	if (img.empty())
	{
		std::cerr << "Image load failed" << std::endl;
		return ;
	}

	cv::namedWindow("image"); // 이미지를 보여주기 위한 빈 창
	cv::imshow("image", img); // "image"라는 이름의 창에 이미지를 넣어 보여줌

	
	return ;
}



void CMfcOpencvTemplateDlg::OnBnClickedBtnMouseevent()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	MouseCheck();

}

void CMfcOpencvTemplateDlg::MouseCheck()
{
	TCHAR chFilePath[256] = { 0, };
	GetModuleFileName(NULL, chFilePath, 256);

	CString strFolderPath(chFilePath);
	strFolderPath = strFolderPath.Left(strFolderPath.ReverseFind('\\'));
	strFolderPath += "\\aloeL.jpg";

	cv::Mat img; // 이미지 처리를 위해 Mat 클래스 선언
	img = cv::imread(string(CT2CA(strFolderPath))); // 이미지 읽기

	// 이미지가 없을 경우 예외 처리
	if (img.empty())
	{
		std::cerr << "Image load failed" << std::endl;
		return;
	}

	//윈도우 생성  
	namedWindow("original image", WINDOW_AUTOSIZE);

	//윈도우에 출력  
	imshow("original image", img);

	//윈도우에 콜백함수를 등록
	setMouseCallback("original image", onMouse, NULL);

	//키보드 입력이 될때까지 대기  
	waitKey(0);

	return ;
}

void CMfcOpencvTemplateDlg::onMouse(int event, int x, int y)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		cout << "왼쪽 마우스 버튼 클릭.. 좌표 = (" << x << ", " << y << ")" << endl;
	}
}

void CMfcOpencvTemplateDlg::onMouse(int event, int x, int y, int, void* userdata)
{
	// Check for null pointer in userdata and handle the error

	CMfcOpencvTemplateDlg* settings = reinterpret_cast<CMfcOpencvTemplateDlg*>(userdata);
	settings->onMouse(event, x, y);

}

void CMfcOpencvTemplateDlg::SettingButton()
{
	// 바꿀 스타일 가져오기
	tButtonStyle tStyle;
	m_tMyButtonStyle.GetButtonStyle(&tStyle);

	// 스타일 바꾸기
	tStyle.m_dRadius = 10.0;   // 버튼 꼭지 곡률
	tStyle.m_tColorFace.m_tEnabled = RGB(200, 200, 200);   // 버튼 기본 글자색

	// 버튼 표면 색 바꾸기
	tStyle.m_tColorFace.m_tEnabled = RGB(220, 220, 220);
	tStyle.m_tColorBorder.m_tEnabled = RGB(0x80, 0x40, 0x40);

	tStyle.m_tColorFace.m_tClicked = RGB(0xFF, 0x80, 0x80);
	tStyle.m_tColorBorder.m_tClicked = RGB(0x80, 0x40, 0x40);

	tStyle.m_tColorFace.m_tPressed = RGB(0x80, 0x80, 0x80);
	tStyle.m_tColorBorder.m_tPressed = RGB(0x40, 0x80, 0x40);

	tStyle.m_tColorBorder.m_tEnabled = RGB(0x00, 0x00, 0xff);
	tStyle.m_tColorBorder.m_tClicked = RGB(0x00, 0x00, 0xff);
	tStyle.m_tColorBorder.m_tEnabled = RGB(0x00, 0x00, 0xff);
	tStyle.m_tColorBorder.m_tHot = RGB(0x00, 0x00, 0xff);

	tStyle.m_tColorBack.m_tEnabled = RGB(0x00, 0x00, 0x00);
	tStyle.m_tColorBack.m_tDisabled = RGB(0x00, 0x00, 0x00);
	tStyle.m_tColorBack.m_tClicked = RGB(0x00, 0x00, 0x00);
	tStyle.m_tColorBack.m_tHot = RGB(0x00, 0x00, 0x00);

	tStyle.m_tColorBack.m_tPressed = RGB(0xff, 0x00, 0x00);

	// 설정한 스타일을 저장
	m_tMyButtonStyle.SetButtonStyle(&tStyle);
	m_btn_close.SetRoundButtonStyle(&m_tMyButtonStyle);
}

void CMfcOpencvTemplateDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CMfcOpencvTemplateDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == 1000)
	{
		//mat_frame가 입력 이미지입니다.

		capture->read(mat_Video_frame);
		DisplayImage_BitBit(mat_Video_frame);
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CMfcOpencvTemplateDlg::OnBnClickedBtnVideo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	capture = new VideoCapture(0);

	if (!capture->isOpened())
	{
		MessageBox(_T("웹캠을 열수 없습니다. \n"));
		return;
	}
	//웹캠 크기를  320x240으로 지정    
	capture->set(CAP_PROP_FRAME_WIDTH, 320);
	capture->set(CAP_PROP_FRAME_HEIGHT, 240);

	SetTimer(1000, 30, NULL);
}

void CMfcOpencvTemplateDlg::DisplayImage_BitBit(Mat Displayimage)
{
	//화면에 보여주기 위한 처리입니다.
	Mat mat_frame = Displayimage.clone();

	int bpp = 8 * mat_frame.elemSize();
	assert((bpp == 8 || bpp == 24 || bpp == 32));

	int padding = 0;
	//32 bit image is always DWORD aligned because each pixel requires 4 bytes
	if (bpp < 32)
		padding = 4 - (mat_frame.cols % 4);

	if (padding == 4)
		padding = 0;

	int border = 0;
	//32 bit image is always DWORD aligned because each pixel requires 4 bytes
	if (bpp < 32)
	{
		border = 4 - (mat_frame.cols % 4);
	}

	Mat mat_temp;
	if (border > 0 || mat_frame.isContinuous() == false)
	{
		// Adding needed columns on the right (max 3 px)
		cv::copyMakeBorder(mat_frame, mat_temp, 0, 0, 0, border, cv::BORDER_CONSTANT, 0);
	}
	else
	{
		mat_temp = mat_frame;
	}

	RECT r;
	m_Picture_1.GetClientRect(&r);
	cv::Size winSize(r.right, r.bottom);

	cimage_mfc.Create(winSize.width, winSize.height, 24);


	BITMAPINFO* bitInfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD));
	bitInfo->bmiHeader.biBitCount = bpp;
	bitInfo->bmiHeader.biWidth = mat_temp.cols;
	bitInfo->bmiHeader.biHeight = -mat_temp.rows;
	bitInfo->bmiHeader.biPlanes = 1;
	bitInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitInfo->bmiHeader.biCompression = BI_RGB;
	bitInfo->bmiHeader.biClrImportant = 0;
	bitInfo->bmiHeader.biClrUsed = 0;
	bitInfo->bmiHeader.biSizeImage = 0;
	bitInfo->bmiHeader.biXPelsPerMeter = 0;
	bitInfo->bmiHeader.biYPelsPerMeter = 0;


	//그레이스케일 인경우 팔레트가 필요
	if (bpp == 8)
	{
		RGBQUAD* palette = bitInfo->bmiColors;
		for (int i = 0; i < 256; i++)
		{
			palette[i].rgbBlue = palette[i].rgbGreen = palette[i].rgbRed = (BYTE)i;
			palette[i].rgbReserved = 0;
		}
	}


	// Image is bigger or smaller than into destination rectangle
	// we use stretch in full rect
	if (mat_temp.cols == winSize.width && mat_temp.rows == winSize.height)
	{
		// source and destination have same size
		// transfer memory block
		// NOTE: the padding border will be shown here. Anyway it will be max 3px width

		SetDIBitsToDevice(cimage_mfc.GetDC(),
			//destination rectangle
			0, 0, winSize.width, winSize.height,
			0, 0, 0, mat_temp.rows,
			mat_temp.data, bitInfo, DIB_RGB_COLORS);
	}
	else
	{
		// destination rectangle
		int destx = 0, desty = 0;
		int destw = winSize.width;
		int desth = winSize.height;

		// rectangle defined on source bitmap
		// using imgWidth instead of mat_temp.cols will ignore the padding border
		int imgx = 0, imgy = 0;
		int imgWidth = mat_temp.cols - border;
		int imgHeight = mat_temp.rows;

		StretchDIBits(cimage_mfc.GetDC(),
			destx, desty, destw, desth,
			imgx, imgy, imgWidth, imgHeight,
			mat_temp.data, bitInfo, DIB_RGB_COLORS, SRCCOPY);
	}


	HDC dc = ::GetDC(m_Picture_1.m_hWnd);
	cimage_mfc.BitBlt(dc, 0, 0);


	::ReleaseDC(m_Picture_1.m_hWnd, dc);

	cimage_mfc.ReleaseDC();
	cimage_mfc.Destroy();

}


void CMfcOpencvTemplateDlg::OnBnClickedBtnVideostop()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	KillTimer(1000);
}


void CMfcOpencvTemplateDlg::OnBnClickedBtnClick()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다
	ImageShow();
}

void CMfcOpencvTemplateDlg::ImageShow()
{
	TCHAR chFilePath[256] = { 0, };
	GetModuleFileName(NULL, chFilePath, 256);

	CString strFolderPath(chFilePath);
	strFolderPath = strFolderPath.Left(strFolderPath.ReverseFind('\\'));
	strFolderPath += "\\aloeL.jpg";

	cv::Mat img; // 이미지 처리를 위해 Mat 클래스 선언
	img = cv::imread(string(CT2CA(strFolderPath))); // 이미지 읽기

	// 이미지가 없을 경우 예외 처리
	if (img.empty())
	{
		std::cerr << "Image load failed" << std::endl;
		return;
	}

	DisplayImage_BitBit(img);
}


void CMfcOpencvTemplateDlg::OnBnClickedBtnClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);
}



void CMfcOpencvTemplateDlg::OnBnClickedBtnSetting()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OpenInifile();
	Readinifile();
}

void CMfcOpencvTemplateDlg::OpenInifile()
{
	TCHAR chFilePath[256] = { 0, };
	GetModuleFileName(NULL, chFilePath, 256);

	CString strIniPath(chFilePath);
	strIniPath = strIniPath.Left(strIniPath.ReverseFind('\\'));
	strIniPath += "\\Setting.ini";

	//ini파일에 데이터 쓰기
	//WritePrivateProfileString("카메라 설정", "ExposureTime", "50000", strFolderPath);
	ShellExecute(NULL,
		"open",
		"notepad", //노트패드(다른 프로그램 변경 가능)
		strIniPath,
		NULL,
		SW_SHOW);
}

void CMfcOpencvTemplateDlg::Readinifile()
{
	TCHAR chFilePath[256] = { 0, };
	GetModuleFileName(NULL, chFilePath, 256);

	CString strIniPath(chFilePath);
	strIniPath = strIniPath.Left(strIniPath.ReverseFind('\\'));
	strIniPath += "\\Setting.ini";

	// 파일 읽기 예시
//	::GetPrivateProfileString("카메라 설정", "ExposureTime", "50000", strReadIni1, 40, strPathIni);
//	m_CamExposureTIme = _ttoi(strReadIni1);
}





void CMfcOpencvTemplateDlg::SettingLEDStatus()
{
	p_static_LED_1 = (CStatic*)GetDlgItem(IDC_PC_LED_1);
	p_static_LED_2 = (CStatic*)GetDlgItem(IDC_PC_LED_2);
	p_static_LED_3 = (CStatic*)GetDlgItem(IDC_PC_LED_3);

	hbit_G = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_GREEN));
	hbit_R = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_RED));
	hbit_B = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_BLACK));
	hbit_Y = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_YELLOW));
}

void CMfcOpencvTemplateDlg::SettingLED(int index, int status)
{
	HBITMAP hbit;

	if (status == LED_BLACK)
	{
		hbit = hbit_B;
	}
	else if (status == LED_GREEEN)   //GREEN
	{
		hbit = hbit_G;
	}
	else if (status == LED_RED)
	{
		hbit = hbit_R;
	}
	else if (status == LED_YELLOW)
	{
		hbit = hbit_Y;
	}

	if (index == 0)
	{
		if (p_static_1_old_hbit != hbit) {
			p_static_1_old_hbit = hbit;
			p_static_LED_1->SetBitmap(hbit); // 이미지를 Picture Control에 설정한다.
		}
	}
	else if (index == 1)
	{
		//		p_static_2->SetBitmap(hbit); // 이미지를 Picture Control에 설정한다.
		if (p_static_2_old_hbit != hbit) {
			p_static_2_old_hbit = hbit;
			p_static_LED_2->SetBitmap(hbit); // 이미지를 Picture Control에 설정한다.
		}

	}
	else if (index == 2)
	{
		//		p_static_3->SetBitmap(hbit); // 이미지를 Picture Control에 설정한다.
		if (p_static_3_old_hbit != hbit) {
			p_static_3_old_hbit = hbit;
			p_static_LED_3->SetBitmap(hbit); // 이미지를 Picture Control에 설정한다.
		}
	}

}

void CMfcOpencvTemplateDlg::SettingLED_Default()
{
	for (int num = 0; num < 3; num++)
	{
		SettingLED(num, 0);
	}
}

void CMfcOpencvTemplateDlg::OnBnClickedBtnLedcheck()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 예시
	SettingLED(1, 1);
}

int CMfcOpencvTemplateDlg::create_log_file()
{
	TCHAR chFilePath[256] = { 0, };
	GetModuleFileName(NULL, chFilePath, 256);

	CString strlogPath(chFilePath);
	strlogPath = strlogPath.Left(strlogPath.ReverseFind('\\'));

	CStdioFile logfile;
	CString fname = NULL;

	SYSTEMTIME tm;
	GetLocalTime(&tm);
	fname.Format("%s\\Log_%04d-%02d-%02d.txt", strlogPath, tm.wYear, tm.wMonth, tm.wDay);

	logpath.Format(fname);

	if (logfile.Open(logpath, CStdioFile::modeCreate | CStdioFile::modeNoTruncate | CStdioFile::modeWrite | CStdioFile::typeText) == FALSE)
	{
		return(1);
	}

	logfile.SeekToEnd();

	CStringA header("\r\n\r\n------------------------------ Log File Start------------------------------\r\n");

	logfile.Write(header, header.GetLength());
	logfile.Close();

	return(0);
}

int CMfcOpencvTemplateDlg::write_log_file(char* str, ...)
{
	CStdioFile logfile;

	//	SYSTEMTIME tm;
		//CString fname;
		//GetLocalTime(&tm);
		//fname.Format("C:\\SicsanNeedle\\Log\\Log_%04d-%02d-%02d.txt", tm.wYear, tm.wMonth, tm.wDay);

		//LogPath.Format(fname);

	SYSTEMTIME lpSystemTime;
	if (logfile.Open(logpath, CStdioFile::modeCreate | CStdioFile::modeNoTruncate | CStdioFile::modeWrite | CStdioFile::typeText) == FALSE)
	{
		return(1);
	}

	logfile.SeekToEnd();

	char buff[1024];
	va_list ap;
	va_start(ap, str);
	vsprintf(buff, str, ap);
	va_end(ap);


	GetLocalTime(&lpSystemTime); // 현재 날짜, 시간 가져오는 함수
	CStringA l_str;
	l_str.Format("[%02d:%02d:%02d] ", lpSystemTime.wHour, lpSystemTime.wMinute, lpSystemTime.wSecond, lpSystemTime.wMilliseconds);

	logfile.Write(l_str, l_str.GetLength());
	logfile.Write(buff, strlen(buff));
	logfile.Write((const void*)"\r\n", 2);
	logfile.Close();

	CString _str1, _str2;
	_str1.Format(_T("%s"), l_str);
	_str2.Format(_T("%s"), str);
	addLog(_str1);
	addLog(_str2);
	return(0);
}

void CMfcOpencvTemplateDlg::addLog(CString msg)
{
	m_log += _T(msg);
	//** Edit Control에 개행
	m_log += _T("\r\n");
	//** Edit Control에 대한 업데이트 진행
	UpdateData(FALSE);

	m_ed_log.LineScroll(m_ed_log.GetLineCount());      //자동 스크롤

	// 로그창이 길어지면 클리어
	if (m_log.GetLength() > 5000) {
		m_log = _T("");
		m_log += _T("\r\n");
		UpdateData(FALSE);
		m_ed_log.LineScroll(m_ed_log.GetLineCount());      //자동 스크롤
	}
}


void CMfcOpencvTemplateDlg::OnBnClickedBtnLog()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	write_log_file("test");
}


BOOL CMfcOpencvTemplateDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	BOOL ret = CDialog::OnEraseBkgnd(pDC);

	return ret;
}




void CMfcOpencvTemplateDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rt;  // 픽쳐 컨트롤의 사각형 영역 조사
     // 픽쳐 컨트롤의 사각형 좌표를 구함
    // GetClientRect 는 크기를 구하니 GetWindowRect 이용...
	((CStatic*)GetDlgItem(IDC_PC_1))->GetWindowRect(&rt);

	// GetWindowRect 로 얻은 좌표는 스크린 좌표(물리적) 이니 이를
	// 화면 좌표(논리적, 클라이언트 좌표)로 변환
	ScreenToClient(&rt);
	if (rt.PtInRect(point)) // 픽쳐 컨트롤의 사각형 영역에 마우스 클릭 좌표(point) 가 있으면...TRUE
	{
		cout << "X: " << point.x << "Y: " <<point.y << endl;
	}  //참고 자료https://iamswdeveloper.tistory.com/entry/MFC%EC%BB%A8%ED%85%8D%EC%8A%A4%ED%8A%B8%EB%A9%94%EB%89%B4-%EC%9C%84%EC%B9%98%EC%B2%B4%ED%81%AC
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMfcOpencvTemplateDlg::OnBnClickedBtnTest()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	std::string pipe = "rtspsrc location=rtsp://192.168.219.106:554/user=admin&password=&channel=1&stream=0.sdp ! rtph264depay ! h264parse ! nvv4l2decoder ! nvvideoconvert ! appsink";

	VideoCapture cap(pipe, CAP_GSTREAMER);

	if (!cap.isOpened()) {
		cerr << "VideoCapture not opened" << endl;
		exit(-1);
	}

	while (true) {
		Mat frame;

		cap.read(frame);

		imshow("receiver.png", frame);

//		getchar();
	}

	return ;
}


void CMfcOpencvTemplateDlg::RecordWebCam()
{
	Mat src;
	// use default camera as video source
	VideoCapture cap(0);
	// check if we succeeded
	if (!cap.isOpened()) {
		cerr << "ERROR! Unable to open camera\n";
		return;
	}
	// get one frame from camera to know frame size and type
	cap >> src;
	// check if we succeeded
	if (src.empty()) {
		cerr << "ERROR! blank frame grabbed\n";
		return ;
	}
	bool isColor = (src.type() == CV_8UC3);

	//--- INITIALIZE VIDEOWRITER
	VideoWriter writer;
	int codec = VideoWriter::fourcc('M', 'J', 'P', 'G');  // select desired codec (must be available at runtime)
	double fps = 25.0;                          // framerate of the created video stream
	string filename = "C:\\BallTypeCounterBar\\live.avi";             // name of the output video file
	writer.open(filename, codec, fps, src.size(), isColor);
	// check if we succeeded
	if (!writer.isOpened()) {
		cerr << "Could not open the output video file for write\n";
		return ;
	}

	//--- GRAB AND WRITE LOOP
	cout << "Writing videofile: " << filename << endl
		<< "Press any key to terminate" << endl;
	for (;;)
	{
		// check if we succeeded
		if (!cap.read(src)) {
			cerr << "ERROR! blank frame grabbed\n";
			break;
		}
		// encode the frame into the videofile stream
		writer.write(src);
		// show live and wait for a key with timeout long enough to show images
		imshow("Live", src);
		if (waitKey(5) >= 0)
			break;
	}
	// the videofile will be closed and released automatically in VideoWriter destructor
	return ;
}

void CMfcOpencvTemplateDlg::OnBnClickedBtnRecord()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	RecordWebCam();
}
