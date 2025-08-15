// GRADE DIB Class

#ifndef __spcCDibSection_H__
#define __spcCDibSection_H__

class spcCDibSection : public CObject
{
protected:
  HBITMAP m_bmp;                                                    // Windows bitmap handle
  LONG    m_Height;                                                 // Height of bitmap
  LONG    m_Width;                                                  // Width of bitmap
  LONG    m_BPP;                                                    // Bits per pixel
  CDC     m_dcBMP;                                                  // CDC with bitmap selected into it
  LPVOID  m_Data;                                                   // -> Image data

public:
  spcCDibSection();                                                           // DIB constructor
  virtual ~spcCDibSection();                                                          // DIB destructer

  // Creation/palette
  BOOL    Create(LONG w, LONG h, LONG BPP, RGBQUAD *Palette = NULL, DWORD rgbRMask = 0, DWORD rgbGMask = 0, DWORD rgbBMask = 0); // Create bitmap
  BOOL    SetPalette(RGBQUAD *Palette);                             // Set DIB palette

  // Blitting/displaying
  VOID    Blit(CWnd *pWnd, LONG x = 0,  LONG y = 0);                // Blit DIB to CWnd
  VOID    Blit(CDC *pDC,   LONG x = 0,  LONG y = 0);                // Blit DIB to CDC

  VOID    Clear();

  // Properties
  inline HBITMAP  GetHbmp()    { return m_bmp;    }                 // Return DIBSection
  inline LPVOID   GetDataPtr() { return m_Data;   }                 // Return -> bitmap data
  inline LONG     GetHeight()  { return m_Height; }                 // Return height of bitmap
  inline LONG     GetWidth()   { return m_Width;  }                 // Return width of bitmap
};

#endif // __spcCDibSection_H__?
