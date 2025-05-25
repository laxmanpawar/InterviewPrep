#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <thread>
#include <mutex>

using namespace std;

bool isPalindrome(const string & str) {
    int l = 0, r = str.size() - 1;
    while(l < r) {
        if(str[l] != str[r]) return false;
        else {
            ++l;--r;
        }
    }
    return true;
}

bool isPalindrome(int num) {
    int rev = 0, temp = num;

    while(temp != 0) {
        int rem = temp%10;
        rev = rev * 10 + rem;
        temp /= 10;
    }

    return rev == num ? true : false;
}

int factorial(int num) {
    if(num == 0 || num == 1) return 1;

    return num * factorial(num - 1);
}

int useOfReferences() {
    int n1 = 10;
    int & ref1 = n1;
    ref1 = 20;

    cout << "n1: " << n1 << "\n";
    cout << "Ref1: " << ref1 << "\n";

    const int & ref2 = 50;
    cout << "Ref2: " << ref2 << "\n";

    return 0;
}

int useOfPointers() {
    int n1 = 10;

    int *ptr1 = &n1;
    cout << "ptr1: " << ptr1 << "\nn1: " << n1 << "\n";
    *ptr1 = 50;
    cout << "ptr1: " << ptr1 << "\nn1: " << n1 << "\n";

    return 0;
}

int ** create2DArray(int r, int c) {
    int ** arr = new int*[r];
    for(int i = 0; i < r; ++i) {
        int * row = new int[c];
        arr[i] = row;
        for(int j = 0; j < c; ++j) {
            arr[i][j] = i * c + j;
        } 
    }

    return arr;
}

void print2DArray(int ** arr, int r, int c) {
    for(int i = 0; i < r; ++i) {
        for(int j = 0; j < c; ++j) {
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
}

void free2DArray(int ** arr, int r) {
    for(int i = 0; i < r; ++i) {
        delete[] arr[i];
    }
    delete[] arr;
}

// operator Overloading 
class Cents {
    int m_cents;
    
    public:
    Cents(int cents) : m_cents(cents) {}
    Cents operator+(const Cents& rhs) {
        return Cents(this->m_cents + rhs.m_cents);
    }
    
    friend ostream & operator << (ostream & out, const Cents & rhs) {
        out << rhs.m_cents << "\n";
        return out;
    }
    
};

// ostream & operator<< (ostream & out, const Cents & rhs) {
//     out << rhs.m_cents << "\n";
//     return out;
// }

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}


//////////////////////////////////////////////////////////
// Function Pointers
void useOfFunctionPointers() {
    
    int (*fptr)(int, int) = add;
    cout << "Sum: " << fptr(10, 20) << "\n";
    fptr = subtract;
    cout << "Subtract: " << fptr(10, 20) << "\n";
}
//////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////
// Virtual tables
namespace vtable {
    class Base {
        public:
        virtual void fun1() {cout << "Base: fun1()\n";}
        virtual void fun2() {cout << "Base: fun2()\n";}
    };
    
    class D1: public Base {
        public:
        virtual void fun1() override {cout << "D1: fun1()\n";}
    };
    
    class D2: public Base {
        public:
        virtual void fun2() override {cout << "D1: fun2()\n";}
    };
};
//////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////
// Pure virtual Functions
namespace pureVirtualFunctions {
    class Base {
        public:
        virtual void fun1() {
            
        }
    };
    class D1: public Base {
        public:
        virtual void fun1() override {
            cout << "D1: fun1()\n";
        }
    };
}
//////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////
// Templates

template <typename T>
bool isEqual(T a, T b) {
    return a == b ? true: false;
}
//////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////
// Copy Constructor and assignment operator
class Complex {
    int m_real;
    int m_imag;
    public:
    Complex(int real = 0, int imag = 0) : m_real(real), m_imag(imag) { 
        cout << "Complex:: ctr called.\n";
    }
    Complex(const Complex& rhs): m_real(rhs.m_real), m_imag(rhs.m_imag) { 
        cout << "Complex::Copy ctr called.\n";
    }
    
    Complex& operator=(const Complex& rhs) {
        cout << "Complex::assignment operator called.\n";
        this->m_real = rhs.m_real;
        this->m_imag = rhs.m_imag;
        return *this;
    }
    
    Complex operator+ (const Complex& rhs) {
        return {this->m_real + rhs.m_real, this->m_imag + rhs.m_imag};
    }
    
    friend ostream& operator<< (ostream& out, const Complex& c) {
        out << c.m_real << " + " << c.m_imag << "i\n";
        return out;
    }
};
//////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////
// MyString class
class MyString {
    int m_len;
    char * m_data {};
    
    void deepCopy(const MyString & rhs) {
        if(m_data) delete[] m_data;
        m_len = rhs.m_len;
        m_data = new char[m_len+1];
        for(int i = 0; i < m_len; ++i) {
            m_data[i] = rhs.m_data[i];
        }
        m_data[m_len] = '\0';
    }
    
    public:
    MyString(char * data = nullptr) {
        m_len = data == nullptr ? 0 : strlen(data);
        
        m_data = new char[m_len+1];
        for(int i = 0; i < m_len; ++i) {
            m_data[i] = data[i];
        }
        m_data[m_len] = '\0';
    }
    void * operator new(size_t size) {
        cout << "MyString::operator new called with size: " << size << "\n";
        void * ptr = ::operator new(size);
        
        return ptr;
    }
    
    void operator delete(void * ptr) {
        cout << "MyString::operator delete called.\n";
        free(ptr);
    }
    
    ~MyString() {
        delete[] m_data;
    }
    
    MyString(const MyString& rhs) {
        cout << "MyString::Copy ctr\n";
        deepCopy(rhs);
    }
    
    MyString& operator= (const MyString & rhs) {
        cout << "MyString::assignment operator called.\n";
        if(this == &rhs) return *this;
        deepCopy(rhs);
        
        return *this;
    }
    
    friend ostream& operator<< (ostream& out, const MyString & str) {
        out << str.m_data;
        return out;
    }
};
//////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////
// Smart Pointers
class Resource {
    
    public:
    Resource() {
        cout << "Resource allocated.\n";
    }
    ~Resource() {
        cout << "Resource de-allocated.\n";
    }
    void sayHi() {
        cout << "Hi from Resource.\n";
    }
};

template <typename T> 
class AutoPtr {
    T * m_ptr;
    public:
    AutoPtr(T* ptr = nullptr): m_ptr(ptr) {
        
    }
    ~AutoPtr() {
        delete m_ptr;
    }
    
    AutoPtr(AutoPtr& rhs) {
        cout << "AutoPtr::copy ctr called.\n";
        m_ptr = rhs.m_ptr;
        rhs.m_ptr = nullptr;
    }
    
    AutoPtr& operator= (AutoPtr & rhs) {
        cout << "AutoPtr::assignment operator called.\n";
        if(this == &rhs) return *this;
        delete m_ptr;
        m_ptr = rhs.m_ptr;
        rhs.m_ptr = nullptr;
        return *this;
    }
    
    T* operator->() { return m_ptr; }
    T& operator *() { return *m_ptr; }
    bool isNull() { return nullptr == m_ptr; }
};
//////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////
// Virtual destructor
namespace virtualDestructor {
    class Base {
        public:
        Base() {
            cout << "Base ctr\n";
        }
        virtual ~Base() {
            cout << "Base dtr\n";
        }
        virtual void print() {
            cout << "printing from class Base\n";
        }
    };
    
    class D: public Base {
        public:
        D() {
            cout << "D ctr\n";
        }
        ~D() {
            cout << "D dtr\n";
        }
        
        virtual void print() override {
            cout << "printing from class D\n";
        }
    };
};
//////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////
// 1. Synchronization using mutexes
namespace mutexSync{
    int val = 0;
    int cnt = 0;
    mutex mtx;
    
    void add(int num) {
        lock_guard<mutex> lock(mtx);
        val += num;
        cnt++;
        cout << "thread: Value: " << val << " Counter: " << cnt << "\n"; 
        
    }
};
//////////////////////////////////////////////////////////

class MySingleton 
{
    static MySingleton* instance;
    static mutex mtx;
    MySingleton() {};
    MySingleton(const MySingleton& rhs) {};
    public:

    static MySingleton* getInstance() {
        if(instance == nullptr) {
            lock_guard<mutex> lock(mtx); // This will automatically unlock the lock once CS is finished.
            // mtx.lock(); 
            if(instance == nullptr)
                instance = new MySingleton();
            // mtx.unlock();
        }

        cout << "instance: " << instance << "\n";

        return instance;
    }

};

MySingleton* MySingleton::instance = nullptr;
mutex MySingleton::mtx;

void func1(int n) {
    for(int i = 0; i < n; ++i) {
        cout << "Hello from thread\n";
    }
}

int main()
{
    // int r = 5, c = 2;
    // int ** arr = create2DArray(r, c);
    // print2DArray(arr, r, c);
    // free2DArray(arr, r, c);
    // print2DArray(arr, r);
    
    //Hey, pointers have a finite size, no matter the indirection level!
    // std::cout << "sizeof(int*): " << sizeof(int*) << std::endl;
    // std::cout << "sizeof(int**): " << sizeof(int**) << std::endl;
    // std::cout << "sizeof(int***): " << sizeof(int***) << std::endl;

    // Cents c1 {10};
    // Cents c2 {20};
    // Cents c3 {30};
    
    // cout << c1 + c2 + c3;
    
    // useOfFunctionPointers();
    
    // use of vTable
    // vtable::Base b1;
    // vtable::D1 d1;
    // vtable::D2 d2;
    // b1.fun1();
    // b1.fun2();
    // d1.fun1();
    // d1.fun2();
    // d2.fun1();
    // d2.fun2();
    
    // // Upcasting/Implicit casting
    // pureVirtualFunctions::D1 d1;
    // pureVirtualFunctions::Base *bptr = &d1;
    
    // // Downcasting/Explicit casting
    // pureVirtualFunctions::Base* bPtr = new pureVirtualFunctions::Base();
    // bPtr->fun1();
    // pureVirtualFunctions::D1 *dptr = dynamic_cast<pureVirtualFunctions::D1*>(bPtr);
    // cout << dptr;
    // pureVirtualFunctions::D1 d1 {};
    // pureVirtualFunctions::Base & bref {d1};
    // pureVirtualFunctions::D1 & dref {dynamic_cast<pureVirtualFunctions::D1&>(bref)};
    

    // cout << boolalpha << isEqual("ABC", "ABC");
    
    // // const and Pointers
    // int a = 10;
    // int b = 60;
    // int *ptr1 = &a;
    // const int* ptr2 = &a;
    // cout << "ptr2: " << *ptr2 << "\n";
    
    // // ptr3 is a pointer variable points to const int, which can points to non-const ints too. 
    // const int* ptr3 = &a;
    // cout << "ptr3: " << *ptr3 << "\n";
    // a = 20; // allowed
    // // *ptr3 = 20; // not-allowed
    // cout << "ptr3: " << *ptr3 << "\n";
    
    
    // // const pointer
    // int* const ptr4 = &a;
    // cout << "ptr4: " << *ptr4 << "\n";
    // *ptr4 = 30;
    // cout << "ptr4: " << *ptr4 << "\n";
    // ptr4 = &b; // not-allowed as it is const pointer

    // Complex c1{10, 20};
    // Complex c2{c1};
    // Complex c3;
    // cout << "c3:" << c3;
    // c2 = c1 = c3;
    // cout << "c2:" << c2;
    // cout << c1 + c2;
    
    // MyString s1 {"ABC"};
    // cout << s1 << "\n";
    // MyString s2 {s1};
    // cout << s2 << "\n";
    // MyString s3 = "XYZ";
    // cout << "*" << s3 << "*" << "\n";
    
    // MyString s4;
    // s4 = s3;
    
    // // Overloading of new and delete operators
    // cout << sizeof(string); // 32
    // MyString * pStr = new MyString("ABCDE");
    // cout << *pStr << "\n";
    // delete pStr;
    
    // // Smart pointers
    // AutoPtr<Resource> ptr1 (new Resource());
    // cout << "ptr1: " << ptr1.isNull() << "\n"; 
    // AutoPtr<Resource> ptr2(ptr1);
    // cout << "ptr1: " << ptr1.isNull() << "\n"; 
    // cout << "ptr2: " << ptr2.isNull() << "\n"; 
    // ptr1->sayHi();
    
    // using namespace virtualDestructor;
    // Base* bptr = new D();
    // bptr->print();
    // delete bptr;
    
    //     using namespace mutexSync;
    // 	thread t1(add, 300);
    // 	thread t2(add, 600);
        
    // 	t1.join();
    // 	t2.join();
        
    // 	cout << "After addition : " << val << endl;

    // // Vector size and capacity comparison
    // vector<int> v;
    // cout << "size: " << v.size() << "\n";
    // cout << "capacity: " << v.capacity() << "\n";
    // v.push_back(10);
    // cout << "size: " << v.size() << "\n";
    // cout << "capacity: " << v.capacity() << "\n";
    // v.push_back(10);
    // cout << "size: " << v.size() << "\n";
    // cout << "capacity: " << v.capacity() << "\n";
    // v.push_back(10);
    // cout << "size: " << v.size() << "\n";
    // cout << "capacity: " << v.capacity() << "\n";
    // v.push_back(10);
    // cout << "size: " << v.size() << "\n";
    // cout << "capacity: " << v.capacity() << "\n";
    // v.push_back(10);
    // cout << "size: " << v.size() << "\n";
    // cout << "capacity: " << v.capacity() << "\n";

    return 0;
}
