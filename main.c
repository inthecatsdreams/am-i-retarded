#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
 
PSP_MODULE_INFO("am-i-retarded", 0, 1, 0);
 
int exit_callback(int arg1, int arg2, void* common){
	sceKernelExitGame();
	return 0;
}
 
int CallbackThread(SceSize args, void* argp) {
	int cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);
	sceKernelSleepThreadCB();
 
	return 0;
}
 
int SetupCallbacks(void) {
	int thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
	if (thid >= 0) {
		sceKernelStartThread(thid, 0, 0);
	}
	return thid;
}
int main() { 
	SetupCallbacks();
	pspDebugScreenInit();
 
    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
 
    struct SceCtrlData padData;
    pspDebugScreenPrintf("Press X if you're a male\nPress O if you're a female\nPress /\\ if none of the above fits your gender\n");
    while(1){
        sceCtrlReadBufferPositive(&padData,1);
 
        if(padData.Buttons & PSP_CTRL_CROSS){
            pspDebugScreenPrintf("X Pressed! You're a male!\n");
        }
        else if (padData.Buttons & PSP_CTRL_CIRCLE){
            pspDebugScreenPrintf("O Pressed! You're a female!\n");
            
        }
        else if (padData.Buttons & PSP_CTRL_TRIANGLE){
            pspDebugScreenPrintf("Triangle Pressed! You're a retard!\n");
            
        }

    }
 
        return 0;
}
