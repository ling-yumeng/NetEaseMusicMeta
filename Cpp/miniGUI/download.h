#pragma once
#include <string>
#include <wx/wx.h>
#include <wx/process.h>
#include <wx/txtstrm.h>
#include <wx/url.h>
#include <wx/sstream.h>
#include <wx/mstream.h>
#include <wx/imagpng.h>

class MainFrame;

class DownloadThread : public wxThread {
    public:
    DownloadThread(MainFrame* frame, std::string url);

    protected:
    ExitCode Entry() override;

    private:
    MainFrame* frame;
    std::string url;
};