
// finalView.h : CfinalView 类的接口
//

#pragma once


class CfinalView : public CView
{
protected: // 仅从序列化创建
	CfinalView();
	DECLARE_DYNCREATE(CfinalView)

// 特性
public:
	CfinalDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CfinalView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:


//五子棋定义的成员
protected:
	int m_data_map[15][15];//储存棋子相对坐标
	int m_data_computer[15][15];//电脑棋子权重表
	int m_count;//步数
	bool m_set_blackfirst;//黑子先手
	bool m_set_whitefirst;//白子先手
	bool m_set_playerfirst;//玩家先手
	bool m_state_gameon;//游戏状态：进行中或者没开始
	bool Judgewinner(int player);//判断胜负
	bool Getpiece(int x,int y);//获取棋子相对坐标
	void Initialize();//数据初始化
	int ComputerJudge();//电脑决策
	bool m_state_gameover;//游戏状态：游戏结束，等待下一轮开始；

public:
	CDC m_white,m_black,m_map;
	CBitmap b_white,b_black,b_map;
	HCURSOR h_black,h_white;

// 生成的消息映射函数
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

#ifndef _DEBUG  // finalView.cpp 中的调试版本
inline CfinalDoc* CfinalView::GetDocument() const
   { return reinterpret_cast<CfinalDoc*>(m_pDocument); }
#endif

