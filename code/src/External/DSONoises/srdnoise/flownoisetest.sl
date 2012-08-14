/*
 * flownoisetest.sl : simple shader to test the "srdnoise" DSO with "flow noise"
 *
 * Lighting has absolutely no influence on this shader.
 * The colors are always fully bright.
 */

surface flownoisetest() {

 // Define some colors we will use for this surface
 color white = color( 1.0, 1.0, 1.0 );
 color black  = color( 0.0, 0.0, 0.0 );

 float ds = 0.0;
 float dt = 0.0;
 float advect_s = 0.0;
 float advect_t = 0.0;
 float advection = 0.2;

 // Sum four octaves of noise, advect each component along the gradient so far
 float weight = srdnoise(8.0*s, 8.0*t, time, ds, dt);
 advect_s = -advection * ds;
 advect_t = -advection * dt;
 weight += 0.5 * srdnoise(16.0*s + advect_s, 16.0*t + advect_t, time*2, ds, dt);
 advect_s -= advection * ds * 0.5;
 advect_t -= advection * dt * 0.5;
 weight += 0.25 * srdnoise(32.0*s + advect_s, 32.0*t + advect_t, time*4, ds, dt);
 advect_s -= advection * ds * 0.25;
 advect_t -= advection * dt * 0.25;
 // No need to compute the derivative for the last component
 weight += 0.125 * srdnoise(64.0*s + advect_s, 64.0*t + advect_t, time*8);

 weight = 0.5 + weight * 0.4; // Shift and scale to interval [0,1]

 Ci = mix(black, white, weight);
 Oi = Os;
}
