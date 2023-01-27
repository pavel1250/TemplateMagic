#include <iostream>
#include <utility>
#include <array>

template<typename TOWNER>
class EmptyClass_t
{
public:
    EmptyClass_t(char ch, TOWNER* owner) : mCh(ch), mOwner(owner) {}
    EmptyClass_t(EmptyClass_t& other) : EmptyClass_t(other.mCh, other.mOwner) {}
    EmptyClass_t(char ch, TOWNER& owner) : mCh(ch), mOwner(owner) {}

    char Ch() { return mCh; }
private:
    const char mCh;
    TOWNER* mOwner = nullptr;
};

template<size_t SIZE>
class MyClass_t
{
    using Self_t = MyClass_t;
    using array_type = EmptyClass_t<Self_t>;

public:
    MyClass_t() : MyClass_t(std::make_index_sequence<SIZE>()) {}

    array_type* begin() { return ObjectArray; }
    array_type* end() { return ObjectArray + SIZE; }

private:
    template<std::size_t ...Is>
    constexpr MyClass_t(const std::index_sequence<Is...>&) : ObjectArray{ EmptyClass_t(static_cast<char>(0x30 + Is), this) ... } {}

    array_type ObjectArray[SIZE];
};

MyClass_t<10> A;

int main()
{
    for (auto&& it : A) std::cout << it.Ch();
    std::cout << std::endl;

    return 0;
}