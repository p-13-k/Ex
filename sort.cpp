#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
double findMedian(vector<int>& numbers) {
    sort(numbers.begin(), numbers.end()); 
    int n = numbers.size();
    return n % 2 == 0 ? (numbers[n / 2 - 1] + numbers[n / 2]) / 2.0 : numbers[n / 2];
}
int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    if (n <= 0) {
        cout << "Number of elements must be greater than 0." << endl;
        return 1;
    }

    vector<int> numbers(n);
    cout << "Enter the numbers: ";
    for (int& num : numbers) cin >> num;

    cout << "Median: " << findMedian(numbers) << endl;
    return 0;
}
