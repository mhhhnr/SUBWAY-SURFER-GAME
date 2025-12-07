#ifndef GAMELIST_H
#define GAMELIST_H

template <typename T>
class GameList {
private:
    T* items;
    int capacity;
    int size;

    void resize();

public:
    GameList();
    ~GameList();
    void add(const T& item);
    T& get(int index);
    void removeAt(int index);
    int getSize() const;
    void clear();
};

template <typename T>
void GameList<T>::resize() {
    capacity *= 2;
    T* newItems = new T[capacity];
    for (int i = 0; i < size; i++) {
        newItems[i] = items[i];
    }
    delete[] items;
    items = newItems;
}

template <typename T>
GameList<T>::GameList() : capacity(10), size(0) {
    items = new T[capacity];
}

template <typename T>
GameList<T>::~GameList() {
    delete[] items;
}

template <typename T>
void GameList<T>::add(const T& item) {
    if (size >= capacity) {
        resize();
    }
    items[size++] = item;
}

template <typename T>
T& GameList<T>::get(int index) {
    return items[index];
}

template <typename T>
void GameList<T>::removeAt(int index) {
    if (index < 0 || index >= size) return;
    for (int i = index; i < size - 1; i++) {
        items[i] = items[i + 1];
    }
    size--;
}

template <typename T>
int GameList<T>::getSize() const {
    return size;
}

template <typename T>
void GameList<T>::clear() {
    size = 0;
}

#endif