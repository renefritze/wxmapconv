#include "wxwfrontend.h"

void Frontend::OnClickSunColour(wxCommandEvent& event)
{
    cldColour = new wxColourDialog(this);
    colourData = new wxColourData;
    if(cldColour->ShowModal() == wxID_OK)
    {
        *colourData = cldColour->GetColourData();
        *colSun = colourData->GetColour();
        pnlSunColourDisplay->SetBackgroundColour(*colSun);
        pnlSunColourDisplay->Refresh();
    }
    delete cldColour;
    delete colourData;
}
void Frontend::OnClickSkyColour(wxCommandEvent& event)
{
    cldColour = new wxColourDialog(this);
    colourData = new wxColourData;
    if(cldColour->ShowModal() == wxID_OK)
    {
        *colourData = cldColour->GetColourData();
        *colSky = colourData->GetColour();
        pnlSkyColourDisplay->SetBackgroundColour(*colSky);
        pnlSkyColourDisplay->Refresh();
    }
    delete cldColour;
    delete colourData;
}
void Frontend::OnClickCloudColour(wxCommandEvent& event)
{
    cldColour = new wxColourDialog(this);
    colourData = new wxColourData;
    if(cldColour->ShowModal() == wxID_OK)
    {
        *colourData = cldColour->GetColourData();
        *colCloud = colourData->GetColour();
        pnlCloudColourDisplay->SetBackgroundColour(*colCloud);
        pnlCloudColourDisplay->Refresh();
    }
    delete cldColour;
    delete colourData;
}
void Frontend::OnClickFogColour(wxCommandEvent& event)
{
    cldColour = new wxColourDialog(this);
    colourData = new wxColourData;
    if(cldColour->ShowModal() == wxID_OK)
    {
        *colourData = cldColour->GetColourData();
        *colFog = colourData->GetColour();
        pnlFogColourDisplay->SetBackgroundColour(*colFog);
        pnlFogColourDisplay->Refresh();
    }
    delete cldColour;
    delete colourData;
}
void Frontend::OnChangeCloudDensityText(wxCommandEvent& event){
}
void Frontend::OnChangeFogStartText(wxCommandEvent& event){
}



void Frontend::OnClickGroundAmbientColour(wxCommandEvent& event)
{
    cldColour = new wxColourDialog(this);
    colourData = new wxColourData;
    if(cldColour->ShowModal() == wxID_OK)
    {
        *colourData = cldColour->GetColourData();
        *colGroundAmbient = colourData->GetColour();
        pnlGroundAmbientColourDisplay->SetBackgroundColour(*colGroundAmbient);
        pnlGroundAmbientColourDisplay->Refresh();
    }
    delete cldColour;
    delete colourData;
}
void Frontend::OnClickGroundSunColour(wxCommandEvent& event)
{
    cldColour = new wxColourDialog(this);
    colourData = new wxColourData;
    if(cldColour->ShowModal() == wxID_OK)
    {
        *colourData = cldColour->GetColourData();
        *colGroundSun = colourData->GetColour();
        pnlGroundSunColourDisplay->SetBackgroundColour(*colGroundSun);
        pnlGroundSunColourDisplay->Refresh();
    }
    delete cldColour;
    delete colourData;
}
void Frontend::OnClickUnitAmbientColour(wxCommandEvent& event)
{
    cldColour = new wxColourDialog(this);
    colourData = new wxColourData;
    if(cldColour->ShowModal() == wxID_OK)
    {
        *colourData = cldColour->GetColourData();
        *colUnitAmbient = colourData->GetColour();
        pnlUnitAmbientColourDisplay->SetBackgroundColour(*colUnitAmbient);
        pnlUnitAmbientColourDisplay->Refresh();
    }
    delete cldColour;
    delete colourData;
}
void Frontend::OnClickUnitSunColour(wxCommandEvent& event)
{
    cldColour = new wxColourDialog(this);
    colourData = new wxColourData;
    if(cldColour->ShowModal() == wxID_OK)
    {
        *colourData = cldColour->GetColourData();
        *colUnitSun = colourData->GetColour();
        pnlUnitSunColourDisplay->SetBackgroundColour(*colUnitSun);
        pnlUnitSunColourDisplay->Refresh();
    }
    delete cldColour;
    delete colourData;
}
void Frontend::OnChangeUnitShadowDensityText(wxCommandEvent& event){
}
void Frontend::OnChangeGroundShadowDensityText(wxCommandEvent& event){
}
