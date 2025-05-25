#include <iostream>
#include <stdexcept>
#include <algorithm> // ��� std::copy

class smart_array
{
private:
    int* data;
    size_t size;
    size_t capacity;

public:
    // �����������
    smart_array(size_t initial_capacity)
        : data(new int[initial_capacity]), size(0), capacity(initial_capacity) 
    {
    }

    // ����������
    ~smart_array()
    {
        delete[] data;
    }

    // ����������� ����������� (�������� �����������)
    smart_array(const smart_array& other)
        : data(new int[other.capacity]), size(other.size), capacity(other.capacity) 
    {
        std::copy(other.data, other.data + other.size, data); // �������� ��������
    }

    // �������� ������������ (�������� �����������)
    smart_array& operator=(const smart_array& other) 
    {
        if (this == &other) // �������� �� ���������������� (arr = arr)
        { 
            return *this;
        }

        // ����������� ������ ������
        delete[] data;

        // �������� ����� ������ � �������� ������
        capacity = other.capacity;
        size = other.size;
        data = new int[capacity];
        std::copy(other.data, other.data + other.size, data);

        return *this;
    }

    // ���������� ��������
    void add_element(int value) 
    {
        if (size >= capacity) 
        {
            throw std::out_of_range("��������� ����������� �������");
        }
        data[size++] = value;
    }

    // ��������� ��������
    int get_element(size_t index) const 
    {
        if (index >= size)
        {
            throw std::out_of_range("������ �� ��������� �������");
        }
        return data[index];
    }
};

int main() 
{
    setlocale(LC_ALL, "rus");
    try 
    {
        smart_array arr(5);
        arr.add_element(1);
        arr.add_element(4);
        arr.add_element(155);

        smart_array new_array(2);
        new_array.add_element(44);
        new_array.add_element(34);

        arr = new_array; // ������ �������� ���������!

        std::cout << arr.get_element(0) << std::endl; // 44
        std::cout << arr.get_element(1) << std::endl; // 34
    }
    catch (const std::exception& ex) 
    {
        std::cout << ex.what() << std::endl;
    }
    return 0;
}