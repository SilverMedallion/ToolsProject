#include "MFCMain.h"
#include "resource.h"


BEGIN_MESSAGE_MAP(MFCMain, CWinApp)
	ON_COMMAND(ID_FILE_QUIT,	&MFCMain::MenuFileQuit)
	ON_COMMAND(ID_FILE_SAVETERRAIN, &MFCMain::MenuFileSaveTerrain)
	ON_COMMAND(ID_EDIT_SELECT, &MFCMain::MenuEditSelect)
	ON_COMMAND(ID_BUTTON40001,	&MFCMain::ToolBarButton1)
	ON_COMMAND(ID_EDIT_TRANSFORM, &MFCMain::MenuEditTransform)  //added for transform modifaction
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_TOOL, &CMyFrame::OnUpdatePage)
END_MESSAGE_MAP()

BOOL MFCMain::InitInstance()
{
	//instanciate the mfc frame
	m_frame = new CMyFrame();
	m_pMainWnd = m_frame;

	m_frame->Create(	NULL,
					_T("World Of Flim-Flam Craft Editor"),
					WS_OVERLAPPEDWINDOW,
					CRect(100, 100, 1024, 768),
					NULL,
					NULL,
					0,
					NULL
				);

	//show and set the window to run and update. 
	m_frame->ShowWindow(SW_SHOW);
	m_frame->UpdateWindow();


	//default open to false for start as not opened using button yet
	WindowOpen = false;

	m_commandManager = new CommandManager();

	//get the rect from the MFC window so we can get its dimensions
	m_toolHandle = m_frame->m_DirXView.GetSafeHwnd();				//handle of directX child window
	m_frame->m_DirXView.GetClientRect(&WindowRECT);
	m_width		= WindowRECT.Width();
	m_height	= WindowRECT.Height();

	m_ToolSystem.onActionInitialise(m_toolHandle, m_width, m_height);
	m_ToolSystem.SetCommandManager(m_commandManager);
	return TRUE;
}

int MFCMain::Run()
{
	MSG msg;
	BOOL bGotMsg;

	PeekMessage(&msg, NULL, 0U, 0U, PM_NOREMOVE);

	while (WM_QUIT != msg.message)
	{
		if (true)
		{
			bGotMsg = (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE) != 0);
		}
		else
		{
			bGotMsg = (GetMessage(&msg, NULL, 0U, 0U) != 0);
		}

		if (bGotMsg)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			m_ToolSystem.UpdateInput(&msg);
		}
		else
		{	
			int ID = m_ToolSystem.getCurrentSelectionID();
			std::wstring statusString = L"Selected Object: " + std::to_wstring(ID);
			m_ToolSystem.Tick(&msg);

			//send current object ID to status bar in The main frame
			m_frame->m_wndStatusBar.SetPaneText(1, statusString.c_str(), 1);	
		}
	}

	return (int)msg.wParam;
}

//set window open to false to allow for object picking again
void MFCMain::OnDialogueBoxDestroyed() 
{
	WindowOpen = false;
	m_ToolSystem.OnWindowStatusChanged(WindowOpen);
}


void MFCMain::MenuFileQuit()
{
	//will post message to the message thread that will exit the application normally
	PostQuitMessage(0);
}

void MFCMain::MenuFileSaveTerrain()
{
	m_ToolSystem.onActionSaveTerrain();
}

void MFCMain::MenuEditSelect()
{
	//SelectDialogue m_ToolSelectDialogue(NULL, &m_ToolSystem.m_sceneGraph);		//create our dialoguebox //modal constructor
	//m_ToolSelectDialogue.DoModal();	// start it up modal

	//modeless dialogue must be declared in the class.   If we do local it will go out of scope instantly and destroy itself
	m_ToolSelectDialogue.Create(IDD_DIALOG1);	//Start up modeless
	m_ToolSelectDialogue.ShowWindow(SW_SHOW);	//show modeless
	m_ToolSelectDialogue.SetObjectData(&m_ToolSystem.m_sceneGraph, &m_ToolSystem.m_selectedObject);

	OnDialogueBoxCreated();
}

void MFCMain::MenuEditTransform()
{
	//with multiselect would need a check here but for this might be ok
	//may need another check 

	int ID = m_ToolSystem.m_selectedObject; 

	m_ToolTransformDialogue.SetCommandManager(m_commandManager);

	//pass the id to the transform dialogue
	m_ToolTransformDialogue.Create(IDD_TRANSFORM_DIALOG);	//Start up modeless
	m_ToolTransformDialogue.SetDisplayGraph(m_ToolSystem.GetDisplayList());
	m_ToolTransformDialogue.SetMain(this);
	m_ToolTransformDialogue.SetGame(&m_ToolSystem.GetGame());
	m_ToolTransformDialogue.SetSelection(ID);
	//TODO: set command manger here when done
	m_ToolTransformDialogue.ShowWindow(SW_SHOW);	//show modeless

	m_ToolTransformDialogue.InitialiseWithSelection(); //TODO: complete definition of update from selected objects(funciton called in this function)
	OnDialogueBoxCreated();

}

void MFCMain::ToolBarButton1()
{
	
	m_ToolSystem.onActionSave();
}

void MFCMain::OnDialogueBoxCreated()
{
	WindowOpen = true;
	m_ToolSystem.OnWindowStatusChanged(WindowOpen);
}


MFCMain::MFCMain()
{
}


MFCMain::~MFCMain()
{
}


