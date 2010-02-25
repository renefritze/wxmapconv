#include "wxwfrontend.h"

Frontend::Frontend(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(600, 600))
{
    bLowpass = true;
    bInvert = true;
    bFeatureEnable = false;
    bTypemapEnable = false;
    bOtherEnable = false;
    bOtherFirstTime = true;

    bHeightmapLoaded = false;
    bTextureLoaded = false;
    bMetalLoaded = false;
    bFeatureLoaded = false;
    bTypemapLoaded = false;

    bSaved = false;

    image = new wxImage(300,300);

//Atmospheric Options//
    colSun = new wxColour(255, 200, 20);
    colSky = new wxColour(20, 20, 240);
    colCloud = new wxColour(150, 150, 150);
    colFog = new wxColour(100, 100, 100);
//Light Options//
    colGroundAmbient = new wxColour(127, 127, 127);
    colGroundSun = new wxColour(127, 127, 127);
    colUnitAmbient = new wxColour(127, 127, 127);
    colUnitSun = new wxColour(127, 127, 127);
//Water Options//
    colWaterBase = new wxColour(100, 150, 200);
    colWaterMin = new wxColour(10, 10, 30);
    colWaterAbsorb = new wxColour(4, 4, 2);
////////////////////////////////////////////////////////////////////////////////////////////////////
//Menu bar//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
    menubar = new wxMenuBar;
    mnFile = new wxMenu;
    mnAbout = new wxMenu;

    mnFile->Append(IDMENU_NEW, wxT("&New"));
    mnFile->Append(IDMENU_OPEN, wxT("&Open"));
    mnFile->Append(IDMENU_SAVE, wxT("&Save"));
    mnFile->Append(IDMENU_SAVEAS, wxT("Save &As"));
    mnFile->AppendSeparator();
    mnFile->Append(wxID_EXIT, wxT("&Quit"));

    menubar->Append(mnFile, wxT("&File"));
    SetMenuBar(menubar);

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
    btnFeature->Enable(bFeatureEnable);
    tcFeature->Enable(bFeatureEnable);

    wxBoxSizer *hboxFeatureList = new wxBoxSizer(wxHORIZONTAL);         //Feature list//////////////
    btnFeatureList = new wxButton(pnlMapConv, IDBTN_FEATURELIST, wxT("Feature List"));
    tcFeatureList = new wxTextCtrl(pnlMapConv, wxID_ANY, wxT("featurelist.txt"));
    btnFeatureList->Enable(bFeatureEnable);
    tcFeatureList->Enable(bFeatureEnable);

    wxBoxSizer *hboxTypeEnable = new wxBoxSizer(wxHORIZONTAL);       //Type enable////////////
    cbTypeEnable = new wxCheckBox(pnlMapConv, IDCB_TYPEMAP_ENABLE, wxT("Enable Type Map"));
    wxBoxSizer *hboxType = new wxBoxSizer(wxHORIZONTAL);             //Type///////////////////
    btnType = new wxButton(pnlMapConv, IDBTN_TYPE, wxT("Type"));
    tcType = new wxTextCtrl(pnlMapConv, wxID_ANY, wxT("typemap.bmp"));
    btnType->Enable(bTypemapEnable);
    tcType->Enable(bTypemapEnable);

    wxBoxSizer *hboxGeovent = new wxBoxSizer(wxHORIZONTAL);               //Geovent///////////////////
    btnGeovent = new wxButton(pnlMapConv, IDBTN_GEOVENT, wxT("Geovent"));
    tcGeovent = new wxTextCtrl(pnlMapConv, wxID_ANY, wxT("geovent.bmp"));

    wxBoxSizer *hboxOutput = new wxBoxSizer(wxHORIZONTAL);               //Output////////////////////
    btnOutput = new wxButton(pnlMapConv, IDBTN_OUTPUT, wxT("Output"));
    tcOutput = new wxTextCtrl(pnlMapConv, wxID_ANY, wxT("Output.smf"));

    wxBoxSizer *hboxOtherOptions = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *vboxOtherOptions = new wxBoxSizer(wxVERTICAL);
    cbOtherOptionsEnable = new wxCheckBox(pnlMapConv, IDCB_OTHER_ENABLE, wxT("Enable Additional Options"));
    tcOtherOptions = new wxTextCtrl(pnlMapConv, IDST_OTHER, wxT("Additional Options"));
    tcOtherOptions->Enable(bOtherEnable);

    wxBoxSizer *hboxMainButtons = new wxBoxSizer(wxHORIZONTAL);
    btnCompile = new wxButton(pnlMapConv, IDBTN_COMPILE, wxT("Compile"));
    btnExit = new wxButton(pnlMapConv, wxID_EXIT, wxT("Exit"));

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

    wxFlexGridSizer *fgHeightOptions = new wxFlexGridSizer(4,2,5,5);
        stMax = new wxStaticText(pnlMapConv, wxID_ANY, wxT("Maximum"));
        tcMax = new wxTextCtrl(pnlMapConv, wxID_ANY, wxT("250"));
        stMin = new wxStaticText(pnlMapConv, wxID_ANY, wxT("Minimum"));
        tcMin = new wxTextCtrl(pnlMapConv, wxID_ANY, wxT("25"));
        cbLowpass = new wxCheckBox(pnlMapConv, IDCB_LOWPASS, wxT("Lowpass"));
        wxPanel *pnlLowpassPadding = new wxPanel(pnlMapConv, wxID_ANY);
        cbInvert = new wxCheckBox(pnlMapConv, IDCB_INVERT, wxT("Invert"));
        wxPanel *pnlInvertPadding = new wxPanel(pnlMapConv, wxID_ANY);
        cbLowpass->SetValue(bLowpass);
        cbInvert->SetValue(bInvert);

    wxFlexGridSizer *fgCompression = new wxFlexGridSizer(2,2,5,5);
        tcCompression = new wxTextCtrl(pnlMapConv, wxID_ANY, wxT("0.8"));
        stCompression = new wxStaticText(pnlMapConv, wxID_ANY, wxT("Compression"));
        tcFeatureRotate = new wxTextCtrl(pnlMapConv, wxID_ANY, wxT("0"));
        stFeatureRotate = new wxStaticText(pnlMapConv, wxID_ANY, wxT("Rotate # features"));

    wxArrayString *asQuality = new wxArrayString();
        asQuality->Add(wxT("Low"), 1);
        asQuality->Add(wxT("Medium"), 1);
        asQuality->Add(wxT("High"), 1);
        asQuality->Add(wxT("Best"), 1);
    rbxQuality = new wxRadioBox(pnlMapConv, IDRBX_QUALITY, wxT("nvdxt Options"), wxDefaultPosition, wxDefaultSize, *asQuality, 0, wxRA_SPECIFY_ROWS, wxDefaultValidator, wxT("radioBox"));
    rbxQuality->SetSelection(2);
    rbxQuality->SetItemToolTip(1, wxT("Requires an nvidia 8 gfx card or better."));

//Preview box////////////////////////////////////////////////////////////////////////////////////////
    sbmPreview = new wxStaticBitmap(pnlMapConv, wxID_ANY, wxBitmap(wxBITMAP(IDBM_PREVIEW_PLACEHOLDER)), wxPoint(10, 10));

    gboxPreview->Add(sbmPreview, 1,  wxEXPAND | wxRIGHT | wxLEFT | wxBOTTOM | wxTOP, 5);
//Assemble Heightmap options////////////////////////////////////////////////////////////////////////
        fgHeightOptions->Add(stMax, 1, wxEXPAND | wxRIGHT | wxLEFT , 5);
        fgHeightOptions->Add(tcMax, 1, wxEXPAND | wxRIGHT | wxLEFT , 5);
        fgHeightOptions->Add(stMin, 1, wxEXPAND | wxRIGHT | wxLEFT , 5);
        fgHeightOptions->Add(tcMin, 1, wxEXPAND | wxRIGHT | wxLEFT , 5);
        fgHeightOptions->Add(cbLowpass, 1, wxEXPAND | wxRIGHT | wxLEFT , 5);
        fgHeightOptions->Add(pnlLowpassPadding, 1, wxRIGHT | wxLEFT , 5);
        fgHeightOptions->Add(cbInvert, 1, wxEXPAND | wxRIGHT | wxLEFT , 5);
        fgHeightOptions->Add(pnlInvertPadding, 1, wxEXPAND | wxRIGHT | wxLEFT , 5);
    gboxHeightOptions->Add(fgHeightOptions, 1, wxEXPAND ,0 ,0);
//Assemble Quality boxes////////////////////////////////////////////////////////////////////////////


    fgCompression->Add(stCompression, 1,  wxEXPAND | wxRIGHT | wxLEFT, 5);
    fgCompression->Add(tcCompression, 1,  wxEXPAND | wxRIGHT | wxLEFT, 5);
    fgCompression->Add(stFeatureRotate, 1,  wxEXPAND | wxRIGHT | wxLEFT, 5);
    fgCompression->Add(tcFeatureRotate, 1,  wxEXPAND | wxRIGHT | wxLEFT, 5);

    gboxAdditionalOptions->Add(fgCompression, 1, wxEXPAND | wxRIGHT | wxLEFT | wxTOP, 8);


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
//Preview Tab///////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
    pnlPreview = new wxPanel(notebook, -1);
    wxBoxSizer *hboxPreview = new wxBoxSizer(wxHORIZONTAL);
    wxStaticBoxSizer *gboxPreviewBig = new wxStaticBoxSizer(wxVERTICAL, pnlPreview, wxT("Preview"));

    bmHeightmap = new wxBitmap(wxBitmap(wxBITMAP(IDBM_PREVIEW_BIG_PLACEHOLDER)));
    bmTexture = new wxBitmap(wxBitmap(wxBITMAP(IDBM_PREVIEW_BIG_PLACEHOLDER)));
    bmMetal = new wxBitmap(wxBitmap(wxBITMAP(IDBM_PREVIEW_BIG_PLACEHOLDER)));
    bmFeature = new wxBitmap(wxBitmap(wxBITMAP(IDBM_PREVIEW_BIG_PLACEHOLDER)));
    bmTypemap = new wxBitmap(wxBitmap(wxBITMAP(IDBM_PREVIEW_BIG_PLACEHOLDER)));


    wxPanel *pnlPreviewBig = new wxPanel(pnlPreview, -1);
    wxBoxSizer *hboxPreviewBig = new wxBoxSizer(wxHORIZONTAL);
    sbmPreviewBig = new wxStaticBitmap(pnlPreviewBig, wxID_ANY, wxBitmap(wxBITMAP(IDBM_PREVIEW_BIG_PLACEHOLDER)), wxPoint(10, 10));

    hboxPreviewBig->Add(sbmPreviewBig, 1, wxEXPAND, 5);
    pnlPreviewBig->SetSizer(hboxPreviewBig);
    gboxPreviewBig->Add(pnlPreviewBig, 1, wxEXPAND | wxRIGHT | wxLEFT | wxBOTTOM | wxTOP, 5);
    sbmPreviewBig->CentreOnParent();

        wxArrayString *asPreview = new wxArrayString();
        asPreview->Add(wxT("Heightmap"), 1);
        asPreview->Add(wxT("Texture"), 1);
        asPreview->Add(wxT("Metal"), 1);
        asPreview->Add(wxT("Feature"), 1);
        asPreview->Add(wxT("Type"), 1);
    rbxPreview = new wxRadioBox(pnlPreview, IDRBX_PREVIEW, wxT("Select File for Preview"), wxDefaultPosition, wxDefaultSize, *asPreview, 0, wxRA_SPECIFY_ROWS, wxDefaultValidator, wxT("radioBox"));

    hboxPreview->Add(gboxPreviewBig, 1, wxEXPAND, 5);
    hboxPreview->Add(rbxPreview, 0, wxEXPAND, 5);
    pnlPreview->SetSizer(hboxPreview);
    notebook->AddPage(pnlPreview, "Preview", true);
////////////////////////////////////////////////////////////////////////////////////////////////////
//SMD///////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

    pnlSMD = new wxPanel(notebook, -1);            //Create a panel to contain the subnotebook
    nbSMD = new wxNotebook(pnlSMD, wxID_ANY);               //Create the subnotebook

    wxFlexGridSizer* box = new wxFlexGridSizer(2,1,0,0);       //create a sizer to expand the subnotebook
    notebook->AddPage(pnlSMD, wxT("SMD"), true);
////////////////////////////////////////////////////////////////////////////////////////////////////
//General page containging basic info and player start positions////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
    pnlSMDGeneral = new wxPanel(nbSMD, -1);
    wxBoxSizer *vboxSMDGeneralMain = new wxBoxSizer(wxVERTICAL);
    wxStaticBoxSizer *gboxSMDGeneral = new wxStaticBoxSizer(wxVERTICAL, pnlSMDGeneral, wxT("General Map Options"));
    wxFlexGridSizer* gsSMDBasic = new wxFlexGridSizer(0,4,5,5);

    wxStaticText *stDescription = new wxStaticText(pnlSMDGeneral, wxID_ANY, wxT("Description"));
    tcDescription = new wxTextCtrl(pnlSMDGeneral, wxID_ANY, wxT("Description of your map"), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    wxStaticText *stGravity = new wxStaticText(pnlSMDGeneral, wxID_ANY, wxT("Gravity"));
    tcGravity = new wxTextCtrl(pnlSMDGeneral, wxID_ANY, wxT("130"));
    wxStaticText *stMapHardness = new wxStaticText(pnlSMDGeneral, wxID_ANY, wxT("Map Hardness"));
    tcMapHardness = new wxTextCtrl(pnlSMDGeneral, wxID_ANY, wxT("100"));
    wxStaticText *stMaxMetal = new wxStaticText(pnlSMDGeneral, wxID_ANY, wxT("Max Metal"));
    tcMaxMetal = new wxTextCtrl(pnlSMDGeneral, wxID_ANY, wxT("3.0"));
    wxStaticText *stExtractorRadius = new wxStaticText(pnlSMDGeneral, wxID_ANY, wxT("Extractor Radius"));
    tcExtractorRadius = new wxTextCtrl(pnlSMDGeneral, wxID_ANY, wxT("50"));
    wxStaticText *stTidalStrength = new wxStaticText(pnlSMDGeneral, wxID_ANY, wxT("TidalStrength"));
    tcTidalStrength = new wxTextCtrl(pnlSMDGeneral, wxID_ANY, wxT("20"));
    wxStaticText *stMaxWind = new wxStaticText(pnlSMDGeneral, wxID_ANY, wxT("MaxWind"));
    tcMaxWind = new wxTextCtrl(pnlSMDGeneral, IDTC_MAX_HEIGHT, wxT("30"));
    wxStaticText *stMinWind = new wxStaticText(pnlSMDGeneral, wxID_ANY, wxT("MinWind"));
    tcMinWind = new wxTextCtrl(pnlSMDGeneral, IDTC_MIN_HEIGHT, wxT("10"));
    wxStaticText *stMaxHeight = new wxStaticText(pnlSMDGeneral, wxID_ANY, wxT("Max Height"));
    tcMaxHeight = new wxTextCtrl(pnlSMDGeneral, IDTC_MAX_HEIGHT, wxT("250"));
    wxStaticText *stMinHeight = new wxStaticText(pnlSMDGeneral, wxID_ANY, wxT("Min Height"));
    tcMinHeight = new wxTextCtrl(pnlSMDGeneral, IDTC_MIN_HEIGHT, wxT("25"));

    wxStaticBoxSizer *gboxSMDStartPos = new wxStaticBoxSizer(wxVERTICAL, pnlSMDGeneral, wxT("Player Start Options"));

    wxGridSizer *gsStartPos = new wxFlexGridSizer(0,5,5,5);
        wxStaticText *stTeamCount = new wxStaticText(pnlSMDGeneral, wxID_ANY, wxT("Number of Players"));
        tcTeamCount = new wxTextCtrl(pnlSMDGeneral, IDTC_TEAM_COUNT, wxT("4"), wxDefaultPosition, wxSize(50,20), 0, wxDefaultValidator, wxT("TeamCount"));
        wxPanel *pnlTeamCountPlaceHolder1 = new wxPanel(pnlSMDGeneral, -1);
        wxPanel *pnlTeamCountPlaceHolder2 = new wxPanel(pnlSMDGeneral, -1);
        wxPanel *pnlTeamCountPlaceHolder3 = new wxPanel(pnlSMDGeneral, -1);

        wxStaticText *stTeam1 = new wxStaticText(pnlSMDGeneral, wxID_ANY, wxT("Team1"));
            wxStaticText *stTeam1X = new wxStaticText(pnlSMDGeneral, -1, wxT(" X "));
            tcTeam1X = new wxTextCtrl(pnlSMDGeneral, -1, wxT("64"));
            wxStaticText *stTeam1Y = new wxStaticText(pnlSMDGeneral, -1, wxT(" Y "));
            tcTeam1Y = new wxTextCtrl(pnlSMDGeneral, -1, wxT("64"));
        wxStaticText *stTeam2 = new wxStaticText(pnlSMDGeneral, wxID_ANY, wxT("Team2"));
            wxStaticText *stTeam2X = new wxStaticText(pnlSMDGeneral, -1, wxT(" X "));
            tcTeam2X = new wxTextCtrl(pnlSMDGeneral, -1, wxT("64"));
            wxStaticText *stTeam2Y = new wxStaticText(pnlSMDGeneral, -1, wxT(" Y "));
            tcTeam2Y = new wxTextCtrl(pnlSMDGeneral, -1, wxT("64"));
        wxStaticText *stTeam3 = new wxStaticText(pnlSMDGeneral, wxID_ANY, wxT("Team3"));
            wxStaticText *stTeam3X = new wxStaticText(pnlSMDGeneral, -1, wxT(" X "));
            tcTeam3X = new wxTextCtrl(pnlSMDGeneral, -1, wxT("64"));
            wxStaticText *stTeam3Y = new wxStaticText(pnlSMDGeneral, -1, wxT(" Y "));
            tcTeam3Y = new wxTextCtrl(pnlSMDGeneral, -1, wxT("64"));
        wxStaticText *stTeam4 = new wxStaticText(pnlSMDGeneral, wxID_ANY, wxT("Team4"));
            wxStaticText *stTeam4X = new wxStaticText(pnlSMDGeneral, -1, wxT(" X "));
            tcTeam4X = new wxTextCtrl(pnlSMDGeneral, -1, wxT("64"));
            wxStaticText *stTeam4Y = new wxStaticText(pnlSMDGeneral, -1, wxT(" Y "));
            tcTeam4Y = new wxTextCtrl(pnlSMDGeneral, -1, wxT("64"));
        wxStaticText *stTeam5 = new wxStaticText(pnlSMDGeneral, wxID_ANY, wxT("Team5"));
            wxStaticText *stTeam5X = new wxStaticText(pnlSMDGeneral, -1, wxT(" X "));
            tcTeam5X = new wxTextCtrl(pnlSMDGeneral, -1, wxT("64"));
            wxStaticText *stTeam5Y = new wxStaticText(pnlSMDGeneral, -1, wxT(" Y "));
            tcTeam5Y = new wxTextCtrl(pnlSMDGeneral, -1, wxT("64"));
        wxStaticText *stTeam6 = new wxStaticText(pnlSMDGeneral, wxID_ANY, wxT("Team6"));
            wxStaticText *stTeam6X = new wxStaticText(pnlSMDGeneral, -1, wxT(" X "));
            tcTeam6X = new wxTextCtrl(pnlSMDGeneral, -1, wxT("64"));
            wxStaticText *stTeam6Y = new wxStaticText(pnlSMDGeneral, -1, wxT(" Y "));
            tcTeam6Y = new wxTextCtrl(pnlSMDGeneral, -1, wxT("64"));
        wxStaticText *stTeam7 = new wxStaticText(pnlSMDGeneral, wxID_ANY, wxT("Team7"));
            wxStaticText *stTeam7X = new wxStaticText(pnlSMDGeneral, -1, wxT(" X "));
            tcTeam7X = new wxTextCtrl(pnlSMDGeneral, -1, wxT("64"));
            wxStaticText *stTeam7Y = new wxStaticText(pnlSMDGeneral, -1, wxT(" Y "));
            tcTeam7Y = new wxTextCtrl(pnlSMDGeneral, -1, wxT("64"));
        wxStaticText *stTeam8 = new wxStaticText(pnlSMDGeneral, wxID_ANY, wxT("Team8"));
            wxStaticText *stTeam8X = new wxStaticText(pnlSMDGeneral, -1, wxT(" X "));
            tcTeam8X = new wxTextCtrl(pnlSMDGeneral, -1, wxT("64"));
            wxStaticText *stTeam8Y = new wxStaticText(pnlSMDGeneral, -1, wxT(" Y "));
            tcTeam8Y = new wxTextCtrl(pnlSMDGeneral, -1, wxT("64"));
        tcTeam5X->Enable(false);
        tcTeam5Y->Enable(false);
        tcTeam6X->Enable(false);
        tcTeam6Y->Enable(false);
        tcTeam7X->Enable(false);
        tcTeam7Y->Enable(false);
        tcTeam8X->Enable(false);
        tcTeam8Y->Enable(false);

    gsSMDBasic->SetFlexibleDirection(wxVERTICAL);
    gsSMDBasic->Add(stDescription, 1, wxEXPAND, 0);
    gsSMDBasic->Add(tcDescription, 3, wxEXPAND, 0);
    gsSMDBasic->Add(stGravity, 1, wxEXPAND, 0);
    gsSMDBasic->Add(tcGravity, 3, wxEXPAND, 0);
    gsSMDBasic->Add(stMapHardness, 1, wxEXPAND, 0);
    gsSMDBasic->Add(tcMapHardness, 3, wxEXPAND, 0);
    gsSMDBasic->Add(stMaxMetal, 1, wxEXPAND, 0);
    gsSMDBasic->Add(tcMaxMetal, 3, wxEXPAND, 0);
    gsSMDBasic->Add(stExtractorRadius, 1, wxEXPAND, 0);
    gsSMDBasic->Add(tcExtractorRadius, 3, wxEXPAND, 0);
    gsSMDBasic->Add(stTidalStrength, 1, wxEXPAND, 0);
    gsSMDBasic->Add(tcTidalStrength, 3, wxEXPAND, 0);
    gsSMDBasic->Add(stMaxWind, 1, wxEXPAND, 0);
    gsSMDBasic->Add(tcMaxWind, 3, wxEXPAND, 0);
    gsSMDBasic->Add(stMinWind, 1, wxEXPAND, 0);
    gsSMDBasic->Add(tcMinWind, 3, wxEXPAND, 0);
    gsSMDBasic->Add(stMaxHeight, 1, wxEXPAND, 0);
    gsSMDBasic->Add(tcMaxHeight, 3, wxEXPAND, 0);
    gsSMDBasic->Add(stMinHeight, 1, wxEXPAND, 0);
    gsSMDBasic->Add(tcMinHeight, 3, wxEXPAND, 0);

    gsStartPos->Add(stTeamCount, 1, wxEXPAND, 0);
    gsStartPos->Add(tcTeamCount, 1, wxEXPAND, 0);
    gsStartPos->Add(pnlTeamCountPlaceHolder1, 1, wxEXPAND, 0);
    gsStartPos->Add(pnlTeamCountPlaceHolder2, 1, wxEXPAND, 0);
    gsStartPos->Add(pnlTeamCountPlaceHolder3, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam1, 1, wxEXPAND, 0);
        gsStartPos->Add(tcTeam1X, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam1X, 1, wxEXPAND, 0);
        gsStartPos->Add(tcTeam1Y, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam1Y, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam2, 1, wxEXPAND, 0);
        gsStartPos->Add(tcTeam2X, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam2X, 1, wxEXPAND, 0);
        gsStartPos->Add(tcTeam2Y, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam2Y, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam3, 1, wxEXPAND, 0);
        gsStartPos->Add(tcTeam3X, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam3X, 1, wxEXPAND, 0);
        gsStartPos->Add(tcTeam3Y, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam3Y, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam4, 1, wxEXPAND, 0);
        gsStartPos->Add(tcTeam4X, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam4X, 1, wxEXPAND, 0);
        gsStartPos->Add(tcTeam4Y, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam4Y, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam5, 1, wxEXPAND, 0);
        gsStartPos->Add(tcTeam5X, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam5X, 1, wxEXPAND, 0);
        gsStartPos->Add(tcTeam5Y, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam5Y, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam6, 1, wxEXPAND, 0);
        gsStartPos->Add(tcTeam6X, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam6X, 1, wxEXPAND, 0);
        gsStartPos->Add(tcTeam6Y, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam6Y, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam7, 1, wxEXPAND, 0);
        gsStartPos->Add(tcTeam7X, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam7X, 1, wxEXPAND, 0);
        gsStartPos->Add(tcTeam7Y, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam7Y, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam8, 1, wxEXPAND, 0);
        gsStartPos->Add(tcTeam8X, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam8X, 1, wxEXPAND, 0);
        gsStartPos->Add(tcTeam8Y, 1, wxEXPAND, 0);
        gsStartPos->Add(stTeam8Y, 1, wxEXPAND, 0);

    gboxSMDGeneral->Add(gsSMDBasic, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    gboxSMDStartPos->Add(gsStartPos, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);

    vboxSMDGeneralMain->Add(gboxSMDGeneral, 3, wxEXPAND, 0);
    vboxSMDGeneralMain->Add(gboxSMDStartPos, 4, wxEXPAND, 0);
////////////////////////////////////////////////////////////////////////////////////////////////////
//Atmospheric and lighting page, containging cloud and atmosphere colouring and lighting////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
    pnlSMDAtmosphere = new wxPanel(nbSMD, -1);
    wxBoxSizer *vboxSMDAtmosphereAndLight = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hboxSMDAtmosphere = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hboxSunDirection = new wxBoxSizer(wxHORIZONTAL);


    wxStaticBoxSizer *gsSMDAtmosphere = new wxStaticBoxSizer(wxVERTICAL, pnlSMDAtmosphere, wxT("Atmospheric Settings"));
    wxFlexGridSizer *fgSMDAtmosphere = new wxFlexGridSizer(6,3,5,5);

        wxStaticText *stSunColour = new wxStaticText(pnlSMDAtmosphere, wxID_ANY, wxT("Sun Colour"));
        btnSunColour = new wxButton(pnlSMDAtmosphere, IDBTN_SUN_COLOUR, wxT("Sun Colour"));
        pnlSunColourDisplay = new wxPanel(pnlSMDAtmosphere, -1);

        wxStaticText *stSkyColour = new wxStaticText(pnlSMDAtmosphere, wxID_ANY, wxT("Sky Colour"));
        btnSkyColour = new wxButton(pnlSMDAtmosphere, IDBTN_SKY_COLOUR, wxT("Sky Colour"));
        pnlSkyColourDisplay = new wxPanel(pnlSMDAtmosphere, -1);

        wxStaticText *stCloudColour = new wxStaticText(pnlSMDAtmosphere, wxID_ANY, wxT("Cloud Colour      "));
        btnCloudColour = new wxButton(pnlSMDAtmosphere, IDBTN_CLOUD_COLOUR, wxT("Cloud Colour"));
        pnlCloudColourDisplay = new wxPanel(pnlSMDAtmosphere, -1);

        wxStaticText *stCloudDensity = new wxStaticText(pnlSMDAtmosphere, wxID_ANY, wxT("Cloud Density"));
        tcCloudDensity = new wxTextCtrl(pnlSMDAtmosphere, IDTC_CLOUD_DENSITY, wxT("0.55"));
        wxPanel *pnlCloudDensityPlacehold = new wxPanel(pnlSMDAtmosphere, -1);

        wxStaticText *stFogColour = new wxStaticText(pnlSMDAtmosphere, wxID_ANY, wxT("Fog Colour"));
        btnFogColour = new wxButton(pnlSMDAtmosphere, IDBTN_FOG_COLOUR, wxT("Fog Colour"));
        pnlFogColourDisplay = new wxPanel(pnlSMDAtmosphere, -1);

        wxStaticText *stFogStart = new wxStaticText(pnlSMDAtmosphere, wxID_ANY, wxT("Fog Density"));
        tcFogStart = new wxTextCtrl(pnlSMDAtmosphere, IDTC_FOG_DENSITY, wxT("0.55"));
        wxPanel *pnlFogStartPlacehold = new wxPanel(pnlSMDAtmosphere, -1);

//Assemble atmospheric settings page///////////////////////////////////////////////////////////////

    fgSMDAtmosphere->Add(stSunColour, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDAtmosphere->Add(btnSunColour, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDAtmosphere->Add(pnlSunColourDisplay, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
        pnlSunColourDisplay->SetBackgroundColour(*colSun);
        pnlSunColourDisplay->Refresh();
    fgSMDAtmosphere->Add(stSkyColour, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDAtmosphere->Add(btnSkyColour, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDAtmosphere->Add(pnlSkyColourDisplay, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
        pnlSkyColourDisplay->SetBackgroundColour(*colSky);
        pnlSkyColourDisplay->Refresh();

    fgSMDAtmosphere->Add(stCloudColour, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDAtmosphere->Add(btnCloudColour, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDAtmosphere->Add(pnlCloudColourDisplay, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
        pnlCloudColourDisplay->SetBackgroundColour(*colCloud);
        pnlCloudColourDisplay->Refresh();
    fgSMDAtmosphere->Add(stCloudDensity, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDAtmosphere->Add(tcCloudDensity, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDAtmosphere->Add(pnlCloudDensityPlacehold, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);

    fgSMDAtmosphere->Add(stFogColour, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDAtmosphere->Add(btnFogColour, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDAtmosphere->Add(pnlFogColourDisplay, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
        pnlFogColourDisplay->SetBackgroundColour(*colFog);
        pnlFogColourDisplay->Refresh();
    fgSMDAtmosphere->Add(stFogStart, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDAtmosphere->Add(tcFogStart, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDAtmosphere->Add(pnlFogStartPlacehold, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);


////////////////////////////////////////////////////////////////////////////////////////////////////
//Lighting page, containing lighting and shadow info////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
    wxStaticBoxSizer *gsSMDLight = new wxStaticBoxSizer(wxVERTICAL, pnlSMDAtmosphere, wxT("Lighting Settings"));
    wxFlexGridSizer *fgSMDLight = new wxFlexGridSizer(6,3,5,5);

        wxStaticText *stGroundAmbientColour = new wxStaticText(pnlSMDAtmosphere, wxID_ANY, wxT("Ground Ambient"));
        btnGroundAmbientColour = new wxButton(pnlSMDAtmosphere, IDBTN_GROUNDAMBIENT_COLOUR, wxT("G A Colour"));
        pnlGroundAmbientColourDisplay = new wxPanel(pnlSMDAtmosphere, -1);

        wxStaticText *stGroundSunColour = new wxStaticText(pnlSMDAtmosphere, wxID_ANY, wxT("Ground Sun"));
        btnGroundSunColour = new wxButton(pnlSMDAtmosphere, IDBTN_GROUNDSUN_COLOUR, wxT("G S Colour"));
        pnlGroundSunColourDisplay = new wxPanel(pnlSMDAtmosphere, -1);

        wxStaticText *stGroundShadowDensity = new wxStaticText(pnlSMDAtmosphere, wxID_ANY, wxT("Ground Shadow Density"));
        tcGroundShadowDensity = new wxTextCtrl(pnlSMDAtmosphere, IDTC_GROUND_SHADOW_DENSITY, wxT("0.55"));
        wxPanel *pnlGroundShadowDensityPlacehold = new wxPanel(pnlSMDAtmosphere, -1);

        wxStaticText *stUnitAmbientColour = new wxStaticText(pnlSMDAtmosphere, wxID_ANY, wxT("Unit Ambient"));
        btnUnitAmbientColour = new wxButton(pnlSMDAtmosphere, IDBTN_UNITAMBIENT_COLOUR, wxT("U A Colour"));
        pnlUnitAmbientColourDisplay = new wxPanel(pnlSMDAtmosphere, -1);

        wxStaticText *stUnitSunColour = new wxStaticText(pnlSMDAtmosphere, wxID_ANY, wxT("Unit Sun"));
        btnUnitSunColour = new wxButton(pnlSMDAtmosphere, IDBTN_UNITSUN_COLOUR, wxT("U S Colour"));
        pnlUnitSunColourDisplay = new wxPanel(pnlSMDAtmosphere, -1);

        wxStaticText *stUnitShadowDensity = new wxStaticText(pnlSMDAtmosphere, wxID_ANY, wxT("Unit Shadow Density"));
        tcUnitShadowDensity = new wxTextCtrl(pnlSMDAtmosphere, IDTC_UNIT_SHADOW_DENSITY, wxT("0.55"));
        wxPanel *pnlUnitShadowDensityPlacehold = new wxPanel(pnlSMDAtmosphere, -1);

    fgSMDLight->Add(stGroundAmbientColour, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDLight->Add(btnGroundAmbientColour, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDLight->Add(pnlGroundAmbientColourDisplay, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    pnlGroundAmbientColourDisplay->SetBackgroundColour(*colGroundAmbient);

    fgSMDLight->Add(stGroundSunColour, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDLight->Add(btnGroundSunColour, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDLight->Add(pnlGroundSunColourDisplay, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    pnlGroundSunColourDisplay->SetBackgroundColour(*colGroundSun);
    fgSMDLight->Add(stGroundShadowDensity, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDLight->Add(tcGroundShadowDensity, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDLight->Add(pnlGroundShadowDensityPlacehold, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);

    fgSMDLight->Add(stUnitAmbientColour, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDLight->Add(btnUnitAmbientColour, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDLight->Add(pnlUnitAmbientColourDisplay, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    pnlUnitAmbientColourDisplay->SetBackgroundColour(*colUnitAmbient);

    fgSMDLight->Add(stUnitSunColour, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDLight->Add(btnUnitSunColour, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDLight->Add(pnlUnitSunColourDisplay, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    pnlUnitSunColourDisplay->SetBackgroundColour(*colUnitSun);
    fgSMDLight->Add(stUnitShadowDensity, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDLight->Add(tcUnitShadowDensity, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    fgSMDLight->Add(pnlUnitShadowDensityPlacehold, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);

    gsSMDAtmosphere->Add(fgSMDAtmosphere, 1, wxEXPAND, 0);
    gsSMDLight->Add(fgSMDLight, 1, wxEXPAND, 0);

    hboxSMDAtmosphere->Add(gsSMDAtmosphere, 1, wxEXPAND, 0);
    hboxSMDAtmosphere->Add(gsSMDLight, 1, wxEXPAND, 0);

////////////////////////////////////////////////////////////////////////////////////////////////////
//Sun Direction graphical interface/////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
    wxStaticBoxSizer *gsSunDirection = new wxStaticBoxSizer(wxVERTICAL, pnlSMDAtmosphere, wxT("SunDirection"));
    wxFlexGridSizer *fgSunDirection = new wxFlexGridSizer(1,1,5,5);

    pnlSunDirection = new wxPanel(pnlSMDAtmosphere, -1);
    pnlSunDirection->SetBackgroundColour(wxColour(255,0,0));

    fgSunDirection->Add(pnlSunDirection, 1, wxEXPAND, 0);
    gsSunDirection->Add(fgSunDirection, 1, wxEXPAND, 0);
    hboxSunDirection->Add(gsSunDirection, 1, wxEXPAND, 0);

    vboxSMDAtmosphereAndLight->Add(hboxSMDAtmosphere, 1, wxEXPAND, 0);
    vboxSMDAtmosphereAndLight->Add(hboxSunDirection, 1, wxEXPAND, 0);
////////////////////////////////////////////////////////////////////////////////////////////////////
//Water page, containg water colour and light info//////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
    pnlSMDWater = new wxPanel(nbSMD, -1);
    wxFlexGridSizer *fgSMDWater = new wxFlexGridSizer(0,1,5,5);
//water base colour
    wxStaticBoxSizer *gboxSMDWater = new wxStaticBoxSizer(wxVERTICAL, pnlSMDWater, wxT("Water Simple"));
    wxGridSizer* gsSMDWater = new wxFlexGridSizer(0,3,5,5);

    wxStaticText *stWaterBaseColour = new wxStaticText(pnlSMDWater, wxID_ANY, wxT("WaterBase Colour"));
    btnWaterBase = new wxButton(pnlSMDWater, IDBTN_WATERBASE_COLOUR, wxT("Water Base"));
    pnlWaterBaseColourDisplay = new wxPanel(pnlSMDWater, -1);
    wxStaticText *stWaterMinColour = new wxStaticText(pnlSMDWater, wxID_ANY, wxT("WaterMin Colour"));
    btnWaterMin = new wxButton(pnlSMDWater, IDBTN_WATERMIN_COLOUR, wxT("Water Min"));
    pnlWaterMinColourDisplay = new wxPanel(pnlSMDWater, -1);
    wxStaticText *stWaterAbsorbColour = new wxStaticText(pnlSMDWater, wxID_ANY, wxT("WaterAbsorb Colour"));
    btnWaterAbsorb = new wxButton(pnlSMDWater, IDBTN_WATERABSORB_COLOUR, wxT("Water Absorb"));
    pnlWaterAbsorbColourDisplay = new wxPanel(pnlSMDWater, -1);

//Assemble water settings page///////////////////////////////////////////////////////////////////

    gsSMDWater->Add(stWaterBaseColour, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    gsSMDWater->Add(btnWaterBase, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    gsSMDWater->Add(pnlWaterBaseColourDisplay, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    pnlWaterBaseColourDisplay->SetBackgroundColour(*colWaterBase);

    gsSMDWater->Add(stWaterMinColour, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    gsSMDWater->Add(btnWaterMin, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    gsSMDWater->Add(pnlWaterMinColourDisplay, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    pnlWaterMinColourDisplay->SetBackgroundColour(*colWaterMin);

    gsSMDWater->Add(stWaterAbsorbColour, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    gsSMDWater->Add(btnWaterAbsorb, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    gsSMDWater->Add(pnlWaterAbsorbColourDisplay, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
    pnlWaterAbsorbColourDisplay->SetBackgroundColour(*colWaterAbsorb);

    gboxSMDWater->Add(gsSMDWater, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP,5);
    fgSMDWater->Add(gboxSMDWater, 1, wxEXPAND, 0);
///////////////////////////////////////////////
    pnlSMDGeneral->SetSizer(vboxSMDGeneralMain);
    pnlSMDAtmosphere->SetSizer(vboxSMDAtmosphereAndLight);
    pnlSMDWater->SetSizer(fgSMDWater);


    nbSMD->AddPage(pnlSMDGeneral, wxT("General"), true);
    nbSMD->AddPage(pnlSMDAtmosphere, wxT("Atmosphere"), true);
    nbSMD->AddPage(pnlSMDWater, wxT("Water"), true);

//Butons for saving the SMD file///////////////////////////////////////////////////////////////////
    btnSMDSave = new wxButton( pnlSMD, IDBTN_SMD_SAVE, wxT("Save SMD"));
    wxBoxSizer *hboxSMDSave = new wxBoxSizer(wxHORIZONTAL);
    hboxSMDSave->Add(btnSMDSave, 0,0,0);

    box->Add( nbSMD, 1, wxEXPAND, 0 );
    box->Add( hboxSMDSave, 0, wxEXPAND, 0);

    pnlSMD->SetSizer( box );
    pnlSMD->Layout();

    notebook->ChangeSelection(1);
    nbSMD->ChangeSelection(0);
////////////////////////////////////////////////////////////////////////////////////////////////////
//Connect the controls to their appropriate functions///////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//Mouse//
    Connect(wxID_ANY, wxEVT_LEFT_DOWN, wxCommandEventHandler(Frontend::OnMouseEvent));
//Menu Options//
    Connect(IDMENU_NEW, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Frontend::OnClickNew));
    Connect(IDMENU_SAVE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Frontend::OnClickSaveProject));
    Connect(IDMENU_OPEN, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Frontend::OnClickLoadProject));

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
    Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Frontend::OnClickExit));
    Connect(IDBTN_SMD_SAVE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Frontend::OnClickSMDSave));
//Player Count//
    Connect(IDTC_TEAM_COUNT, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Frontend::OnChangeTeamCount));
//Preview controls//
    Connect(IDRBX_PREVIEW, wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler(Frontend::OnChangePreview));
//Colours smd Atmosphere
    Connect(IDBTN_SUN_COLOUR, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Frontend::OnClickSunColour));
    Connect(IDBTN_SKY_COLOUR, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Frontend::OnClickSkyColour));
    Connect(IDBTN_CLOUD_COLOUR, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Frontend::OnClickCloudColour));
    Connect(IDBTN_FOG_COLOUR, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Frontend::OnClickFogColour));
    Connect(IDBTN_GROUNDAMBIENT_COLOUR, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Frontend::OnClickGroundAmbientColour));
    Connect(IDBTN_GROUNDSUN_COLOUR, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Frontend::OnClickGroundSunColour));
    Connect(IDBTN_UNITAMBIENT_COLOUR, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Frontend::OnClickUnitAmbientColour));
    Connect(IDBTN_UNITSUN_COLOUR, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Frontend::OnClickUnitSunColour));

    Connect(IDTC_CLOUD_DENSITY, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Frontend::OnChangeCloudDensityText));
    Connect(IDTC_FOG_DENSITY, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Frontend::OnChangeFogStartText));
    Connect(IDTC_GROUND_SHADOW_DENSITY, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Frontend::OnChangeGroundShadowDensityText));
    Connect(IDTC_GROUND_SHADOW_DENSITY, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Frontend::OnChangeUnitShadowDensityText));

    Connect(IDBTN_WATERBASE_COLOUR, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Frontend::OnClickWaterBaseColour));
    Connect(IDBTN_WATERMIN_COLOUR, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Frontend::OnClickWaterMinColour));
    Connect(IDBTN_WATERABSORB_COLOUR, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Frontend::OnClickWaterAbsorbColour));

    Centre();
}

void Frontend::OnClickExit(wxCommandEvent& event)
{
    Close(true);
}

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
        tcOtherOptions->SetValue("");
        tcOtherOptions->Enable(true);
    }
    else
    {
        tcOtherOptions->SetValue("Additional Options");
        tcOtherOptions->Enable(false);
    }
    bOtherEnable = !bOtherEnable;
}
