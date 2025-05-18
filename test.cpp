// C++ program to illustrate the use of initializer_list in
// object construction
#include <iostream>
using namespace std;
#include <initializer_list>

// array type container constructed using initializer list
template <typename T> class MyContainer {
public:
    // Constructor taking initializer_list as a parameter
    MyContainer(initializer_list<T> values)
        : list(values)
    {
    }

    // Function to print all elements
    void printList() const
    {
        for (const T& value : list) {
            cout << value << " ";
        }
        cout << endl;
    }

private:
    initializer_list<T> list;
};

// diver code
int main()
{
    // Creating an instance of MyContainer with
    // initializer_list of int type
    MyContainer<int> intContainer({ 1, 2, 3, 4, 5 });
    MyContainer<char> charContainer({ 'a', 'b', 'c', 'd', 'e' });
    MyContainer<std::string> stringContainer({ "abc", "def", "ghi", "jkl", "mno" });
    cout << "Elements of Integer type are: ";
    intContainer.printList();
    charContainer.printList();
    stringContainer.printList();
    cout << endl;

    // Creating an instance of MyContainer with
    // initializer_list of double type
    cout << "Elements of double type are: ";
    MyContainer<double> doubleContainer
        = { 1.1, 2.2, 3.3, 4.4, 5.5 };
    doubleContainer.printList();
    cout << endl;

    return 0;
}
