#include "stdinlistner.h"

stdInListner::stdInListner(QObject *parent):QThread(parent)
{
    
}

stdInListner::~stdInListner(){
    terminate();
    wait();
}


void stdInListner::run(){
      bool ok = true;
      char chBuf[4096];
      DWORD dwRead;
      HANDLE hStdinDup;

      const HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
      if (hStdin == INVALID_HANDLE_VALUE)
          return;

      DuplicateHandle(GetCurrentProcess(), hStdin,
          GetCurrentProcess(), &hStdinDup,
          0, false, DUPLICATE_SAME_ACCESS);

      CloseHandle(hStdin);

      while (ok) {
          ok = ReadFile(hStdinDup, chBuf, sizeof(chBuf), &dwRead, NULL);
          if (ok && dwRead != 0)
              emit receivedCommand(QString::fromLocal8Bit(chBuf, dwRead));
      }
}

