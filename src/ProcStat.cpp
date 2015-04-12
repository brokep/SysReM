
#include <unistd.h>
#include "ProcStat.h"
#include "ProcMan.h"
#include "StatGen.h"

ProcStat::ProcStat(){
}

ProcStat::~ProcStat(){
    //clean up m_top
}


void ProcStat::measure(){
   //find all pid dirs
    //store list of them then call readBefore on all
    //wait usleep
    //call read After on all
    //sort list
    //pick the top X, defined in statGen NUM_TOPPROC right now 
    //store those in m_top
  DIR *dirp = NULL;
  struct dirent *dp = NULL;
  if ((dirp = opendir("/proc/")) == NULL) {
    std::cout << "opendir failed" << std::endl;
  }
  while ((dirp = readdir_r(dirp)) != NULL) {
    char *dname;
    strncpy(dname, dirp->d_name, char_traits::length(dirp->d_name));
    if (isdigit(fname[0])) {
      
    }
  }



}

std::string ProcStat::read(){
    //print on all in m_top, add all with title and return 
    return "ProcStat reading\n";
}
