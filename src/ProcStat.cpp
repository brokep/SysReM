
#include <unistd.h>
#include "ProcStat.h"
#include "ProcMan.h"
#include "StatGen.h"
#include <algorithm>
#include <memory>
#include <iostream>
#include <string>
#include <cstring>

ProcStat::ProcStat(){
}

ProcStat::~ProcStat(){
    //clean up m_top
  std::for_each(m_top.begin(), m_top.end(), std::default_delete<ProcMan>());
  m_top.clear();
}

bool proc_comp(ProcMan *ptr1, ProcMan *ptr2);

void ProcStat::measure(){
   //find all pid dirs
    //store list of them then call readBefore on all
    //wait usleep
    //call read After on all
    //sort list
    //pick the top X, defined in statGen NUM_TOPPROC right now 
    //store those in m_top

  //hold all the current processes
  std::list<ProcMan*> m_procs;

  //pointer to the
  DIR *dirp = NULL;
  struct dirent *dp = NULL;

  //
  if ((dirp = opendir("/proc/")) == NULL) {
    std::cout << "opendir failed" << std::endl;
  }
  while ((dp = readdir(dirp)) != NULL) {
    char dname[128];
    strncpy(dname, (const char *)(dp->d_name), strlen(dp->d_name));
    if (isdigit(dname[0])) {
      char dirname[128]= "/proc/";
      strncpy(dirname, (const char *)dname, strlen(dname));
      m_procs.push_back(new ProcMan(dirname));
    }
  }

  for (auto it = m_procs.begin(); it != m_procs.end(); ++it) {
    (*it)->readBefore();
  }

  usleep(1000*MEASURE_RES);

  for (auto it = m_procs.begin(); it != m_procs.end(); ++it) {
    (*it)->readAfter();
  }

  m_procs.sort(proc_comp);

  for (int i = 0; i < NUM_TOPPROC; ++i) {
    m_top.push_back(m_procs.front());
    m_procs.pop_front();
  }
}

std::string ProcStat::read(){
    //print on all in m_top, add all with title and return
  char b[200];
  sprintf(b, "%-15s%5s%10s%6s%6s\n", "Top processes", "pid", "Command",
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
