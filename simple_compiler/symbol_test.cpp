#include "Symbol.h"

int main() {
    SymbolTableClass st;
    //Test AddEntry
    st.AddEntry("Banana");
    st.AddEntry("Apple");
    st.AddEntry("Grape");
    st.AddEntry("Kiwi");

    //Test SetValue
    st.SetValue("Banana", 2);
    st.SetValue("Apple", 3);
    st.SetValue("Grape", 1);

    //Test GetIndex
    std::cout << "Index of Apple " << st.GetIndex("Apple") << std::endl;
    std::cout << "Should be 1" << std::endl;

    std::cout << "Failure: " << st.GetIndex("Blueberry") << std::endl;

    //Test GetCount
    std::cout << "Size of Variables " << st.GetCount() << std::endl;

    //Test GetValue
    std::cout << "Apple should be 3" << std::endl;
    std::cout << st.GetValue("Apple") << std::endl;

    return 0;
}