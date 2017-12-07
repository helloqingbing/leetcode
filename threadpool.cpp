#include <pthread.h>
#include <unistd.h>
#include <deque>
#include <iostream>
#include <vector>
#include <errno.h>
#include <string.h>
using namespace std;
const int MAX_TASKS = 4;
const int DEFAULT_POOL_SIZE = 10;
const int STARTED = 0;
const int STOPPED = 1;

//===================================================================
//   CondVar
//===================================================================
class CondVar {
public:

  CondVar();
  ~CondVar();
  void wait(pthread_mutex_t* mutex);
  void signal();
  void broadcast();

private:
  pthread_cond_t m_cond_var;
};
CondVar::CondVar() {
  pthread_cond_init(&m_cond_var, NULL);
}
CondVar::~CondVar() {
  pthread_cond_destroy(&m_cond_var);
}
void CondVar::wait(pthread_mutex_t* mutex) {
  pthread_cond_wait(&m_cond_var, mutex);
}
void CondVar::signal() {
  pthread_cond_signal(&m_cond_var);
}
void CondVar::broadcast() {
  pthread_cond_broadcast(&m_cond_var);
}

//===================================================================
//   Mutex
//===================================================================

class Mutex
{
public:
  Mutex();
  ~Mutex();
  void lock();
  void unlock();
  pthread_mutex_t* get_mutex_ptr();

private:
  pthread_mutex_t m_lock;
  volatile bool is_locked;
};
Mutex::Mutex() {
  pthread_mutex_init(&m_lock, NULL);
  is_locked = false;
}

Mutex::~Mutex() {
  while(is_locked);
  unlock(); // Unlock Mutex after shared resource is safe
  pthread_mutex_destroy(&m_lock);
}

void Mutex::lock() {
  pthread_mutex_lock(&m_lock);
  is_locked = true;
}

void Mutex::unlock() {
  is_locked = false; // do it BEFORE unlocking to avoid race condition
  pthread_mutex_unlock(&m_lock);
}

pthread_mutex_t* Mutex::get_mutex_ptr(){
  return &m_lock;
}

//===================================================================
//  Task
//===================================================================
//template<class TClass>
class Task
{
public:
//  Task(TCLass::* obj_fn_ptr); // pass an object method pointer
  Task(void (*fn_ptr)(void*), void* arg); // pass a free function pointer
  ~Task();
  void operator()();
  void run();
private:
//  TClass* _obj_fn_ptr;
  void (*m_fn_ptr)(void*);
  void* m_arg;
};
Task::Task(void (*fn_ptr)(void*), void* arg) : m_fn_ptr(fn_ptr), m_arg(arg) {
}

Task::~Task() {
}

void Task::operator()() {
  (*m_fn_ptr)(m_arg);
  if (m_arg != NULL) {
    delete (char*)m_arg;
  }
}

void Task::run() {
  (*m_fn_ptr)(m_arg);
}

//===================================================================
//   ThreadPool
//===================================================================
class ThreadPool
{
public:
  ThreadPool();
  ThreadPool(int pool_size);
  ~ThreadPool();
  int initialize_threadpool();
  int destroy_threadpool();
  void* execute_thread();
  int add_task(Task* task);
private:
  int m_pool_size;
  Mutex m_task_mutex;
  CondVar m_task_cond_var;
  std::vector<pthread_t> m_threads; // storage for threads
  std::deque<Task*> m_tasks;
  volatile int m_pool_state;
};
ThreadPool::ThreadPool() : m_pool_size(DEFAULT_POOL_SIZE)
{
  cout << "Constructed ThreadPool of size " << m_pool_size << endl;
}

ThreadPool::ThreadPool(int pool_size) : m_pool_size(pool_size)
{
  cout << "Constructed ThreadPool of size " << m_pool_size << endl;
}

ThreadPool::~ThreadPool()
{
  // Release resources
  if (m_pool_state != STOPPED) {
    destroy_threadpool();
  }
}

// We can't pass a member function to pthread_create.
// So created the wrapper function that calls the member function
// we want to run in the thread.
extern "C"
void* start_thread(void* arg)
{
  ThreadPool* tp = (ThreadPool*) arg;
  tp->execute_thread();
  return NULL;
}

int ThreadPool::initialize_threadpool()
{
  // TODO: COnsider lazy loading threads instead of creating all at once
  m_pool_state = STARTED;
  int ret = -1;
  for (int i = 0; i < m_pool_size; i++) {
    pthread_t tid;
    ret = pthread_create(&tid, NULL, start_thread, (void*) this);
    if (ret != 0) {
      cerr << "pthread_create() failed: " << ret << endl;
      return -1;
    }
    m_threads.push_back(tid);
  }
  cout << m_pool_size << " threads created by the thread pool" << endl;

  return 0;
}

int ThreadPool::destroy_threadpool()
{
  // Note: this is not for synchronization, its for thread communication!
  // destroy_threadpool() will only be called from the main thread, yet
  // the modified m_pool_state may not show up to other threads until its 
  // modified in a lock!
  m_task_mutex.lock();
  m_pool_state = STOPPED;
  m_task_mutex.unlock();
  cout << "Broadcasting STOP signal to all threads..." << endl;
  m_task_cond_var.broadcast(); // notify all threads we are shttung down

  int ret = -1;
  for (int i = 0; i < m_pool_size; i++) {
    void* result;
    ret = pthread_join(m_threads[i], &result);
    cout << "pthread_join() returned " << ret << ": " << strerror(errno) << endl;
    m_task_cond_var.broadcast(); // try waking up a bunch of threads that are still waiting
  }
  cout << m_pool_size << " threads exited from the thread pool" << endl;
  return 0;
}

void* ThreadPool::execute_thread()
{
  Task* task = NULL;
  cout << "Starting thread: " << pthread_self() << endl;
  while(true) {
    // Try to pick a task
    cout << "Locking: " << pthread_self() << endl;
    m_task_mutex.lock();
    
    // We need to put pthread_cond_wait in a loop for two reasons:
    // 1. There can be spurious wakeups (due to signal/ENITR)
    // 2. When mutex is released for waiting, another thread can be waken up
    //    from a signal/broadcast and that thread can mess up the condition.
    //    So when the current thread wakes up the condition may no longer be
    //    actually true!
    while ((m_pool_state != STOPPED) && (m_tasks.empty())) {
      // Wait until there is a task in the queue
      // Unlock mutex while wait, then lock it back when signaled
      cout << "Unlocking and waiting: " << pthread_self() << endl;
      m_task_cond_var.wait(m_task_mutex.get_mutex_ptr());
      cout << "Signaled and locking: " << pthread_self() << endl;
    }

    // If the thread was woken up to notify process shutdown, return from here
    if (m_pool_state == STOPPED) {
      cout << "Unlocking and exiting: " << pthread_self() << endl;
      m_task_mutex.unlock();
      pthread_exit(NULL);
    }

    task = m_tasks.front();
    m_tasks.pop_front();
    cout << "Unlocking: " << pthread_self() << endl;
    m_task_mutex.unlock();

    //cout << "Executing thread " << pthread_self() << endl;
    // execute the task
    (*task)(); // could also do task->run(arg);
    //cout << "Done executing thread " << pthread_self() << endl;
    delete task;
  }
  return NULL;
}

int ThreadPool::add_task(Task* task)
{
  m_task_mutex.lock();

  // TODO: put a limit on how many tasks can be added at most
  m_tasks.push_back(task);

  m_task_cond_var.signal(); // wake up one thread that is waiting for a task to be available

  m_task_mutex.unlock();

  return 0;
}

//===================================================================
//   main g++ -lpthread -o threadpool threadpool.cc
//===================================================================

void hello(void* arg)
{
  int* x = (int*) arg;
  cout << "Hello " << *x << endl;
  cout << "\n";
}

int main(int argc, char* argv[])
{
  ThreadPool tp(2);
  int ret = tp.initialize_threadpool();
  if (ret == -1) {
    cerr << "Failed to initialize thread pool!" << endl;
    return 0;
  }

  for (int i = 0; i < MAX_TASKS; i++) {
    int* x = new int();
    *x = i+1;
    Task* t = new Task(&hello, (void*) x);
    tp.add_task(t);
    cout << "Added to pool, task " << i+1 << endl;
  }

  sleep(2);

  tp.destroy_threadpool();

  // TODO: delete worker objects

  cout << "Exiting app..." << endl;

  return 0;
}
