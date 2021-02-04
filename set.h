#pragma once

#ifndef __SET_H_INCLUDED
#define __SET_H_INCLUDED

#include <iostream>

#include "defs.h"

// Set representation type
class set_t {
  class set_list_t;
  friend std::ostream & operator<<(std::ostream &oStream, const set_t::set_list_t &el);
  friend std::ostream & operator<<(std::ostream &oStream, const set_t &set);

private:
  // List of sets representation type
  class set_list_t {
  public:
    set_list_t *next;
    char str[def::maxCharSeq];

    set_list_t(set_list_t *nextEl, const char el[]);
  };

  set_list_t *set;
  int cardinality;

public:
  set_t(void);
  set_t(const set_t &s);
  ~set_t(void);
  set_t & operator=(const set_t &s);

  int GetCardinality(void) const noexcept;
  void Add(const char el[]);
  void Delete(const char el[]);
  bool Find(const char el[]) const noexcept;

  set_t Union(const set_t &s) const;
  set_t Intersection(const set_t &s) const;
  set_t Difference(const set_t &s) const;
  set_t SymDifference(const set_t &s) const;
  bool IsSubset(const set_t &s) const;
};

std::ostream & operator<<(std::ostream &oStream, const set_t &set);

#endif
