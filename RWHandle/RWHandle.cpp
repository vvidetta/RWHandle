#include <iostream>
#include <shared_mutex>

template <
  typename T
>
class Synchronized;

template <
  typename T
>
class SynchronizedReader
{
  friend class Synchronized<T>;
  std::shared_lock<std::shared_mutex> m_readerLock;
  T const& m_object;

  SynchronizedReader(std::shared_mutex mutex, T const& object)
    : m_readerLock{ mutex },
    m_object{ object }
  {
  }

public:
  [[nodiscard]] T const& operator*() const noexcept
  {
    return m_object;
  }
};

template <
  typename T
>
class SynchronizedWriter
{
  friend class Synchronized<T>;
  std::shared_lock<std::shared_mutex> m_writerLock;
  T& m_object;

  SynchronizedWriter(std::shared_mutex& mutex, T& object)
    : m_writerLock{ mutex.lock() },
    m_object { object }
  {
  }

public:
  [[nodiscard]] T& operator*() const noexcept
  {
    return m_object;
  }
};

template <
  typename T
>
class Synchronized
{
  friend class SynchronizedReader<T>;
  mutable std::shared_mutex m_mutex;
  T m_object;

public:

  SynchronizedReader<T> get_reader()
  {
    auto reader = SynchronizedReader<T>{ this };
    return reader;
  }
};

int main()
{
    std::cout << "Hello World!\n";
}

