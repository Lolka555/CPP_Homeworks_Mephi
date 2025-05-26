#include <chrono>

class Timer {
private:
    std::chrono::steady_clock::time_point time;

public:
    Timer(std::chrono::seconds duration) {
      time = std::chrono::steady_clock::now() + duration;
    }

    bool Expired() const{
      return std::chrono::steady_clock::now() >= time;
    }

};

class TimeMeasurer {
private:
    std::ostream& ostream;
    std::chrono::steady_clock::time_point time;

public:
    TimeMeasurer(std::ostream& ostream): ostream(ostream) {
      time = std::chrono::steady_clock::now();
    }

    ~TimeMeasurer() {
      auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
          std::chrono::steady_clock::now() - time
      ).count();
      ostream << "Elapsed time: " << elapsed << std::endl;
    }
};

