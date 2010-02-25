#include "wxwfrontend.h"

//////////////////////////////////////////////////////////////////////////////////////////
//Water base colour slider changed////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
void Frontend::OnClickWaterBaseColour(wxCommandEvent& event){
    cldColour = new wxColourDialog(this);
    colourData = new wxColourData;
    if(cldColour->ShowModal() == wxID_OK)
    {
        *colourData = cldColour->GetColourData();
        *colWaterBase = colourData->GetColour();
        pnlWaterBaseColourDisplay->SetBackgroundColour(*colWaterBase);
        pnlWaterBaseColourDisplay->Refresh();
    }
    delete cldColour;
    delete colourData;
}
//////////////////////////////////////////////////////////////////////////////////////////
//Water min colour slider changed/////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
void Frontend::OnClickWaterMinColour(wxCommandEvent& event){
    cldColour = new wxColourDialog(this);
    colourData = new wxColourData;
    if(cldColour->ShowModal() == wxID_OK)
    {
        *colourData = cldColour->GetColourData();
        *colWaterMin = colourData->GetColour();
        pnlWaterMinColourDisplay->SetBackgroundColour(*colWaterMin);
        pnlWaterMinColourDisplay->Refresh();
    }
    delete cldColour;
    delete colourData;
}
//////////////////////////////////////////////////////////////////////////////////////////
//Water absorb colour slider changed//////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
void Frontend::OnClickWaterAbsorbColour(wxCommandEvent& event){
    cldColour = new wxColourDialog(this);
    colourData = new wxColourData;
    if(cldColour->ShowModal() == wxID_OK)
    {
        *colourData = cldColour->GetColourData();
        *colWaterAbsorb = colourData->GetColour();
        pnlWaterAbsorbColourDisplay->SetBackgroundColour(*colWaterAbsorb);
        pnlWaterAbsorbColourDisplay->Refresh();
    }
    delete cldColour;
    delete colourData;
}
