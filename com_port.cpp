#include "Unit1.cpp"
//HANDLE COMport;		//?????????? ?????
//WriteThread *writer;     //?????? ?????? WriteThread
//ReadThread *reader;     //?????? ?????? ReadThread

void COMClose()
{
 if(writer)writer->Terminate();
 if(reader)reader->Terminate();         //???? ????? ?????? ????????, ????????? ???; ???????? if(reader) ???????????, ????? ????????? ??????
 CloseHandle(COMport);
 COMport=0;

 handle=0;
}

void COMOpen()
{
 String portname;     	 //??? ????? (????????, "COM1", "COM2" ? ?.?.)
 DCB dcb;                //????????? ??? ????? ????????????? ????? DCB
 COMMTIMEOUTS timeouts;  //????????? ??? ????????? ?????????

 portname =asd->ComboBox1->Text;

 COMport = CreateFile(portname.c_str(),GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);

 if(COMport == INVALID_HANDLE_VALUE)
  { asd->SpeedButton1->Down = false;
   asd->StatusBar1->Panels->Items[0]->Text = "���������� �� �����������";
   return;
  }
  else
  {
  asd->StatusBar1->Panels->Items[0]->Text = "���������� �����������";
  asd->SpeedButton1->Caption = "Disconnect";

  asd->Button1->Enabled = false;
  }

 dcb.DCBlength = sizeof(DCB); 	//? ?????? ???? ????????? DCB ?????????? ??????? ?? ?????, ??? ????? ?????????????? ????????? ????????? ????? ??? ???????? ???????????? ?????????

 if(!GetCommState(COMport, &dcb))	//???? ?? ??????? - ??????? ???? ? ??????? ????????? ?? ?????? ? ?????? ?????????
  {
   COMClose();
   asd->StatusBar1->Panels->Items[0]->Text ="�� ������� ��������� DCB";
   return;
  }

 dcb.BaudRate = 9600;       //?????? ???????? ???????? 115200 ???
 dcb.fBinary = TRUE;                                    //???????? ???????? ????? ??????
 dcb.fOutxCtsFlow = FALSE;                              //????????? ????? ???????? ?? ???????? CTS
 dcb.fOutxDsrFlow = FALSE;                              //????????? ????? ???????? ?? ???????? DSR
 dcb.fDtrControl = DTR_CONTROL_DISABLE;                 //????????? ????????????? ????? DTR
 dcb.fDsrSensitivity = FALSE;                           //????????? ??????????????? ???????? ? ????????? ????? DSR
 dcb.fNull = FALSE;                                     //????????? ????? ??????? ??????
 dcb.fRtsControl = RTS_CONTROL_DISABLE;                 //????????? ????????????? ????? RTS
 dcb.fAbortOnError = FALSE;                             //????????? ????????? ???? ???????? ??????/?????? ??? ??????
 dcb.ByteSize = 8;                                      //?????? 8 ??? ? ?????
 dcb.Parity = 0;                                        //????????? ???????? ????????
 dcb.StopBits = 0;                                      //?????? ???? ????-???

 if(!SetCommState(COMport, &dcb))	//???? ?? ??????? - ??????? ???? ? ??????? ????????? ?? ?????? ? ?????? ?????????
  {
   COMClose();
   asd->StatusBar1->Panels->Items[0]->Text ="?? ??????? ?????????? DCB";
   return;
  }

 //?????????? ????????
 timeouts.ReadIntervalTimeout = 0;	 	//??????? ????? ????? ?????????
 timeouts.ReadTotalTimeoutMultiplier = 0;	//????? ??????? ???????? ??????
 timeouts.ReadTotalTimeoutConstant = 0;         //????????? ??? ?????? ???????? ???????? ??????
 timeouts.WriteTotalTimeoutMultiplier = 0;      //????? ??????? ???????? ??????
 timeouts.WriteTotalTimeoutConstant = 0;        //????????? ??? ?????? ???????? ???????? ??????

 //???????? ????????? ????????? ? ????
 if(!SetCommTimeouts(COMport, &timeouts))	//???? ?? ??????? - ??????? ???? ? ??????? ????????? ?? ?????? ? ?????? ?????????
  {
   COMClose();
   asd->StatusBar1->Panels->Items[0]->Text ="?? ??????? ?????????? ????-????";
   return;
  }

 SetupComm(COMport,2000,2000);

 PurgeComm(COMport, PURGE_RXCLEAR);	//???????? ??????????? ????? ?????

 reader = new ReadThread(false);	//??????? ? ????????? ????? ?????? ??????
 reader->FreeOnTerminate = true;        //?????????? ??? ???????? ??????, ????? ?? ????????????? ??????????? ????? ??????????

}

