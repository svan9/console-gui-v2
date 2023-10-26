#include <SGUIPanel.h>

SGUI::Panel::Panel()
{
}

void SGUI::Panel::AddLine(Line line)
{
  this->_lines.push_back(line);
}

void SGUI::Panel::SetLines(std::vector<Line> lines)
{
  this->_lines = lines;
}

int SGUI::Panel::_getMaxLengthLine()
{ 
  int max = 0, tl;
  for (Line l: this->_lines) {
    tl = l.Text().size();
    if (tl > max) tl = max;
  }   
  return max;
}

std::vector<std::wstring> SGUI::Panel::GenSTR(wchar_t border)
{ 
  std::vector<std::wstring> out;
  int minWidth = _getMaxLengthLine();
  std::wstring str(L"");
  for (int i = 0; i < minWidth+2; i++) {
    str += border;
  }
  out.push_back(str);
  str.clear();
  for (Line l: this->_lines) {
    int startX, len;
    len = l.Text().size();
    switch (l.align) {
      case AlignText::ToCenter:
        startX = (minWidth-len)/2;
        break;
      case AlignText::ToLeft:
        startX = 0;
        break;
      case AlignText::ToRight:
        startX = minWidth-len;
        break;
    }
    str += border;
    for (int i = 1; i < minWidth; i++) {
      str[i] = L'\u2800';
    }
    for (int i = 0; i < minWidth; i++) {
      str[startX+1+i] = l.Text()[i];
    }
    str += border;
    out.push_back(str);
    str.clear();
  }
  for (int i = 0; i < minWidth+2; i++) {
    str += border;
  }
  out.push_back(str);
  str.clear();
  return out;
}




SGUI::Line::Line()
{
  this->align = AlignText::ToLeft;
  this->_text = "";
}

SGUI::Line::Line(std::string text)
{
  this->align = AlignText::ToLeft;
  this->_text = text;
}

std::string SGUI::Line::Text()
{
  return this->_text;
}
void SGUI::Line::Text(std::string text)
{
  this->_text = text;
}
