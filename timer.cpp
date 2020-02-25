#include<iostream>
#include<chrono>
#include<vector>

// instantiate Timer in a scope block to test performance of following statement/s.

class Timer
{
    private:
        using TimerClock = std::chrono::steady_clock;
        using MicroSecond = std::chrono::microseconds;
        using fMilliSecond = std::chrono::duration<float, std::ratio<1, 1'000>>;

        template<typename Duration>
        using TimePoint = std::chrono::time_point<TimerClock, Duration>;

        TimePoint<MicroSecond> start_time_{};
        TimePoint<MicroSecond> end_time_{};
    public:
        Timer() { start_time_ = std::chrono::time_point_cast<MicroSecond>(TimerClock::now()); }
        ~Timer() 
        {
            end_time_ = std::chrono::time_point_cast<MicroSecond>(TimerClock::now());

            fMilliSecond time_elapsed = end_time_ - start_time_;
            std::cout << "\nTime Elapsed: " << time_elapsed.count() << "ms\n"; 
        }
};

void TestPerformance()
{
    std::cout << "Test performance between iteration by reference & by copy\n";
    const int kMaxElement = 1'000'000;
    std::vector<int> storage;
    storage.reserve(kMaxElement);

    for(int i = 0; i < kMaxElement; ++i)
    {
        storage.emplace_back(i);
    }

    {
        std::cout << "Iteration by copy: ";

        Timer timer_access_by_copy;
        for (auto element : storage) {;}
    }
    {
        std::cout << "Iteration by reference: ";

        Timer timer_access_by_ref;
        for (auto& element : storage) {;}
    }
}
int main()
{
    TestPerformance();
}
