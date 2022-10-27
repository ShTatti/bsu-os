#include <queue>
#include <condition_variable>

template<class T>
class BufferedChannel {
private:
	std::queue<T> queue;
	int buffer_size;
	bool is_closed;
	std::mutex mutex;
	std::condition_variable condition_variable;

public:
	explicit BufferedChannel(int size) {
		buffer_size = size;
		is_closed = false;
	}

	BufferedChannel& operator =(BufferedChannel&& channel) {
		queue = channel.queue;
		return *this;
	}

	void Send(T value) {
        if (!is_closed) {
            std::unique_lock<std::mutex> unique_lock(mutex);
            condition_variable.wait(unique_lock, [&]() { return buffer_size > queue.size(); });
            queue.push(value);
            unique_lock.unlock();
            condition_variable.notify_one();
        } else {
            throw std::runtime_error("!!!Channel is closed!!!");
        }
    }

	std::pair<T, bool> Receive() {
		std::unique_lock<std::mutex> unique_lock(mutex);
		condition_variable.wait(unique_lock, [&]() {return !queue.empty(); });
		T return_element = queue.front();
		queue.pop();
		unique_lock.unlock();
		condition_variable.notify_one();
		return std::pair<T, bool>(return_element, !is_closed);
	}

	void Close(){
		std::unique_lock<std::mutex> unique_lock(mutex);
		is_closed = true;
		unique_lock.unlock();
		condition_variable.notify_one();
	}
};
