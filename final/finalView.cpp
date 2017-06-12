
// finalView.cpp : CfinalView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "final.h"
#endif

#include "finalDoc.h"
#include "finalView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CfinalView

IMPLEMENT_DYNCREATE(CfinalView, CView)

BEGIN_MESSAGE_MAP(CfinalView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CfinalView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_RESTART, &CfinalView::OnRestart)
	ON_COMMAND(ID_SET_PLAYERFIRST, &CfinalView::OnSetPlayerfirst)
	ON_UPDATE_COMMAND_UI(ID_SET_PLAYERFIRST, &CfinalView::OnUpdateSetPlayerfirst)
	ON_COMMAND(ID_SET_WHITEFIRST, &CfinalView::OnSetWhitefirst)
	ON_UPDATE_COMMAND_UI(ID_SET_WHITEFIRST, &CfinalView::OnUpdateSetWhitefirst)
	ON_COMMAND(ID_SET_BLACKFIRST, &CfinalView::OnSetBlackfirst)
	ON_UPDATE_COMMAND_UI(ID_SET_BLACKFIRST, &CfinalView::OnUpdateSetBlackfirst)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CfinalView ����/����

CfinalView::CfinalView()
{
	// TODO: �ڴ˴���ӹ������
	h_black  =  LoadCursor(AfxGetInstanceHandle() , MAKEINTRESOURCE(IDC_CURSOR_BLACK));
	h_white  =  LoadCursor(AfxGetInstanceHandle() , MAKEINTRESOURCE(IDC_CURSOR_WHITE));
	Initialize();
}

CfinalView::~CfinalView()
{
}

BOOL CfinalView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CfinalView ����

void CfinalView::OnDraw(CDC *pDC)
{
	CfinalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
		//����λͼ
	//��������
	b_map.Detach ();
	b_black.Detach ();
	b_white.Detach ();
	m_map.Detach();
	m_white.Detach();
	m_black.Detach();
	m_map.CreateCompatibleDC(pDC);
	b_map.LoadBitmapW(IDB_MAP);
	m_map.SelectObject(&b_map);
	pDC->BitBlt(0,0,400,400,&m_map,0,0,SRCCOPY);

	b_white.LoadBitmapW(IDB_WHITE);//�����ɫ����
	m_white.CreateCompatibleDC(pDC);
	m_white.SelectObject(&b_white);

	b_black.LoadBitmapW(IDB_BLACK);//�����ɫ����
	m_black.CreateCompatibleDC(pDC);
	m_black.SelectObject(&b_black);
	for(int i=0;i<15;i++)
		for(int j=0;j<15;j++)
		{
			int m_x=(i+1)*25;
			int m_y=(j+1)*25;
			if(m_data_map[i][j]==1)
			{
				if(m_set_blackfirst||m_set_playerfirst)pDC->BitBlt(m_x-18,m_y-18,m_x+18,m_y+18,&m_black,0,0,SRCAND);
				else pDC->BitBlt(m_x-20,m_y-18,m_x+16,m_y+18,&m_white,0,0,SRCPAINT);
			}
			else
			{
				if(m_data_map[i][j]==2)
				{
					if(m_set_blackfirst||m_set_playerfirst)pDC->BitBlt(m_x-20,m_y-18,m_x+16,m_y+18,&m_white,0,0,SRCPAINT);
					else
					pDC->BitBlt(m_x-18,m_y-18,m_x+18,m_y+18,&m_black,0,0,SRCAND);
				}
			}
		}
}


// CfinalView ��ӡ


void CfinalView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CfinalView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CfinalView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CfinalView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CfinalView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CfinalView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CfinalView ���

#ifdef _DEBUG
void CfinalView::AssertValid() const
{
	CView::AssertValid();
}

void CfinalView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CfinalDoc* CfinalView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CfinalDoc)));
	return (CfinalDoc*)m_pDocument;
}
#endif //_DEBUG


// CfinalView ��Ϣ�������



void CfinalView::Initialize()
{
	for(int i=0;i<15;i++)
	{
		for(int j=0;j<15;j++)
		{
			m_data_map[i][j]=0;
			m_data_computer[i][j]=0;
		}
	}
	m_count=0;
	m_set_blackfirst=true;
	m_set_whitefirst=false;
	m_set_playerfirst=false;
	m_state_gameon=false;
	m_state_gameover=false;
}
bool CfinalView::Getpiece(int x,int y)
{
	/*CString str;//�ò���������ʾ�������ݣ����ӵ�����
		str.Format(_T("%d "),m_count%2+1);
		MessageBox(str,L"data",NULL);*/
	if(!m_data_map[x][y])
	{
		m_data_map[x][y]=m_count%2+1;
		return true;
	}
	else return false;
			
}
//�ж�ʤ��ʵ�ֺ���
bool CfinalView::Judgewinner(int player)
{
	int winner=0;
	for(int x=0;x<=14;x++)
	{
		for(int y=0;y<=14;y++)
		{
			if(m_data_map[x][y]==player)
			{
				if(x-4>=0&&m_data_map[x-1][y]==player &&m_data_map[x-2][y]==player &&m_data_map[x-3][y]==player && m_data_map[x-4][y]==player)winner=player;
				if(x-4>=0&&y-4>=0&&m_data_map[x-1][y-1]==player &&m_data_map[x-2][y-2]==player &&m_data_map[x-3][y-3]==player && m_data_map[x-4][y-4]==player)winner=player;
				if(y-4>=0&&m_data_map[x][y-1]==player &&m_data_map[x][y-2]==player &&m_data_map[x][y-3]==player && m_data_map[x][y-4]==player)winner=player;
				if(x+4<=14&&y-4>=0&&m_data_map[x+1][y-1]==player &&m_data_map[x+2][y-2]==player &&m_data_map[x+3][y-3]==player && m_data_map[x+4][y-4]==player)winner=player;
				if(x+4<=14&&m_data_map[x+1][y]==player &&m_data_map[x+2][y]==player &&m_data_map[x+3][y]==player && m_data_map[x+4][y]==player)winner=player;
				if(x+4<=14&&y+4<=14&&m_data_map[x+1][y+1]==player &&m_data_map[x+2][y+2]==player &&m_data_map[x+3][y+3]==player && m_data_map[x+4][y+4]==player)winner=player;
				if(y+4<=14&&m_data_map[x][y+1]==player &&m_data_map[x][y+2]==player &&m_data_map[x][y+3]==player && m_data_map[x][y+4]==player)winner=player;
				if(x-4>=0&&y+4<=14&&m_data_map[x-1][y+1]==player &&m_data_map[x-2][y+2]==player &&m_data_map[x-3][y+3]==player && m_data_map[x-4][y+4]==player)winner=player;
				if(winner)break;
			}
		}
		if(winner)break;
	}
	if(winner)
	{
		m_state_gameover=true;
		if(winner==1)
		{
			if(m_set_playerfirst)MessageBox(L"���Ӯ��",L"WINNER",NULL);
			if(m_set_blackfirst)MessageBox(L"����Ӯ��",L"WINNER",NULL);
			if(m_set_whitefirst)MessageBox(L"����Ӯ��",L"WINNER",NULL);
			return true;
		}
		if(winner==2)
		{
			if(m_set_playerfirst)MessageBox(L"����Ӯ��",L"WINNER",NULL);
			if(m_set_blackfirst)MessageBox(L"����Ӯ��",L"WINNER",NULL);
			if(m_set_whitefirst)MessageBox(L"����Ӯ��",L"WINNER",NULL);
			return true;
		}
		return true;
	}
	else
	{
		if(m_count==224)
		{
			MessageBox(L"�ƾ�����",L"WINNER",NULL);
			m_state_gameover=true;
			return true;
		}
		else
		return false;
	}
}
int CfinalView::ComputerJudge()
{
	int m_data_best=0;
	int m_data_root[8];
	int m_value[4];
	//��������Ȩ�س�ʼ��
	for(int i=0;i<15;i++)
		for(int j=0;j<15;j++)m_data_computer[i][j]=0;
	//д�����̸������Ȩ��
	for(int i=0;i<15;i++)
	{
		for(int j=0;j<15;j++)
		{
			if(!m_data_map[i][j])
			{
				for(int p=0;p<4;p++)
				{
					m_value[p]=0;
				}
				for(int p=0;p<4;p++)
				{
					if(p==0)
					{
						m_data_root[0]=m_data_map[i-4][j];
						m_data_root[1]=m_data_map[i-3][j];
						m_data_root[2]=m_data_map[i-2][j];
						m_data_root[3]=m_data_map[i-1][j];

						m_data_root[4]=m_data_map[i+1][j];
						m_data_root[5]=m_data_map[i+2][j];
						m_data_root[6]=m_data_map[i+3][j];
						m_data_root[7]=m_data_map[i+4][j];
					}
					if(p==1)
					{
						m_data_root[0]=m_data_map[i-4][j-4];
						m_data_root[1]=m_data_map[i-3][j-3];
						m_data_root[2]=m_data_map[i-2][j-2];
						m_data_root[3]=m_data_map[i-1][j-1];

						m_data_root[4]=m_data_map[i+1][j+1];
						m_data_root[5]=m_data_map[i+2][j+2];
						m_data_root[6]=m_data_map[i+3][j+3];
						m_data_root[7]=m_data_map[i+4][j+4];
					}
					if(p==2)
					{
						m_data_root[0]=m_data_map[i][j-4];
						m_data_root[1]=m_data_map[i][j-3];
						m_data_root[2]=m_data_map[i][j-2];
						m_data_root[3]=m_data_map[i][j-1];

						m_data_root[4]=m_data_map[i][j+1];
						m_data_root[5]=m_data_map[i][j+2];
						m_data_root[6]=m_data_map[i][j+3];
						m_data_root[7]=m_data_map[i][j+4];
					}
					if(p==3)
					{
						m_data_root[0]=m_data_map[i+4][j-4];
						m_data_root[1]=m_data_map[i+3][j-3];
						m_data_root[2]=m_data_map[i+2][j-2];
						m_data_root[3]=m_data_map[i+1][j-1];

						m_data_root[4]=m_data_map[i-1][j+1];
						m_data_root[5]=m_data_map[i-2][j+2];
						m_data_root[6]=m_data_map[i-3][j+3];
						m_data_root[7]=m_data_map[i-4][j+4];
					}
					if(i-4<=0||j-4<=0)m_data_root[0]=3;
					if(i+4>=14||j+4>=14)m_data_root[7]=3;
					//����ж� A�Է�����-B��������-Oû������-KĿ���
				/*	//��һ�����
					//OKOOO
					if(m_data_root[3]==0&&m_data_root[4]==2&&m_data_root[5]==0&&m_data_root[6]==0)m_value=10;
					//OOKOO
					if(m_data_root[2]==0&&m_data_root[3]==2&&m_data_root[4]==0&&m_data_root[5]==0)m_value=10;
					//OOOKO
					if(m_data_root[1]==0&&m_data_root[2]==2&&m_data_root[3]==0&&m_data_root[4]==0)m_value=10;
					*/
					//��������
					//OKBO
					if(m_data_root[3]==0&&m_data_root[4]==2&&m_data_root[5]==0)m_value[p]=299;
					//OBKO
					if(m_data_root[2]==0&&m_data_root[3]==2&&m_data_root[4]==0)m_value[p]=299;
					//AKBO
					//ABKO
					//OBKA
					//OKBA

					//OKAO
					if(m_data_root[3]==0&&m_data_root[4]==1&&m_data_root[5]==0)m_value[p]=290;
					//OAKO
					if(m_data_root[2]==0&&m_data_root[3]==1&&m_data_root[4]==0)m_value[p]=290;

					//BKAO
					//BAKO
					//OAKB
					//OKAB

					//���������
					//OKBBA
					if(m_data_root[3]==0&&m_data_root[4]==2&&m_data_root[5]==2&&m_data_root[6]==1)m_value[p]=199;
					//OBKBA
					if(m_data_root[2]==0&&m_data_root[3]==2&&m_data_root[4]==2&&m_data_root[5]==1)m_value[p]=199;
					//ABKBO
					if(m_data_root[2]==1&&m_data_root[3]==2&&m_data_root[4]==2&&m_data_root[5]==0)m_value[p]=199;
					//ABBKO
					if(m_data_root[1]==1&&m_data_root[2]==2&&m_data_root[3]==2&&m_data_root[4]==0)m_value[p]=199;

					//OKAAB
					if(m_data_root[3]==0&&m_data_root[4]==1&&m_data_root[5]==1&&m_data_root[6]==2)m_value[p]=190;
					//OAKAB
					if(m_data_root[2]==0&&m_data_root[3]==1&&m_data_root[4]==1&&m_data_root[5]==2)m_value[p]=190;
					//BAKAO
					if(m_data_root[2]==2&&m_data_root[3]==1&&m_data_root[4]==1&&m_data_root[5]==0)m_value[p]=190;
					//BAAKO
					if(m_data_root[1]==2&&m_data_root[2]==1&&m_data_root[3]==1&&m_data_root[4]==0)m_value[p]=190;

					//���������
					//OKBBO
					if(m_data_root[3]==0&&m_data_root[4]==2&&m_data_root[5]==2&&m_data_root[6]==0)m_value[p]=1999;
					//OBKBO
					if(m_data_root[2]==0&&m_data_root[3]==2&&m_data_root[4]==2&&m_data_root[5]==0)m_value[p]=1999;
					//OBBKO
					if(m_data_root[1]==0&&m_data_root[2]==2&&m_data_root[3]==2&&m_data_root[4]==0)m_value[p]=1999;


					//OKBOBO
					if(m_data_root[3]==0&&m_data_root[4]==2&&m_data_root[5]==0&&m_data_root[6]==2&&m_data_root[7]==0)m_value[p]=1995;
					//OBOBKO
					if(m_data_root[0]==0&&m_data_root[1]==2&&m_data_root[2]==0&&m_data_root[3]==2&&m_data_root[4]==0)m_value[p]=1995;
					//OKOBBO
					if(m_data_root[3]==0&&m_data_root[4]==0&&m_data_root[5]==2&&m_data_root[6]==2&&m_data_root[7]==0)m_value[p]=1995;
					//OBBOKO
					if(m_data_root[0]==0&&m_data_root[1]==2&&m_data_root[2]==2&&m_data_root[3]==0&&m_data_root[4]==0)m_value[p]=1995;
					//OBOKBO
					if(m_data_root[1]==0&&m_data_root[2]==2&&m_data_root[3]==0&&m_data_root[4]==2&&m_data_root[5]==0)m_value[p]=1995;
					//OBKOBO
					if(m_data_root[2]==0&&m_data_root[3]==2&&m_data_root[4]==0&&m_data_root[5]==2&&m_data_root[6]==0)m_value[p]=1995;
					
					
					//OKAAO
					if(m_data_root[3]==0&&m_data_root[4]==1&&m_data_root[5]==1&&m_data_root[6]==0)m_value[p]=1990;
					//OAKAO
					if(m_data_root[2]==0&&m_data_root[3]==1&&m_data_root[4]==1&&m_data_root[5]==0)m_value[p]=1990;
					//OAAKO
					if(m_data_root[1]==0&&m_data_root[2]==1&&m_data_root[3]==1&&m_data_root[4]==0)m_value[p]=1990;


					//OKAOAO
					if(m_data_root[3]==0&&m_data_root[4]==1&&m_data_root[5]==0&&m_data_root[6]==1&&m_data_root[7]==0)m_value[p]=1989;
					//OAOAKO
					if(m_data_root[0]==0&&m_data_root[1]==1&&m_data_root[2]==0&&m_data_root[3]==1&&m_data_root[4]==0)m_value[p]=1989;
					//OKOAAO
					if(m_data_root[3]==0&&m_data_root[4]==0&&m_data_root[5]==1&&m_data_root[6]==1&&m_data_root[7]==0)m_value[p]=1989;
					//OAAOKO
					if(m_data_root[0]==0&&m_data_root[1]==1&&m_data_root[2]==1&&m_data_root[3]==0&&m_data_root[4]==0)m_value[p]=1989;
					//OAOKAO
					if(m_data_root[1]==0&&m_data_root[2]==1&&m_data_root[3]==0&&m_data_root[4]==1&&m_data_root[5]==0)m_value[p]=1989;
					//OAKOAO
					if(m_data_root[2]==0&&m_data_root[3]==1&&m_data_root[4]==0&&m_data_root[5]==1&&m_data_root[6]==0)m_value[p]=1989;
					

					//���������
					//ABBBKO
					if(m_data_root[0]==1&&m_data_root[1]==2&&m_data_root[2]==2&&m_data_root[3]==2&&m_data_root[4]==0)m_value[p]=599;
					//ABBKBO
					if(m_data_root[1]==1&&m_data_root[2]==2&&m_data_root[3]==2&&m_data_root[4]==2&&m_data_root[5]==0)m_value[p]=599;
					//ABKBBO
					if(m_data_root[2]==1&&m_data_root[3]==2&&m_data_root[4]==2&&m_data_root[5]==2&&m_data_root[6]==0)m_value[p]=599;
					//OKBBBA
					if(m_data_root[3]==0&&m_data_root[4]==2&&m_data_root[5]==2&&m_data_root[6]==2&&m_data_root[7]==1)m_value[p]=599;
					//OBKBBA
					if(m_data_root[2]==0&&m_data_root[3]==2&&m_data_root[4]==2&&m_data_root[5]==2&&m_data_root[6]==1)m_value[p]=599;
					//OBBKBA
					if(m_data_root[1]==0&&m_data_root[2]==2&&m_data_root[3]==2&&m_data_root[4]==2&&m_data_root[5]==1)m_value[p]=599;

					//BAAAKO
					if(m_data_root[0]==2&&m_data_root[1]==1&&m_data_root[2]==1&&m_data_root[3]==1&&m_data_root[4]==0)m_value[p]=590;
					//BAAKAO
					if(m_data_root[1]==2&&m_data_root[2]==1&&m_data_root[3]==1&&m_data_root[4]==1&&m_data_root[5]==0)m_value[p]=590;
					//BAKAAO
					if(m_data_root[2]==2&&m_data_root[3]==1&&m_data_root[4]==1&&m_data_root[5]==1&&m_data_root[6]==0)m_value[p]=590;
					//OKAAAB
					if(m_data_root[3]==0&&m_data_root[4]==1&&m_data_root[5]==1&&m_data_root[6]==1&&m_data_root[7]==2)m_value[p]=590;
					//OAKAAB
					if(m_data_root[2]==0&&m_data_root[3]==1&&m_data_root[4]==1&&m_data_root[5]==1&&m_data_root[6]==2)m_value[p]=590;
					//OAAKAB
					if(m_data_root[1]==0&&m_data_root[2]==1&&m_data_root[3]==1&&m_data_root[4]==1&&m_data_root[5]==2)m_value[p]=590;


					//���������
					//OBBBKO
					if(m_data_root[0]==0&&m_data_root[1]==2&&m_data_root[2]==2&&m_data_root[3]==2&&m_data_root[4]==0)m_value[p]=8999;
					//OBKBBO
					if(m_data_root[2]==0&&m_data_root[3]==2&&m_data_root[4]==2&&m_data_root[5]==2&&m_data_root[6]==0)m_value[p]=8999;
					//OBBKBO
					if(m_data_root[1]==0&&m_data_root[2]==2&&m_data_root[3]==2&&m_data_root[4]==2&&m_data_root[5]==0)m_value[p]=8999;
					//OKBBBO
					if(m_data_root[3]==0&&m_data_root[4]==2&&m_data_root[5]==2&&m_data_root[6]==2&&m_data_root[7]==0)m_value[p]=8999;

					//OAAAKO
					if(m_data_root[0]==0&&m_data_root[1]==1&&m_data_root[2]==1&&m_data_root[3]==1&&m_data_root[4]==0)m_value[p]=8990;
					//OAKAAO
					if(m_data_root[2]==0&&m_data_root[3]==1&&m_data_root[4]==1&&m_data_root[5]==1&&m_data_root[6]==0)m_value[p]=8990;
					//OAAKAO
					if(m_data_root[1]==0&&m_data_root[2]==1&&m_data_root[3]==1&&m_data_root[4]==1&&m_data_root[5]==0)m_value[p]=8990;
					//OKAAAO
					if(m_data_root[3]==0&&m_data_root[4]==1&&m_data_root[5]==1&&m_data_root[6]==1&&m_data_root[7]==0)m_value[p]=8990;

					//�ĸ����ӵ����
					//KBBBB
					if(m_data_root[4]==2&&m_data_root[5]==2&&m_data_root[6]==2&&m_data_root[7]==2)m_value[p]=9999;
					//BKBBB
					if(m_data_root[3]==2&&m_data_root[4]==2&&m_data_root[5]==2&&m_data_root[6]==2)m_value[p]=9999;
					//BBKBB
					if(m_data_root[2]==2&&m_data_root[3]==2&&m_data_root[4]==2&&m_data_root[5]==2)m_value[p]=9999;
					//BBBKB
					if(m_data_root[1]==2&&m_data_root[2]==2&&m_data_root[3]==2&&m_data_root[4]==2)m_value[p]=9999;
					//BBBBK
					if(m_data_root[0]==2&&m_data_root[1]==2&&m_data_root[2]==2&&m_data_root[3]==2)m_value[p]=9999;
					//KAAAA
					if(m_data_root[4]==1&&m_data_root[5]==1&&m_data_root[6]==1&&m_data_root[7]==1)m_value[p]=9990;
					//AKAAA
					if(m_data_root[3]==1&&m_data_root[4]==1&&m_data_root[5]==1&&m_data_root[6]==1)m_value[p]=9990;
					//AAKAA
					if(m_data_root[2]==1&&m_data_root[3]==1&&m_data_root[4]==1&&m_data_root[5]==1)m_value[p]=9990;
					//AAAKA
					if(m_data_root[1]==1&&m_data_root[2]==1&&m_data_root[3]==1&&m_data_root[4]==1)m_value[p]=9990;
					//AAAAK
					if(m_data_root[0]==1&&m_data_root[1]==1&&m_data_root[2]==1&&m_data_root[3]==1)m_value[p]=9990;
				}

				//��ȡ���Ȩ�أ�������һ������¿��ǲ�ͬ������
				int max_1=-9999,max_2=-9999;
				int temp_p=0,temp_k=0;
				for(int p=0;p<4;p++)//��ȡ���Ȩ��
				{
					if(max_1<=m_value[p])
					{
						max_1=m_value[p];
						temp_p=p;
					}
				}
				for(int p=0;p<4;p++)//��ȡ�ڶ���Ȩ��
				{
					if(p!=temp_p&&max_2<=m_value[p])
					{
						max_2=m_value[p];
					}
				}
				//���ǵ�һ��ڶ�Ȩ�ص����
				if(max_1<9990)
				{
					if(max_1>=1989&&max_2>=590)m_data_computer[i][j]=8988;
					if(max_1==590&&max_2==590)m_data_computer[i][j]=8990;
					if(max_1==599&&max_2==599)m_data_computer[i][j]=8999;
					else m_data_computer[i][j]=max_1;
				}
				else m_data_computer[i][j]=max_1;
			}
			else
			{
				m_data_computer[i][j]=-9999;
			}
		}
	}

	//��ȡ���ʺϵ������
	int m_data_max=0;
	for(int i=0;i<15;i++)
	{
		for(int j=0;j<15;j++)
		{
			if(m_data_max<=m_data_computer[i][j])
			{
				m_data_max=m_data_computer[i][j];
				m_data_best=i*100+j;
			}
		}
	}
	return m_data_best;
}

void CfinalView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(!m_state_gameover)
	{
		int m_x=0,m_y=0;//����ʵ������
		int m_data_x=0,m_data_y=0;//�����������
		CDC *pDC=GetDC();
		if(point.x<=380&&point.y<=390)
		{
			int m_temp=0;
			m_state_gameon=true;
			while(1)
			{
				if(point.x<m_x+13 && point.x>=m_x-13)break;
				m_x+=25;
				m_data_x++;
			}
			while(1)
			{
				if(point.y<m_y+13 && point.y>=m_y-13)break;
				m_y+=25;
				m_data_y++;
			}
			if(Getpiece(m_data_x-1,m_data_y-1)==true)
			{
				if(m_set_blackfirst)
				{
					if(m_count%2==0)
					{
						pDC->BitBlt(m_x-18,m_y-18,m_x+18,m_y+18,&m_black,0,0,SRCAND);
					}
					else
					{
						pDC->BitBlt(m_x-20,m_y-18,m_x+16,m_y+18,&m_white,0,0,SRCPAINT);
					}
					Judgewinner(m_count%2+1);
					m_count++;
				}
				else
				{
					if(m_set_whitefirst)
					{
						if(m_count%2==0)
						{
							pDC->BitBlt(m_x-20,m_y-18,m_x+16,m_y+18,&m_white,0,0,SRCPAINT);
						}
						else
						{
							pDC->BitBlt(m_x-18,m_y-18,m_x+18,m_y+18,&m_black,0,0,SRCAND);
						}
						Judgewinner(m_count%2+1);
						m_count++;
					}
					else
					{
						pDC->BitBlt(m_x-18,m_y-18,m_x+18,m_y+18,&m_black,0,0,SRCAND);
						bool temp=Judgewinner(m_count%2+1);
						m_count++;
						if(!temp)
						{
							int m_temp=ComputerJudge();
							m_data_x=m_temp/100;
							m_data_y=m_temp%100;
							Getpiece(m_data_x,m_data_y);
							m_x=(m_data_x+1)*25;
							m_y=(m_data_y+1)*25;
							pDC->BitBlt(m_x-20,m_y-18,m_x+16,m_y+18,&m_white,0,0,SRCPAINT);
							Judgewinner(m_count%2+1);
							m_count++;
						}
					}
				}
			}
		}
	}
	CView::OnLButtonDown(nFlags, point);
}


void CfinalView::OnRestart()
{
	// TODO: Add your command handler code here
	Initialize();
	CDC *pDC=GetDC();
	pDC->BitBlt(0,0,400,400,&m_map,0,0,SRCCOPY);
}


void CfinalView::OnSetPlayerfirst()
{
	// TODO: Add your command handler code here
	m_set_blackfirst=false;
	m_set_whitefirst=false;
	m_set_playerfirst=true;
}


void CfinalView::OnUpdateSetPlayerfirst(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(!m_state_gameon)pCmdUI->Enable(true);
	else pCmdUI->Enable(false);
	if(m_set_playerfirst)pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}


void CfinalView::OnSetWhitefirst()
{
	// TODO: Add your command handler code here
	m_set_blackfirst=false;
	m_set_whitefirst=true;
	m_set_playerfirst=false;
}


void CfinalView::OnUpdateSetWhitefirst(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(!m_state_gameon)pCmdUI->Enable(true);
	else pCmdUI->Enable(false);
	if(m_set_whitefirst)pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}


void CfinalView::OnSetBlackfirst()
{
	// TODO: Add your command handler code here
	m_set_blackfirst=true;
	m_set_whitefirst=false;
	m_set_playerfirst=false;
}


void CfinalView::OnUpdateSetBlackfirst(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(!m_state_gameon)pCmdUI->Enable(true);
	else pCmdUI->Enable(false);
	if(m_set_blackfirst)pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}


void CfinalView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(point.x<=380&&point.y<=390)
	{
		if(m_set_blackfirst)
		{
			if(m_count%2==0)::SetCursor(h_black);
			else ::SetCursor(h_white);
		}
		else
		{
			if(m_set_whitefirst)
			{
				if(m_count%2==0)::SetCursor(h_white);
				else ::SetCursor(h_black);
			}
		}
	}
	CView::OnMouseMove(nFlags, point);
}
