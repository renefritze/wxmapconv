#include "wxwfrontend.h"


void Frontend::OnOpenHeight(wxCommandEvent& event)
{
    openFileDialog = new wxFileDialog(this);
    if (openFileDialog->ShowModal() == wxID_OK)
    {
        path = openFileDialog->GetPath();
        tcHeight->SetValue(path);
        LoadImage(ID_HEIGHT);
        bHeightmapLoaded = true;
    }
}

void Frontend::OnOpenTexture(wxCommandEvent& event)
{
    openFileDialog = new wxFileDialog(this);
    if (openFileDialog->ShowModal() == wxID_OK)
    {
        path = openFileDialog->GetPath();
        tcTexture->SetValue(path);
        LoadImage(ID_TEXTURE);
        bTextureLoaded = true;
    }
}

void Frontend::OnOpenMetal(wxCommandEvent& event)
{
    openFileDialog = new wxFileDialog(this);
    if (openFileDialog->ShowModal() == wxID_OK)
    {
        path = openFileDialog->GetPath();
        tcMetal->SetValue(path);
        LoadImage(ID_METAL);
        bMetalLoaded = true;
    }
}
void Frontend::OnOpenFeature(wxCommandEvent& event)
{
    openFileDialog = new wxFileDialog(this);
    if (openFileDialog->ShowModal() == wxID_OK)
    {
        path = openFileDialog->GetPath();
        tcFeature->SetValue(path);
        LoadImage(ID_FEATURE);
        bFeatureLoaded = true;
    }
}
void Frontend::OnOpenFeatureList(wxCommandEvent& event)
{
    openFileDialog = new wxFileDialog(this);
    if (openFileDialog->ShowModal() == wxID_OK)
    {
        path = openFileDialog->GetPath();
        tcFeatureList->SetValue(path);
    }
}
void Frontend::OnOpenType(wxCommandEvent& event)
{
    openFileDialog = new wxFileDialog(this);
    if (openFileDialog->ShowModal() == wxID_OK)
    {
        path = openFileDialog->GetPath();
        tcType->SetValue(path);
        LoadImage(ID_TYPE);
        bTypemapLoaded = true;
    }
}
void Frontend::OnOpenGeovent(wxCommandEvent& event)
{
    openFileDialog = new wxFileDialog(this);
    if (openFileDialog->ShowModal() == wxID_OK)
    {
        path = openFileDialog->GetPath();
        tcGeovent->SetValue(path);
    }
}
void Frontend::OnOpenOutput(wxCommandEvent& event)
{
    openFileDialog = new wxFileDialog(this);
    if (openFileDialog->ShowModal() == wxID_OK)
    {
        path = openFileDialog->GetPath();
        tcOutput->SetValue(path);
    }
}

void Frontend::LoadImage(int type)
{
    int scale;
    image = new wxImage;

    path.MakeLower();
    if(path.find(wxT(".bmp"), 0)!=wxNOT_FOUND){
        image->LoadFile(path, wxBITMAP_TYPE_BMP, -1);
    }
    else if(path.find(wxT(".jpg"), 0)!=wxNOT_FOUND || path.find(wxT(".jpeg"), 0)!=wxNOT_FOUND){
        image->LoadFile(path, wxBITMAP_TYPE_JPEG, -1);
    }
    else if(path.find(wxT(".png"), 0)!=wxNOT_FOUND){
        image->LoadFile(path, wxBITMAP_TYPE_PNG, -1);
    }
    else if(path.find(wxT(".tga"), 0)!=wxNOT_FOUND){
        image->LoadFile(path, wxBITMAP_TYPE_TGA, -1);
    }
    else{
        //error not a supported file type
    }

    int width = image->GetWidth();
    int height = image->GetHeight();

    if(width > height){
        scale=width/height;
        image->Rescale(440, 440/scale, wxIMAGE_QUALITY_NORMAL);
    }
    else if(height > width){
        scale=height/width;
        image->Rescale(440/scale, 440, wxIMAGE_QUALITY_NORMAL);
    }
    else{
        image->Rescale(440, 440, wxIMAGE_QUALITY_NORMAL);
        scale=1;
    }

    switch(type){
        case ID_HEIGHT:
            bmHeightmap = new wxBitmap(*image, -1);
            if(bmHeightmap->Ok()){
                bHeightmapLoaded = true;
                rbxPreview->Enable(ID_HEIGHT, true);
            }
            if(rbxPreview->GetSelection()==ID_HEIGHT)
                sbmPreviewBig->SetBitmap(*bmHeightmap);
            break;
        case ID_TEXTURE:
            bmTexture = new wxBitmap(*image, -1);
            if(bmTexture->Ok()){
                bTextureLoaded = true;
                rbxPreview->Enable(ID_TEXTURE, true);

                image->Rescale(128, 128, wxIMAGE_QUALITY_NORMAL);
                sbmPreview->SetBitmap(wxBitmap(*image, -1));
            }
            if(rbxPreview->GetSelection()==ID_TEXTURE)
                sbmPreviewBig->SetBitmap(*bmTexture);
            break;
        case ID_METAL:
            bmMetal = new wxBitmap(*image, -1);
            if(bmMetal->Ok()){
                bMetalLoaded = true;
                rbxPreview->Enable(ID_HEIGHT, true);
            }
            if(rbxPreview->GetSelection()==ID_METAL)
                sbmPreviewBig->SetBitmap(*bmMetal);
            break;
        case ID_FEATURE:
            bmFeature = new wxBitmap(*image, -1);
            if(bmFeature->Ok()){
                bFeatureLoaded = true;
                rbxPreview->Enable(ID_HEIGHT, true);
            }
            if(rbxPreview->GetSelection()==ID_FEATURE)
                sbmPreviewBig->SetBitmap(*bmFeature);
            break;
        case ID_TYPE:
            bmTypemap = new wxBitmap(*image, -1);
            if(bmTypemap->Ok()){
                bTypemapLoaded = true;
                rbxPreview->Enable(ID_HEIGHT, true);
            }
            if(rbxPreview->GetSelection()==ID_TYPE)
                sbmPreviewBig->SetBitmap(*bmTypemap);
            break;
        default:
            break;
    }
    sbmPreviewBig->CentreOnParent();
    delete image;
}
