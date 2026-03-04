#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <list>
#include <set>
#include <map>
#include <iterator>

int main() {
    // Example 1: Using std::sort with std::vector
    std::cout << "=== Using std::sort with std::vector ===" << std::endl;
    std::vector<int> vec = {5, 3, 8, 1, 4};

    // Sort the vector in ascending order
    std::sort(vec.begin(), vec.end());

    std::cout << "Sorted vector: ";
    for (const auto& val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Example 2: Using std::find with std::vector
    std::cout << "\n=== Using std::find with std::vector ===" << std::endl;
    auto it = std::find(vec.begin(), vec.end(), 4);

    if (it != vec.end()) {
        std::cout << "Found 4 at position: " << std::distance(vec.begin(), it) << std::endl;
    } else {
        std::cout << "4 not found in the vector" << std::endl;
    }

    // Example 3: Using std::accumulate with std::vector
    std::cout << "\n=== Using std::accumulate with std::vector ===" << std::endl;
    int sum = std::accumulate(vec.begin(), vec.end(), 0);

    std::cout << "Sum of vector elements: " << sum << std::endl;

    // Example 4: Using std::copy with std::list
    std::cout << "\n=== Using std::copy with std::list ===" << std::endl;
    std::list<int> lst = {1, 2, 3, 4, 5};
    std::vector<int> copyVec(lst.size());

    std::copy(lst.begin(), lst.end(), copyVec.begin());

    std::cout << "Copied vector: ";
    for (const auto& val : copyVec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Example 5: Using std::count with std::set
    std::cout << "\n=== Using std::count with std::set ===" << std::endl;
    std::set<int> st = {1, 2, 3, 4, 5};

    int count = std::count(st.begin(), st.end(), 3);

    std::cout << "Count of 3 in the set: " << count << std::endl;

    // Example 6: Using std::transform with std::vector
    std::cout << "\n=== Using std::transform with std::vector ===" << std::endl;
    std::vector<int> transformVec = {1, 2, 3, 4, 5};

    std::transform(transformVec.begin(), transformVec.end(), transformVec.begin(),
                   [](int x) { return x * x; }); // Square each element

    std::cout << "Transformed vector (squared values): ";
    for (const auto& val : transformVec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Example 7: Using std::set_intersection with std::set
    std::cout << "\n=== Using std::set_intersection with std::set ===" << std::endl;
    std::set<int> set1 = {1, 2, 3, 4, 5};
    std::set<int> set2 = {4, 5, 6, 7, 8};
    std::vector<int> intersectionVec;

    std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(),
                          std::back_inserter(intersectionVec));

    std::cout << "Intersection of sets: ";
    for (const auto& val : intersectionVec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Example 8: Using std::for_each with std::map
    std::cout << "\n=== Using std::for_each with std::map ===" << std::endl;
    std::map<int, std::string> mp = {{1, "one"}, {2, "two"}, {3, "three"}};

    std::cout << "Map elements: ";
    std::for_each(mp.begin(), mp.end(),
                  [](const std::pair<const int, std::string>& p) {
                      std::cout << "[" << p.first << ": " << p.second << "] ";
                  });
    std::cout << std::endl;

    return 0;
}
