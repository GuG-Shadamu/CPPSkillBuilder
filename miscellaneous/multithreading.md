# Multi-Threading

## Thread vs Process

Thread is:

- fast to start
- low overhead
- shared memory in same process is very fast

but:

- difficult to implement
- cannot run on distributed system

## Pass parameter in multi-thread

A parameter that is passed by thread, is always pass by value:

- use `std::ref()` to pass by reference or just pass by pointer.
- memory sharing will create `data race` problem. 
- use `std::move()` to pass, it will be both safe & fast.


---

`thread` object can only be `std::move` but not copy. 



## How many threads should I create

when # of thread > # of cores in CPU: oversubscription

- use `std::thread::hardware_concurrency();` to check the max thread you can create.


## Data Race

### Use `mutex` directly
- `mutex.lock`
- `mutex.unlock`

### Use `std::lock_guard<std::mutex> guard()`

- lock_guard is RAII

## DeadLock

to avoid

- make sure lock everything in the same order
- prefer locking single mutex
- prefer not to call user function right after locking `mutex`
- 
use 
``` cpp
std::lock()
``` 
``` cpp
std::lock_guard()
``` 
to lock more than one lock, this can lock locks without worry about deadlock:
  ```cpp
  std::lock(mu1, mu2);
  std::lock_guard<mutex> locker1(mu1, std::adopt_lock);
  std::lock_guard<mutex> locker2(mu2, std::adopt_lock);
  ```

## `unique_lock`

- unique_lock can be lock as well unlock
- you can create a lock without locking it via 
    ```cpp
    std::unique_lock<mutex> locker(mu, std::defer_lock);
    ...
    locker.unlock();
    ...
    locker.lock();

    ```
- unique_lock can be `std::move`
- lock_guard cannot be moved
- more overhead from `unique_lock` comparing with `lock_guard`



## `std::once_flag`

```cpp
std::call_once(flag, [&](){f.open("some_file.txt"); });
```




## Condition Variable

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




## `future`, `promise`, and `async()`

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


## Callable Objs

a few ways to call:

```cpp
class A{
public:
    void f(int x, char c){}
    long g(double x) {return 0;}
    int operator()(int N){return 0;}
};


int main(){
    A a;

    std::thread t1(a, 6);  // create a copy of a in a different thread
    std::thread t2(std::ref(a), 6);  // a() in a different thread
    std::thread t3(A(), 6);  // a() in a different thread
    std::thread t4([](int x){return x*x;}, 6);

    std::thread t5(&A::f, a, 8, 'w');
    std::thread t6(&A::f, &a, 8, 'w');
    std::thread t8(std::move(a), 8, 'w'); // a is no longer useable in main thread


    std::async(std::launch::async, a, 6);
    std::bind(a, 6);

    std::call_once(once_flag, a, 6);

}

```



## `packaged_task`

