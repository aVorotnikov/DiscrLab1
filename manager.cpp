#include <string>
#include <functional>

#include "manager.h"

enum class token_t {
  id,
  element,
  empty
};

using do_cmd_t = std::function<void (std::map<int, set_t> *sets, int id[3], const std::string &el)>;

struct cmd_info_t {
  const std::string
    syntax,
    descr;
  const token_t toks[3];
  do_cmd_t cmdFunc;
};

extern const std::map<const std::string, const cmd_info_t> s_Cmds;

static void _exitCmd(std::map<int, set_t> *sets, int id[3], const std::string &el) {
}

static void _helpCmd(std::map<int, set_t> *sets, int id[3], const std::string &el) {
  for (auto cmds : s_Cmds)
    std::cout << cmds.first << ": " << cmds.second.syntax << " - " << cmds.second.descr << std::endl;
  std::cout << std::endl;
}

static void _createCmd(std::map<int, set_t> *sets, int id[3], const std::string &el) {
  auto set = sets->find(id[0]);
  if (set != sets->end())
    std::cout << "Set is already exist" << std::endl;
  else
    (*sets)[id[0]] = set_t();
}

static void _deleteCmd(std::map<int, set_t> *sets, int id[3], const std::string &el) {
  auto set = sets->find(id[0]);
  if (set != sets->end())
    sets->erase(id[0]);
  else
    std::cout << "Set doesn't exist" << std::endl;
}

static void _cardCmd(std::map<int, set_t> *sets, int id[3], const std::string &el) {
  auto set = sets->find(id[0]);
  if (set != sets->end())
    std::cout << set->second.GetCardinality() << std::endl;
  else
    std::cout << "Set doesn't exist" << std::endl;
}

static void _addCmd(std::map<int, set_t> *sets, int id[3], const std::string &el) {
  auto set = sets->find(id[0]);
  if (set != sets->end())
    set->second.Add(el.c_str());
  else
    std::cout << "Set doesn't exist" << std::endl;
}

static void _delCmd(std::map<int, set_t> *sets, int id[3], const std::string &el) {
  auto set = sets->find(id[0]);
  if (set != sets->end())
    set->second.Delete(el.c_str());
  else
    std::cout << "Set doesn't exist" << std::endl;
}

static void _findCmd(std::map<int, set_t> *sets, int id[3], const std::string &el) {
  auto set = sets->find(id[0]);
  if (set != sets->end())
    std::cout << (set->second.Find(el.c_str()) ? "element exist" : "element doesn't exist") << std::endl;
  else
    std::cout << "Set doesn't exist" << std::endl;
}

static void _uniCmd(std::map<int, set_t> *sets, int id[3], const std::string &el) {
  auto
    set1 = sets->find(id[0]),
    set2 = sets->find(id[1]),
    set3 = sets->find(id[2]);
  if (set1 != sets->end() && set2 != sets->end() && set3 == sets->end())
    (*sets)[id[2]] = set1->second.Union(set2->second);
  else
    std::cout << "Wrong ids" << std::endl;
}

static void _intersecCmd(std::map<int, set_t> *sets, int id[3], const std::string &el) {
  auto
    set1 = sets->find(id[0]),
    set2 = sets->find(id[1]),
    set3 = sets->find(id[2]);
  if (set1 != sets->end() && set2 != sets->end() && set3 == sets->end())
    (*sets)[id[2]] = set1->second.Intersection(set2->second);
  else
    std::cout << "Wrong ids" << std::endl;
}

static void _difCmd(std::map<int, set_t> *sets, int id[3], const std::string &el) {
  auto
    set1 = sets->find(id[0]),
    set2 = sets->find(id[1]),
    set3 = sets->find(id[2]);
  if (set1 != sets->end() && set2 != sets->end() && set3 == sets->end())
    (*sets)[id[2]] = set1->second.Difference(set2->second);
  else
    std::cout << "Wrong ids" << std::endl;
}

static void _sdifCmd(std::map<int, set_t> *sets, int id[3], const std::string &el) {
  auto
    set1 = sets->find(id[0]),
    set2 = sets->find(id[1]),
    set3 = sets->find(id[2]);
  if (set1 != sets->end() && set2 != sets->end() && set3 == sets->end())
    (*sets)[id[2]] = set1->second.SymDifference(set2->second);
  else
    std::cout << "Wrong ids" << std::endl;
}

static void _issubCmd(std::map<int, set_t> *sets, int id[3], const std::string &el) {
  auto
    set1 = sets->find(id[0]),
    set2 = sets->find(id[1]);
  if (set1 != sets->end() && set2 != sets->end())
    std::cout << (set1->second.IsSubset(set2->second) ? "subset" : "not subset") << std::endl;
  else
    std::cout << "Wrong ids" << std::endl;
}

static void _setsCmd(std::map<int, set_t> *sets, int id[3], const std::string &el) {
  for (auto &set : *sets)
    std::cout << set.first << std::endl;
  std::cout << std::endl;
}

static void _viewCmd(std::map<int, set_t> *sets, int id[3], const std::string &el) {
  auto set = sets->find(id[0]);
  if (set != sets->end())
    std::cout << sets->find(id[0])->second;
  else
    std::cout << "Set doesn't exist" << std::endl;
}

static const std::map<const std::string, const cmd_info_t> s_Cmds = {
  {"help", {"help", "print all comands with syntax and description", {token_t::empty, token_t::empty, token_t::empty}, _helpCmd}},
  {"exit", {"exit", "end of session", {token_t::empty, token_t::empty, token_t::empty}, _exitCmd}},

  {"create", {"create <id>", "creates set with id", {token_t::id, token_t::empty, token_t::empty}, _createCmd}},
  {"delete", {"delete <id>", "deletes set with id", {token_t::id, token_t::empty, token_t::empty}, _deleteCmd}},

  {"card", {"card <id>", "print cardinality", {token_t::id, token_t::empty, token_t::empty}, _cardCmd}},
  {"add", {"add <id> \"<element>\"", "add element to set", {token_t::id, token_t::element, token_t::empty}, _addCmd}},
  {"del", {"del <id> \"<element>\"", "delete element from set", {token_t::id, token_t::element, token_t::empty}, _delCmd}},
  {"find", {"find <id> \"<element>\"", "find element in set", {token_t::id, token_t::element, token_t::empty}, _findCmd}},

  {"uni", {"find <id1> <id2> <idRes>", "create union set", {token_t::id, token_t::id, token_t::id}, _uniCmd}},
  {"intersec", {"intersec <id1> <id2> <idRes>", "create intersection set", {token_t::id, token_t::id, token_t::id}, _intersecCmd}},
  {"dif", {"dif <id1> <id2> <idRes>", "create difference set", {token_t::id, token_t::id, token_t::id}, _difCmd}},
  {"sdif", {"sdif <id1> <id2> <idRes>", "create symmetrical difference set", {token_t::id, token_t::id, token_t::id}, _sdifCmd}},
  {"issub", {"issub <id1> <id2>", "check if subset", {token_t::id, token_t::id, token_t::empty}, _issubCmd}},

  {"sets", {"sets", "print all set id", {token_t::empty, token_t::empty, token_t::empty}, _setsCmd}},
  {"view", {"view <id>", "print set elements", {token_t::id, token_t::empty, token_t::empty}, _viewCmd}},
};

manager_t::manager_t(void) {
}

void manager_t::Session(void) {
  bool isExit = false, isErr = false;
  std::string line, cmd, el;
  int id[3];

  std::cout << "Use command 'help' to have help" << std::endl << std::endl;

  while (!isExit) {
    isErr = false;
    std::getline(std::cin, line);
    cmd.clear();
    cmd.reserve(line.size());

    std::string::iterator c = line.begin();
    while (c != line.end() && !isspace(*c)) {
      cmd.push_back(*c);
      c++;
    }

    auto command = s_Cmds.find(cmd);
    if (command == s_Cmds.end()) {
      std::cout << "Unknown comand" << std::endl;
      continue;
    }

    int i = 0;
    for (auto &t : command->second.toks) {
      while (c != line.end() && isspace(*c))
        c++;
      switch (t) {
        case token_t::empty:
          break;
        case token_t::id:
          id[i] = 0;
          if (c == line.end() || !isdigit(*c)) {
            isErr = true;
            break;
          }
          while (c != line.end() && isdigit(*c)) {
            id[i] *= 10;
            id[i] += *c - '0';
            c++;
          }
          break;
        case token_t::element:
          el.clear();
          el.reserve(line.size());
          if (c == line.end() || *c != '\"') {
            isErr = true;
            break;
          }
          c++;
          while (c != line.end() && *c != '\"') {
            el.push_back(*c);
            c++;
          }
          if (c == line.end() || *c != '\"') {
            isErr = true;
            break;
          }
          c++;
          break;
      }
      i++;

      if (isErr)
        break;
    }

    while (c != line.end())
      if (!isspace(*c))
        break;

    if (isErr || c != line.end()) {
      std::cout << "Error command format" << std::endl;
      continue;
    }

    try {
      command->second.cmdFunc(&sets, id, el);
      if (command->first == "exit")
        return;
    }
    catch (std::exception &exc) {
      std::cout << exc.what() << std::endl;
    }
  }
}

std::ostream & operator<<(std::ostream &oStream, const manager_t &m) {
  for (auto &set : m.sets)
    oStream << set.first << std::endl;
  oStream << std::endl;

  return oStream;
}
