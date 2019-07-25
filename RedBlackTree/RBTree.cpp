#include <iostream>

enum Color {
  RED,
  BLACK,
};

template <typename TKey, typename TData>
struct Node {

  Node(const TKey& key, const TData& data);
  ~Node();

  TKey key_;
  TData data_;
  Color color_;
  Node<TKey, TData> *left_, *right_;
};


template <typename TKey, typename TData>
class RBTree {
public:

  RBTree();
  ~RBTree();

  Node<TKey, TData>& find(const TKey& key);

  void insert(const TKey& key, const TData& data);
  void remove(const TKey& key);

  void left_rotate();
  void right_rotate();

  friend std::ostream& operator << (std::ostream&, const RBTree<TKey, TData>&);

private:
  Node<TKey, TData> *root_;

  void insert_fix();
  void delete_fix();

};

int main() {

  
}
