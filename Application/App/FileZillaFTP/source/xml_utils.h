#ifndef __XML_UTILS_H__
#define __XML_UTILS_H__

class TiXmlElement;

namespace XML
{

CStdString ReadText(TiXmlElement* pElement);
void SetText(TiXmlElement* pElement, const CStdString& text);

}

#endif //__XML_UTIL	S_H__