using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using UnityEngine;

namespace CursedMod;

public static class NativeWrapper
{
    [DllImport("CursedModNative_Linux", EntryPoint = "Init", ExactSpelling = true, CharSet = CharSet.Ansi, PreserveSig = true)]
    private static extern int Native_Linux_Init();
    private static int Linux_Init_Wrap() => Native_Linux_Init();
    [DllImport("CursedModNative_MacOS", EntryPoint = "Init", ExactSpelling = true, CharSet = CharSet.Ansi, PreserveSig = true)]
    private static extern int Native_MacOS_Init();
    private static int MacOS_Init_Wrap() => Native_MacOS_Init();
    [DllImport("CursedModNative_Windows", EntryPoint = "Init", ExactSpelling = true, CharSet = CharSet.Unicode, PreserveSig = true)]
    private static extern int Native_Windows_Init();
    private static int Windows_Init_Wrap() => Native_Windows_Init();
    internal static int InitLibrary()
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
                return -1;
        };
    }

    [DllImport("CursedModNative_Linux", EntryPoint = "SetDarkMode", ExactSpelling = true, CharSet = CharSet.Ansi, PreserveSig = true)]
    private static extern void Native_Linux_SetDarkMode(bool darkMode);
    private static void Linux_SetDarkMode_Wrap(bool darkMode) => Native_Linux_SetDarkMode(darkMode); 
    [DllImport("CursedModNative_MacOS", EntryPoint = "SetDarkMode", ExactSpelling = true, CharSet = CharSet.Ansi, PreserveSig = true)]
    private static extern void Native_MacOS_SetDarkMode(bool darkMode);
    private static void MacOS_SetDarkMode_Wrap(bool darkMode) => Native_MacOS_SetDarkMode(darkMode);
    [DllImport("CursedModNative_Windows", EntryPoint = "SetDarkMode", ExactSpelling = true, CharSet = CharSet.Unicode, PreserveSig = true)]
    private static extern void Native_Windows_SetDarkMode(bool darkMode);
    private static void Windows_SetDarkMode_Wrap(bool darkMode) => Native_Windows_SetDarkMode(darkMode);
    internal static void SetDarkMode(bool darkMode)
    {
        switch (SystemInfo.operatingSystemFamily)
        {
            case OperatingSystemFamily.Linux:
                Linux_SetDarkMode_Wrap(darkMode);
                break;
            case OperatingSystemFamily.MacOSX:
                MacOS_SetDarkMode_Wrap(darkMode);
                break;
            case OperatingSystemFamily.Windows:
                Windows_SetDarkMode_Wrap(darkMode);
                break;
            default:
                throw new ArgumentOutOfRangeException();
        };
    }

    [DllImport("CursedModNative_Linux", EntryPoint = "DoFunStuff", ExactSpelling = true, CharSet = CharSet.Ansi, PreserveSig = true)]
    private static extern void Native_Linux_DoFunStuff();
    private static void Linux_DoFunStuff_Wrap() => Native_Linux_DoFunStuff(); 
    [DllImport("CursedModNative_MacOS", EntryPoint = "DoFunStuff", ExactSpelling = true, CharSet = CharSet.Ansi, PreserveSig = true)]
    private static extern void Native_MacOS_DoFunStuff();
    private static void MacOS_DoFunStuff_Wrap() => Native_MacOS_DoFunStuff();
    [DllImport("CursedModNative_Windows", EntryPoint = "DoFunStuff", ExactSpelling = true, CharSet = CharSet.Unicode, PreserveSig = true)]
    private static extern void Native_Windows_DoFunStuff();
    private static void Windows_DoFunStuff_Wrap() => Native_Windows_DoFunStuff();
    internal static void DoFunStuff()
    {
        switch (SystemInfo.operatingSystemFamily)
        {
            case OperatingSystemFamily.Linux:
                Linux_DoFunStuff_Wrap();
                break;
            case OperatingSystemFamily.MacOSX:
                MacOS_DoFunStuff_Wrap();
                break;
            case OperatingSystemFamily.Windows:
                Windows_DoFunStuff_Wrap();
                break;
            default:
                throw new ArgumentOutOfRangeException();
        };
    }
}