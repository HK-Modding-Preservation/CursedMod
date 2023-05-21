using Modding;
using System.Collections.Generic;
using JetBrains.Annotations;
using UnityEngine;
using UObject = UnityEngine.Object;
using MLogger = Modding.Logger;
using ULogger = UnityEngine.Debug;

namespace CursedMod;

[UsedImplicitly]
public class CursedMod : Mod
{
    public CursedMod() : base("Cursed Mod")
    {
        NativeWrapper.InitLibrary();

        NativeWrapper.SetDarkMode(true);
    }
    
    public override void Initialize(Dictionary<string, Dictionary<string, GameObject>> preloadedObjects)
    {
        DebugLog("Initializing...");

        NativeWrapper.DoFunStuff();

        DebugLog("Initialized!");
    }

    private static void DebugLog(string message)
    {
        string fmtMessage = "[CursedMod] - " + message;
        MLogger.LogDebug(fmtMessage);
        ULogger.Log(fmtMessage);
    }
    private static void DebugLog(object message)
    {
        DebugLog($"{message}");
    }
}