#pragma once

#include <afxwin.h> 
#include <afxext.h>
#include <afx.h>
#include "pch.h"
#include "Game.h"
#include "ToolMain.h"
#include "resource.h"
#include "MFCFrame.h"
#include "SelectDialogue.h"
#include "TransformDialogue.h"
#include "ToolMain.h"


class MFCMain : public CWinApp 
{
public:
	MFCMain();
	~MFCMain();
	BOOL InitInstance();
	int  Run();

	void OnDialogueBoxDestroyed();

	void LoadEditorSettings(const std::wstring& filename);

private:

	CMyFrame * m_frame;	//handle to the frame where all our UI is
	HWND m_toolHandle;	//Handle to the MFC window
	ToolMain m_ToolSystem;	//Instance of Tool System that we interface to. 
	CRect WindowRECT;	//Window area rectangle. 
	SelectDialogue m_ToolSelectDialogue;			//for modeless dialogue, declare it here
	TransformDialogue m_ToolTransformDialogue;     //dialogue for move obects with mfc interface
	CommandManager* m_commandManager;
	int m_width;		
	int m_height;

	//used to check if the window is open to control object picking when dialogue box is open
	bool WindowOpen;
	
	//Interface funtions for menu and toolbar etc requires
	afx_msg void MenuFileQuit();
	afx_msg void MenuFileSaveTerrain();
	afx_msg void MenuEditSelect();
	afx_msg void MenuEditTransform();
	afx_msg	void ToolBarButton1();

	//set window bool true to stop object picking
	void OnDialogueBoxCreated();


	DECLARE_MESSAGE_MAP()	// required macro for message map functionality  One per class
};
