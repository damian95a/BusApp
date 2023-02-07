///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/choice.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/statline.h>
#include <wx/textctrl.h>
#include <wx/statbox.h>
#include <wx/frame.h>
#include <wx/grid.h>

///////////////////////////////////////////////////////////////////////////
#include <vector>

///////////////////////////////////////////////////////////////////////////////
/// Class main_window
///////////////////////////////////////////////////////////////////////////////
class main_window : public wxFrame
{
	private:

	protected:
		wxStaticText* line_txt;
		wxChoice* line_box;
		wxButton* timetable_but;
		wxStaticLine* m_staticline1;
		wxStaticText* beg_txt;
		wxChoice* beg_box;
		wxStaticText* end_txt;
		wxChoice* end_box;
		wxButton* route_but;
		wxStaticLine* m_staticline2;
		wxStaticText* bus_txt;
		wxChoice* bus_box;
		wxButton* bus_but;
		wxStaticLine* m_staticline3;
		wxStaticText* login_txt;
		wxTextCtrl* login_box;
		wxStaticText* passwd_txt;
		wxTextCtrl* passwd_box;
		wxButton* login_but;
		wxChoice* table_print_box;
		wxButton* print_but;
		wxButton* insert_but;

		// Virtual event handlers, override them in your derived class
		virtual void mainOnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void line_boxOnChoice( wxCommandEvent& event ) { event.Skip(); }
		virtual void timetable_butOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void beg_boxOnChoice( wxCommandEvent& event ) { event.Skip(); }
		virtual void end_boxOnChoice( wxCommandEvent& event ) { event.Skip(); }
		virtual void route_butOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void bus_boxOnChoice( wxCommandEvent& event ) { event.Skip(); }
		virtual void bus_butOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void login_boxOnTextEnter( wxCommandEvent& event ) { event.Skip(); }
		virtual void passwd_boxOnTextEnter( wxCommandEvent& event ) { event.Skip(); }
		virtual void login_butOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void table_print_boxOnChoice( wxCommandEvent& event ) { event.Skip(); }
		virtual void print_butOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void table_insert_boxOnChoice( wxCommandEvent& event ) { event.Skip(); }
		virtual void insert_butOnButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		wxChoice* table_insert_box;

		main_window( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Autobusy"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 600,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~main_window();

	protected:
	wxArrayString line_boxChoices;
	wxArrayString bus_stop_boxChoices;
	wxArrayString bus_boxChoices;
	std::vector<int> bus_stop_ids;
};

///////////////////////////////////////////////////////////////////////////////
/// Class printout
///////////////////////////////////////////////////////////////////////////////
class printout : public wxFrame
{
	private:

	public:
		wxGrid* printed_table;

	

		printout( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _(L"Przegląd"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 700,400 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~printout();

};

///////////////////////////////////////////////////////////////////////////////
/// Class Insertion
///////////////////////////////////////////////////////////////////////////////
class Insertion : public wxFrame
{
	private:

	protected:

	public:

		Insertion( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Wprowadzanie"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 700,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		virtual void save_ins_butOnButtonClick( wxCommandEvent& event ) { event.Skip(); }

		~Insertion();


		wxFrame* par;
		wxGrid* to_insert;
		wxButton* save_ins_but;

};

