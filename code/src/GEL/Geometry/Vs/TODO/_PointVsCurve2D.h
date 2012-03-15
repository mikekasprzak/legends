// - ------------------------------------------------------------------------------------------ - //
#ifndef __AdvancedGeometry_PointVsSphere2D_H__
#define __AdvancedGeometry_PointVsSphere2D_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector/Vector2D.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// http://alienryderflex.com/polyspline/
// - ------------------------------------------------------------------------------------------ - //
//  public domain function by Darel Rex Finley, 2006

bool pointInSplinePoly(double *poly, double X, double Y) {

  #define  SPLINE     2.
  #define  NEW_LOOP   3.
  #define  END       -2.

  double  Sx, Sy, Ex, Ey, a, b, sRoot, F, plusOrMinus, topPart, bottomPart, xPart ;
  int     i=0, j, k, start=0 ;
  bool    oddNodes=NO ;

  Y+=.000001;   //  prevent the need for special tests when F is exactly 0 or 1

  while (poly[i]!=END) {

    j=i+2; if (poly[i]==SPLINE) j++;
    if (poly[j]==END    || poly[j]==NEW_LOOP) j=start;

    if (poly[i]!=SPLINE && poly[j]!=SPLINE  ) {   //  STRAIGHT LINE
      if (poly[i+1]<Y && poly[j+1]>=Y || poly[j+1]<Y && poly[i+1]>=Y) {
        if (poly[i]+(Y-poly[i+1])/(poly[j+1]-poly[i+1])*(poly[j]-poly[i])<X) oddNodes=!oddNodes; }}

    else if (poly[j]==SPLINE) {                   //  SPLINE CURVE
      a=poly[j+1]; b=poly[j+2]; k=j+3; if (poly[k]==END || poly[k]==NEW_LOOP) k=start;
      if (poly[i]!=SPLINE) {
        Sx=poly[i]; Sy=poly[i+1]; }
      else {   //  interpolate hard corner
        Sx=(poly[i+1]+poly[j+1])/2.; Sy=(poly[i+2]+poly[j+2])/2.; }
      if (poly[k]!=SPLINE) {
        Ex=poly[k]; Ey=poly[k+1]; }
      else {   //  interpolate hard corner
        Ex=(poly[j+1]+poly[k+1])/2.; Ey=(poly[j+2]+poly[k+2])/2.; }
      bottomPart=2.*(Sy+Ey-b-b);
      if (bottomPart==0.) {   //  prevent division-by-zero
        b+=.0001; bottomPart-=.0004; }
      sRoot=2.*(b-Sy); sRoot*=sRoot; sRoot-=2.*bottomPart*(Sy-Y);
      if (sRoot>=0.) {
        sRoot=sqrt(sRoot); topPart=2.*(Sy-b);
        for (plusOrMinus=-1.; plusOrMinus<1.1; plusOrMinus+=2.) {
          F=(topPart+plusOrMinus*sRoot)/bottomPart;
          if (F>=0. && F<=1.) {
            xPart=Sx+F*(a-Sx); if (xPart+F*(a+F*(Ex-a)-xPart)<X) oddNodes=!oddNodes; }}}}

    if (poly[i]==SPLINE) i++;
    i+=2;
    if (poly[i]==NEW_LOOP) {
      i++; start=i; }}

  return oddNodes; }
// - ------------------------------------------------------------------------------------------ - //
// This five-cornered polygon makes a simple house shape:
// 1,0,  1,-1,  -1,-1,  -1,0,  0,1,  END

// This is the same house shape, but with the top corner turned into a spline point:
// 1,0,  1,-1,  -1,-1,  -1,0,  SPLINE,0,1,  END

// Same house shape, but with the two roof’s-eve corners turned into spline points:
// SPLINE,1,0,  1,-1,  -1,-1,  SPLINE,-1,0,  0,1,  END
// Note that this case would not work without the division-by-zero protection, because the
// eve points are vertically at the midpoint between the top and bottom of the house.

// Same house shape, with the two bottom corner points turned into spline points:
// 1,0,  SPLINE,1,-1,  SPLINE,-1,-1,  -1,0,  0,1,  END 	spline polygon

// Same house shape, with all five corners turned into spline points:
// SPLINE,1,0,  SPLINE,1,-1,  SPLINE,-1,-1,  SPLINE,-1,0,  SPLINE,0,1,  END 	spline polygon

// Here’s an example of using the “NEW_LOOP” tag to put two polygons in one.  In this case, the smaller polygon is a hole in the larger one, since it is inside it:
// SPLINE,1,1,  SPLINE,1,-1,  SPLINE,-1,-1,  SPLINE,-1,1,  NEW_LOOP,  SPLINE,.5,.5,  SPLINE,.5,-.5,  SPLINE,-.5,-.5,  SPLINE,-.5,.5,  END 	spline polygon with hole

// This uses the “NEW_LOOP” tag to make two loops, but they don’t overlap each other:
// -.25,0,  .125,0,  .125,-.875,  .25,-.875,  .25,-1,  -.25,-1,  -.25,-.875,  -.125,-.875,  -.125,-.125,  -.25,-.125,  NEW_LOOP,  SPLINE,-.125,.375,  SPLINE,.125,.375,  SPLINE,.125,.25,  SPLINE,-.125,.25,  END 	spline lower-case letter i

// You can’t do a real circle with splines, but this eight-point polygon makes a sweet fake:
// SPLINE,.4142,1,  SPLINE,1,.4142,  SPLINE,1,-.4142,  SPLINE,.4142,-1,  SPLINE,-.4142,-1,  SPLINE,-1,-.4142,  SPLINE,-1,.4142,  SPLINE,-.4142,1,  END
// FYI, .4142 is sqrt(2)-1.
// - ------------------------------------------------------------------------------------------ - //
// http://alienryderflex.com/spline_extent/
double splineXMax(double Sx, double a, double Ex) {

  double  c=Sx-a, d=c+Ex-a, F, X, max=Sx ;

  if (Ex>Sx) max=Ex;
  if (d!=0.) {
    F=c/d;
    if (F>0. && F<1.) {
      X=Sx-c*F; if (X>max) max=X; }}

  return max; }



double splineXMin(double Sx, double a, double Ex) {

  double  c=Sx-a, d=c+Ex-a, F, X, min=Sx ;

  if (Ex<Sx) min=Ex;
  if (d!=0.) {
    F=c/d;
    if (F>0. && F<1.) {
      X=Sx-c*F; if (X<min) min=X; }}

  return min; }



double splineYMax(double Sy, double b, double Ey) {

  double  c=Sy-b, d=c+Ey-b, F, Y, max=Sy ;

  if (Ey>Sy) max=Ey;
  if (d!=0.) {
    F=c/d;
    if (F>0. && F<1.) {
      Y=Sy-c*F; if (Y>max) max=Y; }}

  return max; }



double splineYMin(double Sy, double b, double Ey) {

  double c=Sy-b, d=c+Ey-b, F, Y, min=Sy ;

  if (Ey<Sy) min=Ey;
  if (d!=0.) {
    F=c/d;
    if (F>0. && F<1.) {
      Y=Sy-c*F; if (Y<min) min=Y; }}

  return min; }
// - ------------------------------------------------------------------------------------------ - //
  
// - ------------------------------------------------------------------------------------------ - //
bool TestPointVsSphere2D( const Vector2D& Pos, const Vector2D& VsPos, const Real VsRadius ) {
	return true;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
struct cPointVsSphere2D {
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
cPointVsSphere2D StartPointVsSphere2D( const Vector2D& Pos, const Vector2D& VsPos, const Real VsRadius ) {
	return cPointVsSphere2D();
}
// - ------------------------------------------------------------------------------------------ - //
bool TestPointVsSphere2D( const cPointVsSphere2D& Info ) {
	return true;
}
// - ------------------------------------------------------------------------------------------ - //
cPointVsSphere2D SolvePointVsSphere2D( const cPointVsSphere2D& Info ) {
	return cPointVsSphere2D();
}
// - ------------------------------------------------------------------------------------------ - //
cPointVsSphere2D SolvePointVsSphere2D( const Vector2D& Pos, const Vector2D& VsPos, const Real VsRadius ) {
	return cPointVsSphere2D();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __AdvancedGeometry_PointVsSphere2D_H__ //
// - ------------------------------------------------------------------------------------------ - //
