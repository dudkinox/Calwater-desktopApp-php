#include "StdAfx.h"
#include "xml_utils.h"
#include "conversion.h"
#include "tinyxml/tinyxml.h"

namespace XML
{

CStdString ReadText(TiXmlElement* pElement)
{
	TiXmlNode* textNode = pElement->FirstChild();
	if (!textNode || !textNode->ToText())
		return _T("");

	return ConvFromNetwork(textNode->Value());					
}

void SetText(TiXmlElement* pElement, const CStdString& text)
{
	pElement->Clear();
	pElement->LinkEndChild(new TiXmlText(ConvToNetwork(text)));
}

}