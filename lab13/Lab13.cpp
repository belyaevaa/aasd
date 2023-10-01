#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

//Лабораторная работа по хеш-таблицам с реализацией по списку
// Основная идея: имеем ключи, полученные через хеш-функцию, которые всегда одинаковые для входных данных
//Коллизию решаем тем способом, что у нас всё хранится в списке, т.е на одну позицию можно записать несколько строк
//Например, если запустить поиск по слову is, то найдет только is, слова si не найдет

class HashTable
{
    int capacity;
    list<vector<char>>* table;
    vector<int> keys;
public:
    HashTable(int V);
    void insertItem(int key, vector<char> data);
    int search(string text);
    void deleteItem(int key, vector<char> data = {});
    int checkPrime(int n)
    {
        int i;
        if (n == 1 || n == 0)
        {
            return 0;
        }
        for (i = 2; i < n / 2; i++)
        {
            if (n % i == 0)
            {
                return 0;
            }
        }
        return 1;
    }
    int getPrime(int n)
    {
        if (n % 2 == 0)
        {
            n++;
        }
        while (!checkPrime(n))
        {
            n += 2;
        }
        return n;
    }
    int hashFunction(int key)
    {
        return (key % capacity);
    }
    void displayHash();
};
HashTable::HashTable(int c)
{
    int size = getPrime(c);
    this->capacity = size;
    table = new list<vector<char>>[size];
}
void HashTable::insertItem(int key, vector<char> data)
{
    int index = hashFunction(key);
    vector<int>::iterator findIter = find(keys.begin(), keys.end(), index);
    if (findIter == keys.end()) {
        keys.push_back(index);
    }
    table[index].push_back(data);
}
void HashTable::deleteItem(int key, vector<char> data)
{
    int index = hashFunction(key);
    if (table[index].begin() != table[index].end()) {}
}
void HashTable::displayHash()
{
    list<vector<char>>::iterator it = table->begin();
    for (int j = 0; j < keys.size(); j++) {
        cout << "[" << keys[j] << "]" << endl;
        cout << "[" << endl;
        for (auto n : table[keys[j]]) {
            for (auto k : n) {
                cout << k;
            }
            cout << endl;
        }
        cout << ']' << endl;
    }
}
int HashTable::search(string text)
{
    vector<char> val;
    for (int i = 0; i <= text.size(); i++) {
        if ((int)text[i] != 0) {
            val.push_back(text[i]);
        }
    }
    int tempHash = 0;
    for (char i : val) {
        tempHash += (int)i;
    }
    int index = hashFunction(tempHash);
    int counter = 0;
    for (auto n : table[index]) {
        if (n == val) {
            counter++;
        }
    }
    return counter;
}
int main()
{
    string text;
    int preHash = 0;
    HashTable h(1000);
    vector<char> word = {};
    vector<char> wordToFind = {};
    getline(cin, text, '\n');
    for (int i = 0; i <= text.size(); i++) {
        if (text[i] != ' ' && (int)text[i] != 0) {
            preHash += (int)text[i];
            word.push_back(text[i]);
        }
        else {
            h.insertItem(h.hashFunction(preHash), word);
            word.clear();
            preHash = 0;
        }
    }
    cout << h.search("is") << endl;
    h.displayHash();

}