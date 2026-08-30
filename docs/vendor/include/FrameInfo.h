#pragma once


typedef struct encode_frame_info
{
	unsigned int	keyFrame;
	int			nWidth;
	int			nHeight;
	unsigned int	time;

	int			frameIndex;

	unsigned int	dwLen;
	unsigned char	*pData;
}ENCODE_FRAME_INFO;

typedef struct decode_frameInfo
{
	int			nWidth;
	int			nHeight;
	unsigned int	time;

	unsigned int	dwLen;
	unsigned char	*pData;
}DECODE_FRAME_INFO;


