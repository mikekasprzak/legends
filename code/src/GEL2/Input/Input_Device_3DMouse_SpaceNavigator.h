// - ------------------------------------------------------------------------------------------ - //
#ifndef __INPUT_3DMOUSE_SPACENAVIGATOR_H__
#define __INPUT_3DMOUSE_SPACENAVIGATOR_H__
// - ------------------------------------------------------------------------------------------ - //
void HIDAPI_Check();
void SpaceNavigator_Init();
void SpaceNavigator_Update();

void SpaceNavigator_DrawValues();

extern float SpaceNavigator[6];
extern int SpaceNavigator_Button;
// - ------------------------------------------------------------------------------------------ - //
#endif // __INPUT_3DMOUSE_SPACENAVIGATOR_H__ //
// - ------------------------------------------------------------------------------------------ - //
