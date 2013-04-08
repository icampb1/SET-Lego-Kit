///
///\file FileIO.cpp
///

#include "FileIO.h"


///
/// \brief <b>Brief Description</b> - This method is used to access errorLevel
///
/// \return This method returns errorLevel, an int that represents an error code
///

int FileIO::GetErrorLevel(){
    return errorLevel;
}

///
/// \brief <b>Brief Description</b> - This method is used to find the size of a file
/// \details <b>Details</b>
///
/// This method uses fseek and ftell to find the size of the file as a long
///
/// \return Returns errorLevel to show if any errors took place 
///

int FileIO::FileSize(char * path, long * fileSize){

    FILE * fp = NULL;
    
    if ((fp = fopen(path, "rb")) == NULL) {
        errorLevel = 2;
    }
    
    if (errorLevel == 0){
        //get the size of the file and then point it back to the start
        //bug!! will break if the nicknames.txt file is bigger then 2gbs
        fseek(fp, 0L, SEEK_END); // seek to the end of the file
        *fileSize = ftell(fp); // take the value
        fseek(fp, 0L, SEEK_SET); // return the file pointer to the start of the file
        fclose(fp);
    }
    
    return  errorLevel; // return the error condition 
}

///
/// \brief <b>Brief Description</b> - This method allows you to manipulate a file
/// \details <b>Details</b>
///
/// This method opens up a file and stores it into memory for manipulation
///
/// \return This method returns errorLevel to indicate if any errors occured.
///

int FileIO::SingleFileManip(char * path){
    
    FILE * fp = NULL;
    long fileSize = 0;
    unsigned char * inputBuffer = {0};
    int i = 0; // only include if you use a loop
    
    //get the size of the file that is about to be manipulated
    errorLevel = FileIO::FileSize(path, &fileSize);
    
    //open the file that you are working on
    if (errorLevel == 0){
        if ((fp = fopen(path, "rb" /* <---Remember to change this to your needs*/)) == NULL){
            errorLevel = 2;
        }
    }
    
    if (errorLevel == 0){
        if ((inputBuffer = (unsigned char*) malloc((fileSize + 1) * sizeof(unsigned char))) == NULL){
            //In case of malloc error, make sure you attempt to free up any resources you are using.
            errorLevel = 8;
            fclose(fp);
        }
        else if (errorLevel == 0){
            if (fread(inputBuffer, 1, fileSize, fp) == (unsigned int) fileSize){
                printf("You made it");// <------ replace this with your code
            }
            else {
                //In case of read error, make sure you attempt to free up any resources you are using.
                errorLevel = 4;
                free(inputBuffer);
                fclose(fp);
            }
        }
    }
    
    free(inputBuffer);
    fclose(fp);
    
    return errorLevel;
    
}

///
/// \brief <b>Brief Description</b> - This method allows you to copy a file
/// \details <b>Details</b>
///
/// This method opens up two file pointers and streams the contents of one into the other.
///
/// \return This method returns errorLevel to indicate if any errors occured.
///

int FileIO::FileCopy(char *origin, char *copy){
    FILE * fp = NULL;
    FILE * fpCopy = NULL;
    int  a = 0;
    
    // opens the old file
    if ((fp = fopen(origin, "rb")) != 0){
        errorLevel = 2;
    }
    
    // creates the new file at the specified path
    if ((fpCopy = fopen(copy, "wb")) != 0){
        fclose(fp);
        errorLevel = 2;
    }
    
    // does a character by character copy until it reaches the eof and then it breaks
    while(1){
        a  =  fgetc(fp);
        
        if (!feof(fp)){
            fputc(a, fpCopy);
        } else{
            break;
        }
    }
    // no error checking..... living on the edge :S
    fclose(fpCopy);
    fclose(fp);
    
    return errorLevel;
}

