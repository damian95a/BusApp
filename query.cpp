#include "query.h"
#include "BusApp_main_window.h"

void route_q(int id1, int id2, pqxx::connection *C, printout* f){
    std::stringstream sql;
    sql << "SELECT * FROM proj_mpk.trasa(" << id1 <<", "<< id2 <<");";
    
    pqxx::nontransaction N(*C);
    pqxx::result R(N.exec(sql.str()));

    int row_n = R.size();
    int col_n = 5;

    // Grid
    f->printed_table->CreateGrid( row_n, col_n );
    for(int i=0; i<row_n; ++i) f->printed_table->SetRowSize(i,19);
    for(int i=0; i<col_n; ++i) f->printed_table->SetColSize(i,150);
    f->printed_table->EnableEditing( false );
    f->printed_table->EnableGridLines( true );
    f->printed_table->EnableDragGridSize( false );
    f->printed_table->SetMargins( 0, 0 );

    std::string labels[] = {"numer autobusu", "numer kursu", "numer linii", "przystanek pocz.", "przystanek docel."};
    for(int i=0; i<col_n; ++i){
        f->printed_table->SetColLabelValue(i,labels[i]);
        for(int j=0; j<row_n; ++j){
            std::wstring s;
            s=std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes((R.begin()+j)[i].as<std::string>());
            f->printed_table->SetCellValue(j,i, s); 
        }
    }
}

void bus_q(int id, pqxx::connection *C, printout* f){
    std::stringstream sql;
    sql << "SELECT id_autobus, pojemnosc, przegubowy, naped FROM proj_mpk.autobus WHERE id_autobus = " << id << ";";

    pqxx::nontransaction N(*C);
    pqxx::result R(N.exec(sql.str()));

    int row_n = 1;
    int col_n = 4;

    // Grid
    f->printed_table->CreateGrid( row_n, col_n );
    for(int i=0; i<row_n; ++i) f->printed_table->SetRowSize(i,19);
    for(int i=0; i<col_n; ++i) f->printed_table->SetColSize(i,150);
    f->printed_table->EnableEditing( false );
    f->printed_table->EnableGridLines( true );
    f->printed_table->EnableDragGridSize( false );
    f->printed_table->SetMargins( 0, 0 );

    std::string labels[] = {"numer autobusu", "liczba miejsc", "przegubowy", "naped"};
    for(int i=0; i<col_n; ++i){
        f->printed_table->SetColLabelValue(i,labels[i]);
        std::string s;
        if(i==2) s=R.begin()[i].as<bool>() ? "TAK" : "NIE";
        else s=R.begin()[i].as<std::string>();
        f->printed_table->SetCellValue(0,i, s); 
    }
}

void timetable_q(int linia, pqxx::connection *C, printout* f){
    std::stringstream sql1;
    sql1 << "SELECT id_autobus, nazwa, proj_mpk.czas_jazdy(kolejnosc, godzina_odjazd, " << linia << ") "
    << "FROM proj_mpk.kurs K JOIN proj_mpk.linia L USING(numer_linii) "
    << "JOIN proj_mpk.przystanek_linia PL USING(numer_linii) "
    << "JOIN proj_mpk.przystanek P ON P.id=PL.id_przystanek "
    << "JOIN proj_mpk.kierowca_autobus KA ON KA.id=K.id_kierowca_autobus "
    << "WHERE K.numer_linii=" << linia << " AND K.powrot='false' "
    << "ORDER BY 1,3;";


    std::stringstream sql2;
    sql2 << "SELECT id_autobus, nazwa, proj_mpk.czas_jazdy_powrot(kolejnosc, godzina_odjazd, " << linia << ") "
    << "FROM proj_mpk.kurs K JOIN proj_mpk.linia L USING(numer_linii) "
    << "JOIN proj_mpk.przystanek_linia PL USING(numer_linii) "
    << "JOIN proj_mpk.przystanek P ON P.id=PL.id_przystanek "
    << "JOIN proj_mpk.kierowca_autobus KA ON KA.id=K.id_kierowca_autobus "
    << "WHERE K.numer_linii=" << linia << " AND K.powrot='true' "
    << "ORDER BY 1,3;";


    pqxx::nontransaction N1(*C);
    pqxx::result R1(N1.exec(sql1.str()));

    pqxx::result R2(N1.exec(sql2.str()));

    int row_n = std::max(R1.size(), R2.size());
    int col_n = 6;

    // Grid
    f->printed_table->CreateGrid( row_n, col_n );
    for(int i=0; i<row_n; ++i) f->printed_table->SetRowSize(i,19);
    for(int i=0; i<col_n; ++i) f->printed_table->SetColSize(i,150);
    f->printed_table->EnableEditing( false );
    f->printed_table->EnableGridLines( true );
    f->printed_table->EnableDragGridSize( false );
    f->printed_table->SetMargins( 0, 0 );


    std::string labels[] = {"numer autobusu", "przystanek", "godz. odjazdu"};
    for(int i=0; i<col_n/2; ++i){
        f->printed_table->SetColLabelValue(i,labels[i]);
        f->printed_table->SetColLabelValue(3+i,labels[i]);
    }


    for(int i=0; i<(int)R1.size(); ++i){
        for(int j=0; j<col_n/2; ++j){
            std::string s;
            s=(R1.begin()+i)[j].as<std::string>();
            f->printed_table->SetCellValue(i,j, s); 
        }
    }

    for(int i=0; i<(int)R2.size(); ++i){
        for(int j=0; j<col_n/2; ++j){
            std::string s;
            s=(R2.begin()+i)[j].as<std::string>();
            f->printed_table->SetCellValue(i,3+j, s); 
        }
    }
}


void show_table_q(const int idx, pqxx::connection *C, printout* f){
    std::string sql;
    std::vector<std::wstring> labels;
    int bool_poz[]={-1,-1};

    switch(idx){
        case 0:
            sql="SELECT * FROM proj_mpk.kierowca;";
            labels={L"numer id", L"imie", L"nazwisko", L"uprawnienia przegubowe"};
            bool_poz[0]=3;
            break;
        case 1:
            sql="SELECT * FROM proj_mpk.kierowca WHERE uprawnienia_przegubowe='true';";
            labels={L"numer id", L"imie", L"nazwisko"};
            break;
        case 2:
            sql="SELECT * FROM proj_mpk.autobus;";
            labels={L"numer autobusu", L"liczba miejsc", L"przegubowy", L"napęd"};
            bool_poz[0]=2;
            break;
        case 3:
            sql="SELECT id_autobus, pojemnosc, naped FROM proj_mpk.autobus WHERE przegubowy='true';";
            labels={L"numer autobusu", L"liczba miejsc", L"napęd"};
            break;
        case 4:
            sql="SELECT KA.id, K.*, A.* FROM proj_mpk.kierowca K "
            "JOIN proj_mpk.kierowca_autobus KA ON KA.id_kierowca=K.id "
            "JOIN proj_mpk.autobus A USING(id_autobus);";

            labels={L"id kierowca-autobus", L"numer id kierowcy", L"imie", L"nazwisko", L"uprawniania przegubowe", L"nr autobusu", L"liczba miejsc", L"przegubowy", L"napęd"};
            bool_poz[0] = 4;
            bool_poz[1] = 7;
            break;
        case 5:
            sql="SELECT K.*, CASE WHEN K.powrot THEN L.kierunek_powrotny ELSE L.kierunek END "
            "FROM proj_mpk.kurs K JOIN proj_mpk.linia L USING(numer_linii); "
            "SELECT K.id_kurs, K.id_kierowca_autobus, K.godzina_odjazd, K.godzina_przyjazd, K.numer_linii, CASE WHEN K.powrot THEN L.kierunek_powrotny ELSE L.kierunek END "
            "FROM proj_mpk.kurs K JOIN proj_mpk.linia L USING(numer_linii);";

            labels={L"numer kursu", L"id kierowca-autobus", L"godzina odjazdu", L"godzina przyjazdu", L"nr linii", L"kierunek"};
            break;
        case 6:
            sql="SELECT * FROM proj_mpk.linia;";
            labels={L"nr linii", L"kierunek1", L"kierunek2"};
            break;
        case 7:
            sql="SELECT * FROM proj_mpk.przystanek;";
            labels={L"numer przystanku", L"nazwa"};
            break;
        case 8:
            sql="SELECT P.*, L.* FROM proj_mpk.linia L "
            "JOIN proj_mpk.przystanek_linia PL USING(numer_linii) "
            "JOIN proj_mpk.przystanek P ON PL.id_przystanek=P.id;";
            
            labels={L"numer przystanku", L"nazwa", L"nr linii", L"kierunek1", L"kierunek2"};
            break;
    }

    pqxx::nontransaction N(*C);
    pqxx::result R(N.exec(sql));

    int row_n = R.size();
    int col_n = labels.size();

    // Grid
    f->printed_table->CreateGrid( row_n, col_n );
    for(int i=0; i<row_n; ++i) f->printed_table->SetRowSize(i,19);
    for(int i=0; i<col_n; ++i) f->printed_table->SetColSize(i,150);
    f->printed_table->EnableEditing( false );
    f->printed_table->EnableGridLines( true );
    f->printed_table->EnableDragGridSize( false );
    f->printed_table->SetMargins( 0, 0 );

    for(int i=0; i<col_n; ++i){
        f->printed_table->SetColLabelValue(i,labels[i]);
        for(int j=0; j<row_n; ++j){
            std::wstring s;
            if(i==bool_poz[0] || i==bool_poz[1]) s=(R.begin()+j)[i].as<bool>() ? L"TAK" : L"NIE";
            else s=std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes((R.begin()+j)[i].as<std::string>());
            f->printed_table->SetCellValue(j,i, s); 
        }
    }
}

void insert_table(int id, pqxx::connection *C, Insertion* f){
    pqxx::work trans(*C);
    std::string przeg;
    pqxx::result R;
    C->unprepare("insertion");

    switch(id){
        case 0:
            przeg = f->to_insert->GetCellValue(0,3).ToStdString();
            if(przeg=="TAK" || przeg=="tak") przeg="true";
            else if(przeg=="NIE" || przeg=="nie") przeg="false";

            C->prepare("insertion", "INSERT INTO proj_mpk.kierowca (id, imie, nazwisko, uprawnienia_przegubowe) VALUES ($1, $2, $3, $4);");
            R = trans.exec_prepared("insertion",
                f->to_insert->GetCellValue(0,0).ToStdString(),
                std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(f->to_insert->GetCellValue(0,1).ToStdWstring()),
                std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(f->to_insert->GetCellValue(0,2).ToStdWstring()),
                przeg
                );
            break;
        case 1:
            przeg = f->to_insert->GetCellValue(0,2).ToStdString();
            if(przeg=="TAK" || przeg=="tak") przeg="true";
            else if(przeg=="NIE" || przeg=="nie") przeg="false";

            C->prepare("insertion", "INSERT INTO proj_mpk.autobus (id_autobus, pojemnosc, przegubowy, naped) VALUES ($1, $2, $3, $4);");
            R = trans.exec_prepared("insertion",
                f->to_insert->GetCellValue(0,0).ToStdString(),
                f->to_insert->GetCellValue(0,1).ToStdString(),
                przeg,
                f->to_insert->GetCellValue(0,3).ToStdString()
                );
            break;
        case 2:
            C->prepare("insertion", "INSERT INTO proj_mpk.kierowca_autobus (id_kierowca, id_autobus) VALUES ($1, $2);");
            R = trans.exec_prepared("insertion",
                f->to_insert->GetCellValue(0,0).ToStdString(),
                f->to_insert->GetCellValue(0,1).ToStdString()
                );
            break;
        case 3:
            przeg = f->to_insert->GetCellValue(0,3).ToStdString();
            if(przeg=="TAK" || przeg=="tak") przeg="true";
            else if(przeg=="NIE" || przeg=="nie") przeg="false";

            C->prepare("insertion", "INSERT INTO proj_mpk.kurs (id_kierowca_autobus, godzina_odjazd, numer_linii, powrot) VALUES ($1, $2, $3, $4);");
            R = trans.exec_prepared("insertion",
                f->to_insert->GetCellValue(0,0).ToStdString(),
                f->to_insert->GetCellValue(0,1).ToStdString(),
                f->to_insert->GetCellValue(0,2).ToStdString(),
                przeg
                );
            break;
        case 4:
            C->prepare("insertion", "INSERT INTO proj_mpk.linia (numer_linii, kierunek, kierunek_powrotny) VALUES ($1, $2, $3);");
            R = trans.exec_prepared("insertion",
                f->to_insert->GetCellValue(0,0).ToStdString(),
                std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(f->to_insert->GetCellValue(0,1).ToStdWstring()),
                std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(f->to_insert->GetCellValue(0,2).ToStdWstring())
                );
            break;
        case 5:
            C->prepare("insertion", "INSERT INTO proj_mpk.przystanek (nazwa) VALUES ($1);");
            R = trans.exec_prepared("insertion",
                std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(f->to_insert->GetCellValue(0,0).ToStdWstring())
                );
            break;
        case 6:
            C->prepare("insertion", "INSERT INTO proj_mpk.przystanek_linia (id_przystanek, numer_linii, czas_dojazdu, kolejnosc) VALUES ($1, $2, $3, $4);");
            R = trans.exec_prepared("insertion",
                f->to_insert->GetCellValue(0,0).ToStdString(),
                f->to_insert->GetCellValue(0,1).ToStdString(),
                f->to_insert->GetCellValue(0,2).ToStdString(),
                f->to_insert->GetCellValue(0,3).ToStdString()
                );
            break;
        case 7:
            C->prepare("insertion", "INSERT INTO logowanie.czlonek_zarzadu (login, haslo) VALUES ($1, $2);");
            R = trans.exec_prepared("insertion",
                f->to_insert->GetCellValue(0,0).ToStdString(),
                f->to_insert->GetCellValue(0,1).ToStdString()
                );
                std::cout << f->to_insert->GetCellValue(0,0).ToStdString() << std::endl;
            break;
        case 8:
            C->prepare("insertion", "INSERT INTO logowanie.kierowca (login, haslo) VALUES ($1, $2);");
            R = trans.exec_prepared("insertion",
                f->to_insert->GetCellValue(0,0).ToStdString(),
                f->to_insert->GetCellValue(0,1).ToStdString()
                );
            break;
    }

    trans.commit();
    //std::cout << R.begin()[0].as<std::string>() << std::endl;

    auto win = dynamic_cast<BusApp_main_window*>(f->par);
    switch(id){
        case 1:
            win->add_bus(f->to_insert->GetCellValue(0,0).ToStdString());
            break;
        case 4:
            win->add_line(f->to_insert->GetCellValue(0,0).ToStdString());
            break;
        case 5:
            pqxx::nontransaction N(*C);
            pqxx::result R1(N.exec("SELECT MAX(id) FROM proj_mpk.przystanek;"));

            win->add_stop(
                        wxString(f->to_insert->GetCellValue(0,0).ToStdWstring()),
                        R1.begin()[0].as<int>()
                        );
            break;

    }
}
