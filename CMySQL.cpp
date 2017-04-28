#ifdef BCB  //if compiling under BCB
#include <windows.h>  //include windows.h
#endif

#include "CMySQL.h"  //include the mysql.h files

//---------------------------------------------------------------------------

//CMySQL class implementation

//---------------------------------------------------------------------------

CMySQL::CMySQL()  //constructor
{
    Connected = false;  //initialisation: not yet connected
    Connection = new MYSQL;  //create a new MYSQL structure
    mysql_init(Connection);  //initialise the MYSQL connection structure
}

CMySQL::~CMySQL()  //destructor
{
    Disconnect();  //disconnect from the server
    delete Connection;  //free the MYSQL structure
}

bool CMySQL::Connect(STRING_CLASS Server, STRING_CLASS Username, STRING_CLASS Password, STRING_CLASS Database)  //connect to the server using appropriate credentials and initial database
{
    FreeAllResults();  //free all results
    if (!mysql_real_connect(Connection, Server.c_str(), Username.c_str(), Password.c_str(), Database.c_str(), 0, 0, 0))  //attempt to connect
    {
        Connected = false;  //connect failed, so set the flag
    }
    else
    {
        Connected = true;  //connect succeeded, so set the flag
    }
    return Connected;  //return the connection success flag
}

void CMySQL::Disconnect()  //disconnect from the server
{
    FreeAllResults();  //free all results
    if (Connected)  //if we are actually connected
    {
        mysql_close(Connection);  //close the connection
        Connected = false;  //set the connected flag
    }
}

CMySQLResult* CMySQL::Query(STRING_CLASS Query) //perform a mysql query
{
    /*
      The general idea here is to perform the query, buffer the entire result into a 
      CMySQLResult structure and return it. If the query fails, the function will
      return NULL. If the query succeeded but has no result set, a CMySQLResult will
      still be returned, but will contain no information. To determine if this
      happened, use the CMySQL::GetResult_Exists() function.
    */
    int QueryResult = mysql_query(Connection, Query.c_str());  //perform the query
    if (QueryResult != 0)  //if the query failed to execute (i.e. error in syntax etc)
    {
        return NULL;  //return a NULL result set
    }

    //query succeeded!
    MYSQL_RES*      ResultSet   = mysql_store_result(Connection);  //buffer the entire result from the server

    CMySQLResult*   Result      = NULL;  //the result pointer to be returned

    if (ResultSet == NULL)  //if there is no result set (but the query succeeded)
    {
        Result = new CMySQLResult();    //create a new CMySQLResult
        mysql_free_result(ResultSet);  //free the result set
    }
    else
    {
        //if there is a result set
        Result = new CMySQLResult; //create a new CMySQLResult

        int Rows    = mysql_num_rows(ResultSet);  //determine how many rows there are in the result set
        int Fields  = mysql_num_fields(ResultSet);  //determine how many fields there are the result set
        Result->Data_Rows = Rows;  //set the amount of rows in the result class
        Result->Data_Fields = Fields;  //and the amount of fields in the result class

        Result->Data_Strings = new STRING_CLASS[Rows * Fields]; //allocate the memory for the data text strings
        Result->Data_FieldNames = new STRING_CLASS[Fields]; //allocate the memory for the field name text strings

        int Row     = 0;  //current row counter; initialised to zero
        int Field   = 0;  //current field counter; initialised to zero
        for (Row = 0; Row < Rows; ++Row)     //go through all the rows in the result set
        {
            MYSQL_ROW   RowData = mysql_fetch_row(ResultSet);  //fetch the row from the result set
            for (Field = 0; Field < Fields; ++Field)     //go through all the fields in the result set
            {
                int Index   = Result->GetIndex(Row, Field);  //calculate the index to set the string at int the array
                Result->Data_Strings[Index] = RowData[Field];  //set the string
            }
        }
        for (Field = 0; Field < Fields; ++Field)     //go through the the fields
        {
            MYSQL_FIELD*FieldData;  //structure for field information
            FieldData = mysql_fetch_field(ResultSet);  //fetch the field information
            Result->Data_FieldNames[Field] = FieldData->name;  //get the field name
        }
    }
    Results.push_back(Result);  //add the result to the list of results
    return Result;  //return the CMySQLResult
}

bool CMySQL::IsConnected()  //determines if the connection is established
{
    return Connected;  //return true if connected, and false if not
}

void CMySQL::FreeResult(CMySQLResult* Result)   //frees a result returned from Query()
{
    int SizeBefore  = Results.size();  //get size before remove attempt
    Results.remove(Result);  //remove the result from the list (if its there)
    if (Results.size() != SizeBefore)  //if the size has changed (i.e. the result was in the list)
    {
        delete Result;  //free the result
    }
}

void CMySQL::FreeAllResults()  //free all results created by this instance
{
    while (!Results.empty())     //while there are still results in the CMySQL instance
    {
        CMySQLResult*   Result  = Results.front();  //get a result from the list
        FreeResult(Result);  //free the result
    }
}

//---------------------------------------------------------------------------

//CMySQLResult class implementation

//---------------------------------------------------------------------------

CMySQLResult::CMySQLResult()  //constructor
{
    Data_Rows = 0;  //no rows
    Data_Fields = 0;  //no fields
    Data_Strings = NULL;  //no data strings
    Data_FieldNames = NULL;  //no field names
}

CMySQLResult::~CMySQLResult()  //destructor
{
    FreeData();  //deallocate memory allocated
}

bool CMySQLResult::GetResult_Exists()  //determine if this result has a result set
{
    if ((Data_Rows * Data_Fields) != 0)
    {
        return true;
    }    //if there are rows and fields, return true
    else
    {
        return false;
    }   //otherwise, we know there was no result
}

int CMySQLResult::GetResult_Rows()  //determine how many rows are in the result set
{
    return Data_Rows;  //return the amount of rows in the result set
}

int CMySQLResult::GetResult_Fields()  //determine how many fields are in the result set
{
    return Data_Fields;  //return the amount of fields in the result set
}

STRING_CLASS CMySQLResult::GetResult_FieldName(int Field)  //get the name of a certain field
{
    STRING_CLASS    Result;     //result string
    if (Field >= 0 && Field < Data_Fields)  //if the Field number is in valid range
    {
        Result = Data_FieldNames[Field];  //copy the appropriate string
    }
    return Result;  //return the result
}

STRING_CLASS CMySQLResult::GetResult_Text(int Row, int Field)  //get the result data at Row, Field
{
    STRING_CLASS    Result;     //result string
    if (Row >= 0 && Row < Data_Rows && Field >= 0 && Field < Data_Fields)  //if data item is in range
    {
        Result = Data_Strings[GetIndex(Row, Field)];     //copy the data item to the result string
    }
    return Result;  //return the result
}

void CMySQLResult::FreeData()  //deallocate data
{
    if (Data_Strings != NULL)  //if there are data strings to deallocate
    {
        delete[] Data_Strings;  //delete them
        Data_Strings = NULL;  //reset the pointer
    }
    if (Data_FieldNames != NULL)     //if there are field name strings to delete
    {
        delete[] Data_FieldNames;  //delete them
        Data_FieldNames = NULL;  //reset the pointer
    }
    Data_Rows = 0;  //no rows anymore
    Data_Fields = 0;  //no fields anymore
}

int CMySQLResult::GetIndex(int Row, int Field)  //determine the array index for a certain row/field
{
    return Row + (Field * Data_Rows);  //return the column array index
}

//---------------------------------------------------------------------------

