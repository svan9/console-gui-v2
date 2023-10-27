#include <SGUIConsole.h>


#if defined _WIN32
#define ClearConsole() system("cls")
#else
#define ClearConsole() system("clear")
#endif

inline bool isInteger(const std::string & s)
{
   if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;
   char * p;
   strtol(s.c_str(), &p, 10);
   return (*p == 0);
}



void printfw(std::wstring str) {
  wprintf(L"%s", str.c_str());
}

SGUI::Console::Console() {
  this->EXIT_CODE = ".exit";
  this->CLEAR_CODE = ".clear";
  this->ProgStatus = STATUS::OK;
  this->fnCounter = 0;

  // title
  this->_mpanel.AddLine(Line{"Info Panel", AlignText::ToCenter, L'~'});
  this->_mpanel.AddGap();
}

SGUI::STATUS SGUI::Console::Status()
{
  return this->ProgStatus;
}

bool SGUI::Console::Start()
{ 
  // exit
  this->_mpanel.AddGap();
  this->_mpanel.AddLine(Line{"enter " + this->EXIT_CODE + " for exit", AlignText::ToLeft});
  // clear
  this->_mpanel.AddLine(Line{"enter " + this->CLEAR_CODE + " for clear", AlignText::ToLeft});
  this->_mpanel.AddGap();

  while (this->Status() != SGUI::STATUS::EXIT) {
    if (this->Status() == SGUI::STATUS::BADCODE) {
      std::cout << "\t!BAD CODE\n";
    }

    if (this->Status() == SGUI::STATUS::BUSY) {
      continue;
    }

    if (this->Status() != SGUI::STATUS::REPEAT) {
      ClearConsole();
      this->_pushInfoPanel();
    }
    this->_functionHandler();
  }
  exit(0);
}


SGUI::STATUS SGUI::Console::_pushInfoPanel() {
  printfw(this->_mpanel.GenSTR(L'*') + L"\n");
}

SGUI::STATUS SGUI::Console::_functionHandler() {
  std::string tstr;
  std::cout << ">>> ";
  std::getline(std::cin, tstr);

  if (tstr == this->EXIT_CODE) {
    this->ProgStatus = SGUI::STATUS::EXIT;
  } else if (tstr == this->CLEAR_CODE) {
    this->ProgStatus = SGUI::STATUS::OK;
  } else if (isInteger(tstr)) {
    this->ProgStatus = SGUI::STATUS::BUSY;
    int code = std::stoi(tstr);
    if (code > this->functions.size()) {
      return (this->ProgStatus = SGUI::STATUS::BADCODE);
    }
    std::cout << "\033[33;3mstart function " << this->functions[code].name << "():\033[0m\n";
    code = this->functions[code].fn();
    if (code == 0) {
      std::cout << "\n";
      return (this->ProgStatus = SGUI::STATUS::REPEAT);
    }
  } else {
    this->ProgStatus = SGUI::STATUS::REPEAT;
  }
}

void SGUI::Console::AddFunction(std::function<int(void)> handler, std::string name)
{
  SGUI::FUNCC f_{name, handler};
  this->functions.push_back(f_);

  this->_mpanel.AddLine(Line{std::to_string(this->fnCounter++) + ". " + name, AlignText::ToLeft});
  // this->_mpanel.AddGap();
}


void SGUI::Console::SetPixelW(int x, int y, const wchar_t* text, WORD color) {
  DWORD dw;
  COORD position;
  position.X = x;
  position.Y = y;
  WORD attribute = color;
  LPCWSTR text_ = text;

  WriteConsoleOutputAttribute(this->hStdOut, &attribute, wcslen(text), position, &dw);
  // WriteConsoleOutputCharacterW(this->hStdOut, text_, wcslen(text), position, &dw);
}


