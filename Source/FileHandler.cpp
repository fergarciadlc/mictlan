/*
  ==============================================================================

    FileHandler.cpp
    Created: 23 May 2022 1:18:45am
    Author:  Fernando

  ==============================================================================
*/

#include "FileHandler.h"

FileHandler::FileHandler() 
{
    #if JUCE_WINDOWS
        systemSeparator = "\\";
    #elif JUCE_MAC
        systemSeparator = "/";
    #endif
}

FileHandler::~FileHandler() {}

juce::File FileHandler::getIRFolder()
{
    DBG("********************* userMusicDirectory   *******************************");
    juce::File start = juce::File::getSpecialLocation(juce::File::userMusicDirectory);
    DBG(start.getFullPathName());
    //while (start.exists() && !start.isRoot() && start.getFileName() != "Builds")
    //    start = start.getParentDirectory();
    //if (start.getFileName() != "Builds") { DBG("Some error handling..."); };
    //juce::File ImpulseResponseFolder = start.getSiblingFile("IR");
    juce::File ImpulseResponseFolder = start.getChildFile("IR");

    DBG("*****************IR FOLDER*************************");
    DBG(ImpulseResponseFolder.getFullPathName());

    return ImpulseResponseFolder;
}

juce::File FileHandler::getIRFromIRFolder(juce::String IRFileName)
{
    DBG("****************************************************************");
    DBG("******************IR FILE NAME FULL PATH************************");
    DBG(getIRFolder().getChildFile(IRFileName).getFullPathName());
    return getIRFolder().getChildFile(IRFileName);
}