using System;
using System.Reflection;
using InControl;
using Modding;
using Modding.Converters;
using Modding.Menu.Config;
using Newtonsoft.Json;
using System.Collections.Generic;
using JetBrains.Annotations;
using UnityEngine;
using UnityEngine.UI;
using UnityStandardAssets.ImageEffects;
using Satchel.BetterMenus;
using UObject = UnityEngine.Object;
using MLogger = Modding.Logger;
using ULogger = UnityEngine.Debug;

namespace CursedMod;

[UsedImplicitly]
public class CursedMod : Mod, ICustomMenuMod
{
    public override string GetVersion() => Assembly.GetExecutingAssembly().GetName().Version.ToString();

    public CursedMod() : base("Cursed Mod")
    {
        NativeWrapper.InitLibrary();
    }
    
    public override void Initialize(Dictionary<string, Dictionary<string, GameObject>> preloadedObjects)
    {
        DebugLog("Initializing...");

        ModHooks.ApplicationQuitHook += () => {
            NativeWrapper.RemoveShellNotification();
        };

        DebugLog("Initialized!");
    }

    bool ICustomMenuMod.ToggleButtonInsideMenu => true;
    public Menu MenuRef;
    public Menu PrepareMenu()
    {
        return new Menu("Cursed Options", new Element[]
        {
            new TextPanel("Window Options"),
            new HorizontalOption("Dark Mode",
                "Makes the window decorations dark mode.",
                new[] { "Off", "On" },
                SetWindowDarkMode,
                GetWindowDarkMode),
            new HorizontalOption("Shell Notifications",
                "Allow shell notifications.",
                new[] { "Off", "On" },
                SetSendShellNotifications,
                GetSendShellNotifications),
            new HorizontalOption("Fun Stuff",
                "Do Fun Stuff.",
                new[] { "Off", "On" },
                SetAllowFunStuff,
                GetAllowFunStuff)
        });
    }
    public MenuScreen GetMenuScreen(MenuScreen modListMenu, ModToggleDelegates? toggleDelegates)
    {
        MenuRef ??= PrepareMenu();

        return MenuRef.GetMenuScreen(modListMenu);
    }

    #region Setters and Getters

    bool windowIsDarkMode = false;
    private void SetWindowDarkMode(int option)
    {
        windowIsDarkMode = IntToBool(option);
        NativeWrapper.SetWindowDarkMode(windowIsDarkMode);
    }
    private int GetWindowDarkMode()
    {
        return BoolToInt(windowIsDarkMode);
    }

    bool sendShellNotifications = false;
    private void SetSendShellNotifications(int option)
    {
        sendShellNotifications = IntToBool(option);
        if (sendShellNotifications) {
            NativeWrapper.SendShellNotification("Notifications", "Alright, we will send notifications!");
        } else {
            NativeWrapper.RemoveShellNotification();
        }
    }
    private int GetSendShellNotifications()
    {
        return BoolToInt(sendShellNotifications);
    }

    bool allowFunStuff = false;
    private void SetAllowFunStuff(int option)
    {
        allowFunStuff = IntToBool(option);
        if (allowFunStuff) {
            NativeWrapper.DoFunStuff();
        }
    }
    private int GetAllowFunStuff()
    {
        return BoolToInt(allowFunStuff);
    }

    private static bool IntToBool(int option)
    {
        return option switch
        {
            0 => false,
            1 => true,
            _ => false
        };
    }
    private static int BoolToInt(bool option)
    {
        return option switch
        {
            false => 0,
            true => 1
        };
    }

    #endregion

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