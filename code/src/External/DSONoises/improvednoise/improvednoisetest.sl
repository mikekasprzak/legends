/*
 * improvednoisetest.sl : simple shader to test the improved noise DSO
 *
 * Lighting has absolutely no influence on this shader.
 * The colors are always fully bright.
 */

surface improvednoisetest() {

 color white = color( 1.0, 1.0, 1.0 );
 color black  = color( 0.0, 0.0, 0.0 );

 float weight = improvednoise(8.0*P);

 Ci = mix(black, white, weight);
 Oi = Os;
}
