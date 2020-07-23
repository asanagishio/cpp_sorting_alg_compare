object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 
    'Performance Evaluation for Sorting Algorithms by Wei-ran Zhu ver' +
    '.0.1.0'
  ClientHeight = 665
  ClientWidth = 818
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 0
    Top = 207
    Width = 818
    Height = 3
    Cursor = crVSplit
    Align = alTop
    ExplicitTop = 201
    ExplicitWidth = 464
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 818
    Height = 207
    Align = alTop
    TabOrder = 0
    object GroupBox1: TGroupBox
      Left = 16
      Top = 16
      Width = 241
      Height = 169
      Caption = 'Input parameters'
      TabOrder = 0
      object Label1: TLabel
        Left = 31
        Top = 37
        Width = 82
        Height = 13
        Caption = 'Execution times: '
      end
      object Label2: TLabel
        Left = 84
        Top = 77
        Width = 29
        Height = 13
        Caption = 'N += '
      end
      object Label3: TLabel
        Left = 53
        Top = 118
        Width = 60
        Height = 13
        Caption = 'Variables 1~'
      end
      object Edit1: TEdit
        Left = 119
        Top = 34
        Width = 88
        Height = 21
        TabOrder = 0
      end
      object Edit2: TEdit
        Left = 119
        Top = 74
        Width = 88
        Height = 21
        TabOrder = 1
      end
      object Edit3: TEdit
        Left = 119
        Top = 115
        Width = 88
        Height = 21
        TabOrder = 2
      end
    end
    object GroupBox2: TGroupBox
      Left = 288
      Top = 16
      Width = 241
      Height = 169
      Caption = 'Sorting methods'
      TabOrder = 1
      object CheckBox1: TCheckBox
        Left = 24
        Top = 31
        Width = 65
        Height = 17
        Caption = 'Selection'
        TabOrder = 0
      end
      object CheckBox2: TCheckBox
        Left = 24
        Top = 63
        Width = 49
        Height = 17
        Caption = 'Insert'
        TabOrder = 1
      end
      object CheckBox3: TCheckBox
        Left = 24
        Top = 95
        Width = 49
        Height = 17
        Caption = 'Bubble'
        TabOrder = 2
      end
      object CheckBox4: TCheckBox
        Left = 95
        Top = 31
        Width = 66
        Height = 17
        Caption = 'Merge(R)'
        TabOrder = 3
      end
      object CheckBox5: TCheckBox
        Left = 95
        Top = 63
        Width = 66
        Height = 17
        Caption = 'Merge'
        TabOrder = 4
      end
      object CheckBox6: TCheckBox
        Left = 95
        Top = 95
        Width = 58
        Height = 17
        Caption = 'Quick(R)'
        TabOrder = 5
      end
      object CheckBox7: TCheckBox
        Left = 167
        Top = 31
        Width = 97
        Height = 17
        Caption = 'Quick'
        TabOrder = 6
      end
      object CheckBox8: TCheckBox
        Left = 167
        Top = 63
        Width = 71
        Height = 17
        Caption = 'Radix'
        TabOrder = 7
      end
      object CheckBox9: TCheckBox
        Left = 167
        Top = 95
        Width = 42
        Height = 17
        Caption = 'Heap'
        TabOrder = 8
      end
      object Button2: TButton
        Left = 32
        Top = 128
        Width = 176
        Height = 25
        Caption = 'Start sorting'
        TabOrder = 9
        OnClick = Button2Click
      end
    end
    object Memo2: TMemo
      Left = 560
      Top = 16
      Width = 241
      Height = 169
      Lines.Strings = (
        'Checking')
      TabOrder = 2
    end
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 210
    Width = 818
    Height = 455
    ActivePage = TabSheet1
    Align = alClient
    TabOrder = 1
    object TabSheet1: TTabSheet
      Caption = 'Data'
      object Memo1: TMemo
        Left = 0
        Top = 0
        Width = 810
        Height = 427
        Align = alClient
        Lines.Strings = (
          'Generated Array:')
        TabOrder = 0
      end
    end
  end
end
