object Form5: TForm5
  Left = 300
  Top = 164
  BorderStyle = bsDialog
  Caption = 'Flash'#23637#31034#23646#24615
  ClientHeight = 383
  ClientWidth = 509
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
    Top = 24
    Width = 57
    Height = 13
    AutoSize = False
    Caption = #23637#31034#21517#31216
  end
  object Edit1: TEdit
    Left = 64
    Top = 16
    Width = 121
    Height = 21
    ImeName = #20013#25991' ('#31616#20307') - '#24494#36719#25340#38899
    TabOrder = 0
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 56
    Width = 369
    Height = 281
    Caption = #23186#20307#21015#34920
    TabOrder = 1
    object ListBox1: TListBox
      Left = 16
      Top = 16
      Width = 337
      Height = 225
      ImeName = #20013#25991' ('#31616#20307') - '#24494#36719#25340#38899
      ItemHeight = 13
      TabOrder = 0
    end
    object Button1: TButton
      Left = 16
      Top = 248
      Width = 75
      Height = 25
      Caption = #28155'    '#21152'(&A)'
      TabOrder = 1
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 118
      Top = 248
      Width = 75
      Height = 25
      Caption = #21024'    '#38500'(&D)'
      TabOrder = 2
      OnClick = Button2Click
    end
    object Button5: TButton
      Left = 216
      Top = 248
      Width = 75
      Height = 25
      Caption = #28165'    '#31354'(&C)'
      TabOrder = 3
      OnClick = Button5Click
    end
  end
  object Button3: TButton
    Left = 24
    Top = 345
    Width = 75
    Height = 25
    Caption = #30830'    '#23450'(&O)'
    TabOrder = 2
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 128
    Top = 345
    Width = 75
    Height = 25
    Caption = #21462'    '#28040'(&C)'
    TabOrder = 3
    OnClick = Button4Click
  end
  object GroupBox2: TGroupBox
    Left = 384
    Top = 56
    Width = 113
    Height = 281
    Caption = #25773#25918#35774#32622
    TabOrder = 4
    object GroupBox3: TGroupBox
      Left = 8
      Top = 24
      Width = 97
      Height = 65
      Caption = #25773#25918#26041#24335
      TabOrder = 0
      object RadioButton1: TRadioButton
        Left = 16
        Top = 16
        Width = 73
        Height = 17
        Caption = #19979#36733#25773#25918
        Checked = True
        TabOrder = 0
        TabStop = True
      end
      object RadioButton2: TRadioButton
        Left = 16
        Top = 40
        Width = 73
        Height = 17
        Caption = #22312#32447#25773#25918
        TabOrder = 1
        Visible = False
      end
    end
    object GroupBox4: TGroupBox
      Left = 8
      Top = 96
      Width = 97
      Height = 73
      TabOrder = 1
      object RadioButton3: TRadioButton
        Left = 16
        Top = 16
        Width = 73
        Height = 17
        Caption = #24490#29615#25773#25918
        Checked = True
        TabOrder = 0
        TabStop = True
      end
      object RadioButton4: TRadioButton
        Left = 16
        Top = 40
        Width = 73
        Height = 17
        Caption = #21482#25773#19968#27425
        TabOrder = 1
      end
    end
    object GroupBox5: TGroupBox
      Left = 8
      Top = 176
      Width = 97
      Height = 89
      TabOrder = 2
      object RadioButton5: TRadioButton
        Left = 16
        Top = 16
        Width = 73
        Height = 17
        Caption = #20840#23631#25773#25918
        Checked = True
        TabOrder = 0
        TabStop = True
      end
      object RadioButton6: TRadioButton
        Left = 16
        Top = 40
        Width = 73
        Height = 17
        Caption = #19968#20493#31383#21475
        TabOrder = 1
      end
      object RadioButton7: TRadioButton
        Left = 16
        Top = 64
        Width = 73
        Height = 17
        Caption = #20108#20493#31383#21475
        TabOrder = 2
      end
    end
  end
  object OpenDialog1: TOpenDialog
    Filter = 'Flash'#25991#20214'|*.swf'
    Options = [ofHideReadOnly, ofAllowMultiSelect, ofEnableSizing]
    Left = 240
    Top = 8
  end
end
