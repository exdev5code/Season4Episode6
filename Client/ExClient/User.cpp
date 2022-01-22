#include "StdAfx.h"
#include "User.h"

User gObjUser;

User::User()
{
	this->VieweTargetID = -1;
}

void User::Refresh()
{
	
	this->VieweTargetID		= pViewAttackTargetID;

	this->BattleCursor = CheckBattleCursor();
}