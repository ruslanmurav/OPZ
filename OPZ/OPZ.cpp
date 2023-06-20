#include <iostream>
using namespace std;

struct StackOPERATION
{
    char oper;
    int priority;
    StackOPERATION* next = nullptr;
}*head = nullptr;

struct StackSYMB
{
    char symbolic;
    double value = 0;
    StackSYMB* next = nullptr;
};

struct StackVALUE
{
    double value;
    StackVALUE* next = nullptr;
};

int get_length(StackOPERATION* head)
{
    int size = 1;
    while (head != nullptr)
    {
        cout << head->oper << " ";
        head = head->next;
        size++;
    }
    return size;
}

int get_length(StackSYMB* head)
{
    int size = 1;
    while (head != nullptr)
    {
        cout << head->symbolic << " ";
        head = head->next;
        size++;
    }
    return size;
}


void print(StackOPERATION* head)
{
    while (head != nullptr)
    {
        cout << head->oper << " ";
        head = head->next;
    }
}

void print(StackSYMB* head)
{
    while (head != nullptr)
    {
        cout << head->symbolic << "=" << head->value << "; ";
        head = head->next;
    }
}


int get_prior(char);

void push(char value, int priority, StackOPERATION*& head)
{
    StackOPERATION* new_element = new StackOPERATION;
    new_element->oper = value;
    new_element->priority = priority;
    new_element->next = head;
    head = new_element;
}

void push(double value,  StackVALUE*& head)
{
    StackVALUE* new_element = new StackVALUE;
    new_element->value = value;
    new_element->next = head;
    head = new_element;
}

void push(char symb, double value, StackSYMB*& head)
{
    StackSYMB* new_element = new StackSYMB;
    new_element->symbolic = symb;
    new_element->value = value;
    new_element->next = head;
    head = new_element;
}


char pop(StackOPERATION*& head)
{
    char value = head->oper;
    StackOPERATION* temp = head;
    head = head->next;
    delete temp;
    return value;
}

char pop(StackSYMB*& head)
{
    char value = head->symbolic;
    StackSYMB* temp = head;
    head = head->next;
    delete temp;
    return value;
}

double pop(StackVALUE*& head)
{
    double value = head->value;
    StackVALUE* temp = head;
    head = head->next;
    delete temp;
    return value;
}

bool CheckLetter(char character)
{
    if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z'))
    {
        return true;
    }
    return false;
}

bool check_prior(char character, StackOPERATION* head)
{
    StackOPERATION* temp = head;
    int priority = get_prior(character);

    while (temp != nullptr)
    {
        if (temp->priority >= priority)
        {
            return false;
        }
        temp = temp->next;
    }
    return true;
}

bool check_repeat(char value, StackSYMB* head)
{
    while (head != nullptr)
    {
        if (value == head->symbolic)
        {
            return true;
        }
        head = head->next;
    }
    return false;
}

int get_prior(char character)
{
    int priority = 0;
    if (character == '+' || character == '-')
    {
        priority = 1;
    }
    else if (character == '*' || character == '/')
    {
        priority = 2;
    }
    else if (character == '^')
    {
        priority = 3;
    }
    return priority;
}


bool CheckOperation(char string)
{
    if (string == '-' || string == '+' || string == '*' || string == '/' || string == '^')
    {
        return true;
    }
    return false;
}

void inputString(char* buffer) 
{
    cout << "Введите строку: ";
    cin.getline(buffer, 255);
}

double get_value(char symb , StackSYMB* shead)
{
    while (shead != nullptr)
    {
        if (shead->symbolic == symb)
        {
            return shead->value;
        }
        shead = shead->next;
    }
    return 0;

}

StackSYMB* get_symbolyc(char* OPZstring)
{
    double value;
    StackSYMB* shead = nullptr;

    while (*OPZstring != '\0')
    {
        if (CheckLetter(*OPZstring))
        {
            if (!check_repeat(*OPZstring, shead))
            {
                cout << "Введите значение " << *OPZstring << ": ";
                cin >> value;
                push(*OPZstring, value, shead);
            }
        }
        OPZstring++;
    }
    return shead;
}

double calculating(char* OPZstring)
{
    StackSYMB* shead = get_symbolyc(OPZstring);
    StackVALUE* vhead = nullptr;
    double result = 0, first_operand, second_operand;

    while (*OPZstring != '\0')
    {
        if (CheckLetter(*OPZstring))
        {
            push(get_value(*OPZstring, shead), vhead);
            OPZstring++;
            continue;
        }
        else
        {
            second_operand = pop(vhead);
            first_operand = pop(vhead);

            switch (*OPZstring)
            {
            case '+':
                push(first_operand + second_operand, vhead);
                break;
            case '-':
                push(first_operand - second_operand, vhead);
                break;
            case '/':
                push(first_operand / second_operand, vhead);
                break;
            case '*':
                push(first_operand * second_operand, vhead);
                break;
            case '^':
                push(pow(first_operand, second_operand), vhead);
                break;
            default:
                break;
            };
            OPZstring++;
        }
    }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
    return pop(vhead);
}

int main()
{
    setlocale(LC_ALL, "ru");
    int iOutput = 0;
    double result = 0;
    char main_string[255]{"x*(y+a)/(y+b^w)-c\0"}, output_string[255]{};
    /*inputString(main_string);*/
    char* iter = main_string;

    while (*iter != '\0')
    {
        if (CheckLetter(*iter))
        {
            output_string[iOutput++] = *iter;
        }
        else if (CheckOperation(*iter))
        {
            if (check_prior(*iter, head))
            {
                int priority = get_prior(*iter);
                push(*iter, priority, head);
            }
            else
            {
                StackOPERATION* temp = head;
                int priority = get_prior(*iter);
                while (temp != nullptr && temp->priority >= priority)
                {
                    output_string[iOutput++] = pop(head);
                    temp = head;
                }
                push(*iter, priority, head);
            }
        }
        else if (*iter == '(')
        {
            push(*iter, 0, head);
        }
        else if (*iter == ')')
        {
            while (head != nullptr && head->oper != '(')
            {
                output_string[iOutput++] = pop(head);
            }
            if (head == nullptr)
            {
                cout << "Ошибка: неправильно расставлены скобки!" << endl;
                return 0;
            }
            else
            {
                pop(head); 
            }
        }
        else
        {
            cout << "Неизвестный символ: " << *iter << endl;
        }
        iter++;
    }

    while (head != nullptr)
    {
        output_string[iOutput++] = pop(head);
    }

    output_string[iOutput] = '\0';

    cout << "Выходная строка: " << output_string << endl;

    result = calculating(output_string);

    cout << "Результат вычисления: " << double(result);

    return 0;
}
