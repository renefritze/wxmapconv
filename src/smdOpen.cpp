#include "wxwfrontend.h"
#include <string>

void Frontend::OpenSMD(void)
{
    wxString str;
    wxString name;
    wxString value;
    int start, length;

    wxTextFile *file;
    wxFileDialog *loadSMDDialog = new wxFileDialog(this);

    if (loadSMDDialog->ShowModal() == wxID_OK)
    {
        file = new wxTextFile(loadSMDDialog->GetPath());

        for (str = file->GetFirstLine(); !file->Eof(); str = file->GetNextLine())
        {
            int startPosID = -1;
            str.MakeLower();

            if(str.Contains(wxT("[")) && str.Contains(wxT("]")))
            {
                str = str.After('[');
                str = str.Before(']');
                if(str == wxT("team0"))
                    startPosID = 0;
                else if(str == wxT("team1"))
                    startPosID = 1;
                else if(str == wxT("team2"))
                    startPosID = 2;
                else if(str == wxT("team3"))
                    startPosID = 3;
                else if(str == wxT("team4"))
                    startPosID = 4;
                else if(str == wxT("team5"))
                    startPosID = 5;
                else if(str == wxT("team6"))
                    startPosID = 6;
                else if(str == wxT("team7"))
                    startPosID = 7;

            }
            if(str.Contains(wxT("=")))
            {
                str = str.After(RXwhite);
                str = str.Before(RXwhite);
                start = 0;
                length = str.Find(wxT("="));
                name = str.Mid(start, length);

                start = str.Find(wxT("=")) + 1;
                length = str.Find(wxT(";")) - start;
                value = str.Mid(start, length);

                if(name == wxT("description"))
                    tcDescription->SetValue(value);
                else if(name == wxT("tidalstrenght"))
                    tcTidalStrength->SetValue(value);
                else if(name == wxT("gravity"))
                    tcGravity->SetValue(value);
                else if(name == wxT("maxmetal"))
                    tcMaxMetal->SetValue(value);
                else if(name == wxT("extractorradius"))
                    tcExtractorRadius->SetValue(value);
                else if(name == wxT("maphardness"))
                    tcMapHardness->SetValue(value);
                else if(name == wxT("maxheight"))
                    tcMaxHeight->SetValue(value);
                else if(name == wxT("minheight"))
                    tcMinHeight->SetValue(value);
                else if(name == wxT("fogcolor"))
                {
                    int subLength;
                    float red, green, blue;

                    subLength = value.Find(wxT(" "));
                    red = wxAtof( value.Mid( 0, subLength));
                    value = value.Mid( subLength+1, value.Length());

                    subLength = value.Find(wxT(" "));
                    green = wxAtof( value.Mid(0, subLength));
                    value = value.Mid( subLength+1, value.Length());

                    blue = wxAtof( value );
                    colFog->Set((unsigned char)(red*255), (unsigned char)(green*255), (unsigned char)(blue*255));
                    pnlFogColourDisplay->SetBackgroundColour(*colFog);
                }
                else if(name == wxT("fogstart"))
                    tcFogStart->SetValue(value);
                else if(name == wxT("suncolor"))
                {
                    int subLength;
                    float red, green, blue;

                    subLength = value.Find(wxT(" "));
                    red = wxAtof( value.Mid( 0, subLength));
                    value = value.Mid( subLength+1, value.Length());

                    subLength = value.Find(wxT(" "));
                    green = wxAtof( value.Mid(0, subLength));
                    value = value.Mid( subLength+1, value.Length());

                    blue = wxAtof( value );
                    colSun->Set((unsigned char)(red*255), (unsigned char)(green*255), (unsigned char)(blue*255));
                    pnlSunColourDisplay->SetBackgroundColour(*colSun);
                }
                else if(name == wxT("skycolor"))
                {
                    int subLength;
                    float red, green, blue;

                    subLength = value.Find(wxT(" "));
                    red = wxAtof( value.Mid( 0, subLength));
                    value = value.Mid( subLength+1, value.Length());

                    subLength = value.Find(wxT(" "));
                    green = wxAtof( value.Mid(0, subLength));
                    value = value.Mid( subLength+1, value.Length());

                    blue = wxAtof( value );
                    colSky->Set((unsigned char)(red*255), (unsigned char)(green*255), (unsigned char)(blue*255));
                    pnlSkyColourDisplay->SetBackgroundColour(*colSky);
                }
                else if(name == wxT("cloudcolor"))
                {
                    int subLength;
                    float red, green, blue;

                    subLength = value.Find(wxT(" "));
                    red = wxAtof( value.Mid( 0, subLength));
                    value = value.Mid( subLength+1, value.Length());

                    subLength = value.Find(wxT(" "));
                    green = wxAtof( value.Mid(0, subLength));
                    value = value.Mid( subLength+1, value.Length());

                    blue = wxAtof( value );
                    colCloud->Set((unsigned char)(red*255), (unsigned char)(green*255), (unsigned char)(blue*255));
                    pnlCloudColourDisplay->SetBackgroundColour(*colCloud);
                }
                else if(name == wxT("clouddensity"))
                    tcCloudDensity->SetValue(value);
                else if(name == wxT("minwind"))
                    tcMinWind->SetValue(value);
                else if(name == wxT("maxwind"))
                    tcMaxWind->SetValue(value);
                else if(name == wxT("sundir"))
                {
                    int subLength;

                    subLength = value.Find(wxT(" "));
                    tcSunDirX->SetValue( value.Mid( 0, subLength));
                    value = value.Mid( subLength+1, value.Length());

                    subLength = value.Find(wxT(" "));
                    tcSunDirY->SetValue( value.Mid(0, subLength));
                    value = value.Mid( subLength+1, value.Length());

                    tcSunDirZ->SetValue( value );
                }
                else if(name == wxT("groundambientcolor"))
                {
                    int subLength;
                    float red, green, blue;

                    subLength = value.Find(wxT(" "));
                    red = wxAtof( value.Mid( 0, subLength));
                    value = value.Mid( subLength+1, value.Length());

                    subLength = value.Find(wxT(" "));
                    green = wxAtof( value.Mid(0, subLength));
                    value = value.Mid( subLength+1, value.Length());

                    blue = wxAtof( value );
                    colGroundAmbient->Set((unsigned char)(red*255), (unsigned char)(green*255), (unsigned char)(blue*255));
                    pnlGroundAmbientColourDisplay->SetBackgroundColour(*colGroundAmbient);
                }
                else if(name == wxT("groundsuncolor"))
                {
                    int subLength;
                    float red, green, blue;

                    subLength = value.Find(wxT(" "));
                    red = wxAtof( value.Mid( 0, subLength));
                    value = value.Mid( subLength+1, value.Length());

                    subLength = value.Find(wxT(" "));
                    green = wxAtof( value.Mid(0, subLength));
                    value = value.Mid( subLength+1, value.Length());

                    blue = wxAtof( value );
                    colGroundSun->Set((unsigned char)(red*255), (unsigned char)(green*255), (unsigned char)(blue*255));
                    pnlGroundSunColourDisplay->SetBackgroundColour(*colGroundSun);
                }
                else if(name == wxT("groundshadowdensity"))
                    tcUnitShadowDensity->SetValue(value);
                else if(name == wxT("unitambientcolor"))
                {
                    int subLength;
                    float red, green, blue;

                    subLength = value.Find(wxT(" "));
                    red = wxAtof( value.Mid( 0, subLength));
                    value = value.Mid( subLength+1, value.Length());

                    subLength = value.Find(wxT(" "));
                    green = wxAtof( value.Mid(0, subLength));
                    value = value.Mid( subLength+1, value.Length());

                    blue = wxAtof( value );
                    colUnitAmbient->Set((unsigned char)(red*255), (unsigned char)(green*255), (unsigned char)(blue*255));
                    pnlUnitAmbientColourDisplay->SetBackgroundColour(*colUnitAmbient);
                }
                else if(name == wxT("unitsuncolor"))
                {
                    int subLength;
                    float red, green, blue;

                    subLength = value.Find(wxT(" "));
                    red = wxAtof( value.Mid( 0, subLength));
                    value = value.Mid( subLength+1, value.Length());

                    subLength = value.Find(wxT(" "));
                    green = wxAtof( value.Mid(0, subLength));
                    value = value.Mid( subLength+1, value.Length());

                    blue = wxAtof( value );
                    colUnitSun->Set((unsigned char)(red*255), (unsigned char)(green*255), (unsigned char)(blue*255));
                    pnlUnitSunColourDisplay->SetBackgroundColour(*colUnitSun);
                }
                else if(name == wxT("unitshadowdensity"))
                    tcUnitShadowDensity->SetValue(value);
                else if(name == wxT("waterbasecolor"))
                {
                    int subLength;
                    float red, green, blue;

                    subLength = value.Find(wxT(" "));
                    red = wxAtof( value.Mid( 0, subLength));
                    value = value.Mid( subLength+1, value.Length());

                    subLength = value.Find(wxT(" "));
                    green = wxAtof( value.Mid(0, subLength));
                    value = value.Mid( subLength+1, value.Length());

                    blue = wxAtof( value );
                    colWaterBase->Set((unsigned char)(red*255), (unsigned char)(green*255), (unsigned char)(blue*255));
                    pnlWaterBaseColourDisplay->SetBackgroundColour(*colWaterBase);
                }
                else if(name == wxT("watermincolor"))
                {
                    int subLength;
                    float red, green, blue;

                    subLength = value.Find(wxT(" "));
                    red = wxAtof( value.Mid( 0, subLength));
                    value = value.Mid( subLength+1, value.Length());

                    subLength = value.Find(wxT(" "));
                    green = wxAtof( value.Mid(0, subLength));
                    value = value.Mid( subLength+1, value.Length());

                    blue = wxAtof( value );
                    colWaterMin->Set((unsigned char)(red*255), (unsigned char)(green*255), (unsigned char)(blue*255));
                    pnlWaterMinColourDisplay->SetBackgroundColour(*colWaterMin);
                }
                else if(name == wxT("waterabsorbcolor"))
                {
                    int subLength;
                    float red, green, blue;

                    subLength = value.Find(wxT(" "));
                    red = wxAtof( value.Mid( 0, subLength));
                    value = value.Mid( subLength+1, value.Length());

                    subLength = value.Find(wxT(" "));
                    green = wxAtof( value.Mid(0, subLength));
                    value = value.Mid( subLength+1, value.Length());

                    blue = wxAtof( value );
                    colWaterAbsorb->Set((unsigned char)(red*255), (unsigned char)(green*255), (unsigned char)(blue*255));
                    pnlWaterAbsorbColourDisplay->SetBackgroundColour(*colWaterAbsorb);
                }
                else if(name == wxT("startposx"))
                {
                    switch(startPosID)
                    {
                        case 0:
                            tcTeam1X->SetValue(value);
                            break;
                        case 1:
                            tcTeam2X->SetValue(value);
                            break;
                        case 2:
                            tcTeam3X->SetValue(value);
                            break;
                        case 3:
                            tcTeam4X->SetValue(value);
                            break;
                        case 4:
                            tcTeam5X->SetValue(value);
                            break;
                        case 5:
                            tcTeam6X->SetValue(value);
                            break;
                        case 6:
                            tcTeam7X->SetValue(value);
                            break;
                        case 7:
                            tcTeam8X->SetValue(value);
                            break;
                        default:
                            break;
                    }
                }
                else if(name == wxT("startposz"))
                {
                    switch(startPosID)
                    {
                        case 0:
                            tcTeam1Y->SetValue(value);
                            break;
                        case 1:
                            tcTeam2Y->SetValue(value);
                            break;
                        case 2:
                            tcTeam3Y->SetValue(value);
                            break;
                        case 3:
                            tcTeam4Y->SetValue(value);
                            break;
                        case 4:
                            tcTeam5Y->SetValue(value);
                            break;
                        case 5:
                            tcTeam6Y->SetValue(value);
                            break;
                        case 6:
                            tcTeam7Y->SetValue(value);
                            break;
                        case 7:
                            tcTeam8Y->SetValue(value);
                            break;
                        default:
                            break;
                    }
                }
            }
        }
        file->Close();
    }
    delete loadSMDDialog;
    //bSaved = true;
}

