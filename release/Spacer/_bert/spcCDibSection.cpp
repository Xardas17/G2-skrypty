// GRADE DIB Class - Implementation


#include "stdafx.h"

#include "zengine.h"

#include "spcCDibSection.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
// Construct DIB (resets to NULL)
//
spcCDibSection::spcCDibSection()
{
  m_Data=NULL;
  m_bmp=NULL;
  m_Height=0;
  m_Width=0;
  m_BPP=0;

  m_dcBMP.CreateCompatibleDC(NULL);
}

//
// Destroy DIB
//
spcCDibSection::~spcCDibSection()
{
  if (m_bmp) DeleteObject(m_bmp);
}

//
// Create a general bitmap with dimensions <w> by <h> and <BPP> bits per pixel
//
BOOL spcCDibSection::Create(LONG w, LONG h, LONG BPP, RGBQUAD *Palette, DWORD rgbRMask, DWORD rgbGMask, DWORD rgbBMask)
{
  BYTE    DIBSpace[sizeof(BITMAPINFOHEADER)+256*sizeof(RGBQUAD)];   // Space for bitmap info stuff
  LPBITMAPINFOHEADER pCT=(LPBITMAPINFOHEADER)DIBSpace;              // Bitmap info structure
  LPDWORD pBitFields;                                               // -> RGB masks
  LPWORD  OTO;                                                      // -> 1-to-1 color table
  RGBQUAD *RC;                                                      // -> Color table
  LONG    i, PalMode;                                               // Set dependant of the amount of colours

  ASSERT((w >= 0) && (w <= 16384));
  ASSERT((h >= 0) && (h <= 16384));
  ASSERT((BPP == 8) || (BPP == 16) || (BPP==32));
  ASSERT((Palette == NULL) || (BPP == 8));

  // If this DIB has been used before, destory old object
  if (m_bmp) DeleteObject(m_bmp);                                   // Delete old object if present

  // Create BitmapInfoHeader for 32-bit color image (no palette needed)
  ZeroMemory(pCT, sizeof(BITMAPINFO));                              // Wipe out info structure
  pCT->biSize=sizeof(BITMAPINFOHEADER);                             // Size of header
  pCT->biWidth=w;                                                   // Width of DIB
  pCT->biHeight=-h;                                                 // Height of DIB
  pCT->biPlanes=1;                                                  // 1 Color plane
  pCT->biBitCount=(WORD)BPP;                                        // Bits/pixel
  pCT->biCompression=BI_RGB;                                        // Pixel compression

  // Create a DIB section, note that the palette has to be selected into the device 
  // context whereof the Hdc is passed to the CreateDIBSection() call to function 
  // properly. This is because the CreateDIBSection uses a one-to-one color table
  // in 256 color modes. This will map the palette colors to those in the hdc.
  if (BPP == 8)
  {
    CPalette WinPal;                                                // New windows palette
    RGBQUAD Pal[256];                                               // Palette

    // If this is an unpaletted 8 bit mode, make a phoney palette, otherwise, take user's
    ZeroMemory(Pal, 1024);                                          // Wipe out!
    Pal[255].rgbRed=Pal[255].rgbGreen=Pal[255].rgbBlue=0xff;        // Set color 255 to white
    if (Palette) CopyMemory(Pal, Palette, 1024);                    // Copy palette if it's given

    // Create a one-to-one color table or one with color values in it
    if (m_dcBMP.GetDeviceCaps(BITSPIXEL)==8)                        // Windows running in 8 bit mode?
    {
      // Windows is running in 8 bit mode, do an identity palette
      OTO=(LPWORD)((LPBYTE)pCT+sizeof(BITMAPINFOHEADER));           // -> One-2-One color table
      PalMode=DIB_PAL_COLORS;                                       // Palette mode
      for (i=0; i<256; i++) *OTO++=(WORD)i;                         // HDC(x) maps to Screen(x)
    }
    else
    {
      // The bitmap is 8 bit, but windows is running in a highcolor mode
      // copy palette and use these colors
      RC=(RGBQUAD *)(((LPBYTE)&pCT)+sizeof(BITMAPINFOHEADER));      // -> RGB table
      PalMode=DIB_RGB_COLORS;                                       // Palette mode
      CopyMemory(RC, Pal, 256*sizeof(RGBQUAD));                     // Copy palette
      for (i=0; i<256; i++, RC++) RC->rgbReserved=0;                // Reset reserved flags
    }

    // Create, select and realize the new palette
    BYTE    PalSpace[sizeof(LOGPALETTE)+256*sizeof(PALETTEENTRY)];  // Space for palette
    LPLOGPALETTE pPal=(LPLOGPALETTE)PalSpace;                       // -> Logical palette
    pPal->palVersion=0x300;                                         // Version 3.00
    pPal->palNumEntries=256;                                        // All of 'em
    for (i=0; i<256; i++)
    {
      pPal->palPalEntry[i].peRed   = Pal[i].rgbRed;                 // Copy Red   component
      pPal->palPalEntry[i].peGreen = Pal[i].rgbGreen;               // Copy Green component
      pPal->palPalEntry[i].peBlue  = Pal[i].rgbBlue;                // Copy Blue  component
      pPal->palPalEntry[i].peFlags = PC_NOCOLLAPSE;                 // No collapsing!
    }
    WinPal.CreatePalette(pPal);                                     // Create palette from log palette

    CPalette *OldPal=m_dcBMP.SelectPalette(&WinPal, FALSE);         // Select new palette
    m_dcBMP.RealizePalette();                                       // Realize new palette

    // Create DIBSection and return the pointer to the data in m_Data
    m_bmp=CreateDIBSection(m_dcBMP.GetSafeHdc(), (LPBITMAPINFO)pCT, PalMode, (LPVOID *)&m_Data, NULL, 0);

    m_dcBMP.SelectPalette(OldPal, FALSE);                           // Re-select old-palette in DC
  }
  else
  {
    DWORD DefRGBMasks[2][3]={ { 0x0000f800, 0x000007e0, 0x0000001f }, 
                              { 0x00ff0000, 0x0000ff00, 0x000000ff } };
    pBitFields=(LPDWORD)(((LPBYTE)pCT)+sizeof(BITMAPINFOHEADER));   // -> RGB Bitfields
    pCT->biCompression=BI_BITFIELDS;                                // Set RGB Masks
    if (rgbRMask | rgbGMask | rgbBMask)                             // Any mask given?
    {
      pBitFields[0]=rgbRMask;                                       // Red   Mask
      pBitFields[1]=rgbGMask;                                       // Green Mask
      pBitFields[2]=rgbBMask;                                       // Blue  Mask
    }
    else
    {
      LONG rgbIndex=(BPP==32);                                      // 16->0, 32->1
      for (LONG i=0; i<3; i++) pBitFields[i]=DefRGBMasks[rgbIndex][i]; // Copy masks
    }

    // Create DIBSection and return the pointer to the data in m_Data
    m_bmp=CreateDIBSection(m_dcBMP.GetSafeHdc(), (LPBITMAPINFO)pCT, DIB_RGB_COLORS, (LPVOID *)&m_Data, NULL, 0);
  }

	if (m_bmp==0) {
		int I =0;
		I++;}

  // Check if bitmap could be created  
  if (m_bmp==NULL)                                                  // Got one?
  {
    TRACE("spcCDibSection: Could not create a DIB sized %ux%u %u-bit", w, h, BPP);
    return FALSE;                                                   // Couldn't create! Return false
  }
  else
  {
    // We got a bitmap, select it into a DC so it can be used as the source for blitting
    m_dcBMP.SelectObject(CBitmap::FromHandle(m_bmp));               // Select object in DC
  }

  // Copy properties to spcCDibSection
  m_Width=w; m_Height=h; m_BPP=BPP;                                 // Store properties

  // Clean up and leave
  ZeroMemory(m_Data, w*h*BPP/8);                                    // Clear DIB
  return TRUE;                                                      // Done!
}

//
// Set DIB palette
//
BOOL spcCDibSection::SetPalette(RGBQUAD *Palette)
{
  ASSERT(Palette);
  ASSERT(m_BPP==8);
  
  return Create(m_Width, m_Height, m_BPP, Palette);
}

//
// Blit DIB to CWnd
//
VOID spcCDibSection::Blit(CWnd *pWnd, LONG x,  LONG y)
{    
	if (!pWnd) return;
	CDC *wndDC=pWnd->GetDC();                                         // Get window DC
	Blit(wndDC, x, y);                                                // Blit
	pWnd->ReleaseDC(wndDC);                                           // Release window DC
}

//
// Blit DIB to CDC
//
VOID spcCDibSection::Blit(CDC *pDC, LONG x,  LONG y)
{
  if (m_bmp==0) return;
  if (m_Width==0) return;
  if (m_Height==0) return;
  if (m_BPP==0) return;
  if (m_Data==0) return;
  
  pDC->BitBlt(x, y, m_Width, m_Height, &m_dcBMP, 0, 0, SRCCOPY);    // Blit bitmap
}

VOID spcCDibSection::Clear()
{
	memset(m_Data,0,m_Height * m_Width * int(m_BPP/8));
};