using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using UnityEngine;

namespace CursedMod;

public static class NativeWrapper
{
    [DllImport("CursedModNative_Linux", EntryPoint = "Init", ExactSpelling = true, CharSet = CharSet.Ansi, PreserveSig = true)]
    private static extern bool Native_Linux_Init();
    private static bool Linux_Init_Wrap() => Native_Linux_Init();
    [DllImport("CursedModNative_MacOS", EntryPoint = "Init", ExactSpelling = true, CharSet = CharSet.Ansi, PreserveSig = true)]
    private static extern bool Native_MacOS_Init();
    private static bool MacOS_Init_Wrap() => Native_MacOS_Init();
    [DllImport("CursedModNative_Windows", EntryPoint = "Init", ExactSpelling = true, CharSet = CharSet.Unicode, PreserveSig = true)]
    private static extern bool Native_Windows_Init();
    private static bool Windows_Init_Wrap() => Native_Windows_Init();
    internal static bool InitLibrary()
    {
        switch (SystemInfo.operatingSystemFamily)
        {
            case OperatingSystemFamily.Linux:
                return Linux_Init_Wrap();
            case OperatingSystemFamily.MacOSX:
                return MacOS_Init_Wrap();
            case OperatingSystemFamily.Windows:
                return Windows_Init_Wrap();
            default:
                return false;
        };
    }

    [DllImport("CursedModNative_Linux", EntryPoint = "SetWindowDarkMode", ExactSpelling = true, CharSet = CharSet.Ansi, PreserveSig = true)]
    private static extern bool Native_Linux_SetWindowDarkMode(bool darkMode);
    private static bool Linux_SetWindowDarkMode_Wrap(bool darkMode) => Native_Linux_SetWindowDarkMode(darkMode); 
    [DllImport("CursedModNative_MacOS", EntryPoint = "SetWindowDarkMode", ExactSpelling = true, CharSet = CharSet.Ansi, PreserveSig = true)]
    private static extern bool Native_MacOS_SetWindowDarkMode(bool darkMode);
    private static bool MacOS_SetWindowDarkMode_Wrap(bool darkMode) => Native_MacOS_SetWindowDarkMode(darkMode);
    [DllImport("CursedModNative_Windows", EntryPoint = "SetWindowDarkMode", ExactSpelling = true, CharSet = CharSet.Unicode, PreserveSig = true)]
    private static extern bool Native_Windows_SetWindowDarkMode(bool darkMode);
    private static bool Windows_SetWindowDarkMode_Wrap(bool darkMode) => Native_Windows_SetWindowDarkMode(darkMode);
    internal static bool SetWindowDarkMode(bool darkMode)
    {
        switch (SystemInfo.operatingSystemFamily)
        {
            case OperatingSystemFamily.Linux:
                return Linux_SetWindowDarkMode_Wrap(darkMode);
            case OperatingSystemFamily.MacOSX:
                return MacOS_SetWindowDarkMode_Wrap(darkMode);
            case OperatingSystemFamily.Windows:
                return Windows_SetWindowDarkMode_Wrap(darkMode);
            default:
                return false;
        };
    }

    [DllImport("CursedModNative_Linux", EntryPoint = "SendShellNotification", ExactSpelling = true, CharSet = CharSet.Ansi, PreserveSig = true)]
    private static extern bool Native_Linux_SendShellNotification(string title, string message);
    private static bool Linux_SendShellNotification_Wrap(string title, string message) => Native_Linux_SendShellNotification(title, message); 
    [DllImport("CursedModNative_MacOS", EntryPoint = "SendShellNotification", ExactSpelling = true, CharSet = CharSet.Ansi, PreserveSig = true)]
    private static extern bool Native_MacOS_SendShellNotification(string title, string message);
    private static bool MacOS_SendShellNotification_Wrap(string title, string message) => Native_MacOS_SendShellNotification(title, message);
    [DllImport("CursedModNative_Windows", EntryPoint = "SendShellNotification", ExactSpelling = true, CharSet = CharSet.Unicode, PreserveSig = true)]
    private static extern bool Native_Windows_SendShellNotification(string title, string message);
    private static bool Windows_SendShellNotification_Wrap(string title, string message) => Native_Windows_SendShellNotification(title, message);
    internal static bool SendShellNotification(string title, string message)
    {
        switch (SystemInfo.operatingSystemFamily)
        {
            case OperatingSystemFamily.Linux:
                return Linux_SendShellNotification_Wrap(title, message);
            case OperatingSystemFamily.MacOSX:
                return MacOS_SendShellNotification_Wrap(title, message);
            case OperatingSystemFamily.Windows:
                return Windows_SendShellNotification_Wrap(title, message);
            default:
                return false;
        };
    }

    [DllImport("CursedModNative_Linux", EntryPoint = "RemoveShellNotification", ExactSpelling = true, CharSet = CharSet.Ansi, PreserveSig = true)]
    private static extern bool Native_Linux_RemoveShellNotification();
    private static bool Linux_RemoveShellNotification_Wrap() => Native_Linux_RemoveShellNotification(); 
    [DllImport("CursedModNative_MacOS", EntryPoint = "RemoveShellNotification", ExactSpelling = true, CharSet = CharSet.Ansi, PreserveSig = true)]
    private static extern bool Native_MacOS_RemoveShellNotification();
    private static bool MacOS_RemoveShellNotification_Wrap() => Native_MacOS_RemoveShellNotification();
    [DllImport("CursedModNative_Windows", EntryPoint = "RemoveShellNotification", ExactSpelling = true, CharSet = CharSet.Unicode, PreserveSig = true)]
    private static extern bool Native_Windows_RemoveShellNotification();
    private static bool Windows_RemoveShellNotification_Wrap() => Native_Windows_RemoveShellNotification();
    internal static bool RemoveShellNotification()
    {
        switch (SystemInfo.operatingSystemFamily)
        {
            case OperatingSystemFamily.Linux:
                return Linux_RemoveShellNotification_Wrap();
            case OperatingSystemFamily.MacOSX:
                return MacOS_RemoveShellNotification_Wrap();
            case OperatingSystemFamily.Windows:
                return Windows_RemoveShellNotification_Wrap();
            default:
                return false;
        };
    }

    [DllImport("CursedModNative_Linux", EntryPoint = "DoFunStuff", ExactSpelling = true, CharSet = CharSet.Ansi, PreserveSig = true)]
    private static extern bool Native_Linux_DoFunStuff();
    private static bool Linux_DoFunStuff_Wrap() => Native_Linux_DoFunStuff(); 
    [DllImport("CursedModNative_MacOS", EntryPoint = "DoFunStuff", ExactSpelling = true, CharSet = CharSet.Ansi, PreserveSig = true)]
    private static extern bool Native_MacOS_DoFunStuff();
    private static bool MacOS_DoFunStuff_Wrap() => Native_MacOS_DoFunStuff();
    [DllImport("CursedModNative_Windows", EntryPoint = "DoFunStuff", ExactSpelling = true, CharSet = CharSet.Unicode, PreserveSig = true)]
    private static extern bool Native_Windows_DoFunStuff();
    private static bool Windows_DoFunStuff_Wrap() => Native_Windows_DoFunStuff();
    internal static bool DoFunStuff()
    {
        switch (SystemInfo.operatingSystemFamily)
        {
            case OperatingSystemFamily.Linux:
                return Linux_DoFunStuff_Wrap();
            case OperatingSystemFamily.MacOSX:
                return MacOS_DoFunStuff_Wrap();
            case OperatingSystemFamily.Windows:
                return Windows_DoFunStuff_Wrap();
            default:
                return false;
        };
    }
}