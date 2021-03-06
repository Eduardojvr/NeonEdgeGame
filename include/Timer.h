#ifndef TIMER_H_
#define TIMER_H_

class Timer {
private:
	float time = 0;
	float limit = 0;
	bool running = false;

public:
	Timer();
	Timer(float limit);
	~Timer();
	void Start();
    void Stop();
    void Reset();
	void Update(float dt);
	void SetLimit(float l);
	bool IsRunning();
	float GetElapsed();
	float GetTime();
};

#endif /* TIMER_H_ */
