#include "stdafx.h"
#include "ReportCtrlLayout.h"
#include "../TinyXml/tinyxml.h"

CReportCtrlLayout::CReportCtrlLayout()
{
}


CReportCtrlLayout::~CReportCtrlLayout()
{
}

void CReportCtrlLayout::Layout(LPCTSTR lpLayoutFile, CXTPReportControl* pControl)
{
	ASSERT(pControl);

	USES_CONVERSION;
	TiXmlDocument doc(T2A(lpLayoutFile));
	if (!doc.LoadFile())
	{
		return;
	}

	TiXmlElement* root = doc.RootElement();
	if (root)
	{
		TiXmlElement* child = root->FirstChildElement("item");
		while (child)
		{
			int idx = 0, pos = 0, width = 0, visible = 0;
			child->QueryIntAttribute("index", &idx);
			child->QueryIntAttribute("width", &width);
			child->QueryIntAttribute("pos", &pos);
			child->QueryIntAttribute("visible", &visible);
			
			CXTPReportColumn* pColumn = NULL;
			for (int i = 0; i < pControl->GetColumns()->GetCount(); i++)
			{
				if ( pControl->GetColumns()->GetAt(i)->GetItemIndex() == idx)
				{
					pColumn = pControl->GetColumns()->GetAt(i);
					break;
				}
			}
			
			pControl->GetColumns()->GetAt(idx);
			pColumn->SetVisible(visible);
			pColumn->SetWidth(width);
			pControl->GetColumns()->ChangeColumnOrder( pos, pColumn->GetIndex());

			child = child->NextSiblingElement("item");
		}
	}

	pControl->Populate();
}

void CReportCtrlLayout::SaveLayout(LPCTSTR lpLayoutFile, CXTPReportControl* pControl)
{
	ASSERT(pControl);
	USES_CONVERSION;

	TiXmlDocument doc(T2A(lpLayoutFile));
	doc.LinkEndChild(new TiXmlDeclaration("1.0", "gb18030", ""));

	TiXmlElement* root = new TiXmlElement("layout");
	doc.LinkEndChild(root);

	for (int i = 0; i < pControl->GetColumns()->GetCount(); i++)
	{
		CXTPReportColumn* pColumn = pControl->GetColumns()->GetAt(i);
		
		TiXmlElement* item = new TiXmlElement("item");
		item->SetAttribute("index", pColumn->GetItemIndex());
		item->SetAttribute("width", pColumn->GetWidth());
		item->SetAttribute("pos", pColumn->GetIndex());
		item->SetAttribute("visible", pColumn->IsVisible());

		root->LinkEndChild(item);
	}
	doc.SaveFile(T2A(lpLayoutFile));
}
