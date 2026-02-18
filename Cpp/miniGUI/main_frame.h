#pragma once
#include <string>
#include <wx/wx.h>
#include <wx/process.h>
#include <wx/txtstrm.h>
#include <wx/url.h>
#include <wx/sstream.h>
#include <wx/mstream.h>
#include <wx/imagpng.h>

class MainFrame : public wxFrame {
    public:
    MainFrame();
    private:
    wxStaticBitmap* cover;
    wxStaticText* nameText;
    wxStaticText* artistText;
    wxStaticText* albumText;
    wxStaticText* runInfo;
    void querySong(const std::string& song);
};
