#ifndef CARRAYWRAPPER_H
#define CARRAYWRAPPER_H

#include <cstddef>

template <class T>
class CArrayWrapper
{
public:
    explicit CArrayWrapper(size_t num) : m_num(num), m_array(nullptr)
    {
        m_array = new T[m_num];
    }

    explicit CArrayWrapper(T* array, size_t num) : m_num(num), m_array(array)
    {}

    CArrayWrapper(const CArrayWrapper&) = delete;

    CArrayWrapper( CArrayWrapper&& rhs) : m_num(rhs.m_num), m_array(rhs.m_array)
    {
        rhs.m_array = nullptr;
        rhs.m_num = 0;
    }

    CArrayWrapper& operator=(const CArrayWrapper&) = delete;
    CArrayWrapper& operator=( CArrayWrapper&& rhs)
    {
        clear();
        m_array = rhs.m_array;
        rhs.m_array = nullptr;
        m_num = rhs.m_num;
        rhs.m_num = 0;
        return *this;
    }

    ~CArrayWrapper(){ clear(); }

    size_t size() const { return m_num; }

    const T& operator[] (int indx) const {return m_array[indx];}
    T& operator[] (int indx) {return m_array[indx];}

    operator T* () noexcept { return m_array; };
    operator const T* () const noexcept {return (const T*)m_array;};

    void clear()
    {
        delete[] m_array;
        m_array = nullptr;
        m_num = 0;
    }

private:

private:
    size_t m_num = 0;
    T*     m_array;
};


#endif // PAM_STEPIC_CARRAYWRAPPER_H
