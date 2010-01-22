#include "wxwfrontend.h"

void Frontend::OnOpenHeight(wxCommandEvent& event)
{
    openFileDialog = new wxFileDialog(this);
    if (openFileDialog->ShowModal() == wxID_OK)
    {
        tcHeight->SetValue(openFileDialog->GetPath());
    }
}

void Frontend::OnOpenTexture(wxCommandEvent& event)
{
    openFileDialog = new wxFileDialog(this);
    if (openFileDialog->ShowModal() == wxID_OK)
    {
        wxBitmap bitmap(128,128);
        wxImage image(128,128);
        int scale=1;

        wxString path = openFileDialog->GetPath();
        tcTexture->SetValue(path);
        path.MakeLower();

        if(path.find(wxT(".bmp"), 0)!=wxNOT_FOUND){
            image.LoadFile(path, wxBITMAP_TYPE_BMP, -1);
        }
        else if(path.find(wxT(".jpg"), 0)!=wxNOT_FOUND || path.find(wxT(".jpeg"), 0)!=wxNOT_FOUND){
            image.LoadFile(path, wxBITMAP_TYPE_JPEG, -1);
        }
        else if(path.find(wxT(".png"), 0)!=wxNOT_FOUND){
            image.LoadFile(path, wxBITMAP_TYPE_PNG, -1);
        }
        else if(path.find(wxT(".tga"), 0)!=wxNOT_FOUND){
            image.LoadFile(path, wxBITMAP_TYPE_TGA, -1);
        }

        float width = image.GetWidth();
        float height = image.GetHeight();

        if(width > height){
            scale=width/height;
            image.Rescale(128, 128/scale, wxIMAGE_QUALITY_NORMAL);
        }
        else if(height > width){
            scale=height/width;
            image.Rescale(128/scale, 128, wxIMAGE_QUALITY_NORMAL);
        }
        else{
            image.Rescale(128, 128, wxIMAGE_QUALITY_NORMAL);
        }

        bitmap = wxBitmap(image, -1);
        sbmPreview->SetBitmap(bitmap);
    }
}

void Frontend::OnOpenMetal(wxCommandEvent& event)
{
    openFileDialog = new wxFileDialog(this);
    if (openFileDialog->ShowModal() == wxID_OK)
    {
        tcMetal->SetValue(openFileDialog->GetPath());
    }
}
void Frontend::OnOpenFeature(wxCommandEvent& event)
{
    openFileDialog = new wxFileDialog(this);
    if (openFileDialog->ShowModal() == wxID_OK)
    {
        tcFeature->SetValue(openFileDialog->GetPath());
    }
}
void Frontend::OnOpenFeatureList(wxCommandEvent& event)
{
    openFileDialog = new wxFileDialog(this);
    if (openFileDialog->ShowModal() == wxID_OK)
    {
        tcFeatureList->SetValue(openFileDialog->GetPath());
    }
}
void Frontend::OnOpenType(wxCommandEvent& event)
{
    openFileDialog = new wxFileDialog(this);
    if (openFileDialog->ShowModal() == wxID_OK)
    {
        tcType->SetValue(openFileDialog->GetPath());
    }
}
void Frontend::OnOpenGeovent(wxCommandEvent& event)
{
    openFileDialog = new wxFileDialog(this);
    if (openFileDialog->ShowModal() == wxID_OK)
    {
        tcGeovent->SetValue(openFileDialog->GetPath());
    }
}
void Frontend::OnOpenOutput(wxCommandEvent& event)
{
    openFileDialog = new wxFileDialog(this);
    if (openFileDialog->ShowModal() == wxID_OK)
    {
        tcOutput->SetValue(openFileDialog->GetPath());
    }
}