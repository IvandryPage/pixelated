#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>

void stlMap() {
  std::map<std::string, float> f_map;  // sorted with fast lookups
  std::unordered_map<std::string, float>
      s_map;  // faster key lookpus but don't care about order -- Hash Map

  // if sorted key is needed, use map instead of unordered map

  f_map["Ivandry"] = 3.95f;
  f_map["Eva"] = 3.90f;
  f_map["Vavo"] = 4.0f;

  std::cout << "\nFROM FOREACH";
  for (auto& pair : f_map) {
    std::cout << "\nNama: " << pair.first << "\nIPK : " << pair.second << '\n';
  }

  std::cout << "\nFROM [name, ipk] structured binding?";
  for (auto& [name, ipk] :
       f_map) {  // [name, ipk] is structured binding, instead of pair.first and
                 // pair.second, it gives more readable name for each key-pair
                 // value
    std::cout << "\nNama: " << name << "\nIPK : " << ipk << '\n';
  }
}

void stlSet() {
  std::set<int> player_numbers{
      8, 4, 3, 9, 10, 11, 15};  // stores unique element in sorted order
  std::unordered_set<int> college_numbers{105, 1023, 234, 5872, 32587, 123};

  player_numbers.insert(10);  // ignored because 10 is already in the set, same
                              // things happens when using unordered_set
  player_numbers.insert(0);

  std::cout << "\nPlayer_numbers Set: ";
  for (int num : player_numbers) {
    std::cout << num << " ";
  }

  std::cout << "\nCollege_numbers unordered set:\n";
  for (int num : college_numbers) {
    std::cout << num << " ";
  }
}

void stlSequence() {
  std::deque<int> dq{
      1, 2, 3};  // double ended queue front and back fast insert/delete
  std::list<int> numbers{1, 2, 3};  // doubly linked list used when need
                                    // frequent insert/remove in the middle
  numbers.push_front(0);
  dq.push_front(5);
  dq.push_back(0);

  std::cout << "STL Deque : ";
  for (int num : dq) {
    std::cout << num << " ";
  }
}

void stlInOut() {
  std::stack<int> stack_var;  // Last in, First out
  stack_var.push(1);
  stack_var.push(2);
  stack_var.push(3);

  std::cout << "\nStack: ";
  while (!stack_var.empty()) {
    std::cout << stack_var.top() << " ";
    stack_var.pop();
  }

  std::queue<int> queue_var;  // First in, First out
  queue_var.push(4);
  queue_var.push(2);
  queue_var.push(3);

  std::cout << "\nQueue: ";
  while (!queue_var.empty()) {
    std::cout << queue_var.front() << " ";
    queue_var.pop();
  }

  std::priority_queue<int> priority;  // Max Elements first descending order
  priority.push(5);
  priority.push(50);
  priority.push(15);
  priority.push(25);
  priority.push(125);

  std::cout << "\nPriority_Queue: ";
  while (!priority.empty()) {
    std::cout << priority.top() << " ";
    priority.pop();
  }
  std::cout << '\n';
}

void stlTuple() {
  std::tuple<int, std::string, double> person(21, "Ivan", 3.95f);
  std::cout << std::get<0>(person) << " " << std::get<1>(person) << " "
            << std::get<2>(person) << '\n';
}

int main() {
  stlInOut();
  return 0;
}