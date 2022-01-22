#ifndef __PROTOCOLDEF__
#define __PROTOCOLDEF__
//////////////////////////////////////////////////////////////////////////////
// �������ݿ� ���

#define PMHC_BYTE				0xC1 // Ŭ���̾�Ʈ�� ������ 1����Ʈ¥�� �������� 
#define PMHC_WORD				0xC2 // Ŭ���̾�Ʈ�� ������ 2����Ʈ¥�� �������� 
#define PMHCE_BYTE				0xC3 // Ŭ���̾�Ʈ�� ������ 1����Ʈ¥�� �������� 
#define PMHCE_WORD				0xC4 // Ŭ���̾�Ʈ�� ������ 2����Ʈ¥�� �������� 

#define SET_NUMBERH(x) ( (BYTE)((DWORD)(x)>>(DWORD)8) )
#define SET_NUMBERL(x) ( (BYTE)((DWORD)(x) & 0xFF) )

typedef struct
{
	void set ( LPBYTE lpBuf, BYTE head, BYTE size)
	{
		lpBuf[0] = PMHC_BYTE;
		lpBuf[1] = size;
		lpBuf[2] = head;
	};

	void setE ( LPBYTE lpBuf, BYTE head, BYTE size)
	{
		lpBuf[0] = PMHCE_BYTE;
		lpBuf[1] = size;
		lpBuf[2] = head;
	};	

	BYTE c;			// �������� �ڵ�
	BYTE size;		// �������� ũ��( ��� ũ�� ���� )
	BYTE headcode;	// �������� ����
} PBMSG_HEAD, *LPPBMSG_HEAD;

typedef struct
{
	void set( LPBYTE lpBuf, BYTE head, int size)
	{
		lpBuf[0] = PMHC_WORD;
		lpBuf[1] = SET_NUMBERH(size);
		lpBuf[2] = SET_NUMBERL(size);
		lpBuf[3] = head;
	};

	void setE( LPBYTE lpBuf, BYTE head, int size)
	{
		lpBuf[0] = PMHCE_WORD;
		lpBuf[1] = SET_NUMBERH(size);
		lpBuf[2] = SET_NUMBERL(size);
		lpBuf[3] = head;
	};

	BYTE c;			// �������� �ڵ�
	BYTE sizeH;		// �������� ũ��( ��� ũ�� ���� ) ����
	BYTE sizeL;
	BYTE headcode;	// �������� ����
} PWMSG_HEAD, *LPPWMSG_HEAD;


typedef struct
{
	void set( LPBYTE lpBuf, BYTE head, BYTE sub, BYTE size)
	{
		lpBuf[0] = PMHC_BYTE;
		lpBuf[1] = size;
		lpBuf[2] = head;
		lpBuf[3] = sub;
	};

	BYTE c;			// �������� �ڵ�
	BYTE size;		// �������� ũ��( ��� ũ�� ���� )
	BYTE headcode;	// �������� ����
	BYTE subcode;	// ���� �������� ����
} PBMSG_HEAD2, * LPPBMSG_HEAD2;

typedef struct
{
	void set(LPBYTE lpBuf, BYTE head, BYTE sub, int size)
	{
		lpBuf[0] = PMHC_WORD;
		lpBuf[1] = SET_NUMBERH(size);
		lpBuf[2] = SET_NUMBERL(size);
		lpBuf[3] = head;
		lpBuf[4] = sub;
	}

	BYTE c;			// �������� �ڵ�
	BYTE sizeH;		// �������� ũ�� ���� ����Ʈ
	BYTE sizeL;		// �������� ũ�� ���� ����Ʈ
	BYTE headcode;	// �������� ����
	BYTE subcode;	// ���� �������� ����
} PWMSG_HEAD2, * LPPWMSG_HEAD2;


//----------------------------------------------------------------------------
// ī����
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	BYTE		count;
} PBMSG_COUNT, * LPPBMSG_COUNT;


//----------------------------------------------------------------------------
// ī����
//----------------------------------------------------------------------------
typedef struct
{
	PWMSG_HEAD	h;
	BYTE		count;
} PWMSG_COUNT, * LPPWMSG_COUNT;

//----------------------------------------------------------------------------
// SUBCODE �� �ִ� ī���� 
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	BYTE		subcode;
	BYTE		count;
} PBMSGS_COUNT, * LPPBMSGS_COUNT;


#endif
