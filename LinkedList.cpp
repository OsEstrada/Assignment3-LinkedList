#include <iostream>
#include <string>
#include "assert.h"

using namespace std;

typedef std::string ItemType;

struct Node
{
    ItemType value;
    Node *next;
};

class LinkedList
{

private:
    Node *head;

public:
    //default constructor
    LinkedList();

    //copyConstructor
    LinkedList(const LinkedList &rhs);

    //Destroys all the dyanamically allocated memory
    ~LinkedList();

    //assignment operator
    const LinkedList &operator=(const LinkedList &rhs);

    //inserts val at the rear of the list
    void insertToRear(const ItemType &val);

    //Prints the LinkedList
    void printList() const;

    //Sets Item to the value at position i in this
    //LinkedList and return true, returns false if
    //there is no element i
    bool get(int i, ItemType &item) const;

    //Reverses the LinkedList
    void reverseList();

    //Prints LinkedList in reverse order
    void printReverse() const;

    //Appends the values of other onto the end of this
    //LinkedList.
    void append(const LinkedList &other);

    //Exchange the contents of this LinkedList with the other
    //one
    void swap(LinkedList &other);

    //Returns the number of items in the Linked List
    int size() const;
};

//LinkedList.cpp

LinkedList ::LinkedList()
{
    head = nullptr;
};

LinkedList ::LinkedList(const LinkedList &rhs)
{
    Node *aux = rhs.head;
    //Hacemos null el head de nuestra lista
    head = nullptr;

    //1->2->3->4->null
    Node **list2 = &head;

    while (aux)
    {
        Node *n = new Node;
        n->value = aux->value;
        n->next = nullptr;

        if (!*list2)
        {
            *list2 = n;
        }
        else
        {
            Node *aux2 = *list2;
            while (aux2->next)
                aux2 = aux2->next;
            aux2->next = n;
        }
        aux = aux->next;
    }
};

LinkedList ::~LinkedList()
{
    Node **list = &head;
    if (!*list)
    {
        return;
    }
    else
    {
        Node *aux = *list, *next = nullptr;
        while (aux)
        {
            next = aux->next;
            free(aux); // C
            //delete aux; // C++ tambien llama al destructor de esa clase
            aux = next;
        }
        head = nullptr;
    }
};

//list1 = list2

const LinkedList &LinkedList ::operator=(const LinkedList &rhs)
{
    Node **list = &head;

    //Recorre la lista y elimina sus nodos (si es que tiene) desalojando la memoria reservada
    Node *aux = *list, *next = nullptr;
    while (aux)
    {
        next = aux->next;
        free(aux); // C
        aux = next;
    }
    head = nullptr;

    //Reutilizamos el puntero declarado anteriormente, y lo igualamos a la lista rhs
    //Luego de eso se repite el algoritmo para hacer un insertToRear
    aux = rhs.head;
    while (aux)
    {
        Node *n = new Node;
        n->value = aux->value;
        n->next = nullptr;

        if (!*list)
        {
            *list = n;
        }
        else
        {
            Node *aux2 = *list;
            while (aux2->next)
                aux2 = aux2->next;
            aux2->next = n;
        }
        aux = aux->next;
    }
    //Por ultimo se retorna la lista de la derecha actualizada
    return *this;
};

void LinkedList::insertToRear(const ItemType &val)
{
    Node *n = new Node;
    n->value = val;
    n->next = nullptr;
    Node **list2 = &head;
    if (!*list2)
    {
        *list2 = n;
    }
    else
    {
        Node *aux2 = *list2;
        while (aux2->next)
        {
            aux2 = aux2->next;
        }
        aux2->next = n;
    }
};

void LinkedList::printList() const
{
    Node *aux = head;
    while (aux)
    {
        cout << aux->value << " ";
        aux = aux->next;
    }
    cout << endl;
};

int LinkedList::size() const
{
    Node *aux = head;
    int counter = 0;
    while (aux)
    {
        counter++;
        aux = aux->next;
    }
    return counter;
}

//0->1->2....
bool LinkedList::get(int i, ItemType &item) const
{
    //Casos que falla
    if (i < 0)
    {
        return false;
    }
    if (i > size() - 1)
    {
        return false;
    }
    //Caso exitoso
    Node *aux = head;
    for (int j = 0; j < i; j++)
    {
        aux = aux->next;
    }
    item = aux->value;
    return true;
}

void LinkedList::reverseList()
{
    //La salida mas fácil para revertir esta lista simplemente enlazada es crear una nueva lista.
    Node *auxList = nullptr;
    //Si queremos que la lista nueva se inserte de manera invertida, podemos en lugar de insertar al final, insertar al inicio de la lista.
    //Para esto recorreremos la lista original, y a medida avanzemos en los nodos los insertaremos en auxList
    Node *originalList = head, *next = nullptr;
    while (originalList)
    {
        //Debemos insertar al inicio de la nueva lista, para esto es tan simple como poner la primera posicion de la lista original como el siguiente
        //elemento de la nueva lista
        Node *n = new Node;
        n->value = originalList->value;
        n->next = auxList;
        auxList = n;

        //Si ya copiamos el elemento de una lista a otra, entonces debemos limpiar la memoria.
        next = originalList->next;
        free(originalList); // C
        originalList = next;
    }
    delete originalList;
    head = auxList;
};

void LinkedList::printReverse() const
{
    //Al no poder usar recursividad, usare esta forma no muy eficiente
    //Guardare los datos en un arreglo
    //Declaramos una variable i que me ayudara a recorrer el arreglo y una variable n que guardara el tamaño de la lista
    int i = 0, n = size();
    //Declaro un arreglo de string de tamaño n (guardara los nombres que hay en la lista)
    string *a = new string[n];
    //recorro la lista y lleno el arreglo
    Node *aux = head;
    while (aux)
    {
        a[i] = aux->value;
        aux = aux->next;
        i++;
    }
    //Al conocer los indices del arreglo, lo recorro a la inversa y lo imprimo.
    for (i = n - 1; i >= 0; i--)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    //Liberamos la memoria reservada por el arreglo dinamico
    delete[] a;
}

void LinkedList::append(const LinkedList &other)
{
    //creo un nodo para recorrer mas facilmente la lista que queremos anexar
    Node *list = other.head;
    //recorremos la lista, y cada elemento que tenga la agregamos al final de nuestra lista actual. Podemos usar la funcion insertToRear
    //creada anteriormente
    while (list)
    {
        insertToRear(list->value);
        list = list->next;
    }
}

void LinkedList::swap(LinkedList &other)
{
    //Crearemos una nuevo objeto de tipo LinkedList, el cual almacenara temporalmente todo lo que tenga la lista other (aca la sobrecarga del operador "=" resulta util)
    LinkedList aux = other;
    other = *this;
    *this = aux;
}

int main(void)
{
    //TODO ESTO SON LAS PRUEBAS QUE YO HICE
    /* LinkedList ls;
    string s1 = "";

    cout << "Lista1" << endl;
    ls.insertToRear("Carl");
    ls.insertToRear("Hariette");
    ls.insertToRear("Eddie");
    ls.printList();

    cout << "Lista2" << endl;
    LinkedList ls2(ls);
    ls2.printList();

    ls.insertToRear("Cory");
    cout << "Lista1" << endl;
    ls.printList();

    cout << "List2" << endl;
    ls2.printList();

    cout << "get" << endl;
    ls.get(3, s1);
    cout << s1 << endl;

    ls2 = ls;
    ls.insertToRear("Laura");
    ls.printList();  //Laura
    ls2.printList(); // cory

    ls2.reverseList();
    cout<<"Reversed"<<endl;
    ls2.printList();
    ls2.printReverse();
    ls2.printList();

    ls2.append(ls);
    ls2.printList();

    cout<<"list1"<<endl;
    ls.printList();

    ls.swap(ls2);
    cout<<"after swap"<<endl;
    cout<<"list1"<<endl;
    ls.printList();
    cout<<"list2"<<endl;
    ls2.printList(); */

    //A PARTIR DE AQUI TODO ESTO SALE EN TU GUIA, SI NO TE TIRA NADA SIGNIFICA QUE FUNCIONA, COMO VERAS TIENES QUE IR PROBANDO UNO POR UNO.

    //Append function (todo esto esta en la guia)
    /* LinkedList e1;
    e1.insertToRear("devoe");
    e1.insertToRear("biv");
    e1.insertToRear("bell");
    LinkedList e2;
    e2.insertToRear("Big Boi");
    e2.insertToRear("Andre");
    e1.append(e2); // adds contents of e2 to the end of e1
    string s;
    assert(e1.size() == 5 && e1.get(3, s) && s == "Big Boi");
    assert(e2.size() == 2 && e2.get(1, s) && s == "Andre"); */

    //ReverseList (todo esto esta en la guia)
    /* LinkedList e1;
    e1.insertToRear("Norm");
    e1.insertToRear("Cliff");
    e1.insertToRear("Carla");
    e1.insertToRear("Sam");
    e1.reverseList(); // reverses the contents of e1
    string s;
    assert(e1.size() == 4 && e1.get(0, s) && s == "Sam"); */

    //Swap (todo esto esta en la guia)
    LinkedList e1;
    e1.insertToRear("D");
    e1.insertToRear("C");
    e1.insertToRear("B");
    e1.insertToRear("A");
    LinkedList e2;
    e2.insertToRear("Z");
    e2.insertToRear("Y");
    e2.insertToRear("X");
    e1.swap(e2); // exchange contents of e1 and e2
    string s;
    assert(e1.size() == 3 && e1.get(0, s) && s == "Z");
    assert(e2.size() == 4 && e2.get(2, s) && s == "B");

    return 0;
}