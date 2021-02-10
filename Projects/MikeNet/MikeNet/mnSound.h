#pragma once

/**
 * @brief Commands for procedural programming, that wrap around internal classes.
 *
 * These commands exist for those who prefer procedural programming over object orientated.
 * They wrap around the classes of the sound input/output module and deal with errors differently 
 * dependent on the error mode we are in.
 */
namespace mnSound
{
#ifdef C_LINKAGE
	extern "C"
	{
#endif
	DBP_CPP_DLL size_t GetNumInputDevices();
	DBP_CPP_DLL size_t GetNumOutputDevices();

	DBP_CPP_DLL unsigned short GetDeviceManuID(unsigned int deviceID, bool output);
	DBP_CPP_DLL unsigned short GetDeviceProductID(unsigned int deviceID, bool output);
	DBP_CPP_DLL unsigned char GetDeviceDriverMinorVersion(unsigned int deviceID, bool output);
	DBP_CPP_DLL unsigned char GetDeviceDriverMajorVersion(unsigned int deviceID, bool output);
	CPP_DLL char * GetDeviceName(unsigned int deviceID, bool output);

	DBP_CPP_DLL int GetDeviceFormatSupport(unsigned int deviceID, bool output, DWORD khz, WORD bits, WORD channels);
	DBP_CPP_DLL unsigned short GetDeviceMaxChannels(unsigned int deviceID, bool output);
	DBP_CPP_DLL int GetIndependentVolumeControlSupported(unsigned int outputDeviceID);
	DBP_CPP_DLL int GetVolumeControlSupported(unsigned int outputDeviceID);
	DBP_CPP_DLL int GetSampleAccurate(unsigned int outputDeviceID);
	DBP_CPP_DLL int GetPlaybackRateControlSupported(unsigned int outputDeviceID);
	DBP_CPP_DLL int GetPitchControlSupported(unsigned int outputDeviceID);

	DBP_CPP_DLL int StartSound(size_t numInputInstances, size_t numOutputInstances);
	DBP_CPP_DLL int FinishSound();
	DBP_CPP_DLL size_t GetNumInputInstances();
	DBP_CPP_DLL size_t GetNumOutputInstances();

	DBP_CPP_DLL __int64 CreateSoundProfile();
	DBP_CPP_DLL int DeleteSoundProfile(__int64 profile);
	DBP_CPP_DLL int SetSoundProfile(__int64 profile, DWORD khz, WORD bitsPerSample, WORD channels);
	DBP_CPP_DLL int SetSoundProfileHighQuality(__int64 profile);
	DBP_CPP_DLL int SetSoundProfileMediumQuality(__int64 profile);
	DBP_CPP_DLL int SetSoundProfileLowQuality(__int64 profile);
	DBP_CPP_DLL	WORD GetSoundProfileChannels(__int64 profile);
	DBP_CPP_DLL DWORD GetSoundProfileSamplesPerSecond(__int64 profile);
	DBP_CPP_DLL WORD GetSoundProfileBitsPerSample(__int64 profile);
	
	DBP_CPP_DLL int StartOutput(size_t instanceID, unsigned int outputDeviceID, size_t msStoredDataCap, size_t timeGapCap, __int64 soundFormat);
	DBP_CPP_DLL int FinishOutput(size_t instanceID);

	DBP_CPP_DLL int PlayData(size_t instanceID, __int64 packet);
	DBP_CPP_DLL int SetOutputSmoothValues(size_t instanceID, size_t MillisecondsOfStoredDataCap, size_t TimeSinceLastAddedCap);
	DBP_CPP_DLL int SetDataVolume(WORD bitsPerSample, __int64 dataPacket, double percentageChange);
	DBP_CPP_DLL int GetDataVolume(WORD bitsPerSample, __int64 dataPacket);

	DBP_CPP_DLL WORD GetOutputChannels(size_t instanceID);
	DBP_CPP_DLL DWORD GetOutputSamplesPerSec(size_t instanceID);
	DBP_CPP_DLL WORD GetOutputBitsPerSample(size_t instanceID);
	DBP_CPP_DLL size_t GetOutputStoredDataCap(size_t instanceID);
	DBP_CPP_DLL size_t GetOutputLastAddedCap(size_t instanceID);

	DBP_CPP_DLL double GetHardwarePlaybackRate(size_t instanceID);
	DBP_CPP_DLL double GetHardwarePitch(size_t instanceID);
	DBP_CPP_DLL unsigned short GetHardwareVolumeLeft(size_t instanceID);
	DBP_CPP_DLL unsigned short GetHardwareVolumeRight(size_t instanceID);
	DBP_CPP_DLL int SetHardwarePlaybackRate(size_t instanceID, double rate);
	DBP_CPP_DLL int SetHardwarePitch(size_t instanceID, double pitch);
	DBP_CPP_DLL int SetHardwareVolume(size_t instanceID, WORD left, WORD right);

	DBP_CPP_DLL int StartInput(size_t instanceID, unsigned int inputDeviceID, size_t numBuffers, size_t buffTimeLength, __int64 soundFormat);
	DBP_CPP_DLL int FinishInput(size_t instanceID);
	DBP_CPP_DLL int PauseInput(size_t instanceID);
	DBP_CPP_DLL int UnpauseInput(size_t instanceID);

	DBP_CPP_DLL size_t GetInputData(size_t instanceID, __int64 destination);
	DBP_CPP_DLL int GetInputUnpaused(size_t instanceID);
	DBP_CPP_DLL int GetInputPaused(size_t instanceID);

	DBP_CPP_DLL WORD GetInputChannels(size_t instanceID);
	DBP_CPP_DLL DWORD GetInputSamplesPerSec(size_t instanceID);
	DBP_CPP_DLL WORD GetInputBitsPerSample(size_t instanceID);
	DBP_CPP_DLL size_t GetInputNoBuffers(size_t instanceID);
	DBP_CPP_DLL size_t GetInputTimePerBuffer(size_t instanceID);

#ifdef DBP
	DBP_CPP_DLL DWORD DBP_GetDeviceName(DWORD pOldString, size_t DeviceID, bool Output);
#endif

#ifdef C_LINKAGE
	}
#endif

	int StartOutput(size_t instanceID, unsigned int outputDeviceID, size_t msStoredDataCap, size_t timeGapCap, const SoundFormat & soundFormat);
	int PlayData(size_t instanceID, const Packet & packet);
	int SetDataVolume(WORD bitsPerSample, Packet * packet, double percentageChange);
	int GetDataVolume(WORD bitsPerSample, const Packet * packet);
	int StartInput(size_t instanceID, unsigned int inputDeviceID, size_t numBuffers, size_t buffTimeLength, const SoundFormat & soundFormat);
	size_t GetInputData(size_t instanceID, Packet & destination);
};

