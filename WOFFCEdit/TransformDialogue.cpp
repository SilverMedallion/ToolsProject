#include "stdafx.h"
#include "MFCMain.h"
#include "Game.h"
#include "TransformDialogue.h"
#include "MoveObjectCommand.h"
IMPLEMENT_DYNAMIC(TransformDialogue, CDialogEx) //if this flags error just delete and type in again for some reason fixes it

TransformDialogue::TransformDialogue(CWnd* pParent)
	: CDialogEx(IDD_TRANSFORM_DIALOG, pParent)
{

}

TransformDialogue::~TransformDialogue()
{

}

void TransformDialogue::SetMain(MFCMain* main)
{
	Main = main;
}

void TransformDialogue::SetGame(Game* game)
{
	m_game = game;
}


void TransformDialogue::SetDisplayGraph(std::vector<DisplayObject>* displayGraph)
{
	m_displayGraph = displayGraph;
}

void TransformDialogue::UpdateFromSelectedObject()
{
	//return if nothing selected
	if (!m_displayGraph || !m_currentSelection || *m_currentSelection < 0) return;

	//set object for modifying 
	const auto& obj = m_displayGraph->at(*m_currentSelection);

	//modify position
	float posX, posY, posZ;
	posX = obj.m_position.x;
	posY = obj.m_position.y;
	posZ = obj.m_position.z;


	//std::wstring wideName(obj.name.begin(), obj.name.end());
	//m_objectName.SetWindowTextW(wideName.c_str());
	
	m_posX.SetWindowTextW(std::to_wstring(posX).c_str());
	m_posY.SetWindowTextW(std::to_wstring(posY).c_str());
	m_posZ.SetWindowTextW(std::to_wstring(posZ).c_str());

	
}

void TransformDialogue::End()
{
	Main->OnDialogueBoxDestroyed();

	DestroyWindow();	//destroy the window properly
}

void TransformDialogue::OnClose()
{
	if (Main != nullptr)
	{
		Main->OnDialogueBoxDestroyed();
	}

	DestroyWindow();

	CDialogEx::OnClose();
}


BOOL TransformDialogue::PreTranslateMessage(MSG* pMsg)
{
	if ((pMsg->message == WM_KEYDOWN) && (GetKeyState(VK_CONTROL) & 0x8000))
	{
		switch (pMsg->wParam)
		{
			case 'Z': OnUndo(); return TRUE;
			case 'Y': OnRedo(); return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

//assigns buttons to variables
void TransformDialogue::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	// Transforms
	DDX_Control(pDX, IDC_EDIT_POS_X, m_posX);
	DDX_Control(pDX, IDC_EDIT_POS_Y, m_posY);
	DDX_Control(pDX, IDC_EDIT_POS_Z, m_posZ);

	// buttons to add or remove
	DDX_Control(pDX, IDC_PLUSX, m_plusXButton);
	DDX_Control(pDX, IDC_MINUSX, m_minusXButton);
	DDX_Control(pDX, IDC_PLUSY, m_plusYButton);
	DDX_Control(pDX, IDC_MINUSY, m_minusYButton);
	DDX_Control(pDX, IDC_PLUSZ, m_plusZButton);
	DDX_Control(pDX, IDC_MINUSZ, m_minusZButton);
	
}

BOOL TransformDialogue::OnInitDialogue()
{
	CDialogEx::OnInitDialog();

	UpdateFromSelectedObject();
	return TRUE;
}

void TransformDialogue::OnChangePosition()
{
	ApplyChangesToObject();
}

void TransformDialogue::OnIncrement(UINT nID)
{

}

void TransformDialogue::ApplyChangesToObject()
{
	if (!m_displayGraph || !m_currentSelection || *m_currentSelection < 0)
		return;

	DisplayObject& obj = m_displayGraph->at(*m_currentSelection);

	CString value;

	if (m_currentSelection != nullptr && m_game != nullptr)
	{
		//m_game->BuildDisplayList(m_displayGraph);
	}
}

void TransformDialogue::InitialiseWithSelection()
{
	if (m_displayGraph && !m_displayGraph->empty())
	{
		//m_indexStorage = static_cast<int>(m_displayGraph->size() - 1);
		//m_currentSelection = &m_indexStorage;
		UpdateFromSelectedObject();
	}
}

void TransformDialogue::OnUndo()
{
	/*if (m_commandManager)
	{
		m_commandManager->Undo();
		UpdateFromSelectedObject();
		if (m_game != nullptr)
		{
			m_game->BuildDisplayList(m_displayGraph);
		}
	}*/
}

void TransformDialogue::OnRedo()
{
	/*if (m_commandManager)
	{
		m_commandManager->Redo();
		UpdateFromSelectedObject();  // Refresh the UI with the redone state

		if (m_game != nullptr)
		{
			m_game->BuildDisplayList(m_displayGraph);
		}

	}*/
}

void TransformDialogue::UpdateEditFields()
{
	UpdateFromSelectedObject();
}

BEGIN_MESSAGE_MAP(TransformDialogue, CDialogEx)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(IDCLOSE, &TransformDialogue::End)
	
	ON_BN_CLICKED(IDC_PLUSX, &TransformDialogue::OnBnClickedPlusx)
	ON_BN_CLICKED(IDC_MINUSX, &TransformDialogue::OnBnClickedMinusx)
	ON_BN_CLICKED(IDC_PLUSY, &TransformDialogue::OnBnClickedPlusy)
	ON_BN_CLICKED(IDC_MINUSY, &TransformDialogue::OnBnClickedMinusy)
	ON_BN_CLICKED(IDC_PLUSZ, &TransformDialogue::OnBnClickedPlusz)
	ON_BN_CLICKED(IDC_MINUSZ, &TransformDialogue::OnBnClickedMinusz)
END_MESSAGE_MAP()

//BASE OPERATION FOR PLUS TO BASE ALL OTHER OFF
/*
void TransformDialogue::OnOperationPlus()
{
	m_operation = Operation::Add;

	// Set the "Plus" button as selected
	m_plusXButton.ModifyStyle(0x0, BS_FLAT);
	// Force the button to repaint
	m_plusXButton.Invalidate();
	// Ensure it updates immediately
	m_plusXButton.UpdateWindow();

}*/





void TransformDialogue::OnBnClickedPlusx()
{

	DisplayObject& obj = m_displayGraph->at(*m_currentSelection);
	
	PositionData oldData = {
		obj.m_position.x, obj.m_position.y, obj.m_position.z
	};

	m_game->AddPositionX();

	PositionData newData = {
		obj.m_position.x, obj.m_position.y, obj.m_position.z
	};

	if (m_commandManager)
	{
		m_commandManager->ExecuteCommand(new MoveObjectCommand(&obj, oldData, newData));
	}

	UpdateFromSelectedObject(); // Refresh the UI
}


void TransformDialogue::OnBnClickedMinusx()
{
	DisplayObject& obj = m_displayGraph->at(*m_currentSelection);

	PositionData oldData = {
		obj.m_position.x, obj.m_position.y, obj.m_position.z
	};

	m_game->MinusPositionX();

	PositionData newData = {
		obj.m_position.x, obj.m_position.y, obj.m_position.z
	};

	if (m_commandManager)
	{
		m_commandManager->ExecuteCommand(new MoveObjectCommand(&obj, oldData, newData));
	}

	UpdateFromSelectedObject(); // Refresh the UI
}


void TransformDialogue::OnBnClickedPlusy()
{

	DisplayObject& obj = m_displayGraph->at(*m_currentSelection);

	PositionData oldData = {
		obj.m_position.x, obj.m_position.y, obj.m_position.z
	};

	m_game->AddPositionY();

	PositionData newData = {
		obj.m_position.x, obj.m_position.y, obj.m_position.z
	};

	if (m_commandManager)
	{
		m_commandManager->ExecuteCommand(new MoveObjectCommand(&obj, oldData, newData));
	}

	UpdateFromSelectedObject(); // Refresh the UI
}


void TransformDialogue::OnBnClickedMinusy()
{

	DisplayObject& obj = m_displayGraph->at(*m_currentSelection);

	PositionData oldData = {
		obj.m_position.x, obj.m_position.y, obj.m_position.z
	};

	m_game->MinusPositionY();

	PositionData newData = {
		obj.m_position.x, obj.m_position.y, obj.m_position.z
	};

	if (m_commandManager)
	{
		m_commandManager->ExecuteCommand(new MoveObjectCommand(&obj, oldData, newData));
	}

	UpdateFromSelectedObject(); // Refresh the UI
}


void TransformDialogue::OnBnClickedPlusz()
{
	DisplayObject& obj = m_displayGraph->at(*m_currentSelection);

	PositionData oldData = {
		obj.m_position.x, obj.m_position.y, obj.m_position.z
	};

	m_game->AddPositionX();

	PositionData newData = {
		obj.m_position.x, obj.m_position.y, obj.m_position.z
	};

	if (m_commandManager)
	{
		m_commandManager->ExecuteCommand(new MoveObjectCommand(&obj, oldData, newData));
	}

	UpdateFromSelectedObject(); // Refresh the UI
}


void TransformDialogue::OnBnClickedMinusz()
{
	DisplayObject& obj = m_displayGraph->at(*m_currentSelection);

	PositionData oldData = {
		obj.m_position.x, obj.m_position.y, obj.m_position.z
	};

	m_game->MinusPositionZ();

	PositionData newData = {
		obj.m_position.x, obj.m_position.y, obj.m_position.z
	};

	if (m_commandManager)
	{
		m_commandManager->ExecuteCommand(new MoveObjectCommand(&obj, oldData, newData));
	}

	UpdateFromSelectedObject(); // Refresh the UI
}
