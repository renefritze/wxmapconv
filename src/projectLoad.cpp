#include "wxwfrontend.h"

void Frontend::OnClickLoadProject(wxCommandEvent& event)
{
    wxTextFile *file;

    wxString str;
    wxString name;
    wxString value;

    int start, length;

    wxFileDialog *loadFileDialog = new wxFileDialog(this);
    if (openFileDialog->ShowModal() == wxID_OK)
    {
        file = new wxTextFile(openFileDialog->GetPath());
        if(file->Open())
        {
            for ( str = file->GetFirstLine(); !file->Eof(); str = file->GetNextLine() )
            {
                start = 0;
                length = str.Find(wxT("="));
                name = str.Mid(start, length);

                start = str.Find(wxT("=")) + 1;
                length = str.Find(wxT(";")) - start;
                value = str.Mid(start, length);

                if(name == wxT("heightmap"))
                    tcHeight->SetValue(value);
                else if(name == wxT("texture"))
                    tcTexture->SetValue(value);
                else if(name == wxT("metal"))
                    tcMetal->SetValue(value);
                else if(name == wxT("enablefeaturemap")){
                    if(value == wxT("true"))
                        cbFeatureEnable->SetValue(true);
                    else
                        cbFeatureEnable->SetValue(false);
                }
                else if(name == wxT("featuremap"))
                    tcFeature->SetValue(value);
                else if(name == wxT("featurelist"))
                    tcFeatureList->SetValue(value);
                else if(name == wxT("enabletypemap")){
                    if(value == wxT("true"))
                        cbTypeEnable->SetValue(true);
                    else
                        cbTypeEnable->SetValue(false);
                }
                else if(name == wxT("typemap"))
                    tcType->SetValue(value);
                else if(name == wxT("geovent"))
                    tcGeovent->SetValue(value);
                else if(name == wxT("additionaloptions"))
                    tcOtherOptions->SetValue(value);
                else if(name == wxT("output"))
                    tcOutput->SetValue(value);
                else if(name == wxT("maxheight"))
                    tcMax->SetValue(value);
                else if(name == wxT("minheight"))
                    tcMin->SetValue(value);
                else if(name == wxT("lowpass")){
                    if(value == wxT("true"))
                        cbLowpass->SetValue(true);
                    else
                        cbLowpass->SetValue(false);
                }
                else if(name == wxT("invert")){
                    if(value == wxT("true"))
                        cbInvert->SetValue(true);
                    else
                        cbInvert->SetValue(false);
                }
                else if(name == wxT("quality"))
                    rbxQuality->SetSelection(wxAtoi(value));
                else if(name == wxT("compression"))
                    tcCompression->SetValue(value);
                else if(name == wxT("rotatefeatures"))
                    tcFeatureRotate->SetValue(value);
                else if(name == wxT("heightmaploaded")){
                    if(value == wxT("true")){
                        bHeightmapLoaded=true;
                        path = tcHeight->GetValue();
                        LoadImage(ID_HEIGHT);
                    }
                    else    bHeightmapLoaded=false;
                }
                else if(name == wxT("textureloaded")){
                    if(value == wxT("true")){
                        bTextureLoaded=true;
                        path = tcTexture->GetValue();
                        LoadImage(ID_TEXTURE);
                    }
                    else    bTextureLoaded=false;
                }
                else if(name == wxT("metalloaded")){
                    if(value == wxT("true")){
                        bMetalLoaded=true;
                        path = tcMetal->GetValue();
                        LoadImage(ID_METAL);
                    }
                    else    bMetalLoaded=false;
                }
                else if(name == wxT("featureloaded")){
                    if(value == wxT("true")){
                        bFeatureLoaded=true;
                        path = tcFeature->GetValue();
                        LoadImage(ID_FEATURE);
                    }
                    else    bFeatureLoaded=false;
                }

                else if(name == wxT("typemaploaded")){
                    if(value == wxT("true")){
                        bTypemapLoaded=true;
                        path = tcType->GetValue();
                        LoadImage(ID_TYPE);
                    }
                    else    bTypemapLoaded=false;
                }
                else{}//error value not found
            }

            file->Close();
        }
    }
    delete loadFileDialog;
    bSaved = true;
}
