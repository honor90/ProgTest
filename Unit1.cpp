//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <stdlib.h>
#include "Unit1.h"
#include "com_port.cpp"
#include "analisys.cpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "sCustomComboEdit"
#pragma link "sMaskEdit"
#pragma link "sTooledit"
#pragma link "acPNG"
#pragma resource "*.dfm"
Tasd *asd;


        public int number  = -1;
        public int number0 = -1;
        public int number1 = -1;
        public int number2 = -1;
        public int number3 = -1;
        public int number4 = -1;
        public int number5 = -1;

        public int num1_green = -1;
        public int num2_green = -1;
        public int num3_green = -1;
        public int num4_green = -1;

        public int num1_red = -1;
        public int num2_red = -1;
        public int num3_red = -1;
        public int num4_red = -1;

        public int var_time = 0;

        public int number_old;

        public int buf_data[100];
        public int type_module;
        public int temperature;
        public int address;
        public int old_address = 0x00;
        public int end_rest;
        public int test_rs485;
        public int test_pin;
        public int test_rele;

        public int var_module=1;
        public int var_pin=1;
        public int var_rs485=1;
        public int var_temperature=1;
        public int var_text=1;
        public int var_rele;



         

        public HANDLE com_status;
        public DWORD bytesWriteen;
        public DWORD bytesRead;


     public DWORD btr;



//---------------------------------------------------------------------------
__fastcall Tasd::Tasd(TComponent* Owner)
        : TForm(Owner)
{

}
//=============================================================================
//=============================================================================

#define BUFSIZE 255

unsigned char bufrd[BUFSIZE], bufwr[BUFSIZE];
__int8 buff[10];
__int8 i = 0;

//---------------------------------------------------------------------------

public HANDLE COMport;		//?????????? ?????
public HANDLE COMscan;

OVERLAPPED overlapped;		//????? ???????????? ??? ???????? ?????? (??. ????? ReadThread)
OVERLAPPED overlappedwr;       	//????? ???????????? ??? ???????? ?????? (??. ????? WriteThread)

//---------------------------------------------------------------------------

int handle;             	//?????????? ??? ?????? ? ?????? ? ??????? ?????????? <io.h>

//---------------------------------------------------------------------------

bool fl=0;	//????, ??????????? ?? ?????????? ???????? ?????? (1 - ???????, 0 - ?? ???????)

unsigned long counter=0;	//??????? ???????? ??????, ?????????? ??? ?????? ???????? ?????


//=============================================================================
//.............................. ?????????? ??????? ...........................
//=============================================================================

void COMOpen(void);             //??????? ????
void COMClose(void);            //??????? ????

//=============================================================================
//.............................. ?????????? ??????? ...........................


//????? ??? ?????? ?????????????????? ?????? ?? COM-????? ? ?????
class ReadThread : public TThread
{
 private:
        void __fastcall Printing();	//????? ???????? ?????? ?? ????? ? ? ????
 protected:
        void __fastcall Execute();	//???????? ??????? ??????
 public:
        __fastcall ReadThread(bool CreateSuspended);	//??????????? ??????
};

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
class WriteThread : public TThread
{
private:
 	void __fastcall Printing();	//????? ????????? ?? ?????
protected:
        void __fastcall Execute();      //???????? ??????? ??????
public:
        __fastcall WriteThread(bool CreateSuspended);	//??????????? ??????
};
//---------------------------------------------------------------------------
//=============================================================================
//.............................. ?????????? ??????? ...........................
//=============================================================================

//-----------------------------------------------------------------------------
//............................... ????? ReadThead .............................
//-----------------------------------------------------------------------------

public ReadThread *reader;     //?????? ?????? ReadThread

//---------------------------------------------------------------------------

//??????????? ?????? ReadThread, ?? ????????? ??????
__fastcall ReadThread::ReadThread(bool CreateSuspended) : TThread(CreateSuspended)
{}

//---------------------------------------------------------------------------

void __fastcall ReadThread::Execute()
{
 COMSTAT comstat;
 DWORD  temp, mask, signal;

 overlapped.hEvent = CreateEvent(NULL, true, true, NULL);
 SetCommMask(COMport, EV_RXCHAR);
 while(!Terminated)
  {
   WaitCommEvent(COMport, &mask, &overlapped);
   signal = WaitForSingleObject(overlapped.hEvent, INFINITE);
   if(signal == WAIT_OBJECT_0)
    {
     if(GetOverlappedResult(COMport, &overlapped, &temp, true))
      if((mask & EV_RXCHAR)!=0)
       {
        ClearCommError(COMport, &temp, &comstat);
        btr = comstat.cbInQue;
        if(btr)
        {
         ReadFile(COMport, bufrd, btr, &temp, &overlapped);

         buff[counter]= bufrd[0];
         counter++;
         Synchronize(Printing);

        }
       }
    }
  }
 CloseHandle(overlapped.hEvent);
}

//-----------------------------------------------------------------------------
//............................... ????? WriteThead ............................
//-----------------------------------------------------------------------------

public WriteThread *writer;     //?????? ?????? WriteThread

//---------------------------------------------------------------------------

//??????????? ?????? WriteThread, ?? ????????? ??????
__fastcall WriteThread::WriteThread(bool CreateSuspended) : TThread(CreateSuspended)
{}

//---------------------------------------------------------------------------

void __fastcall WriteThread::Execute()
{
 DWORD temp, signal;

 overlappedwr.hEvent = CreateEvent(NULL, true, true, NULL);   	  //??????? ???????
 WriteFile(COMport, bufwr, strlen(bufwr), &temp, &overlappedwr);  //???????? ????? ? ???? (????????????? ????????!)
 signal = WaitForSingleObject(overlappedwr.hEvent, INFINITE);	  //????????????? ?????, ???? ?? ?????????? ????????????? ???????? WriteFile
 if((signal == WAIT_OBJECT_0) && (GetOverlappedResult(COMport, &overlappedwr, &temp, true))) fl = true; //???? ???????? ??????????? ???????, ?????????? ??????????????? ??????
 else fl = false;
 CloseHandle(overlappedwr.hEvent);
}

//---------------------------------------------------------------------------
void __fastcall WriteThread::Printing()
{
}



//---------------------------------------------------------------------------
void __fastcall ReadThread::Printing()
{
if(counter==2)
{
asd->StatusBar1->Panels->Items[1]->Text ="������ ����������";
counter=0;
switch( buff[0])
{
case 0x11:
type_module = buff[1];
break;
case 0x62:
temperature = buff[1];
if (var_temperature)
{
if (temperature)
{ num1_green = 0;
asd->StringGrid3->Cells[1][0]=temperature;
var_temperature=0;
temperature=0x00;
}
}
break;
case 0x38:
address = buff[1];

if (old_address < address)
{
dip_analisys();
}
var_time = 0;
asd->StringGrid2->Repaint();
break;
case 0x04:
test_pin = buff[1];
break;
case 0x05:
test_rele = buff[1];
break;
case 0x77:
test_rs485 = buff[1];
break;
}


if(var_module)
{
switch(type_module)
{
case 0x15:
asd->StringGrid1->Cells[0][1]="������ ����� ���������";
asd->StringGrid1->Cells[1][1]="���-�2-��";
break;
case 0x16:
asd->StringGrid1->Cells[0][1]="������ ������������� ����������";
asd->StringGrid1->Cells[1][1]="���-�2-��";
break;
case 0x17:
asd->StringGrid1->Cells[0][1]="������ ��������� ����������" ;
asd->StringGrid1->Cells[1][1]="���-�2-�" ;
break;
case 0x18:
asd->StringGrid1->Cells[0][1]="������ ������� �����������";
asd->StringGrid1->Cells[1][1]="���-�2-��";
break;
}
var_module=0;
}


if (var_pin)
{
asd->StringGrid3->Cells[1][2]="�����������";
switch(test_pin)
{
case 0x01:
num2_green = 1;
asd->StringGrid3->Cells[1][1]="��������";
break;
case 0x02:
num2_red = 1;
asd->StringGrid3->Cells[1][1]="�� �������� ���";
break;
case 0x03:
num2_red = 1;
asd->StringGrid3->Cells[1][1]="�� �������� START";
break;
case 0x04:
num2_red = 1;
asd->StringGrid3->Cells[1][1]="�� �������� AVAR";
break;
}
var_pin=0;
}

if(var_rele)
{
switch(test_rele)
{
case 0x01:
asd->StringGrid3->Cells[1][2]="��������";
break;
case 0x02:
asd->StringGrid3->Cells[1][2]="�� �������� REL TST";
break;
case 0x03:
asd->StringGrid3->Cells[1][2]="�� �������� IN1";
break;
}
}

if (var_rs485)
{
switch(test_rs485)
{
case 0x22:
num4_green = 3;
asd->StringGrid3->Cells[1][3]="��������";
break;
case 0x33:
num4_red = 3;
asd->StringGrid3->Cells[1][3]="�� ��������";
break;
}
var_rs485=0;
}


if (var_text)
{
  asd->Memo1->Lines->Add("������ �����");
  asd->Memo1->Lines->Add("���������� ������������� �1 � ��������� ON");
  var_text=0;
}

buff[0]=0x00;
buff[1]=0x00;

var_time = 0;

memset(bufrd, 0, BUFSIZE);
 }
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void __fastcall Tasd::FormCreate(TObject *Sender)
{
asd->StringGrid1->Cells[0][0]="��� ������";
asd->StringGrid1->Cells[1][0]="������";

asd->StringGrid3->Cells[0][0]="�������� �����������";
asd->StringGrid3->Cells[0][1]="��������� ������������";
asd->StringGrid3->Cells[0][2]="��������� ����";
asd->StringGrid3->Cells[0][3]="��������� 485 ����������";
   var_module=1;
   var_pin=1;
   var_rs485=1;
   var_temperature=1;
   var_text=1;

asd->StatusBar1->Panels->Items[1]->Text = " ";

asd->Memo1->Lines->Clear();
}
//---------------------------------------------------------------------------
void __fastcall Tasd::StringGrid2DrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
if(ACol <= number && ARow == 0 ) // ���������� ���������� ������ {
{
asd->StringGrid2->Canvas->Brush->Color = clGreen;
asd->StringGrid2->Canvas->FillRect(Rect);

}
else
{
asd->StringGrid2->Canvas->Brush->Color = clBlue;
asd->StringGrid2->Canvas->FillRect(Rect);
}
if(ACol == number0 && ARow == 0 ) // ���������� ���������� ������ {
{
asd->StringGrid2->Canvas->Brush->Color = clRed;
asd->StringGrid2->Canvas->FillRect(Rect);
}
if(ACol == number1 && ARow == 0 ) // ���������� ���������� ������ {
{
asd->StringGrid2->Canvas->Brush->Color = clRed;
asd->StringGrid2->Canvas->FillRect(Rect);
}
if(ACol == number2 && ARow == 0 ) // ���������� ���������� ������ {
{
asd->StringGrid2->Canvas->Brush->Color = clRed;
asd->StringGrid2->Canvas->FillRect(Rect);
}
if(ACol == number3 && ARow == 0 ) // ���������� ���������� ������ {
{
asd->StringGrid2->Canvas->Brush->Color = clRed;
asd->StringGrid2->Canvas->FillRect(Rect);
}
if(ACol == number4 && ARow == 0 ) // ���������� ���������� ������ {
{
asd->StringGrid2->Canvas->Brush->Color = clRed;
asd->StringGrid2->Canvas->FillRect(Rect);
}
if(ACol == number5 && ARow == 0 ) // ���������� ���������� ������ {
{
asd->StringGrid2->Canvas->Brush->Color = clRed;
asd->StringGrid2->Canvas->FillRect(Rect);
}

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------




void __fastcall Tasd::SpeedButton1Click(TObject *Sender)
{
 if(asd->SpeedButton1->Down==true)
  {
   COMOpen();
   asd->StringGrid2->Repaint(); // �����������
}
  else
  {
   COMClose();
   asd->Button1->Enabled = true;
   asd->Memo1->Lines->Clear();   //��������    Memo1
   SpeedButton1->Caption = "Connect";

     buff[0]=0x00;
     buff[1]=0x00;

 asd->StringGrid1->Rows[1]->Clear();
 asd->StringGrid3->Cols[1]->Clear();

   var_module=1;
   var_pin=1;
   var_rs485=1;
   var_temperature=1;
   var_text=1;

  number  = -1;
  number0 = -1;
  number1 = -1;
  number2 = -1;
  number3 = -1;
  number4 = -1;
  number5 = -1;

        num1_green = -1;
        num2_green = -1;
        num3_green = -1;
        num4_green = -1;

        num1_red = -1;
        num2_red = -1;
        num3_red = -1;
        num4_red = -1;

  asd->StringGrid2->Repaint();

         type_module=0;
         temperature=0x00;
         address=0;
         old_address=0;
         end_rest=0;

   asd->StatusBar1->Panels->Items[0]->Text = " ";
   asd->StatusBar1->Panels->Items[1]->Text = " ";
   }

}
//-------------------------------------------------------------------------
TGridRect rect;

void __fastcall Tasd::StringGrid3DrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
        rect.Top = -1;
        rect.Left = -1;
        rect.Right = -1;
        rect.Bottom = -1;
        StringGrid3->Selection = rect;

if(asd->StringGrid3->Row == ARow && asd->StringGrid3->Col == ACol && asd->StringGrid3->Focused())
asd->StringGrid3->Canvas->DrawFocusRect(Rect);


if(ACol == 1 && ARow == num1_green ) // ���������� ���������� ������ {
{
asd->StringGrid3->Canvas->Brush->Color = clGreen;
asd->StringGrid3->Canvas->FillRect(Rect);

asd->StringGrid3->Canvas->TextOutA(Rect.left+1,Rect.Top+1, //������������ ����� � ������
asd->StringGrid3->Cells[ACol][ARow]);
}
if(ACol == 1 && ARow == num2_green ) // ���������� ���������� ������ {
{
asd->StringGrid3->Canvas->Brush->Color = clGreen;
asd->StringGrid3->Canvas->FillRect(Rect);

asd->StringGrid3->Canvas->TextOutA(Rect.left+1,Rect.Top+1, //������������ ����� � ������
asd->StringGrid3->Cells[ACol][ARow]);
}
if(ACol == 1 && ARow == num3_green ) // ���������� ���������� ������ {
{
asd->StringGrid3->Canvas->Brush->Color = clGreen;
asd->StringGrid3->Canvas->FillRect(Rect);

asd->StringGrid3->Canvas->TextOutA(Rect.left+1,Rect.Top+1, //������������ ����� � ������
asd->StringGrid3->Cells[ACol][ARow]);
}
if(ACol == 1 && ARow == num4_green ) // ���������� ���������� ������ {
{
asd->StringGrid3->Canvas->Brush->Color = clGreen;
asd->StringGrid3->Canvas->FillRect(Rect);

asd->StringGrid3->Canvas->TextOutA(Rect.left+1,Rect.Top+1, //������������ ����� � ������
asd->StringGrid3->Cells[ACol][ARow]);
}
if(ACol == 1 && ARow == num1_red ) // ���������� ���������� ������ {
{
asd->StringGrid3->Canvas->Brush->Color = clRed;
asd->StringGrid3->Canvas->FillRect(Rect);

asd->StringGrid3->Canvas->TextOutA(Rect.left+1,Rect.Top+1, //������������ ����� � ������
asd->StringGrid3->Cells[ACol][ARow]);
}
if(ACol == 1 && ARow == num2_red ) // ���������� ���������� ������ {
{
asd->StringGrid3->Canvas->Brush->Color = clRed;
asd->StringGrid3->Canvas->FillRect(Rect);

asd->StringGrid3->Canvas->TextOutA(Rect.left+1,Rect.Top+1, //������������ ����� � ������
asd->StringGrid3->Cells[ACol][ARow]);
}
if(ACol == 1 && ARow == num3_red ) // ���������� ���������� ������ {
{
asd->StringGrid3->Canvas->Brush->Color = clRed;
asd->StringGrid3->Canvas->FillRect(Rect);

asd->StringGrid3->Canvas->TextOutA(Rect.left+1,Rect.Top+1, //������������ ����� � ������
asd->StringGrid3->Cells[ACol][ARow]);
}
if(ACol == 1 && ARow == num4_red ) // ���������� ���������� ������ {
{
asd->StringGrid3->Canvas->Brush->Color = clRed;
asd->StringGrid3->Canvas->FillRect(Rect);

asd->StringGrid3->Canvas->TextOutA(Rect.left+1,Rect.Top+1, //������������ ����� � ������
asd->StringGrid3->Cells[ACol][ARow]);
}
}
//---------------------------------------------------------------------------
void __fastcall Tasd::StringGrid1DrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
        rect.Top = -1;
        rect.Left = -1;
        rect.Right = -1;
        rect.Bottom = -1;
        StringGrid1->Selection = rect;

if(asd->StringGrid1->Row == ARow && asd->StringGrid1->Col == ACol && asd->StringGrid1->Focused())
asd->StringGrid1->Canvas->DrawFocusRect(Rect);

}
//---------------------------------------------------------------------------
void __fastcall Tasd::FormClose(TObject *Sender, TCloseAction &Action)
{
 if(reader)reader->Terminate(); 	//????????? ????? ?????? ?? ?????, ???????? if(reader) ???????????, ????? ????????? ??????
 if(writer)writer->Terminate();         //????????? ????? ?????? ? ????, ???????? if(writer) ???????????, ????? ????????? ??????
 if(COMport)CloseHandle(COMport);
}
//---------------------------------------------------------------------------
void __fastcall Tasd::Timer1Timer(TObject *Sender)
{
 if (buff[0]==0x00 & buff[1]==0x00)
{
   var_module=1;
   var_pin=1;
   var_rs485=1;
   var_temperature=1;

 if (var_time >= 5)
 { asd->StringGrid1->Rows[1]->Clear();
   asd->StringGrid3->Cols[1]->Clear();
  var_text=1;
  number  = -1;
  number0 = -1;
  number1 = -1;
  number2 = -1;
  number3 = -1;
  number4 = -1;
  number5 = -1;

        num1_green = -1;
        num2_green = -1;
        num3_green = -1;
        num4_green = -1;

        num1_red = -1;
        num2_red = -1;
        num3_red = -1;
        num4_red = -1;

  old_address=0x00;
  address=0x00;
  asd->StringGrid2->Repaint();
  var_time = 0;
  asd->Memo1->Lines->Clear();

         type_module=0;
         temperature=0x00;
         end_rest=0;
   asd->StatusBar1->Panels->Items[1]->Text ="���������� ������ � ������";
  }


}
}
//---------------------------------------------------------------------------
void __fastcall Tasd::Button1Click(TObject *Sender)
{
 char com[]="COM";
 char port;
 char buffer [33];
 asd->ComboBox1->Items->Clear();
 for (int i =0; i<256; i++ )
 {
 itoa (i, buffer, 10);
 strcat(com,buffer);
 COMscan = CreateFile(com,GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);

 if(!(COMscan == INVALID_HANDLE_VALUE))
  {
  asd->ComboBox1->Items->Add(com);
  CloseHandle(COMscan);
  }
  memset(buffer, 0, 33);
  memset(com, 0, 33);
  com[0]='C' ;
  com[1]='O';
  com[2]='M' ;
  }

  asd->ComboBox1->ItemIndex =0;
}
//---------------------------------------------------------------------------
void __fastcall Tasd::Timer2Timer(TObject *Sender)
{
memset(bufwr,0,BUFSIZE);
PurgeComm(COMport, PURGE_TXCLEAR);
strcpy(bufwr,"P");

writer = new WriteThread(false);
writer->FreeOnTerminate = true;
buff[0]=0x00;
buff[1]=0x00;
}
//---------------------------------------------------------------------------



void __fastcall Tasd::Timer3Timer(TObject *Sender)
{
 var_time++;

}
//---------------------------------------------------------------------------



