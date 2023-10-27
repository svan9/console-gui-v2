#include <SGUIPanel.h>
#include <iostream>

SGUI::Panel::Panel()
{
}

void SGUI::Panel::AddLine(Line line)
{
  this->_lines.push_back(line);
}
void SGUI::Panel::AddGap()
{
  this->_lines.push_back(SGUI::Line{""});
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
    if (tl > max) max = tl;
  }   
  return max;
}

std::wstring fillW(wchar_t c, int length) {
  std::wstring out(L"");
  for (int i = 0; i < length; i++) {
    out += c;
  }
  return out;
}

std::vector<std::wstring> SGUI::Panel::GenSTRV(wchar_t border)
{ 
  std::vector<std::wstring> out;
  const int minWidth = _getMaxLengthLine();
  std::wstring str(L"");

  if (this->HasTopBorder()) {
    str = fillW(border, minWidth+4);
    out.push_back(str);
    str.clear();
  }

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
    for (int i = 1; i < minWidth+3; i++) {
      str += l.FillGapS();
    }
    for (int i = 0; i < l.Text().size(); i++) {
      str[startX+2+i] = l.Text()[i];
    }
    str += border;
    out.push_back(str);
    str.clear();
  }
  
  if (this->HasBottomBorder()) {
    str = fillW(border, minWidth+4);
    out.push_back(str);
    str.clear();
  }

  return out;
}

std::wstring SGUI::Panel::GenSTR(wchar_t border) {
  std::vector<std::wstring> in_ = this->GenSTRV(border);
  std::wstring out{L""};
  for (std::wstring str: in_) {
    out += str + L'\n';
  }
  return out;
}

void SGUI::Panel::offBottom()
{
  this->_hasBottomBorder = false;
}
void SGUI::Panel::onBottom()
{
  this->_hasBottomBorder = true;
}

void SGUI::Panel::offTop()
{
  this->_hasTopBorder = false;
}
void SGUI::Panel::onTop()
{
  this->_hasTopBorder = true;
}

bool SGUI::Panel::HasBottomBorder() 
{
  return this->_hasBottomBorder;
}
bool SGUI::Panel::HasTopBorder() 
{
  return this->_hasTopBorder;
}

SGUI::Line::Line()
{
  this->align = AlignText::ToLeft;
  this->_text = "";
  this->_space = L' ';
}

SGUI::Line::Line(std::string text)
{
  this->align = AlignText::ToLeft;
  this->_text = text;
  this->_space = L' ';
}

SGUI::Line::Line(std::string text, AlignText align)
{
  this->align = align;
  this->_text = text;
  this->_space = L' ';
}

SGUI::Line::Line(std::string text, AlignText align, wchar_t space)
{
  this->align = align;
  this->_text = text;
  this->_space = space;
}

wchar_t SGUI::Line::FillGapS()
{
  return this->_space;
}

std::string SGUI::Line::Text()
{
  return this->_text;
}
void SGUI::Line::Text(std::string text)
{
  this->_text = text;
}
