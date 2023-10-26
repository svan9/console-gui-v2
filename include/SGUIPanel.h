#ifndef _SGUI_PANEL_H
#define _SGUI_PANEL_H

#include <string>
#include <vector>

namespace SGUI {
  enum AlignText {ToLeft, ToCenter, ToRight};
  
  class Line {
  private:
    std::string _text;
  public: 
    AlignText align;

    Line();
    Line(std::string text);

    void Text(std::string text);
    std::string Text();
  };

  class Panel {
  private:
    std::vector<Line> _lines;
    int _getMaxLengthLine();
  public:
    Panel();
    void AddLine(Line line);
    void SetLines(std::vector<Line> lines);

    std::vector<std::wstring> GenSTR(wchar_t border);
  };

}

#endif 