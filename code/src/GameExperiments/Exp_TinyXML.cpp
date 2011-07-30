
#include <Debug/Log.h>

#include <tinyxml.h>

extern void CallExp_TinyXML();
void CallExp_TinyXML() {
	Log("+ Now Testing TinyXML\n");
	{
		// TODO: Not sure why I can't get any node data as text.  Was loking for info a way to get text, but the text
		// function returns an TiXmlText type... dunno what tha tis. 
		
//		DataBlock* Jay = new_read_nullterminate_DataBlock( "Content/Misc/Junk.xml" );

		TiXmlDocument doc( "Content/Misc/Junk.xml" );
		doc.LoadFile();
		
		TiXmlHandle docHandle( &doc );
		//TiXmlElement* child2 = docHandle.FirstChild( "Document" ).FirstChild( "Element" ).Child( "Child", 1 ).ToElement();

		Log( "> %s\n", docHandle.ToText() );
		
		TiXmlElement* child = docHandle.FirstChild().ToElement();
		if ( child ) {
			Log( "> %s\n", child->GetText() );
		}
	
//		delete_DataBlock( Jay );
	}
	Log("- Done Testing TinyXML\n");
	Log("\n");
}
