{
  "optionsFile": "options.json",
  "options": [],
  "exportToGame": true,
  "supportedTargets": -1,
  "extensionVersion": "1.2.0",
  "packageId": "",
  "productId": "",
  "author": "",
  "date": "2022-05-15T00:50:41.2406269+05:00",
  "license": "",
  "description": "",
  "helpfile": "",
  "iosProps": false,
  "tvosProps": false,
  "androidProps": false,
  "installdir": "",
  "files": [
    {"filename":"Par.dll","origname":"","init":"Par_DummyFunction","final":"Par_DummyFunction","kind":1,"uncompress":false,"functions":[
        {"externalName":"YYExtensionInitialise","kind":1,"help":"Par_YYExtensionInitialise(DONT,CALL)","hidden":false,"returnType":2,"argCount":0,"args":[
            1,
            2,
          ],"resourceVersion":"1.0","name":"Par_YYExtensionInitialise","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"Par_ScriptCallSetup","kind":1,"help":"Par_ScriptCallSetup(scriptExecuteMethod,callbackSelfStruct)","hidden":false,"returnType":2,"argCount":0,"args":[
            1,
            1,
          ],"resourceVersion":"1.0","name":"Par_ScriptCallSetup","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_Init","kind":1,"help":"ParInput_Init(bExplicitlyCallRunFrame)","hidden":false,"returnType":2,"argCount":0,"args":[
            2,
          ],"resourceVersion":"1.0","name":"ParInput_Init","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_Shutdown","kind":1,"help":"ParInput_Shutdown()","hidden":false,"returnType":2,"argCount":0,"args":[],"resourceVersion":"1.0","name":"ParInput_Shutdown","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_SetInputActionManifestFilePath","kind":1,"help":"ParInput_SetInputActionManifestFilePath(pchInputActionManifestAbsolutePath)","hidden":false,"returnType":2,"argCount":0,"args":[
            1,
          ],"resourceVersion":"1.0","name":"ParInput_SetInputActionManifestFilePath","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_RunFrame","kind":1,"help":"ParInput_RunFrame(bReservedValue=true)","hidden":false,"returnType":2,"argCount":0,"args":[
            2,
          ],"resourceVersion":"1.0","name":"ParInput_RunFrame","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_BWaitForData","kind":1,"help":"ParInput_BWaitForData(bWaitForever,unTimeout)","hidden":false,"returnType":2,"argCount":0,"args":[
            2,
            2,
          ],"resourceVersion":"1.0","name":"ParInput_BWaitForData","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_BNewDataAvailable","kind":1,"help":"ParInput_BNewDataAvailable()","hidden":false,"returnType":2,"argCount":0,"args":[],"resourceVersion":"1.0","name":"ParInput_BNewDataAvailable","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_GetConnectedControllers","kind":1,"help":"ParInput_GetConnectedControllers(handlesOut)","hidden":false,"returnType":2,"argCount":0,"args":[
            1,
          ],"resourceVersion":"1.0","name":"ParInput_GetConnectedControllers","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_EnableDeviceCallbacks","kind":1,"help":"ParInput_EnableDeviceCallbacks()","hidden":false,"returnType":2,"argCount":0,"args":[],"resourceVersion":"1.0","name":"ParInput_EnableDeviceCallbacks","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_EnableActionEventCallbacks","kind":1,"help":"_ParInput_EnableActionEventCallbacks(pCallback_SCRIPT_INDEX_ONLY_NOT_METHOD)","hidden":false,"returnType":2,"argCount":0,"args":[
            2,
          ],"resourceVersion":"1.0","name":"_ParInput_EnableActionEventCallbacks","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_GetActionSetHandle","kind":1,"help":"ParInput_GetActionSetHandle(pszActionSetName)","hidden":false,"returnType":2,"argCount":0,"args":[
            1,
          ],"resourceVersion":"1.0","name":"ParInput_GetActionSetHandle","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_ActivateActionSet","kind":1,"help":"ParInput_ActivateActionSet(inputHandle,actionSetHandle)","hidden":false,"returnType":2,"argCount":0,"args":[
            2,
            2,
          ],"resourceVersion":"1.0","name":"ParInput_ActivateActionSet","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_GetCurrentActionSet","kind":1,"help":"ParInput_GetCurrentActionSet(inputHandle)","hidden":false,"returnType":2,"argCount":0,"args":[
            2,
          ],"resourceVersion":"1.0","name":"ParInput_GetCurrentActionSet","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_ActivateActionSetLayer","kind":1,"help":"ParInput_ActivateActionSetLayer(inputHandle,actionSetLayerHandle)","hidden":false,"returnType":2,"argCount":0,"args":[
            2,
            2,
          ],"resourceVersion":"1.0","name":"ParInput_ActivateActionSetLayer","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_DeactivateActionSetLayer","kind":1,"help":"ParInput_DeactivateActionSetLayer(inputHandle,actionSetLayerHandle)","hidden":false,"returnType":2,"argCount":0,"args":[
            2,
            2,
          ],"resourceVersion":"1.0","name":"ParInput_DeactivateActionSetLayer","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_DeactivateAllActionSetLayers","kind":1,"help":"ParInput_DeactivateAllActionSetLayers(inputHandle)","hidden":false,"returnType":2,"argCount":0,"args":[
            2,
          ],"resourceVersion":"1.0","name":"ParInput_DeactivateAllActionSetLayers","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_GetActiveActionSetLayers","kind":1,"help":"ParInput_GetActiveActionSetLayers(inputHandle,handlesOut)","hidden":false,"returnType":2,"argCount":0,"args":[
            2,
            1,
          ],"resourceVersion":"1.0","name":"ParInput_GetActiveActionSetLayers","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_GetDigitalActionHandle","kind":1,"help":"ParInput_GetDigitalActionHandle(pszActionName)","hidden":false,"returnType":2,"argCount":0,"args":[
            1,
          ],"resourceVersion":"1.0","name":"ParInput_GetDigitalActionHandle","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_GetDigitalActionData","kind":1,"help":"ParInput_GetDigitalActionData(inputHandle,digitalActionHandle)","hidden":false,"returnType":1,"argCount":0,"args":[
            2,
            2,
          ],"resourceVersion":"1.0","name":"ParInput_GetDigitalActionData","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_GetDigitalActionOrigins","kind":1,"help":"ParInput_GetDigitalActionOrigins(inputHandle,actionSetHandle,digitalActionHandle,originsOut)","hidden":false,"returnType":2,"argCount":0,"args":[
            2,
            2,
            2,
            1,
          ],"resourceVersion":"1.0","name":"ParInput_GetDigitalActionOrigins","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_GetStringForDigitalActionName","kind":1,"help":"ParInput_GetStringForDigitalActionName(eActionHandle)","hidden":false,"returnType":1,"argCount":0,"args":[
            2,
          ],"resourceVersion":"1.0","name":"ParInput_GetStringForDigitalActionName","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_GetAnalogActionHandle","kind":1,"help":"ParInput_GetAnalogActionHandle(pszActionName)","hidden":false,"returnType":2,"argCount":0,"args":[
            1,
          ],"resourceVersion":"1.0","name":"ParInput_GetAnalogActionHandle","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_GetAnalogActionData","kind":1,"help":"ParInput_GetAnalogActionData(inputHandle,analogActionHandle)","hidden":false,"returnType":1,"argCount":0,"args":[
            2,
            2,
          ],"resourceVersion":"1.0","name":"ParInput_GetAnalogActionData","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_GetAnalogActionOrigins","kind":1,"help":"ParInput_GetAnalogActionOrigins(inputHandle,actionSetHandle,analogActionHandle,originsOut)","hidden":false,"returnType":2,"argCount":0,"args":[
            2,
            2,
            2,
            1,
          ],"resourceVersion":"1.0","name":"ParInput_GetAnalogActionOrigins","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_GetGlyphPNGForActionOrigin","kind":1,"help":"ParInput_GetGlyphPNGForActionOrigin(eOrigin,eSize,unFlags)","hidden":false,"returnType":1,"argCount":0,"args":[
            2,
            2,
            2,
          ],"resourceVersion":"1.0","name":"ParInput_GetGlyphPNGForActionOrigin","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_GetGlyphSVGForActionOrigin","kind":1,"help":"ParInput_GetGlyphSVGForActionOrigin(eOrigin,unFlags)","hidden":false,"returnType":1,"argCount":0,"args":[
            2,
            2,
          ],"resourceVersion":"1.0","name":"ParInput_GetGlyphSVGForActionOrigin","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_GetGlyphForActionOrigin_Legacy","kind":1,"help":"ParInput_GetGlyphForActionOrigin_Legacy(eOrigin)","hidden":false,"returnType":1,"argCount":0,"args":[
            2,
          ],"resourceVersion":"1.0","name":"ParInput_GetGlyphForActionOrigin_Legacy","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_GetStringForActionOrigin","kind":1,"help":"ParInput_GetStringForActionOrigin(eOrigin)","hidden":false,"returnType":1,"argCount":0,"args":[
            2,
          ],"resourceVersion":"1.0","name":"ParInput_GetStringForActionOrigin","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_GetStringForAnalogActionName","kind":1,"help":"ParInput_GetStringForAnalogActionName(eActionHandle)","hidden":false,"returnType":1,"argCount":0,"args":[
            2,
          ],"resourceVersion":"1.0","name":"ParInput_GetStringForAnalogActionName","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_StopAnalogActionMomentum","kind":1,"help":"ParInput_StopAnalogActionMomentum(inputHandle,eAction)","hidden":false,"returnType":2,"argCount":0,"args":[
            2,
            2,
          ],"resourceVersion":"1.0","name":"ParInput_StopAnalogActionMomentum","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_GetMotionData","kind":1,"help":"ParInput_GetMotionData(inputHandle)","hidden":false,"returnType":1,"argCount":0,"args":[
            2,
          ],"resourceVersion":"1.0","name":"ParInput_GetMotionData","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_TriggerVibration","kind":1,"help":"ParInput_TriggerVibration(inputHandle,usLeftSpeed,usRightSpeed)","hidden":false,"returnType":2,"argCount":0,"args":[
            2,
            2,
            2,
          ],"resourceVersion":"1.0","name":"ParInput_TriggerVibration","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_TriggerVibrationExtended","kind":1,"help":"ParInput_TriggerVibrationExtended(inputHandle,usLeftSpeed,usRightSpeed,usLeftTriggerSpeed,usRightTriggerSpeed)","hidden":false,"returnType":2,"argCount":0,"args":[
            2,
            2,
            2,
            2,
            2,
          ],"resourceVersion":"1.0","name":"ParInput_TriggerVibrationExtended","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_TriggerSimpleHapticEvent","kind":1,"help":"ParInput_TriggerSimpleHapticEvent(inputHandle,eHapticLocation,nIntensity,nGainDB,nOtherIntensity,nOtherGainDB)","hidden":false,"returnType":2,"argCount":0,"args":[
            2,
            2,
            2,
            2,
            2,
            2,
          ],"resourceVersion":"1.0","name":"ParInput_TriggerSimpleHapticEvent","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_SetLEDColor","kind":1,"help":"ParInput_SetLEDColor(inputHandle,nColorR,nColorG,nColorB,nFlags)","hidden":false,"returnType":2,"argCount":0,"args":[
            2,
            2,
            2,
            2,
            2,
          ],"resourceVersion":"1.0","name":"ParInput_SetLEDColor","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_Legacy_TriggerHapticPulse","kind":1,"help":"ParInput_Legacy_TriggerHapticPulse(inputHandle,eTargetPad,usDurationMicroSec)","hidden":false,"returnType":2,"argCount":0,"args":[
            2,
            2,
            2,
          ],"resourceVersion":"1.0","name":"ParInput_Legacy_TriggerHapticPulse","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_Legacy_TriggerRepeatedHapticPulse","kind":1,"help":"ParInput_Legacy_TriggerRepeatedHapticPulse(inputHandle,eTargetPad,usDurationMicroSec,usOffMicroSec,unRepeat,nFlags)","hidden":false,"returnType":2,"argCount":0,"args":[
            2,
            2,
            2,
            2,
            2,
            2,
          ],"resourceVersion":"1.0","name":"ParInput_Legacy_TriggerRepeatedHapticPulse","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_ShowBindingPanel","kind":1,"help":"ParInput_ShowBindingPanel(inputHandle)","hidden":false,"returnType":2,"argCount":0,"args":[
            2,
          ],"resourceVersion":"1.0","name":"ParInput_ShowBindingPanel","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_GetInputTypeForHandle","kind":1,"help":"ParInput_GetInputTypeForHandle(inputHandle)","hidden":false,"returnType":2,"argCount":0,"args":[
            2,
          ],"resourceVersion":"1.0","name":"ParInput_GetInputTypeForHandle","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_GetControllerForGamepadIndex","kind":1,"help":"ParInput_GetControllerForGamepadIndex(nIndex)","hidden":false,"returnType":2,"argCount":0,"args":[
            2,
          ],"resourceVersion":"1.0","name":"ParInput_GetControllerForGamepadIndex","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_GetGamepadIndexForController","kind":1,"help":"ParInput_GetGamepadIndexForController(ulinputHandle)","hidden":false,"returnType":2,"argCount":0,"args":[
            2,
          ],"resourceVersion":"1.0","name":"ParInput_GetGamepadIndexForController","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_GetStringForXboxOrigin","kind":1,"help":"ParInput_GetStringForXboxOrigin(eOrigin)","hidden":false,"returnType":1,"argCount":0,"args":[
            2,
          ],"resourceVersion":"1.0","name":"ParInput_GetStringForXboxOrigin","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_GetGlyphForXboxOrigin","kind":1,"help":"ParInput_GetGlyphForXboxOrigin(eOrigin)","hidden":false,"returnType":1,"argCount":0,"args":[
            2,
          ],"resourceVersion":"1.0","name":"ParInput_GetGlyphForXboxOrigin","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_GetActionOriginFromXboxOrigin","kind":1,"help":"ParInput_GetActionOriginFromXboxOrigin(inputHandle,eOrigin)","hidden":false,"returnType":2,"argCount":0,"args":[
            2,
            2,
          ],"resourceVersion":"1.0","name":"ParInput_GetActionOriginFromXboxOrigin","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_TranslateActionOrigin","kind":1,"help":"ParInput_TranslateActionOrigin(eDestinationInputType,eSourceOrigin)","hidden":false,"returnType":2,"argCount":0,"args":[
            2,
            2,
          ],"resourceVersion":"1.0","name":"ParInput_TranslateActionOrigin","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_GetDeviceBindingRevision","kind":1,"help":"ParInput_GetDeviceBindingRevision(inputHandle,pMajor,pMinor)","hidden":false,"returnType":2,"argCount":0,"args":[
            2,
            1,
            1,
          ],"resourceVersion":"1.0","name":"ParInput_GetDeviceBindingRevision","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_GetRemotePlaySessionID","kind":1,"help":"ParInput_GetRemotePlaySessionID(inputHandle)","hidden":false,"returnType":2,"argCount":0,"args":[
            2,
          ],"resourceVersion":"1.0","name":"ParInput_GetRemotePlaySessionID","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParInput_GetSessionInputConfigurationSettings","kind":1,"help":"ParInput_GetSessionInputConfigurationSettings()","hidden":false,"returnType":2,"argCount":0,"args":[],"resourceVersion":"1.0","name":"ParInput_GetSessionInputConfigurationSettings","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParRemoteStorage_BeginFileWriteBatch","kind":1,"help":"ParRemoteStorage_BeginFileWriteBatch()","hidden":false,"returnType":2,"argCount":0,"args":[],"resourceVersion":"1.0","name":"ParRemoteStorage_BeginFileWriteBatch","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParRemoteStorage_EndFileWriteBatch","kind":1,"help":"ParRemoteStorage_EndFileWriteBatch()","hidden":false,"returnType":2,"argCount":0,"args":[],"resourceVersion":"1.0","name":"ParRemoteStorage_EndFileWriteBatch","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParUtils_IsSteamRunningOnSteamDeck","kind":1,"help":"ParUtils_IsSteamRunningOnSteamDeck()","hidden":false,"returnType":2,"argCount":0,"args":[],"resourceVersion":"1.0","name":"ParUtils_IsSteamRunningOnSteamDeck","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParUtils_ShowFloatingGamepadTextInput","kind":1,"help":"ParUtils_ShowFloatingGamepadTextInput(eKeyboardMode,nTextFieldXPosition,nTextFieldYPosition,nTextFieldWidth,nTextFieldHeight)","hidden":false,"returnType":2,"argCount":0,"args":[
            2,
            2,
            2,
            2,
            2,
          ],"resourceVersion":"1.0","name":"ParUtils_ShowFloatingGamepadTextInput","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParUtils_SetGameLauncherMode","kind":1,"help":"ParUtils_SetGameLauncherMode(bLauncherMode)","hidden":false,"returnType":2,"argCount":0,"args":[
            2,
          ],"resourceVersion":"1.0","name":"ParUtils_SetGameLauncherMode","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParUtils_DismissFloatingGamepadTextInput","kind":1,"help":"ParUtils_DismissFloatingGamepadTextInput()","hidden":false,"returnType":2,"argCount":0,"args":[],"resourceVersion":"1.0","name":"ParUtils_DismissFloatingGamepadTextInput","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParUtils_GetIPv6ConnectivityState","kind":1,"help":"ParUtils_GetIPv6ConnectivityState(eProtocol)","hidden":false,"returnType":2,"argCount":0,"args":[
            2,
          ],"resourceVersion":"1.0","name":"ParUtils_GetIPv6ConnectivityState","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParUtils_FilterText","kind":1,"help":"ParUtils_FilterText(eContext,sourceSteamID,pchInputMessage,pchOutFilteredText,nByteSizeOutFilteredText)","hidden":false,"returnType":2,"argCount":0,"args":[
            2,
            2,
            2,
            2,
            2,
          ],"resourceVersion":"1.0","name":"ParUtils_FilterText","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParUtils_InitFilterText","kind":1,"help":"ParUtils_InitFilterText(unFilterOptions=0)","hidden":false,"returnType":2,"argCount":0,"args":[
            2,
          ],"resourceVersion":"1.0","name":"ParUtils_InitFilterText","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParUtils_IsSteamChinaLauncher","kind":1,"help":"ParUtils_IsSteamChinaLauncher()","hidden":false,"returnType":2,"argCount":0,"args":[],"resourceVersion":"1.0","name":"ParUtils_IsSteamChinaLauncher","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParUtils_SetVRHeadsetStreamingEnabled","kind":1,"help":"ParUtils_SetVRHeadsetStreamingEnabled(bEnabled)","hidden":false,"returnType":2,"argCount":0,"args":[
            2,
          ],"resourceVersion":"1.0","name":"ParUtils_SetVRHeadsetStreamingEnabled","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParUtils_IsVRHeadsetStreamingEnabled","kind":1,"help":"ParUtils_IsVRHeadsetStreamingEnabled()","hidden":false,"returnType":2,"argCount":0,"args":[],"resourceVersion":"1.0","name":"ParUtils_IsVRHeadsetStreamingEnabled","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParUtils_StartVRDashboard","kind":1,"help":"ParUtils_StartVRDashboard()","hidden":false,"returnType":2,"argCount":0,"args":[],"resourceVersion":"1.0","name":"ParUtils_StartVRDashboard","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParUtils_IsSteamInBigPictureMode","kind":1,"help":"ParUtils_IsSteamInBigPictureMode()","hidden":false,"returnType":2,"argCount":0,"args":[],"resourceVersion":"1.0","name":"ParUtils_IsSteamInBigPictureMode","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParUtils_SetOverlayNotificationInset","kind":1,"help":"ParUtils_SetOverlayNotificationInset(nHorizontalInset,nVerticalInset)","hidden":false,"returnType":2,"argCount":0,"args":[
            2,
            2,
          ],"resourceVersion":"1.0","name":"ParUtils_SetOverlayNotificationInset","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParUtils_IsSteamRunningInVR","kind":1,"help":"ParUtils_IsSteamRunningInVR()","hidden":false,"returnType":2,"argCount":0,"args":[],"resourceVersion":"1.0","name":"ParUtils_IsSteamRunningInVR","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParUtils_GetSteamUILanguage","kind":1,"help":"ParUtils_GetSteamUILanguage()","hidden":false,"returnType":2,"argCount":0,"args":[],"resourceVersion":"1.0","name":"ParUtils_GetSteamUILanguage","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParUtils_GetEnteredGamepadTextInput","kind":1,"help":"ParUtils_GetEnteredGamepadTextInput(pchText,cchText)","hidden":false,"returnType":2,"argCount":0,"args":[
            1,
            2,
          ],"resourceVersion":"1.0","name":"ParUtils_GetEnteredGamepadTextInput","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParUtils_GetEnteredGamepadTextLength","kind":1,"help":"ParUtils_GetEnteredGamepadTextLength()","hidden":false,"returnType":2,"argCount":0,"args":[],"resourceVersion":"1.0","name":"ParUtils_GetEnteredGamepadTextLength","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParUtils_ShowGamepadTextInput","kind":1,"help":"ParUtils_ShowGamepadTextInput(eInputMode,eLineInputMode,pchDescription,unCharMax,pchExistingText)","hidden":false,"returnType":2,"argCount":0,"args":[
            2,
            2,
            2,
            2,
            2,
          ],"resourceVersion":"1.0","name":"ParUtils_ShowGamepadTextInput","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"Par_DummyFunction","kind":1,"help":"Par_DummyFunction()","hidden":false,"returnType":2,"argCount":0,"args":[],"resourceVersion":"1.0","name":"Par_DummyFunction","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParRemoteStorage_GetLocalFileChangeCount","kind":1,"help":"ParRemoteStorage_GetLocalFileChangeCount()","hidden":false,"returnType":2,"argCount":0,"args":[],"resourceVersion":"1.0","name":"ParRemoteStorage_GetLocalFileChangeCount","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"ParRemoteStorage_GetLocalFileChange","kind":1,"help":"ParRemoteStorage_GetLocalFileChange(iFile,pEChangeType,pEFilePathType)","hidden":false,"returnType":1,"argCount":0,"args":[
            2,
            1,
            1,
          ],"resourceVersion":"1.0","name":"ParRemoteStorage_GetLocalFileChange","tags":[],"resourceType":"GMExtensionFunction",},
      ],"constants":[],"ProxyFiles":[
        {"TargetMask":6,"resourceVersion":"1.0","name":"Par_x64.dll","tags":[],"resourceType":"GMProxyFile",},
        {"TargetMask":7,"resourceVersion":"1.0","name":"libPar_linux.so","tags":[],"resourceType":"GMProxyFile",},
        {"TargetMask":1,"resourceVersion":"1.0","name":"libPar.dylib","tags":[],"resourceType":"GMProxyFile",},
      ],"copyToTargets":194,"order":[
        {"name":"Par_YYExtensionInitialise","path":"extensions/Par/Par.yy",},
        {"name":"Par_ScriptCallSetup","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_Init","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_Shutdown","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_SetInputActionManifestFilePath","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_RunFrame","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_BWaitForData","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_BNewDataAvailable","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_GetConnectedControllers","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_EnableDeviceCallbacks","path":"extensions/Par/Par.yy",},
        {"name":"_ParInput_EnableActionEventCallbacks","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_GetActionSetHandle","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_ActivateActionSet","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_GetCurrentActionSet","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_ActivateActionSetLayer","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_DeactivateActionSetLayer","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_DeactivateAllActionSetLayers","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_GetActiveActionSetLayers","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_GetDigitalActionHandle","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_GetDigitalActionData","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_GetDigitalActionOrigins","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_GetStringForDigitalActionName","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_GetAnalogActionHandle","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_GetAnalogActionData","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_GetAnalogActionOrigins","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_GetGlyphPNGForActionOrigin","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_GetGlyphSVGForActionOrigin","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_GetGlyphForActionOrigin_Legacy","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_GetStringForActionOrigin","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_GetStringForAnalogActionName","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_StopAnalogActionMomentum","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_GetMotionData","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_TriggerVibration","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_TriggerVibrationExtended","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_TriggerSimpleHapticEvent","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_SetLEDColor","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_Legacy_TriggerHapticPulse","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_Legacy_TriggerRepeatedHapticPulse","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_ShowBindingPanel","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_GetInputTypeForHandle","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_GetControllerForGamepadIndex","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_GetGamepadIndexForController","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_GetStringForXboxOrigin","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_GetGlyphForXboxOrigin","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_GetActionOriginFromXboxOrigin","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_TranslateActionOrigin","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_GetDeviceBindingRevision","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_GetRemotePlaySessionID","path":"extensions/Par/Par.yy",},
        {"name":"ParInput_GetSessionInputConfigurationSettings","path":"extensions/Par/Par.yy",},
        {"name":"ParRemoteStorage_BeginFileWriteBatch","path":"extensions/Par/Par.yy",},
        {"name":"ParRemoteStorage_EndFileWriteBatch","path":"extensions/Par/Par.yy",},
        {"name":"ParUtils_IsSteamRunningOnSteamDeck","path":"extensions/Par/Par.yy",},
        {"name":"ParUtils_ShowFloatingGamepadTextInput","path":"extensions/Par/Par.yy",},
        {"name":"ParUtils_SetGameLauncherMode","path":"extensions/Par/Par.yy",},
        {"name":"ParUtils_DismissFloatingGamepadTextInput","path":"extensions/Par/Par.yy",},
        {"name":"ParUtils_GetIPv6ConnectivityState","path":"extensions/Par/Par.yy",},
        {"name":"ParUtils_FilterText","path":"extensions/Par/Par.yy",},
        {"name":"ParUtils_InitFilterText","path":"extensions/Par/Par.yy",},
        {"name":"ParUtils_IsSteamChinaLauncher","path":"extensions/Par/Par.yy",},
        {"name":"ParUtils_SetVRHeadsetStreamingEnabled","path":"extensions/Par/Par.yy",},
        {"name":"ParUtils_IsVRHeadsetStreamingEnabled","path":"extensions/Par/Par.yy",},
        {"name":"ParUtils_StartVRDashboard","path":"extensions/Par/Par.yy",},
        {"name":"ParUtils_IsSteamInBigPictureMode","path":"extensions/Par/Par.yy",},
        {"name":"ParUtils_SetOverlayNotificationInset","path":"extensions/Par/Par.yy",},
        {"name":"ParUtils_IsSteamRunningInVR","path":"extensions/Par/Par.yy",},
        {"name":"ParUtils_GetSteamUILanguage","path":"extensions/Par/Par.yy",},
        {"name":"ParUtils_GetEnteredGamepadTextInput","path":"extensions/Par/Par.yy",},
        {"name":"ParUtils_GetEnteredGamepadTextLength","path":"extensions/Par/Par.yy",},
        {"name":"ParUtils_ShowGamepadTextInput","path":"extensions/Par/Par.yy",},
        {"name":"Par_DummyFunction","path":"extensions/Par/Par.yy",},
        {"name":"ParRemoteStorage_GetLocalFileChangeCount","path":"extensions/Par/Par.yy",},
        {"name":"ParRemoteStorage_GetLocalFileChange","path":"extensions/Par/Par.yy",},
      ],"resourceVersion":"1.0","name":"","tags":[],"resourceType":"GMExtensionFile",},
  ],
  "classname": "",
  "tvosclassname": null,
  "tvosdelegatename": null,
  "iosdelegatename": "",
  "androidclassname": "",
  "sourcedir": "",
  "androidsourcedir": "",
  "macsourcedir": "",
  "maccompilerflags": "",
  "tvosmaccompilerflags": "",
  "maclinkerflags": "",
  "tvosmaclinkerflags": "",
  "iosplistinject": "",
  "tvosplistinject": "",
  "androidinject": "",
  "androidmanifestinject": "",
  "androidactivityinject": "",
  "gradleinject": "",
  "androidcodeinjection": "",
  "hasConvertedCodeInjection": true,
  "ioscodeinjection": "",
  "tvoscodeinjection": "",
  "iosSystemFrameworkEntries": [],
  "tvosSystemFrameworkEntries": [],
  "iosThirdPartyFrameworkEntries": [],
  "tvosThirdPartyFrameworkEntries": [],
  "IncludedResources": [],
  "androidPermissions": [],
  "copyToTargets": 194,
  "iosCocoaPods": "",
  "tvosCocoaPods": "",
  "iosCocoaPodDependencies": "",
  "tvosCocoaPodDependencies": "",
  "parent": {
    "name": "Parworks itself",
    "path": "folders/Parworks itself.yy",
  },
  "resourceVersion": "1.2",
  "name": "Par",
  "tags": [],
  "resourceType": "GMExtension",
}