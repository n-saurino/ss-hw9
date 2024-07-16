#include <thread>

class ScopedThread{
private:
    std::thread t_;
public:
    ScopedThread(std::thread t): t_(std::move(t)){

    }

    ~ScopedThread(){
        if(!t_.joinable()){
            throw std::logic_error("Thread is not joinable!");
        }
        t_.join();
    }
};