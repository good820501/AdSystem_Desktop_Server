object Form3: TForm3
  Left = 419
  Top = 171
  BorderStyle = bsDialog
  Caption = #24490#29615#22270#29255#23646#24615
  ClientHeight = 311
  ClientWidth = 587
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
  object Button1: TButton
    Left = 40
    Top = 272
    Width = 75
    Height = 25
    Caption = #30830'    '#23450'(&O)'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 144
    Top = 272
    Width = 75
    Height = 25
    Caption = #21462'    '#28040'(&C)'
    TabOrder = 1
    OnClick = Button2Click
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 561
    Height = 249
    TabOrder = 2
    object Label1: TLabel
      Left = 8
      Top = 24
      Width = 73
      Height = 13
      AutoSize = False
      Caption = #23637#31034#21517#31216
    end
    object Label2: TLabel
      Left = 8
      Top = 56
      Width = 81
      Height = 13
      AutoSize = False
      Caption = #22270#29255#25152#22312#30446#24405
    end
    object Label3: TLabel
      Left = 8
      Top = 224
      Width = 89
      Height = 13
      AutoSize = False
      Caption = #22270#29255#20999#25442#38388#38548
    end
    object Label4: TLabel
      Left = 192
      Top = 224
      Width = 20
      Height = 13
      AutoSize = False
      Caption = #31186
    end
    object Edit1: TEdit
      Left = 96
      Top = 16
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#24494#36719#25340#38899
      TabOrder = 0
    end
    object Edit2: TEdit
      Left = 96
      Top = 48
      Width = 369
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#24494#36719#25340#38899
      ReadOnly = True
      TabOrder = 1
    end
    object BitBtn1: TBitBtn
      Left = 470
      Top = 48
      Width = 75
      Height = 25
      Caption = #27983'    '#35272
      TabOrder = 2
      OnClick = BitBtn1Click
    end
    object GroupBox2: TGroupBox
      Left = 8
      Top = 88
      Width = 545
      Height = 121
      Caption = #22270#29255#29305#25928
      TabOrder = 3
      object RadioButton1: TRadioButton
        Left = 40
        Top = 24
        Width = 65
        Height = 17
        Caption = #26080#29305#25928
        TabOrder = 0
      end
      object RadioButton2: TRadioButton
        Left = 40
        Top = 56
        Width = 105
        Height = 17
        Caption = #31446#30452#30334#21494#31383
        TabOrder = 1
      end
      object RadioButton3: TRadioButton
        Left = 40
        Top = 88
        Width = 89
        Height = 17
        Caption = #27700#24179#30334#21494#31383
        TabOrder = 2
      end
      object RadioButton4: TRadioButton
        Left = 192
        Top = 24
        Width = 121
        Height = 17
        Caption = #21475#23383#21521#22235#21608#21047#26032
        TabOrder = 3
      end
      object RadioButton5: TRadioButton
        Left = 192
        Top = 56
        Width = 121
        Height = 17
        Caption = #20117#23383#21521#22235#21608#21047#26032
        TabOrder = 4
      end
      object RadioButton6: TRadioButton
        Left = 192
        Top = 88
        Width = 153
        Height = 17
        Caption = #20998#21035#20174#24038#21491#36827#20837#23631#24149
        TabOrder = 5
      end
      object RadioButton7: TRadioButton
        Left = 360
        Top = 24
        Width = 137
        Height = 17
        Caption = #20174#20013#38388#21521#24038#21491#21047#26032
        TabOrder = 6
      end
      object RadioButton8: TRadioButton
        Left = 360
        Top = 56
        Width = 137
        Height = 17
        Caption = #20998#23567#31383#21475#21047#26032
        TabOrder = 7
      end
      object RadioButton9: TRadioButton
        Left = 360
        Top = 88
        Width = 137
        Height = 17
        Caption = #20197#19978#29305#25928#38543#26426#36873#25321
        Checked = True
        TabOrder = 8
        TabStop = True
      end
    end
    object Edit3: TEdit
      Left = 96
      Top = 216
      Width = 89
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#24494#36719#25340#38899
      TabOrder = 4
    end
  end
  object OpenDialog1: TOpenDialog
    Filter = 'Flash'#25991#20214'|*.swf'
    Left = 480
    Top = 16
  end
end
