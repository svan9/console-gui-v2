#ifndef _SGUI_CONSOLE_H_
#define _SGUI_CONSOLE_H_

#include <iostream>
#include <functional>
#include <windows.h>
#include <stdexcept>
#include <string>
#include <vector>


#include <SGUIPanel.h>

namespace SGUI { 
  
  enum STATUS {
    NORMAL,
    EXIT,
    REPEAT,
    OK,
    BADCODE,
    BUSY
  };

  struct FUNCC {
    std::string name;
    std::function<int(void)> fn;
  };

  class Console {
  private:
    const wchar_t* border;
    HANDLE hStdOut;
    Panel _mpanel;
    std::vector<SGUI::FUNCC> functions;
    int fnCounter;

    STATUS ProgStatus;
    STATUS _fnStatus;
    std::string EXIT_CODE;
    std::string CLEAR_CODE;

    SGUI::STATUS _pushInfoPanel();
    SGUI::STATUS _functionHandler();
    void SetPixelW(int x, int y, const wchar_t *text, WORD color);
  public:
    Console();

    STATUS Status();

    bool Update();
    bool Start();

    void AddFunction(std::function<int(void)> handler, std::string name);
  };
};

#endif