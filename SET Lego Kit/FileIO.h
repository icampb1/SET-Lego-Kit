///
/// \file FileIO.h
/// \class FileIO
///
/// \brief <b>Brief Description</b> - This class contains many method templates for manipulating files and directories.
/// \details <b>Details</b>
///
/// This class contains method templates that allow you to manipulate files and directories in both POSIX
/// and Windows(hopefully :-)).
///
/// \author <i>myName</i>
///


#ifndef __SET_Lego_Kit__FileIO__
#define __SET_Lego_Kit__FileIO__

#include <iostream>
#include <stdlib.h>
#include <string.h>
#if defined WIN32
#include <windows.h>
#elif defined _Unix
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

class FileIO{
private:
    int errorLevel;///<Holds a value based on any wrong doings
    
public:
    
    //constructor
    ///
	/// \brief <b>Brief Description</b> - This is the constructor
	/// \details <b>Details</b>
	///
    /// This constructor sets the initial value of errorLevel to 0.  It takes no parameters.
	///
	/// \return As this is a <i>constructor</i> Nothing is returned from the constuctor
	///
    
    FileIO(){
        errorLevel = 0;
    }
    
    //accessor
    int GetErrorLevel();
    
    //prototypes
    int FileSize(char * path, long * fileSize);
    int SingleFileManip(char * path);
    int FileCopy(char * origin, char * copy);
    //POSIX Prototypes
    #if defined _Unix
    int SearchDirectory(char * path);
    int CreateDirectory(char * path);
    int CopyDirectory(char * origin, char * copy);
    //Windows Prototypes
    #elif defined WIN32
    int SearchDirectory(char * path);
    int CreateDirectory(char * path);
    int CopyDirectory(char * origin, char * copy);
    #endif
};

#endif /* defined(__SET_Lego_Kit__FileIO__) */
