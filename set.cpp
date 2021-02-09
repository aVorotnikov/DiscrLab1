#include <exception>
#include <cstring>

#include "set.h"

set_t::set_list_t::set_list_t(set_list_t *nextEl, const char el[]) : next(nextEl) {
  int i = 0;

  do {
    str[i] = el[i];
    i++;
  } while (el[i] != 0 && i < def::maxCharSeq);
  if (i == def::maxCharSeq)
    throw std::exception("String is more than 80 symbols");
}

set_t::set_t(void) : set(nullptr), cardinality(0) {
}

set_t::set_t(const set_t &s) : cardinality(s.cardinality) {
  set_list_t *elS = s.set, *el = set = new set_list_t(nullptr, "");

  while (elS != nullptr) {
    el = el->next = new set_list_t(nullptr, elS->str);
    elS = elS->next;
  }
  el = set;
  set = set->next;
  delete el;
}

set_t::~set_t(void) {
  set_list_t *cur = set, *tmp;

  while (cur != nullptr) {
    tmp = cur->next;
    delete cur;
    cur = tmp;
  }
}

set_t & set_t::operator=(const set_t &s) {
  set_list_t *elS = s.set, *el = set = new set_list_t(nullptr, "");

  cardinality = s.cardinality;
  while (elS != nullptr) {
    el = el->next = new set_list_t(nullptr, elS->str);
    elS = elS->next;
  }
  el = set;
  set = set->next;
  delete el;

  return *this;
}

int set_t::GetCardinality(void) const noexcept {
  return cardinality;
}

void set_t::Add(const char el[]) {
  int comp = 1;
  set_list_t *prev = nullptr, *cur = set;

  while (cur != nullptr && (comp = strcmp(cur->str, el)) < 0) {
    prev = cur;
    cur = cur->next;
  }
  if (comp == 0)
    throw std::exception("Element already exist");
  if (prev == nullptr)
    set = new set_list_t(cur, el);
  else
    prev->next = new set_list_t(cur, el);
  cardinality++;
}

void set_t::Delete(const char el[]) {
  int comp = 1;
  set_list_t *prev = nullptr, *cur = set;

  while (cur != nullptr && (comp = strcmp(cur->str, el)) < 0) {
    prev = cur;
    cur = cur->next;
  }
  if (comp != 0)
    throw std::exception("Element doesn't exist");
  if (prev == nullptr) {
    set = cur->next;
    delete cur;
  }
  else {
    prev->next = cur->next;
    delete cur;
  }
  cardinality--;
}

bool set_t::Find(const char el[]) const noexcept {
  int comp = 1;
  set_list_t *cur = set;

  while (cur != nullptr && (comp = strcmp(cur->str, el)) < 0)
    cur = cur->next;

  if (comp == 0)
    return true;
  return false;
}

set_t set_t::Union(const set_t &s) const {
  set_t uni;
  set_list_t *el1 = set, *el2 = s.set, *elUni = uni.set = new set_list_t(nullptr, "");

  uni.set = elUni;
  while (el1 != nullptr && el2 != nullptr) {
    int comp = strcmp(el1->str, el2->str);

    if (comp == 0) {
      elUni = elUni->next = new set_list_t(nullptr, el1->str);
      uni.cardinality++;
      el1 = el1->next;
      el2 = el2->next;
    }
    else if (comp < 0) {
      elUni = elUni->next = new set_list_t(nullptr, el1->str);
      uni.cardinality++;
      el1 = el1->next;
    }
    else {
      elUni = elUni->next = new set_list_t(nullptr, el2->str);
      uni.cardinality++;
      el2 = el2->next;
    }
  }

  while (el1 != nullptr) {
    elUni = elUni->next = new set_list_t(nullptr, el1->str);
    uni.cardinality++;
    el1 = el1->next;
  }
  while (el2 != nullptr) {
    elUni = elUni->next = new set_list_t(nullptr, el2->str);
    uni.cardinality++;
    el2 = el2->next;
  }

  elUni = uni.set;
  uni.set = uni.set->next;
  delete elUni;

  return uni;
}

set_t set_t::Intersection(const set_t &s) const {
  set_t intersec;
  set_list_t *el1 = set, *el2 = s.set, *elIntersec = intersec.set = new set_list_t(nullptr, "");

  intersec.set = elIntersec;
  while (el1 != nullptr && el2 != nullptr) {
    int comp = strcmp(el1->str, el2->str);

    if (comp == 0) {
      elIntersec = elIntersec->next = new set_list_t(nullptr, el1->str);
      intersec.cardinality++;
      el1 = el1->next;
      el2 = el2->next;
    }
    else if (comp < 0)
      el1 = el1->next;
    else
      el2 = el2->next;
  }

  elIntersec = intersec.set;
  intersec.set = intersec.set->next;
  delete elIntersec;

  return intersec;
}

set_t set_t::Difference(const set_t &s) const {
  set_t dif;
  set_list_t *el1 = set, *el2 = s.set, *elDif = dif.set = new set_list_t(nullptr, "");

  dif.set = elDif;
  while (el1 != nullptr && el2 != nullptr) {
    int comp = strcmp(el1->str, el2->str);

    if (comp == 0) {
      el1 = el1->next;
      el2 = el2->next;
    }
    else if (comp < 0) {
      elDif = elDif->next = new set_list_t(nullptr, el1->str);
      dif.cardinality++;
      el1 = el1->next;
    }
    else
      el2 = el2->next;
  }

  while (el1 != nullptr) {
    elDif = elDif->next = new set_list_t(nullptr, el1->str);
    dif.cardinality++;
    el1 = el1->next;
  }

  elDif = dif.set;
  dif.set = dif.set->next;
  delete elDif;

  return dif;
}

set_t set_t::SymDifference(const set_t &s) const {
  set_t sDif;
  set_list_t *el1 = set, *el2 = s.set, *elSDif = sDif.set = new set_list_t(nullptr, "");

  sDif.set = elSDif;
  while (el1 != nullptr && el2 != nullptr) {
    int comp = strcmp(el1->str, el2->str);

    if (comp == 0) {
      el1 = el1->next;
      el2 = el2->next;
    }
    else if (comp < 0) {
      elSDif = elSDif->next = new set_list_t(nullptr, el1->str);
      sDif.cardinality++;
      el1 = el1->next;
    }
    else {
      elSDif = elSDif->next = new set_list_t(nullptr, el2->str);
      sDif.cardinality++;
      el2 = el2->next;
    }
  }

  while (el1 != nullptr) {
    elSDif = elSDif->next = new set_list_t(nullptr, el1->str);
    sDif.cardinality++;
    el1 = el1->next;
  }
  while (el2 != nullptr) {
    elSDif = elSDif->next = new set_list_t(nullptr, el2->str);
    sDif.cardinality++;
    el2 = el2->next;
  }

  elSDif = sDif.set;
  sDif.set = sDif.set->next;
  delete elSDif;

  return sDif;
}

bool set_t::IsSubset(const set_t &s) const {
  set_list_t *el1 = set, *el2 = s.set;

  while (el1 != nullptr && el2 != nullptr) {
    int comp = strcmp(el1->str, el2->str);

    if (comp == 0) {
      el1 = el1->next;
      el2 = el2->next;
    }
    else if (comp < 0)
      return false;
    else
      el2 = el2->next;
  }

  if (el1 != nullptr)
    return false;

  return true;
}

std::ostream & operator<<(std::ostream &oStream, const set_t::set_list_t &el) {
  oStream << "\t\"" << el.str << "\"" << std::endl;
  return oStream;
}

std::ostream & operator<<(std::ostream &oStream, const set_t &set) {
  set_t::set_list_t *cur = set.set;

  while (cur != nullptr) {
    oStream << *cur;
    cur = cur->next;
  }
  oStream << std::endl;

  return oStream;
}
