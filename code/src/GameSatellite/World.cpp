
// Space Station Tiles //
class cTile {
public:
	
};

// TODO: Special Vector Type that is made of Integers, and shifted before use //
// 		IVector3D might be usable, but I will need a "ToVector3D" func.
//		28:4  --> +134,217,728.16
//		25:7  --> +16,777,216.128
//		24:8  --> +8,388,608.256
//		20:12 --> +524,288.4096
//		16:16 --> +32768.65536		**	Maximum Level Size 32768x32768 (1MB, -16,384 to +16,384)

// Technically, we can use the above as a Zone size (Max +/-16,384). Stepping over the line does a
//   zone advance, Pos += 32768 or Pos -= 32768.

// Cell Grid type. A grid of X by Y sized blocks, with methods for addressing linearly and atomically //

// Trails and Smoke Gestures //

// Players //
class cObject {
	
};

// Simpler objects that are collected ? //
class cItemObject {
	
};

// Large massive bodies like planets, asteroids, and suns //
class cMassiveObject {
	
};
