#include <iostream>;
#include <string>;
using std::string;

typedef string node_type;

struct ListNode{
    node_type value;
    ListNode* next;
};

struct List {
    ListNode* first;
    ListNode* last;
    int len;
};

ListNode* create_node(node_type value) {
    ListNode* node = new ListNode;
    node->value = value;
    return node;
}

List* create_empty(){
    List* empty_list = new List;
    empty_list->first = nullptr;
    empty_list->last = nullptr;
    empty_list->len = 0;
    return empty_list;
}

void add2end(List* listik, node_type val) {
    ListNode* new_node = create_node(val);
    if (listik->len == 0) {
        listik->first = new_node;
        listik->last = new_node;
        listik->len = 1;
    } else {
        listik->last->next = new_node;
        listik->last = new_node;
        listik->len++;
    }
}

void remove_by_value(List* listik, node_type val) {
    if (listik->first->value == val) {
        ListNode* old_element = listik->first;
        listik->first = listik->first->next;
        if (listik->len == 1) {
            listik->last = nullptr;
        }
        listik->len--;
        delete old_element;
    } else {
        ListNode* current = listik->first;
        for (int i = 0; i < listik->len - 1; ++i) {
            if (current->next->value == val) {
                ListNode* old_element = current->next;
                current->next = current->next->next;
                if (i == listik->len - 2) {
                    listik->last = current;
                }
                listik->len--;
                delete old_element;
                break;
            }
        }
    }
}

bool find_by_value(List* listik, node_type val) {
    if (listik->first->value == val) {
       return true;
        } else {
        ListNode* current = listik->first;
        if ((current->next->value == val) && (current != nullptr)) {
                return true;
            }
            current = current->next;
            if (current = nullptr) {
                return false;
                }
}
}

void print_list(List* listik) {
    ListNode* current = listik->first;
    for (int i = 0; i < listik->len; ++i) {
        std::cout << current->value << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

int hash_function(int prime, string s, int table_len) {
    int hash = 0;
    for (int i = 0; i < s.size(); i++) {
        hash = (prime*hash + s[i]) % table_len;
    }
    return hash;
}

class hash_table {
public:
    List* a;
    int len;
    int size;
};

hash_table add(hash_table table, string s) {
    int hash = hash_function(59, s, table.size);
    add2end(&table.a[hash], s);
    table.len++;
    return table;
}

bool find(hash_table table, string s) {
    int hash = hash_function(59, s, table.size);
    if (find_by_value(&table.a[hash], s) == true) {
        std::cout << hash;
        return true;
    } else {
        return false;
    }
}

void remove(hash_table table, string s) {
    int hash = hash_function(59, s, table.size);
    if (find(table, s) == true) {
        remove_by_value(&table.a[hash], s);
    }
}

int main() {
}
