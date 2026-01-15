#include <iostream>
#include <vector>
#include "../Rasberrysoup-src/include/Rasberrysoup/Rasberrysoup.hpp" // 로컬 경로 직접 참조 테스트

int main() {
    std::cout << "--- Rasberrysoup Math Test ---" << std::endl;
    
    // 1. 황금비 상수 확인
    std::cout << "Golden Ratio: " << rasberry::gold << std::endl;

    // 2. 이차방정식 해 구하기 (x^2 - 5x + 6 = 0 -> x=2, 3)
    auto roots = rasberry::quad(1, -5, 6);
    std::cout << "Roots of x^2 - 5x + 6: ";
    for(double r : roots) std::cout << r << " ";
    std::cout << std::endl;

    // 3. 거리 계산 (0,0) ~ (3,4) -> 5
    std::cout << "Distance (0,0) to (3,4): " << rasberry::dist(0, 0, 3, 4) << std::endl;

    std::cout << "-----------------------------" << std::endl;
    std::cout << "Test Result: SUCCESS" << std::endl;
    
    return 0;
}
