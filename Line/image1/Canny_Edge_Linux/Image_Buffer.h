#include <iostream>
#include <fstream>
using namespace std;
#include <qimage.h>

typedef unsigned char byte; 
typedef double PIXEL;

class ImageBuffer
{
  protected:

    byte **m_ppImage;    // Matrix Image
    PIXEL **m_normex;    // Matrix of the horizontal mask
    PIXEL **m_normey;    // Matrix of the vertical mask 
    PIXEL **m_norme;     // Matrix of the norm gradient

    byte **m_buffer;     // Buffer Image
    int m_nWidth ;       // Image width
    int m_nHeight ;      // Image height

    // Allocation and Free methods

    void Allocate();
    void Free();

  public :

    ImageBuffer() ;
    ImageBuffer(int,int);
    ~ImageBuffer();

    int Width() ;  // Image width
    int Height();  // Image height

    // Display Raw Data

    void display();

    // Threshold

    void threshold(int,int);

    // Border detection

    void maskvert(void);
    void maskhori(void);

    // Gradient norms

    void normex(int);
    void normey(int);
    void norme(int);

    // Transfer buffer methods

    void transferx(void);
    void transfery(void);
    void transfer_n(void);

    // Getting Line

    byte* GetLine(int);

    // In/Out

    bool Read(char*,int ,int) ;
    bool Write(char*);

    // Transfer Methods between QImage and EXimage

    void transfer_to_qim(QImage*);
    void transfer_to_exim(QImage*);

    // For Color case 

    void rgb_to_lum(int);

    // Invert Values

    void invert_values(int);

    // Noise removing

    void gaussian(int);

    // Getting Buffer 

    byte* get_buffer(void) ;

};
