#include "StdAfx.h"
#include "3DCamera.h"
#include "ChatWnd.h"
#include "Configs.h"
#include "ToolKit.h"
#include "Message.h"
// 1.03k



int *MAIN_STATE_ADDR  = (int*)0x008D6F7C; 
int *MAP_CHECKER_ADDR = (int*)0x008C5CF8; 

float *Camera_Zoom   = (float*)0x006001E9;
float *Camera_RotY   = (float*)0x0088BC78;
float *Camera_RotZ   = (float*)0x0809F150;
float *Camera_PosZ   = (float*)0x0088ACFC;
float *Camera_ClipX  = (float*)0x0088BB18;
float *Camera_ClipY  = (float*)0x005AB4CD;
float *Camera_GlClip = (float*)0x0088BB4C;

struct CameraStruct 
{
		float Zoom;
		float RotY;
		float RotZ;
		float PosZ;
		float ClipX;
		float ClipY;
		float GlClip;
} Camera;

#define CAM_DEFAULT (*Camera_PosZ != 150.0f || *Camera_RotZ != -45.0f || *Camera_RotY != -48.5f || *Camera_Zoom != 35.0f)

enum MAINSTATE 
{
	SELECT_SERVER    = 2,
	SELECT_CHARACTER = 4,
	SELECT_GAME      = 5,
};

int MouseX; 
int MouseY; 
bool MoveCamera = false;
bool InitCamera = true; 
bool VK_IsPressed = false;
bool NotAvaible;
int Sensivity = 8;

float GetMemBuffer(DWORD *dwpAddress) 
{
	float pBuffer;
	if (ReadProcessMemory(GetCurrentProcess(), dwpAddress, (float*)&pBuffer, 4, 0) == TRUE) 
		return pBuffer;
	else return 0;
}

void UnProtect(DWORD *dwpAddress, float pBuffer) 
{
	DWORD dwOldProtect = 0;
	HANDLE hWnd = GetCurrentProcess();
	VirtualProtectEx(hWnd, dwpAddress, 4, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	WriteProcessMemory(hWnd, dwpAddress, (void*)&pBuffer, 4, 0);
	VirtualProtectEx(hWnd, dwpAddress, 4, PAGE_EXECUTE_READWRITE, &dwOldProtect);
}

void CAMDefault(void *lParam)
{
	while (CAM_DEFAULT)
	{
		(*Camera_PosZ > 150.0f) ? UnProtect((DWORD*)Camera_PosZ, (GetMemBuffer((DWORD*)CAMERA_POSZ))-5.0f) : UnProtect((DWORD*)Camera_PosZ, (GetMemBuffer((DWORD*)CAMERA_POSZ))+5.0f);
		if (*Camera_PosZ > 146.0f && *Camera_PosZ < 152.0f)
			UnProtect((DWORD*)Camera_PosZ, 150.0f);

		(*Camera_RotZ > -45.0f) ? UnProtect((DWORD*)Camera_RotZ, (GetMemBuffer((DWORD*)CAMERA_ROTZ))-1.0f) : UnProtect((DWORD*)Camera_RotZ, (GetMemBuffer((DWORD*)CAMERA_ROTZ))+1.0f);
		if (*Camera_RotZ > -47.0f && *Camera_RotZ < -43.0f)
			UnProtect((DWORD*)Camera_RotZ, -45.0f);

		(*Camera_RotY > -48.5f) ? UnProtect((DWORD*)Camera_RotY, (GetMemBuffer((DWORD*)CAMERA_ROTY))-0.5f) : UnProtect((DWORD*)Camera_RotY, (GetMemBuffer((DWORD*)CAMERA_ROTY))+0.5f);
		if (*Camera_RotY > -50.5f && *Camera_RotY < -46.5f)
			UnProtect((DWORD*)Camera_RotY, -48.5f);

		(*Camera_Zoom > 35.0f) ? UnProtect((DWORD*)Camera_Zoom, (GetMemBuffer((DWORD*)CAMERA_ZOOM))-1.0f) : UnProtect((DWORD*)Camera_Zoom, (GetMemBuffer((DWORD*)CAMERA_ZOOM))+1.0f);
		if (*Camera_Zoom > 33.0f && *Camera_Zoom < 37.0f)
			UnProtect((DWORD*)Camera_Zoom, 35.0f);

		Sleep(2);
	}
	_endthread();
};
//==============
//	functions 3D
//==============
void Function3DStart()
{
	if (*MAIN_STATE_ADDR == SELECT_CHARACTER || *MAP_CHECKER_ADDR == 0x1E || *MAP_CHECKER_ADDR == 0x3E
		|| *MAP_CHECKER_ADDR == 24
		|| *MAP_CHECKER_ADDR == 25
		|| *MAP_CHECKER_ADDR == 26
		|| *MAP_CHECKER_ADDR == 27
		|| *MAP_CHECKER_ADDR == 28
		|| *MAP_CHECKER_ADDR == 29
		|| *MAP_CHECKER_ADDR == 36
		|| *MAP_CHECKER_ADDR == 63
		) 
	{
		InitCamera = false;
		NotAvaible = TRUE;
		UnProtect((DWORD*)Camera_ClipX, Camera.ClipX);
		UnProtect((DWORD*)Camera_ClipY, Camera.ClipY); 
		UnProtect((DWORD*)Camera_GlClip, Camera.GlClip);
		UnProtect((DWORD*)Camera_PosZ, 150.0f); 
		UnProtect((DWORD*)Camera_RotY, -48.5f);
		UnProtect((DWORD*)Camera_RotZ, -45.0f);
 		UnProtect((DWORD*)Camera_Zoom, 35.0f);		
	}
}

void Function3DInitCamera()
{
	Camera.ClipX = *Camera_ClipX; Camera.ClipY = *Camera_ClipY; Camera.GlClip = *Camera_GlClip;
	Camera.PosZ = *Camera_PosZ; Camera.RotY = *Camera_RotY; Camera.RotZ = *Camera_RotZ; Camera.Zoom = *Camera_Zoom;
	InitCamera = false;
}

void Function3DZoom(int direction)
{
	if (direction > 0) 
	{
		if(*Camera_Zoom < 45) 
		{ 
			UnProtect((DWORD*)Camera_Zoom, (GetMemBuffer((DWORD*)CAMERA_ZOOM))+2);
		}
	}
	else if (direction < 0) 
	{
		if (*Camera_Zoom > 12)
		{ 
			UnProtect((DWORD*)Camera_Zoom, (GetMemBuffer((DWORD*)CAMERA_ZOOM))-2);
		}
	}
	float Aux = abs(GetMemBuffer((DWORD*)CAMERA_POSZ) - 150) * 3;
	UnProtect((DWORD*)Camera_ClipX, 1190.0f + Aux + 3000.0f);
	UnProtect((DWORD*)Camera_ClipY, 2400.0f + Aux + 3000.0f);
	UnProtect((DWORD*)Camera_GlClip, 3000.0f + Aux + 1500.0f);
}

void Function3DMove(int x, int y)
{
	if (MouseX < x) 
	{
		UnProtect((DWORD*)Camera_RotZ, (GetMemBuffer((DWORD*)CAMERA_ROTZ))+Sensivity);
		if (*Camera_RotZ > 315) 
		{
			UnProtect((DWORD*)Camera_RotZ, -45.0f);
		}
	}
	else if (MouseX > x) 
	{
		UnProtect((DWORD*)Camera_RotZ, (GetMemBuffer((DWORD*)CAMERA_ROTZ))-Sensivity);
		if (*Camera_RotZ < -405) 
		{
			UnProtect((DWORD*)Camera_RotZ, -45.0f);
		}
	}
	if (MouseY < y) 
	{
		if (*Camera_RotY < -45) 
		{	
			UnProtect((DWORD*)Camera_PosZ, (GetMemBuffer((DWORD*)CAMERA_POSZ))-44);;
			UnProtect((DWORD*)Camera_RotY, (GetMemBuffer((DWORD*)CAMERA_ROTY))+2.42f);		
		}
	}
	else if (MouseY > y) 
	{
		if (*Camera_RotY > -90) 
		{
			UnProtect((DWORD*)Camera_PosZ, (GetMemBuffer((DWORD*)CAMERA_POSZ))+44);
			UnProtect((DWORD*)Camera_RotY, (GetMemBuffer((DWORD*)CAMERA_ROTY))-2.42f);
		}
	}
	MouseX = x;
	MouseY = y;
	
	float Aux = abs(GetMemBuffer((DWORD*)CAMERA_POSZ) - 150) * 3;
	UnProtect((DWORD*)Camera_ClipX, 1190.0f + Aux + 3000.0f);
	UnProtect((DWORD*)Camera_ClipY, 2400.0f + Aux + 3000.0f);
	UnProtect((DWORD*)Camera_GlClip, 3000.0f + Aux + 1500.0f);
}

void Function3DRoom1(int x,int y)
{
	MouseX = x;
	MouseY = y;
	MoveCamera = true;
}
void Function3DRoom2()
{
	MoveCamera = false;
}
bool Function3DReturn()
{
	return MoveCamera;
}
bool Function3DNotAvaible()
{
	return NotAvaible;
}
void Function3DNotAvaibleFalse()
{
	NotAvaible = false;
}
bool Function3DInitCameraReturn()
{
	return InitCamera;
}
void Function3DOff()
{
	if(Config.exCAM_IsActive)
	{
		Message_Glob(1,"3DCamera: Off");
		VK_IsPressed = true; Config.CAM_IsActive = false;
	}
}
void Function3DOn()
{
	if(Config.exCAM_IsActive)
	{
		Message_Glob(1,"3DCamera: On");
		VK_IsPressed = false; Config.CAM_IsActive = true;
	}
}
bool Function3DVK_IsPressed()
{
	return VK_IsPressed;
}