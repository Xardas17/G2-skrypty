
// spcCMatListbox.cpp : implementation file
//

#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"
#include "SpacerView.h"
#include "MainFrm.h"
#include "spcCMatListbox.h"
// z-files
#include "zmaterial.h"
#include "zthread.h"


#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int TEX_PREVIEW_SIZE = 64;
const int MAX_BUFFERED = 0;

spcCTextureDibCache::spcCTextureDibCache()
{	
};


spcCTextureDibCache::~spcCTextureDibCache()
{
};

spcCDibSection* spcCTextureDibCache::GetDib(int index, bool& use)
{
	spcCTextureCacheItem* item=0;
	
	int numInList = list.GetNumInList();

	if (numInList<MAX_BUFFERED)
	{
		if (numInList <= index)
		{
			for (int i=numInList;i<=index;i++)
			{
				item = new spcCTextureCacheItem;
				item->dib = new spcCDibSection;
				item->dib->Create(TEX_PREVIEW_SIZE,TEX_PREVIEW_SIZE,16),
				list.InsertEnd(item);			
			};
		}

		item = list[index];
		use = item->inUse;
		return item->dib;
	}
	else
	{
		static spcCDibSection* singleDib = 0;
		if (!singleDib)
		{
			singleDib = new spcCDibSection;
			singleDib->Create(TEX_PREVIEW_SIZE,TEX_PREVIEW_SIZE,16);
		};
		singleDib->Clear();
		use = false;
		return singleDib;
	};	
};

void spcCTextureDibCache::Reset()
{
	for (int i = 0;i<list.GetNumInList();i++) 
	{
		list[i]->inUse = false;
	}
};


/////////////////////////////////////////////////////////////////////////////
// spcCMatListbox

spcCMatListbox::spcCMatListbox()
{	
	num_columns = 0;
	num_pix_space=6;
	num_pix_mat	 =TEX_PREVIEW_SIZE+num_pix_space;
	dibCache.Reset();
	selectedMaterial = 0;	
	selectedLine = -1;
	topLine = -1;
}

spcCMatListbox::~spcCMatListbox()
{
}


BEGIN_MESSAGE_MAP(spcCMatListbox, CListBox)
	//{{AFX_MSG_MAP(spcCMatListbox)
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()	
	ON_CONTROL_REFLECT(LBN_SELCHANGE, OnSelchange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// spcCMatListbox message handlers


void ConvertTextureToDIB (zCTexture *sourceTexture, spcCDibSection* dib)
{
	if (!sourceTexture) return;
	if (!dib)			return;

	sourceTexture->CacheIn(-1);

	static zCMutex* mutex = 0;
	if (mutex==0)
	{
		mutex = new zCMutex();
	};

	if (!mutex->Lock(2000)) return;
	
	zCTextureConvert* texCon = zrenderer->CreateTextureConvert();
	zCTextureExchange::CopyContents(sourceTexture, texCon);
	
 	zCTextureInfo destTexInfo = texCon->GetTextureInfo();	// info holen
    destTexInfo.texFormat = zRND_TEX_FORMAT_RGB_565;		// info modifizieren, alle Formate aus 'zTRnd_TextureFormat' moeglich! 
	destTexInfo.numMipMap = 1;	
	
	// Skalierung berechnen (nur runterskalieren!)
	double texSizeMultX = double(dib->GetWidth()) / double(destTexInfo.sizeX);
	double texSizeMultY = double(dib->GetHeight()) / double(destTexInfo.sizeY);
	double texSizeMult = (texSizeMultX<texSizeMultY) ? texSizeMultX : texSizeMultY;		
	if (texSizeMult<1.0)
	{
		destTexInfo.sizeX = int(destTexInfo.sizeX * texSizeMult);
		destTexInfo.sizeY = int(destTexInfo.sizeY * texSizeMult);
	}
	if (destTexInfo.sizeX>dib->GetWidth())	destTexInfo.sizeX = dib->GetWidth();
	if (destTexInfo.sizeY>dib->GetHeight())	destTexInfo.sizeY = dib->GetHeight();
		
	if ( (destTexInfo.sizeX>0) && (destTexInfo.sizeY>0) )
	{
		texCon->ConvertTextureFormat (destTexInfo);				// und ins neue Format Konvertieren

		// Hier kommt jetzt der Code, mit dem die Texture aus dem texCon 
		// Objekt ausgelesen wird und in die DIB gepackt wird.
		// Groesse der Textur kann bei Bedarf auch aus der destTexInfo Struktur ermittelt werden.
		// 'DIBPtr' enthaelt am Ende die Textur im oben gewaehlten Format (RGB_565)    
    		
		int destPitch = destTexInfo.sizeX*2;
		zBOOL result = TRUE;
		dib->Clear();
		result = texCon->Lock(zTEX_LOCK_READ) && result;
		result = texCon->CopyTextureDataTo(0, dib->GetDataPtr(), destPitch) && result;
		result = texCon->Unlock() && result;
	}
	else
	{
		zERR_MESSAGE(1,0,"B: CS: ");
	};
    delete texCon;
	
	mutex->Unlock();
};

void spcCMatListbox::DrawItem(LPDRAWITEMSTRUCT lpDIS) 
{
	RECT rc; 
	GetClientRect(&rc);
	
	bool inUse;
	spcCDibSection* dib = 0;

	// Zeichenbereich holen (CDC=class of device-context objects)
	CDC* pDC = CDC::FromHandle(lpDIS->hDC);
	rc = lpDIS->rcItem;
	
	// Hole Materialnamen
	if (lpDIS->itemID<0) return;
	int line = GetItemData(lpDIS->itemID);	
	if (line<0) return;

	// caluclate positions and dimensions	
	int x = rc.left;	
	int y = rc.top;		
	/*
	int cx = rc.right-rc.left;
	int cy = rc.bottom-rc.top;	
	*/

	zCTexture* tex = 0;
	zCMaterial* mat = NULL;
	CString matname;
	pDC->FillSolidRect( &rc, RGB(255,255,255) );
	
	for (int column=1;column<=num_columns;column++)
	{
		// init data CListbox
		tex  = 0;
		mat  = 0;
		
		// get material (column, line)
		int listIndex = (line-1)*num_columns+(column-1);
		if (listIndex>=0 && listIndex<current_matlist.GetNumInList()) mat = current_matlist.Get(listIndex);
							
		if (mat) 
		{
			tex = mat->GetTexture();

			int width  = TEX_PREVIEW_SIZE;
			int height = TEX_PREVIEW_SIZE;
		
			matname = CString(mat->GetName().ToChar())+"  ";
			matname.MakeLower();									

			rc.left = x+(width+num_pix_space)*(column-1);
			rc.right= x+(width+num_pix_space)*(column-1)+num_pix_mat;

			if (mat == selectedMaterial)
			{
				pDC->FillSolidRect(&rc,RGB(255,0,0));
				pDC->SetBkColor(RGB(255,0,0));
				pDC->SetTextColor(RGB(255,255,255));											
			}
			else
			{
				pDC->FillSolidRect(&rc,RGB(255,255,255));
				pDC->SetBkColor(RGB(255,255,255));
				pDC->SetTextColor(RGB(0,0,0));
			}

//#ifdef NDEBUG
			pDC->ExtTextOut(rc.left+2,y+height,ETO_CLIPPED, &rc, matname, NULL);
//#else
//			pDC->ExtTextOut(rc.left+2,y+height,ETO_CLIPPED, &rc, zSTRING(listIndex).ToChar(), NULL);
//#endif
			
			if (tex)
			{
				// Dib-Section holen
				dib  = dibCache.GetDib(listIndex,inUse);
				if (dib)
				{
					if (!inUse)
					// inUse zeigt an, dass die Textur noch nicht in die DIB-Section kopiert wurde
					{
						ConvertTextureToDIB(tex,dib);
					}
					
					dib->Blit(pDC,x+(width+num_pix_space)*(column-1)+2,y+2);
				}
			}
			else			
			{
				RECT rc1 = rc;
				rc1.left +=2;
				rc1.right = rc1.left+width;
				rc1.top +=2;
				rc1.bottom = rc1.top+height;
				pDC->FillSolidRect(&rc1,RGB(mat->GetColorR(),mat->GetColorG(),mat->GetColorB()));
			}			
		}
	}
}

void spcCMatListbox::DeleteItem(LPDELETEITEMSTRUCT lpD) 
{
	CListBox::DeleteItem(lpD);
}

int spcCMatListbox::CompareItem(LPCOMPAREITEMSTRUCT lpC) 
{
	return 0;
}

void spcCMatListbox::MeasureItem(LPMEASUREITEMSTRUCT lpM) 
{
	lpM->itemWidth	= num_pix_mat*num_columns;
	lpM->itemHeight	= 80;
}

void spcCMatListbox::CreateList(CString filter)
{	 	
	filterName = filter;

	filter.MakeLower();	
	zCList<zCMaterial>	*lList, *nextList;
	zCMaterial			*nextMat;

	current_matlist.DeleteList();	
	dibCache.Reset();	
		
	spcCMatFilter* trashItem = 0;
	spcCMatFilter* filterItem = 0;

	int pos						= spcConfig.FindMatFilterIndexByName(filter);
	if (pos>=0)		 filterItem	= spcConfig.matFilterList[pos];

	if (!filterItem) return;

	zERR_MESSAGE(7,0,"B: (TEX) Creating Texture-List for filter "+zSTRING(filter.GetBuffer(0))+" with id "+zSTRING(filterItem->id));

	int undefPos				= spcConfig.FindMatFilterIndexByName(NO_FILTER_FOLDER);	
	if (undefPos>=0) trashItem	= spcConfig.matFilterList[undefPos];		
	
	zCClassDef* classDef		= zCMaterial::GetStaticClassDef();
	
	zCMaterial*	mat				= 0;
	unsigned int	matIter					= 0;
	unsigned int	numOfMats				= classDef->GetNumObjects();		
	if (numOfMats>matIter) mat	= dynamic_cast<zCMaterial*>(classDef->GetObjectByIndex(matIter));	

	// iterate materials in matlist
	if (pos>=0)
	{
		while (mat)
		{		
			// zCTexture* texture = mat->GetTexture();
			// if (texture) texture->SetCacheOutLock(TRUE);
			// So, nun feststellen, ob das Material wirklich zu dem Filter gehoert
			if (
				(mat->GetUsage() == zCMaterial::zMAT_USAGE_LEVEL)
				&&
				(mat->GetLibFlag() == filterItem->id)
			   )
			{				
				// insert to current-list
				lList = &current_matlist;
				if (lList) 
				{							
					// suche nach einfuegepunkt (sortiert)					
					do
					{							
						nextMat = 0;
						nextList = lList->GetNextInList();
						if (nextList) 
						{
							nextMat = nextList->GetData();
							if (mat->GetName() < nextMat->GetName()) break;
							lList = nextList;
						}						
					} while (nextList);					
					if (lList) lList->Insert(mat);					
				}
				else 
				{					
					current_matlist.Insert(mat);
				}								
			}
			
			matIter++;
			if (numOfMats>matIter) mat = dynamic_cast<zCMaterial*>(classDef->GetObjectByIndex(matIter));
			else mat = 0;
		}		
	}

	UpdateList();
}


void spcCMatListbox::OnLButtonDown(UINT nFlags, CPoint point) 
{
	BOOL out;
	int line = ItemFromPoint(point,out);
	if (out || line<0) return;
	line++;
	
	int matIndex = (num_pix_mat!=0) ? (line-1)*num_columns+int(point.x/num_pix_mat) : -1;

	if (matIndex>=0)
	{
		selectedMaterial = current_matlist.Get(matIndex);		
		if (selectedMaterial) CMainFrame::mainframe->ObjectSelection(selectedMaterial,GetParent());
		CListBox::OnLButtonDown(nFlags, point);	
	}
}

void spcCMatListbox::RemoveSelected()
{
	current_matlist.Remove(selectedMaterial);	
	dibCache.Reset();
}

void spcCMatListbox::OnSize(UINT nType, int cx, int cy) 
{	
	int width = cx-5;
	int old_num_columns = num_columns;
	num_columns = int( width / TEX_PREVIEW_SIZE );
	if (num_columns<1) num_columns = 1;
	num_pix_space = ( num_columns==1 ? 0 : int( (width-(num_columns*TEX_PREVIEW_SIZE))/ (num_columns-1) ));
	num_pix_mat		= num_pix_space + TEX_PREVIEW_SIZE;

	CListBox::OnSize(nType, cx, cy);

	if (num_columns != old_num_columns)
	{
		UpdateList();		
	}	
	RedrawWindow();
}



void spcCMatListbox::UpdateList()
{
	int num_lines = int(current_matlist.GetNumInList() / num_columns);
	if (current_matlist.GetNumInList() % num_columns != 0) num_lines++;
		
	ResetContent();
	int index;
	for (int i=1;i<=num_lines;i++)
	{
		index = InsertString(-1,"Line "+CString(zSTRING(i).ToChar()));
		if ((index!=LB_ERR) && (index!=LB_ERRSPACE)) SetItemData( index, i );
	}

	if (topLine>=0) 
	{
		SetTopIndex(topLine);
	}

	RedrawWindow();
}


void spcCMatListbox::OnSelchange() 
{
	selectedLine = GetCurSel();	
	topLine = GetTopIndex();
	CSpacerView::view->SetFocus();
}

void spcCMatListbox::SelectMaterial(zCMaterial *mat)
{
	if (!mat) return;
	selectedMaterial = mat;
	OnPaint();
}
