// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_HIDAPI
// - ------------------------------------------------------------------------------------------ - //
#include "Input_3DMouse_SpaceNavigator.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Real.h>
#include <Debug/GelDebug.h>

#include <Graphics/Graphics.h>
#include <Graphics/GraphicsDraw.h>
// - ------------------------------------------------------------------------------------------ - //
#include <hidapi.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
hid_device* SpaceNavigator_HID_Handle = 0;
float SpaceNavigator[6];
int SN_DOF[6];
int SpaceNavigator_Button;
// - ------------------------------------------------------------------------------------------ - //
struct SpaceNavigator_Packet {
	char Type;
//	short a;
//	short b;
//	short c;
	char a,b,c,d,e,f;

	char PAD;
	int MORE_PAD[12];
};// __attribute__((packed));
// - ------------------------------------------------------------------------------------------ - //
void HIDAPI_Check() {
	hid_device_info* Devices;
	hid_device_info* CurrentDevice;

	Devices = hid_enumerate(0x0, 0x0);
	CurrentDevice = Devices;	
	while ( CurrentDevice ) {
		VLog("");
		VLog("Device Found!");
		VLog("  VID PID: %04hx %04hx",	CurrentDevice->vendor_id, CurrentDevice->product_id );
		VVLog("  path: %s", 				CurrentDevice->path );
		VLog("  serial_number: %ls",		CurrentDevice->serial_number);
		VLog("");
		VLog("  Manufacturer: %ls",		CurrentDevice->manufacturer_string);
		VLog("  Product:      %ls",		CurrentDevice->product_string);
		VLog("  Release:      %hx",		CurrentDevice->release_number);
		VLog("  Interface:    %d",		CurrentDevice->interface_number);
		VLog("");
		CurrentDevice = CurrentDevice->next;
	}
	hid_free_enumeration( Devices );	
}
// - ------------------------------------------------------------------------------------------ - //
void SpaceNavigator_Init() {
	SpaceNavigator_HID_Handle = 0;
	
	// Check for Space Navigator //
	hid_device* HIDHandle = hid_open( 0x046d, 0xc626, NULL );
	if ( HIDHandle ) {
		int MAX_STR = 256;
		wchar_t Manufacturer[MAX_STR];
		wchar_t Product[MAX_STR];
		//wchar_t SerialNumber[MAX_STR];

		// Just in case, zero //			
		Manufacturer[0] = 0;
		Product[0] = 0;
		//SerialNumber[0] = 0;
		
		int Ret;
		
		// Get Strings //
		Ret = hid_get_manufacturer_string(HIDHandle, Manufacturer, MAX_STR);
		Ret = hid_get_product_string(HIDHandle, Product, MAX_STR);
		//Ret = hid_get_serial_number_string(HIDHandle, SerialNumber, MAX_STR);

		Log( "* %ls %ls (HID Device) Found!", Manufacturer, Product );
		
		hid_set_nonblocking( HIDHandle, 1 );

		SpaceNavigator_HID_Handle = HIDHandle;
	}
}
// - ------------------------------------------------------------------------------------------ - //
void SpaceNavigator_Update() {
	if ( SpaceNavigator_HID_Handle ) {
		SpaceNavigator_Packet Packet;
		
		// NOTE: Max seems to be between 340 and 350 per axis limit (+,-) //
		float DOF_Scalar = 350.0f;

		int Count = 0;

		do {
			Count = hid_read( SpaceNavigator_HID_Handle, (unsigned char*)&Packet, sizeof(SpaceNavigator_Packet) );
			if ( Count > 0 ) {
				if ( Packet.Type == 1 ) {
					// Translation //
					SN_DOF[0] = (Packet.a & 0x000000ff) | ((int)Packet.b<<8 & 0xffffff00);
					SN_DOF[1] = (Packet.c & 0x000000ff) | ((int)Packet.d<<8 & 0xffffff00); 
					SN_DOF[2] = (Packet.e & 0x000000ff) | ((int)Packet.f<<8 & 0xffffff00);

					SpaceNavigator[0] = SN_DOF[0] / DOF_Scalar;
					SpaceNavigator[1] = SN_DOF[1] / DOF_Scalar;
					SpaceNavigator[2] = SN_DOF[2] / DOF_Scalar;
				}
				else if ( Packet.Type == 2 ) {
					// Rotation //
					SN_DOF[3] = (Packet.a & 0x000000ff) | ((int)Packet.b<<8 & 0xffffff00);
					SN_DOF[4] = (Packet.c & 0x000000ff) | ((int)Packet.d<<8 & 0xffffff00); 
					SN_DOF[5] = (Packet.e & 0x000000ff) | ((int)Packet.f<<8 & 0xffffff00);

					SpaceNavigator[3] = SN_DOF[3] / DOF_Scalar;
					SpaceNavigator[4] = SN_DOF[4] / DOF_Scalar;
					SpaceNavigator[5] = SN_DOF[5] / DOF_Scalar;
				}
				else if ( Packet.Type == 3 ) {
					// Buttons //
					SpaceNavigator_Button = Packet.a;
				}
				else {
					Log( "Unknown Packet" );
				}
			}
		}
		while ( Count > 0 );
	}
	//Log( "%i %i %i -- %i %i %i", SN_DOF[0], SN_DOF[1], SN_DOF[2], SN_DOF[3], SN_DOF[4], SN_DOF[5] );
}
// - ------------------------------------------------------------------------------------------ - //
void SpaceNavigator_DrawValues() {
	if ( SpaceNavigator_HID_Handle ) {
		for ( size_t idx = 0; idx < 6; idx++ ) {
			gelSetColor( GEL_RGB_YELLOW );
			gelDrawCircle( Vector3D( -96 + ((int)idx * 32), 140, 0), Real(16) );

			if ( SpaceNavigator[idx] > 0.0f ) {
				gelSetColor( GEL_RGB_WHITE );
			}
			else {
				gelSetColor( GEL_RGB_RED );				
			}
			gelDrawCircleFill( Vector3D( -96 + ((int)idx * 32), 140, 0), Real(SpaceNavigator[idx] * 16.0f) );
		}
	}	
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_HIDAPI //
// - ------------------------------------------------------------------------------------------ - //
