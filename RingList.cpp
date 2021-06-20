#include <iostream>

using namespace std;

// струткура состоит из элемента
struct  node
{
    // элемент
    int Element;
    // указатель на пред эелемент
    node* BeforeElement;
    // указатель на след элемент
    node* AfterElement;
};

class RingList
{
private:
    node* phead;
public:
    // Создание и удаление заглавного звена
    RingList() { phead = new(node); };
    ~RingList() { delete phead; };
    // Функции создания и удаления кольцевого списка
    void Construction();
    void Clearing();
    // Функции вывода кольцевого спсика
    void PrintForward();
    void PrintBack();
    // Функции вставки звеньев в колцьевой список
    void InsertAfter(int, node*);
    void InsertBefore(int, node*);
    // Функции удаление звеньев
    void DeleteLink(node*);
    void DeleteLinkAfter(node*);
    // Функции поиска звеньев
    node* SearchForward(int);
    node* SearchBack(int);
    // Функция поиска звена по счету
    node* SearchLink(int);
    // Функция возвращает true, если в функции осталось одно звено, и false, если звеньев больше
    int CheckLink(node*);

};

void RingList::Construction()
{
    node* temp;
    int elementValue;

    // 
    temp = phead;
    temp->AfterElement = NULL;
    
    cout << "Input element:\n";
    cin >> elementValue;
    
    while (elementValue != 0)
    {
        temp->AfterElement = new(node){ elementValue, temp, NULL };
        temp = temp->AfterElement;
        cout << "Input element:\n";
        cin >> elementValue;
    }
    temp->AfterElement = phead->AfterElement;
    (temp->AfterElement)->BeforeElement = temp;
    //(phead->AfterElement)->BeforeElement = temp;
}

void RingList::PrintForward()
{
    node* temp;
    temp = phead->AfterElement;
    cout << "Ring list items: ";
    if (temp != NULL)
    {
        cout << temp->Element << " ";
        temp = temp->AfterElement;
        while (temp != phead->AfterElement)
        {
            cout << temp->Element << " ";
            temp = temp->AfterElement;
        }
    }
    else
    {
        cout << "empty" << endl;
    }
    cout << endl;
}

void RingList::PrintBack()
{
    node* temp;
    temp = (phead->AfterElement)->BeforeElement;
    cout << "Ring list items reverse: ";
    
    if (temp != NULL)
    {
        cout << temp->Element << " ";
        temp = temp->BeforeElement;
        while (temp->AfterElement != phead->AfterElement)
        {
            cout << temp->Element << " ";
            temp = temp->BeforeElement;
        }
    }
    else
    {
        cout << "empty" << endl;
    }
    cout << endl;
}

void RingList::Clearing()
{
    node* temp1, * temp2;

    temp1 = phead;
    temp2 = temp1->AfterElement;
    do
    {
        temp1 = temp2;
        temp2 = temp2->AfterElement;
        delete temp1;
    } while (temp2 != phead->AfterElement);
}

void RingList::InsertAfter(int elementValue, node* Res)
{
    node* temp;
    if (Res->AfterElement != phead->AfterElement)
    {
        temp = new(node) {elementValue, Res, Res->AfterElement };
        (Res->AfterElement)->BeforeElement = temp;
        Res->AfterElement = temp;
    }
    else
    {
        temp = new(node){ elementValue, Res, phead->AfterElement };
        (phead->AfterElement)->BeforeElement = temp;
        Res->AfterElement = temp;
    }
}

void RingList::InsertBefore(int elementValue, node* Res)
{
    node* temp;
    temp = new(node){ elementValue, Res->BeforeElement, (Res->BeforeElement)->AfterElement };
    (Res->BeforeElement)->AfterElement = temp;
    Res->BeforeElement = temp;
}

void RingList::DeleteLink(node* Res)
{
    if ((*Res).AfterElement != (*phead).AfterElement)
    {
        phead->AfterElement = Res->AfterElement;
        (Res->AfterElement)->BeforeElement = Res->BeforeElement;
        (Res->BeforeElement)->AfterElement = Res->AfterElement;
        delete Res;
    }
    else  if ((*Res).AfterElement == Res)
    {
        //В кольце единственное звено.
        (*phead).AfterElement = NULL;
        delete Res;
    }
    else
    {
        (Res->BeforeElement)->AfterElement = (*phead).AfterElement;
        ((*phead).AfterElement)->BeforeElement = Res->BeforeElement;
        delete Res;
    }
}

void RingList::DeleteLinkAfter(node* Res)
{
    node* temp;

    if (Res->AfterElement != (*phead).AfterElement)
    {
        temp = Res->AfterElement;
        ((Res->AfterElement)->AfterElement)->BeforeElement = Res;
        Res->AfterElement = (Res->AfterElement)->AfterElement;
        delete temp;
    }
    else  if ((*Res).AfterElement == Res)
    {
        //В кольце единственное звено.
        (*phead).AfterElement = NULL;
        delete Res;
    }
    else
    {
        //Удаляемое звено - первое в кольце и не единственное.
        temp = Res->AfterElement;
        phead->AfterElement = (Res->AfterElement)->AfterElement;
        (temp->AfterElement)->BeforeElement = Res;
        Res->AfterElement = temp->AfterElement;
        delete temp;
    }
}

node* RingList::SearchForward(int elementValue)
{
    node* Res;
    node* temp;

    Res = NULL;
    temp = phead->AfterElement;

    while (Res == NULL)
    {
        if (temp->Element == elementValue)
            Res = temp;
        else 
            temp = temp->AfterElement;
    }
    cout << endl << "ELEMENT - " << Res->Element << endl;
    return Res;
}

node* RingList::SearchBack(int elementValue)
{
    node* Res;
    node* temp;
    Res = NULL;
    temp = (phead->AfterElement)->BeforeElement;

    while (Res == NULL)
    {
        if (temp->Element == elementValue)
            Res = temp;
        else
            temp = temp->BeforeElement;
    }
    cout << endl << "ELEMENT - " << Res->Element << endl;
    return Res;
}

node* RingList::SearchLink(int elementValue)
{
    node* Res;
    node* temp;
    int counter = 1;

    Res = NULL;
    temp = phead->AfterElement;

    while (Res == NULL)
    {
        if (counter == elementValue)
            Res = temp;
        else
        {
            temp = temp->AfterElement;
            counter++;
        }
    }
    cout << endl << "ELEMENT - " << Res->Element << endl;
    return Res;
}

int RingList::CheckLink(node* Res)
{
    if (Res->AfterElement == Res)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}


int main()
{
    RingList ring;
    node* Res;
    int elementValue;
    int linkValue;

    ring.Construction();
    
    ring.PrintForward();
    ring.PrintBack();
    
    // Считалочка
    cout << "Delete link counter: ";
    cin >> linkValue;
    Res = ring.SearchLink(linkValue);
    if (Res != NULL)
    {
        do
        {
            ring.DeleteLink(Res);
            ring.PrintForward();
            ring.PrintBack();
            Res = ring.SearchLink(linkValue);
        } while (ring.CheckLink(Res));
    }
    else cout << "None link\n";

    // Основные операции с кольцевым списком
    /*
    cout << "After which element is the new element inserted: ";
    cin >> elementValue;
    cout << "Input element new link: ";
    cin >> linkValue;
    Res = ring.SearchForward(elementValue);
    if (Res != NULL)
    {
        ring.InsertAfter(linkValue, Res);
        ring.PrintForward();
        ring.PrintBack();
    }
    else cout << "None link\n";
    
    cout << "Before which element is the new element inserted: ";
    cin >> elementValue;
    cout << "Input element new link: ";
    cin >> linkValue;
    Res = ring.SearchBack(elementValue);
    if (Res != NULL)
    {
        ring.InsertBefore(linkValue, Res);
        ring.PrintForward();
        ring.PrintBack();
    }
    else cout << "None link\n";
    
    cout << "Enter the link you want to delete: ";
    cin >> linkValue;
    Res = ring.SearchForward(linkValue);
    if (Res != NULL)
    {
        ring.DeleteLink(Res);
        ring.PrintForward();
        ring.PrintBack();
    }
    else cout << "None link\n";
    
    cout << "Enter the link after which you want to delete it: ";
    cin >> linkValue;
    Res = ring.SearchForward(linkValue);
    if (Res != NULL)
    {
        ring.DeleteLinkAfter(Res);
         ring.PrintForward();
        ring.PrintBack();
    }
    else cout << "None link\n";
    */

    ring.Clearing();
    

    return 0;
}