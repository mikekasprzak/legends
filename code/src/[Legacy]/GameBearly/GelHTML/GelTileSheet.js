// - -------------------------------------------------------------------------------------------------------------- - //
// cTileSheet - Load an image and draw cells by number. //
// - -------------------------------------------------------------------------------------------------------------- - //
function cTileSheet( InFile, _XCells, _YCells ) {
	// Data //
	this.XCells = _XCells;
	this.YCells = _YCells;
	this.CellW = 0;
	this.CellH = 0;

	var _super = this;	// Make a copy of "this", so we can access it inside the function //
	this.Data = new Image;
	this.Data.onload = function() {
		_super.CellW = _super.Data.width / _XCells;
		_super.CellH = _super.Data.height / _YCells;
	};
	this.Data.src = InFile;
}
// - -------------------------------------------------------------------------------------------------------------- - //
cTileSheet.prototype.Draw = function( cell, _x, _y ) {
	var cx = (cell % this.XCells); // We have to subtract the mod, since all numbers are doubles //
	cell -= cx;
	cx *= this.CellW;
	var cy = (cell / this.XCells) * this.CellH;	// Yes, XCells again //
	ctx.drawImage( this.Data, cx, cy, this.CellW, this.CellH, Math.round(_x), Math.round(_y), this.CellW, this.CellH );
}
// - -------------------------------------------------------------------------------------------------------------- - //
cTileSheet.prototype.DrawCentered = function( cell, _x, _y ) {
	var cx = (cell % this.XCells); // We have to subtract the mod, since all numbers are doubles //
	cell -= cx;
	cx *= this.CellW;
	var cy = (cell / this.XCells) * this.CellH; // Yes, XCells again //
	ctx.drawImage( this.Data, cx, cy, this.CellW, this.CellH, Math.round(_x - (this.CellW >> 1)), Math.round(_y - (this.CellH >> 1)), this.CellW, this.CellH );
}
// - -------------------------------------------------------------------------------------------------------------- - //
