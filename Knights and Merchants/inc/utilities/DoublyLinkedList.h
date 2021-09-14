#ifndef KNIGHTS_AND_MERCHANTS_UTILITIES_DOUBLY_LINKED_LIST_H
#define KNIGHTS_AND_MERCHANTS_UTILITIES_DOUBLY_LINKED_LIST_H

#include <cstdlib>

namespace knights_and_merchants::utilities
{
    template<class T>
    struct Node
    {
        Node<T> * next;
        Node<T> * previous;
        int i8;
        T * i12;
    };

    template<class T>
    class DoublyLinkedList
    {
    public:
        DoublyLinkedList();

        ~DoublyLinkedList();

        bool add(int p0, T * p4);

        void clear();

        bool startIterateBegin();

        bool startIterateEnd();

        bool moveNext();

        bool movePrevious();

        bool unknown(int p0);

        [[nodiscard]]
        int unk001() const;

        [[nodiscard]]
        T * unk002() const;

        [[nodiscard]]
        Node<T> * getI0() { return i0; }

        [[nodiscard]]
        Node<T> * getI4() { return i4; }

    private:
        void reset();

        Node<T> * i0;
        Node<T> * i4;
    };

    template<class T>
    bool DoublyLinkedList<T>::unknown(int p0)
    {
        if (!startIterateBegin())
            return false;

        do {
            if (unk001() == p0)
                return true;
        } while (moveNext());

        return false;
    }

    template<class T>
    DoublyLinkedList<T>::DoublyLinkedList()
    {
        reset();
    }

    template<class T>
    DoublyLinkedList<T>::~DoublyLinkedList()
    {
        clear();
        reset();
    }

    template<class T>
    void DoublyLinkedList<T>::reset()
    {
        i0 = nullptr;
        i4 = nullptr;
    }

    template<class T>
    bool DoublyLinkedList<T>::startIterateBegin()
    {
        i4 = i0;
        return i4 != nullptr;
    }

    template<class T>
    bool DoublyLinkedList<T>::startIterateEnd()
    {
        if (!startIterateBegin())
            return false;

        while (i4->next != nullptr)
            i4 = i4->next;

        return true;
    }

    template<class T>
    bool DoublyLinkedList<T>::moveNext()
    {
        if (i4 == nullptr || i4->next == nullptr)
            return false;

        i4 = i4->next;
        return true;
    }

    template<class T>
    bool DoublyLinkedList<T>::movePrevious()
    {
        if (i4 == nullptr || i4->previous == nullptr)
            return false;

        i4 = i4->previous;
        return true;
    }

    template<class T>
    void DoublyLinkedList<T>::clear()
    {
        startIterateBegin();

        while (i4 != nullptr) {
            auto var4 = i4->next;
            free(i4);
            i4 = var4;
        }

        i0 = nullptr;
        i4 = nullptr;
    }

    template<class T>
    bool DoublyLinkedList<T>::add(int p0, T * p4)
    {
        auto * var8 = static_cast<Node<T> *>(malloc(sizeof(Node<T>)));
        if (var8 == nullptr)
            return false;

        var8->next = nullptr;
        var8->previous = nullptr;
        var8->i8 = p0;
        var8->i12 = p4;

        if (i0 != nullptr) {
            Node<T> * var4 = i0;

            while (var4->next != nullptr)
                var4 = var4->next;

            var4->next = var8;
            var8->previous = var4;
        } else {
            i0 = var8;
        }

        return true;
    }

    template<class T>
    int DoublyLinkedList<T>::unk001() const
    {
        return (i4 != nullptr) ? i4->i8 : 0;
    }

    template<class T>
    T * DoublyLinkedList<T>::unk002() const
    {
        return (i4 != nullptr) ? i4->i12 : nullptr;
    }
}

#endif
