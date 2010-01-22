#include "wxwfrontend.h"

Frontend::Frontend(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(550, 550))
{
//Set default values for options////////////////////////////////////////////////////////////////////
    bLowpass = false;
    bInvert = false;
    bFeatureEnable = false;
    bTypemapEnable = false;
    bOtherEnable = false;
    bOtherFirstTime = true;

    bPreviewLoaded = false;

    notebook = new wxNotebook(this, IDNB_MAIN);
    pnlMapConv = new wxPanel(notebook, -1);
    wxBoxSizer *hboxMain = new wxBoxSizer(wxHORIZONTAL);

//Vertical box for the files////////////////////////////////////////////////////////////////////////
    wxStaticBoxSizer *gboxFiles = new wxStaticBoxSizer(wxVERTICAL, pnlMapConv, wxT("Files"));

    wxBoxSizer *hboxHeight = new wxBoxSizer(wxHORIZONTAL);              //Heightmap/////////////////
    btnHeight = new wxButton(pnlMapConv, IDBTN_HEIGHT, wxT("Height Map"));
    tcHeight = new wxTextCtrl(pnlMapConv, wxID_ANY, wxT("heightmap.bmp"));

    wxBoxSizer *hboxTexture = new wxBoxSizer(wxHORIZONTAL);             //Texture///////////////////
    btnTexture = new wxButton(pnlMapConv, IDBTN_TEXTURE, wxT("Texture"));
    tcTexture = new wxTextCtrl(pnlMapConv, wxID_ANY, wxT("texture.bmp"));

    wxBoxSizer *hboxMetal = new wxBoxSizer(wxHORIZONTAL);               //Metal/////////////////////
    btnMetal = new wxButton(pnlMapConv, IDBTN_METAL, wxT("Metal"));
    tcMetal = new wxTextCtrl(pnlMapConv, wxID_ANY, wxT("metal.bmp"));

    wxBoxSizer *hboxFeatureEnable = new wxBoxSizer(wxHORIZONTAL);       //Feature enable////////////
    cbFeatureEnable = new wxCheckBox(pnlMapConv, IDCB_FEATURE_ENABLE, wxT("Enable Feature Map"));
    wxBoxSizer *hboxFeature = new wxBoxSizer(wxHORIZONTAL);             //Feature///////////////////
    btnFeature = new wxButton(pnlMapConv, IDBTN_FEATURE, wxT("Feature"));
    tcFeature = new wxTextCtrl(pnlMapConv, wxID_ANY, wxT("featuremap.bmp"));
    btnFeature->Enable(false);
    tcFeature->Enable(false);

    wxBoxSizer *hboxFeatureList = new wxBoxSizer(wxHORIZONTAL);         //Feature list//////////////
    btnFeatureList = new wxButton(pnlMapConv, IDBTN_FEATURELIST, wxT("Feature List"));
    tcFeatureList = new wxTextCtrl(pnlMapConv, wxID_ANY, wxT("featurelist.txt"));
    btnFeatureList->Enable(false);
    tcFeatureList->Enable(false);

    wxBoxSizer *hboxTypeEnable = new wxBoxSizer(wxHORIZONTAL);       //Type enable////////////
    cbTypeEnable = new wxCheckBox(pnlMapConv, IDCB_TYPEMAP_ENABLE, wxT("Enable Type Map"));
    wxBoxSizer *hboxType = new wxBoxSizer(wxHORIZONTAL);             //Type///////////////////
    btnType = new wxButton(pnlMapConv, IDBTN_TYPE, wxT("Type"));
    tcType = new wxTextCtrl(pnlMapConv, wxID_ANY, wxT("typemap.bmp"));
    btnType->Enable(false);
    tcType->Enable(false);

    wxBoxSizer *hboxGeovent = new wxBoxSizer(wxHORIZONTAL);               //Geovent///////////////////
    btnGeovent = new wxButton(pnlMapConv, IDBTN_GEOVENT, wxT("Geovent"));
    tcGeovent = new wxTextCtrl(pnlMapConv, wxID_ANY, wxT("geovent.bmp"));

    wxBoxSizer *hboxOutput = new wxBoxSizer(wxHORIZONTAL);               //Output////////////////////
    btnOutput = new wxButton(pnlMapConv, IDBTN_OUTPUT, wxT("Output"));
    tcOutput = new wxTextCtrl(pnlMapConv, wxID_ANY, wxT("Output.smf"));

    wxBoxSizer *hboxOtherOptions = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *vboxOtherOptions = new wxBoxSizer(wxVERTICAL);
    cbOtherOptionsEnable = new wxCheckBox(pnlMapConv, IDCB_OTHER_ENABLE, wxT("Enable Additional Options"));
    tcOtherOptions = new wxTextCtrl(pnlMapConv, IDST_OTHER, wxT("Additional Options"), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE ,wxDefaultValidator, wxT("OtherOptions"));
    tcOtherOptions->Enable(false);

    wxBoxSizer *hboxMainButtons = new wxBoxSizer(wxHORIZONTAL);
    btnCompile = new wxButton(pnlMapConv, IDBTN_COMPILE, wxT("Compile"));
    btnExit = new wxButton(pnlMapConv, IDBTN_EXIT, wxT("Exit"));
//Assemble files vbox////////////////////////////////////////////////////////////////////
    hboxHeight->Add(tcHeight, 1, wxLEFT | wxRIGHT, 8);
    hboxHeight->Add(btnHeight, 0, wxLEFT | wxRIGHT, 8);
    hboxTexture->Add(tcTexture, 1, wxLEFT | wxRIGHT, 8);
    hboxTexture->Add(btnTexture, 0, wxLEFT | wxRIGHT, 8);
    hboxMetal->Add(tcMetal, 1, wxLEFT | wxRIGHT, 8);
    hboxMetal->Add(btnMetal, 0, wxLEFT | wxRIGHT, 8);
    hboxFeatureEnable->Add(cbFeatureEnable, 0, wxLEFT | wxRIGHT, 8);
    hboxFeature->Add(tcFeature, 1, wxLEFT | wxRIGHT, 8);
    hboxFeature->Add(btnFeature, 0, wxLEFT | wxRIGHT, 8);
    hboxFeatureList->Add(tcFeatureList, 1, wxLEFT | wxRIGHT, 8);
    hboxFeatureList->Add(btnFeatureList, 0, wxLEFT | wxRIGHT, 8);
    hboxTypeEnable->Add(cbTypeEnable, 0, wxLEFT | wxRIGHT, 8);
    hboxType->Add(tcType, 1, wxLEFT | wxRIGHT, 8);
    hboxType->Add(btnType, 0, wxLEFT | wxRIGHT, 8);
    hboxGeovent->Add(tcGeovent, 1, wxLEFT | wxRIGHT, 8);
    hboxGeovent->Add(btnGeovent, 0, wxLEFT | wxRIGHT, 8);
    hboxOutput->Add(tcOutput, 1, wxLEFT | wxRIGHT, 8);
    hboxOutput->Add(btnOutput, 0, wxLEFT | wxRIGHT, 8);
        vboxOtherOptions->Add(cbOtherOptionsEnable, 0, wxLEFT | wxRIGHT, 8);
        vboxOtherOptions->Add(-1, 15);
        vboxOtherOptions->Add(tcOtherOptions, 1, wxLEFT | wxRIGHT, 8);
    hboxOtherOptions->Add(vboxOtherOptions, 1, wxLEFT | wxRIGHT, 8);
    hboxMainButtons->Add(btnCompile, 0, wxLEFT | wxRIGHT, 8);
    hboxMainButtons->Add(btnExit, 0, wxLEFT | wxRIGHT, 8);

    gboxFiles->Add(hboxHeight, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    gboxFiles->Add(hboxTexture, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    gboxFiles->Add(hboxMetal, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    gboxFiles->Add(hboxFeatureEnable, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    gboxFiles->Add(hboxFeature, 1, wxEXPAND | wxLEFT | wxRIGHT, 5);
    gboxFiles->Add(hboxFeatureList, 1, wxEXPAND | wxLEFT | wxRIGHT, 5);
    gboxFiles->Add(hboxTypeEnable, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    gboxFiles->Add(hboxType, 1, wxEXPAND | wxLEFT | wxRIGHT, 5);
    gboxFiles->Add(hboxGeovent, 1, wxEXPAND | wxLEFT | wxRIGHT, 5);
    gboxFiles->Add(hboxOutput, 1, wxEXPAND | wxLEFT | wxRIGHT, 5);

    gboxFiles->Add(hboxOtherOptions, 0, wxEXPAND | wxLEFT | wxRIGHT, 5);
    gboxFiles->Add(-1, 15);
    gboxFiles->Add(hboxMainButtons, 1, wxEXPAND | wxLEFT | wxRIGHT, 5);

//Vertical box for the heightmap options and quality controls/////////////////////////////////////////////////////////////////
    wxBoxSizer *vboxOptions = new wxBoxSizer(wxVERTICAL);
    wxStaticBoxSizer *gboxHeightOptions = new wxStaticBoxSizer(wxVERTICAL, pnlMapConv, wxT("Heightmap Options"));
    wxStaticBoxSizer *gboxAdditionalOptions = new wxStaticBoxSizer(wxVERTICAL, pnlMapConv, wxT("Other Options"));
    wxStaticBoxSizer *gboxPreview = new wxStaticBoxSizer(wxVERTICAL, pnlMapConv, wxT("Preview"));

    wxBoxSizer *hboxMax = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hboxMin = new wxBoxSizer(wxHORIZONTAL);
    tcMax = new wxTextCtrl(pnlMapConv, wxID_ANY, "250", wxDefaultPosition, wxSize(30,20), 0,wxDefaultValidator,"tcMax");
    tcMin = new wxTextCtrl(pnlMapConv, wxID_ANY, "25", wxDefaultPosition, wxSize(30,20), 0,wxDefaultValidator,"tcMin");
    stMax = new wxStaticText(pnlMapConv, wxID_ANY, wxT("Maximum"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT, wxT("MaxHeight"));
    stMin = new wxStaticText(pnlMapConv, wxID_ANY, wxT("Minimum"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT, wxT("MinHeight"));
    cbLowpass = new wxCheckBox(pnlMapConv, IDCB_LOWPASS, wxT("Lowpass"));
    cbInvert = new wxCheckBox(pnlMapConv, IDCB_INVERT, wxT("Invert"));
    cbLowpass->SetValue(true);
    cbInvert->SetValue(true);


    wxBoxSizer *hboxCompression = new wxBoxSizer(wxHORIZONTAL);
    tcCompression = new wxTextCtrl(pnlMapConv, wxID_ANY, wxT("0.8"), wxDefaultPosition, wxSize(30,20), 0,wxDefaultValidator,"wxTextCtrl");
    stCompression = new wxStaticText(pnlMapConv, wxID_ANY, wxT("Compression"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT, wxT("Compression"));
    wxBoxSizer *hboxFeatureRotate = new wxBoxSizer(wxHORIZONTAL);
    tcFeatureRotate = new wxTextCtrl(pnlMapConv, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(30,20), 0,wxDefaultValidator,"wxTextCtrl");
    stFeatureRotate = new wxStaticText(pnlMapConv, wxID_ANY, wxT("Rotate # features"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT, wxT("FeatureRotate"));

    wxArrayString *asQuality = new wxArrayString();
    asQuality->Add(wxT("Low"), 1);
    asQuality->Add(wxT("Medium"), 1);
    asQuality->Add(wxT("High"), 1);
    asQuality->Add(wxT("Best"), 1);
    rbxQuality = new wxRadioBox(pnlMapConv, IDRBX_QUALITY, wxT("nvdxt Options"), wxDefaultPosition, wxDefaultSize, *asQuality, 0, wxRA_SPECIFY_ROWS, wxDefaultValidator, wxT("radioBox"));
    rbxQuality->SetSelection(2);
    rbxQuality->SetItemToolTip(1, wxT("Requires an nvidia 8 gfx card or better."));

//Preview box////////////////////////////////////////////////////////////////////////////////////////
    wxBitmap bitmap( 128, 128 );
    bitmap = wxBitmap(_T("placeholder.bmp"), wxBITMAP_TYPE_BMP);
    sbmPreview = new wxStaticBitmap(pnlMapConv, wxID_ANY, bitmap, wxPoint(10, 10));

    gboxPreview->Add(sbmPreview, 1,  wxRIGHT | wxLEFT | wxBOTTOM | wxTOP, 8);
//Assemble Heightmap options////////////////////////////////////////////////////////////////////////
    hboxMax->Add(stMax, 0,  wxRIGHT | wxLEFT , 8);
    hboxMax->Add(tcMax, 1,  wxRIGHT | wxLEFT , 8);
    hboxMin->Add(stMin, 0,  wxRIGHT | wxLEFT , 8);
    hboxMin->Add(tcMin, 1,  wxRIGHT | wxLEFT , 8);
    gboxHeightOptions->Add(hboxMax, 1,  wxRIGHT | wxLEFT , 8);
    gboxHeightOptions->Add(hboxMin, 1,  wxRIGHT | wxLEFT , 8);
    gboxHeightOptions->Add(cbLowpass, 1,  wxRIGHT | wxLEFT , 8);
    gboxHeightOptions->Add(cbInvert, 1,  wxRIGHT | wxLEFT , 8);
//Assemble Quality boxes////////////////////////////////////////////////////////////////////////////
    hboxCompression->Add(stCompression, 1,  0, 8);
    hboxCompression->Add(tcCompression, 0,  0, 8);
    hboxFeatureRotate->Add(stFeatureRotate, 1,  0, 8);
    hboxFeatureRotate->Add(tcFeatureRotate, 0,  0, 8);

    gboxAdditionalOptions->Add(hboxCompression, 0,  wxRIGHT | wxLEFT | wxTOP, 8);
    gboxAdditionalOptions->Add(hboxFeatureRotate, 0,  wxRIGHT | wxLEFT | wxTOP, 8);


    vboxOptions->Add(gboxHeightOptions, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    vboxOptions->Add(rbxQuality, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);/////////////////////////////////////////////////////
    vboxOptions->Add(gboxAdditionalOptions, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    vboxOptions->Add(gboxPreview, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
//Final assembly////////////////////////////////////////////////////////////////////////////////////
    hboxMain->Add(gboxFiles, 2, wxLEFT | wxRIGHT | wxTOP | wxBOTTOM, 5);
    hboxMain->Add(vboxOptions, 1, wxTOP | wxBOTTOM | wxALIGN_RIGHT, 5);

    pnlMapConv->SetSizer(hboxMain);
    notebook->AddPage(pnlMapConv, "MapConv", true);
////////////////////////////////////////////////////////////////////////////////////////////////////
//SMD////////////////////////////////////////////////////////////////////////////////////e2F//////////
////////////////////////////////////////////////////////////////////////////////////////////////////

    pnlSMD = new wxPanel(notebook, -1);            //Create a panel to contain the subnotebook
    nbSMD = new wxNotebook(pnlSMD, wxID_ANY);               //Create the subnotebook
    wxBoxSizer* box = new wxBoxSizer( wxHORIZONTAL );       //create a sizer to expand the subnotebook
    box->Add( nbSMD, 1, wxEXPAND, 0 );

    wxPanel *pnlSMDGeneral = new wxPanel(pnlSMD, -1);
    wxBoxSizer *vboxSMDGeneralMain = new wxBoxSizer(wxVERTICAL);
    wxStaticBoxSizer *gboxSMDGeneral = new wxStaticBoxSizer(wxVERTICAL, pnlSMDGeneral, "General Ma0 Options");
    wxStaticBoxSizer *gboxSMDStartPos = new wxStaticBoxSizer(wxVERTICAL, pnlSMDGeneral, "Player Start Options");

    vboxSMDGeneralMain->Add(gboxSMDGeneral, 1, wxEXPAND, 0);
    vboxSMDGeneralMain->Add(gboxSMDStartPos, 1, wxEXPAND, 0);

    pnlSMDGeneral->SetSizer(vboxSMDGeneralMain);

    nbSMD->AddPage(pnlSMDGeneral, "General", true);
    nbSMD->AddPage(pnlSMDGeneral, "General2", true);
    pnlSMD->SetSizer( box );
    pnlSMD->Layout();

    notebook->AddPage(pnlSMD, "SMD", true);
    notebook->ChangeSelection(1);
////////////////////////////////////////////////////////////////////////////////////////////////////
//Connect the controls to their appropriate functions///////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//Enabling checkboxes//
    Connect(IDCB_FEATURE_ENABLE, wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(Frontend::OnToggleFeatureEnable));
    Connect(IDCB_TYPEMAP_ENABLE, wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(Frontend::OnToggleTypemapEnable));
    Connect(IDCB_OTHER_ENABLE, wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(Frontend::OnToggleOtherEnable));

    Connect(IDCB_LOWPASS, wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(Frontend::OnToggleLowpass));
    Connect(IDCB_INVERT, wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(Frontend::OnToggleInvert));
//File inputs//
    Connect(IDBTN_HEIGHT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Frontend::OnOpenHeight));
    Connect(IDBTN_TEXTURE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Frontend::OnOpenTexture));
    Connect(IDBTN_METAL, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Frontend::OnOpenMetal));
    Connect(IDBTN_FEATURE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Frontend::OnOpenFeature));
    Connect(IDBTN_FEATURELIST, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Frontend::OnOpenFeatureList));
    Connect(IDBTN_TYPE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Frontend::OnOpenType));
    Connect(IDBTN_GEOVENT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Frontend::OnOpenGeovent));
    Connect(IDBTN_OUTPUT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Frontend::OnOpenOutput));
//Buttons//
    Connect(IDBTN_COMPILE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Frontend::OnClickCompile));
    Connect(IDBTN_EXIT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Frontend::OnClickExit));
//Tabs
    Connect(IDNB_MAIN, wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxCommandEventHandler(Frontend::OnTabSwitch));

    Centre();
}

void Frontend::OnTabSwitch(wxCommandEvent& event)
{
    pnlSMD->Refresh();
}


//
void Frontend::OnToggleLowpass(wxCommandEvent& event)
{
    bLowpass=!bLowpass;
}
void Frontend::OnToggleInvert(wxCommandEvent& event)
{
    bInvert=!bInvert;
}
void Frontend::OnToggleFeatureEnable(wxCommandEvent& event)
{
    if(bFeatureEnable == false)
    {
        btnFeature->Enable(true);
        tcFeature->Enable(true);
        btnFeatureList->Enable(true);
        tcFeatureList->Enable(true);
    }
    else
    {
        btnFeature->Enable(false);
        tcFeature->Enable(false);
        btnFeatureList->Enable(false);
        tcFeatureList->Enable(false);
    }
    bFeatureEnable = !bFeatureEnable;
}
void Frontend::OnToggleTypemapEnable(wxCommandEvent& event)
{
    if(bTypemapEnable == false)
    {
        btnType->Enable(true);
        tcType->Enable(true);
    }
    else
    {
        btnType->Enable(false);
        tcType->Enable(false);
    }
    bTypemapEnable = !bTypemapEnable;
}
void Frontend::OnToggleOtherEnable(wxCommandEvent& event)
{
    if(bOtherFirstTime == true)
    {
        tcOtherOptions->SetValue("");
        bOtherFirstTime = false;
    }
    if(bOtherEnable == false)
    {
        tcOtherOptions->Enable(true);
    }
    else
    {
        tcOtherOptions->Enable(false);
    }
    bOtherEnable = !bOtherEnable;
}
void Frontend::OnClickExit(wxCommandEvent& event)
{
    Close(true);
}