#ifndef _SGUI_CONSOLE_H_
#define _SGUI_CONSOLE_H_

#include <iostream>
#include <functional>
#include <windows.h>
#include <stdexcept>
#include <string>
#include <vector>

namespace SGUI {
 
 
  class Console {
  private:
    const wchar_t* border;
    HANDLE hStdOut;

    void SetPixelW(int x, int y, const wchar_t *text, WORD color);

  public:
    Console();

    bool isExit();
  };
};

#endif