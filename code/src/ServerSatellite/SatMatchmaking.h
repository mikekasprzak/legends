

		if ( MyGeo->IsGood() ) {	
			int MyPort = 10240;
			int MyVersion = 100;
			
			printf( "Sending Update Packet...\n" );
			fflush( 0 );
			
			{
				char KeyData[1024];
				safe_sprintf( KeyData, sizeof(KeyData), "%i&%s&%i&%s",
					MyPort,
					MyGeo->IP,
					MyVersion,
					"ChupacabraSatellites"
					);
				
				MD5Hash MD5 = hash_MD5_Data( KeyData, strlen(KeyData) );	
				
				char PostData[4096];
				safe_sprintf( PostData, sizeof(PostData), "action=update&Address=%s&Port=%i&Version=%i&Latitude=%f&Longitude=%f&Info=%s%s%s%s&Key=%s",
					MyGeo->IP,
					MyPort,
					MyVersion,
					MyGeo->Latitude,
					MyGeo->Longitude,
					"DD",
					MyGeo->Country,
					"__",
					"__",
					MD5.Text // Not actually a key //
					);
				
				printf( "To Send: %s\n", PostData );
				
				GelArray<char>* ServerData = gelNetPostText( "http://sykhronics.com/satellite/json.php", PostData );
				
				// Nothing to do with it //
				printf( "Return: \n%s\n", ServerData->Data );
				
				delete_GelArray<char>( ServerData );
			}
		}	
		
		