#include <wx/wx.h>
#include <wx/process.h>
#include <wx/txtstrm.h>
#include <wx/url.h>
#include <wx/sstream.h>
#include <wx/mstream.h>
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
            auto text = searchBox->GetValue().ToStdString();
            querySong(text);
        });
    }

private:
    wxStaticBitmap* cover;
    wxStaticText* nameText;
    wxStaticText* artistText;
    wxStaticText* albumText;

    void querySong(const std::string& song) {
        DBG("Starting query for: " << song);

        //auto pipe = popen("./nemeta > nemeta.out", "w");
        int writePipe[2];
        int readPipe[2];
        pipe(writePipe);
        pipe(readPipe);
        auto pid = fork();
        if(pid == 0) {
            close(writePipe[1]);
            close(readPipe[0]);
            dup2(writePipe[1], STDIN_FILENO);
            dup2(readPipe[0], STDOUT_FILENO);
            execl("./nemeta", "./nemeta", NULL);
            exit(1);
        }
        close(writePipe[0]);
        close(readPipe[1]);
        auto send_to_child = [&writePipe](const char* content) {
            std::string buffer(content);
            buffer += "\n";
            write(writePipe[1], buffer.c_str(), buffer.length());
        };

        //if (!pipe) {
        //    DBG("Failed to start process");
        //    return;
        //}

        DBG("Process started");

        //fprintf(pipe, "get-by-name\n");
        send_to_child("get-by-name");
        DBG("get-by-name");

        //fprintf(pipe, "%s\n", song.c_str());
        send_to_child(song.c_str());
        DBG(song.c_str());

        //fprintf(pipe, "name\n");
        send_to_child("name");
        DBG("name");

        //fflush(pipe);

        char buf[256];
        auto nemeta_out = fopen("./nemeta.out", "r");
        if (fgets(buf, sizeof(buf), nemeta_out)) {
            DBG("Received: " << buf);
            nameText->SetLabel(wxString("Name: ") + buf);
        } else {
            DBG("No response received");
        }

        //pclose(pipe);
        DBG("Process closed");
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