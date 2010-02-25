#ifndef RESOURCES_H
#define RESOURCES_H
#define IDST_HEIGHT      1001
#define IDST_TEXTURE     1002
#define IDST_METAL       1003
#define IDST_FEATURE     1004
#define IDST_FEATURELIST 1005
#define IDST_TYPE        1006
#define IDST_GEOVENT     1007
#define IDST_OUTPUT      1008
#define IDST_OTHER       1009

#define IDBTN_HEIGHT      2001
#define IDBTN_TEXTURE     2002
#define IDBTN_METAL       2003
#define IDBTN_FEATURE     2004
#define IDBTN_FEATURELIST 2005
#define IDBTN_TYPE        2006
#define IDBTN_GEOVENT     2007
#define IDBTN_OUTPUT      2008

#define IDBTN_SUN_COLOUR    2011
#define IDBTN_SKY_COLOUR    2012
#define IDBTN_CLOUD_COLOUR  2013
#define IDBTN_FOG_COLOUR    2014
#define IDBTN_GROUNDAMBIENT_COLOUR  2015
#define IDBTN_GROUNDSUN_COLOUR      2016
#define IDBTN_UNITAMBIENT_COLOUR    2017
#define IDBTN_UNITSUN_COLOUR        2018
#define IDBTN_WATERBASE_COLOUR    2019
#define IDBTN_WATERMIN_COLOUR     2020
#define IDBTN_WATERABSORB_COLOUR  2021

#define ID_HEIGHT      0
#define ID_TEXTURE     1
#define ID_METAL       2
#define ID_FEATURE     3
#define ID_TYPE        4

#define IDBTN_COMPILE     3001
#define IDBTN_EXIT        3002
#define IDBTN_SMD_SAVE    3003

#define IDCB_LOWPASS     4001
#define IDCB_INVERT      4002
#define IDCB_FEATURE_ENABLE 4003
#define IDCB_TYPEMAP_ENABLE 4004
#define IDCB_GEO_ENABLE 4005
#define IDCB_OTHER_ENABLE 4006

#define IDI_MAX         5001
#define IDI_MIN         5002
#define IDF_QUALITY     5003

#define IDRB_LOW         6001
#define IDRB_MEDIUM      6002
#define IDRB_HIGH        6003
#define IDRB_BEST        6004
#define IDRBX_QUALITY    6005

#define IDRBX_PREVIEW    6101

#define IDNB_MAIN        7001

#define IDTC_CLOUD_DENSITY 8019
#define IDTC_FOG_DENSITY 8026

#define IDTC_MAX_HEIGHT 8027
#define IDTC_MIN_HEIGHT 8028

#define IDTC_GROUND_SHADOW_DENSITY 8044
#define IDTC_UNIT_SHADOW_DENSITY 8056

#define IDMENU_NEW  9001
#define IDMENU_OPEN 9002
#define IDMENU_SAVE 9003
#define IDMENU_SAVEAS 9004

#define IDTC_TEAM_COUNT 10001
#define IDBM_PREVIEW_PLACEHOLDER 10002
#define IDBM_PREVIEW_BIG_PLACEHOLDER 10003

#include <wx/wx.h>
#include <iostream>
#include <wx/dcclient.h>
#include <wx/image.h>
#include <wx/bitmap.h>
#include <wx/window.h>
#include <wx/statbmp.h>
#include <wx/notebook.h>
#include <wx/colour.h>
#include <wx/grid.h>
#include <wx/slider.h>
#include <wx/scrolwin.h>
#include <wx/event.h>
#include <wx/menu.h>
#include <wx/file.h>
#include <wx/ffile.h>
#include <wx/textfile.h>
#include <wx/colordlg.h>
#include <wx/cmndata.h>

#endif
