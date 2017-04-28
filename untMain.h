//---------------------------------------------------------------------------

#ifndef untMainH
#define untMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include "CSPIN.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmMain:public TForm
{
__published:    // IDE-managed Components
    TGroupBox*              grpConnection;
    TButton*                btnConnect;
    TEdit*                  edtServer;
    TLabel*                 lblServer;
    TLabel*                 lblDatabase;
    TLabel*                 lblUsername;
    TEdit*                  edtDatabase;
    TEdit*                  edtUsername;
    TGroupBox*              grpStatus;
    TMemo*                  mmoStatus;
    TGroupBox*              grpContent;
    TMemo*                  mmoBody;
    TGroupBox*              grpManager;
    TListBox*               lbxItems;
    TBitBtn*                btnRefresh;
    TBitBtn*                btnDelete;
    TBitBtn*                btnEdit;
    TCheckBox*              chkReplace;
    TCSpinEdit*             spnReplace;
    TLabel*                 lblPassword;
    TEdit*                  edtPassword;
    TCheckBox*              chkSavePassword;
    TBitBtn*                btnNew;
    TBitBtn*                btnSubmit;
    TPanel*                 Panel1;
    TLabel*                 lblTitle;
    TEdit*                  edtTitle;
    TEdit*                  edtDescription;
    TLabel*                 lblDescription;
    TLabel*                 lblKeywords;
    TEdit*                  edtKeywords;
    TEdit*                  edtDateTime;
    TLabel*                 lblDateTime;
    TCheckBox*              chkOldestFirst;
    TButton*                btnUpdate;
    void __fastcall         btnConnectClick(TObject* Sender);
    void __fastcall         FormCreate(TObject* Sender);
    void __fastcall         FormClose(TObject* Sender, TCloseAction& Action);
    void __fastcall         Button2Click(TObject* Sender);
    void __fastcall         btnRefreshClick(TObject* Sender);
    void __fastcall         btnDeleteClick(TObject* Sender);
    void __fastcall         btnEditClick(TObject* Sender);
    void __fastcall         btnNewClick(TObject* Sender);
    void __fastcall         chkReplaceClick(TObject* Sender);
    void __fastcall         lbxItemsDblClick(TObject* Sender);
    void __fastcall         FormShow(TObject* Sender);
    void __fastcall         edtTitleChange(TObject* Sender);
    void __fastcall         mmoBodyChange(TObject* Sender);
    void __fastcall         edtDateTimeDblClick(TObject* Sender);
    void __fastcall         edtDateTimeChange(TObject* Sender);
    void __fastcall         edtKeywordsChange(TObject* Sender);
    void __fastcall         edtDescriptionChange(TObject* Sender);
    void __fastcall         chkOldestFirstClick(TObject* Sender);
    void __fastcall         btnUpdateClick(TObject* Sender);
    void __fastcall         mmoBodyKeyDown(TObject* Sender, WORD& Key, TShiftState Shift);
private:    // User declarations
    bool                    ChangesUnsaved;
    void                    RenderStatus();
    void                    LoadSettings();
    void                    SaveSettings();
    AnsiString              EscapeString(AnsiString s);
    AnsiString              UnEscapeString(AnsiString s);
    int                     GetCurrentID();
    void                    SetStatus(AnsiString st);
    void                    UpdateDateTime();
    void                    OnConnect();
    void                    OnDisconnect();
    void                    SetUIState(bool fConnected);
public:     // User declarations
    __fastcall              TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain*frmMain;
//---------------------------------------------------------------------------
#endif
