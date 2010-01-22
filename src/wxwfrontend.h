#include <wx/wx.h>
#include <iostream>
#include <wx/dcclient.h>
#include <wx/image.h>
#include <wx/bitmap.h>
#include <wx/window.h>
#include <wx/statbmp.h>
#include <wx/notebook.h>

#include "resources.h"

class Frontend : public wxFrame
{
public:
    Frontend(const wxString& title);

private:
    void OnToggleLowpass(wxCommandEvent& event);
    void OnToggleInvert(wxCommandEvent& event);
    void OnToggleFeatureEnable(wxCommandEvent& event);
    void OnToggleTypemapEnable(wxCommandEvent& event);
    void OnToggleOtherEnable(wxCommandEvent& event);

    void OnClickCompile(wxCommandEvent& event);
    void OnClickExit(wxCommandEvent& event);

    void OnOpenHeight(wxCommandEvent& event);
    void OnOpenTexture(wxCommandEvent& event);
    void OnOpenMetal(wxCommandEvent& event);
    void OnOpenFeature(wxCommandEvent& event);
    void OnOpenFeatureList(wxCommandEvent& event);
    void OnOpenType(wxCommandEvent& event);
    void OnOpenGeovent(wxCommandEvent& event);
    void OnOpenOutput(wxCommandEvent& event);

    void OnTabSwitch(wxCommandEvent& event);

    bool bLowpass;
    bool bInvert;
    bool bFeatureEnable;
    bool bTypemapEnable;
    bool bOtherEnable;
    bool bOtherFirstTime;

    bool bPreviewLoaded;

    wxNotebook *notebook;
    wxNotebook *nbSMD;
    wxPanel *pnlSMD;
//Map Compiler panel//////////////////////////////////////////////////////////
    wxFileDialog *openFileDialog;
    wxPanel *pnlMapConv;
//Heightmap/////////////////
    wxButton *btnHeight;
    wxTextCtrl *tcHeight;
//Texture///////////////////
    wxButton *btnTexture;
    wxTextCtrl *tcTexture;
//Metal/////////////////////
    wxButton *btnMetal;
    wxTextCtrl *tcMetal;
//Feature enable////////////
    wxCheckBox *cbFeatureEnable;
//Feature///////////////////
    wxButton *btnFeature;
    wxTextCtrl *tcFeature;
//Feature list//////////////
    wxButton *btnFeatureList;
    wxTextCtrl *tcFeatureList;
//Type enable////////////
    wxCheckBox *cbTypeEnable;
//Type///////////////////
    wxButton *btnType;
    wxTextCtrl *tcType;
//Geovent///////////////////
    wxButton *btnGeovent;
    wxTextCtrl *tcGeovent;
    wxCheckBox *cbOtherOptionsEnable;
    wxTextCtrl *tcOtherOptions;

//Output////////////////////
    wxButton *btnOutput;
    wxTextCtrl *tcOutput;

    wxBoxSizer *hboxMax;
    wxBoxSizer *hboxMin;
    wxTextCtrl *tcMax;
    wxTextCtrl *tcMin;
    wxStaticText *stMax;
    wxStaticText *stMin;
    wxCheckBox *cbLowpass;
    wxCheckBox *cbInvert;

    wxTextCtrl *tcCompression;
    wxStaticText *stCompression;
    wxTextCtrl *tcFeatureRotate;
    wxStaticText *stFeatureRotate;

    wxRadioBox *rbxQuality;

    wxStaticBitmap *sbmPreview;

    wxButton *btnCompile;
    wxButton *btnExit;
//smd creater panel///////////////////////////////////////////////////////////

};