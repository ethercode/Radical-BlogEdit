//---------------------------------------------------------------------------

#include <windows.h>

#include <vcl.h>
#pragma hdrstop
#include "untMain.h"
#include "CMySQL.h"
#include <stdio.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TfrmMain*   frmMain;
CMySQL      MySQL;

struct SSettings
{
    char    szServer[256];
    char    szUsername[256];
    char    szDatabase[256];
    char    szPassword[256];
    bool    fOldestFirst;
};

//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner):
    TForm(Owner)
{
    ChangesUnsaved = false;
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::btnConnectClick(TObject* Sender)
{
    if (edtPassword->Text == "")
    {
        Application->MessageBox("Please enter a password.", "Error - no password", MB_ICONERROR | MB_OK);
        return;
    }
    SaveSettings();
    btnConnect->Enabled = false;
    if (MySQL.IsConnected() == false)
    {
        SetStatus("Attempting to connect...");
        MySQL.Connect(edtServer->Text, edtUsername->Text, edtPassword->Text, edtDatabase->Text);
        if (MySQL.IsConnected())
        {
            btnRefresh->OnClick(this);
        }
    }
    else
    {
        MySQL.Disconnect();
    }
    RenderStatus();
    if (MySQL.IsConnected())
    {
        SetStatus("Connected.");
        ChangesUnsaved = false;
        OnConnect();
    }
    else
    {
        SetStatus("Disconnected.");
        OnDisconnect();
    }
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmMain::RenderStatus()
{
    btnConnect->Enabled = true;
    if (MySQL.IsConnected() == false)
    {
        btnConnect->Caption = "Connect";
        SetStatus("Disconnected.");
        btnNewClick(this);
        lbxItems->Clear();
        edtKeywords->Clear();
        edtDescription->Clear();
        edtDateTime->Clear();
    }
    else
    {
        btnConnect->Caption = "Disconnect";
        SetStatus("Connected.");
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormCreate(TObject* Sender)
{
    LoadSettings();
    RenderStatus();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmMain::LoadSettings()
{
    SSettings   s;
    FILE*       f   = fopen("settings.dat", "rb");
    if (f)
    {
        fread(&s, sizeof(SSettings), 1, f);
        fclose(f);
        edtDatabase->Text = s.szDatabase;
        edtUsername->Text = s.szUsername;
        edtServer->Text = s.szServer;
        edtPassword->Text = s.szPassword;
        chkSavePassword->Checked = (s.szPassword[0] != NULL);
        chkOldestFirst->Checked = s.fOldestFirst;
    }
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmMain::SaveSettings()
{
    SSettings   s;
    FILE*       f   = fopen("settings.dat", "wb");
    if (f)
    {
        strcpy(s.szUsername, edtUsername->Text.c_str());
        strcpy(s.szDatabase, edtDatabase->Text.c_str());
        strcpy(s.szServer, edtServer->Text.c_str());
        if (chkSavePassword->Checked)
        {
            strcpy(s.szPassword, edtPassword->Text.c_str());
        }
        else
        {
            s.szPassword[0] = NULL;
        }
        s.fOldestFirst = chkOldestFirst->Checked;

        fwrite(&s, sizeof(SSettings), 1, f);
        fclose(f);
    }
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


void __fastcall TfrmMain::FormClose(TObject* Sender, TCloseAction& Action)
{
    SaveSettings();
    MySQL.Disconnect();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Button2Click(TObject* Sender)
{
    if (MySQL.IsConnected() == false)
    {
        btnConnect->OnClick(this);
    }

    AnsiString      szDate  = edtDateTime->Text;

    CMySQLResult*   pResult;
    if (!chkReplace->Checked)
    {
        SetStatus("Adding blog entry...");

        AnsiString  SubmitString    = "INSERT INTO `blog` (`id`, `title`, `body`, `description`, `keywords`, `datetime`) VALUES ('" + EscapeString(IntToStr(spnReplace->Value)) + "', '" + EscapeString(edtTitle->Text) + "', '" + EscapeString(mmoBody->Text) + "', '" + EscapeString(edtDescription->Text) + "', '" + EscapeString(edtKeywords->Text) + "', '" + szDate + "');";

        pResult = MySQL.Query(SubmitString);
    }
    else
    {
        SetStatus("Updating blog entry...");

        AnsiString  SubmitString    = "UPDATE `blog` SET `id` = '" + EscapeString(IntToStr(spnReplace->Value)) + "', "
                                                  "`title` = '" + EscapeString(edtTitle->Text) + "', "
                                                  "`body` = '" + EscapeString(mmoBody->Text) + "', "
                                                  "`description` = '" + EscapeString(edtDescription->Text) + "', "
                                                  "`keywords` = '" + EscapeString(edtKeywords->Text) + "', "
                                                  "`datetime` = '" + szDate + "' " + "WHERE `id` = '" + IntToStr(spnReplace->Value) + "' LIMIT 1";

        pResult = MySQL.Query(SubmitString);
    }
    if (pResult)
    {
        SetStatus("Submission succeeded.");
        MySQL.FreeResult(pResult);
        if (MySQL.IsConnected())
        {
            btnRefresh->OnClick(this);
        }
        ChangesUnsaved = false;
        btnNewClick(this);
    }
    else
    {
        SetStatus("Submission failed.");
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnRefreshClick(TObject* Sender)
{
    if (MySQL.IsConnected() == false)
    {
        btnConnect->OnClick(this);
    }

    AnsiString  szSortOrder;
    if (!chkOldestFirst->Checked)
    {
        szSortOrder = "DESC";
    }

    SetStatus("Getting list of entries...");

    CMySQLResult*   pRes    = MySQL.Query("SELECT `id`, `title` from `blog` ORDER BY `id` " + szSortOrder);
    if (pRes)
    {
        if (pRes->GetResult_Fields() == 2)
        {
            lbxItems->Clear();
            int iTotalRows  = pRes->GetResult_Rows();
            for (int i = 0; i < iTotalRows; ++i)
            {
                char    temp[12];
                sprintf(temp, "[%03d]: ", StrToInt(pRes->GetResult_Text(i, 0)));
                lbxItems->Items->Add(temp + UnEscapeString(pRes->GetResult_Text(i, 1)));
            }
        }
        MySQL.FreeResult(pRes);
    }
    SetStatus("Ready.");
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnDeleteClick(TObject* Sender)
{
    if (lbxItems->ItemIndex < 0)
    {
        return;
    }

    if (MySQL.IsConnected() == false)
    {
        btnConnect->OnClick(this);
    }

    AnsiString  szId    = IntToStr(GetCurrentID());

    AnsiString  Query   = "DELETE FROM `blog` WHERE `id` = '" + szId + "' LIMIT 1";
    SetStatus("Deleting entry...");
    MySQL.FreeResult(MySQL.Query(Query));
    btnRefresh->OnClick(this);
    SetStatus("Entry deleted.");

    btnNew->OnClick(this);
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
AnsiString TfrmMain::UnEscapeString(AnsiString s)
{
    return s;
    AnsiString  sRet        = "";
    int         iLen        = s.Length();
    char        EscapeChar  = 0;
    for (int i = 0; i < iLen; ++i)
    {
        char    cCurrent    = s.c_str()[i];
        if (EscapeChar != 0)
        {
            if (EscapeChar == '%')
            {
                sRet += cCurrent;
            }
            EscapeChar = 0;
        }
        else
        {
            if (cCurrent == '%')
            {
                EscapeChar = cCurrent;
            }
            else
            {
                sRet += cCurrent;
            }
        }
    }
    return sRet;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
AnsiString TfrmMain::EscapeString(AnsiString s)
{
    AnsiString  sRet    = "";
    int         iLen    = s.Length();

    char*       pBuf    = new char[iLen*4];
    mysql_escape_string(pBuf, s.c_str(), iLen);
    sRet = pBuf;

    /*for (int i=0;i<iLen;++i)
    {
        if (s.c_str()[i] == '\'')
        {
            sRet += '\'';
        }
        if (s.c_str()[i] == '\\')
        {
            sRet += '\\';
        }
        if (s.c_str()[i] == '%')
        {
        }
        sRet += s.c_str()[i];
    }*/
    return sRet;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnEditClick(TObject* Sender)
{
    int iCur    = GetCurrentID();
    if (iCur < 0)
    {
        return;
    }

    SetStatus("Getting entry...");
    CMySQLResult*   pRes        = MySQL.Query("SELECT `title`, `body`, `keywords`, `description`, `datetime` FROM `blog` WHERE `id` = '" + IntToStr(iCur) + "'");
    bool            fSuccess    = false;
    if (pRes)
    {
        if (pRes->GetResult_Rows() == 1 && pRes->GetResult_Fields() == 5)
        {
            edtTitle->Text = UnEscapeString(pRes->GetResult_Text(0, 0));
            mmoBody->Text = UnEscapeString(pRes->GetResult_Text(0, 1));
            edtKeywords->Text = UnEscapeString(pRes->GetResult_Text(0, 2));
            edtDescription->Text = UnEscapeString(pRes->GetResult_Text(0, 3));
            edtDateTime->Text = UnEscapeString(pRes->GetResult_Text(0, 4));
            fSuccess = true;
        }
        MySQL.FreeResult(pRes);
    }
    if (fSuccess)
    {
        SetStatus("Got blog entry.");
        ChangesUnsaved = false;
    }
    else
    {
        SetStatus("Couldn't get blog entry.");
    }


    chkReplace->Checked = true;
    spnReplace->Value = iCur;
    spnReplace->Enabled = true;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
int TfrmMain::GetCurrentID()
{
    if (lbxItems->ItemIndex < 0)
    {
        return -1;
    }
    AnsiString  szId    = lbxItems->Items->Strings[lbxItems->ItemIndex];
    szId = szId.SubString(2, 3);
    if (szId.c_str()[0] == '0')
    {
        szId = szId.SubString(2, 2);
    }
    if (szId.c_str()[0] == '0')
    {
        szId = szId.SubString(2, 1);
    }
    int i   = 0;
    TryStrToInt(szId, i);
    return i;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnNewClick(TObject* Sender)
{
    if (ChangesUnsaved)
    {
        if (Application->MessageBox("Would you like to submit your unsaved changes?", "Unsaved Changes", MB_YESNO | MB_ICONQUESTION) == IDYES)
        {
            btnSubmit->OnClick(this);
        }
    }

    mmoBody->Clear();
    edtTitle->Clear();
    edtDateTime->Clear();
    edtDescription->Clear();
    edtKeywords->Clear();
    chkReplace->Checked = false;
    spnReplace->Value = 0;
    spnReplace->Enabled = false;
    ChangesUnsaved = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::chkReplaceClick(TObject* Sender)
{
    spnReplace->Enabled = chkReplace->Checked;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmMain::SetStatus(AnsiString St)
{
    mmoStatus->Text = St;
    Application->ProcessMessages();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::lbxItemsDblClick(TObject* Sender)
{
    if (ChangesUnsaved)
    {
        if (Application->MessageBox("Would you like to submit your unsaved changes?", "Unsaved Changes", MB_YESNO | MB_ICONQUESTION) == IDYES)
        {
            btnSubmit->OnClick(this);
        }
    }
    btnEditClick(this);
}
//---------------------------------------------------------------------------





void __fastcall TfrmMain::FormShow(TObject* Sender)
{
    edtServer->SetFocus();
    ChangesUnsaved = false;
    OnDisconnect();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::edtTitleChange(TObject* Sender)
{
    btnSubmit->Enabled = (edtTitle->Text != "" && mmoBody->Text != "");
    ChangesUnsaved = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mmoBodyChange(TObject* Sender)
{
    btnSubmit->Enabled = (edtTitle->Text != "" && mmoBody->Text != "");
    ChangesUnsaved = true;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmMain::UpdateDateTime()
{
    AnsiString  szDate;
    TDateTime   cDate   = Date();  // store the current date and time
    TDateTime   cTime   = Time();  // store the current date and time
    szDate = cDate.FormatString("dd mmm yyyy") + ", " + cTime.FormatString("hh:nn") + cTime.FormatString("am/pm");
    edtDateTime->Text = szDate;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::edtDateTimeDblClick(TObject* Sender)
{
    UpdateDateTime();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::edtDateTimeChange(TObject* Sender)
{
    ChangesUnsaved = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::edtKeywordsChange(TObject* Sender)
{
    ChangesUnsaved = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::edtDescriptionChange(TObject* Sender)
{
    ChangesUnsaved = true;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmMain::OnConnect()
{
    SetUIState(true);
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmMain::OnDisconnect()
{
    SetUIState(false);
}
//---------------------------------------------------------------------------

void TfrmMain::SetUIState(bool fConnected)
{
    //connected section
    btnDelete->Enabled = fConnected;
    btnEdit->Enabled = fConnected;
    mmoBody->Enabled = fConnected;
    edtTitle->Enabled = fConnected;
    edtKeywords->Enabled = fConnected;
    edtDateTime->Enabled = fConnected;
    edtDescription->Enabled = fConnected;
    lblTitle->Enabled = fConnected;
    lblKeywords->Enabled = fConnected;
    lblDateTime->Enabled = fConnected;
    lblDescription->Enabled = fConnected;
    chkReplace->Enabled = fConnected;
    chkOldestFirst->Enabled = fConnected;
    btnNew->Enabled = fConnected;
    btnUpdate->Enabled = fConnected;
    btnRefresh->Enabled = fConnected;
    grpContent->Enabled = fConnected;
    grpManager->Enabled = fConnected;

    //disconnected section
    edtServer->Enabled = !fConnected;
    edtDatabase->Enabled = !fConnected;
    edtUsername->Enabled = !fConnected;
    edtPassword->Enabled = !fConnected;
    lblServer->Enabled = !fConnected;
    lblDatabase->Enabled = !fConnected;
    lblUsername->Enabled = !fConnected;
    lblPassword->Enabled = !fConnected;
    chkSavePassword->Enabled = !fConnected;

    spnReplace->Enabled = false;
}


//---------------------------------------------------------------------------


void __fastcall TfrmMain::chkOldestFirstClick(TObject* Sender)
{
    if (MySQL.IsConnected())
    {
        btnRefreshClick(this);
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnUpdateClick(TObject* Sender)
{
    UpdateDateTime();
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::mmoBodyKeyDown(TObject* Sender, WORD& Key, TShiftState Shift)
{
    if (((Key == 'a') || (Key == 'A')) && (Shift.Contains(ssCtrl)))
    {
        mmoBody->SelectAll();
    }
}
//---------------------------------------------------------------------------

