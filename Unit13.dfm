object Form13: TForm13
  Left = 335
  Top = 208
  BorderStyle = bsNone
  Caption = #36828#31243#25511#21046#26381#21153
  ClientHeight = 208
  ClientWidth = 491
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label2: TLabel
    Left = 136
    Top = 88
    Width = 41
    Height = 13
    AutoSize = False
    Caption = 'IP'#22320#22336
  end
  object Label3: TLabel
    Left = 120
    Top = 120
    Width = 48
    Height = 13
    Caption = #25351#20196#21517#31216
  end
  object Label4: TLabel
    Left = 72
    Top = 32
    Width = 357
    Height = 16
    Caption = #27491#22312#25191#34892#36828#31243#25511#21046#25351#20196#65292#35831#31245#21518#12290#12290#12290#12290#12290#12290#12290
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = #23435#20307
    Font.Style = [fsBold]
    ParentFont = False
  end
  object CGauge1: TCGauge
    Left = 40
    Top = 168
    Width = 425
    Height = 25
    ForeColor = clGreen
    Progress = 40
  end
  object Edit2: TEdit
    Left = 200
    Top = 80
    Width = 121
    Height = 21
    ImeName = #20013#25991' ('#31616#20307') - '#24494#36719#25340#38899
    TabOrder = 0
  end
  object Edit3: TEdit
    Left = 200
    Top = 112
    Width = 121
    Height = 21
    ImeName = #20013#25991' ('#31616#20307') - '#24494#36719#25340#38899
    TabOrder = 1
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 48
    Top = 80
  end
end
