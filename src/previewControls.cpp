#include "wxwfrontend.h"

void Frontend::OnChangePreview(wxCommandEvent& event)
{
    int selection = rbxPreview->GetSelection();

    switch(selection){
        case ID_HEIGHT:
            sbmPreviewBig->SetBitmap(*bmHeightmap);
            break;
        case ID_TEXTURE:
            sbmPreviewBig->SetBitmap(*bmTexture);
            break;
        case ID_METAL:
            sbmPreviewBig->SetBitmap(*bmMetal);
            break;
        case ID_FEATURE:
            sbmPreviewBig->SetBitmap(*bmFeature);
            break;
        case ID_TYPE:
            sbmPreviewBig->SetBitmap(*bmTypemap);
            break;
        default:
            break;
    }
    sbmPreviewBig->CentreOnParent();
    sbmPreviewBig->Refresh();
}


