#ifndef LAVITYPES_H
#define LAVITYPES_H


typedef struct {
    unsigned short  wFormatTag;
    unsigned short  nChannels;
    unsigned int   nSamplesPerSec;
    unsigned int   nAvgBytesPerSec;
    unsigned short  nBlockAlign;
} __attribute__((packed)) WAVEFORMAT;

typedef struct tWAVEFORMATEX
{
    unsigned short       wFormatTag;         /* format type */
    unsigned short       nChannels;          /* number of channels (i.e. mono, stereo...) */
    unsigned int       nSamplesPerSec;     /* sample rate */
    unsigned int       nAvgBytesPerSec;    /* for buffer estimation */
    unsigned short        nBlockAlign;        /* block size of data */
    unsigned short        wBitsPerSample;     /* number of bits per sample of mono data */
    unsigned short        cbSize;             /* the count in bytes of the size of */
				    /* extra information (after cbSize) */
} __attribute__((packed)) WAVEFORMATEX;

typedef struct mpeg1waveformat_tag {
	WAVEFORMATEX    wfx;
	unsigned short	fwHeadLayer;
	unsigned int	dwHeadBitrate;
	unsigned short	fwHeadMode;
	unsigned short	fwHeadModeExt;
	unsigned short	wHeadEmphasis;
	unsigned short	fwHeadFlags;
	unsigned int	dwPTSLow;
	unsigned int	dwPTSHigh;
} __attribute__((packed)) MPEG1WAVEFORMAT; // 40

typedef	MPEG1WAVEFORMAT	*PMPEG1WAVEFORMAT;

typedef struct mpeglayer3waveformat_tag {
	WAVEFORMATEX  wfx;
	unsigned short	wID;
	unsigned short	fdwFlags;
	unsigned short	nBlockSize;
	unsigned short	nFramesPerBlock;
	unsigned short	nCodecDelay;
} __attribute__((packed)) MPEGLAYER3WAVEFORMAT;

//
//  IMA endorsed ADPCM structure definitions--note that this is exactly
//  the same format as Intel's DVI ADPCM.
//
//      for WAVE_FORMAT_IMA_ADPCM   (0x0011)
//
//
typedef struct ima_adpcmwaveformat_tag {
	WAVEFORMATEX    wfx;
	//WORD            wSamplesPerBlock;
	unsigned short  wSamplesPerBlock;
} __attribute__((packed)) IMAADPCMWAVEFORMAT;

typedef struct tagBITMAPINFOHEADER{ // bmih
	unsigned int  biSize;
	int   biWidth;
	int   biHeight;
	unsigned short   biPlanes;
	unsigned short   biBitCount;
	unsigned int  biCompression;
	unsigned int  biSizeImage;
	int   biXPelsPerMeter;
	int   biYPelsPerMeter;
	unsigned int  biClrUsed;
	unsigned int  biClrImportant;
}__attribute__((packed)) BITMAPINFOHEADER;

typedef struct tagBITMAPFILEHEADER
{
	unsigned short  bfType;
	unsigned int	bfSize;
	unsigned short  bfReserved1;
	unsigned short  bfReserved2;
	unsigned int   bfOffBits;
} __attribute__((packed))BITMAPFILEHEADER, *PBITMAPFILEHEADER;

typedef struct tagRGBQUAD {
	unsigned char    rgbBlue;
	unsigned char    rgbGreen;
	unsigned char    rgbRed;
	unsigned char    rgbReserved;
} __attribute__((packed))RGBQUAD;

#ifndef mmioFOURCC
#define mmioFOURCC( ch0, ch1, ch2, ch3 ) \
	( (unsigned int)(unsigned char)(ch0) | ( (unsigned int)(unsigned char)(ch1) << 8 ) |	\
	( (unsigned int)(unsigned char)(ch2) << 16 ) | ( (unsigned int)(unsigned char)(ch3) << 24 ) )
#endif

typedef struct
{
	unsigned int	ckid;
	unsigned int	dwFlags;
	unsigned int	dwChunkOffset;		// Position of chunk
	unsigned int	dwChunkLength;		// Length of chunk
} __attribute__((packed)) AVIINDEXENTRY;

#define WAVE_FORMAT_PCM			0x0001
#define WAVE_FORMAT_ALAW		0x0006  /*  Microsoft Corporation  */
#define WAVE_FORMAT_MULAW		0x0007  /*  Microsoft Corporation  */
#define WAVE_FORMAT_IMA_ADPCM	0x0011  /*  Intel Corporation  */
#define WAVE_FORMAT_MPEG		0x0050  /*  Microsoft Corporation  */
#define WAVE_FORMAT_MPEGLAYER3	0x0055  /*  ISO/MPEG Layer3 Format Tag */
#define WAVE_FORMAT_DVI_ADPCM	WAVE_FORMAT_IMA_ADPCM
#define WAVE_FORMAT_G726_ADPCM	0x0064
#define AVIERR_OK		0
#define AVIERR_ERROR	1



#endif
