#pragma once
#include "iostream"
#include "map"

template <class T, T defValue>
class MatrixRow;

/**
 * @brief The Matrix class - Шаблонный класс 2-мерной разряженной бесконечной матрицы
 */
template<class T, T defValue>
class Matrix
{
public:
    /**
     * @brief Matrix - Конструктор
     */
    Matrix(): m_defValue(defValue)
    {
    }

    /**
     * @brief size - Размер матрицы (количество занятых ячеек)
     * @return размер матрицы
     */
    std::size_t size()
    {
        return m_matrix.size();
    }

    /**
     * @brief operator [] - Оператор доступа к строке
     * @param row - Номер строки
     * @return строку матрицы
     */
    MatrixRow<T,defValue> operator [](int row)
    {
        MatrixRow<T, defValue> curRow(this, row);
        return curRow;
    }

    /**
     * @brief getValue - Получить значение по координатам
     * @param x - Номер строки
     * @param y - Номер столбца
     * @return значение
     */
    const T& getValue(int x, int y) const
    {
       auto it = m_matrix.find(std::make_pair(x, y));
        if(it != m_matrix.end())
            return it->second;

        return m_defValue;
    }

    /**
     * @brief insertValue - Вставить значение в матрицу
     * @param x - Номер строки
     * @param y - Номер столбца
     * @param val - значение
     */
    void insertValue(int x, int y,T val)
    {
        if(val == m_defValue)
        {
            auto it = m_matrix.find(std::make_pair(x,y));
            if(it != m_matrix.end())
                m_matrix.erase(it);
        }
        else
        {
            std::pair<int, int> coord = std::make_pair(x,y);
            m_matrix.emplace(coord, val);
        }
    }

    /**
     * @brief printAllValues - Напечатать все значения в матрице
     */
    void printAllValues()
    {
        for(auto it: m_matrix)
        {
            auto k = it.first ;
            auto val = it.second;
            std::cout<<"["<<k.first<<"]["<<k.second<<"] = "<<val<<std::endl;
        }
    }

    /**
     * @brief printValues - Напечатать значения из диапазона
     * @param from - Координаты начала диапазона
     * @param to - Координаты конца диапазона
     */
    void printValues(std::pair<int,int> from, std::pair<int, int> to)
    {
        for(int i = from.first; i <= to.first; i++)
        {
            for(int j = from.second; j <= to.second; j++)
            {
                std::cout << getValue(i, j)<<" ";
            }
            std::cout << std::endl;
        }
    }

    /**
     * @brief The iterator class - Класс итератора
     */
    class iterator{
        /**
         * @brief m_cur - Текущее значение итератора
         */
        typename std::map<std::pair<int, int>, T>::iterator m_cur;
    public:
        iterator(typename std::map<std::pair<int, int>, T>::iterator it): m_cur(it)
        {}
        typename std::map<std::pair<int, int>, T>::iterator getIter()
        {
            return m_cur;
        }
        iterator& operator++()
        {
            m_cur++;
            return *this;
        }

        iterator operator++(int)
        {
            iterator retval = *this;
            ++(*this);
            return retval;
        }

        bool operator==(iterator other) const
        {
            return m_cur == other.getIter();
        }

        bool operator!=(iterator other) const
        {
            return m_cur != other.getIter();
        }

        std::tuple<int, int, T> operator*()
        {
            auto k = m_cur->first ;
            auto val = m_cur->second;
            return std::make_tuple(k.first, k.second, val);
        }

    };

    /**
     * @brief begin - итератор начала матрицы
     * @return итератор
     */
    iterator begin()
    {
        return iterator(m_matrix.begin());
    }
    /**
     * @brief end - итератор конца матрицы
     * @return итератор
     */
    iterator end()
    {
        return iterator(m_matrix.end());
    }

private:
    /**
     * @brief m_matrix - Карта для хранения заполненных значений в матрице
     */
    std::map<std::pair<int, int>, T> m_matrix;
    /**
     * @brief m_defValue - Значение по умолчанию
     */
    T m_defValue;
};

/**
 * @brief The MatrixRow class - Класс строки матрицы
 */
template <class T, T defValue>
class MatrixRow
{
public:
    /**
     * @brief MatrixRow - Конструктора строки
     * @param matrix - Указатель на матрицу
     * @param r - Нмоер строки
     */
    MatrixRow(Matrix<T, defValue>* matrix, int r): m_matrix(matrix), m_curRow(r), m_col(0)
    {
    }

    /**
     * @brief operator [] - Получить значение в столбце
     * @param col - Номер столбца
     * @return значение из матрицы
     */
    MatrixRow& operator[](int col)
    {
        m_col = col;
        savedValue = m_matrix->getValue(m_curRow, col);
        return *this;
    }
    /**
     * @brief operator T - Сохраненное значение
     */
    operator T()
    {
        return savedValue;
    }

    /**
     * @brief operator = - Оператор присваивания
     * @param newValue новое значение
     */
    void operator =(T newValue)
    {
        savedValue = newValue;
        m_matrix->insertValue(m_curRow, m_col, newValue);
    }

private:
    /**
     * @brief m_matrix - Указатель на стрицу
     */
    Matrix<T, defValue>* m_matrix;
    /**
     * @brief m_curRow - Номер строки
     */
    int m_curRow;
    /**
     * @brief m_col - Номер столбца
     */
    int m_col;
    /**
     * @brief savedValue - Значение в ячейке
     */
    T savedValue;
};
