#ifndef __CONVERSION_H__
#define __CONVERSION_H__

CStdStringW ConvFromNetwork(const char* buffer);
char* ConvToNetworkW(const CStdStringW& str);
char* ConvToNetworkA(const CStdStringA& str);
#ifdef _UNICODE
#define ConvToNetwork ConvToNetworkW
#else
#define ConvToNetwork ConvToNetworkA
#endif
CStdStringA ConvToLocal(const CStdStringW& str);
CStdStringW ConvFromLocal(const CStdStringA& str);

#endif //__CONVERSION_H__