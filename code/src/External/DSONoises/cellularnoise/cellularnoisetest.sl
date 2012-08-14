/*
 * cellularnoisetest.sl : simple shader to test the cellular noise DSO
 *
 * Lighting has absolutely no influence on this shader.
 * The colors are always fully bright.
 */

surface cellularnoisetest() {

 color white = color( 1.0, 1.0, 1.0 );
 color black  = color( 0.0, 0.0, 0.0 );

 float f1, f2, id;
 cellularnoise(16.0*P, f1, f2, id);
 color cellcolor = color(mod(id/256, 1), mod(id/(64*256), 1), mod(id/(4096*256), 1));
 float weight = f2 - f1 + 0.3;

 Ci = mix(black, cellcolor, weight);
 Oi = Os;
}
