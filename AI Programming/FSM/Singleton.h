#pragma once


#define IS_SINGLETON(T)friend class Singleton<T>; private: T(){}; T(const T& other); T& operator=(const T& other);

template <typename T> class Singleton
{
	static T* m_oInstance;

public:
	static bool IsNotInit()
	{
		return m_oInstance == nullptr;
	}
	~Singleton()
	{
		delete(m_oInstance);
	}

	static T* GetSingleton()
	{
		if (IsNotInit())
		{
			m_oInstance = new T();
		}
		return m_oInstance;
	}

	static void Release()
	{
		delete(m_oInstance);
		m_oInstance = nullptr;
	}

};

template <typename T> T* Singleton <T>::m_oInstance = 0;
