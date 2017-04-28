#ifndef _CIniFile_h_
#define _CIniFile_h_

//note: this BCB define is not a default C++ Builder 6 define, it needs to be added when compiling under BCB6
#ifndef BCB  //if not compiling under C++ Builder
#include <string>  //string class from standard library
#define STRING_CLASS std::string  //use the standard  library's string class for the interface string
#else
#include <vcl.h>  //borland visual component libray
#define STRING_CLASS AnsiString  //use the VCL ansistring class as the string class
#endif

#include <stdio.h>

#include <list>
using namespace std;

struct  SIniFile_Group;
struct  SIniFile_Item;

//=======================================================================================================
/*
    An item in an ini file (a value)
*/
struct SIniFile_Item
{
    SIniFile_Group* Group;  //pointer to group item belongs in
    STRING_CLASS    Name;  //name of the item
    STRING_CLASS    Value;  //value of the item
};
//=======================================================================================================


//=======================================================================================================
/*
    A group in an ini file
*/
struct SIniFile_Group
{
    STRING_CLASS            Name;  //name of the group
    list<SIniFile_Item*>    Items;  //list of items in that group
};
//=======================================================================================================


//=======================================================================================================
/*
    Ini file loading / saving return values
*/
const int               INI_SUCCESS     = 0;  //successful read/write performed
const int               INI_ERROR_LOAD  = 1;  //couldn't load; file not found
const int               INI_ERROR_SAVE  = 2;  //couldn't save; file not writable for some reason
//=======================================================================================================


//=======================================================================================================
class CIniFile
{
public:
                            CIniFile();  //constructor
                            ~CIniFile();  //destructor

    int                     LoadFile(STRING_CLASS Filename);  //load and parse an ini file
    int                     SaveFile(STRING_CLASS Filename);  //save the ini file to Filename

    STRING_CLASS            GetItem(STRING_CLASS GroupName, STRING_CLASS Name);  //get the value of an item from a certain group
    bool                    GetGroupItems(STRING_CLASS GroupName, list<STRING_CLASS>* Names);  //get a list of items in a certain group
    bool                    GroupExists(STRING_CLASS GroupName);  //determine if a group exists

    bool                    AddItem(STRING_CLASS GroupName, STRING_CLASS Name, STRING_CLASS Value);  //add/change an item to a certain group
    bool                    RemoveItem(STRING_CLASS GroupName, STRING_CLASS Name);  //remove an item from a certain group
    void                    AddGroup(STRING_CLASS GroupName);  //add a new group
    void                    RemoveGroup(STRING_CLASS GroupName);  //remove a group


private:
    list<STRING_CLASS>      Lines;  //all lines read from the file
    int                     ReadLines(STRING_CLASS Filename);  //read in all the lines from the file
    void                    ParseLines();  //parse the loaded lines, look for items

    list<SIniFile_Group*>   Groups;  //all groups in the file

    SIniFile_Group*         GetGroup(STRING_CLASS GroupName);  //gets a group pointer from a group name
    SIniFile_Item*          GetItem(SIniFile_Group* Group, STRING_CLASS Name);  //get the value of an item from a certain group
};
//=======================================================================================================

#endif
