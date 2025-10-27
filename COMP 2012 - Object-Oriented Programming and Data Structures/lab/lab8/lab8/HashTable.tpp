#include"HashTable.h"
/*
  Construtor:
  - It dynamically allocates an array of Entry objects in size table_size.
  - It also initializes all the other data members using the parameters.
*/
// TODO #1: --- BEGIN ---
template<typename K, typename V>
HashTable<K,V>::HashTable(unsigned int table_size, 
              unsigned int(*hash_func)(const K&), 
              CollisionResolutionAlgo algo, 
              unsigned int(*hash_func2)(const K&))
              : table_size(table_size), algo(algo)
{
  this->table = new Entry<K,V>[this->table_size];
  this->hash_func = hash_func1;
  this->hash_func2 = hash_func2;
}
// TODO #1: --- END ---


/*
   Destructor:
   - It deallocates all the dynamically allocated memory to avoid memory leaks.
*/
// TODO #2: --- BEGIN ---
template<typename K, typename V>
HashTable<K,V>:: ~HashTable()
{
  if(this->table != nullptr)
  delete [] this->table;
}
// TODO #2: --- END ---


/*
  offset function (equivalent to f in the lecture notes):
  - i: Represents the number of collisions
  - key: Represents the key
  - It returns the offset from the home location (i.e., hash value computed using hash_value1) 
    according to the current collision resolution algorithm, algo.
*/
// TODO #3: --- BEGIN ---
template<typename K, typename V>
unsigned int HashTable<K,V>::offset(int i, const K& key)
{
  if(this->algo == LINEAR)
  {
    return i;
  }
  else if(this->algo == QUADRATIC)
  {
    return i*i;
  }
  else
  {
    return i * this->hash_func2(key);
  }
}
// TODO #3: --- END ---


/*
  insert function
  - key: Represents the key
  - value: Represents the value
  - It inserts the key-value pair to the hash table, and returns the number of probes
    for the insertion of key-value pair. 
  - If the key-value pair cannot be inserted
    to the hash table due to exceeding the maximum number of probes, i.e., table_size * 2,
    the return value should be table_size * 2.
*/
template <typename K, typename V>
unsigned int HashTable<K,V>::insert(const K& key, const V& value) {
  // Given
  unsigned int index = hash_func(key); // Compute the home location
  unsigned int i = 1; // The number of probes
  unsigned j = index; // The next probe location

  // Given
  while(i < table_size * 2) { // Assume the number of probes should be less than 2*table_size
    cout << "Probe: " << j << ", ";

    // TODO #4: --- BEGIN ---
    if(this->table[j].status == EMPTY)
    {
      this->table[j].key = key;
      this->table[j].value = value;
      this->table[j].status = ACTIVE;
      return i;
    }
    if(this->table[j].key == key)
    {
      this->table[j].status = ACTIVE;
      return i;
    }
    // TODO #4: --- END ---

    j = (index + offset(i, key)) % table_size; // Compute the next probe location
    ++i; // Number of probes + 1
  }
  cerr << "Over the limit" << endl;
  return i;
}

/*
  remove function
  - key: Represents the key
  - It performs lazy deletion for the key-value pair, and returns the number of probes
    for the removal of key-value pair.
  - If the key-value pair cannot be removed from the hash table due to exceeding the
    maximum number of probes, i.e., table_size * 2, the return value should be 
    table_size * 2.
*/
template <typename K, typename V>
unsigned int HashTable<K,V>::remove(const K& key) {
  // Given
  unsigned int index = hash_func(key); // Compute the home location
  unsigned int i = 1;     // The number of probes
  unsigned int j = index; // The next probe location

  // Given
  while(i < table_size * 2) { // Assume the number of probes should be less than 2*table_size
    cout << "Probe: " << j << ", ";

    // TODO #5: --- BEGIN ---     
    if(this->table[j].key == key && this->table[j].status == ACTIVE)
    {
      this->table[j].status = DELETE;
      return i;
    }
    if(this->table[j].status == EMPTY)
    {
      break;
    }
    // TODO #5: --- END --- 

    j = (index + offset(i, key)) % table_size; // Compute the next probe location
    ++i; // Number of probes + 1
  }
  cerr << "Key not found" << endl;
  return i;
}

/*
  find function
  - key: Represents the key
  - value: The pointer to the value of the key if the key is found, otherwise it is nullptr.
  - It returns the number of probes for the searching of key-value pair.
  - If the key-value pair cannot be found due to exceeding the maximum number of
    probes, i.e., table_size * 2, the return value should be table_size * 2.
*/
template <typename K, typename V>
unsigned int HashTable<K,V>::find(const K& key, V*& v) {
  // Given
  unsigned int index = hash_func(key); // Compute the home location
  unsigned int i = 1;     // The number of probes
  unsigned int j = index; // The next probe location

  // Given
  while(i < table_size * 2) { // Assume the number of probes should be less than 2*table_size
    cout << "Probe: " << j << ", ";

    // TODO #6: --- BEGIN ---
    if(this->table[j].key == key )
    {
      if(this->table[j].status == ACTIVE)
      {
        v = &(this->table[j].value);
        return i;
      }
      else
      {
        break;
      }
    }
    if(this->table[j].status == EMPTY)
    {
      break;
    }
    // TODO #6: --- END ---
    
    j = (index + offset(i, key)) % table_size; // Compute the next probe location
    ++i; // Number of probes + 1
  }
  // Key not in the table, set v to nullptr
  v = nullptr;
  return i;
}
