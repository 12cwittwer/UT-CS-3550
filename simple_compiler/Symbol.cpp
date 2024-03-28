#include "Symbol.h"

SymbolTableClass::SymbolTableClass() { }


bool SymbolTableClass::Exists(const std::string & s) {
    bool exists = false;
    for (unsigned int i = 0; i < mVariables.size(); i++) {
        if (s == mVariables[i].mLabel) {
            exists = true;
        }
    }
    return exists;
}

void SymbolTableClass::AddEntry(const std::string & s) {
    if (Exists(s)) {
        std::cout << "Entry could not be added -- " <<  "Variable '" << s << "' already exists" << std::endl;
        exit(1);
    } else {
        Variable v;
        v.mLabel = s;
        mVariables.push_back(v);
    }
}

int SymbolTableClass::GetValue(const std::string & s) {
    int value;
    bool found = false;

    for (unsigned int i = 0; i < mVariables.size(); i++) {
        if (mVariables[i].mLabel == s) {
            found = true;
            value = mVariables[i].mValue;
        }
    }
    if (found) {
        return value;
    } else {
        std::cout << "Could not return value -- " << "No variable with the label '" << s <<"'" << std::endl;
        exit(1);
    }
}

void SymbolTableClass::SetValue(const std::string & s, int v) {
    bool found = false;

    for (unsigned int i = 0; i < mVariables.size(); i++) {
        if (mVariables[i].mLabel == s) {
            found = true;
            mVariables[i].mValue = v;
        }
    }
    if (!found) {
        std::cout << "Could not set value -- " << "No variable with the label '" << s <<"'" << std::endl;
        exit(1);
    }
}

int SymbolTableClass::GetIndex(const std::string & s) {
    bool found = false;
    unsigned int index = 0;

    for (unsigned int i = 0; i < mVariables.size(); i++) {
        if (mVariables[i].mLabel == s) {
            found = true;
            index = i;
        }
    }
    if (!found) {
        return -1;
    } else {
        return index;
    }
}

size_t SymbolTableClass::GetCount() {
    return mVariables.size();
}
    // returns the current number of variables in the symbol
    // table.  