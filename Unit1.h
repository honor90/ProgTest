//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "sCustomComboEdit.hpp"
#include "sMaskEdit.hpp"
#include "sTooledit.hpp"
#include <Mask.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include "acPNG.hpp"
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class Tasd : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TSpeedButton *SpeedButton1;
        TLabel *Label2;
        TGroupBox *GroupBox2;
        TStringGrid *StringGrid3;
        TStringGrid *StringGrid2;
        TLabel *Label4;
        TLabel *Label3;
        TGroupBox *GroupBox3;
        TStringGrid *StringGrid1;
        TStatusBar *StatusBar1;
        TTimer *Timer1;
        TButton *Button1;
        TComboBox *ComboBox1;
        TTimer *Timer2;
        TMemo *Memo1;
        TTimer *Timer3;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall StringGrid2DrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall StringGrid3DrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
        void __fastcall StringGrid1DrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Timer2Timer(TObject *Sender);
        void __fastcall Timer3Timer(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall Tasd(TComponent* Owner);
        int num;
        int buf_data[100];
        int type_module;
        int temperature;
        int address;
        int dip;
        HANDLE com_status;
};
//---------------------------------------------------------------------------
extern PACKAGE Tasd *asd;
//---------------------------------------------------------------------------
#endif
