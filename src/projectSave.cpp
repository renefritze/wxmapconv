#include "wxwfrontend.h"

void Frontend::OnClickSaveProject(wxCommandEvent& event)
{
    if(!bSaved)
    {
        wxFileDialog* saveAsFileDialog = new wxFileDialog(this, wxT("Save Project As..."), wxT(""), wxT(""), wxT("*.mprj"), wxFD_SAVE);
        if (openFileDialog->ShowModal() == wxID_OK)
        {
            projectPath = openFileDialog->GetPath();
            SaveProject();
        }
        delete saveAsFileDialog;
    }
    else
        SaveProject();
}

void Frontend::OnClickSaveProjectAs(wxCommandEvent& event)
{
    wxFileDialog* saveAsFileDialog = new wxFileDialog(this, wxT("Save Project As..."), wxT(""), wxT(""), wxT("*.mprj"), wxFD_SAVE);
    if (openFileDialog->ShowModal() == wxID_OK)
    {
        projectPath = openFileDialog->GetPath();
        SaveProject();
    }
    delete saveAsFileDialog;
}


void Frontend::SaveProject(void)
{
    wxFile file;

    file.Open(projectPath, wxFile::write);

    file.Write(wxT("heightmap=") + tcHeight->GetValue() + wxT(";\n"));
    file.Write(wxT("texture=") + tcTexture->GetValue() + wxT(";\n"));
    file.Write(wxT("metal=") + tcMetal->GetValue() + wxT(";\n"));
    file.Write(wxT("enablefeaturemap="));
        if(cbFeatureEnable->GetValue()) file.Write(wxT("true;\n"));
        else                            file.Write(wxT("false;\n"));
    file.Write(wxT("featuremap=") + tcFeature->GetValue() + wxT(";\n"));
    file.Write(wxT("featurelist=") + tcFeatureList->GetValue() + wxT(";\n"));
    file.Write(wxT("enabletypemap="));
        if(cbTypeEnable->GetValue()) file.Write(wxT("true;\n"));
        else                         file.Write(wxT("false;\n"));
    file.Write(wxT("typemap=") + tcType->GetValue() + wxT(";\n"));
    file.Write(wxT("geovent=") + tcGeovent->GetValue() + wxT(";\n"));
    file.Write(wxT("additionaloptions=") + tcOtherOptions->GetValue() + wxT(";\n"));
    file.Write(wxT("output=") + tcOutput->GetValue() + wxT(";\n"));
    file.Write(wxT("maxheight=") + tcMax->GetValue() + wxT(";\n"));
    file.Write(wxT("minheight=") + tcMin->GetValue() + wxT(";\n"));
    file.Write(wxT("lowpass="));
        if(cbLowpass->GetValue()) file.Write(wxT("true;\n"));
        else                      file.Write(wxT("false;\n"));
    file.Write(wxT("invert="));
        if(cbInvert->GetValue()) file.Write(wxT("true;\n"));
        else                     file.Write(wxT("false;\n"));
    file.Write(wxT("quality=") + wxString::Format(wxT("%i"),rbxQuality->GetSelection()) + wxT(";\n"));
    file.Write(wxT("compression=") + tcCompression->GetValue() + wxT(";\n"));
    file.Write(wxT("rotatefeatures=") + tcFeatureRotate->GetValue() + wxT(";\n"));
    file.Write(wxT("heightmaploaded="));
        if(bHeightmapLoaded)    file.Write(wxT("true;\n"));
        else                    file.Write(wxT("false;\n"));
    file.Write(wxT("textureloaded="));
        if(bTextureLoaded) file.Write(wxT("true;\n"));
        else               file.Write(wxT("false;\n"));
    file.Write(wxT("metalloaded="));
        if(bMetalLoaded)   file.Write(wxT("true;\n"));
        else               file.Write(wxT("false;\n"));
    file.Write(wxT("featureloaded="));
        if(bFeatureLoaded) file.Write(wxT("true;\n"));
        else               file.Write(wxT("false;\n"));
    file.Write(wxT("typemaploaded="));
        if(bTypemapLoaded) file.Write(wxT("true;\n"));
        else               file.Write(wxT("false;\n"));

    file.Close();
    bSaved = true;
}
