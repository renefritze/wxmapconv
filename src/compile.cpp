#include "wxwfrontend.h"

void Frontend::OnClickCompile(wxCommandEvent& event)
{
    wxString command;
    command.append(wxT("MapConv"));

    if(bLowpass)
        command.append(wxT(" -l"));
    if(bInvert)
        command.append(wxT(" -i"));
    command.append(wxT(" -c ") + tcCompression->GetValue());//compression
    command.append(wxT(" -x ") + tcMax->GetValue());        //height maximum
    command.append(wxT(" -n ") + tcMin->GetValue());        //height minimum

    command.append(wxT(" -o \"") + tcOutput->GetValue() + wxT("\""));     //output
    command.append(wxT(" -t \"") + tcTexture->GetValue() + wxT("\""));    //texture
    command.append(wxT(" -a \"") + tcHeight->GetValue() + wxT("\""));     //heightmap
    command.append(wxT(" -m \"") + tcMetal->GetValue() + wxT("\""));      //metalmap
    command.append(wxT(" -g \"") + tcGeovent->GetValue() + wxT("\""));    //geoventmap

    if(bFeatureEnable)
    {
        command.append(wxT(" -f \"") + tcFeature->GetValue() + wxT("\""));
        command.append(wxT(" -j \"") + tcFeatureList->GetValue() + wxT("\""));
    }
    if(bTypemapEnable)
    {
        command.append(wxT(" -y \"") + tcType->GetValue() + wxT("\""));
    }
    if(bOtherEnable)
    {
        command.append(wxT(" ") + tcOtherOptions->GetValue());
    }
    int iQuality = rbxQuality->GetSelection();
    if(iQuality == 0)
    {
        command.append(wxT(" -z \"nvdxt.exe -dxt1a -nmips 4 -quick -file\""));
    }
    else if(iQuality == 1)
    {
        command.append(wxT(" -q "));
    }
    else if(iQuality == 2)
    {
    }
    else if(iQuality == 3)
    {
        command.append(wxT(" -z \"nvdxt.exe -dxt1a -nmips 4 -Sinc -quality_highest -file\""));
    }
    system(command.c_str());
}
