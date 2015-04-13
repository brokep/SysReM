
#include <unistd.h>
#include "ProcStat.h"
#include "ProcMan.h"
#include "StatGen.h"
#include <algorithm>
#include <memory>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>

ProcStat::ProcStat(){
}

ProcStat::~ProcStat(){
  this->clean();
}

//helper method to compare the two ProcMan objects
//pointed by two pointer
bool proc_comp(ProcMan *ptr1, ProcMan *ptr2);

void ProcStat::measure(){
   //find all pid dirs
    //store list of them then call readBefore on all
    //wait usleep
    //call read After on all
    //sort list
    //pick the top X, defined in statGen NUM_TOPPROC right now 
    //store those in m_top

    //clean up previous top procs
  this->clean();


  //hold all the current processes
  std::list<ProcMan*> m_procs;

  //pointer to the directory
  DIR *dirp = NULL;

  //pointer to the content of the directory
  struct dirent *dp = NULL;

  //open
  if ((dirp = opendir("/proc/")) == NULL) {
    std::cout << "opendir failed" << std::endl;
    return;
  }
  while ((dp = readdir(dirp)) != NULL) {
    char dname[128];
    strncpy(dname, (const char *)(dp->d_name), strlen(dp->d_name));
    dname[strlen(dp->d_name)] = '\0';
    //file representing processes are named 
    if (isdigit(dname[0])) {
      char dirname[32]= "/proc/";
      strncpy(dirname + 6, (const char *)dname, strlen(dname));
      dirname[6 + strlen(dname)] = '\0';
      std::string dir_str(dirname, dirname + 32);
      m_procs.push_back(new ProcMan(strtol(dname,nullptr,10)));
    }
  }

  //close the opened directory
  closedir(dirp);

  for (auto it = m_procs.begin(); it != m_procs.end(); ++it) {
    (*it)->readBefore();
  }

  usleep(1000*MEASURE_RES);

  for (auto it = m_procs.begin(); it != m_procs.end(); ++it) {
    (*it)->readAfter();
  }

  //sort the list of all current processes in ascending order
  m_procs.sort(proc_comp);

  //enter the NUM_TOPPROC most active processes' pointers to m_procs
  for (int i = 0; i < NUM_TOPPROC; ++i) {
    m_top.push_back(m_procs.back());
    m_procs.pop_back();
  }
}

std::string ProcStat::read(){
    //print on all in m_top, add all with title and return
  char b[200];
  sprintf(b, "%-15s%5s%20s%6s%6s\n", "Top processes", "pid", "Command",
	  "%cpu", "%mem");
  std::string ret(b);
  for (auto it = m_top.begin(); it != m_top.end(); ++it) {
    ret += (*it)->print();
  }
  return ret;
}

bool proc_comp(ProcMan *ptr1, ProcMan *ptr2) {
  return (*ptr1) < (*ptr2);
}

void ProcStat::clean() {
  std::for_each(m_top.begin(), m_top.end(), std::default_delete<ProcMan>());
  m_top.clear();
}
