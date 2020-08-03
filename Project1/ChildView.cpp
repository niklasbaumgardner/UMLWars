
// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include "framework.h"
#include "Project1.h"
#include "ChildView.h"
#include "ItemHarold.h"
#include "ItemScoreboard.h"
#include "ItemSharpie.h"
#include "DoubleBufferDC.h"
#include <memory>
using namespace Gdiplus;
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int FrameDuration = 30;

// CChildView

CChildView::CChildView()
{
	srand((unsigned int)time(nullptr));
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_CHANGECHARACTER_HAROLD, &CChildView::OnChangecharacterHarold)
	ON_COMMAND(ID_CHANGECHARACTER_IKE, &CChildView::OnChangecharacterIke)
	ON_COMMAND(ID_CHANGECHARACTER_SPARTY, &CChildView::OnChangecharacterSparty)
	ON_COMMAND(ID_CHANGECHARACTER_VINNIE, &CChildView::OnChangecharacterVinnie)
	ON_COMMAND(ID_TEAMDAHL_WILL, &CChildView::OnTeamdahlWill)
	ON_COMMAND(ID_TEAMDAHL_NIK, &CChildView::OnTeamdahlNik)
	ON_COMMAND(ID_TEAMDAHL_CHRIS, &CChildView::OnTeamdahlChris)
	ON_COMMAND(ID_CHANGECHARACTER_DROWEN, &CChildView::OnChangecharacterDrowen)
	ON_COMMAND(ID_TEAMDAHL_HSUKENGL, &CChildView::OnTeamdahlHsukengl)
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}
/** 
* Draws the game
*/
void CChildView::OnPaint() 
{
	CPaintDC paintDC(this); 
	CDoubleBufferDC dc(&paintDC); // device context for painting
	Graphics graphics(dc.m_hDC);    // Create GDI+ graphics context

	if (mFirstDraw)
	{
		mFirstDraw = false;
		SetTimer(1, FrameDuration, nullptr);

		/*
		* Initialize the elapsed time system
		*/
		LARGE_INTEGER time, freq;
		QueryPerformanceCounter(&time);
		QueryPerformanceFrequency(&freq);

		mLastTime = time.QuadPart;
		mTimeFreq = double(freq.QuadPart);
	}

	/*
	* Compute the elapsed time since the last draw
	*/
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	long long diff = time.QuadPart - mLastTime;
	double elapsed = double(diff) / mTimeFreq;
	mLastTime = time.QuadPart;

	mGame.Update(elapsed);

	CRect rect;
	GetClientRect(&rect);

	mGame.OnDraw(&graphics, rect.Width(), rect.Height());

}

/**
* Notifies the game of mouse movement
* \param nFlags 
* \param point Mouse coordinates
*/
void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	mGame.OnMouseMove(point.x, point.y);
	CWnd::OnMouseMove(nFlags, point);

}

/**
* Notifies the game of left button click
* \param nFlags
* \param point Mouse coordinates
*/
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CWnd::OnLButtonDown(nFlags, point);
	mGame.Shoot(point.x, point.y);
}

/**
*  Erase the background prior to drawing.
*
* We return true so this does nothing. This prevents the flicker
* of a repaint of white before actual drawing.
* \param pDC
* \return FALSE
*/
BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	Invalidate();
	return FALSE;
}

/**
* Changes character image to Harold
*/
void CChildView::OnChangecharacterHarold()
{
	mGame.ChangeCharacter(L"../images/harold.png");
}

/**
* Changes character image to Ike
*/
void CChildView::OnChangecharacterIke()
{
	mGame.ChangeCharacter(L"../images/ike.png");
	// TODO: Add your command handler code here
}

/**
* Changes character image to Sparty
*/
void CChildView::OnChangecharacterSparty()
{
	mGame.ChangeCharacter(L"../images/sparty.png");
	// TODO: Add your command handler code here
}

/**
* Changes character image to Vinnie
*/
void CChildView::OnChangecharacterVinnie()
{
	mGame.ChangeCharacter(L"../images/vinnie.png");
	// TODO: Add your command handler code here
}

/**
* Changes character image to Will
*/
void CChildView::OnTeamdahlWill()
{
	mGame.ChangeCharacter(L"../images/will.png");
	// TODO: Add your command handler code here
}

/**
* Changes character image to Nik
*/
void CChildView::OnTeamdahlNik()
{
	mGame.ChangeCharacter(L"../images/nik.png");
	// TODO: Add your command handler code here
}

/**
* Changes character image to Chris
*/
void CChildView::OnTeamdahlChris()
{
	mGame.ChangeCharacter(L"../images/chris.png");
	// TODO: Add your command handler code here
}

/**
* Changes character image to Dr. Owen
*/
void CChildView::OnChangecharacterDrowen()
{
	mGame.ChangeCharacter(L"../images/dr.owen.png");
	// TODO: Add your command handler code here
}

/**
* Changes character image to Huskengl
*/
void CChildView::OnTeamdahlHsukengl()
{
	mGame.ChangeCharacter(L"../images/huskengl.png");
	// TODO: Add your command handler code here
}
