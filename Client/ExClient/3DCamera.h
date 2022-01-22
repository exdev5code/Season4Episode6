//#pragma once 

#include "StdAfx.h"

static HINSTANCE hInstance;

#pragma data_seg(".SHAREDDATA")
static HHOOK MouseHook = NULL; 
static HHOOK KeyboardHook = NULL;
#pragma data_seg()

#pragma comment(linker, "/SECTION:.SHAREDDATA,RWS")

#define CAMERA_ZOOM   0x006001E9
#define CAMERA_ROTY   0x0088BC78
#define CAMERA_ROTZ   0x0809F150
#define CAMERA_POSZ   0x0088ACFC
#define CAMERA_CLIPX  0x0088BB18
#define CAMERA_CLIPY  0x005AB4CD
#define CAMERA_GLCLIP 0x0088BB4C 

//float *Camera_Zoom   = (float*)0x006001E9;
//float *Camera_RotY   = (float*)0x0088BC78;
//float *Camera_RotZ   = (float*)0x0809F150;
//float *Camera_PosZ   = (float*)0x0088ACFC;
//float *Camera_ClipX  = (float*)0x0088BB18;
//float *Camera_ClipY  = (float*)0x005AB4CD;
//float *Camera_GlClip = (float*)0x0088BB4C;

//extern bool VK_IsPressed;

float GetMemBuffer(DWORD *dwpAddress);
void UnProtect(DWORD *dwpAddress, float Buffer);

void CAMDefault(void *lParam);


//Functions 3D
void Function3DStart();
void Function3DInitCamera();
void Function3DZoom(int direction);
void Function3DMove(int x, int y);
void Function3DRoom1(int x,int y);
void Function3DRoom2();
bool Function3DReturn();
bool Function3DNotAvaible();
void Function3DNotAvaibleFalse();
bool Function3DInitCameraReturn();
void Function3DOff();
void Function3DOn();
bool Function3DVK_IsPressed();