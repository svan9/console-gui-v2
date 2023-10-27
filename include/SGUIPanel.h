#ifndef _SGUI_PANEL_H
#define _SGUI_PANEL_H

#include <string>
#include <vector>

namespace SGUI {
  enum AlignText {ToLeft, ToCenter, ToRight};
  
  class Line {
  private:
    std::string _text;
    wchar_t _space;
  public: 
    AlignText align;

    Line();
    Line(std::string text);
    Line(std::string text, AlignText align);
    Line(std::string text, AlignText align, wchar_t space);

    void Text(std::string text);
    wchar_t FillGapS();

    std::string Text();
  };
  

  class Panel {
  private:
    std::vector<Line> _lines;
       
    int _getMaxLengthLine();
    bool _hasBottomBorder;
    bool _hasTopBorder;
  public:
    Panel();
    void AddLine(Line line);
    void AddGap();
    void SetLines(std::vector<Line> lines);


    void offBottom();
    void onBottom();

    void offTop();
    void onTop();

    bool HasBottomBorder();
    bool HasTopBorder();

    std::wstring GenSTR(wchar_t border);
    std::vector<std::wstring> GenSTRV(wchar_t border);
  };

}

#endif 