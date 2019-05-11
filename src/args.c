#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/args.h"


const char *checkITDFile(const char *file){
  //parses filename until it reaches the dot of the extension
  const char *point = (strrchr(file,'.'));
  if(!point ||point == file){
    return "";
  }else{
    //returns whats after the dot, if it's "itd"
    return point + 1;
  }
}
