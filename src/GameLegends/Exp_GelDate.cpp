#ifdef USES_WINDOWS
#include <Debug/Log.h>
#include <Timer/GelDate.h>
#include <Timer/GelTime.h>

extern void CallExp_GelDate();
void CallExp_GelDate() {
	Log("+ Now Testing GelDate\n");
	{
		GelDate Today = get_GelDate();
		Log( "Today's Date is: %i\n", Today );
		
		//GelDate TestDate = 19800706;
		//GelDate TestDate = new_GelDate( GEL_JULY, 6, 1980 );
		GelDate TestDate = new_GelDate( GEL_JANUARY, 1, 2011 );
		Log( "TestDate is: %i\n", TestDate );
		
		if ( Today > TestDate ) {
			Log( "Today is greater than TestDate\n" );
		}
		else if ( Today == TestDate ) {
			Log( "Today is TestDate\n" );
		}
		else {
			Log( "Today is less than TestDate\n" );
		}
			
		Log( "Today is Month: %i  Day: %i  Year: %i\n", get_Month_GelDate(Today), get_Day_GelDate(Today), get_Year_GelDate(Today) );
	}
	Log("- Done Testing GelDate\n");
	Log("\n");
	Log("+ Now Testing GelTime\n");
	{
		GelTime Now = get_GelTime();
		Log( "Now is is: %i\n", Now );
		
		GelTime TestTime = new_GelTime( 10, 0, 0 );
		Log( "TestTime is: %i\n", TestTime );
		
		if ( Now > TestTime ) {
			Log( "Now is greater than TestTime\n" );
		}
		else if ( Now == TestTime ) {
			Log( "Now is TestTime\n" );
		}
		else {
			Log( "Now is less than TestTime\n" );
		}
		
		Log( "Now is Hour: %i  Minute: %i  Second: %i\n", get_Hour_GelTime(Now), get_Minute_GelTime(Now), get_Second_GelTime(Now) );
	}
	Log("- Done Testing GelTime\n");
	Log("\n");
}
#endif // USES_WINDOWS //
