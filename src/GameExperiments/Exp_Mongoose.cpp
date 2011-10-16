// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_MONGOOSE
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include "mongoose.h"
// - ------------------------------------------------------------------------------------------ - //
#define MG_NEWLINE "<br />"
// - ------------------------------------------------------------------------------------------ - //
static void *goose_callback( enum mg_event event, struct mg_connection *conn, const struct mg_request_info *request_info ) {
	if (event == MG_NEW_REQUEST) {
		// Send HTTP Header //
//		mg_printf(conn, "HTTP/1.1 200 OK\r\n" "Content-Type: text/plain\r\n\r\n" );
		mg_printf(conn, "HTTP/1.1 200 OK\r\n" "Content-Type: text/html\r\n\r\n" );
		
		// Send Content //
		mg_printf(conn, "%s" MG_NEWLINE, request_info->uri);
		mg_printf(conn, "Request Method: %s" MG_NEWLINE, request_info->request_method );
		mg_printf(conn, "Remote User: <b>%s</b>" MG_NEWLINE, request_info->remote_user );
		mg_printf(conn, "Remote IP: %i.%i.%i.%i" MG_NEWLINE, ((unsigned char*)(&request_info->remote_ip))[3], ((unsigned char*)(&request_info->remote_ip))[2], ((unsigned char*)(&request_info->remote_ip))[1], ((unsigned char*)(&request_info->remote_ip))[0] );
		
		// Mark as processed (non null) //
		return (void*)-1;
	} 
	else {
		return NULL;
	}
}
// - ------------------------------------------------------------------------------------------ - //
struct mg_context *MongooseContext = 0;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
extern void ExpInit_Mongoose();
void ExpInit_Mongoose() {
	const char *options[] = { "listening_ports", "8080", NULL };	
	MongooseContext = mg_start( &goose_callback, NULL, options );	
}
// - ------------------------------------------------------------------------------------------ - //
extern void ExpExit_Mongoose();
void ExpExit_Mongoose() {
	mg_stop( MongooseContext );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#endif // USES_MONGOOSE //
// - ------------------------------------------------------------------------------------------ - //
