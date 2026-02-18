#include <wx/wx.h>
#include <wx/process.h>
#include <wx/txtstrm.h>
#include <wx/url.h>
#include <wx/sstream.h>
#include <wx/mstream.h>
#include <string.h>
#include "info.h"

#define debug true

#if debug
#define DBG(x) do { std::cerr << "[DEBUG] " << x << std::endl; } while(0)
#else
#define DBG(x)
#endif

class MainFrame : public wxFrame {
public:
    MainFrame() : wxFrame(nullptr, wxID_ANY, "Music Search", wxDefaultPosition, wxSize(600, 400)) {

        // ====== 顶部搜索栏 ======
        auto searchBox = new wxTextCtrl(this, wxID_ANY);
        auto searchBtn = new wxButton(this, wxID_ANY, "Search");

        auto topSizer = new wxBoxSizer(wxHORIZONTAL);
        topSizer->Add(searchBox, 1, wxEXPAND | wxALL, 5);
        topSizer->Add(searchBtn, 0, wxALL, 5);

        // ====== 左侧图片 ======
        cover = new wxStaticBitmap(this, wxID_ANY, wxBitmap(200, 200));

        // ====== 右侧信息 ======
        nameText = new wxStaticText(this, wxID_ANY, "Name:");
        artistText = new wxStaticText(this, wxID_ANY, "Artists:");
        albumText = new wxStaticText(this, wxID_ANY, "Album:");

        auto infoSizer = new wxBoxSizer(wxVERTICAL);
        infoSizer->Add(nameText, 0, wxALL, 5);
        infoSizer->Add(artistText, 0, wxALL, 5);
        infoSizer->Add(albumText, 0, wxALL, 5);

        auto bottomSizer = new wxBoxSizer(wxHORIZONTAL);
        bottomSizer->Add(cover, 0, wxALL, 10);
        bottomSizer->Add(infoSizer, 1, wxEXPAND | wxALL, 10);

        // ====== 总布局 ======
        auto mainSizer = new wxBoxSizer(wxVERTICAL);
        mainSizer->Add(topSizer, 0, wxEXPAND);
        mainSizer->Add(bottomSizer, 1, wxEXPAND);

        SetSizer(mainSizer);

        // ====== 事件绑定 ======
        searchBtn->Bind(wxEVT_BUTTON, [=](wxCommandEvent&) {
            //auto text = searchBox->GetValue().ToStdString();
            std::string text = searchBox->GetValue().ToUTF8().data();
            querySong(text);
        });
    }

private:
    wxStaticBitmap* cover;
    wxStaticText* nameText;
    wxStaticText* artistText;
    wxStaticText* albumText;

    void querySong(const std::string& song) {
        DBG("Quering " << song);
        info::info sngInfo;
        sngInfo.get(info::info::searchByKeywords(song.c_str()));
        nameText->SetLabel(wxString("Name: ") + sngInfo.name);
        albumText->SetLabel(wxString("Album: ") + sngInfo.album_name);
        std::string artists_display = "";
        for(int i = 0; i<sngInfo.artists_length; i++) {
            artists_display += sngInfo.artists[i];
            artists_display += "\n";
        }
        artistText->SetLabel(wxString("Artists: ") + artists_display.c_str());
    }
};

class MyApp : public wxApp {
public:
    bool OnInit() override {
        auto frame = new MainFrame();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);