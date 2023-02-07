#include <wx/wx.h>
#include "BusApp_main_window.h"

#include <pqxx/pqxx> 
#include <iostream>

#include <codecvt>
#include <locale>
#include <string>
#include <vector>

class MyApp : public wxApp {

public:

 virtual bool OnInit();
 virtual int OnExit() { 
    if(C){
        C->pqxx::connection::~connection();
        //delete C;
    }

    return 0;
    }

 protected:
 pqxx::connection* C;

};

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit() 
{
 wxFrame *mainFrame = new BusApp_main_window(NULL);
 mainFrame->Show(true);
 SetTopWindow(mainFrame);
 
try {
    C = new pqxx::connection("dbname = u0lyszczarz user = u0lyszczarz password = zzW2g2BX hostaddr = 127.0.0.1 port = 5432");

    auto* win = dynamic_cast<BusApp_main_window*>(mainFrame);
    if(win) win->setConnection(C);
    
 } catch(pqxx::pqxx_exception &e){
    wxMessageDialog dlg(mainFrame, L"Nie udało się nawiązać połączenia.", wxMessageBoxCaptionStr, wxOK|wxICON_ERROR);
        if ( dlg.ShowModal() == wxID_OK )
            return false;
}catch (const std::exception &e) {
    wxMessageDialog dlg(mainFrame, std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(e.what()), wxMessageBoxCaptionStr, wxOK|wxICON_ERROR);
        if ( dlg.ShowModal() == wxID_OK )
            return false;
 }

 try{
    if(C->is_open()){
        {
            const char* sql = "SELECT id_autobus FROM proj_mpk.autobus;";

            pqxx::nontransaction N(*C);
            pqxx::result R(N.exec(sql));

            wxString ids[R.size()];
            int i=0;
            for(auto it=R.begin(); it!=R.end(); ++it){
                ids[i++] = it[0].as<std::string>();
            }

        
            auto* win = dynamic_cast<BusApp_main_window*>(mainFrame);
            if(win) win->set_buses_list(sizeof(ids)/sizeof(wxString), ids);
        }
        
        {
            const char* sql = "SELECT numer_linii FROM proj_mpk.linia;";

            pqxx::nontransaction N(*C);
            pqxx::result R(N.exec(sql));

            wxString ids[R.size()];
            int i=0;
            for(auto it=R.begin(); it!=R.end(); ++it){
                ids[i++] = it[0].as<std::string>();
            }

        
            auto* win = dynamic_cast<BusApp_main_window*>(mainFrame);
            if(win) win->set_lines_list(sizeof(ids)/sizeof(wxString), ids);
        }

        {
            const char* sql = "SELECT nazwa, id FROM proj_mpk.przystanek;";

            pqxx::nontransaction N(*C);
            pqxx::result R(N.exec(sql));

            wxString names[R.size()];
            
            std::vector<int> ids;
            int i=0;
            for(auto it=R.begin(); it!=R.end(); ++it){
                ids.push_back(stoi(it[1].as<std::string>()));
                names[i++] = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(it[0].as<std::string>());
            }

        
            auto* win = dynamic_cast<BusApp_main_window*>(mainFrame);
            if(win)win->set_stops_list(sizeof(names)/sizeof(wxString), names, ids);
        }
    }
 } catch(std::exception &e){
    std::cerr << "Błąd zapytania.\n";
    return false;
 }

 return true;
}