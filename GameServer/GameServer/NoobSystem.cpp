#include "StdAfx.h"

#if __MuRain__

#include "NoobSystem.h"
#include "user.h"

cNoobSystem gNoobSystem;

void cNoobSystem::Init()
{
	this->Enable = GetPrivateProfileInt("Common","Enable",0,NOOBSYSTEM_DIR);
	this->MaxTime = (GetPrivateProfileInt("Common","MaxTime",0,NOOBSYSTEM_DIR) * 60);
	this->PlusExp = GetPrivateProfileInt("Common","PlusExp",0,NOOBSYSTEM_DIR);
}

void cNoobSystem::Timer(int aIndex)
{
	if(!this->Enable)return;

	if(this->MaxTime >= ExUser[aIndex].NoobTime)
	{
		ExUser[aIndex].NoobTime++;
	}
}

void cNoobSystem::Experience(LPOBJ lpObj, __int64 &Exp)
{
	if(!this->Enable) return;
	if(ExUser[lpObj->m_Index].Reset >= 2) return;
	if(this->MaxTime > ExUser[lpObj->m_Index].NoobTime)
	{
		Exp += (( Exp * this->PlusExp ) / 100 );
	}
}

#endif