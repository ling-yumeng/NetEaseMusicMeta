#include "main_frame.h"
#include <string.h>
#include <string>
#include "../info.h"
#include <vector>
#include "download.h"

#define debug true

#if debug
#define DBG(x) do { std::cerr << "[DEBUG] " << x << std::endl; } while(0)
#else
#define DBG(x)
#endif

MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, "Music Search", wxDefaultPosition, wxSize(600, 400)) {
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

    //运行状态
    runInfo = new wxStaticText(this, wxID_ANY, "standby.");

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
    mainSizer->Add(runInfo, 2, wxALL, 10);

    SetSizer(mainSizer);

    // ====== 事件绑定 ======
    searchBtn->Bind(wxEVT_BUTTON, [=](wxCommandEvent&) {
        //auto text = searchBox->GetValue().ToStdString();
        std::string text = searchBox->GetValue().ToUTF8().data();
        runInfo->SetLabel(wxString("Quering..."));
        querySong(text);
    });
    Bind(wxEVT_THREAD, [&](wxThreadEvent&) {
        runInfo->SetLabel(wxString("Download Finished!"));
        DBG("Download finished!");
        wxImage img("cover.jpg", wxBITMAP_TYPE_JPEG);
        cover->SetBitmap(wxBitmap(img.Scale(200, 200, wxIMAGE_QUALITY_HIGH)));
    });
}

void MainFrame::querySong(const std::string& song) {
    DBG("Quering " << song);
    info::info sngInfo;
    sngInfo.get(info::info::searchByKeywords(song.c_str()));
    DBG("Full name: " << sngInfo.name.c_str());
    nameText->SetLabel(wxString("Name: ") + wxString::FromUTF8(sngInfo.name.c_str()));
    DBG("Album name: " << sngInfo.album_name.c_str());
    albumText->SetLabel(wxString("Album: ") + wxString::FromUTF8(sngInfo.album_name.c_str()));
    std::string artists_display = "";
    for(int i = 0; i<sngInfo.artists_length; i++) {
        if(i != 0) artists_display += ", ";
        artists_display += sngInfo.artists[i];
    }
    DBG("Artists: " << artists_display);
    artistText->SetLabel(wxString("Artists: ") + wxString::FromUTF8(artists_display.c_str()));
    runInfo->SetLabel(wxString("Downloading..."));
    DBG("Downloading Cover");
    auto th = new DownloadThread(this, sngInfo.coverURL);
    th->Run();
}