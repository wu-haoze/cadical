#include "learner.hpp"
#include "internal.hpp"

namespace CaDiCaL {

	SelfLearner::SelfLearner(Internal *internal) {
		_internal = internal;
	}

	void SelfLearner::record_decision(int lit) {
		_lit_to_conflicts[lit] = _internal->number_of_conflicts();
	}

	void SelfLearner::pop_decision(int lit) {
		if (_working_cube.empty() &&
			_lit_to_conflicts[lit] == 0 &&
			_internal->number_of_conflicts() - _lit_to_conflicts[lit] >= _internal->opts.cubeconflictlim) {
			_should_cube = true;
		}
		//std::cout << _internal->number_of_conflicts() << " " << _lit_to_conflicts[lit] << " " <<  _internal->opts.cubeconflictlim << std::endl;
		_lit_to_conflicts.erase(lit);
	}

	bool SelfLearner::should_cube() {
		return _should_cube && _working_cube.empty();
	}

	bool SelfLearner::finalize_cube()
	{
		if (_should_cube) {
			_should_cube = false;
			_cubes.push_back(_working_cube);
			dump();
			_working_cube.clear();
			return _cubes.size() >= _internal->opts.cubing;
		}
		return false;
	}

	void SelfLearner::reset() {
		_cubes.clear();
		_lit_to_conflicts.clear();
		_working_cube.clear();
		_should_cube = false;
	}

}
