#include "Image_Buffer.h"
#include <assert.h>
#include <iostream>
#include <math.h>

using namespace std;

#define min(a,b)    ((a<b) ? a : b)
#define max(a,b)    ((a<b) ? b : a)
#define abs(a)      ((a<0) ? -a : a)

// Width Image

int ImageBuffer::Width(void)
{
  return m_nWidth;
}

// Height Image

int ImageBuffer::Height(void)
{
  return m_nHeight;
}

// Constructor

ImageBuffer::ImageBuffer() : m_ppImage(NULL)
{
  m_nWidth = m_nHeight = 0;
}

ImageBuffer::ImageBuffer( int nHeight, int nWidth ) : m_ppImage(NULL)
{
  m_nWidth = nWidth;
  m_nHeight = nHeight;
  Allocate();
}

ImageBuffer::~ImageBuffer()
{
  Free();
}

void ImageBuffer::Allocate()
{
  if ( m_ppImage != NULL )
    return;

  m_ppImage = new byte* [m_nHeight];
  m_normex = new PIXEL* [m_nHeight];
  m_normey = new PIXEL* [m_nHeight];
  m_norme = new PIXEL* [m_nHeight];   
  m_buffer = new byte* [m_nHeight];   

  for ( int i=0 ;i< m_nHeight; i++ )
  {
    m_ppImage[i]= new byte[ m_nWidth]; 
    m_normex[i]= new PIXEL[ m_nWidth];
    m_normey[i]= new PIXEL[ m_nWidth];
    m_norme[i]= new PIXEL[ m_nWidth];
    m_buffer[i]= new byte[ m_nWidth];	
  }
  return;
} 

void ImageBuffer::Free()
{
  for ( int i=0 ;i< m_nHeight; i++ )
  {

    delete [] m_ppImage[i];
    delete [] m_normex[i];
    delete [] m_normey[i];
    delete [] m_norme[i];
    delete [] m_buffer[i];
  }

  delete [] m_ppImage;
  delete [] m_normex;
  delete [] m_normey;
  delete [] m_norme;
  delete [] m_buffer;
  return;
}

// Raw Image values writing 

bool ImageBuffer::Write( char* strRawFile )
{

  if( m_nWidth==0 || m_nHeight==0 || !m_ppImage )
    return false;

  ofstream f;
  f.open( strRawFile, ios::out | ios::binary );
  if( !f )
    return false;

  // Image line writing 

  for (int i =0 ;i < m_nHeight ; i++  )
    f.write( (char*)m_buffer[i], m_nWidth );

  f.close();
  return true;
}

void ImageBuffer::display()
{
  if ( ! (m_nWidth && m_nHeight && m_ppImage ) )
    return ;

  int i,j;

  for (i=0 ; i<m_nHeight ; i++)
  {
    for (j=0;j< m_nWidth; j++)
    {
      cout << " " << (int) m_buffer[i][j] << " "  ;
    }
    cout << endl;
  }
  return;
}

void ImageBuffer::threshold(int tresh, int fact)
{  
  int i,j,k;
  int som=0;
  int moy=0;

  for( i=0 ; i<m_nHeight ; i++)

  { for(j=fact ; j<m_nWidth-fact ; j=j+fact)
    {
      if (fact>1)
      {
        som=0;
        for(k=0;k<fact-1;k++)
        { 
          som=som+m_ppImage[i][j+k];

        }
        moy=som/(fact-1); 

        if(moy<=tresh)
        { 
          for(k=0;k<fact-1;k++)
          { 
            m_ppImage[i][j+k]=255;

          }         
        }
        else { 
          for(k=0;k<fact-1;k++)
          { 
            m_ppImage[i][j+k]=0;
          }
        }
      }
      else {
        if(m_ppImage[i][j]<=tresh)
        { 
          m_ppImage[i][j]=255;
        }
        else { 
          m_ppImage[i][j]=0;
        }
      }
    }			    
  }

}

void ImageBuffer::rgb_to_lum( int fact)
{
  int i,j;

  unsigned char lum;

  for(i=1;i<m_nHeight-1;i++) 
  {
    for(j=fact;j<m_nWidth-fact;j=j+fact)
    {
      lum=(min(min(m_ppImage[i][j],m_ppImage[i][j+1]),m_ppImage[i][j+2])+max(max(m_ppImage[i][j],m_ppImage[i][j+1]),m_ppImage[i][j+2]))/2;   
      m_ppImage[i][j]=lum;
      m_ppImage[i][j+1]=lum;
      m_ppImage[i][j+2]=lum;
      m_ppImage[i][j+3]=0;   
    }
  }  
}

void ImageBuffer::normey(int fact)
{
  int i,j,k;

  for(i=1;i<m_nHeight-1;i++) 
  {
    for(j=fact;j<m_nWidth-fact;j=j+fact) 
    { 
      if (fact>1)
      {
        for(k=0;k<fact-1;k++)
        {
          m_normey[i][j+k]=min(m_ppImage[i-1][j+k-fact]+2*m_ppImage[i-1][j+k]+m_ppImage[i-1][j+fact+k]-m_ppImage[i+1][j+k-fact]-2*m_ppImage[i+1][j+k]-m_ppImage[i+1][j+fact+k],255);
        }
      }
      else 
      { 
        m_normey[i][j]=min(m_ppImage[i-1][j-1]+2*m_ppImage[i-1][j]+m_ppImage[i-1][j+1]-m_ppImage[i+1][j-1]-2*m_ppImage[i+1][j]-m_ppImage[i+1][j+1],255);
      }		       
    }
  }
}

void ImageBuffer::normex(int fact)
{
  int i,j,k;

  for(i=1;i<m_nHeight-1;i++) 
  {
    for(j=fact;j<m_nWidth-fact;j=j+fact) 
    {  
      if (fact>1)
      {
        for(k=0;k<fact-1;k++)
        {
          m_normex[i][j+k]=min(m_ppImage[i-1][j+k-fact]+2*m_ppImage[i][j+k-fact]+m_ppImage[i+1][j+k-fact]-m_ppImage[i-1][j+fact+k]-2*m_ppImage[i][j+fact+k]-m_ppImage[i+1][j+fact+k],255);
        }
      }
      else
      { 
        m_normex[i][j]=min(m_ppImage[i-1][j-1]+2*m_ppImage[i][j-1]+m_ppImage[i+1][j-1]-m_ppImage[i-1][j+1]-2*m_ppImage[i][j+1]-m_ppImage[i+1][j+1],255);
      }
    }
  }  
}

void ImageBuffer::gaussian(int fact)
{
  int i,j,k;

  for(i=2;i<m_nHeight-2;i++)
  {
    for(j=2*fact;j<m_nWidth-2*fact;j=j+fact)
    { 
      if(fact>1)
      {
        for(k=0;k<fact-1;k++)
        {
          m_ppImage[i][j+k]=min(255,(2*m_ppImage[i-2][j+k-2*fact]+4*m_ppImage[i-2][j+k-fact]+5*m_ppImage[i-2][j+k]+4*m_ppImage[i-2][j+k+fact]+2*m_ppImage[i-2][j+k+2*fact]+
                4*m_ppImage[i-1][j+k-2*fact]+9*m_ppImage[i-1][j+k-fact]+12*m_ppImage[i-1][j+k]+9*m_ppImage[i-1][j+k+fact]+4*m_ppImage[i-1][j+k+2*fact]+
                5*m_ppImage[i][j+k-2*fact]+12*m_ppImage[i][j+k-fact]+15*m_ppImage[i][j+k]+12*m_ppImage[i][j+k+fact]+5*m_ppImage[i][j+k+2*fact]+
                4*m_ppImage[i+1][j+k-2*fact]+9*m_ppImage[i+1][j+k-fact]+12*m_ppImage[i+1][j+k]+9*m_ppImage[i+1][j+k+fact]+4*m_ppImage[i+1][j+k+2*fact]+
                2*m_ppImage[i+2][j+k-2*fact]+4*m_ppImage[i+2][j+k-fact]+5*m_ppImage[i+2][j+k]+4*m_ppImage[i+2][j+k+fact]+2*m_ppImage[i+2][j+k+2*fact])/157);	        
        }
      }   
      else
      {
        m_ppImage[i][j]=min(255,(2*m_ppImage[i-2][j-2*fact]+4*m_ppImage[i-2][j-fact]+5*m_ppImage[i-2][j]+4*m_ppImage[i-2][j+fact]+2*m_ppImage[i-2][j+2*fact]+
              4*m_ppImage[i-1][j-2*fact]+9*m_ppImage[i-1][j-fact]+12*m_ppImage[i-1][j]+9*m_ppImage[i-1][j+fact]+4*m_ppImage[i-1][j+2*fact]+
              5*m_ppImage[i][j-2*fact]+12*m_ppImage[i][j-fact]+15*m_ppImage[i][j]+12*m_ppImage[i][j+fact]+5*m_ppImage[i][j+2*fact]+
              4*m_ppImage[i+1][j-2*fact]+9*m_ppImage[i+1][j-fact]+12*m_ppImage[i+1][j]+9*m_ppImage[i+1][j+fact]+4*m_ppImage[i+1][j+2*fact]+
              2*m_ppImage[i+2][j-2*fact]+4*m_ppImage[i+2][j-fact]+5*m_ppImage[i+2][j]+4*m_ppImage[i+2][j+fact]+2*m_ppImage[i+2][j+2*fact])/157);	        
      }
    }
  }
}

void ImageBuffer::norme(int fact)
{  
  int i,j,k;

  for(i=1;i<m_nHeight-1;i++)
  {
    for(j=fact;j<m_nWidth-fact;j=j+fact)
    { 
      if (fact>1)
      {
        for(k=0;k<fact-1;k++)
        {
          m_ppImage[i][j+k]=min(sqrt(pow((m_normex[i][j+k]),2)+pow((m_normey[i][j+k]),2)),255);
        }
      }
      else 
      {
        m_ppImage[i][j]=min(sqrt(pow((m_normex[i][j]),2)+pow((m_normey[i][j]),2)),255); 
      }
    }
  }
}

void ImageBuffer::transferx()
{   int i,j;

  for(i=0;i<m_nHeight;i++)
  {
    for(j=0;j<m_nWidth;j++)
    {
      m_ppImage[i][j]=min(255,abs(m_normex[i][j]));
    } 
  }     
}	

void ImageBuffer::transfery()
{   int i,j;

  for(i=0;i<m_nHeight;i++)
  {
    for(j=0;j<m_nWidth;j++)
    {
      m_ppImage[i][j]=min(255,abs(m_normey[i][j]));
    } 
  }     
}	

void ImageBuffer::invert_values(int fact)
{
  int i,j,k;

  for(i=1;i<m_nHeight-1;i++)
  {
    for(j=fact;j<m_nWidth-fact;j=j+fact)
    { 
      if (fact>1)
      {
        for(k=0;k<fact-1;k++)
        {
          m_ppImage[i][j+k]=255-m_ppImage[i][j+k];
        }
      }
      else 
      {
        m_ppImage[i][j]=255-m_ppImage[i][j]; 
      }
    }
  }
}

void ImageBuffer::transfer_to_exim(QImage * pqImg)
{
  float fact;
  int w, h;
  byte * pLine;

  fact=pqImg->depth()/8;
  w=pqImg->width(); 
  h=pqImg->height() ;

  for ( int i = 0 ; i< h ; i++ )
  {
    pLine = pqImg->scanLine(i);
    memcpy ( m_ppImage[i],  pLine , w*fact*sizeof(byte ));
    assert(m_ppImage[i] != NULL);
  }
}

void ImageBuffer::transfer_to_qim(QImage * pqImg)
{
  int w,h;
  byte* pLine;
  w=m_nWidth;
  h=m_nHeight;

  for ( int i=0 ; i<h ; i++ )
  { 
    pLine=pqImg->scanLine(i);
    memcpy ( pLine, m_ppImage[i] , w*sizeof(byte ));         
  }
}

byte* ImageBuffer::get_buffer()
{
  return m_ppImage[0];
}  



