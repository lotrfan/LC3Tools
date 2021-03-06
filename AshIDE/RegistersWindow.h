//	Copyright 2003 Ashley Wise
//	University Of Illinois Urbana-Champaign
//	awise@crhc.uiuc.edu

#ifndef REGISTERSWINDOW_H
#define REGISTERSWINDOW_H

#pragma warning (disable:4786)
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Choice.H>
#include <string>
#include <list>
#include "ReadOnlyEditor.h"

using namespace std;

namespace AshIDE
{
	class RegistersWindow : public Fl_Double_Window
	{
	protected:
		friend class SimulatorWindow;

		//Widgets for main menu
		Fl_Menu_Bar *pMainMenu;
		static Fl_Menu_Item MenuItems[];

		//Widgets for the address query
		Fl_Choice *pRegisterSet, *pRegister;

		//Widgets for Registers view
		ReadOnlyEditor *pTextDisplay;

		//Widgets for the register list dialog
		Fl_Window *pRegisterDlg;
		//*NOTE: a feature in FLTK widgets (or at least Fl_Box) is that the char * passed to
		//the constructor as a title is stored directoy as a pointer, and is not copied.
		//So I need to keep the titles I generate around permanently.
		list<string> sRegisterText;

		//Stuff for syntax highlighting
		static Fl_Text_Display::Style_Table_Entry StyleTable[];

		//Widgets for the status bar
		Fl_Output *pStatus;

	public:
		/**********************************************************************\
			RegistersWindow( )

			Constructs the Registers window.
			This window only displays text, there is no editing.
		\******/
		RegistersWindow();

		/**********************************************************************\
			~RegistersWindow( )

			Destructor
		\******/
		virtual ~RegistersWindow();



		
	//*** Window Management Functions ***//
		static void HelpCB(Fl_Widget *pW, void *pV);

		/**********************************************************************\
			Close( )

			Closes the window and removes it from the SimulatorWindow's list.
		\******/
		static void CloseCB(Fl_Widget *pW, void *pV)	{	((RegistersWindow *)pV)->Close();	}
		bool Close();

		/**********************************************************************\
			SetTitle( )

			Sets the title.
		\******/
		bool SetTitle();



	//*** Registers Management Functions ***//
		static void ListCB(Fl_Widget *pW, void *pV)	{	((RegistersWindow *)pV)->List();	}
		bool List();
		static void SaveCB(Fl_Widget *pW, void *pV)	{	((RegistersWindow *)pV)->pTextDisplay->Save();	}
		static void CopyCB(Fl_Widget *pW, void *pV)	{	((RegistersWindow *)pV)->pTextDisplay->Copy();	}
		static void FindCB(Fl_Widget *pW, void *pV)	{	((RegistersWindow *)pV)->pTextDisplay->Find();	}
		static void FindAgainCB(Fl_Widget *pW, void *pV)	{	((RegistersWindow *)pV)->pTextDisplay->FindAgain();	}

		/**********************************************************************\
			ChangeRegisterSet( )

			Changes whether it's displaying logical data or physical memory
			bytes.
		\******/
		static void ChangeRegisterSetCB(Fl_Widget *pW, void *pV)	{	((RegistersWindow *)pV)->ChangeRegisterSet();	}
		bool ChangeRegisterSet();

		/**********************************************************************\
			Enter( )

			Displays the data per the parameters.
		\******/
		static void EnterCB(Fl_Widget *pW, void *pV)	{	((RegistersWindow *)pV)->Enter();	}
		bool Enter();

		/**********************************************************************\
			ViewRegister( [in] register )

			Displays the specified register.
		\******/
		bool ViewRegister(const string &);



	//*** Style Management Functions ***//
		/**********************************************************************\
			UpdateStyle( )

			Called when the text changes. Updates the syntax highlighting
			of the changed text.
		\******/
		static void UpdateStyleCB(int Pos, int nInserted, int nDeleted, int nRestyled, const char *pszDeleted, void *pV)
			{	((RegistersWindow *)pV)->UpdateStyle(Pos, nInserted, nDeleted, nRestyled, pszDeleted);	}
		bool UpdateStyle(int, int, int, int, const char *);

		/**********************************************************************\
			ParseStyle( [in] updated text, [out] updated style )

			Parses the updated text and updates the style of that text
			character by character.
		\******/
		virtual bool ParseStyle(const string &, string &);
	};
}

#endif
