object asd: Tasd
  Left = 190
  Top = 150
  BorderStyle = bsDialog
  Caption = #1055#1088#1086#1074#1077#1088#1082#1072' '#1084#1086#1076#1091#1083#1103' '#1057#1056#1050'-'#1052'2'
  ClientHeight = 500
  ClientWidth = 785
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDefault
  Visible = True
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 4
    Top = 4
    Width = 325
    Height = 109
    Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080' COM '#1087#1086#1088#1090#1072
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    object SpeedButton1: TSpeedButton
      Left = 24
      Top = 64
      Width = 85
      Height = 29
      AllowAllUp = True
      GroupIndex = 1
      Caption = 'Connect'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      OnClick = SpeedButton1Click
    end
    object Label2: TLabel
      Left = 176
      Top = 12
      Width = 66
      Height = 13
      Caption = #1053#1086#1084#1077#1088' '#1087#1086#1088#1090#1072
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Button1: TButton
      Left = 24
      Top = 24
      Width = 85
      Height = 29
      Caption = 'Scan'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = Button1Click
    end
    object ComboBox1: TComboBox
      Left = 168
      Top = 32
      Width = 85
      Height = 21
      Style = csDropDownList
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemHeight = 13
      ParentFont = False
      TabOrder = 1
    end
  end
  object GroupBox2: TGroupBox
    Left = 4
    Top = 120
    Width = 777
    Height = 341
    Caption = #1058#1077#1089#1090#1080#1088#1086#1074#1072#1085#1080#1077' '#1084#1086#1076#1091#1083#1103
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
    object Label4: TLabel
      Left = 161
      Top = 20
      Width = 104
      Height = 13
      Caption = #1057#1086#1089#1090#1086#1103#1085#1080#1077' DIP-swish'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label3: TLabel
      Left = 155
      Top = 92
      Width = 142
      Height = 13
      Caption = #1046#1091#1088#1085#1072#1083' '#1087#1088#1086#1074#1077#1088#1082#1080' DIP-swich'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object StringGrid3: TStringGrid
      Left = 444
      Top = 28
      Width = 305
      Height = 105
      ColCount = 2
      DefaultColWidth = 150
      FixedColor = 16776176
      RowCount = 4
      FixedRows = 0
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnDrawCell = StringGrid3DrawCell
      RowHeights = (
        24
        24
        26
        24)
    end
    object StringGrid2: TStringGrid
      Left = 28
      Top = 40
      Width = 389
      Height = 33
      ColCount = 6
      DefaultColWidth = 60
      DefaultRowHeight = 30
      FixedColor = clBtnHighlight
      FixedCols = 0
      RowCount = 1
      FixedRows = 0
      GridLineWidth = 5
      TabOrder = 1
      OnDrawCell = StringGrid2DrawCell
      RowHeights = (
        30)
    end
    object Memo1: TMemo
      Left = 28
      Top = 112
      Width = 393
      Height = 213
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      Lines.Strings = (
        'Memo1')
      ParentFont = False
      TabOrder = 2
    end
  end
  object GroupBox3: TGroupBox
    Left = 332
    Top = 4
    Width = 449
    Height = 109
    Caption = #1048#1085#1092#1086#1088#1084#1072#1094#1080#1103' '#1086' '#1084#1086#1076#1091#1083#1077
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
    object StringGrid1: TStringGrid
      Left = 24
      Top = 32
      Width = 381
      Height = 53
      ColCount = 2
      FixedColor = 16776176
      FixedCols = 0
      RowCount = 2
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnDrawCell = StringGrid1DrawCell
      ColWidths = (
        217
        158)
    end
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 467
    Width = 785
    Height = 33
    Panels = <
      item
        Width = 392
      end
      item
        Width = 50
      end>
    SimplePanel = False
  end
  object Timer1: TTimer
    Interval = 500
    OnTimer = Timer1Timer
    Left = 628
    Top = 320
  end
  object Timer2: TTimer
    Interval = 500
    OnTimer = Timer2Timer
    Left = 676
    Top = 320
  end
  object Timer3: TTimer
    Interval = 100
    OnTimer = Timer3Timer
    Left = 720
    Top = 320
  end
end
