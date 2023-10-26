#include <SGUIConsole.h>

#if defined _WIN32
#define ClearConsole() system("cls")
#else 
#define ClearConsole() system("clear")
#endif


void SGUI::Console::SetPixelW(int x, int y, const wchar_t* text, WORD color) {
  DWORD dw;
  COORD position;
  position.X = x;
  position.Y = y;
  WORD attribute = color;
  LPCWSTR text_ = text;

  WriteConsoleOutputAttribute(this->hStdOut, &attribute, wcslen(text), position, &dw);
  WriteConsoleOutputCharacterW(this->hStdOut, text_, wcslen(text), position, &dw);
}