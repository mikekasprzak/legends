// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_TASK_H__
#define __GEL_TASK_H__
// - ------------------------------------------------------------------------------------------ - //

class GelTask {
public:
	
	void Start() {
		
	}
	
	void StartThread() {
		Start();
	}
	
	
public:
	inline const bool IsReady() const {
		return true;
	}
	
	inline const bool IsFinished() const {
		return true;
	}
};

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_TASK_H__ //
// - ------------------------------------------------------------------------------------------ - //