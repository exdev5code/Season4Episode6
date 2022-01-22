//----------------------------------------------------------------------------
// MU ����������Ʈ ���ݿ� ���� ���ǵǾ� ���Ǿ����� �͵�..
//----------------------------------------------------------------------------
#ifndef __DEFINE_H__
#define __DEFINE_H__

#include "..\\Include\\Public.h"

//----------------------------------------------------------------------------
// �����Ͻÿ� ���Ǵ� ��
//#define _DEBUG_PROTOCOL					// ���������� ����� �ÿ� ��� 
#define LOG_PRINT			1				// �α׸� ����Ұ��ΰ�?
#define SPEEDHACK_CHECK		1				// ���ǵ����� üũ�Ұ��ΰ�?
#define TESTSERVER	 		1				// �׽�Ʈ �����ΰ�..
#define LOCALCONNECT		0				// �系������ ���� �����ϰ�..
#define DATANOSAVE			0				// �����Ͱ� ������� �ʰ� �Ѵ�.

//----------------------------------------------------------------------------
#define CERTIFYTYPE_ACCOUNT		0			// ��������
#define CERTIFYTYPE_IP			1			// IP ����

#define BILLTYPE_JUNGYANG		0			// ���� 
#define BILLTYPE_JUNGACK		1			// ���� 
#define BILLTYPE_JONGYANG		2			// ����
#define BILLTYPE_TIME			3			// �ð���		
#define BILLTYPE_DATE			4			// ��¥��
#define BILLTYPE_NOCHARGE		5			// ����

//----------------------------------------------------------------------------
// ���������� �����ϴ� ���α׷��� Ÿ��
#define ST_GAMESERVER				1			// ���Ӽ��� ��ȣ

#define DEFMAPSERVERPORT			55900		// Map Server port number
#define DEFJOINSERVERPORT			55970		// Join Server port number
#define DEFDATASERVERPORT			55960		// Game Data Server Port number

//----------------------------------------------------------------------------
#define MAX_ROADPATH				15		// ����ڰ� �̵��ϴ� PATH �ִ� ũ��
#define MAX_PATHDIR					8		// �̵��� ���Ǵ� ���� ����
#define MAX_IDSTRING				10		// ���̵� ũ��
#define DEFAULT_MONEY				0		// �ʱ� �־����� �� �׼�
#define MAX_LEVEL					400		// ���� �ִ� ũ��

//----------------------------------------------------------------------------
// ���������� ���Ǵ� ���ǵ�..
#define MAX_JOOMINNUMBERSTR			13		// �ֹε�Ϲ�ȣ ��Ʈ�� ũ�� -�� �A ũ���̴�.
#define MAX_QUESTIONSTR				30		// ���� ��Ʈ�� ũ��
#define MAX_ANSWERSTR				30		// �亯 ��Ʈ�� ũ��
#define MAX_PHONENUMBERSTR			20		// ��ȭ��ȣ ��Ʈ�� ũ��
#define MAX_EMAILSTR				50		// e-mail ��Ʈ�� ũ��

#define MAXVIEWPORTOBJECT			75		// ����Ʈ �ִ� OBJECT �� 
#define MAX_MONVIEWPORTOBJECT		20		// ������ �¿��� �ִ� 10 ���� ���� ǥ��


#define MAXUSERCHARACTER			5		// ������ ������ �ִ� �ִ� ĳ���� ��


#define MAX_GUILDNAMESTRING			8		// ��� �̸� ��Ʈ�� ����

#define MAX_INVENTORYMAP			8*8

#define MAX_PSHOP_SIZE				8*4

#define MAX_ITEMDBBYTE				16		// �������� DB�� ����Ǵ� ����Ʈ ��

#define MAX_EQUIPMENT				12

#define MAX_DBINVENTORY				((MAX_INVENTORYMAP+MAX_EQUIPMENT+MAX_PSHOP_SIZE)*MAX_ITEMDBBYTE) // (8x8x10)+120 �����ͺ��̽� �б�&����Ǵ� �κ��丮������ ũ��


#define MAX_ITEMDBBYTE_V00			7		// �������� DB�� ����Ǵ� ����Ʈ ��


//#define MAX_DBEQUIPMENT				84		// (12x7) �����ͺ��̽� �б�&����Ǵ� ������� ũ��
//#define MAX_DBINVENTORY				532		// (8x8x7)+84 �����ͺ��̽� �б�&����Ǵ� �κ��丮������ ũ��
//#define MAX_ITEMDBBYTE				7		// �������� DB�� ����Ǵ� ����Ʈ ��

#define MAX_WAREHOUSEDBSIZE			1920
#define MAX_WAREHOUSEITEMS			(8*15)

#define MAX_CHAOSBOXSIZE			8*4
#define MAX_CHAOSBOXITEMS			8*4

#define MAX_QUEST					50

#define MAX_INVENTORY				76		// (8x8)+12 �κ��丮 �ִ� ����
#define MAX_TRADEITEM				32		// (8x4) 

#define MAX_DBMAGIC					(MAX_MAGIC*3)	// �����ͺ��̽��� ����Ǵ� ���� ������ ũ��

//----------------------------------------------------------------------------
// Server Type
#define ST_JOINSERVER				0		// ���� ���� ����
#define ST_GAMESERVER				1		// ���� ����
#define MAX_CHAT					60		// ��ȭ �ִ� ũ��
#define MAX_GUILDNOTICE				60		// �ִ� ��� ���� ����

//----------------------------------------------------------------------------
// ĳ���Ϳ� ���õ� ���ǵ�
#define PK_MINIMUM_LEVEL			5		// ����ڳ��� ���ϼ� �ִ� �ּ� ���� 
#define MAX_CLASSTYPE				6		// �ִ� ���� ����

#define MAX_PREVIEWCHARSET			9		// ĳ���� ��Ʈ �ִ� ũ��( �̸������ ���� )


#define MAX_OBJECT					4800	// ���Ӽ����� �ִ� ������Ʈ(����) ��
#define ALLOC_USEROBJECTSTART		2000	// ���Ӽ����� �ִ� ������Ʈ(����) ��

#define OBJTYPE_CHARACTER			1		// ������Ʈ Ÿ���� ����ĳ�����̴�.
#define OBJTYPE_MONSTER				2		// ������Ʈ Ÿ���� �����̴�.
#define OBJTYPE_NPC					3		// ������Ʈ Ÿ����  NPC �̴�.
#define OBJTYPE_ITEM				5		// �������̴�.

//----------------------------------------------------------------------------
// Killer Type ( �׿���
#define KT_CHAR						0		// �÷��̾����� �׾���.
#define KT_MONSTER					1		// �������� �׾���.
#define KT_GUILDWARCHAR				2		// ��������� �÷��̾ �׿���.

//----------------------------------------------------------------------------
// ���ӿ� ���Ǵ� ���ǵ�
#define MAX_LEVELUPPOINT			5		// ĳ���ʹ� ������ ������ ����Ʈ
#define MAX_SHOP					12		// �ִ� ���� ����

#define PK_LEVEL_DEFAULT			3		// PK Level �� �⺻ ��

#define I_TRADE						1		// ��ȯ ������
#define I_PARTY						2		// ��Ƽ ������
#define I_SHOP						3
#define I_GUILD						4		// ��� ���� �������̽�
#define I_GUILDCREATE				5		// ��� ���� �������̽�
#define I_WAREHOUSE					6		// â��
#define I_CHAOSBOX					7		// ī���� �ڽ�

//----------------------------------------------------------------------------
// �ʼ������� ���Ǵ� ���ǵ�..
#define MAX_MAPITEM					200
#define MAX_MAP						63

#define MAX_USEROBJECT				45000
#endif
