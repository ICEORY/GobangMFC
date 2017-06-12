
// finalView.h : CfinalView ��Ľӿ�
//

#pragma once


class CfinalView : public CView
{
protected: // �������л�����
	CfinalView();
	DECLARE_DYNCREATE(CfinalView)

// ����
public:
	CfinalDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CfinalView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:


//�����嶨��ĳ�Ա
protected:
	int m_data_map[15][15];//���������������
	int m_data_computer[15][15];//��������Ȩ�ر�
	int m_count;//����
	bool m_set_blackfirst;//��������
	bool m_set_whitefirst;//��������
	bool m_set_playerfirst;//�������
	bool m_state_gameon;//��Ϸ״̬�������л���û��ʼ
	bool Judgewinner(int player);//�ж�ʤ��
	bool Getpiece(int x,int y);//��ȡ�����������
	void Initialize();//���ݳ�ʼ��
	int ComputerJudge();//���Ծ���
	bool m_state_gameover;//��Ϸ״̬����Ϸ�������ȴ���һ�ֿ�ʼ��

public:
	CDC m_white,m_black,m_map;
	CBitmap b_white,b_black,b_map;
	HCURSOR h_black,h_white;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRestart();
	afx_msg void OnSetPlayerfirst();
	afx_msg void OnUpdateSetPlayerfirst(CCmdUI *pCmdUI);
	afx_msg void OnSetWhitefirst();
	afx_msg void OnUpdateSetWhitefirst(CCmdUI *pCmdUI);
	afx_msg void OnSetBlackfirst();
	afx_msg void OnUpdateSetBlackfirst(CCmdUI *pCmdUI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // finalView.cpp �еĵ��԰汾
inline CfinalDoc* CfinalView::GetDocument() const
   { return reinterpret_cast<CfinalDoc*>(m_pDocument); }
#endif

