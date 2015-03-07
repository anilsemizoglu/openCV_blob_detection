#include "utility.h"
#include "windows.h"

#define MAX_DATE 256

std::string get_date(void)
{
SYSTEMTIME st;
GetLocalTime(&st);
 std::string strMessage;

char the_date[MAX_DATE];
	the_date[0] = '\0';

 sprintf( the_date,
             "%02d-%02d_%02d%02d%02d", 
             //st.wYear,
             st.wMonth, 
             st.wDay,                      
             st.wHour, 
             st.wMinute, 
             st.wSecond);
             //st.wMilliseconds );
 
 strMessage = the_date;
return  strMessage;
/*
	time_t now;
	char the_date[MAX_DATE];

	the_date[0] = '\0';

	now = time(NULL);

	if (now != -1)
	{
		strftime(the_date, MAX_DATE, "%b%d_%H:%M:%S", gmtime(&now));
	}

	return std::string(the_date);
*/
}

