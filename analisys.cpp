#include "Unit1.cpp"

void dip_analisys(void)
{

number++;

switch(number)
{
case 0:
if(address != 0x01) number0=0;
old_address = 0x01;
break;
case 1:
if(address != 0x02) number1=1;
old_address = 0x02;
break;
case 2:
if(address != 0x04) number2=2;
old_address = 0x04;
break;
case 3:
if(address != 0x08) number3=3;
old_address = 0x08;
break;
case 4:
if(address != 0x10) number4=4;
old_address = 0x10;
break;
case 5:
if(address != 0x20) number5=5;
old_address = 0x20;
break;
}

var_text = 1;
if (var_text)
{
var_text = 0;
switch(number)
{
case 0:
asd->Memo1->Lines->Add("���������� ������������� �1 � ��������� OFF");
asd->Memo1->Lines->Add("���������� ������������� �2 � ��������� ON");
break;
case 1:
asd->Memo1->Lines->Add("���������� ������������� �2 � ��������� OFF");
asd->Memo1->Lines->Add("���������� ������������� �3 � ��������� ON");
break;
case 2:
asd->Memo1->Lines->Add("���������� ������������� �3 � ��������� OFF");
asd->Memo1->Lines->Add("���������� ������������� �4 � ��������� ON");
break;
case 3:
asd->Memo1->Lines->Add("���������� ������������� �4 � ��������� OFF");
asd->Memo1->Lines->Add("���������� ������������� �5 � ��������� ON");
break;
case 4:
asd->Memo1->Lines->Add("���������� ������������� �5 � ��������� OFF");
asd->Memo1->Lines->Add("���������� ������������� �6 � ��������� ON");
break;
case 5:
asd->Memo1->Lines->Add("���������� ������������� �6 � ��������� OFF");
asd->Memo1->Lines->Add("���� ��������");
break;
}
}

}