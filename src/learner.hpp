#ifndef _learner_hpp_INCLUDED
#define _learner_hpp_INCLUDED

#include <map>
#include <vector>
#include <iostream>

namespace CaDiCaL {

  struct Internal;

  struct SelfLearner {

    Internal *_internal;
    std::vector<std::vector<int>> _cubes; // Record the cubes to learn so far
    std::map<int, int> _lit_to_conflicts; // These are decisions to the number of conflicts at the time the decision is pushed
    std::vector<int> _working_cube;
    bool _should_cube = false;

    SelfLearner(Internal *internal);

    void record_decision(int lit);
    void pop_decision(int lit);
    bool should_cube();
    void add_to_working_cube(int lit) { _working_cube.push_back(lit); }
    bool finalize_cube();
    void reset();

    void dump() {
      std::cout << "a ";
      for (const auto c : _working_cube) {
        std::cout << c << " ";
      }
      std::cout << "0" << std::endl;
    }

    void dump_status() {
      std::cout << "Learner: ";
      for (const auto &t : _lit_to_conflicts){
        std::cout << t.first << ": " << t.second << ", ";
      }
      std::cout << std::endl;
    }
  };
}

#endif
