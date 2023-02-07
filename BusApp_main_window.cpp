#include "BusApp_main_window.h"
#include "BusApp_printout.h"
#include "BusApp_Insertion.h"

#include <wx/wx.h>
#include "query.h"

#include <string>
#include <sstream>
#include <codecvt>
#include <locale>


BusApp_main_window::BusApp_main_window( wxWindow* parent )
:
main_window( parent )
{

}

void BusApp_main_window::mainOnClose( wxCloseEvent& event )
{
event.Skip();
}

void BusApp_main_window::line_boxOnChoice( wxCommandEvent& event )
{
    
}

void BusApp_main_window::timetable_butOnButtonClick( wxCommandEvent& event )
{
    if(line_box->GetSelection() == wxNOT_FOUND){
        wxMessageDialog dlg(this, "Nie wybrano numeru linii.", wxMessageBoxCaptionStr, wxOK|wxICON_ERROR);
        dlg.ShowModal();
    } else {
        
        printout *viewFrame = new BusApp_printout(this);
        

        timetable_q(
            std::stoi(line_boxChoices[line_box->GetSelection()].ToStdString()),
            C,
            viewFrame);


        viewFrame->Show(true);
    }
}

void BusApp_main_window::beg_boxOnChoice( wxCommandEvent& event )
{
// TODO: Implement beg_boxOnChoice
}

void BusApp_main_window::end_boxOnChoice( wxCommandEvent& event )
{
// TODO: Implement end_boxOnChoice
}

void BusApp_main_window::route_butOnButtonClick( wxCommandEvent& event )
{
    if(beg_box->GetSelection() == wxNOT_FOUND){
        wxMessageDialog dlg(this, L"Nie wybrano przystanku początkowego.", wxMessageBoxCaptionStr, wxOK|wxICON_ERROR);
        dlg.ShowModal();
    } else if(end_box->GetSelection() == wxNOT_FOUND){
        wxMessageDialog dlg(this, L"Nie wybrano przystanku końcowego.", wxMessageBoxCaptionStr, wxOK|wxICON_ERROR);
        dlg.ShowModal();
    } else {
        
        printout *viewFrame = new BusApp_printout(this);
        
        int idp=bus_stop_ids[beg_box->GetSelection()];
        int ide=bus_stop_ids[end_box->GetSelection()];

        if(ide==idp){
            wxMessageDialog dlg(this, L"Przystanki muszą być różne.", wxMessageBoxCaptionStr, wxOK|wxICON_ERROR);
        if ( dlg.ShowModal() == wxID_OK )
            return;
        }

        route_q(idp,ide,C,viewFrame);


        viewFrame->Show(true);
    }
}

void BusApp_main_window::bus_boxOnChoice( wxCommandEvent& event )
{
// TODO: Implement bus_boxOnChoice
}

void BusApp_main_window::bus_butOnButtonClick( wxCommandEvent& event )
{
    if(bus_box->GetSelection() == wxNOT_FOUND){
        wxMessageDialog dlg(this, "Nie wybrano numeru autobusu.", wxMessageBoxCaptionStr, wxOK|wxICON_ERROR);
        dlg.ShowModal();
    } else {
        
        printout *viewFrame = new BusApp_printout(this);
        

        bus_q(
            std::stoi(bus_boxChoices[bus_box->GetSelection()].ToStdString()),
            C,
            viewFrame);


        viewFrame->Show(true);
    }
}

void BusApp_main_window::login_boxOnTextEnter( wxCommandEvent& event )
{
// TODO: Implement login_boxOnTextEnter
}

void BusApp_main_window::passwd_boxOnTextEnter( wxCommandEvent& event )
{
// TODO: Implement passwd_boxOnTextEnter
}

void BusApp_main_window::login_butOnButtonClick( wxCommandEvent& event )
{
    if(loggedin){
        insert_but->Disable();
        print_but->Disable();
        table_insert_box->Disable();
        table_print_box->Disable();

        login_box->Enable();
        passwd_box->Enable();

        login_but->SetLabel("Zaloguj");
        loggedin=false;
    } else {
        std::stringstream sql1;
        sql1 << "SELECT COUNT(*) FROM logowanie.kierowca WHERE login='"
        << login_box->GetLineText(0) << "' AND haslo='" << passwd_box->GetLineText(0) << "' GROUP BY login, haslo;";

        std::stringstream sql2;
        sql2 << "SELECT COUNT(*) FROM logowanie.czlonek_zarzadu WHERE login='"
        << login_box->GetLineText(0) << "' AND haslo='" << passwd_box->GetLineText(0) << "' GROUP BY login, haslo;";

        pqxx::nontransaction N1(*C);
        pqxx::result R1(N1.exec(sql1.str()));
        pqxx::result R2(N1.exec(sql2.str()));

        if(R2.size() > 0 && R2.begin()[0].as<int>() > 0){
            insert_but->Enable();
            print_but->Enable();
            table_insert_box->Enable();
            table_print_box->Enable();

            login_box->Clear();
            login_box->Disable();
            passwd_box->Clear();
            passwd_box->Disable();

            login_but->SetLabel("Wyloguj");
            loggedin=true;
        } 
        else if(R1.size() > 0 && R1.begin()[0].as<int>() > 0){
            print_but->Enable();
            table_print_box->Enable();

            login_box->Clear();
            login_box->Disable();
            passwd_box->Clear();
            passwd_box->Disable();

            login_but->SetLabel("Wyloguj");
            loggedin=true;
        } else {
            wxMessageDialog dlg(this, L"Błędne dane logowania.", wxMessageBoxCaptionStr, wxOK|wxICON_ERROR);
            dlg.ShowModal();
        }
    }
}

void BusApp_main_window::table_print_boxOnChoice( wxCommandEvent& event )
{
// TODO: Implement table_print_boxOnChoice
}

void BusApp_main_window::print_butOnButtonClick( wxCommandEvent& event )
{
    if(table_print_box->GetSelection() == wxNOT_FOUND){
        wxMessageDialog dlg(this, "Nie wybrano tabeli.", wxMessageBoxCaptionStr, wxOK|wxICON_ERROR);
        dlg.ShowModal();
    } else {
        
        printout *viewFrame = new BusApp_printout(this);
        

        show_table_q(
            table_print_box->GetSelection(),
            C,
            viewFrame);


        viewFrame->Show(true);
    }
}

void BusApp_main_window::table_insert_boxOnChoice( wxCommandEvent& event )
{
// TODO: Implement table_insert_boxOnChoice
}

void BusApp_main_window::insert_butOnButtonClick( wxCommandEvent& event )
{
    int col_n;
    std::vector<std::wstring> labels;
    int id = table_insert_box->GetSelection();

    switch(id){
        case 0:
            labels={L"id", L"imie", L"nazwisko", L"uprawnienia przegubowe"};
            break;
        case 1:
            labels={L"id", L"liczba miejsc", L"przegubowy", L"napęd"};
            break;
        case 2:
            labels={L"id kierowcy", L"id autobusu"};
            break;
        case 3:
            labels={L"id kierowca-autobus", L"godzina odjazdu", L"numer linii", L"kierunek powrotny"};
            break;
        case 4:
            labels={L"numer linii", L"kierunek1", L"kierunek2"};
            break;
        case 5:
            labels={L"nazwa"};
            break;
        case 6:
            labels={L"id przystanku", L"numer linii", L"czas dojazdu", L"kolejnosc"};
            break;
        case 7:
        case 8:
            labels={L"login", L"hasło"};
            break;
    }

    col_n = labels.size();

    Insertion *inFrame = new BusApp_Insertion(this);

    // Grid
    inFrame->to_insert->CreateGrid( 1, col_n );
    inFrame->to_insert->SetRowSize(0,25);
    for(int i=0; i<col_n; ++i) inFrame->to_insert->SetColSize(i,150);
    inFrame->to_insert->EnableEditing( true );
	inFrame->to_insert->EnableGridLines( true );
	inFrame->to_insert->EnableDragGridSize( false );
	inFrame->to_insert->SetMargins( 0, 0 );
    for(int i=0; i<col_n; ++i) inFrame->to_insert->SetColLabelValue(i,labels[i]);

    inFrame->Show(true);
}

void BusApp_main_window::set_lines_list(size_t s, wxString* lst){
    line_boxChoices = wxArrayString(s, lst);
    line_box->Set(line_boxChoices);
}

void BusApp_main_window::set_stops_list(size_t s, wxString* lst, std::vector<int> &ids){
    bus_stop_boxChoices = wxArrayString(s, lst);
    bus_stop_ids=ids;
    beg_box->Set(bus_stop_boxChoices);
    end_box->Set(bus_stop_boxChoices);
}

void BusApp_main_window::set_buses_list(size_t s, wxString* lst){
    bus_boxChoices = wxArrayString(s, lst);
    bus_box->Set(bus_boxChoices);
}

void BusApp_main_window::add_line(wxString str){
    line_boxChoices.Add(str);
    line_box->Append(str);
}

void BusApp_main_window::add_stop(wxString str, int id){
    bus_stop_boxChoices.Add(str);
    bus_stop_ids.push_back(id);
    beg_box->Append(str);
    end_box->Append(str);
}

void BusApp_main_window::add_bus(wxString str){
    bus_boxChoices.Add(str);
    bus_box->Append(str);
}