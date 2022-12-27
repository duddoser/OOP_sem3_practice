// группа КМБО-01-21
// Листова Анастасия
// Вариант 16:
// Пациенты
// key - номер карты, value - группа крови
using namespace std;

#include <iostream>
#include <map>
#include <vector>
#include <set>

// 2.1

template <class K, class V>
typename map<K, V>::iterator findByKey(map<K, V>& tree, K key)
{
    return tree.find(key);
}

template <class K, class V>
typename map<K, V>::iterator findByValue(map<K, V>& tree, V value)
{
    typename map<K, V>::iterator p = tree.begin();
    while (p != tree.end())
    {
        if (p->second == value)
            break;
        ++p;
    }
    return p;
}

template <class K, class V>
void printTree(map<K, V>& tree)
{
    typename map<K, V>::iterator p = tree.begin();
    while (p != tree.end())
    {
        cout << "key: " << p->first << ", value: " << p->second << "\n";
        ++p;
    }
}

template <class K, class V>
map<K, V> filter(map<K, V>& tree, V threshold)
{
    map<K, V> result;
    typename map<K, V>::iterator p = tree.begin();
    while (p != tree.end())
    {
        if (p->second > threshold)
            result.insert({ p->first, p->second });
        ++p;
    }
    return result;
}

template <class K, class V>
pair<typename map<K, V>::iterator, bool> insert(map<K, V>& tree, pair<K, V> element)
{
    if (tree.find(element.first) != tree.end())
        throw invalid_argument("Key already exists!");
    return tree.insert(element);
}

template <class K, class V>
vector<V> uniqueTreeValues(map<K, V>& tree)
{
    vector<V> result;
    set<V> pom;
    typename map<K, V>::iterator p = tree.begin();
    while (p != tree.end())
    {
        if (pom.insert(p->second).second == true)
            result.push_back(p->second);
        ++p;
    }

    return result;
}

// 2.2

template <class K, class V>
vector<V> findByKey(multimap<K, V>& tree, K key)
{
    vector<V> result;

    typename multimap<K, V>::iterator find_p = tree.find(key);
    typename multimap<K, V>::iterator p = find_p;

    result.push_back(p->second);

    while (p++ != tree.end())
    {
        if (p->first != find_p->first)
            break;
        result.push_back(p->second);
    }

    return result;
}

template <class K, class V>
typename multimap<K, V>::iterator findByValue(multimap<K, V>& tree, V value)
{
    typename multimap<K, V>::iterator p = tree.begin();
    while (p != tree.end())
    {
        if (p->second == value)
            break;
        ++p;
    }
    return p;
}

template <class K, class V>
void printTree(multimap<K, V>& tree)
{
    typename multimap<K, V>::iterator p = tree.begin();
    while (p != tree.end())
    {
        cout << "key: " << p->first << ", value: " << p->second << "\n";
        ++p;
    }
}

template <class K, class V>
multimap<K, V> filter(multimap<K, V>& tree, V threshold)
{
    multimap<K, V> result;
    typename multimap<K, V>::iterator p = tree.begin();
    while (p != tree.end())
    {
        if (p->second > threshold)
            result.insert({ p->first, p->second });
        ++p;
    }
    return result;
}

template <class K, class V>
typename multimap<K, V>::iterator insert(multimap<K, V>& tree, pair<K, V> element)
{
    return tree.insert({ element.first, element.second });
}

template <class K, class V>
vector<V> uniqueTreeValues(multimap<K, V>& tree)
{
    vector<V> result;
    set<V> pom;
    typename multimap<K, V>::iterator p = tree.begin();
    while (p != tree.end())
    {
        if (pom.insert(p->second).second == true)
            result.push_back(p->second);
        ++p;
    }

    return result;
}

template <class K, class V>
multimap<K, V> getElementsByKey(multimap<K, V>& tree, K key)
{
    multimap<K, V> result;
    typename multimap<K, V>::iterator p = tree.find(key);
    while (p != tree.end() && p->first == key)
    {
        result.insert({ p->first, p->second });
        ++p;
    }
    return result;
}

// Пациенты

void fillMap(map<int, int>& tree)
{
    insert(tree, { 123, 2 });
    insert(tree, { 437, 3 });
    insert(tree, { 120, 1 });
    insert(tree, { 258, 4 });
}

void fillMultiMap(multimap<int, int>& tree)
{
    insert(tree, { 123, 2 });
    insert(tree, { 437, 3 });
    insert(tree, { 120, 1 });
    insert(tree, { 258, 4 });
    insert(tree, { 111, 3 });
    insert(tree, { 045, 1 });
    insert(tree, { 605, 3 });
    insert(tree, { 437, 2 });
    insert(tree, { 111, 4 });
    insert(tree, { 437, 1 });
}

int main()
{
    // map
    map<int, int> mapPatients;
    fillMap(mapPatients);

    cout << findByKey<int, int>(mapPatients, 437)->second << endl;
    cout << findByValue<int, int>(mapPatients, 1)->first << endl;

    cout << endl;

    printTree(mapPatients);

    cout << endl;

    map<int, int> f_mapPatients(filter(mapPatients, 1));
    printTree(f_mapPatients);

    cout << endl;

    vector<int> uniq_MapValues(uniqueTreeValues(mapPatients));
    for (int v : uniq_MapValues)
        cout << v << " " << endl;

    cout << endl;

    try
    {
        insert(mapPatients, { 258, 3 });
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << endl;
    }

    cout << endl;

    // multimap

    multimap<int, int> multiPatients;

    fillMultiMap(multiPatients);

    vector<int> vec(findByKey<int, int>(multiPatients, 111));
    for (auto i : vec)
        cout << i << " " << endl;

    cout << findByValue<int, int>(multiPatients, 2)->first << endl;

    cout << endl;

    printTree(multiPatients);

    cout << endl;

    multimap<int, int> f_multiPatients(filter(multiPatients, 2));
    printTree(f_multiPatients);

    cout << endl;

    vector<int> uniq_MultiMapValues(uniqueTreeValues(multiPatients));
    for (int v : uniq_MultiMapValues)
        cout << v << " " << endl;

    cout << endl;

    multimap<int, int> similarKeyElements(getElementsByKey<int, int>(multiPatients, 437));
    printTree(similarKeyElements);
}