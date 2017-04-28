#include "CIniFile.h"

//=======================================================================================================
CIniFile::CIniFile()
{
}
//=======================================================================================================


//=======================================================================================================
CIniFile::~CIniFile()
{
    while (Groups.size() > 0)
    {
        SIniFile_Group* pGroup  = Groups.front();
        RemoveGroup(pGroup->Name);
    }
}
//=======================================================================================================


//=======================================================================================================
int CIniFile::LoadFile(STRING_CLASS Filename)
{
    /*
        Loads and parses an ini file.
    */
    int Code    = ReadLines(Filename);
    if (Code != INI_SUCCESS)
    {
        return Code;  //for now, return the error code
    }
    ParseLines();  //parse the loaded lines and get the information
    Lines.clear();  //empty the lines (we dont need it anymore)
    return INI_SUCCESS;  //return success code
}
//=======================================================================================================


//=======================================================================================================
int CIniFile::SaveFile(STRING_CLASS Filename)
{
    /*
        Saves the ini file to Filename.
    */
    FILE*   File    = fopen(Filename.c_str(), "wb");  //attempt to open destination file for saving
    if (!File)  //if couldnt open file
    {
        return INI_ERROR_SAVE;  //return error
    }

    list<SIniFile_Group*>::iterator GroupIterator   = Groups.begin();  //group list iterator initialisation
    int                             TotalGroups     = Groups.size();  //total amount of groups
    int                             CurrentGroupNum;  //current group counter
    for (CurrentGroupNum = 0; CurrentGroupNum < TotalGroups; ++CurrentGroupNum)
    {
        SIniFile_Group* CurrentGroup    = *GroupIterator;  //set up group iterator
        ++GroupIterator;  //advance the group iterator

        fprintf(File, "[%s]\r\n", CurrentGroup->Name.c_str());  //write group name
        list<SIniFile_Item*>::iterator  ItemIterator    = CurrentGroup->Items.begin();  //item interator initialisation
        int                             TotalItems      = CurrentGroup->Items.size();  //get total amount of items in this group
        int                             CurrentItemNum;  //current item number
        for (CurrentItemNum = 0; CurrentItemNum < TotalItems; ++CurrentItemNum)
        {
            SIniFile_Item*  CurrentItem = *ItemIterator;  //get current item
            ++ItemIterator;  //advance the item iterator
            fprintf(File, "%s=%s\r\n", CurrentItem->Name.c_str(), CurrentItem->Value.c_str());  //write item data
        }
        if (CurrentGroupNum != TotalGroups - 1)  //if the last group wasnt just written
        {
            fprintf(File, "\r\n");  //write a blank line
        }
    }

    fclose(File);  //close the file
    return INI_SUCCESS;  //return success
}
//=======================================================================================================


//=======================================================================================================
STRING_CLASS CIniFile::GetItem(STRING_CLASS GroupName, STRING_CLASS Name)
{
    /*
        Gets the value of an item from a certain group
    */
    SIniFile_Group* Group   = GetGroup(GroupName);  //get the appropriate group structure
    if (Group == NULL)  //if group doesnt exist
    {
        return "";  //return a null STRING_CLASS
    }
    SIniFile_Item*  Item    = GetItem(Group, Name);  //get item
    if (Item == NULL)  //if item doesnt exist in the group
    {
        return "";  //return a null STRING_CLASS
    }
    return Item->Value;  //return the value
} 
//=======================================================================================================


//=======================================================================================================
bool CIniFile::GetGroupItems(STRING_CLASS GroupName, list<STRING_CLASS>* Names)
{
    /*
        Gets a list of items in a certain group 
    */
    SIniFile_Group* Group   = GetGroup(GroupName);  //get the appropriate group structure
    if (Group == NULL)  //if group doesnt exist
    {
        Names->clear();  //clear the contents of the list
        return false;  //group was invalid, return false
    }
    list<SIniFile_Item*>::iterator  ItemIterator    = Group->Items.begin();  //item interator initialisation
    int                             TotalItems      = Group->Items.size();  //get total amount of items in this group
    int                             CurrentItemNum;  //current item number
    for (CurrentItemNum = 0; CurrentItemNum < TotalItems; ++CurrentItemNum)
    {
        SIniFile_Item*  CurrentItem = *ItemIterator;  //get current item
        ++ItemIterator;  //advance the item iterator
        Names->push_back(CurrentItem->Name);  //add the item name to the list
    }
    return true;  //group was valid, return true
}
//=======================================================================================================


//=======================================================================================================
bool CIniFile::AddItem(STRING_CLASS GroupName, STRING_CLASS Name, STRING_CLASS Value)
{
    /*
        Adds or changes an item in a certain group
    */
    SIniFile_Group* Group   = GetGroup(GroupName);  //get the appropriate group structure
    if (Group == NULL)  //if group doesnt exist
    {
        return false;  //group didnt exist; return error
    }
    SIniFile_Item*  Item    = GetItem(Group, Name);  //get item
    if (Item == NULL)  //if item doesnt exist in the group
    {
        Item = new SIniFile_Item;  //create a new item
        Item->Name = Name;  //set the name
        Item->Value = Value;  //set the value
        Group->Items.push_back(Item);  //add the item to the list
    }
    else  //if item already exists
    {
        Item->Value = Value;  //just change the value
    }
    return true;  //success
}
//=======================================================================================================


//=======================================================================================================
bool CIniFile::RemoveItem(STRING_CLASS GroupName, STRING_CLASS Name)
{
    /*
        Removes an item from a certain group
    */
    SIniFile_Group* Group   = GetGroup(GroupName);  //get the appropriate group structure
    if (Group == NULL)  //if group doesnt exist
    {
        return false;  //group didnt exist; return error
    }
    SIniFile_Item*  Item    = GetItem(Group, Name);  //get item
    if (Item == NULL)  //if item doesnt exist in the group
    {
        return true;  //the item didnt need to be removed; return success
    }
    else  //if item exists
    {
        Group->Items.remove(Item);  //remove the item from the linked list
        delete Item;  //free the memory allocated by the item
    }
    return true;  //success
}
//=======================================================================================================


//=======================================================================================================
void CIniFile::ParseLines()
{
    /*
        Parses lines. Any items not in a group will be ignored! (those before a group tag)
    */
    SIniFile_Group*                 CurrentGroup    = NULL;  //current group; not in a group yet
    list<STRING_CLASS>::iterator    Iterator        = Lines.begin();  //start off the line iterator
    int                             TotalLines      = Lines.size();  //get total amount of lines in the ini file
    int                             LineNumber;  //line number (loop variable)
    for (LineNumber = 0; LineNumber < TotalLines; ++LineNumber)  //go through all the lines
    {
        STRING_CLASS    Line    = *Iterator;   //get the current line from the list
        ++Iterator;  //move iterator on to next line
        if (Line.c_str()[0] == 0)
        {
            continue;
        }  //if the line is blank, skip this line

        if (Line.c_str()[0] == '[')  //if first character is a left square bracket
        {
            //this line represents a group name, so take this into account
            STRING_CLASS    GroupName   = Line.substr(1, Line.length() - 2);  //get the groupname
            CurrentGroup = new SIniFile_Group;  //create a new group
            CurrentGroup->Name = GroupName;  //set group name
            if (CurrentGroup != NULL)  //if this isn't the first one
            {
                Groups.push_back(CurrentGroup);  //add the current group to the list
            }
        }
        else  //if not a group tag
        {
            if (CurrentGroup == NULL)
            {
                continue;
            }  //if there is no group, ignore this line
            STRING_CLASS    Name;  //name that will be found before '=' sign
            STRING_CLASS    Value;  //and the value that will be found after it
            Split(Line, '=', &Name, &Value);  //split the line between the '=' sign

            SIniFile_Item*  Item    = new SIniFile_Item;  //create a new item
            Item->Group = CurrentGroup;  //set the group
            Item->Name = Name;  //set the name
            Item->Value = Value;  //set the value
            CurrentGroup->Items.push_back(Item);  //add the item to the list
        }
    }
}
//=======================================================================================================


//=======================================================================================================
int CIniFile::ReadLines(STRING_CLASS Filename)
{
    /*
        Reads in lines from Filename.
    */
    FILE*   File    = fopen(Filename.c_str(), "rb");  //try to load settings file
    if (File == 0)  //if there was no settings file
    {
        return INI_ERROR_LOAD;  //return error state (cannot open file)
    }
    char            Character;  //char read in from file
    bool            GotCR   = false;  //flag to indicate if we got carriage return
    STRING_CLASS    Line;  //STRING_CLASS to store line text
    while (!feof(File))  //read until end of file
    {
        fread(&Character, 1, 1, File);  //read in a character
        if (Character == 10 || Character == 13)  //if a carriage return is detected
        {
            if (!GotCR)  //if we we havent got the carriage return yet
            {
                Lines.push_back(Line);  //add the newly-read line to the list of lines
                Line = "";  //clear the line
                GotCR = true;  //we now have the carriage return
            }
        }
        else  //the character wasnt a carriage-return character
        {
            GotCR = false;  //set the got carriage return flag to false
            Line += Character;  //add the character to the line
        }
    }
    if (Line != "")  //if there are leftovers (text before a carriage return)
    {
        Lines.push_back(Line);  //add this line to the list of lines
    }
    fclose(File);  //close the settings file.
    return INI_SUCCESS;  //return success code
}
//=======================================================================================================


//=======================================================================================================
SIniFile_Group* CIniFile::GetGroup(STRING_CLASS GroupName)
{
    /*
         Gets a group pointer by name
    */
    list<SIniFile_Group*>::iterator GroupIterator   = Groups.begin();  //group list iterator initialisation
    int                             TotalGroups     = Groups.size();  //total amount of groups
    int                             CurrentGroupNum;  //current group counter
    for (CurrentGroupNum = 0; CurrentGroupNum < TotalGroups; ++CurrentGroupNum)
    {
        SIniFile_Group* CurrentGroup    = *GroupIterator;  //set up group iterator
        ++GroupIterator;  //advance the group iterator
        if (CurrentGroup->Name == GroupName)  //if found appropriate group
        {
            return CurrentGroup;  //return pointer to the group
        }
    }
    return NULL;  //group not found, return null
}
//=======================================================================================================


//=======================================================================================================
SIniFile_Item* CIniFile::GetItem(SIniFile_Group* Group, STRING_CLASS Name)
{
    /*
        Gets the value of an item from a certain group
    */
    list<SIniFile_Item*>::iterator  ItemIterator    = Group->Items.begin();  //item interator initialisation
    int                             TotalItems      = Group->Items.size();  //get total amount of items in this group
    int                             CurrentItemNum;  //current item number
    for (CurrentItemNum = 0; CurrentItemNum < TotalItems; ++CurrentItemNum)
    {
        SIniFile_Item*  CurrentItem = *ItemIterator;  //get current item
        ++ItemIterator;  //advance the item iterator
        if (CurrentItem->Name == Name)
        {
            return CurrentItem;  //return current item
        }
    }
    return NULL;  //not found; return error (NULL)
}
//=======================================================================================================


//=======================================================================================================
void CIniFile::AddGroup(STRING_CLASS GroupName)
{
    /*
        Adds a group
    */
    SIniFile_Group* Group   = GetGroup(GroupName);  //get the appropriate group structure
    if (Group == NULL)  //if group doesnt exist
    {
        Group = new SIniFile_Group;  //create a new group
        Group->Name = GroupName;  //set the name
        Groups.push_back(Group);  //add the group to the list
    }
}
//=======================================================================================================


//=======================================================================================================
void CIniFile::RemoveGroup(STRING_CLASS GroupName)
{
    /*
        Removes a group
    */
    SIniFile_Group* Group   = GetGroup(GroupName);  //get the appropriate group structure
    if (Group == NULL)  //if group doesnt exist
    {
        return;  //group is already gone; do nothing
    }
    list<SIniFile_Item*>::iterator  ItemIterator    = Group->Items.begin();  //item interator initialisation
    int                             TotalItems      = Group->Items.size();  //get total amount of items in this group
    int                             CurrentItemNum;  //current item number
    for (CurrentItemNum = 0; CurrentItemNum < TotalItems; ++CurrentItemNum)
    {
        SIniFile_Item*  CurrentItem = *ItemIterator;  //get current item
        ++ItemIterator;  //advance the item iterator
        delete CurrentItem;  //free the item
    }
    Groups.remove(Group);  //remove the group from the list
    delete Group;  //free the group
}
//=======================================================================================================


//=======================================================================================================
bool CIniFile::GroupExists(STRING_CLASS GroupName)
{
    /*
        Determines if a group exists
    */
    SIniFile_Group* Group   = GetGroup(GroupName);  //get the appropriate group structure
    if (Group == NULL)  //if group doesnt exist
    {
        return false;  //group doesn't exist
    }
    else
    {
        return true;  //group exists
    }
}
//=======================================================================================================
