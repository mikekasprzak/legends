// - -------------------------------------------------------------------------------------------------------------- - //
var SoundEnabled = true;
// - -------------------------------------------------------------------------------------------------------------- - //
//var SoundFile_Prefix = "Content/Sound/";
//var SoundFile_Ext = ".wav";
//var SoundFile_Prefix = "Content/SoundMP3/";
//var SoundFile_Ext = ".mp3";
var SoundFile_Prefix = "Content/SoundOGG/";
var SoundFile_Ext = ".ogg";
// - -------------------------------------------------------------------------------------------------------------- - //
var SoundNames = {};
// - -------------------------------------------------------------------------------------------------------------- - //


// - -------------------------------------------------------------------------------------------------------------- - //
function sndInit() {
	SoundEnabled = !isMobileSafari();
}
// - -------------------------------------------------------------------------------------------------------------- - //
function sndExit() {
}
// - -------------------------------------------------------------------------------------------------------------- - //
function sndAvailable() {
	if ( !SoundEnabled )
		return false;
	return buzz.isSupported();
}
// - -------------------------------------------------------------------------------------------------------------- - //
function sndLoad( _Name, _File ) {
	if ( !SoundEnabled )
		return;
		
	SoundNames[_Name] = new buzz.sound( SoundFile_Prefix + _File, {
		formats: [ "ogg" ],
		preload: true,
		autoplay: false,
		loop: false
	});
/*		
	soundManager.createSound({
		id: _Name,
		autoLoad: true,
		autoPlay: false,
		multiShot: true,
		url: SoundFile_Prefix + _File + SoundFile_Ext,
		volume: 50
	});	
*/
}
// - -------------------------------------------------------------------------------------------------------------- - //
function sndLoadAndPlay( _Name, _File ) {
	if ( !SoundEnabled )
		return;

	SoundNames[_Name] = new buzz.sound( SoundFile_Prefix + _File, {
		formats: [ "ogg" ],
		preload: true,
		autoplay: true,
		loop: false
	});
}
// - -------------------------------------------------------------------------------------------------------------- - //
function sndPlay( _Name ) {
	if ( !SoundEnabled )
		return;

	if ( !SoundNames[_Name].isPaused() )
		SoundNames[_Name].setTime( 0 );
	else
		SoundNames[_Name].play();
}
// - -------------------------------------------------------------------------------------------------------------- - //
function sndHasLoaded( _Name ) {
	if ( !SoundEnabled )
		return false;

	if ( SoundNames[_Name] )
		return SoundNames[_Name].getStateCode() >= 0;//buzz.HAVE_CURRENT_DATA;
	return false;
}
// - -------------------------------------------------------------------------------------------------------------- - //

function sndPause( _Name ) {
	if ( SoundNames[_Name] )
		SoundNames[_Name].pause();
}
// - -------------------------------------------------------------------------------------------------------------- - //
function sndResume( _Name ) {
	if ( SoundNames[_Name] )
		SoundNames[_Name].play();
}
// - -------------------------------------------------------------------------------------------------------------- - //
