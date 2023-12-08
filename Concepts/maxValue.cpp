#include <iostream>

template<typename T>
concept IsPointer = requires(T p){
        *p;
        {p < p} -> std::convertible_to<bool>;
        p == nullptr;
    };

auto maxValue(auto a, auto b){
    return b < a ? a : b;
}

auto maxValue(IsPointer auto a, IsPointer auto b)
requires std::three_way_comparable_with<decltype(*a), decltype(*b)>
{
    return maxValue(*a, *b);
}

int main(){
    int x{42};
    int y{77};
    
    std::cout << maxValue(x, y) << '\n';
    std::cout << maxValue(&x, &y) << '\n';
    
    int *xp{&x};
    int *yp{&y};
    
    std::cout << maxValue(&xp, &yp) << '\n';
    
    double d{49.9};
    std::cout << maxValue(xp, &d) << '\n';
    return 0;    
}