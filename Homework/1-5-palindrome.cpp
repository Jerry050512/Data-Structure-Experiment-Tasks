#include <iostream>
#include <string>
#include <cctype> // 用于tolower函数

using namespace std;

bool isPalindrome(const string& str) {
    // 创建两个指针,分别指向字符串的开头和结尾
    int start = 0;
    int end = str.length() - 1;

    // 循环直到两个指针相遇
    while (start < end) {
        // 跳过非字母字符
        while (start < end && !isalnum(str[start])) {
            start++;
        }
        while (start < end && !isalnum(str[end])) {
            end--;
        }

        // 检查两个字符是否相同(忽略大小写)
        if (tolower(str[start]) != tolower(str[end])) {
            return false; // 如果不同,则不是回文
        }

        start++;
        end--;
    }

    return true; // 如果两个指针相遇且所有字符都相同,则是回文
}

int main() {
    string str1 = "A man a plan a canal Panama";
    string str2 = "Hello, World!";

    cout << str1 << " is " << (isPalindrome(str1) ? "" : "not ") << "a palindrome." << endl;
    cout << str2 << " is " << (isPalindrome(str2) ? "" : "not ") << "a palindrome." << endl;

    return 0;
}