///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
///////////////////////////////////////////////////////////////////////////

#include "GUI.h"

///////////////////////////////////////////////////////////////////////////

main_window::main_window( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 600,600 ), wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );

	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _(L"Użytkownik") ), wxVERTICAL );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer121;
	bSizer121 = new wxBoxSizer( wxHORIZONTAL );

	line_txt = new wxStaticText( sbSizer3->GetStaticBox(), wxID_ANY, _("Nr linii:"), wxDefaultPosition, wxDefaultSize, 0 );
	line_txt->Wrap( -1 );
	bSizer121->Add( line_txt, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	
	line_box = new wxChoice( sbSizer3->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, line_boxChoices, 0 );
	line_box->SetSelection( 0 );
	bSizer121->Add( line_box, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer3->Add( bSizer121, 0, wxALIGN_CENTER_HORIZONTAL, 5 );

	timetable_but = new wxButton( sbSizer3->GetStaticBox(), wxID_ANY, _(L"Pokaż rozkład"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( timetable_but, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_staticline1 = new wxStaticLine( sbSizer3->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer3->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer1211;
	bSizer1211 = new wxBoxSizer( wxHORIZONTAL );

	beg_txt = new wxStaticText( sbSizer3->GetStaticBox(), wxID_ANY, _(L"Początek:"), wxDefaultPosition, wxDefaultSize, 0 );
	beg_txt->Wrap( -1 );
	bSizer1211->Add( beg_txt, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	
	beg_box = new wxChoice( sbSizer3->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, bus_stop_boxChoices, 0 );
	beg_box->SetSelection( 0 );
	bSizer1211->Add( beg_box, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer3->Add( bSizer1211, 1, wxALIGN_CENTER_HORIZONTAL, 5 );

	wxBoxSizer* bSizer12111;
	bSizer12111 = new wxBoxSizer( wxHORIZONTAL );

	end_txt = new wxStaticText( sbSizer3->GetStaticBox(), wxID_ANY, _("    Koniec:"), wxDefaultPosition, wxDefaultSize, 0 );
	end_txt->Wrap( -1 );
	bSizer12111->Add( end_txt, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	
	end_box = new wxChoice( sbSizer3->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, bus_stop_boxChoices, 0 );
	end_box->SetSelection( 0 );
	bSizer12111->Add( end_box, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer3->Add( bSizer12111, 1, wxALIGN_CENTER_HORIZONTAL, 5 );

	route_but = new wxButton( sbSizer3->GetStaticBox(), wxID_ANY, _(L"Możliwe trasy"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( route_but, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_staticline2 = new wxStaticLine( sbSizer3->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer3->Add( m_staticline2, 0, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer121111;
	bSizer121111 = new wxBoxSizer( wxHORIZONTAL );

	bus_txt = new wxStaticText( sbSizer3->GetStaticBox(), wxID_ANY, _("Nr autobusu:"), wxDefaultPosition, wxDefaultSize, 0 );
	bus_txt->Wrap( -1 );
	bSizer121111->Add( bus_txt, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	
	bus_box = new wxChoice( sbSizer3->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, bus_boxChoices, 0 );
	bus_box->SetSelection( 0 );
	bSizer121111->Add( bus_box, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer3->Add( bSizer121111, 1, wxALIGN_CENTER_HORIZONTAL, 5 );

	bus_but = new wxButton( sbSizer3->GetStaticBox(), wxID_ANY, _(L"Pokaż"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( bus_but, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_staticline3 = new wxStaticLine( sbSizer3->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer3->Add( m_staticline3, 0, wxEXPAND|wxALL, 5 );


	bSizer3->Add( 0, 15, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );

	login_txt = new wxStaticText( sbSizer3->GetStaticBox(), wxID_ANY, _("Login:"), wxDefaultPosition, wxDefaultSize, 0 );
	login_txt->Wrap( -1 );
	bSizer12->Add( login_txt, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	login_box = new wxTextCtrl( sbSizer3->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	#ifdef __WXGTK__
	if ( !login_box->HasFlag( wxTE_MULTILINE ) )
	{
	login_box->SetMaxLength( 50 );
	}
	#else
	login_box->SetMaxLength( 50 );
	#endif
	bSizer12->Add( login_box, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer3->Add( bSizer12, 0, wxALIGN_CENTER_HORIZONTAL, 5 );

	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );

	passwd_txt = new wxStaticText( sbSizer3->GetStaticBox(), wxID_ANY, _(L"Hasło:"), wxDefaultPosition, wxDefaultSize, 0 );
	passwd_txt->Wrap( -1 );
	bSizer13->Add( passwd_txt, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	passwd_box = new wxTextCtrl( sbSizer3->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD );
	bSizer13->Add( passwd_box, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer3->Add( bSizer13, 0, wxALIGN_CENTER_HORIZONTAL, 5 );


	bSizer3->Add( 0, 15, 0, wxEXPAND, 5 );

	login_but = new wxButton( sbSizer3->GetStaticBox(), wxID_ANY, _("Zaloguj"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( login_but, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );


	sbSizer3->Add( bSizer3, 1, wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );


	bSizer1->Add( sbSizer3, 1, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );

	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxVERTICAL );

	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Kierowca") ), wxHORIZONTAL );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	wxString table_print_boxChoices[] = { _("kierowca"), _("kierowca przegubowych"), _("autobus"), _("autobus przegubowy"), _("kierowca+autobus"), _("kurs"), _("linia"), _("przystanek"), _("przystanek+linia") };
	int table_print_boxNChoices = sizeof( table_print_boxChoices ) / sizeof( wxString );
	table_print_box = new wxChoice( sbSizer1->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, table_print_boxNChoices, table_print_boxChoices, 0 );
	table_print_box->SetSelection( 0 );
	table_print_box->Enable( false );

	bSizer4->Add( table_print_box, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	print_but = new wxButton( sbSizer1->GetStaticBox(), wxID_ANY, _(L"Wyświetl"), wxDefaultPosition, wxDefaultSize, 0 );
	print_but->Enable( false );

	bSizer4->Add( print_but, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );


	sbSizer1->Add( bSizer4, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer14->Add( sbSizer1, 1, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _(L"Zarząd") ), wxHORIZONTAL );

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );

	wxString table_insert_boxChoices[] = { _("kierowca"), _("autobus"), _("kierowca+autobus"), _("kurs"), _("linia"), _("przystanek"), _("przystanek+linia"), _("konto - admin"), _("konto - kierowca") };
	int table_insert_boxNChoices = sizeof( table_insert_boxChoices ) / sizeof( wxString );
	table_insert_box = new wxChoice( sbSizer2->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, table_insert_boxNChoices, table_insert_boxChoices, 0 );
	table_insert_box->SetSelection( 0 );
	table_insert_box->Enable( false );

	bSizer5->Add( table_insert_box, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	insert_but = new wxButton( sbSizer2->GetStaticBox(), wxID_ANY, _("Wstaw"), wxDefaultPosition, wxDefaultSize, 0 );
	insert_but->Enable( false );

	bSizer5->Add( insert_but, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );


	sbSizer2->Add( bSizer5, 1, wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );


	bSizer14->Add( sbSizer2, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );


	bSizer1->Add( bSizer14, 1, wxEXPAND|wxBOTTOM, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( main_window::mainOnClose ) );
	line_box->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( main_window::line_boxOnChoice ), NULL, this );
	timetable_but->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( main_window::timetable_butOnButtonClick ), NULL, this );
	beg_box->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( main_window::beg_boxOnChoice ), NULL, this );
	end_box->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( main_window::end_boxOnChoice ), NULL, this );
	route_but->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( main_window::route_butOnButtonClick ), NULL, this );
	bus_box->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( main_window::bus_boxOnChoice ), NULL, this );
	bus_but->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( main_window::bus_butOnButtonClick ), NULL, this );
	login_box->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( main_window::login_boxOnTextEnter ), NULL, this );
	passwd_box->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( main_window::passwd_boxOnTextEnter ), NULL, this );
	login_but->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( main_window::login_butOnButtonClick ), NULL, this );
	table_print_box->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( main_window::table_print_boxOnChoice ), NULL, this );
	print_but->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( main_window::print_butOnButtonClick ), NULL, this );
	table_insert_box->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( main_window::table_insert_boxOnChoice ), NULL, this );
	insert_but->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( main_window::insert_butOnButtonClick ), NULL, this );
}

main_window::~main_window()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( main_window::mainOnClose ) );
	line_box->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( main_window::line_boxOnChoice ), NULL, this );
	timetable_but->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( main_window::timetable_butOnButtonClick ), NULL, this );
	beg_box->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( main_window::beg_boxOnChoice ), NULL, this );
	end_box->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( main_window::end_boxOnChoice ), NULL, this );
	route_but->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( main_window::route_butOnButtonClick ), NULL, this );
	bus_box->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( main_window::bus_boxOnChoice ), NULL, this );
	bus_but->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( main_window::bus_butOnButtonClick ), NULL, this );
	login_box->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( main_window::login_boxOnTextEnter ), NULL, this );
	passwd_box->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( main_window::passwd_boxOnTextEnter ), NULL, this );
	login_but->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( main_window::login_butOnButtonClick ), NULL, this );
	table_print_box->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( main_window::table_print_boxOnChoice ), NULL, this );
	print_but->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( main_window::print_butOnButtonClick ), NULL, this );
	table_insert_box->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( main_window::table_insert_boxOnChoice ), NULL, this );
	insert_but->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( main_window::insert_butOnButtonClick ), NULL, this );

}

printout::printout( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 700,400 ), wxDefaultSize );

	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxVERTICAL );

	printed_table = new wxGrid( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	

	// Columns
	// printed_table->SetColSize( 0, 76 );
	// printed_table->SetColSize( 1, 80 );
	// printed_table->SetColSize( 2, 80 );
	// printed_table->SetColSize( 3, 80 );
	// printed_table->SetColSize( 4, 80 );
	// printed_table->EnableDragColMove( false );
	// printed_table->EnableDragColSize( true );
	// printed_table->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// // Rows
	// printed_table->SetRowSize( 0, 19 );
	// printed_table->SetRowSize( 1, 15 );
	// printed_table->SetRowSize( 2, 19 );
	// printed_table->SetRowSize( 3, 19 );
	// printed_table->SetRowSize( 4, 19 );
	// printed_table->EnableDragRowSize( true );
	// printed_table->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	printed_table->SetDefaultCellAlignment( wxALIGN_RIGHT, wxALIGN_TOP );
	bSizer15->Add( printed_table, 1, wxALL|wxEXPAND, 5 );


	this->SetSizer( bSizer15 );
	this->Layout();

	this->Centre( wxBOTH );
}

printout::~printout()
{
}

Insertion::Insertion( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 700,300 ), wxDefaultSize );

	wxBoxSizer* bSizer24;
	bSizer24 = new wxBoxSizer( wxVERTICAL );

	to_insert = new wxGrid( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// // Grid
	// to_insert->CreateGrid( 1, 5 );
	// to_insert->EnableEditing( true );
	// to_insert->EnableGridLines( true );
	// to_insert->EnableDragGridSize( false );
	// to_insert->SetMargins( 0, 0 );

	// // Columns
	// to_insert->SetColSize( 0, 80 );
	// to_insert->SetColSize( 1, 80 );
	// to_insert->SetColSize( 2, 80 );
	// to_insert->SetColSize( 3, 80 );
	// to_insert->SetColSize( 4, 80 );
	// to_insert->EnableDragColMove( false );
	// to_insert->EnableDragColSize( true );
	// to_insert->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// // Rows
	// to_insert->EnableDragRowSize( true );
	// to_insert->SetRowLabelValue( 0, wxEmptyString );
	// to_insert->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// // Label Appearance
	// to_insert->SetLabelFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	// Cell Defaults
	to_insert->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer24->Add( to_insert, 1, wxALL|wxEXPAND, 5 );

	save_ins_but = new wxButton( this, wxID_ANY, _(L"Zatwierdź"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer24->Add( save_ins_but, 0, wxALL|wxALIGN_RIGHT, 5 );

	save_ins_but->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Insertion::save_ins_butOnButtonClick), NULL, this );


	this->SetSizer( bSizer24 );
	this->Layout();

	this->Centre( wxBOTH );
}

Insertion::~Insertion()
{
	save_ins_but->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Insertion::save_ins_butOnButtonClick), NULL, this );
}
