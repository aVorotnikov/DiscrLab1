#pragma once

#ifndef __MANAGER_H_INCLUDED
#define __MANAGER_H_INCLUDED

#include <map>

#include "set.h"

// Sets and comand manager representation type
class manager_t {
  friend std::ostream & operator<<(std::ostream &oStream, const manager_t &m);
private:
  std::map<int, set_t> sets;

public:
  manager_t(void);
  void Session(void);
};

#endif
