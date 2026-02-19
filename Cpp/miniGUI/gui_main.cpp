#include "main_frame.h"

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