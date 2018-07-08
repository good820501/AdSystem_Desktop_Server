object Form4: TForm4
  Left = 714
  Top = 387
  BorderStyle = bsDialog
  Caption = 'web'#39029#38754
  ClientHeight = 165
  ClientWidth = 370
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
  object GroupBox1: TGroupBox
    Left = 8
    Top = 0
    Width = 353
    Height = 121
    TabOrder = 0
    object Label1: TLabel
      Left = 8
      Top = 24
      Width = 57
      Height = 13
      AutoSize = False
      Caption = #23637#31034#21517#31216
    end
    object Label3: TLabel
      Left = 8
      Top = 64
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'URL'#22320#22336
    end
    object Label4: TLabel
      Left = 8
      Top = 96
      Width = 57
      Height = 13
      AutoSize = False
      Caption = #31383#21475#23610#23544
    end
    object Label2: TLabel
      Left = 144
      Top = 88
      Width = 16
      Height = 24
      Caption = 'X'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Edit1: TEdit
      Left = 64
      Top = 16
      Width = 129
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#24494#36719#25340#38899
      TabOrder = 0
    end
    object Edit3: TEdit
      Left = 64
      Top = 56
      Width = 281
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#24494#36719#25340#38899
      TabOrder = 1
    end
    object Edit4: TEdit
      Left = 64
      Top = 88
      Width = 57
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#24494#36719#25340#38899
      TabOrder = 2
    end
    object Edit2: TEdit
      Left = 176
      Top = 88
      Width = 65
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#24494#36719#25340#38899
      TabOrder = 3
    end
  end
  object Button1: TButton
    Left = 24
    Top = 128
    Width = 75
    Height = 25
    Caption = #30830'    '#23450'(&O)'
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 136
    Top = 128
    Width = 75
    Height = 25
    Caption = #21462'    '#28040'(&C)'
    TabOrder = 2
    OnClick = Button2Click
  end
end
