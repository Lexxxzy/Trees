#include<iostream>

using namespace std;

class BinarySearchTree
{
public:

    int size;
    int* array;

    void postOrder(int currentIndex);
    void addToTree(BinarySearchTree* A, BinarySearchTree* B, int size);

    void insert(int x);
    void search(int x);

    void inOrder(int currentIndex);
    void preOrder(int currentIndex);
    void print(int currentIndex);
    void parentPrintHandler(int x);

    int extendSize(int x);

    BinarySearchTree(int size) {
        this->size = extendSize(size);
        //cout << this -> size << endl;
        this->array = new int[this->size];
        for (int x = 0; x < this->size; x++) {
            array[x] = NULL;
        }
    }

};

int BinarySearchTree::extendSize(int x) {
    int value = 0;
    for (int i = 0; i < x +1 ; i++) { //максимально может быть x уровней, поэтому повотряем цикл x раз
        value = (2 * value) + 2;
    }
    return value;
}

void BinarySearchTree::insert(int x) {
    int currentIndex = 0;
    cout << "Добавление: " << x; //выводим что добавляем
    while (true) {
        if (array[currentIndex] == NULL) {
            array[currentIndex] = x;
            cout << " Индекс вставленного элемента: " << currentIndex << endl; //для пониманимания выводим на какой индекс встал элемент - левый 2i+1, правый 2i+2
            break; // выходим когда доходим до конца какой-то ветки(т.е. до листьев)
        }
        else if (array[currentIndex] <= x) { //идем вправо если элемент больше родителя
            if (array[currentIndex] == x) {
                cout << "ERROR!-- Повторяющийся элемент" << endl; //проверка на повторение элемента (если элемент с таким номером уже есть в дереве)
                break;
            }
            else
                cout << " Вправо ";
            currentIndex = (2 * currentIndex + 2);
        }
        else if (array[currentIndex] >= x) { //идем влево если элемент больше родителя
            if (array[currentIndex] == x) {
                cout << "ERROR!-- Повторяющийся элемент" << endl;
                break;
            }
            else
                cout << " Влево ";
            currentIndex = (2 * currentIndex + 1);
        }

    }
}

void BinarySearchTree::search(int x) { //функция поиска (если понадобиться)

    int currentIndex = 0;
    while (true) {
        if (array[currentIndex] == NULL) {
            cout << "Not Found" << endl;
            break;
        }
        if (array[currentIndex] == x) {
            cout << "Found at index: " << currentIndex << endl;
            break;
        }
        else if (array[currentIndex] < x) {
            currentIndex = (2 * currentIndex + 2);
        }
        else if (array[currentIndex] > x) {
            currentIndex = (2 * currentIndex + 1);
        }

    }

}

void BinarySearchTree::parentPrintHandler(int x) {
    while (x != 0) {
        x = (x - 1) / 2;
        cout << "---";
    }

}

void BinarySearchTree::inOrder(int currentIndex) {//симметричный
    if (array[currentIndex] != NULL) {
        inOrder(2 * currentIndex + 1);
        cout << array[currentIndex] << " ";
        inOrder(2 * currentIndex + 2);

    }
}

void BinarySearchTree::preOrder(int currentIndex) {//прямой порядок печати
    if (array[currentIndex] != NULL) {
        
        cout << array[currentIndex] << " ";
        preOrder(2 * currentIndex + 1);
        preOrder(2 * currentIndex + 2);
    }
}

void BinarySearchTree::print(int currentIndex) { //просто красивый принт(для тестов)
    if (array[currentIndex] != NULL) {
        print(2 * currentIndex + 1);
        parentPrintHandler(currentIndex);
        cout << array[currentIndex] << " " << endl;
        print(2 * currentIndex + 2);
    }
}

// обратный порядок, для добавления в массив и последующей вставки в дерево A 
//(i,temp временные переменные i-итератор для массива, temp массив для хранения обратного порядка
int i = 0;
int* temp = new int[100];
void BinarySearchTree::postOrder(int currentIndex) {

    if (array[currentIndex] != NULL) {
        
        postOrder(2 * currentIndex + 1);
        postOrder(2 * currentIndex + 2);
        temp[i]= array[currentIndex];
        i++;
    }
}

void BinarySearchTree::addToTree(BinarySearchTree* A, BinarySearchTree* B, int size)
{
    B->postOrder(0); //Обходим дерево B в обратном порядке

    for (int i = 0;i < size;i++)
    {
        A->insert(temp[i]);
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    BinarySearchTree A(6);
    BinarySearchTree B(6);

    for (int i = 0;i < 6;i++)
    {
        A.insert(1 + rand() % 100);
    }

    cout << "\n";

    for (int i = 0;i < 6;i++)
    {
        B.insert(1 + rand() % 100);
    }

    A.inOrder(0);
    cout << "\n";
    B.preOrder(0);
    cout << "\n";

    A.addToTree(&A, &B, 6);

    

    A.preOrder(0);

    //очищаем память
    delete[] A.array;
    delete[] B.array;
};