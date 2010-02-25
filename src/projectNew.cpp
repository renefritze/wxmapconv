#include "wxwfrontend.h"

void Frontend::OnClickNew(wxCommandEvent& event){
    wxFileDialog* newfiledialog = new wxFileDialog(this, wxT("Save Project"), wxT(""), wxT(""), wxT("*.mprj"), wxFD_SAVE);
    if(newfiledialog->ShowModal() == wxID_OK)
    {
        projectPath = newfiledialog->GetPath();
        sProjectName = newfiledialog->GetFilename();
        this->SetTitle(wxT("Mapconv Frontend - ") + sProjectName);
        setDefaultsMapconv();
        setDefaultsSMD();

        SaveProject();
    }
    delete newfiledialog;
}

void Frontend::setDefaultsMapconv(void){
//MapConv Options//
    bLowpass = true;
    bInvert = true;
    bFeatureEnable = false;
    bTypemapEnable = false;
    bOtherEnable = false;
    bOtherFirstTime = true;
    bTextureLoaded = false;

    cbLowpass->SetValue(bLowpass);
    cbInvert->SetValue(bInvert);
    btnFeature->Enable(bFeatureEnable);
    tcFeature->Enable(bFeatureEnable);
    btnFeatureList->Enable(bFeatureEnable);
    tcFeatureList->Enable(bFeatureEnable);
    btnType->Enable(bTypemapEnable);
    tcType->Enable(bTypemapEnable);
    cbOtherOptionsEnable->SetValue(bOtherEnable);
    tcOtherOptions->Enable(bOtherEnable);

    tcHeight->SetValue(wxT("heightmap.bmp"));
    tcTexture->SetValue(wxT("texture.bmp"));
    tcMetal->SetValue(wxT("metal.bmp"));
    tcFeature->SetValue(wxT("feature.bmp"));
    tcFeatureList->SetValue(wxT("featurelist.txt"));
    tcType->SetValue(wxT("typemap.bmp"));
    tcGeovent->SetValue(wxT("geovent.bmp"));
    tcOutput->SetValue(wxT("output.smf"));
    tcOtherOptions->SetValue(wxT(""));

    if(bHeightmapLoaded)
        delete bmHeightmap;
    if(bTextureLoaded)
        delete bmTexture;
    if(bMetalLoaded)
        delete bmMetal;
    if(bFeatureLoaded)
        delete bmFeature;
    if(bTypemapLoaded)
        delete bmTypemap;


    sbmPreviewBig->SetBitmap(wxBitmap(wxBITMAP(IDBM_PREVIEW_BIG_PLACEHOLDER)));
}


void Frontend::setDefaultsSMD(void){
//Atmospheric Options//
    colSun->Set(255, 190, 20);
    colSky->Set(20, 20, 240);
    colCloud->Set(150, 150, 150);
    colFog->Set(100, 100, 100);
//Light Options//
    colGroundAmbient->Set(127, 127, 127);
    colGroundSun->Set(127, 127, 127);
    colUnitAmbient->Set(127, 127, 127);
    colUnitSun->Set(127, 127, 127);
//Water Options//
    colWaterBase->Set(100, 150, 200);
    colWaterMin->Set(10, 10, 30);
    colWaterAbsorb->Set(4, 4, 2);
}
