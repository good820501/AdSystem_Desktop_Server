object Form16: TForm16
  Left = 483
  Top = 217
  BorderStyle = bsDialog
  Caption = #20998#32452#23646#24615#39029
  ClientHeight = 209
  ClientWidth = 401
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 16
    Width = 65
    Height = 13
    AutoSize = False
    Caption = #20998#32452#21517#31216
  end
  object Edit1: TEdit
    Left = 88
    Top = 8
    Width = 121
    Height = 21
    TabOrder = 0
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 40
    Width = 377
    Height = 121
    Caption = #22791#27880
    TabOrder = 1
    object Memo1: TMemo
      Left = 8
      Top = 16
      Width = 361
      Height = 97
      Lines.Strings = (
        '')
      TabOrder = 0
    end
  end
  object Button1: TButton
    Left = 48
    Top = 176
    Width = 75
    Height = 25
    Caption = #30830'    '#23450'(&O)'
    TabOrder = 2
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 240
    Top = 176
    Width = 75
    Height = 25
    Caption = #21462'    '#28040'(&C)'
    TabOrder = 3
    OnClick = Button2Click
  end
end
