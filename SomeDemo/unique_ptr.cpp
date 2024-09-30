#include<memory>
#include<string>
#include<vector>
#include<iostream>
#include<algorithm>
using std::string;
using std::wstring;
using std::unique_ptr;
using std::vector;
using std::make_unique;
using std::for_each;
class Song 
{

public:
    wstring artist;
    wstring title;

    Song() {}
    Song(const wstring& artist, const wstring& title): artist(artist), title(title) {}

    
};

unique_ptr<Song> SongFactory(const wstring& artist, const wstring& title)
{
    // Implicit move operation into the variable that stores the result.
    return make_unique<Song>(artist, title);
}

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

    // Create a new unique_ptr with a new object.
    auto song = make_unique<Song>(L"Mr. Children", L"Namonaki Uta");

    // Use the unique_ptr.
    vector<wstring> titles = { song->title };

    // Move raw pointer from one unique_ptr to another.
    unique_ptr<Song> song2 = std::move(song);

    // wcout << song->artist << L"\n"; // seg fault
    wcout << song2->artist << L"\n";

    // Obtain unique_ptr from function that returns by value.
    auto song3 = SongFactory(L"Michael Jackson", L"Beat It");

    // delete song2.get(); // 如果自己delete掉指针，unique_ptr在析构时就会寄掉（合理


    return 0;
}