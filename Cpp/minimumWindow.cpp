#include <wx/wx.h>
#include <wx/process.h>
#include <wx/txtstrm.h>
#include <wx/url.h>
#include <wx/sstream.h>
#include <wx/mstream.h>
#include <wx/imagpng.h>
#include <string.h>
#include <string>
#include "info.h"
#include <vector>

#define debug true

#if debug
#define DBG(x) do { std::cerr << "[DEBUG] " << x << std::endl; } while(0)
#else
#define DBG(x)
#endif

class MainFrame;

class DownloadThread : public wxThread {
    public:
    DownloadThread(MainFrame* frame, std::string url)
        : wxThread(wxTHREAD_DETACHED), frame(frame), url(url) {}

    protected:
    ExitCode Entry() override;

    private:
    MainFrame* frame;
    std::string url;
};


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

private:
    wxStaticBitmap* cover;
    wxStaticText* nameText;
    wxStaticText* artistText;
    wxStaticText* albumText;
    wxStaticText* runInfo;

    void querySong(const std::string& song) {
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
        //runInfo->SetLabel(wxString("standby."));
    }
};

wxThread::ExitCode DownloadThread::Entry()  {
    /*aria2::libraryInit();
    aria2::SessionConfig config;
    aria2::KeyVals options;
    aria2::KeyVals sessionOptions;
    //sessionOptions.emplace_back("dir", ".");
    options.push_back({"dir", "."});
    aria2::Session* session = aria2::sessionNew(sessionOptions, config);
    if(!session) {
        std::cerr << "Failed to create session" << std::endl;
        return (wxThread::ExitCode)1;
    }
    std::vector<std::string> uris = { url };
    DBG("Cover URL: " << url);
    aria2::A2Gid gid = aria2::addUri(session, nullptr, uris, options);
    if(!gid) {
        std::cerr << "Fail to add download" << std::endl;
        return (wxThread::ExitCode)1;
    }
    int running = 1;
    while(running) {
        running = aria2::run(session, aria2::RUN_ONCE);
    }

    aria2::sessionFinal(session);
    aria2::libraryDeinit();

    wxQueueEvent(frame,
        new wxThreadEvent(wxEVT_THREAD, wxID_ANY));

    return (wxThread::ExitCode)0;*/
    system("unlink cover.jpg");
    DBG("Downloading " << url);
    std::string cmd("aria2c -o cover.jpg ");
    cmd += url;
    system(cmd.c_str());
    wxQueueEvent(frame,
        new wxThreadEvent(wxEVT_THREAD, wxID_ANY));
    return (wxThread::ExitCode)0;
}

class MyApp : public wxApp {
public:
    bool OnInit() override {
        wxInitAllImageHandlers();
        auto frame = new MainFrame();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);