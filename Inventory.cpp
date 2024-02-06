#include <utility>
#include "Inventory.h"

// Allow the compiler to define the remaining
// comparison operators
using namespace std::rel_ops;

//------------------------------------------------------------------------------
Inventory::Node::Node()
    :data(Item(0, "Air"), 0)
{
    this->next = nullptr;
}

//------------------------------------------------------------------------------
Inventory::Node::Node(ItemStack s)
    :data(s)
{
    this->next = nullptr;
}

//------------------------------------------------------------------------------
Inventory::Inventory()
{
    this->head     = nullptr;
    this->tail     = nullptr;
    this->slots    = 10;
    this->occupied = 0;

    //std::cerr << Node().data << "\n";
}

//------------------------------------------------------------------------------
Inventory::Inventory(int n)
{
    this->head     = nullptr;
    this->tail     = nullptr;
    this->slots    = n;
    this->occupied = 0;
}

//------------------------------------------------------------------------------
Inventory::Inventory(const Inventory &src) {
    this->head = nullptr;
    this->tail = nullptr;
    this->slots = src.slots;
    this->occupied = src.occupied;
    Node* srcNode = src.head;
    while (srcNode != nullptr) {
        this->addItemStackNoCheck(srcNode->data);
        srcNode = srcNode->next;
    }
}


//------------------------------------------------------------------------------
Inventory::~Inventory() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = tail = nullptr;
}


//------------------------------------------------------------------------------
bool Inventory::isFull() const {
    return occupied == slots;
}


//------------------------------------------------------------------------------
void Inventory::display(std::ostream &outs) const
{
    outs << " -Used " << occupied << " of " << slots << " slots" << "\n";

    Node* it = head;
    while(it != nullptr){
        outs << "  " << it->data << "\n";

        it = it->next;
    }
}

//------------------------------------------------------------------------------
Inventory& Inventory::operator=(Inventory rhs)
{
    std::swap(*this, rhs);
    return *this;
}

//------------------------------------------------------------------------------
void swap(Inventory& lhs, Inventory& rhs)
{
    using std::swap;

    swap(lhs.head, rhs.head);
    swap(lhs.tail, rhs.tail);
    swap(lhs.slots, rhs.slots);
    swap(lhs.occupied, rhs.occupied);
}

//------------------------------------------------------------------------------
Inventory::Node* Inventory::findMatchingItemStackNode(const ItemStack& itemStack) {
    Node* current = head;
    while (current != nullptr) {
        if (current->data == itemStack) return current;
        current = current->next;
    }
    return nullptr;
}

//------------------------------------------------------------------------------
void Inventory::mergeStacks(ItemStack& lhs, const ItemStack& rhs) {
    int totalQuantity = lhs.size() + rhs.size(); // Calculate total quantity
    int quantityToAdd = totalQuantity - lhs.size(); // Determine additional quantity needed
    lhs.addItems(quantityToAdd); // Adjust lhs quantity to the total
}

//------------------------------------------------------------------------------
void Inventory::addItemStackNoCheck(ItemStack itemStack) {
    Node* newNode = new Node(itemStack);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    ++occupied; // Assuming 'occupied' tracks the number of stacks, not individual items
}

