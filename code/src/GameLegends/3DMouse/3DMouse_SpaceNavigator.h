// - ------------------------------------------------------------------------------------------ - //
#ifndef __3DMOUSE_SPACENAVIGATOR_H__
#define __3DMOUSE_SPACENAVIGATOR_H__
// - ------------------------------------------------------------------------------------------ - //
void HIDAPI_Check();
void SpaceNavigator_Init();
void SpaceNavigator_Update();

void SpaceNavigator_DrawValues();

extern float SpaceNavigator[6];
extern int SpaceNavigator_Button;
// - ------------------------------------------------------------------------------------------ - //
#endif // __3DMOUSE_SPACENAVIGATOR_H__ //
// - ------------------------------------------------------------------------------------------ - //
