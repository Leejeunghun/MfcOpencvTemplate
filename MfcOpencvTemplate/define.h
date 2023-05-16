#pragma once

#define LED_BLACK 0
#define LED_GREEEN 1
#define LED_RED 2
#define LED_YELLOW 3


// 카메라 설정

#define CAM_1 0
#define CAM_2 1
#define PC_3  2

typedef struct
{
	int Cam_index;
	HANDLE param;
}ThreadCameradParameter;


#define PostMessageLOG WM_USER+1