object frmEffect: TfrmEffect
  Left = 389
  Top = 280
  Width = 635
  Height = 488
  Caption = 'Edit Effect'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCloseQuery = FormCloseQuery
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object grpEffect: TGroupBox
    Left = 3
    Top = 0
    Width = 621
    Height = 425
    Anchors = [akLeft, akTop, akRight, akBottom]
    Caption = 'Effect'
    TabOrder = 0
    object mmoEffect: TMemo
      Left = 7
      Top = 14
      Width = 607
      Height = 402
      Anchors = [akLeft, akTop, akRight, akBottom]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Courier New'
      Font.Style = []
      ParentFont = False
      ScrollBars = ssBoth
      TabOrder = 0
      WordWrap = False
      OnChange = mmoEffectChange
    end
  end
  object btnOk: TButton
    Left = 462
    Top = 432
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = 'OK'
    ModalResult = 1
    TabOrder = 1
  end
  object btnCancel: TButton
    Left = 548
    Top = 432
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 2
  end
end
