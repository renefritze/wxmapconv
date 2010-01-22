#include "wxwfrontend.h"

void Frontend::OnClickCompile(wxCommandEvent& event)
{
    wxString command;
    command.append("MapConv");
    if(bLowpass)
        command.append(" -l");
    if(bInvert)
        command.append(" -i");
    command.append(" -c " + tcCompression->GetValue());//compression
    command.append(" -x " + tcMax->GetValue());        //height maximum
    command.append(" -n " + tcMin->GetValue());        //height minimum

    command.append(" -o \"" + tcOutput->GetValue() + "\"");     //output
    command.append(" -t \"" + tcTexture->GetValue() + "\"");    //texture
    command.append(" -a \"" + tcHeight->GetValue() + "\"");     //heightmap
    command.append(" -m \"" + tcMetal->GetValue() + "\"");      //metalmap
    command.append(" -g \"" + tcGeovent->GetValue() + "\"");    //geoventmap

    if(bFeatureEnable)
    {
        command.append(" -f \"" + tcFeature->GetValue() + "\"");
        command.append(" -j \"" + tcFeatureList->GetValue() + "\"");
    }
    if(bTypemapEnable)
    {
        command.append(" -y \"" + tcType->GetValue() + "\"");
    }
    if(bOtherEnable)
    {
        command.append(" " + tcOtherOptions->GetValue());
    }
    int iQuality = rbxQuality->GetSelection();
    if(iQuality == 0)
    {
        command.append(" -z \"nvdxt.exe -dxt1a -nmips 4 -quick -file\"");
    }
    else if(iQuality == 1)
    {
        command.append(" -q ");
    }
    else if(iQuality == 2)
    {
    }
    else if(iQuality == 3)
    {
        command.append(" -z \"nvdxt.exe -dxt1a -nmips 4 -Sinc -quality_highest -file\"");
    }
    //tcHeight->SetValue(command);
    system(command.c_str());
}