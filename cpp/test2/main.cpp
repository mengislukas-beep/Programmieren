#include <iostream>
#include "akskdatest.h"
#include "Person.h"




int main() {

    std::string testString = "madam";
    bool result = isPalindrome(testString);
    print(result);


    Person person("Alice", 300);
    person.vorstellen();

    return 0;
}