#include "resources.h"

class Frontend : public wxFrame{
    public:
        Frontend(const wxString& title);

    private:
        void setDefaultsMapconv(void);
        void setDefaultsSMD(void);

        void SaveProject(void);
        void OpenSMD(void);

        void LoadImage(int type);

        void OnClickNew(wxCommandEvent& event);
        void OnClickLoadProject(wxCommandEvent& event);
        void OnClickSaveProject(wxCommandEvent& event);
        void OnClickSaveProjectAs(wxCommandEvent& event);

        void OnChangePreview(wxCommandEvent& event);

        void OnToggleLowpass(wxCommandEvent& event);
        void OnToggleInvert(wxCommandEvent& event);
        void OnToggleFeatureEnable(wxCommandEvent& event);
        void OnToggleTypemapEnable(wxCommandEvent& event);
        void OnToggleOtherEnable(wxCommandEvent& event);

        void OnClickCompile(wxCommandEvent& event);
        void OnClickExit(wxCommandEvent& event);
        void OnClickSMDSave(wxCommandEvent& event);

        void OnOpenHeight(wxCommandEvent& event);
        void OnOpenTexture(wxCommandEvent& event);
        void OnOpenMetal(wxCommandEvent& event);
        void OnOpenFeature(wxCommandEvent& event);
        void OnOpenFeatureList(wxCommandEvent& event);
        void OnOpenType(wxCommandEvent& event);
        void OnOpenGeovent(wxCommandEvent& event);
        void OnOpenOutput(wxCommandEvent& event);

        void OnChangeTeamCount(wxCommandEvent& event);

        void OnClickSunColour(wxCommandEvent& event);
        void OnClickSkyColour(wxCommandEvent& event);
        void OnClickCloudColour(wxCommandEvent& event);
        void OnClickFogColour(wxCommandEvent& event);
        void OnChangeCloudDensityText(wxCommandEvent& event);
        void OnChangeFogStartText(wxCommandEvent& event);

        void OnClickGroundAmbientColour(wxCommandEvent& event);
        void OnClickGroundSunColour(wxCommandEvent& event);
        void OnClickUnitAmbientColour(wxCommandEvent& event);
        void OnClickUnitSunColour(wxCommandEvent& event);
        void OnChangeGroundShadowDensityText(wxCommandEvent& event);
        void OnChangeUnitShadowDensityText(wxCommandEvent& event);

        void OnMouseEvent(wxCommandEvent& event);

        void OnClickWaterBaseColour(wxCommandEvent& event);
        void OnClickWaterMinColour(wxCommandEvent& event);
        void OnClickWaterAbsorbColour(wxCommandEvent& event);

        bool bSaved;

        bool bLowpass;
        bool bInvert;
        bool bFeatureEnable;
        bool bTypemapEnable;
        bool bOtherEnable;
        bool bOtherFirstTime;

        bool bTextureLoaded;
        bool bHeightmapLoaded;
        bool bMetalLoaded;
        bool bFeatureLoaded;
        bool bTypemapLoaded;

        wxString sProjectName;
        wxString path;
        wxString projectPath;

        int iOldTeamCount;

        wxColourDialog *cldColour;
        wxColourData *colourData;
        wxColour *tempColour;

        wxButton *btnSunColour;
        wxButton *btnSkyColour;
        wxButton *btnCloudColour;
        wxButton *btnFogColour;
        wxPanel *pnlSunColourDisplay;
        wxPanel *pnlSkyColourDisplay;
        wxPanel *pnlCloudColourDisplay;
        wxTextCtrl *tcCloudDensity;
        wxPanel *pnlFogColourDisplay;
        wxTextCtrl *tcFogStart;

        wxButton *btnGroundAmbientColour;
        wxButton *btnGroundSunColour;
        wxButton *btnUnitAmbientColour;
        wxButton *btnUnitSunColour;
        wxPanel *pnlGroundAmbientColourDisplay;
        wxTextCtrl *tcGroundShadowDensity;
        wxPanel *pnlGroundSunColourDisplay;
        wxPanel *pnlUnitAmbientColourDisplay;
        wxPanel *pnlUnitSunColourDisplay;
        wxTextCtrl *tcUnitShadowDensity;


        wxColour *colSun;
        wxColour *colSky;
        wxColour *colCloud;
        wxColour *colFog;

        wxColour *colGroundAmbient;
        wxColour *colGroundSun;
        wxColour *colUnitAmbient;
        wxColour *colUnitSun;
        wxPanel *pnlSunDirection;

        wxColour *colWaterBase;
        wxColour *colWaterMin;
        wxColour *colWaterAbsorb;

        wxMenuBar *menubar;
        wxMenu *mnFile;
        wxMenu *mnAbout;

        wxNotebook *notebook;
        wxNotebook *nbSMD;
        wxPanel *pnlMapConv;
        wxPanel *pnlPreview;
        wxPanel *pnlSMD;
        //Map Compiler panel//////////////////////////////////////////////////////////
        wxFileDialog *openFileDialog;
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
        wxButton *btnSMDSave;
        //preveiew panel//////////////////////////////////////////////////////////////
        wxStaticBitmap *sbmPreviewBig;
        wxRadioBox *rbxPreview;
        wxBitmap *bmHeightmap;
        wxBitmap *bmTexture;
        wxBitmap *bmMetal;
        wxBitmap *bmFeature;
        wxBitmap *bmTypemap;
        wxImage *image;
        //smd creater panel///////////////////////////////////////////////////////////
        wxPanel *pnlSMDGeneral;
        wxPanel *pnlSMDAtmosphere;

        wxTextCtrl *tcDescription;
        wxTextCtrl *tcGravity;
        wxTextCtrl *tcMapHardness;
        wxTextCtrl *tcMaxMetal;
        wxTextCtrl *tcExtractorRadius;
        wxTextCtrl *tcTidalStrength;
        wxTextCtrl *tcMaxWind;
        wxTextCtrl *tcMinWind;
        wxTextCtrl *tcMaxHeight;
        wxTextCtrl *tcMinHeight;

        wxPanel *pnlSMDLight;
        wxTextCtrl *tcSunDirX;
        wxTextCtrl *tcSunDirY;
        wxTextCtrl *tcSunDirZ;

        wxPanel *pnlSMDWater;
            wxButton *btnWaterBase;
            wxPanel *pnlWaterBaseColourDisplay;
            wxButton *btnWaterMin;
            wxPanel *pnlWaterMinColourDisplay;
            wxButton *btnWaterAbsorb;
            wxPanel *pnlWaterAbsorbColourDisplay;

        wxTextCtrl *tcTeam1X;
        wxTextCtrl *tcTeam1Y;
        wxTextCtrl *tcTeam2X;
        wxTextCtrl *tcTeam2Y;
        wxTextCtrl *tcTeam3X;
        wxTextCtrl *tcTeam3Y;
        wxTextCtrl *tcTeam4X;
        wxTextCtrl *tcTeam4Y;
        wxTextCtrl *tcTeam5X;
        wxTextCtrl *tcTeam5Y;
        wxTextCtrl *tcTeam6X;
        wxTextCtrl *tcTeam6Y;
        wxTextCtrl *tcTeam7X;
        wxTextCtrl *tcTeam7Y;
        wxTextCtrl *tcTeam8X;
        wxTextCtrl *tcTeam8Y;

        wxTextCtrl *tcTeamCount;
};

