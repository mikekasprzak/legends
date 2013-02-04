<?php

$TickStart = microtime( true );

// PHP aBoaT Server //
$DataFolder = "";
$CTX =& $_REQUEST; // Reference //

$RegionX = (int)$CTX["rx"];
$RegionY = (int)$CTX["ry"];

$file = sprintf("%s%02xx%02x.png", $DataFolder, $RegionX, $RegionY );

// Gets Regions (8x8 groups of tiles) //
if ( $CTX["action"] == "get" ) {	
	// @ sign to suppress warning //
	$fp = @fopen($file,'rb');
	if ( $fp ) {
		flock( $fp, LOCK_SH );
		//header('Content-Type: image/png');
		fpassthru( $fp );
		flock( $fp, LOCK_UN );
		fclose( $fp );
	}
	else {
		// Fail //
		die( "Failed to find region" );
	}
}
// Sets pixels/tiles of Regions //
else if ( $CTX["action"] == "update" ) {
	$x = (int)$CTX["x"];
	$y = (int)$CTX["y"];
	$val = (int)$CTX["val"];

	// Attempt to open the File //
	$fp = @fopen($file,'rb');
	if ( $fp ) {
		// Lock the File //
		flock( $fp, LOCK_EX );

		$img = imagecreatefrompng( $file );
		imagesetpixel( $img, $x, $y, imagecolorallocate( $img, ($val)&0xff, ($val>>8)&0xff, ($val>>16)&0xff ) );
		imagepng($img,$file);

		//header('Content-Type: image/png');
		imagepng($img);
		imagedestroy($img);

		// Unlock //
		flock( $fp, LOCK_UN );
		fclose( $fp );
	}
	else {
		// Fail //
		die( "Failed to find file to update" );
	}
}
// Upload a whole region //
else if ( $CTX["action"] == "upload" ) {
	$data64 = $CTX["data"];
//	$data64 =& $CTX["data"]; // Optimization? //
	
	$data64 = str_replace('data:image/png;base64,', '', $data64);
	$data64 = str_replace(' ', '+', $data64);
	$data = base64_decode($data64);
	
	$img = @imagecreatefromstring($data);

	if ( $img ) {
		// Attempt to open the File //
		$fp = @fopen($file,'rb');
		if ( $fp ) {
			// Lock the File //
			flock( $fp, LOCK_EX );
	
			imagepng($img,$file);
		
			header('Content-Type: image/png');
			imagepng($img);
	
			// Unlock //
			flock( $fp, LOCK_UN );
			fclose( $fp );
		}
		// Load Failed, which means we don't need a lock //
		else {
			imagepng($img,$file);
		
			header('Content-Type: image/png');
			imagepng($img);
		}
	
		imagedestroy($img);
	}
	else {
		// Fail //
		die( "Failed to decode image" );
	}
}

echo "\nTime Elapsed: " . (microtime(true)-$TickStart);

?>
