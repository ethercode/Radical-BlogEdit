object frmMain: TfrmMain
  Left = 296
  Top = 133
  Width = 732
  Height = 532
  Caption = 'Radical BlogEdit 1.7'
  Color = clBtnFace
  Constraints.MinHeight = 400
  Constraints.MinWidth = 550
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnShow = FormShow
  DesignSize = (
    724
    498)
  PixelsPerInch = 96
  TextHeight = 13
  object grpConnection: TGroupBox
    Left = 513
    Top = 2
    Width = 206
    Height = 151
    Anchors = [akTop, akRight]
    Caption = 'Connection settings'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Verdana'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    object lblServer: TLabel
      Left = 6
      Top = 25
      Width = 65
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = 'Server:'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
    end
    object lblDatabase: TLabel
      Left = 6
      Top = 49
      Width = 65
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = 'Database:'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
    end
    object lblUsername: TLabel
      Left = 6
      Top = 73
      Width = 65
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = 'Username:'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
    end
    object lblPassword: TLabel
      Left = 6
      Top = 97
      Width = 65
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = 'Password:'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
    end
    object btnConnect: TButton
      Left = 8
      Top = 121
      Width = 77
      Height = 23
      Caption = 'Connect'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      OnClick = btnConnectClick
    end
    object edtServer: TEdit
      Left = 76
      Top = 22
      Width = 121
      Height = 20
      AutoSize = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
    end
    object edtDatabase: TEdit
      Left = 76
      Top = 46
      Width = 121
      Height = 20
      AutoSize = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
    end
    object edtUsername: TEdit
      Left = 76
      Top = 70
      Width = 121
      Height = 20
      AutoSize = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
    end
    object edtPassword: TEdit
      Left = 76
      Top = 94
      Width = 121
      Height = 20
      AutoSize = False
      Color = 14079487
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
      PasswordChar = '*'
      TabOrder = 3
    end
    object chkSavePassword: TCheckBox
      Left = 91
      Top = 124
      Width = 105
      Height = 17
      Alignment = taLeftJustify
      Caption = 'Save password'
      Enabled = False
      TabOrder = 5
    end
  end
  object grpStatus: TGroupBox
    Left = 4
    Top = 459
    Width = 715
    Height = 41
    Anchors = [akLeft, akRight, akBottom]
    Caption = 'Status:'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Verdana'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    TabStop = True
    DesignSize = (
      715
      41)
    object mmoStatus: TMemo
      Left = 8
      Top = 16
      Width = 700
      Height = 17
      TabStop = False
      Anchors = [akLeft, akTop, akRight]
      BevelEdges = []
      BevelInner = bvNone
      BevelOuter = bvNone
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      Lines.Strings = (
        'Ready.')
      ParentFont = False
      ReadOnly = True
      TabOrder = 0
    end
  end
  object grpContent: TGroupBox
    Left = 4
    Top = 2
    Width = 503
    Height = 454
    Anchors = [akLeft, akTop, akRight, akBottom]
    Caption = 'Content'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Verdana'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    DesignSize = (
      503
      454)
    object mmoBody: TMemo
      Left = 9
      Top = 16
      Width = 483
      Height = 279
      Anchors = [akLeft, akTop, akRight, akBottom]
      Color = 8404992
      Font.Charset = ANSI_CHARSET
      Font.Color = clWhite
      Font.Height = -11
      Font.Name = 'Lucida Console'
      Font.Style = []
      ParentFont = False
      ScrollBars = ssVertical
      TabOrder = 0
      OnChange = mmoBodyChange
      OnKeyDown = mmoBodyKeyDown
    end
    object chkReplace: TCheckBox
      Left = 7
      Top = 425
      Width = 84
      Height = 17
      Alignment = taLeftJustify
      Anchors = [akLeft, akBottom]
      Caption = 'Replace ID'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = chkReplaceClick
    end
    object spnReplace: TCSpinEdit
      Left = 100
      Top = 423
      Width = 53
      Height = 22
      Anchors = [akLeft, akBottom]
      Enabled = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
    end
    object btnNew: TBitBtn
      Left = 341
      Top = 421
      Width = 69
      Height = 25
      Anchors = [akRight, akBottom]
      Caption = 'New'
      TabOrder = 3
      OnClick = btnNewClick
      Kind = bkNo
    end
    object btnSubmit: TBitBtn
      Left = 418
      Top = 421
      Width = 75
      Height = 25
      Anchors = [akRight, akBottom]
      Caption = 'Submit'
      ModalResult = 6
      TabOrder = 4
      OnClick = Button2Click
      Glyph.Data = {
        DE010000424DDE01000000000000760000002800000024000000120000000100
        0400000000006801000000000000000000001000000000000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
        3333333333333333333333330000333333333333333333333333F33333333333
        00003333344333333333333333388F3333333333000033334224333333333333
        338338F3333333330000333422224333333333333833338F3333333300003342
        222224333333333383333338F3333333000034222A22224333333338F338F333
        8F33333300003222A3A2224333333338F3838F338F33333300003A2A333A2224
        33333338F83338F338F33333000033A33333A222433333338333338F338F3333
        0000333333333A222433333333333338F338F33300003333333333A222433333
        333333338F338F33000033333333333A222433333333333338F338F300003333
        33333333A222433333333333338F338F00003333333333333A22433333333333
        3338F38F000033333333333333A223333333333333338F830000333333333333
        333A333333333333333338330000333333333333333333333333333333333333
        0000}
      NumGlyphs = 2
    end
    object Panel1: TPanel
      Left = 8
      Top = 304
      Width = 485
      Height = 110
      Anchors = [akLeft, akRight, akBottom]
      BevelInner = bvRaised
      BevelOuter = bvLowered
      TabOrder = 5
      DesignSize = (
        485
        110)
      object lblTitle: TLabel
        Left = 10
        Top = 11
        Width = 69
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'Title:'
      end
      object lblDescription: TLabel
        Left = 10
        Top = 34
        Width = 69
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'Description:'
      end
      object lblKeywords: TLabel
        Left = 10
        Top = 58
        Width = 69
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'Keywords:'
      end
      object lblDateTime: TLabel
        Left = 10
        Top = 82
        Width = 69
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'Date:'
      end
      object edtTitle: TEdit
        Left = 83
        Top = 9
        Width = 393
        Height = 20
        Anchors = [akLeft, akTop, akRight]
        AutoSize = False
        Color = 8404992
        Font.Charset = ANSI_CHARSET
        Font.Color = clWhite
        Font.Height = -11
        Font.Name = 'Verdana'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        OnChange = edtTitleChange
      end
      object edtDescription: TEdit
        Left = 83
        Top = 32
        Width = 393
        Height = 21
        Anchors = [akLeft, akTop, akRight]
        Color = 8404992
        Font.Charset = ANSI_CHARSET
        Font.Color = clWhite
        Font.Height = -11
        Font.Name = 'Verdana'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        OnChange = edtDescriptionChange
      end
      object edtKeywords: TEdit
        Left = 83
        Top = 56
        Width = 393
        Height = 21
        Anchors = [akLeft, akTop, akRight]
        Color = 8404992
        Font.Charset = ANSI_CHARSET
        Font.Color = clWhite
        Font.Height = -11
        Font.Name = 'Verdana'
        Font.Style = []
        ParentFont = False
        TabOrder = 2
        OnChange = edtKeywordsChange
      end
      object edtDateTime: TEdit
        Left = 83
        Top = 80
        Width = 326
        Height = 21
        Anchors = [akLeft, akTop, akRight]
        Color = 8404992
        Font.Charset = ANSI_CHARSET
        Font.Color = clWhite
        Font.Height = -11
        Font.Name = 'Verdana'
        Font.Style = []
        ParentFont = False
        TabOrder = 3
        OnChange = edtDateTimeChange
        OnDblClick = edtDateTimeDblClick
      end
      object btnUpdate: TButton
        Left = 415
        Top = 80
        Width = 60
        Height = 21
        Anchors = [akRight, akBottom]
        Caption = 'Update'
        TabOrder = 4
        OnClick = btnUpdateClick
      end
    end
  end
  object grpManager: TGroupBox
    Left = 514
    Top = 160
    Width = 205
    Height = 296
    Anchors = [akTop, akRight, akBottom]
    Caption = 'News manager'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Verdana'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    DesignSize = (
      205
      296)
    object lbxItems: TListBox
      Left = 8
      Top = 16
      Width = 189
      Height = 209
      Anchors = [akLeft, akTop, akRight, akBottom]
      Color = 13041659
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ItemHeight = 13
      ParentFont = False
      ScrollWidth = 400
      TabOrder = 0
      OnDblClick = lbxItemsDblClick
    end
    object btnRefresh: TBitBtn
      Left = 8
      Top = 264
      Width = 85
      Height = 26
      Anchors = [akRight, akBottom]
      Caption = 'Refresh'
      ModalResult = 4
      TabOrder = 3
      OnClick = btnRefreshClick
      Glyph.Data = {
        DE010000424DDE01000000000000760000002800000024000000120000000100
        0400000000006801000000000000000000001000000000000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333444444
        33333333333F8888883F33330000324334222222443333388F3833333388F333
        000032244222222222433338F8833FFFFF338F3300003222222AAAAA22243338
        F333F88888F338F30000322222A33333A2224338F33F8333338F338F00003222
        223333333A224338F33833333338F38F00003222222333333A444338FFFF8F33
        3338888300003AAAAAAA33333333333888888833333333330000333333333333
        333333333333333333FFFFFF000033333333333344444433FFFF333333888888
        00003A444333333A22222438888F333338F3333800003A2243333333A2222438
        F38F333333833338000033A224333334422224338338FFFFF8833338000033A2
        22444442222224338F3388888333FF380000333A2222222222AA243338FF3333
        33FF88F800003333AA222222AA33A3333388FFFFFF8833830000333333AAAAAA
        3333333333338888883333330000333333333333333333333333333333333333
        0000}
      NumGlyphs = 2
    end
    object btnDelete: TBitBtn
      Left = 112
      Top = 264
      Width = 86
      Height = 26
      Anchors = [akLeft, akBottom]
      Cancel = True
      Caption = 'Delete'
      ModalResult = 2
      TabOrder = 2
      OnClick = btnDeleteClick
      Glyph.Data = {
        DE010000424DDE01000000000000760000002800000024000000120000000100
        0400000000006801000000000000000000001000000000000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
        333333333333333333333333000033338833333333333333333F333333333333
        0000333911833333983333333388F333333F3333000033391118333911833333
        38F38F333F88F33300003339111183911118333338F338F3F8338F3300003333
        911118111118333338F3338F833338F3000033333911111111833333338F3338
        3333F8330000333333911111183333333338F333333F83330000333333311111
        8333333333338F3333383333000033333339111183333333333338F333833333
        00003333339111118333333333333833338F3333000033333911181118333333
        33338333338F333300003333911183911183333333383338F338F33300003333
        9118333911183333338F33838F338F33000033333913333391113333338FF833
        38F338F300003333333333333919333333388333338FFF830000333333333333
        3333333333333333333888330000333333333333333333333333333333333333
        0000}
      NumGlyphs = 2
    end
    object btnEdit: TBitBtn
      Left = 8
      Top = 231
      Width = 57
      Height = 25
      Anchors = [akLeft, akBottom]
      Caption = '< Edit'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = btnEditClick
    end
    object chkOldestFirst: TCheckBox
      Left = 72
      Top = 235
      Width = 123
      Height = 17
      Anchors = [akRight, akBottom]
      Caption = 'Show oldest first'
      TabOrder = 4
      OnClick = chkOldestFirstClick
    end
  end
end
