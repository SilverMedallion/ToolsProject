#pragma once
#include "afxdialogex.h"
#include "resource.h"
#include "afxwin.h"
#include "SceneObject.h"
#include "DisplayObject.h"
#include <vector>
#include "CommandManager.h"



class MFCMain;
class Game;



	class TransformDialogue : public CDialogEx
	{
		DECLARE_DYNAMIC(TransformDialogue)
	public:
		TransformDialogue(CWnd* pParent = nullptr);
		virtual ~TransformDialogue();

		void SetMain(MFCMain* main);
		void SetGame(Game* game);


		//set selected object in scene graph 
		inline void SetSelection(int selection) { m_selectedIndex = selection; }
		
		//populate vector of display objects
		void SetDisplayGraph(std::vector<DisplayObject>* displayGraph);

		inline void SetCommandManager(CommandManager* commandManager) { m_commandManager = commandManager; }

		void UpdateFromSelectedObject();
		
		void InitialiseWithSelection();

		void OnUndo();

		void OnRedo();

		afx_msg void End(); //kill dialogue box

		void OnClose();


		BOOL PreTranslateMessage(MSG* pMsg);


#ifdef AFX_DESIGN_TIME
		enum { IDD = IDD_TRANSFORM_DIALOG };
#endif 

	protected: 
		virtual void DoDataExchange(CDataExchange* pDX);
		virtual BOOL OnInitDialogue();

		MFCMain* Main;

		CommandManager* m_commandManager;



	private: 
		//vector of objects in the scene
		std::vector<DisplayObject>* m_displayGraph = nullptr;
		int m_selectedIndex = -1;
		int* m_currentSelection = &m_selectedIndex;
		//pointer to the game object
		Game* m_game = nullptr;

		//position 
		CEdit m_posX, m_posY, m_posZ;

		
		//buttons
		CButton m_plusXButton;
		CButton m_minusXButton;
		CButton m_plusYButton;
		CButton m_minusYButton;
		CButton m_plusZButton;
		CButton m_minusZButton;


		
		//event handlers
		afx_msg void OnChangePosition();
		afx_msg void OnIncrement(UINT nID); //all increment buttons share on handler
		void ApplyChangesToObject();

		void UpdateEditFields();

	public:
		DECLARE_MESSAGE_MAP()

		afx_msg void OnBnClickedPlusx();
		afx_msg void OnBnClickedButton5();
		afx_msg void OnBnClickedMinusx();
		afx_msg void OnBnClickedPlusy();
		afx_msg void OnBnClickedMinusy();
		afx_msg void OnBnClickedPlusz();
		afx_msg void OnBnClickedMinusz();
};


