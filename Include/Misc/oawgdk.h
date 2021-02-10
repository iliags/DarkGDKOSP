#pragma once

#pragma comment ( lib, "oawgdk.lib"  )

void     oawLoadSound            (int id , char* file);
void     oawPlaySound2d          (int id , bool loop);
void     oawDeleteSound          (int id);
void     oawRelease              (      );
void     oawPanSound             (int id , float pan);
void     oawStopSound            (int id);
void     oawSetVolume            (int id , float vol);
void     oawSetSpeed             (int id , float speed);
void     oawSetPlayPosition      (int id , int pos );
void     oawPlaySound3d          (int id,float x ,float y , float z , bool loop);
void     oawSet3dPosition        (int id,float x,float y ,float z);
void     oawSetMasterVolume      (float vol);
void     oawSetMin3dDistance     (int id , float distance);
void     oawSetMax3dDistance     (int id , float distance);
void     oawSetListener3dPosition(float x, float y , float z ,float lookx , float looky ,float lookz);
void     oawEnableWavesReverb    (int id ,float fInGain, float fReverbMix,float fReverbTime, float fHighFreqRTRatio);
void     oawDisableWavesReverb   (int id);
void     oawDisableAllEffects    ();
void     oawEnableEcho           (int id, float fWetDryMix,float fFeedback,float fLeftDelay,float fRightDelay, int lPanDelay);
void     oawDisableEcho          (int id);
void     oawSetIsPaused          (int id , bool choice);
void     oawSetIsLooped          (int id , bool choice);
bool     oawGetIsPaused          (int id);
float    oawGetMax3dDistance     (int id);
float    oawGetMin3dDistance     (int id);
float    oawGetSoundPan          (int id);
float    oawGetPlaybackSpeed     (int id);
int      oawGetPlayLength        (int id);
int      oawGetPlayPosition      (int id);
float    oawGet3dpositionX       (int id);
float    oawGet3dpositionY       (int id);
float    oawGet3dpositionZ       (int id);
float    oawGetSoundVolume       (int id);
bool     oawGetIsFinished        (int id);
bool     oawGetIsLooped          (int id);