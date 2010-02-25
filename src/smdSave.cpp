#include <wx/file.h>
#include "wxwfrontend.h"

void Frontend::OnClickSMDSave(wxCommandEvent& event)
{
    wxString sBuffer;
    wxFile file;
    int iTeamCount;
//A large number of variables are read as char's but need to be stored as floats between 1 and 0
    wxString sSunRed = wxString::Format(wxT("%f"), (float)colSun->Red()/255);
    wxString sSunGreen = wxString::Format(wxT("%f"), (float)colSun->Green()/255);
    wxString sSunBlue = wxString::Format(wxT("%f"), (float)colSun->Blue()/255);

    wxString sSkyRed = wxString::Format(wxT("%f"), (float)colSky->Red()/255);
    wxString sSkyGreen = wxString::Format(wxT("%f"), (float)colSky->Green()/255);
    wxString sSkyBlue = wxString::Format(wxT("%f"), (float)colSky->Blue()/255);
    wxString sCloudRed = wxString::Format(wxT("%f"), (float)colCloud->Red()/255);
    wxString sCloudGreen = wxString::Format(wxT("%f"), (float)colCloud->Green()/255);
    wxString sCloudBlue = wxString::Format(wxT("%f"), (float)colCloud->Blue()/255);
    wxString sFogRed = wxString::Format(wxT("%f"), (float)colFog->Red()/255);
    wxString sFogGreen = wxString::Format(wxT("%f"), (float)colFog->Green()/255);
    wxString sFogBlue = wxString::Format(wxT("%f"), (float)colFog->Blue()/255);

    wxString sGroundAmbientRed = wxString::Format(wxT("%f"), (float)colGroundAmbient->Red()/255);
    wxString sGroundAmbientGreen = wxString::Format(wxT("%f"), (float)colGroundAmbient->Green()/255);
    wxString sGroundAmbientBlue = wxString::Format(wxT("%f"), (float)colGroundAmbient->Blue()/255);
    wxString sGroundSunRed = wxString::Format(wxT("%f"), (float)colGroundSun->Red()/255);
    wxString sGroundSunGreen = wxString::Format(wxT("%f"), (float)colGroundSun->Green()/255);
    wxString sGroundSunBlue = wxString::Format(wxT("%f"), (float)colGroundSun->Blue()/255);
    wxString sUnitSunRed = wxString::Format(wxT("%f"), (float)colUnitSun->Red()/255);
    wxString sUnitSunGreen = wxString::Format(wxT("%f"), (float)colUnitSun->Green()/255);
    wxString sUnitSunBlue = wxString::Format(wxT("%f"), (float)colUnitSun->Blue()/255);
    wxString sUnitAmbientRed = wxString::Format(wxT("%f"), (float)colUnitAmbient->Red()/255);
    wxString sUnitAmbientGreen = wxString::Format(wxT("%f"), (float)colUnitAmbient->Green()/255);
    wxString sUnitAmbientBlue = wxString::Format(wxT("%f"), (float)colUnitAmbient->Blue()/255);

    wxString sWaterBaseRed = wxString::Format(wxT("%f"), (float)colWaterBase->Red()/255);
    wxString sWaterBaseGreen = wxString::Format(wxT("%f"), (float)colWaterBase->Green()/255);
    wxString sWaterBaseBlue = wxString::Format(wxT("%f"), (float)colWaterBase->Blue()/255);
    wxString sWaterMinRed = wxString::Format(wxT("%f"), (float)colWaterMin->Red()/255);
    wxString sWaterMinGreen = wxString::Format(wxT("%f"), (float)colWaterMin->Green()/255);
    wxString sWaterMinBlue = wxString::Format(wxT("%f"), (float)colWaterMin->Blue()/255);
    wxString sWaterAbsorbRed = wxString::Format(wxT("%f"), (float)colWaterAbsorb->Red()/255);
    wxString sWaterAbsorbGreen = wxString::Format(wxT("%f"), (float)colWaterAbsorb->Green()/255);
    wxString sWaterAbsorbBlue = wxString::Format(wxT("%f"), (float)colWaterAbsorb->Blue()/255);

    sFogRed.Truncate(5);
    sFogGreen.Truncate(5);
    sFogBlue.Truncate(5);
    sSunRed.Truncate(5);
    sSunGreen.Truncate(5);
    sSunBlue.Truncate(5);
    sSkyRed.Truncate(5);
    sSkyGreen.Truncate(5);
    sSkyBlue.Truncate(5);
    sCloudRed.Truncate(5);
    sCloudGreen.Truncate(5);
    sCloudBlue.Truncate(5);

    sGroundAmbientRed.Truncate(5);
    sGroundAmbientGreen.Truncate(5);
    sGroundAmbientBlue.Truncate(5);
    sGroundSunRed.Truncate(5);
    sGroundSunGreen.Truncate(5);
    sGroundSunBlue.Truncate(5);
    sUnitAmbientRed.Truncate(5);
    sUnitAmbientGreen.Truncate(5);
    sUnitAmbientBlue.Truncate(5);
    sUnitSunRed.Truncate(5);
    sUnitSunGreen.Truncate(5);
    sUnitSunBlue.Truncate(5);

    sWaterBaseRed.Truncate(5);
    sWaterBaseGreen.Truncate(5);
    sWaterBaseBlue.Truncate(5);
    sWaterMinRed.Truncate(5);
    sWaterMinGreen.Truncate(5);
    sWaterMinBlue.Truncate(5);
    sWaterAbsorbRed.Truncate(6);
    sWaterAbsorbGreen.Truncate(6);
    sWaterAbsorbBlue.Truncate(6);

    file.Open(wxT("map.smd"), wxFile::write);
    file.Write(wxT("[MAP]\n{\n"));
        file.Write(wxT("\tDescription=") + tcDescription->GetValue() + wxT(";\n"));
        file.Write(wxT("\tTidalStrength=") + tcTidalStrength->GetValue() + wxT(";\n"));
        file.Write(wxT("\tGravity=") + tcGravity->GetValue() + wxT(";\n"));
        file.Write(wxT("\tMaxMetal=") + tcMaxMetal->GetValue() + wxT(";\n"));
        file.Write(wxT("\tExtractorRadius=") + tcExtractorRadius->GetValue() + wxT(";\n"));
        file.Write(wxT("\tMapHardness=") + tcMapHardness->GetValue() + wxT(";\n"));
        file.Write(wxT("\t[SMF]\n\t{\n"));
            file.Write(wxT("\t\tminheight = ") + tcMinHeight->GetValue() + wxT(";\n"));
            file.Write(wxT("\t\tmaxheight = ") + tcMaxHeight->GetValue() + wxT(";\n"));
        file.Write(wxT("\t}\n\t[ATMOSPHERE]\n\t{\n"));
            file.Write(wxT("\t\tFogColour=") + sFogRed + wxT(" ") + sFogGreen + wxT(" ") + sFogBlue + wxT(";\n"));
            file.Write(wxT("\t\tFogStart=") + tcFogStart->GetValue() + wxT(";\n"));
            file.Write(wxT("\t\tSunColour=") + sSunRed + wxT(" ") + sSunGreen + wxT(" ") + sSunBlue + wxT(";\n"));
            file.Write(wxT("\t\tSkyColour=") + sSkyRed + wxT(" ") + sSkyGreen + wxT(" ") + sSkyBlue + wxT(";\n"));
            file.Write(wxT("\t\tCloudColour=") + sCloudRed + wxT(" ") + sCloudGreen + wxT(" ") + sCloudBlue + wxT(";\n"));
            file.Write(wxT("\t\tCloudDensity=") + tcCloudDensity->GetValue() + wxT(";\n"));
            file.Write(wxT("\t\tMinWind=") + tcMinWind->GetValue() + wxT(";\n"));
            file.Write(wxT("\t\tMaxWind=") + tcMaxWind->GetValue() + wxT(";\n"));
        file.Write(wxT("\t}\n\t[LIGHT]\n\t{\n"));
            file.Write(wxT("\t\tSunDir=1 2 0;\n"));//            file.Write(wxT("\t\tSunDir=") + tcSunDirX->GetValue() + wxT(" ") + tcSunDirY->GetValue() + wxT(" ") + tcSunDirZ->GetValue() + wxT(";\n"));
            file.Write(wxT("\t\tGroundAmbientColour=") + sGroundAmbientRed + wxT(" ") + sGroundAmbientGreen + wxT(" ") + sGroundAmbientBlue + wxT(";\n"));
            file.Write(wxT("\t\tGroundSunColour=") + sGroundSunRed + wxT(" ") + sGroundSunGreen + wxT(" ") + sGroundSunBlue + wxT(";\n"));
            file.Write(wxT("\t\tGroundShadowDensity=") + tcGroundShadowDensity->GetValue() +wxT(";\n"));
            file.Write(wxT("\t\tUnitAmbientColour=") + sUnitAmbientRed + wxT(" ") + sUnitAmbientGreen + wxT(" ") + sUnitAmbientBlue + wxT(";\n"));
            file.Write(wxT("\t\tUnitSunColour=") + sUnitSunRed + wxT(" ") + sUnitSunGreen + wxT(" ") + sUnitSunBlue + wxT(";\n"));
            file.Write(wxT("\t\tUnitShadowDensity=") + tcUnitShadowDensity->GetValue() +wxT(";\n"));
        file.Write(wxT("\t}\n\t[WATER]\n\t{\n"));
            file.Write(wxT("\t\tWaterBaseColour=") + sWaterBaseRed + wxT(" ") + sWaterBaseGreen + wxT(" ") + sWaterBaseBlue + wxT(";\n"));
            file.Write(wxT("\t\tWaterMinColour=") + sWaterMinRed + wxT(" ") + sWaterMinGreen + wxT(" ") + sWaterMinBlue + wxT(";\n"));
            file.Write(wxT("\t\tWaterAbsorbColour=") + sWaterAbsorbRed + wxT(" ") + sWaterAbsorbGreen + wxT(" ") + sWaterAbsorbBlue + wxT(";\n"));
        file.Write(wxT("\t}\n"));
        iTeamCount = wxAtoi(tcTeamCount->GetValue());
        switch(iTeamCount){
            case 8:
                file.Write(wxT("\t[TEAM7]\n\t{\n\t\tStartPosX=") + tcTeam8X->GetValue() + wxT(";\n\t\tStartPosZ=") + tcTeam8Y->GetValue() + wxT(";\n\t}\n"));
            case 7:
                file.Write(wxT("\t[TEAM6]\n\t{\n\t\tStartPosX=") + tcTeam7X->GetValue() + wxT(";\n\t\tStartPosZ=") + tcTeam7Y->GetValue() + wxT(";\n\t}\n"));
            case 6:
                file.Write(wxT("\t[TEAM5]\n\t{\n\t\tStartPosX=") + tcTeam6X->GetValue() + wxT(";\n\t\tStartPosZ=") + tcTeam6Y->GetValue() + wxT(";\n\t}\n"));
            case 5:
                file.Write(wxT("\t[TEAM4]\n\t{\n\t\tStartPosX=") + tcTeam5X->GetValue() + wxT(";\n\t\tStartPosZ=") + tcTeam5Y->GetValue() + wxT(";\n\t}\n"));
            case 4:
                file.Write(wxT("\t[TEAM3]\n\t{\n\t\tStartPosX=") + tcTeam4X->GetValue() + wxT(";\n\t\tStartPosZ=") + tcTeam4Y->GetValue() + wxT(";\n\t}\n"));
            case 3:
                file.Write(wxT("\t[TEAM2]\n\t{\n\t\tStartPosX=") + tcTeam3X->GetValue() + wxT(";\n\t\tStartPosZ=") + tcTeam3Y->GetValue() + wxT(";\n\t}\n"));
            case 2:
                file.Write(wxT("\t[TEAM1]\n\t{\n\t\tStartPosX=") + tcTeam2X->GetValue() + wxT(";\n\t\tStartPosZ=") + tcTeam2Y->GetValue() + wxT(";\n\t}\n"));
                file.Write(wxT("\t[TEAM0]\n\t{\n\t\tStartPosX=") + tcTeam1X->GetValue() + wxT(";\n\t\tStartPosZ=") + tcTeam1Y->GetValue() + wxT(";\n\t}\n"));
        }
        file.Write(wxT("\n}"));

    file.Close();
}
//        file.Write(wxT("\t\t=") + ->GetValue() + wxT(";\n"));
//	[TERRAINTYPE0]
//	{
//		name=default;
//		hardness=1;
//		tankmovespeed=1;
//		kbotmovespeed=1;
//		hovermovespeed=1;
//		shipmovespeed=1;
//
//	}
