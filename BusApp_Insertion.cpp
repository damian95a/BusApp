#include "BusApp_Insertion.h"
#include "BusApp_main_window.h"
#include "query.h"
#include <wx/wx.h>

#include <codecvt>
#include <locale>
#include <string>

BusApp_Insertion::BusApp_Insertion( wxWindow* parent )
:
Insertion( parent )
{
    par=dynamic_cast<wxFrame*>(parent);
}

void BusApp_Insertion::save_ins_butOnButtonClick( wxCommandEvent& event ){
    auto win = dynamic_cast<BusApp_main_window*>(par);
    try{
        insert_table(win->table_insert_box->GetSelection(), win->C, this);

        wxMessageDialog dlg(this, "Zapisano zmiany.", wxMessageBoxCaptionStr, wxOK);
        dlg.ShowModal();
    } catch(std::exception &e){
        wxMessageDialog dlg(this, std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(e.what()), wxMessageBoxCaptionStr, wxOK|wxICON_ERROR);
        dlg.ShowModal();
    }
}