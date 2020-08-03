
// ChildView.h : interface of the CChildView class
//


#pragma once
#include "Game.h"

/**  The child window our program draws in. */

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
private:
	/// An object that describes our game
	CGame mGame;
	/// First draw of game
	bool mFirstDraw = true;
	/// Last time the game was drawn
	long long mLastTime;
	/// Frequency
	double mTimeFreq;
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnChangecharacterHarold();
	afx_msg void OnChangecharacterIke();
	afx_msg void OnChangecharacterSparty();
	afx_msg void OnChangecharacterVinnie();
	afx_msg void OnTeamdahlWill();
	afx_msg void OnTeamdahlNik();
	afx_msg void OnTeamdahlChris();
	afx_msg void OnChangecharacterDrowen();
	afx_msg void OnTeamdahlHsukengl();
};

