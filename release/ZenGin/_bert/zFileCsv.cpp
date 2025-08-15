#include "zcore.h"
#include "zfilecsv.h"

const zSTRING CSV_DEF_FIELD_DELIMITER	= ";";	// Trennzeichen zwischen Datenfeldern (z.B. Feld1;Feld2;Feld3)
const zSTRING CSV_DEF_FIELD_FRAME		= "\""; // Rahmenzeichen um ein Feld (z.B. "Feld1")

zCFileCSV::zCFileCSV(const zSTRING& path) : zFILE_FILE(path)
{
	InitCSV();
};

zCFileCSV::zCFileCSV() : zFILE_FILE()
{	
	InitCSV();	
};

zCFileCSV::~zCFileCSV()
{
};

void zCFileCSV::InitCSV()
{
	csvFieldDelimiter = CSV_DEF_FIELD_DELIMITER;
	csvFieldFrame = CSV_DEF_FIELD_FRAME;	
	csvCompleteDelimiter = csvFieldFrame + csvFieldDelimiter + csvFieldFrame;
	csvHasHeader = false;
	headerProcessed = false;
	column=1;
};



////////////////////////////////////////////////////////////////////////////////
// Format des CSV-Files
////////////////////////////////////////////////////////////////////////////////


// Delemiter: TAB '\t', Semikolon, Doppelpunkt, Komma
// Feld-Rahmenzeichen: Entweder '\"' oder leer
void zCFileCSV::SetFormat(bool hasHeader, const zSTRING& delimiter, const zSTRING& frame)
{
	csvFieldDelimiter = delimiter;
	csvFieldFrame = frame;
	csvHasHeader = hasHeader;
	csvCompleteDelimiter = csvFieldFrame + csvFieldDelimiter + csvFieldFrame;
};



////////////////////////////////////////////////////////////////////////////////
// Schreiben
////////////////////////////////////////////////////////////////////////////////



// Füge ein neues Feld zum aktuellen Datensatz hinzu
void zCFileCSV::AddNextField(const zSTRING& s)
{
	// Soll ein Feld-Delimiter angefuegt werden?
	if (!current_set.IsEmpty()) current_set = current_set + csvFieldDelimiter;
	// Feld mit Frame-Charactern dem Datensatz anfuegen
	current_set = current_set + csvFieldFrame + s + csvFieldFrame;	
};


// Füge eine neuen Header hinzu
void zCFileCSV::AddNextHeader(const zSTRING& s)
{
	if (!csvHasHeader) return;

	// Soll ein Feld-Delimiter angefuegt werden?
	if (!current_set.IsEmpty()) current_set = current_set + csvFieldDelimiter;
	// Feld mit Frame-Charactern dem Datensatz anfuegen
	current_set = current_set + csvFieldFrame + s + csvFieldFrame;	
};


// Schreibe den aktuellen Datensatz 
zBOOL zCFileCSV::WriteSet()
{
	if (csvHasHeader && !headerProcessed) return FALSE;

	zERROR_ID result = Write(current_set+"\r\n");
	current_set.Clear();
	return result == zERR_NONE;
};



////////////////////////////////////////////////////////////////////////////////
// Lesen
////////////////////////////////////////////////////////////////////////////////



// Hole das nächste Datenfeld
zSTRING zCFileCSV::GetNextField (const zSTRING& s)
{
	zSTRING result;

	if (!s.IsEmpty())
	{
		// Ermittle Spaltennummer		
		int i=0;
		while (i<columnList.GetNumInList() && columnList[i]!=s) i++;
		if ((i>=columnList.GetNumInList()) || (columnList[i]!=s)) return "";
		column=i+1;
	};

	// Wenn es einen Feldrahmen gibt (z.B. "Feld1"), dann ...
	if (!csvFieldFrame.IsEmpty())
	{		
		if (column==1)
		{
			int index = current_set.Search(csvCompleteDelimiter);
			result = current_set.Copied(csvFieldFrame.Length(),index-csvFieldFrame.Length());
		}
		else
		{
			int delimiterSize = csvCompleteDelimiter.Length();
			int index1 = current_set.Search(csvCompleteDelimiter,column-1);
			int index2 = current_set.Search(index1+1, csvFieldFrame+csvFieldDelimiter+csvFieldFrame,1);
			if (index1<0) return "";
			if (index2<0) index2 = current_set.Length()-1;
			index1 += delimiterSize;
			int copySize = index2-index1;			
			result = (copySize<=0 ? "" : current_set.Copied(index1,copySize));
		}
		//result.TrimLeft();
		//result.TrimRight();
		//result = result.PickWord(1,csvFieldFrame,csvFieldFrame);
	}
	else 
	{
		result = current_set.PickWord(column,csvFieldDelimiter,csvFieldDelimiter);		
	}
	column++;	
	return result;
};



// Lese den naechsten Satz
zBOOL zCFileCSV::ReadSet()
{
	if (csvHasHeader && !headerProcessed) return FALSE;
	zERROR_ID result = Read(current_set);
	column = 1;
	return result == zERR_NONE;
};

zBOOL zCFileCSV::ReadHeader()
{
	if (!csvHasHeader || headerProcessed) return FALSE;
	
	zERROR_ID result = Read(current_set);
	column = 1;
	if (result != zERR_NONE) return FALSE;
	
	zSTRING s;
	do
	{
		s= GetNextField();
		if (!s.IsEmpty()) columnList.InsertEnd(s);
	} while (!s.IsEmpty());
	
	headerProcessed = true;

	return result == zERR_NONE;
};

zBOOL zCFileCSV::WriteHeader()
{
	if (!csvHasHeader || headerProcessed) return FALSE;
	zERROR_ID result = Write(current_set+"\n");
	current_set.Clear();
	headerProcessed = true;
	return result == zERR_NONE;
};
