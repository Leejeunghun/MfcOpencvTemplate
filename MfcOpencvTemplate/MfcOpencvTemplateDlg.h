
// MfcOpencvTemplateDlg.h: 헤더 파일
//

#pragma once
#include "opencv2/opencv.hpp"
#include <opencv2/highgui.hpp>  
#include <opencv2/imgproc.hpp>  
using namespace cv;
#include <iostream>
using namespace std;

#include <functional>
using std::endl;
// CMfcOpencvTemplateDlg 대화 상자

//Button Design
#include "RoundButton2.h"
#include "RoundButtonStyle.h"

#include "define.h"

class CMfcOpencvTemplateDlg : public CDialogEx
{
// 생성입니다.
public:
	CMfcOpencvTemplateDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCOPENCVTEMPLATE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnImshosw();
	void ImshowTest(); // OpenCV 제대로 나

public:
	afx_msg void OnBnClickedBtnMouseevent();
	void MouseCheck();

	// In you header make a static and a member version of onMouse
	void onMouse(int event, int x, int y);
	static void onMouse(int event, int x, int y, int, void* userdata);


	//버튼 이미지 생성
	CRoundButtonStyle m_tMyButtonStyle;
	void SettingButton();    //수정 작업 필요
	CRoundButton2 m_btn_close;
	
	// 로그 파일 관련 세팅
	int create_log_file();
	int write_log_file(char* str, ...);
	void addLog(CString msg);
	CString logpath;
	CString m_log;
	CEdit m_ed_log;
	afx_msg void OnBnClickedBtnLog();


// Picture Contorl에 데이터 표시

	CStatic m_Picture_1;
	VideoCapture* capture;
	CImage cimage_mfc;
	Mat mat_Video_frame;

	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnVideo();

	void DisplayImage_BitBit(Mat Displayimage);
	afx_msg void OnBnClickedBtnVideostop();

	afx_msg void OnBnClickedBtnClick();
	void ImageShow();
	afx_msg void OnBnClickedBtnClose();


	//ini파일 관련 함수
	afx_msg void OnBnClickedBtnSetting();
	void OpenInifile();
	void Readinifile();


	//LED 관련 설정
	CStatic* p_static_LED_1 = NULL;
	CStatic* p_static_LED_2 = NULL;
	CStatic* p_static_LED_3 = NULL;

	HBITMAP p_static_1_old_hbit;
	HBITMAP p_static_2_old_hbit;
	HBITMAP p_static_3_old_hbit;

	HBITMAP hbit_G;
	HBITMAP hbit_R;
	HBITMAP hbit_B;
	HBITMAP hbit_Y;
	
	void SettingLEDStatus();
	void SettingLED(int num, int status);
	void SettingLED_Default(); // 기본 상태로 변경

	//라디오 버튼 처리
	UINT m_Radio_index = 0;
	afx_msg void RadioCtrl(UINT id);

	afx_msg void OnBnClickedBtnLedcheck();



	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedBtnTest();

	void RecordWebCam();
	afx_msg void OnBnClickedBtnRecord();


	afx_msg void OnBnClickedButton2();
};
