#include "wxwfrontend.h"

void Frontend::OnClickCompile(wxCommandEvent& /*event*/)
{
    wxString command;
	command.append(_T("MapConv"));
    if(bLowpass)
		command.append(_T(" -l"));
    if(bInvert)
		command.append(_T(" -i"));
	command.append(_T(" -c ") + tcCompression->GetValue());//compression
	command.append(_T(" -x ") + tcMax->GetValue());        //height maximum
	command.append(_T(" -n ") + tcMin->GetValue());        //height minimum

	command.append(_T(" -o \"") + tcOutput->GetValue() + _T("\""));     //output
	command.append(_T(" -t \"") + tcTexture->GetValue() + _T("\""));    //texture
	command.append(_T(" -a \"") + tcHeight->GetValue() + _T("\""));     //heightmap
	command.append(_T(" -m \"") + tcMetal->GetValue() + _T("\""));      //metalmap
	command.append(_T(" -g \"") + tcGeovent->GetValue() + _T("\""));    //geoventmap

    if(bFeatureEnable)
    {
		command.append(_T(" -f \"") + tcFeature->GetValue() + _T("\""));
		command.append(_T(" -j \"") + tcFeatureList->GetValue() + _T("\""));
    }
    if(bTypemapEnable)
    {
		command.append(_T(" -y \"") + tcType->GetValue() + _T("\""));
    }
    if(bOtherEnable)
    {
		command.append(_T(" ") + tcOtherOptions->GetValue());
    }
    int iQuality = rbxQuality->GetSelection();
    if(iQuality == 0)
    {
		command.append(_T(" -z \"nvdxt.exe -dxt1a -nmips 4 -quick -file\""));
    }
    else if(iQuality == 1)
    {
		command.append(_T(" -q "));
    }
    else if(iQuality == 2)
    {
    }
    else if(iQuality == 3)
    {
		command.append(_T(" -z \"nvdxt.exe -dxt1a -nmips 4 -Sinc -quality_highest -file\""));
    }
    //tcHeight->SetValue(command);
	wxArrayString output;
	long return_value = wxExecute( command, output, wxEXEC_SYNC );
}
