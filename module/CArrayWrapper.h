#ifndef CARRAYWRAPPER_H
#define CARRAYWRAPPER_H

#include <cstddef>

template <class T>
class CArrayWrapper
{
public:
    explicit CArrayWrapper(size_t num) : m_num(num), m_array(nullptr)
    {
        m_array = new T*[num];
        for(size_t i =0; i < num; i++)
            m_array[i] = new T;
    }

    CArrayWrapper(const CArrayWrapper&) = delete;
    CArrayWrapper& operator=(const CArrayWrapper&) = delete;

    ~CArrayWrapper(){free_array();}

    const T& operator[] (int indx) const {return *m_array[indx];}
    T& operator[] (int indx) {return *m_array[indx];}

    operator T** () const noexcept { return m_array; };
    operator const T** () const noexcept {return m_array;};

private:
    void free_array() noexcept
    {
        ///@todo: check delete vs free
        for(size_t i =0; i < m_num; i++)
            delete m_array[i];

        delete m_array;
    }

private:
    size_t m_num = 0;
    T**    m_array;
};


#endif // PAM_STEPIC_CARRAYWRAPPER_H
