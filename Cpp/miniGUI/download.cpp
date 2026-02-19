#include "download.h"
#include "main_frame.h"

#define debug true

#if debug
#define DBG(x) do { std::cerr << "[DEBUG] " << x << std::endl; } while(0)
#else
#define DBG(x)
#endif

DownloadThread::DownloadThread(MainFrame* frame, std::string url) : wxThread(wxTHREAD_DETACHED), frame(frame), url(url) {}
wxThread::ExitCode DownloadThread::Entry() {
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