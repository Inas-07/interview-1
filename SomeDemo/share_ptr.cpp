#include<memory>
#include<iostream>
#include<thread>
#include<mutex>

using namespace std;

class B;
class A
{
public:
    weak_ptr<B> pb_;
    ~A()
    {
        cout << "A delete\n";
    }
};

class B
{
public:
    weak_ptr<A> pa_;
    ~B()
    {
        cout << "B delete\n";
    }
};

shared_ptr<long> global_instance = make_shared<long>(0);
mutex g_i_mutex; // 当前编译器里没有……

void thread_fcn()
{
    std::lock_guard<std::mutex> lock(g_i_mutex); // shared_ptr在多线程下，发生写时，同样需要加锁
    shared_ptr<long> local = global_instance;
    for (int i = 0; i < 100000000; i++)
    {
        *global_instance = *global_instance + 1;
    }
}

int main()
{
    shared_ptr<B> pb(new B());
    shared_ptr<A> pa(new A());
    pb->pa_ = pa; // 若有shared_ptr的循环引用，就会有“智能指针的内存泄漏”（面试可能会这么问
    pa->pb_ = pb; // 上面只需要A B中的其中1个（而不需要2个）改为weak_ptr即可；
                  // 实际应用中，在不导致循环引用的基础上，用weak还是shared依然取决于实际需求，不能直接说“全都用weak_ptr就行”
    cout << endl;
    cout << pb.use_count() << endl;
    cout << pa.use_count() << endl;

    auto pb2 = pa->pb_.lock(); // 通过lock得到一个shared_ptr；pb2析构时，pb的引用计数器自动减一（也就是说，要用weak_ptr指向的数据的话，直接lock()即可，没有（也不需要）手动'unlock'

    return 0;
}