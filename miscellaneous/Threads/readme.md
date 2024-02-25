# Threadings

## Concepts

| Concept                      | Use Case                                                                                                                                               | Pros                                                                                        | Cons                                                                                     |
| ---------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------ | ------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------- |
| **Multithreading**           | - Tasks that are lightweight and IO-bound.<br>- Applications needing shared state or resources.<br>- GUI applications requiring background processing. | - Efficient resource usage due to shared memory.<br>- Faster communication between threads. | - Complexity in managing threads.<br>- Potential for deadlocks and race conditions.      |
| **Multiprocessing**          | - CPU-bound tasks performed in parallel without frequent data sharing.<br>- High-performance computing applications with independent tasks.            | - Improved stability due to process isolation.<br>- Better CPU core utilization.            | - Higher resource usage.<br>- Complex and slower inter-process communication.            |
| **Asynchronous Programming** | - I/O-bound applications like web servers.<br>- Tasks involving waiting for external resources (network requests, file IO).                            | - Efficient single-thread utilization.<br>- Simplifies concurrent I/O-bound task handling.  | - Challenging to debug due to non-linear execution flow.<br>- Requires language support. |

## Elements


### `atomic`

```cpp
    std::atomic_int acnt;
    for (int n = 0; n < 10000; ++n)
    {
        ++cnt;
        acnt.fetch_add(1, std::memory_order_relaxed);
    }
```


### `lock_guard`


```cpp
std::mutex mtx;
{
    std::lock_guard<std::mutex> guard(mtx);
    // critical section
} // mtx is automatically released here
```

### `unique_lock`

- unique_lock can be lock as well unlock
- you can create a lock without locking it via 
```cpp
std::mutex mtx;
{
    std::unique_lock<std::mutex> ulock(mtx, std::defer_lock);
    // Do something without lock...
    ulock.lock(); // Manually lock the mutex
    // critical section
    ulock.unlock(); // Manually unlock if needed before the end of the scope
    // Do something else without lock...
    ulock.lock(); // Lock again if necessary
    // another critical section
} // mtx is automatically released here if still locked

```

- unique_lock can be `std::move`
- lock_guard cannot be moved
- more overhead from `unique_lock` comparing with `lock_guard`


### `std::once_flag`

```cpp
std::call_once(flag, [&](){f.open("some_file.txt"); });
```



### `std::condition_variable`

- solution for busy-waiting

```cpp
std::condition_variable cond;
std::mutex mu;
...
// put thread to wait for a lock
std::unique_lock<mutex> locker(mu);
cond.wait(locker, [](){return if(1 == 1)}); 
// it represent a bool condition so that it only wake up once the condition is satisfied

// will notify one thread that is waiting
cond.notify_one();
// will notify one thread that is waiting
cond.notify_all();
```

- since `conditiona_variable` will lock & unlock the lock for multiple times, so we cannot use `lock_guard`. 




### `future`, `promise`, and `async()`

say there is a function:
```cpp
template <typename T>
T func(T para){return xxx};

std::future<T> future_ = std::async(func, parameter) // will create a seperate thread
std::future<T> future_ = std::async(std::launch::deferred, func, parameter) 
// will only call the func in the same thread

std::future<T> future_ = std::async(std::launch::async, func, parameter) 
// it will create a func by thread

std::future<T> future_ = std::async(std::launch::async | std::launch::deferred, func, parameter) 
// this depends on the implementation
// also this is the default parameter

// if we want to create a thread in the furture:
std::promise<T> p;
std::future<T> f = p.get_future();
std::future<T> fu = std::async(std::lanuch::async, func, std::ref(f));
p.set_value(4)

// if we have multiple threads, we use shared_future

std::promise<T> p;
std::future<T> f = p.get_future();
std::shared_future<T> sf = f.shared()
std::future<T> fu1 = std::async(std::lanuch::async, func, sf);
std::future<T> fu2 = std::async(std::lanuch::async, func, sf);
std::future<T> fu3 = std::async(std::lanuch::async, func, sf);
...
sf.set_value(4);


// if we need to get the result
x = fu.get(); 

// if we didn't call get, then we get a exception
//get result
T res = future_.get();
```

Future object can only be `get` once.

- `async` may or may not create another thread