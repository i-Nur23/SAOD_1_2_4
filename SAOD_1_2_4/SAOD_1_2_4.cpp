#include <locale>
#include <set>
#include <ctime>
#include <iostream>

using namespace std;

struct StackElement
{
    int info;
    StackElement* next = NULL;
};

void InitStacks(StackElement** stack1, StackElement** stack2) // Инициализация стеков
{
    *stack1 = NULL;
    *stack2 = NULL;
}

bool isEmpty(StackElement* sp) // Проверка стека на пустоту
{
    if (sp == NULL)
    {
        return true;
    }
    return false;
}

void PrintStack(StackElement* sp) // Вывод текущего состояния стека
{
    StackElement* current = sp;
    cout << "Стек: ";
    while (current != NULL)
    {
        cout << current->info << " ";
        current = current->next;
    }
}

int CheckedInput(int begin, int end) // Ввод целочисленного значения с проверкой
{
    int choice;
    while (true) 
    {
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Вводите данные корректно: ";
            continue;
        }
        cin.ignore(32767, '\n');
        if (choice < begin || choice > end)
        {
            cout << "Вводите данные корректно: ";
            continue;
        }
        break;
    }
    return choice;
}

int CheckedInput() // Ввод целочисленного значения с проверкой
{
    int choice;
    while (true)
    {
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Вводите данные корректно: ";
            continue;
        }
        cin.ignore(32767, '\n');
        break;
    }
    return choice;
}

void Push(StackElement** sp, StackElement* newSp) // Добавление нового элемента в стек
{
    newSp->next = *sp;
    *sp = newSp;   
}

StackElement* Pop(StackElement** sp) // Удаление элемента из стека
{
    if (!isEmpty(*sp))
    {
        StackElement* pTemp = *sp;
        *sp = (* sp)->next;
        return pTemp;
    }
    else
    {
        cout << "Стек пуст";
        return NULL;
    }
}

void DeleteAll(StackElement* sp) // Очищение стека 
{
    StackElement* current = sp;
    while (current != NULL)
    {
        delete Pop(&current);
    }
}


void CallMenu(StackElement* mainSp, StackElement* subSp) // Основное меню
{
    bool work{ true };
    while (work)
    {
        cout << "Выберите действие:\n1 - Проверка пустоты стека\n2 - Добавить элемент\n";
        cout << "3 - Удалить элемент\n4 - Вывод основного стека\n5 - Добавление нескольких элементов\n6 - Вывод вспомогательного стека.\n7 - Завершение работы\n";
        cout << "Введите номер действия: ";
        int choice = CheckedInput(1,7);
        int count, way;
        StackElement* newSp;
        switch (choice)
        {
        
        case 1:
            if (isEmpty(mainSp))
            {
                cout << "Стек пустой";
            }
            else
            {
                cout << "Стек не пустой";
            }
            cout << "\n\n";
            break;
        case 2:
            cout << "Как вы собираетесь добавить элемент?\n1 - Создать новый элемент\n2 - Добавить из вспомогательного стека\nВыберите действие: ";
            way = CheckedInput(1, 2);
            switch (way)
            {
            case 1:
                int number;
                cout << "Какое число хотите ввести? Число: ";
                number = CheckedInput();
                newSp = new StackElement;
                newSp->info = number;
                Push(&mainSp, newSp);
                break;
            case 2:
                if (!isEmpty(subSp))
                {
                    Push(&mainSp, Pop(&subSp));
                }
                else
                {
                    cout << "Вспомогательный стек пустой";
                }
                break;
            default:
                break;
            }
            cout << "\n\n";
            break;
        
        case 3:
            cout << "Как вы собираетесь удалить элемент?\n1 - Удалить элемент\n2 - Добавить в вспомогательный стек\nВыберите действие: ";
            way = CheckedInput(1, 2);
            switch (way)
            {
            case 1:
                delete Pop(&mainSp);
                break;
            case 2:
                Push(&subSp,Pop(&mainSp));
                break;
            default:
                break;
            }
            cout << "\n\n";
            break;
        
        case 4:
            if (isEmpty(mainSp))
            {
                cout << "В стеке нет элементов";
            }
            else 
            {
                PrintStack(mainSp);
            }
            cout << "\n\n";
            break;
        
        case 5:
            cout << "Введите кол-во новых элементов (до 100): ";
            count = CheckedInput(0,100);
            for (size_t i = 0; i < count; i++)
            {
                StackElement* newSp = new StackElement;
                newSp->info = rand();
                Push(&mainSp,newSp);
            }
            cout << "\n\n";
            break;
        
        case 6:
            if (isEmpty(subSp))
            {
                cout << "В стеке нет элементов";
            }
            else
            {
                PrintStack(subSp);
            }
            cout << "\n\n";
            break;
        
        case 7:
            work = false;
            DeleteAll(mainSp);
            DeleteAll(subSp);
            break;
        
        default:
            break;
        }
    }
}

int main()
{
    setlocale(LC_ALL,"RUS");
    srand(static_cast<unsigned int>(time(0)));
    StackElement* mainSp;
    StackElement* subSp;
    InitStacks(&mainSp, &subSp);
    CallMenu(mainSp,subSp);
    return 0;
}