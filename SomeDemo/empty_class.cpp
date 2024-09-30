#include<memory>
#include<string>
#include<vector>
#include<iostream>
#include<algorithm>
#include<list>
#include<set>
#include<unordered_set>
using std::string;
using std::wstring;
using std::unique_ptr;
using std::vector;
using std::make_unique;
using std::for_each;
class Song 
{
private:
    int v1;
    int v2;

public:
    Song& set_v1(const int&& v) {
        v1 = v;
        return *this;
    }

    Song& set_v2(const int&& v) {
        v2 = v;
        return *this;
    }

    int get_v1() const {
        return v1;
    }

    int get_v2() const {
        return v2;
    }

    Song() {}

    Song(const int& v1, const int& v2): v1(v1), v2(v2) {}
};



int main() {
    /*
unique_ptr 不共享它的指针：
    它无法复制到其他 unique_ptr，
    无法通过值传递到函数 （因为会产生复制），
    也无法用于需要副本的任何 C++ 标准库算法。 

只能移动 unique_ptr。
这意味着，内存资源所有权将转移到另一 unique_ptr，并且原始 unique_ptr 不再拥有此资源。
    */
    using std::cout;
    using std::wcout;
    using std::endl;

    Song s1;
    s1.set_v1(1).set_v2(2);

    Song s2 = s1; // 会自动拷贝所有的field；赋值运算符

    s1 = Song(s2); // copy constructor
    cout << endl << endl;

    // 两行的输出是一样的
    cout << s1.get_v1() << " " << s1.get_v2() << endl;
    cout << s2.get_v1() << " " << s2.get_v2() << endl;
    return 0;

    using std::list;
    list<int> ls = list<int>();
    
    auto iter = ls.begin();
    // iter += 4; // nope
    ls.erase(iter++);
    *iter = 5;

    using std::unordered_set;
    unordered_set<int> st;
    st.erase(5);
    

    using std::set;
    set<Song> s;
    s.emplace(1, 2);


}