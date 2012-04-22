
// - -------------------------------------------------------------------------------------------------------------- - //
// ** Sound Manager 2 ** //
soundManager.url = 'external/sm2/';
soundManager.flashVersion = 9; // optional: shiny features (default = 8)
soundManager.useFlashBlock = false; // optionally, enable when you're ready to dive in	
//soundManager.waitForWindowLoad = true;
//soundManager.debugMode = false;
// ** Sound Manager 2 ** //
// - -------------------------------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------------------------------- - //
var SoundEnabled = true;
// - -------------------------------------------------------------------------------------------------------------- - //
//var SoundFile_Prefix = "Content/Sound/";
//var SoundFile_Ext = ".wav";
var SoundFile_Prefix = "Content/SoundMP3/";
var SoundFile_Ext = ".mp3";
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
	return soundManager.ok();
}
// - -------------------------------------------------------------------------------------------------------------- - //
function sndLoad( _Name, _File ) {
	if ( !SoundEnabled )
		return;

	soundManager.createSound({
		id: _Name,
		autoLoad: true,
		autoPlay: false,
		multiShot: true,
		url: SoundFile_Prefix + _File + SoundFile_Ext,
		volume: 50
	});	
}
// - -------------------------------------------------------------------------------------------------------------- - //
function sndLoadAndPlay( _Name, _File ) {
	if ( !SoundEnabled )
		return;

	soundManager.createSound({
		id: _Name,
		autoLoad: true,
		autoPlay: true,
		url: SoundFile_Prefix + _File + SoundFile_Ext,
		volume: 50
	});	
}
// - -------------------------------------------------------------------------------------------------------------- - //
function sndLoadAndPlayAndLoop( _Name, _File ) {
	if ( !SoundEnabled )
		return;

	soundManager.createSound({
		id: _Name,
		autoLoad: true,
		autoPlay: true,
		loops: 999999,
		url: SoundFile_Prefix + _File + SoundFile_Ext,
		volume: 50
	});	
}
// - -------------------------------------------------------------------------------------------------------------- - //
function sndPlay( _Name ) {
	if ( !SoundEnabled )
		return;

	soundManager.play( _Name );
}
// - -------------------------------------------------------------------------------------------------------------- - //
function sndHasLoaded( _Name ) {
	if ( !SoundEnabled )
		return false;

	if ( soundManager.sounds[_Name] )
		return !soundManager.sounds[_Name].isBuffering;
	return false;
}
// - -------------------------------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------------------------------- - //
function sndPause( _Name ) {
	if ( soundManager.getSoundById(_Name) )
		soundManager.getSoundById(_Name).pause();		
}
// - -------------------------------------------------------------------------------------------------------------- - //
function sndResume( _Name ) {
	if ( soundManager.getSoundById(_Name) )
		soundManager.getSoundById(_Name).resume();
}
// - -------------------------------------------------------------------------------------------------------------- - //

